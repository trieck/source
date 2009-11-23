.PHONY: clean All

All:
	@echo ----------Building project:[ iso9660 - Debug ]----------
	@"D:\MinGW\bin\mingw32-make.exe"  -j 1 -f "iso9660.mk"
clean:
	@echo ----------Cleaning project:[ iso9660 - Debug ]----------
	@"D:/MinGW/bin/mingw32-make.exe"  -j 1 -f "iso9660.mk" clean
