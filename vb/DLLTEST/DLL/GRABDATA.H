////////////////
// grabdata.h //
////////////////

#include <windows.h>
#include <sql.h>
#include <sqlext.h> 
#include <ole2.h>
#include <stdio.h>
#include <stdlib.h>
#include <compobj.h>    
#include <dispatch.h> 
#include <olenls.h>  


extern "C"{
extern int FAR PASCAL _export GrabData(LPSAFEARRAY FAR *ppsa);
}