package org.trieck.apps;

import java.text.DecimalFormat;
import java.nio.*;
import org.trieck.util.*;

public class HashTest {

	private static final DecimalFormat df = new DecimalFormat("#.00");
	
	/* compare bits from key/result */
	private float compare(int i, int j) {
		int b = 32, diff = 0;

		while (b-- > 0) {
			if ((i & (1 << b)) != (j & (1 << b))) 
				diff++;
		}

		return diff / (float)32;
	}

	/* return base2 formatted string */
	private String bits(int h) {
		StringBuffer output = new StringBuffer();

		int b = 32;

		while (b-- > 0) {
			output.append(((h & (1 << b)) != 0) ? "1" : "0");
		}

		return output.toString();
	}
	
	/* hash compare for "avalanche effect" */	
	private void hashtest(Hash32 fnc) {
		int h = 0, i, j = 0, k = 0, t = 0;
		float f = 0, g = 0;
		String b, c;
		byte[] bytes = new byte[Integer.SIZE / Byte.SIZE];
		
		ByteBuffer buf = ByteBuffer.allocate(Integer.SIZE / Byte.SIZE);
		buf.order(ByteOrder.LITTLE_ENDIAN);
		
		for (i = 0; i < 32; i++) {
			if (i > 0) k = h;
			j = (j << 1) | 1;
			
			buf.clear();
			buf.putInt(j);
			buf.flip();
			buf.get(bytes);
			
			h = fnc.hash(bytes);
			
			b = bits(j); c = bits(h);
			System.out.print(b + ' ' + c);
			if (i > 0) {
				g += f = compare(k , h);
				System.out.print("  ");
				if (f * 100 < 10) System.out.print('*');
				System.out.println(df.format(100 * f));
				t++;
			} else {
				System.out.println("  N/A");
			}
		}

	    System.out.print("     avg. diff: ");
	    System.out.println(df.format(100 * (g / t)));
	}

	public static void main(String[] args) {
		HashTest tester = new HashTest();
		
		System.out.println("hash32");
		System.out.println("------------");
		tester.hashtest(new FNVHash32());
		
		System.out.println("\ndoublehash32");
		System.out.println("------------");
		tester.hashtest(new Doublehash32());
	}
}
