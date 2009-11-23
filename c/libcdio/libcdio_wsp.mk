.PHONY: clean All

All:
	@echo ----------Building project:[ iso_read - Debug ]----------
	@"D:\MinGW\bin\mingw32-make.exe"  -j 1 -f "iso_read.mk"
clean:
	@echo ----------Cleaning project:[ iso_read - Debug ]----------
	@"D:/MinGW/bin/mingw32-make.exe"  -j 1 -f "iso_read.mk" clean
