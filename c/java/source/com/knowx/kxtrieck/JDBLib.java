
package com.knowx.kxtrieck;

import java.io.*;
import java.util.*;

/**
********************************************************************************
** JDBLib.java
**
** Java SQL Server db-lib interface
**
** @author Thomas A. Rieck
** @version 0.0.1 --- 05-JUN-2001<BR><BR>
** <TT>
** Revision History<BR>
** ----------------<BR>
** 0.0.1  05-JUN-2001	Initial writing and development.<BR>
**
** </TT>
**
********************************************************************************
*/

public class JDBLib extends Object {
	
	static {
		System.loadLibrary("jdblib");
	}
	
	/*
	 * construction
	 */
	JDBLib() {
		super();
	}
	
	/*
	 * allocate a login record
	 */
	public native int dblogin();
	
	/*
	 * free login record
	 */
	public native void dbfreelogin(int login); 
	
	/*
	 * open a database connection
	 */
	public native int dbopen(int login, String server); 
	
	/*
	 * close a database connection
	 */
	public native int dbclose(int process); 
	
	/*
	 * set user name
	 */
	public native int dbsetluser(int login, String username);
	
	/*
	 * set password
	 */
	public native int dbsetlpwd(int login, String username);
	
	/*
	 * send command string
	 */
	public native int dbcmd(int process, String cmd);
		
	/* 
	 * execute SQL
	 */
	public native int dbsqlexec(int process);
	
	/* 
	 * main entry point 
	 */
	public static void main(String[] args) {
		JDBLib dblib = new JDBLib();
		int record = 0, process = 0;
		
		try {
			// allocate a login record
			record = dblib.dblogin();
			System.out.println("Your login record is: " + record);
			
			// set the username
			dblib.dbsetluser(record, "trieck");
			
			// set the password
			dblib.dbsetlpwd(record, "erskine1");
			
			// open database connection
			process = dblib.dbopen(record, "KXQATXN1");
			if (process == 0) 
				throw new Exception("Unable to open database connection.");
				
			System.out.println("Your process connection is: " + process);
			
			int retcode = dblib.dbcmd(process, "select * from nothing");
			retcode = dblib.dbsqlexec(process);			
			
		} catch (Exception E) {
			System.err.println(E);
		} finally {
			System.out.println("Freeing process connection: " + process + "...");
			dblib.dbclose(process);		
			System.out.println("Freeing login record: " + record + "...");
			dblib.dbfreelogin(record);				
		}		
	}
	
}

