package org.trieck.apps.ecalc;

public class CompilerException extends Exception {
    /**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	public static final int CE_NAN = 0; // not a number

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
        switch (code) {
            case CE_NAN:
                return "A number was expected and not found.";
            default:
                return "Unknown error.";
        }
    }

}
