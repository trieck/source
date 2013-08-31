@echo off
java -Xms64m -Xmx512m -cp ..\dist\pixie.jar org.pixielib.games.jumble.Jumble %1
