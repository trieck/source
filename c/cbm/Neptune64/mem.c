/*
 * 	MEM.C
 *
 * 	C64 Memory Management Module
 *
 *	Neptune64 Commodore 64 Emulator
 * 	Copyright (C) 2001 Thomas A. Rieck <trieck@bellsouth.net>
 *
 *	This module is based largely on the
 * 	c64mem.h, c64mem.c modules in VICE, the Versatile Commodore Emulator
 * 	Written by:
 *
 *  Ettore Perazzoli <ettore@comm2000.it>
 *  Andreas Boose <boose@linux.rz.fh-hannover.de>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307  USA.
 *
 */

#include "common.h"
#include "mem.h"
#include "video.h"
#include "cia.h"
#include "sid.h"
#include "cart.h"
#define RAM_SIZE			0x10000
#define KERNAL_ROM_SIZE		0x2000
#define BASIC_ROM_SIZE		0x2000
#define CHARGEN_ROM_SIZE	0x1000
#define CONFIGURATIONS 		0x20
#define PAGES 				0x100
static byte ram[RAM_SIZE];
static byte basic_rom[BASIC_ROM_SIZE];
static byte kernal_rom[KERNAL_ROM_SIZE];
static byte chargen_rom[CHARGEN_ROM_SIZE];
extern const char *kernal_name;
extern const char *basic_name;
extern const char *chargen_name;
/*
 * current memory configuration
 *
 * -----------------------------------------
 * | GAME | EXROM | CHAREN | HIRAM | LORAM |
 * -----------------------------------------
 *
 */
static word mem_config;
static struct {
    byte data;
    byte dir;
    byte data_out;
} pport;
typedef byte (*read_func_ptr_t)(word address);
typedef void (*store_func_ptr_t)(word address, byte b);
/* current read and write function pointers */
static read_func_ptr_t *read_func_ptr;
static store_func_ptr_t *write_func_ptr;
/* memory read and write tables */
static store_func_ptr_t mem_write_tab[CONFIGURATIONS][PAGES];
static read_func_ptr_t mem_read_tab[CONFIGURATIONS][PAGES];
/* ROM load routines */
static void load_rom(const char *filename, byte *pb, word size);
static void load_kernal(void);
static void load_basic(void);
static void load_chargen(void);
static void initialize_memory(void);
/* memory access routines */
static byte read_zero(word addr);
static void store_zero(word addr, byte value);
static byte ram_read(word addr);
static void ram_store(word addr, byte value);
static byte basic_read(word addr);
static byte kernal_read(word addr);
static byte chargen_read(word addr);
static byte read_roml(word addr);
static byte io1_read(word addr);
static void io1_store(word addr, byte value);
static byte io2_read(word addr);
static void io2_store(word addr, byte value);
static void config_changed(void);
/*
 * read from basic ROM
 */
byte basic_read(word addr)
{
    return basic_rom[addr & 0x1fff];
}
/*
 * read from kernal ROM
 */
byte kernal_read(word addr)
{
    return kernal_rom[addr & 0x1fff];
}
/*
 * read from chargen ROM
 */
byte chargen_read(word addr)
{
    return chargen_rom[addr & 0xfff];
}
/*
 * fetch a byte from memory
 * located at address
 */
byte fetch_byte(word address)
{
    /* FIXME: implement this */
    return (*read_func_ptr[address >> 8])(address);
}
/*
 * store a byte to memory
 * located at address
 */
void store_byte(word address, byte b)
{
    /* FIXME: implement this */
    (*write_func_ptr[address >> 8])(address, b);
}
/*
 * initialize memory
 */
void mem_init(void)
{
    load_kernal();
    load_basic();
    load_chargen();
    initialize_memory();
}
#if defined(_MSC_VER) || defined(__BORLANDC__)
#define OPENFLAGS O_RDONLY | O_BINARY
#else
#define OPENFLAGS O_RDONLY
#endif
/*
 * generalized routine for loading a
 * ROM image into memory
 */
