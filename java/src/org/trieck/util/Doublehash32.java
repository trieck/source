package org.trieck.util;

import java.nio.*;

public class Doublehash32 implements Hash32 {

	public int hash(byte[] v) {
		
		Hash32 H = new FNVHash32();
		
		int r = H.hash(v);
		
		byte[] bytes = new byte[Integer.SIZE / Byte.SIZE];
		ByteBuffer buf = ByteBuffer.allocate(Integer.SIZE / Byte.SIZE);
		
		buf.order(ByteOrder.LITTLE_ENDIAN);
		buf.putInt(r);
		buf.flip();
		buf.get(bytes);
		
		return H.hash(bytes);
	}

}
