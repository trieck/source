@echo off
@echo off
call setenv.bat
java %JAVA_OPTS% -cp %CLASSPATH% org.pixielib.content.XMLSplitter %*


