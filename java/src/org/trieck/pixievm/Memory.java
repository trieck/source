package org.trieck.pixievm;

import java.io.IOException;
import java.io.InputStream;

public class Memory {

    private static final int MEM_SIZE = 0x10000;
    private byte[] memory;
    private static Memory instance = null;

    /**
     * Public ctor
     */
    private Memory() {
        memory = new byte[MEM_SIZE];
    }

    /**
     * Singleton instance
     */
    public static Memory getInstance() {
        if (instance == null)
            instance = new Memory();
        return instance;
    }

    /**
     * Load stream into memory
     *
     * @param is
     * @param address
     * @param len
     * @return number of bytes read
     * @throws IOException
     */
    int load(InputStream is, int address, int len) throws IOException {
        return is.read(memory, address, len);
    }

    /**
     * Fetch a byte
     *
     * @param address
     * @return byte @ address
     */
    byte fetch(int address) {
        return memory[address & 0x0000FFFF];
    }

    /**
     * Store a byte
     *
     * @param address
     * @param b       byte
     */
    void store(int address, byte b) {
        memory[address & 0x0000FFFF] = b;
    }
}
