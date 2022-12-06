
OBJECTS = \
    prg\alpha.prg \
    prg\bitmap.prg \
    prg\blink.prg \
    prg\blink-vic.prg \
    prg\color.prg \
    prg\loop.prg \
    prg\util.prg \
    prg\vicpencil.prg

all: $(OBJECTS)

.asm.prg:
    t6502 $<

clean:
    @-erase prg\*.prg 2>nul