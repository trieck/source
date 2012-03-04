@echo off
java -Dorg.pixielib.util.Config=d:\source\java\config\pixie.properties -cp ..\classes org.pixielib.content.CheckIndex %1