void load_rom(const char *filename, byte *pb, word size)
{
    struct stat st;
    int fd, n;

    fd = open(filename, OPENFLAGS);
    if (-1 == fd)
        error("unable to open ROM image \"%s\".\n", filename);

    fstat(fd, &st);
    if (size != st.st_size) {
        close(fd);
        error("ROM image \"%s\" is wrong size; expected %d bytes, "
              "found %d bytes.\n", filename, size, st.st_size);
    }

    n = read(fd, pb, size);
    if (size != n) {
        close(fd);
        error("error reading ROM image \"%s\"; expected %d bytes, "
              "read %d bytes.\n", filename, size, n);
    }

    close(fd);
}
/*
 * load kernal image into memory
 */
void load_kernal(void)
{
    load_rom(kernal_name, kernal_rom, KERNAL_ROM_SIZE);
}
/*
 * load basic image into memory
 */
void load_basic(void)
{
    load_rom(basic_name, basic_rom, BASIC_ROM_SIZE);
}
/*
 * load chargen image into memory
 */
void load_chargen(void)
{
    load_rom(chargen_name, chargen_rom, CHARGEN_ROM_SIZE);
}
/*
 * initialize memory
 */
void initialize_memory(void)
{
    int i, j;

    /* IO is enabled at memory configs 5, 6, 7 and Ultimax */
    int io_config[CONFIGURATIONS] = { 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1,
                                      1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1
                                    };

    /* ROML is enabled at memory configs 11, 15, 27, 31 and Ultimax */
    int roml_config[CONFIGURATIONS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
                                        1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1
                                      };

    /* ROMH is enabled at memory configs 10, 11, 14, 15, 26, 27, 30, 31
       and Ultimax.  */
    int romh_config[CONFIGURATIONS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                        1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1
                                      };

    /* ROMH is mapped to $A000-$BFFF at memory configs 10, 11, 14, 15, 26,
       27, 30, 31.  If Ultimax is enabled it is mapped to $E000-$FFFF.  */
    int romh_mapping[CONFIGURATIONS] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                         0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
                                         0x00, 0xa0, 0xa0, 0x00, 0x00, 0xa0, 0xa0
                                       };

    for (i = 0; i < CONFIGURATIONS; i++) {
        mem_write_tab[i][0] = store_zero;
        mem_read_tab[i][0] = read_zero;
        for (j = 1; j < PAGES; j++) {
            mem_read_tab[i][j] = ram_read;
            mem_write_tab[i][j] = ram_store;
        }
    }

    /* BASIC ROM is banked in at $A000-$BFFF in memory configs 3, 7, 11, 15 */
    for (i = 0xa0; i <= 0xbf; i++) {
        mem_read_tab[3][i] = basic_read;
        mem_read_tab[7][i] = basic_read;
        mem_read_tab[11][i] = basic_read;
        mem_read_tab[15][i] = basic_read;
    }

    /*
     * chargen ROM is banked in at $D000-$DFFF in memory configs 1, 2, 3, 9, 10,
     * 11, 25, 26, 27)
     */
    for (i = 0xd0; i <= 0xdf; i++) {
        mem_read_tab[1][i] = chargen_read;
        mem_read_tab[2][i] = chargen_read;
        mem_read_tab[3][i] = chargen_read;
        mem_read_tab[9][i] = chargen_read;
        mem_read_tab[10][i] = chargen_read;
        mem_read_tab[11][i] = chargen_read;
        mem_read_tab[25][i] = chargen_read;
        mem_read_tab[26][i] = chargen_read;
        mem_read_tab[27][i] = chargen_read;
    }

    /* I/O is banked in at $D000-$DFFF in memory configs 5, 6, 7 */
    for (j = 0; j < CONFIGURATIONS; j++) {
        if (io_config[j]) {
            for (i = 0xd0; i <= 0xd3; i++) {
                mem_read_tab[j][i] = vic_read;
                mem_write_tab[j][i] = vic_store;
            }
            for (i = 0xd4; i <= 0xd5; i++) {
                mem_read_tab[j][i] = sid_read;
                mem_write_tab[j][i] = sid_store;
            }
            for (i = 0xd6; i <= 0xd7; i++) {
                mem_read_tab[j][i] = sid_read;
                mem_write_tab[j][i] = sid_store;
            }
            for (i = 0xd8; i <= 0xdb; i++) {
                mem_read_tab[j][i] = colorram_read;
                mem_write_tab[j][i] = colorram_store;
            }
            mem_read_tab[j][0xdc] = cia1_read;
            mem_write_tab[j][0xdc] = cia1_store;
            mem_read_tab[j][0xdd] = cia2_read;
            mem_write_tab[j][0xdd] = cia2_store;
            mem_read_tab[j][0xde] = io1_read;
            mem_write_tab[j][0xde] = io1_store;
            mem_read_tab[j][0xdf] = io2_read;
            mem_write_tab[j][0xdf] = io2_store;
        }
    }

    /* Kernal ROM is banked in at $E000-$FFFF in memory configs 2, 3, 6, 7, 10,
       11, 14, 15, 26, 27, 30, 31 */
    for (i = 0xe0; i <= 0xff; i++) {
        mem_read_tab[2][i] = kernal_read;
        mem_read_tab[3][i] = kernal_read;
        mem_read_tab[6][i] = kernal_read;
        mem_read_tab[7][i] = kernal_read;
        mem_read_tab[10][i] = kernal_read;
        mem_read_tab[11][i] = kernal_read;
        mem_read_tab[14][i] = kernal_read;
        mem_read_tab[15][i] = kernal_read;
        mem_read_tab[26][i] = kernal_read;
        mem_read_tab[27][i] = kernal_read;
        mem_read_tab[30][i] = kernal_read;
        mem_read_tab[31][i] = kernal_read;
    }

    /* Setup ROML at $8000-$9FFF */
    for (j = 0; j < CONFIGURATIONS; j++) {
        if (roml_config[j]) {
            for (i = 0x80; i <= 0x9f; i++) {
                mem_read_tab[j][i] = read_roml;
            }
        }
    }

    for (j = 16; j < 24; j++) {
        for (i = 0x80; i <= 0x9f; i++) {
            mem_write_tab[j][j] = store_roml;
        }

        for (i = 0xa0; i <= 0xbf; i++) {
            mem_read_tab[j][i] = read_ultimax_a000_bfff;
            mem_write_tab[j][i] = store_ultimax_a000_bfff;
        }
    }

    /* Setup ROMH at $A000-$BFFF and $E000-$FFFF */
    for (j = 0; j < CONFIGURATIONS; j++) {
        if (romh_config[j]) {
            for (i = romh_mapping[j]; i <= (romh_mapping[j] + 0x1f); i++) {
                mem_read_tab[j][i] = read_romh;
            }
        }
    }

    read_func_ptr = mem_read_tab[7];
    write_func_ptr = mem_write_tab[7];
    pport.data = 0x37;
    pport.dir = 0x2f;
    export.exrom = 0;
    export.game = 0;

    config_changed();
}
/*
 * read memory on zero page
 */
