package org.trieck.pixievm;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Map;
import java.util.TreeMap;

public class Monitor {

	private final BufferedReader in = new BufferedReader(new InputStreamReader(
			System.in));
	private final Map<String, Command> table = new TreeMap<String, Command>();

	/**
	 * Command interface
	 */
	public interface Command {
		void exec(String[] tokens);
	}

	/**
	 * Help command
	 */
	private final Command Help = new Command() {
		public void exec(String[] tokens) {
			System.out.println("?   print help screen");
			System.out.println("r   print registers");
			System.out.println("q   quit");
		}
	};

	/**
	 * Quit command
	 */
	private final Command Quit = new Command() {
		public void exec(String[] tokens) {
			System.exit(0);
		}
	};

	/**
	 * Registers command
	 */
	private final Command Registers = new Command() {
		public void exec(String[] tokens) {
			/*
			 * Object[] args = { toHex(cpu.getPC()), toHex(cpu.getA()),
			 * toHex(cpu.getIn()[0]), toHex(cpu.getIn()[1]),
			 * toHex(cpu.getIn()[2]), toHex(cpu.getIn()[3]), toHex(cpu.getIX()),
			 * toHex(cpu.getSP()), cpu.getBreakFlag() ? 1 : 0,
			 * cpu.getIntDisableFlag() ? 1 : 0, cpu.getZeroFlag() ? 1 : 0,
			 * cpu.getCarryFlag() ? 1 : 0 };
			 * 
			 * System.out.println("ADDR AC IX I0 I1 I2 I3 SP ----BIZC");
			 * System.out.println(MessageFormat.format("{0} {1} {2} {3} {4} {5}
			 * {6} {7} {8}{9}{10}{11}", args));
			 */
		}
	};

	/**
	 * Public ctor
	 */
	public Monitor() {
		init();
	}

	public void init() {
		table.put("?", Help);
		table.put("help", Help);
		table.put("q", Quit);
		table.put("x", Quit);
		table.put("r", Registers);
	}

	/**
	 * Run the monitor
	 */
	public void run() throws IOException {
		prompt();
		String line;
		while ((line = in.readLine()) != null) {
			dispatch(line);
			prompt();
		}
	}

	/**
	 * Dispatch command
	 * 
	 * @param line
	 */
	public void dispatch(String line) {
		final String[] tokens = line.toLowerCase().split("[ \r\t\n]+");
		if (tokens.length == 0) {
			System.out.println("?");
		} else {
			final Command c = table.get(tokens[0]);
			if (c == null) {
				System.out.println("?");
			} else {
				c.exec(tokens);
			}
		}
	}

	private void prompt() {
		System.out.print("> ");
	}
}
