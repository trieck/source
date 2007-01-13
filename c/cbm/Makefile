#
# base CBM makefile
#
TARBALL = cbm.tar.gz
default:
clean:
	@rm -f $(TARBALL)
	@make -C neptune64 clean
	@make -C t6502 clean
	@make -C td6502 clean
all:
	@make -C neptune64
	@make -C t6502
	@make -C td6502
tarball:
	@make clean
	@tar cvf $(TARBALL) * --gzip
	
tarballwin32:
	@clean.bat
	@tar cvf $(TARBALL) * --gzip
