/////////////////////////////////////////////////////////////////////////////
//
// PROTOCOL.H : Databot protocol definition
//
// Copyright(c) 2008, Thomas A. Rieck, All Rights Reserved.
//

#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#define DEFAULT_PORT	(5009)

/////////////////////////////////////////////////////////////////////////////
//
// Message packages passed between client and server are in the following 
// format:
//
// BYTE		DESCRIPTION
// --------------------------------------------------------------------------
// [00..19]	The SHA1 message digest of the remaining message.
//
// [20..23] The size in bytes of the remaining message.
//
// [24..??] The remaining XML message.
//

/////////////////////////////////////////////////////////////////////////////
//
// Messages are essentially dictionaries encoded in a simple XML format.
// Dictionaries are defined to be a set of key/value pairs.
// The structure of a message complies with the following grammar:
//
//		message		:= dictionary
//
//		dictionary	:= '<dict>' pairs '</dict>'
//
//		pairs		:= pair
//					 | pair pairs
//
//		pair		:= key value
//
//		key			:= '<key>' characters '</key>'
//
//		value		:= dictionary
//					 | array
//					 | string
//					 | int
//					 | float
//
//		array		:= '<array>' values '<array>'
//
//		values		:= value
//					 | value values
//
//		string		:= '<string>' characters </string>'
//
//		int			:= '<int>' [0-9]+ '</int>'
//
//		float		:= '<real>' [0-9]*\.[0-9]+ '</real>'
//

#endif // __PROTOCOL_H__