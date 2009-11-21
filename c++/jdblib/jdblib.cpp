
#include "common.h"
#include <jni.h>

static HINSTANCE hInstance;

static int err_handler(DBPROCESS *dbproc, int severity, int dberr,
                       int oserr, const char *dberrstr, const char *oserrstr);

BOOL WINAPI DllMain(HINSTANCE hInstDLL, DWORD dwReason, LPVOID lpvReserved)
{
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		hInstance = hInstDLL;
		dbinit();

		// supply a user function to handle DB-Library errors
		dberrhandle(err_handler);

		break;
	case DLL_PROCESS_DETACH:
		dbwinexit();
	}

	return TRUE;
}

/*
 * allocate a login record
 */
JNIEXPORT jint JNICALL Java_com_knowx_kxtrieck_JDBLib_dblogin(JNIEnv * env, jobject obj)
{
	PLOGINREC record = dblogin();

	return reinterpret_cast<jint>(record);
}

/*
 * free login record
 */
JNIEXPORT void JNICALL Java_com_knowx_kxtrieck_JDBLib_dbfreelogin(JNIEnv * env,
        jobject obj, jint record)
{
	PLOGINREC precord = reinterpret_cast<PLOGINREC>(record);

	dbfreelogin(precord);
}

/*
 * open a database connection
 */
JNIEXPORT jint JNICALL Java_com_knowx_kxtrieck_JDBLib_dbopen(JNIEnv * env,
        jobject obj, jint record, jstring server)
{
	PLOGINREC precord = reinterpret_cast<PLOGINREC>(record);

	// convert the jstring to PCSTR
	jboolean iscopy;
	PCSTR pserver = env->GetStringUTFChars(server, &iscopy);

	// open the database conenction
	PDBPROCESS process = dbopen(precord, pserver);

	// release the allocated string
	env->ReleaseStringUTFChars(server, pserver);

	if (process != NULL) {
		// associate environment with dbprocess
		// for use in error handler
		dbsetuserdata (process, (void *)env);
	}

	return reinterpret_cast<jint>(process);
}

/*
 * close a database connection
 */
JNIEXPORT jint JNICALL Java_com_knowx_kxtrieck_JDBLib_dbclose(JNIEnv *env,
        jobject obj, jint process)
{
	PDBPROCESS pprocess = reinterpret_cast<PDBPROCESS>(process);

	return dbclose(pprocess);
}

/*
 * set user name
 */
JNIEXPORT jint JNICALL Java_com_knowx_kxtrieck_JDBLib_dbsetluser(JNIEnv *env,
        jobject obj, jint record, jstring username)
{
	PLOGINREC precord = reinterpret_cast<PLOGINREC>(record);

	// convert the jstring to PCSTR
	jboolean iscopy;
	PCSTR pusername = env->GetStringUTFChars(username, &iscopy);

	// set the user name
	RETCODE retcode = DBSETLUSER(precord, pusername);

	// release the allocated string
	env->ReleaseStringUTFChars(username, pusername);

	return retcode;
}

/*
 * set password
 */
JNIEXPORT jint JNICALL Java_com_knowx_kxtrieck_JDBLib_dbsetlpwd(JNIEnv *env,
        jobject obj, jint record, jstring pwd)
{
	PLOGINREC precord = reinterpret_cast<PLOGINREC>(record);

	// convert the jstring to PCSTR
	jboolean iscopy;
	PCSTR ppwd = env->GetStringUTFChars(pwd, &iscopy);

	// set the password
	RETCODE retcode = DBSETLPWD(precord, ppwd);

	// release the allocated string
	env->ReleaseStringUTFChars(pwd, ppwd);

	return retcode;
}

/*
 * send command string
 */
JNIEXPORT jint JNICALL Java_com_knowx_kxtrieck_JDBLib_dbcmd(JNIEnv *env,
        jobject obj, jint process, jstring cmd)
{
	PDBPROCESS pprocess = reinterpret_cast<PDBPROCESS>(process);

	// convert the jstring to PCSTR
	jboolean iscopy;
	PCSTR pcmd = env->GetStringUTFChars(cmd, &iscopy);

	RETCODE retcode = dbcmd(pprocess, pcmd);

	// release the allocated string
	env->ReleaseStringUTFChars(cmd, pcmd);

	return retcode;
}

JNIEXPORT jint JNICALL Java_com_knowx_kxtrieck_JDBLib_dbsqlexec(JNIEnv *env,
        jobject obj, jint process)
{
	PDBPROCESS pprocess = reinterpret_cast<PDBPROCESS>(process);
	return dbsqlexec(pprocess);
}

/*
 * error handling
 */
int err_handler(DBPROCESS *dbproc, int severity, int dberr,
                int oserr, const char *dberrstr, const char *oserrstr)
{
	// we need to look up the user's environment
	// that requires disabling the error handler
	// to ensure we don't have an infinite recursion problem
	dberrhandle(NULL);

	JNIEnv *env = static_cast<JNIEnv*>(dbgetuserdata(dbproc));
	if (env != NULL) {
		jclass cls = env->FindClass("java/lang/Exception");
		env->ThrowNew(cls, dberrstr);
	}

	// reenable the error handler
	dberrhandle(err_handler);

	return INT_CANCEL;
}