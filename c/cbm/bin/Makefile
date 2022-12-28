OBJECTS = \
    prg\alpha.prg \
    prg\bitmap.prg \
    prg\blink-vic.prg \
    prg\blink.prg \
    prg\color.prg \
    prg\loop.prg \
    prg\scroll-up-down.prg \
    prg\util.prg \
	prg\plot.prg

all: $(OBJECTS)
.asm.prg:
    t6502 $<


clean:
    @-erase prg\*.prg 2>nul