@echo off
java -Dorg.pixielib.util.Config=d:\source\java\config\pixie.properties -cp ..\classes org.pixielib.content.Search %1 %2 %3

