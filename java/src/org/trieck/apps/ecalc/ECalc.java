package org.trieck.apps.ecalc;

import java.io.*;

public class ECalc {

    private Machine machine;

    public ECalc() {
        machine = Machine.getInstance();
    }

    public void run(String file) throws IOException {
        FileInputStream fis;

        try {
            fis = new FileInputStream(file);
        } catch (FileNotFoundException e) {
            throw new IOException(e.toString());
        }

        run(fis);
    }

    public void run(InputStream is) throws IOException {

        BufferedReader reader =
                new BufferedReader(
                        new InputStreamReader(is));

        String line;
        while ((line = reader.readLine()) != null) {
            machine.run(line);
        }

        is.close();
    }

    public static void main(String[] args) {

        ECalc calculator = new ECalc();

        try {
            if (args.length > 0) {
                calculator.run(args[0]);
            } else {
                calculator.run(System.in);
            }
        } catch (IOException e) {
            System.err.println(e);
        }

    }
}
