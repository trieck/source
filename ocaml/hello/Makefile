OC = ocamlc
OBJECTS = hello.cmo

TARGET = hello.exe
LINKFLAGS = -o $(TARGET)

# suffix rules
.SUFFIXES: .cmo .ml
.ml.cmo:
	$(OC) -c $<
	
hello:	$(OBJECTS)
	$(OC) $(LINKFLAGS) $(OBJECTS)

clean:
	@rm -rf *.cm?
	@rm -f $(TARGET)
	@rm -f $(TARGETDIR)/core
	@rm -f core
