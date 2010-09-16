package org.pixielib.apps.ecalc;

public class MachineException extends Exception {
    /**
     *
     */
    private static final long serialVersionUID = 1L;
    public static final int ME_DIV_BY_ZERO = 0; // division by zero
    public static final int ME_ASSIGNLITERAL = 1; // assignment to a literal
    public static final int ME_NONVARASSIGN = 2; // non-variable assignment

    /**
     * Public ctor
     *
     * @param e the exception code
     */
    public MachineException(int code) {
        super(getMessage(code));
    }

    /**
     * Retrieve exception message for an exception code
     *
     * @param code the exception code
     * @return the exception message
     */
    private static String getMessage(int code) {
        switch (code) {
            case ME_DIV_BY_ZERO:
                return "Attempt to divide by zero.";
            case ME_ASSIGNLITERAL:
                return "Attempt to assign to a literal.";
            case ME_NONVARASSIGN:
                return "Attempt to assign to a non-variable.";
            default:
                return "Unknown error.";
        }
    }

}
