@echo off
java -Xms64m -Xmx512m -Dorg.pixielib.util.Config=d:\source\java\config\pixie.properties -Djava.io.tmpdir=d:/tmp -cp ..\classes org.pixielib.content.XMLIndexer %1
