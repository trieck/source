@echo off
java -Dorg.pixielib.util.Config=c:\source\java\config\content.properties -Djava.io.tmpdir=c:/tmp -cp ..\classes org.pixielib.content.XMLIndexer %1



