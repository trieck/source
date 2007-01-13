#include <memory.h>
#include <stdlib.h>
#include "javani.h"

int main(int argc, char *argv[])
{
	JavaNI jni;
	JavaVMInitArgs args;
	memset(&args, 0, sizeof(JavaVMInitArgs));
	args.version = JNI_VERSION_1_2;

	if (!jni.CreateJVM(&args)) {
		exit(1);
	}

	jclass cls = jni.FindClass("java/lang/String");

	return 0;
}