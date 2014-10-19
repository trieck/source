@echo off
set JAVA_OPTS=-Xms64m -Xmx512m -Djava.io.tmpdir=d:/tmp -ea
set CLASSPATH=..\content\target\*;..\webapps\target\*;..\content\util\*;..\webapps\io\*;..\webapps\ui\*
