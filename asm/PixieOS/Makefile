OBJECT = bootsect.bin
IMAGE = $(OBJECT).img

AFLAGS = -f bin

all:	$(OBJECT) $(IMAGE)

$(OBJECT):
	@-nasm bootsect.asm $(AFLAGS) -o $@

$(IMAGE):
	@-cp $(OBJECT) $(IMAGE)
	@-truncate --size 1474560 $(IMAGE)

format:
	@format a: /q

install:
	partcopy bootsect.bin 0 200 -f0

clean:
	@-rm -f $(OBJECT) $(IMAGE) > /dev/null

	
	


