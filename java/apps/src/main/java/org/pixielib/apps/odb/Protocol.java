package org.pixielib.apps.odb;

public class Protocol {

	/* request / response keys */
	public static final String KEY_REQUEST_FNC = "function";
	public static final String KEY_REQUEST_OTYPE = "object_type";
	public static final String KEY_POOL_ID = "pool_id";
	public static final String KEY_OBJECT_ID = "object_id";
	public static final String KEY_OBJECT_VAL = "object_val";

	/* function identifiers */
	public static final int FNC_MKPOOL = 0x001;
	public static final int FNC_CREATE = 0x002;
	public static final int FNC_DESTROY = 0x003;
	public static final int FNC_GET = 0x004;
	public static final int FNC_SET = 0x005;
	public static final int FNC_KILLPOOL = 0x006;

	/* object types */
	public static final int OT_INTEGER = 0x001;
	public static final int OT_STRING = 0x002;
	public static final int OT_LIST = 0x003;
	public static final int OT_DICT = 0x004;

	/* response specific keys */
	public static final String KEY_RESPONSE_CD = "response_code";
	public static final String KEY_RESPONSE_MSG = "response_msg";

	/* response codes */
	public static final int E_OK = 0x000;
	public static final int E_BAD_REQUEST = 0x001;
	public static final int E_INC_REQUEST = 0x002;
	public static final int E_BAD_FNC = 0x003;
	public static final int E_CANT_CREATE = 0x004;
	public static final int E_CANT_DESTROY = 0x005;
	public static final int E_CANT_GET = 0x006;
	public static final int E_CANT_SET = 0x007;
}
