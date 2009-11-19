package org.trieck.pixievm;

import java.io.IOException;
import java.io.InputStream;

public class Machine {

    private Memory memory = Memory.getInstance();
    private Monitor monitor = new Monitor();

    /**
     * Public ctor
     *
     * @throws IOException
     */
    public Machine() throws IOException {
        init();
    }

    /**
     * Initialize machine
     *
     * @throws IOException
     */
    private void init() throws IOException {
        load_rom("/bin/chargen.rom", MMU.CHARGEN_ADDRESS, MMU.CHARGEN_SIZE);
    }

    /**
     * Display application note
     */
    private void notice() {
        System.out.print("\nPixieVM version 0.0.1, Copyright (c) 2006 Thomas A. Rieck\n");
    }

    /**
     * Load rom image into memory
     *
     * @param resource
     * @param address
     * @param size
     * @throws IOException
     */
    private void load_rom(String resource, int address, int size) throws IOException {
        InputStream is = getResource(resource);
        if (is == null) throw new IOException("can't load image \"" + resource + "\".");
        int read = memory.load(is, address, size);
        if (read != size) throw new IOException("rom size mismatch for image \"" + resource + "\".");
        is.close();
    }

    /**
     * Get resource as stream
     *
     * @param resource
     * @return stream
     */
    private InputStream getResource(String resource) {
        return getClass().getResourceAsStream(resource);
    }

    /**
     * Run the machine
     */
    public void run() throws IOException {
        notice();
        monitor.run();
    }

    public static void main(String[] args) {
        try {
            Machine machine = new Machine();
            machine.run();
        } catch (IOException e) {
            System.err.println(e.getMessage());
            System.exit(1);
        }
    }
}
