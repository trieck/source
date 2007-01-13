OBJECTS = triangle.ps
ROFF = groff
RFLAGS = -e -p -ms

# suffix rules
.SUFFIXES: .ms .ps
.ms.ps:
	$(ROFF) $(RFLAGS) $< > $@
	
all:	$(OBJECTS)

clean:
	@rm -f *.ps
