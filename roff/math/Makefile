OBJECTS = math.ps
ROFF = groff
RFLAGS = -e -p -t -ms

# suffix rules
.SUFFIXES: .ms .ps
.ms.ps:
	$(ROFF) $(RFLAGS) $< > $@
	
all:	$(OBJECTS)

clean:
	@rm -f *.ps
