package org.trieck.apps.ecalc;

import java.util.Stack;

public class Machine {

    private static Machine instance;    // Singleton instance
    private Stack<Datum> machinestack;         // Machine stack
    /**
     * Private ctor
     */
    private Machine() {
        machinestack = new Stack<Datum>();
        new Stack<Object>();
    }

    /**
     * Singleton
     *
     * @return the singleton instance
     */
    public static Machine getInstance() {
        if (instance != null)
            return instance;
        return (instance = new Machine());
    }


    /**
     * Run the machine
     *
     * @param input the program as a string
     */
    public void run(String input) {
        Compiler compiler = new Compiler();

        try {
            exec(compiler.compile(input));
        } catch (CompilerException ce) {
            ;
        } catch (MachineException me) {
            ;
        }
    }

    /**
     * Execute a program
     *
     * @program the program
     */
    private void exec(Program program)
            throws MachineException {

    }

    /**
     * Addition instruction
     */
    public final Instruction plus = new Instruction() {
        public void execute() throws MachineException {
            Datum d1 = machinestack.pop();
            Datum d2 = machinestack.pop();

            Datum d3 = new Datum();
            d3.value = d1.value + d2.value;

            machinestack.push(d3);
        }
    };

    /**
     * Subtraction instruction
     */
    public final Instruction minus = new Instruction() {
        public void execute() throws MachineException {
            Datum d1 = machinestack.pop();
            Datum d2 = machinestack.pop();

            Datum d3 = new Datum();
            d3.value = d2.value - d1.value;

            machinestack.push(d3);
        }
    };

    /**
     * Unary minus instruction
     */
    public final Instruction unaryminus = new Instruction() {
        public void execute() throws MachineException {
            Datum d = machinestack.pop();
            d.value = -d.value;
            machinestack.push(d);
        }
    };

    /**
     * Multiply instruction
     */
    public final Instruction mult = new Instruction() {
        public void execute() throws MachineException {
            Datum d1 = machinestack.pop();
            Datum d2 = machinestack.pop();

            Datum d3 = new Datum();
            d3.value = d1.value * d2.value;

            machinestack.push(d3);
        }
    };

    /**
     * Divide instruction
     */
    public final Instruction divide = new Instruction() {
        public void execute() throws MachineException {
            Datum d1 = machinestack.pop();
            Datum d2 = machinestack.pop();

            if (d1.value == 0)
                throw new MachineException(MachineException.ME_DIV_BY_ZERO);

            Datum d3 = new Datum();
            d3.value = d2.value / d1.value;

            machinestack.push(d3);
        }
    };

    /**
     * Modulo instruction
     */
    public final Instruction mod = new Instruction() {
        public void execute() throws MachineException {
            Datum d1 = machinestack.pop();
            Datum d2 = machinestack.pop();

            if (d1.value == 0)
                throw new MachineException(MachineException.ME_DIV_BY_ZERO);

            Datum d3 = new Datum();
            d3.value = d2.value % d1.value;

            machinestack.push(d3);
        }
    };

    /**
     * Exponent instruction
     */
    public final Instruction pow = new Instruction() {
        public void execute() throws MachineException {
            Datum d1 = machinestack.pop();
            Datum d2 = machinestack.pop();

            Datum d3 = new Datum();
            d3.value = Math.pow(d2.value, d1.value);

            machinestack.push(d3);
        }
    };

    /**
     * Variable assignment
     */
    public final Instruction assign = new Instruction() {
        public void execute() throws MachineException {
            Datum d1 = machinestack.pop();
            Datum d2 = machinestack.pop();

            if (d2.symbol == null)
                throw new MachineException(MachineException.ME_ASSIGNLITERAL);
            if (d2.symbol.getType() != Symbol.ST_VAR &&
                    d2.symbol.getType() != Symbol.ST_UNDEF)
                throw new MachineException(MachineException.ME_NONVARASSIGN);

            d2.symbol.setValue(d1.value);
            d2.symbol.setType(Symbol.ST_VAR);

            machinestack.push(d1);
        }
    };

    /**
     * Pop top value from machine stack
     */
    public final Instruction pop = new Instruction() {
        public void execute() throws MachineException {
            machinestack.pop();
        }
    };
}
