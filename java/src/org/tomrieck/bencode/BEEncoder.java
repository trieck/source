package org.pixielib.bencode;

import java.io.IOException;
import java.io.OutputStream;
import java.util.Iterator;
import java.util.Map;

public class BEEncoder {

    private static final byte BEGIN_DICT = 'd';

    private static final byte BEGIN_LIST = 'l';

    private static final byte BEGIN_INT = 'i';

    private static final byte END_OBJECT = 'e';

    private final OutputStream os;

    private BEEncoder(OutputStream os) {
        this.os = os;
    }

    public static void encode(BEObject o, OutputStream os) throws IOException {

        final BEEncoder encoder = new BEEncoder(os);
        encoder.encodeObject(o);
    }

    private void encodeObject(BEObject o) throws IOException {

        switch (o.getType()) {
            case BEObject.BET_INTEGER:
                encodeInteger((BEInteger) o);
                break;
            case BEObject.BET_STRING:
                encodeString((BEString) o);
                break;
            case BEObject.BET_DICT:
                encodeDictionary((BEDictionary) o);
                break;
            case BEObject.BET_LIST:
                encodeList((BEList) o);
                break;
        }
    }

    private void encodeInteger(BEInteger i) throws IOException {
        beginInteger();
        writeRawInt(i.getVal());
        endObject();
    }

    private void encodeString(BEString s) throws IOException {
        writeRawInt(s.length());
        writeByte((byte) ':');
        writeRawString(s);
    }

    private void encodeDictionary(BEDictionary d) throws IOException {

        beginDictionary();

        final Iterator<Map.Entry<BEString, BEObject>> it = d.getIterator();
        while (it.hasNext()) {
            final Map.Entry<BEString, BEObject> entry = it.next();
            final BEString key = entry.getKey();
            final BEObject val = entry.getValue();

            encodeString(key);
            encodeObject(val);
        }

        endObject();
    }

    private void encodeList(BEList l) throws IOException {

        beginList();

        for (int i = 0; i < l.size(); i++) {
            encodeObject(l.getAt(i));
        }

        endObject();
    }

    private void beginDictionary() throws IOException {
        os.write(BEGIN_DICT);
    }

    private void beginList() throws IOException {
        os.write(BEGIN_LIST);
    }

    private void beginInteger() throws IOException {
        os.write(BEGIN_INT);
    }

    private void endObject() throws IOException {
        os.write(END_OBJECT);
    }

    private void writeBytes(byte[] b) throws IOException {
        os.write(b);
    }

    private void writeRawInt(long l) throws IOException {
        final String s = new String("" + l);
        writeBytes(s.getBytes());
    }

    private void writeByte(byte b) throws IOException {
        os.write(b);
    }

    private void writeRawString(BEString s) throws IOException {
        writeBytes(s.getBytes());
    }

}
