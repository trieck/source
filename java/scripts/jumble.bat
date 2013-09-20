@echo off
call setenv.bat
java %JAVA_OPTS% -cp %CLASSPATH% org.pixielib.webapps.jumble.Jumble %1
