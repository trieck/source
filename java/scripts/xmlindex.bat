@echo off
java -Dorg.tomrieck.util.Config=c:\source\java\config\content.properties -Djava.io.tmpdir=c:/tmp -cp ..\classes org.tomrieck.content.XMLIndexer %1



