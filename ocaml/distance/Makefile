OC = ocamlc
OBJECTS = distance.cmo

TARGET = distance.exe
LINKFLAGS = -o $(TARGET)

# suffix rules
.SUFFIXES: .cmo .ml
.ml.cmo:
	$(OC) -c $<
	
distance:	$(OBJECTS)
	$(OC) $(LINKFLAGS) $(OBJECTS)

clean:
	@rm -rf *.cm?
	@rm -f $(TARGET)
	@rm -f $(TARGETDIR)/core
	@rm -f core
