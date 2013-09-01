package org.pixielib.pixievm.assembler;

import java.io.IOException;

public class Assembler {

	/**
	 * Public ctor
	 */
	public Assembler() {
	}

	/**
	 * Assemble file
	 *
	 * @param filename
	 * @throws IOException
	 * @throws ParserException
	 */
	public void assemble(String filename) throws IOException, ParserException {
		final Parser parser = new Parser(filename);
		parser.parse();
	}

	/**
	 * Application entry point
	 *
	 * @param args
	 */
	public static void main(String[] args) {
		if (args.length < 1) {
			usage();
		}

		final Assembler assembler = new Assembler();
		try {
			assembler.assemble(args[0]);
		} catch (final IOException e) {
			System.err.println(e.getMessage());
			System.exit(1);
		} catch (final ParserException pe) {
			System.err.println(pe.getMessage());
			System.exit(2);
		}
	}

    /* Display usage message and exit */

	public static void usage() {
		System.err.println("usage: assembler file");
		System.exit(1);
	}
}
