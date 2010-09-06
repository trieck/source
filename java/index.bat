@echo off
java -Djava.io.tmpdir=c:/tmp -cp classes org.tomrieck.content.Indexer %1 %2

