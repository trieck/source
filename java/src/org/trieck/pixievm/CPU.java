package org.trieck.pixievm;

/**
 * 16-bit Big Endian Machine
 * Support for 4 16-bit general purpose registers: A, B, C, D.
 * Register SP is a 16-bit stack pointer.
 * Register IP is a 16-bit instruction pointer.
 * Flags register holds various CPU state flags ie. break, interrupt disable,
 * zero and carry.
 *
 * Each general purpose register can be referred to by it's high byte and low byte:
 *
 * ----------- ----------- ----------- -----------
 * |   AX    | |   BX    | |   CX    | |   DX    |
 * ----------- ----------- ----------- -----------
 * | AH | AL | | BH | BL | | CH | CL | | DH | DL |
 * ----------- ----------- ----------- -----------
 */
public class CPU {

    /* Registers */
    private char a, b, c, d, sp, ip, flags;

    private static final int BRK_FLAG = 0x08;
    private static final int INT_DISABLE_FLAG = 0x04;
    private static final int ZERO_FLAG = 0x02;
    private static final int CARRY_FLAG = 0x01;

    private static final Memory memory = Memory.getInstance();
    private static CPU instance = null;

    public boolean getBreakFlag() {
        return ((flags & BRK_FLAG) >> 3) != 0;
    }

    private void setBreakFlag() {
        flags |= BRK_FLAG;
    }

    public boolean getIntDisableFlag() {
        return ((flags & INT_DISABLE_FLAG) >> 2) != 0;
    }

    private void setIntDisableFlag() {
        flags |= INT_DISABLE_FLAG;
    }

    public boolean getZeroFlag() {
        return ((flags & ZERO_FLAG) >> 1) != 0;
    }

    private void setZeroFlag() {
        flags |= ZERO_FLAG;
    }

    private void clearZeroFlag() {
        flags &= ~ZERO_FLAG;
    }

    private void setCarryFlag() {
        flags |= CARRY_FLAG;
    }

    private void clearCarryFlag() {
        flags &= ~CARRY_FLAG;
    }

    private void setZero(boolean t) {
        if (t) setZeroFlag();
        else clearZeroFlag();
    }

    private void setZeroFlag(int t) {
        setZero((t & 0xFF) == 0);
    }

    public boolean getCarryFlag() {
        return getCarry() != 0;
    }

    private int getCarry() {
        return flags & CARRY_FLAG;
    }

    private void setCarryFlag(boolean t) {
        if (t) setCarryFlag();
        else clearCarryFlag();
    }

    private interface Instruction {
        public void exec();
    }

    /* Public ctor */
    private CPU() {
    }

    public static CPU getInstance() {
        if (instance == null)
            instance = new CPU();
        return instance;
    }
}
