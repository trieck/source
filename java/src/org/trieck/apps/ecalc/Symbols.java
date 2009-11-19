package org.trieck.apps.ecalc;

import java.util.HashMap;
import java.util.Map;

public class Symbols {

	private static Symbols instance; // Singleton
	Map<String, Symbol> symbols;

	/**
	 * Private ctor
	 */
	private Symbols() {
		symbols = new HashMap<String, Symbol>();
		init();
	}

	/**
	 * Singleton instance
	 * 
	 * @return the singleton instance
	 */
	public static Symbols getInstance() {
		if (instance != null) {
			return instance;
		}
		return (instance = new Symbols());
	}

	/**
	 * Lookup symbol by name
	 * 
	 * @param key
	 *            the key
	 * @return the symbol if found or null
	 */
	public static Symbol lookup(String key) {
		final Symbol symbol = instance.symbols.get(key);
		return symbol;
	}

	/**
	 * Install function / procedure definition
	 * 
	 * @param name
	 *            the symbol name
	 * @param type
	 *            the symbol type
	 * @param defn
	 *            the function definition
	 */
	public static Symbol install(String name, int type, Instruction defn) {
		Symbol symbol = instance.symbols.get(name);
		if (symbol == null) {
			symbol = new Symbol();
		}

		symbol.setType(type);
		symbol.setDefn(defn);

		instance.symbols.put(name, symbol);

		return symbol;
	}

	/**
	 * Install floating point literal symbol
	 * 
	 * @name the symbol name
	 * @type the symbol type
	 * @value the numeric value
	 */
	public static Symbol install(String name, int type, double value) {
		Symbol symbol = instance.symbols.get(name);
		if (symbol == null) {
			symbol = new Symbol();
		}

		symbol.setType(type);
		symbol.setValue(value);

		instance.symbols.put(name, symbol);

		return symbol;
	}

	/**
	 * Install built-in symbol
	 * 
	 * @param name
	 *            the symbol name
	 * @param i
	 *            the instruction
	 */
	private Symbol install(String name, Instruction i) {
		Symbol symbol = symbols.get(name);
		if (symbol == null) {
			symbol = new Symbol();
		}

		symbol.setType(Symbol.ST_BUILTIN);
		symbol.setInstr(i);

		symbols.put(name, symbol);

		return symbol;
	}

	/**
	 * One time initialization for symbol table
	 */
	private void init() {

		final Machine machine = Machine.getInstance();

		// Install built-in functions
		install("pow", machine.pow);

		// Install keywords
	}

}
