/////////////////////////////////////////////////////////////////////////////
//
// WSCRIPT.JAVA : implementation for the WestScript class
//
// This class implements the westscript language which consists of html text
// containing special variables and functions and objects starting with a
// $ sign. During evaluation, the variables are substituted with their text
// values and functions are evalueted and replaced with their return value.
//
//
//          westscript :=  html
//                      |  html function westscript
//                      |  'westscript'
//
//          html       :=  characters other then $ and '
//                      |  empty string
//
//          function   :=  $name
//                      |  $name(arglist)
//                      |  $name.name(arglist)
//                      |  $name.name
//                      |  $name = expression
//                      |  $function
//
//          arglist    :=  argument
//                      |  argument, arglist
//
//          argument   :=  'westscript'
//                      |  function
//                      |  constant
//
//          name       :=  alpha numberic string including _
//
//          constant   :=  alpha numeric string including _ + - .
//                      |  empty string
//
//
// A westscript function can write to it's output stream and/or return a
// string value.  Output to a function's output stream is not evalueted
// further.  The string returned by a westscript function is evaluated
// untill it contains no more functions or variables.
//
// Copyright (C) 1995-1997 West Publishing Corporation.
// All rights reserved.
//
// Ported to Java by Thomas A. Rieck
// Copyright (C) 2004 KnowX.com
//

package org.trieck.WestScript;

import java.io.IOException;
import java.io.OutputStream;

public class WestScript {

    private String script;
    private int index;

    public WestScript() {
        script = new String();
        index = 0;
    }

    public WestScript(String str) {
        this();
        script = str;
    }

    public WestScript(String format, String str1, String str2, String str3) {
        this();
        String[] args = {str1, str2, str3};
        StringBuffer output = new StringBuffer();

        for (int i = 0, j = 0; i < format.length(); i++) {
            switch (format.charAt(i)) {
                case '%':
                    i++;    // '%'
                    i++;    // 's'
                    output.append(args[j++]);
                    break;
                default:
                    output.append(format.charAt(i));
                    break;
            }
        }

        script = output.toString();
    }

    /* one step evaluation */
    public WestScript function(OutputStream s) {
        String token = lookahead();

        // escaped function / variable
        if (token.length() > 1 && token.charAt(1) == '$') {
            if (lookahead(2).equals("(")) {
                index++;
                // escaped function
                stream(s, getFunction());
            } else {
                // escaped variable
                token = getTok();
                // stream(s, htmlencode(symbol[token.Mid(2)]); FIXME!
            }
            return new WestScript();
        }

        return new WestScript();
    }

    /* evaluates current function */
    public String getValue() {
        return "";
    }

    /* get expression token */
    public String getTok() {
        return "";
    }

    /* get unevaluated expr */
    public String getExpr() {
        return "";
    }

    /* get variable name */
    public String getVar() {
        return "";
    }

    /* lookahead 1 token */
    public String lookahead() {
        return "";
    }

    /* lookahead n tokens */
    public String lookahead(int n) {
        return "";
    }

    // read in newline char
    public String getNewline() {
        return "";
    }

    // get westscript
    private String getWscript() {
        return "";
    }

    // get function token
    private String getFunction() {
        return "";
    }

    // get the arglist
    private String getArgs() {
        return "";
    }

    // get constant
    private String getConst() {
        return "";
    }

    // get pure html text
    private String getHtml() {
        return "";
    }

    private OutputStream eval(OutputStream s) {
        if (lookahead().equals("'"))
            getTok();

        while (index < script.length()) {
            stream(s, getHtml());

            if (script.charAt(index) == '$')
                stream(s, function(s));
            else if (script.charAt(index) == '\'')
                break;
        }

        if (lookahead().equals("'"))
            getTok();

        return s;
    }

    private static void stream(OutputStream s, String str) {
        try {
            s.write(str.getBytes());
        } catch (IOException e) {
            ;
        }
    }

    private static void stream(OutputStream s, WestScript ws) {
        ws.eval(s);
    }

}
