package org.tomrieck.bencode;

import java.io.*;

public class BEDecoder {

    /* input stream */
    private final PushbackInputStream is;

    /**
     * Construct a decoder from an input stream
     *
     * @param s, the input stream
     */
    private BEDecoder(InputStream s) {
        is = new PushbackInputStream(s);
    }

    /**
     * static method to decode a bencoded stream
     *
     * @return decoded object
     * @throws IOException
     */
    public static BEObject decode(InputStream s) throws IOException {
        final BEDecoder decoder = new BEDecoder(s);
        return decoder.loadObject();
    }

    /**
     * Load an object from a bencoded stream
     *
     * @return decoded object
     * @throws IOException
     */
    private BEObject loadObject() throws IOException {
        final int t = getTok();

        switch (t) {
            case BEObject.BET_DICT:
                return loadDictionary();
            case BEObject.BET_INTEGER:
                return loadInteger();
            case BEObject.BET_LIST:
                return loadList();
            case BEObject.BET_STRING:
                return loadString();
        }

        throw new IOException("unexpected token: \"" + (char) t + "\"");
    }

    /**
     * Load an integer
     *
     * @return BEInteger
     * @throws IOException
     */
    private BEInteger loadInteger() throws IOException {
        final StringBuffer buf = new StringBuffer();

        int c;
        while ((c = is.read()) != 'e' && c != -1) {
            buf.append((char) c);
        }

        return new BEInteger(Long.parseLong(buf.toString()));
    }

    /**
     * Load a string
     *
     * @return BEString
     * @throws IOException
     */
    private BEString loadString() throws IOException {
        final StringBuffer blen = new StringBuffer();

        int c;
        while ((c = is.read()) != ':' && c != -1) {
            blen.append((char) c);
        }

        final int nlen = Integer.parseInt(blen.toString());
        final byte[] buf = new byte[nlen];

        is.read(buf);

        return new BEString(buf);
    }

    /**
     * Load a dictionary
     *
     * @return BEDictionary
     * @throws IOException
     */
    private BEDictionary loadDictionary() throws IOException {

        final BEDictionary d = new BEDictionary();
        BEString k;
        BEObject v;

        int c;
        while ((c = peek()) != 'e' && c != -1) {
            k = loadString();
            v = loadObject();
            d.set(k, v);
        }

        is.read();

        return d;
    }

    /**
     * Load a list
     *
     * @return BEList
     * @throws IOException
     */
    private BEList loadList() throws IOException {
        final BEList l = new BEList();

        int c;
        while ((c = peek()) != 'e' && c != -1) {
            l.addObject(loadObject());
        }

        is.read();

        return l;
    }

    /**
     * Get next token from input
     *
     * @return token id
     * @throws IOException
     */
    private int getTok() throws IOException {
        final int c = is.read();

        switch (c) {
            case 'd':
                return BEObject.BET_DICT;
            case 'i':
                return BEObject.BET_INTEGER;
            case 'l':
                return BEObject.BET_LIST;
            default:
                if (Character.isDigit(c) || c == '-') {
                    is.unread(c);
                    return BEObject.BET_STRING;
                }
        }

        return c;
    }

    /**
     * Peek one character of the input
     *
     * @return the peeked character
     * @throws IOException
     */
    private int peek() throws IOException {
        final int c = is.read();
        is.unread(c);
        return c;
    }

    /**
     * Application entry point
     *
     * @param args application arguments
     */
    public static void main(String[] args) {
        if (args.length == 0) {
            System.err.println("usage: BEDecoder file");
            return;
        }

        try {
            final FileInputStream is = new FileInputStream(args[0]);
            final BEObject o = BEDecoder.decode(is);

            final FileOutputStream os = new FileOutputStream("d:/tmp/out.benc");
            BEEncoder.encode(o, os);

        } catch (final FileNotFoundException e) {
            System.err.println(e);
            System.exit(-1);
        } catch (final IOException ioe) {
            System.err.println(ioe);
            System.exit(-2);
        }

    }
}
