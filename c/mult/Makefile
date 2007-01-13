OBJECTS = mult.obj
LINKFLAGS = -nologo

mult:	$(OBJECTS)
	$(CC) $(OBJECTS) $(LINKFLAGS)

nptune64.exe:	$(INTDIR) $(OBJECTS)
	@$(CC) $(OBJECTS) $(LINKFLAGS)
clean:	
	@-erase *.obj 2>nul
	@-erase *.exe 2>nul
	@-erase *.tds 2>nul
	