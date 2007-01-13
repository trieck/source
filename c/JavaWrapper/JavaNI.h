/////////////////////////////////////////////////////////////////////////////
//
//	JAVANI.H : Java Native Interface Class Wrapper
//
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __JAVANI_H__
#define __JAVANI_H__

#include <jni.h>

/////////////////////////////////////////////////////////////////////////////
class JavaNI
{
// Construction / Destruction
public:
	JavaNI();
	virtual ~JavaNI();

// Interface
	bool CreateJVM(JavaVMInitArgs *args);
	jclass FindClass(const char *name);

// Implementation
private:
	JavaVM* jvm;
	JNIEnv* env;
};

/////////////////////////////////////////////////////////////////////////////

#endif // __JAVANI_H__
