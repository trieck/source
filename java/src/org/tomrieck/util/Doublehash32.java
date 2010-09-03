package org.tomrieck.util;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class Doublehash32 implements Hash32 {

    public int hash(byte[] v) {

        final Hash32 H = new FNVHash32();

        final int r = H.hash(v);

        final byte[] bytes = new byte[Integer.SIZE / Byte.SIZE];
        final ByteBuffer buf = ByteBuffer.allocate(Integer.SIZE / Byte.SIZE);

        buf.order(ByteOrder.LITTLE_ENDIAN);
        buf.putInt(r);
        buf.flip();
        buf.get(bytes);

        return H.hash(bytes);
    }

}
