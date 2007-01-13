OC = ocamlc
OBJECTS = list.cmo

TARGET = list.exe
LINKFLAGS = -o $(TARGET)

# suffix rules
.SUFFIXES: .cmo .ml
.ml.cmo:
	$(OC) -c $<
	
list:	$(OBJECTS)
	$(OC) $(LINKFLAGS) $(OBJECTS)

clean:
	@rm -rf *.cm?
	@rm -f $(TARGET)
	@rm -f $(TARGETDIR)/core
	@rm -f core
