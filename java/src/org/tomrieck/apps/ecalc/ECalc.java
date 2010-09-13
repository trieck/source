package org.tomrieck.apps.ecalc;

import java.io.*;

public class ECalc {

    private final Machine machine;

    public ECalc() {
        machine = Machine.getInstance();
    }

    public void run(String file) throws IOException {
        FileInputStream fis;

        try {
            fis = new FileInputStream(file);
        } catch (final FileNotFoundException e) {
            throw new IOException(e.toString());
        }

        run(fis);
    }

    public void run(InputStream is) throws IOException {

        final BufferedReader reader = new BufferedReader(new InputStreamReader(
                is));

        String line;
        while ((line = reader.readLine()) != null) {
            machine.run(line);
        }

        is.close();
    }

    public static void main(String[] args) {

        final ECalc calculator = new ECalc();

        try {
            if (args.length > 0) {
                calculator.run(args[0]);
            } else {
                calculator.run(System.in);
            }
        } catch (final IOException e) {
            System.err.println(e);
        }

    }
}