byte read_zero(word addr)
{
    return ram[addr & 0xff];
}
/*
 * write memory to zero page
 */
void store_zero(word addr, byte value)
{
    addr &= 0xff;

    switch (addr) {
    case 0:
        if (pport.dir != value) {
            pport.dir = value;
            config_changed();
        }
        break;
    case 1:
        if (pport.data != value) {
            pport.data = value;
            config_changed();
        }
        break;
    default:
        ram[addr] = value;
    }
}

/*
 * read RAM
 */
byte ram_read(word addr)
{
    return ram[addr];
}
/*
 * store RAM
 */
void ram_store(word addr, byte value)
{
    ram[addr] = value;
}
/*
 * read ROML
 */
byte read_roml(word addr)
{
    /* FIXME: implement this */
    return 0;
}
byte io1_read(word addr)
{
    /* FIXME: implement this */
    return 0;
}
void io1_store(word addr, byte value)
{
    /* FIXME: implement this */
}
byte io2_read(word addr)
{
    /* FIXME: implement this */
    return 0;
}
void io2_store(word addr, byte value)
{
    /* FIXME: implement this */
}
/*
 * memory configuration change
 */
void config_changed(void)
{
    mem_config = (((~pport.dir | pport.data) & 0x7) | (export.exrom << 3)
                  | (export.game << 4));
    pport.data_out = (pport.data_out & ~pport.dir)
                     | (pport.data & pport.dir);
    ram[1] = ((pport.data | ~pport.dir) & (pport.data_out | 0x17));
    ram[0] = pport.dir;
}
