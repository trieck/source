package org.pixielib.apps.ecalc;

public class CompilerException extends Exception {
    public static final int CE_NAN = 0; // not a number
    /**
     *
     */
    private static final long serialVersionUID = 1L;

    /**
     * Public ctor
     *
     * @param e the exception code
     */
    public CompilerException(int code) {
        super(getMessage(code));
    }

    /**
     * Retrieve exception message for an exception code
     *
     * @param code the exception code
     * @return the exception message
     */
    private static String getMessage(int code) {
        if (code == CE_NAN) {
            return "A number was expected and not found.";
        }
        return "Unknown error.";
    }

}
