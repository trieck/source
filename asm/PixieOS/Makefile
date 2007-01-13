OBJECTS = bootsect.bin
AFLAGS = -f bin

all:	$(OBJECTS)

bootsect.bin:
	nasm bootsect.asm $(AFLAGS) -o $@

format:
	@format a: /q

install:
	partcopy bootsect.bin 0 200 -f0

clean:
	@-rm $(OBJECTS) 2>nul
	
	


