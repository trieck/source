package org.pixielib.bencode;

public abstract class BEObject {

	public static final int BET_INTEGER = 1;
	public static final int BET_STRING = 2;
	public static final int BET_LIST = 3;
	public static final int BET_DICT = 4;

	public abstract int getType();

}
