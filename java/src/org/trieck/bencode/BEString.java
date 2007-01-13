package org.trieck.bencode;

import java.nio.charset.*;
import java.nio.*;
import java.util.*;

public class BEString extends BEObject implements Comparable<BEString> {

	private byte[] data;
	private static CharsetDecoder cd;
	
	static {
		try {
			cd = Charset.defaultCharset().newDecoder();
		} catch (UnsupportedCharsetException e) {
			System.err.println(e);
		}
	}
	
	public BEString(byte[] data) {
		this.data = new byte[data.length];
		System.arraycopy(data, 0, this.data, 0, data.length);
	}
	
	public BEString(String str) {
        this(str.getBytes());
	}
	
	public String toString() {		
		CharBuffer cb = null;
		
		try {
			cb = cd.decode(ByteBuffer.wrap(data));
		} catch (CharacterCodingException e) {
			System.err.println(e);
			return "";
		}
		
		return cb.toString();
	}
	
	public int length() { return data.length; }
	public byte[] getBytes() { return data; }
	
	@Override
	public int getType() { return BEObject.BET_STRING; }

	@Override
	public int hashCode() {
		final int PRIME = 31;
		int result = 1;
		result = PRIME * result + Arrays.hashCode(data);
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		final BEString other = (BEString) obj;
		if (!Arrays.equals(data, other.data))
			return false;
		return true;
	}
	
    public int compareTo(BEString rhs) {
    	if (this == rhs)
    		return 0;
    	
    	int len1 = length();
    	int len2 = rhs.length();
    	int n = Math.min(len1, len2);
    	byte v1[] = data;
    	byte v2[] = rhs.data;
    	int i = 0, j = 0;

    	while (n-- != 0) {
    		byte b1 = v1[i++];
    		byte b2 = v2[j++];
    		if (b1 != b2) {
    		    return b1 - b2;
    		}
    	}
    		
    	return len1 - len2;
    }

}
