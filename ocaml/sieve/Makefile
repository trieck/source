OC = ocamlc
OBJECTS = sieve.cmo

TARGET = sieve.exe
LINKFLAGS = -o $(TARGET)

# suffix rules
.SUFFIXES: .cmo .ml
.ml.cmo:
	$(OC) -c $<
	
sieve:	$(OBJECTS)
	$(OC) $(LINKFLAGS) $(OBJECTS)

clean:
	@rm -rf *.cm?
	@rm -f $(TARGET)
	@rm -f $(TARGETDIR)/core
	@rm -f core
