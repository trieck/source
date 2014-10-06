package org.pixielib.util;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class DoubleHash64 {

    public static long hash(String s) {
        return hash(s.getBytes());
    }

    public static long hash(byte[] b) {

        long l = Hash64.hash(b);

        final byte[] bytes = new byte[Long.SIZE / Byte.SIZE];
        final ByteBuffer buf = ByteBuffer.allocate(Long.SIZE / Byte.SIZE);

        buf.order(ByteOrder.LITTLE_ENDIAN);
        buf.putLong(l);
        buf.flip();
        buf.get(bytes);

        return Hash64.hash(bytes);
    }
}
