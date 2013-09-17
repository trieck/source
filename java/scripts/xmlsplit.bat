@echo off
java -Xms64m -Xmx512m -cp ..\dist\pixie.jar org.pixielib.content.XMLSplitter %1 %2 %3

