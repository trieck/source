#include <stdlib.h>
#include <string.h>
#include "tcipher.h"

static char rotor_one(char c, unsigned key);
static char rotor_two(char c, unsigned key);
static char rotor_three(char c, unsigned key);
static char rotor_four(char c, unsigned key);

static char key_table[256] = {
	0x23, 0x30, 0xd7, 0x7b, 0x59, 0x1b, 0xd9, 0xb7, 
	0xf7, 0xde, 0xcb, 0x60, 0xf6, 0x69, 0x5f, 0xe9, 
	0x9a, 0x17, 0x46, 0x61, 0x9c, 0x03, 0x5e, 0x41, 
	0xba, 0x78, 0x4d, 0x4f, 0xe5, 0x76, 0xc4, 0x02, 
	0x0b, 0x26, 0x84, 0x1d, 0x92, 0xa0, 0xa5, 0x0c, 
	0x16, 0xcf, 0x04, 0xa8, 0xf8, 0x40, 0x49, 0x53, 
	0x08, 0xc8, 0x86, 0x2d, 0x43, 0x51, 0xe7, 0xd2, 
	0x9b, 0x56, 0x81, 0x38, 0xad, 0x2b, 0xaa, 0x91, 
	0x07, 0x0a, 0xe2, 0x5d, 0x3e, 0xfa, 0xca, 0xb8, 
	0xb1, 0x5b, 0x14, 0xf9, 0x83, 0x2c, 0xc9, 0x82, 
	0xea, 0x4c, 0x45, 0x35, 0x42, 0x4a, 0x58, 0xd1, 
	0xfb, 0x3c, 0x70, 0xa9, 0xcd, 0x3a, 0xcc, 0xbb, 
	0xb3, 0xab, 0xbd, 0x73, 0x29, 0xa4, 0xbf, 0xfd, 
	0x1f, 0x7c, 0xa1, 0x85, 0xa3, 0x68, 0x20, 0xe1, 
	0x34, 0x3d, 0x00, 0xf0, 0xc0, 0x47, 0x8c, 0x1c, 
	0x89, 0x6a, 0x93, 0xff, 0x6c, 0x80, 0xb2, 0xb0, 
	0xdb, 0x6e, 0x6f, 0x8b, 0x13, 0x6b, 0x97, 0x25, 
	0xb9, 0x09, 0x5a, 0x96, 0x54, 0xe0, 0x7a, 0xf5, 
	0xbc, 0x01, 0x90, 0xd3, 0x94, 0x8e, 0xed, 0x05, 
	0x27, 0xe4, 0x31, 0xae, 0x18, 0x2e, 0xc1, 0xd8, 
	0x21, 0x4b, 0xa2, 0xd5, 0x06, 0xa7, 0x39, 0xce, 
	0xc3, 0xbe, 0xac, 0xe6, 0x7d, 0x0e, 0x2f, 0xfc, 
	0xdd, 0xe3, 0xee, 0x48, 0x63, 0xf1, 0xaf, 0x71, 
	0x4e, 0xc7, 0x24, 0xd4, 0x1e, 0x36, 0x9f, 0x62, 
	0xc6, 0xf3, 0xc2, 0xd6, 0xec, 0xc5, 0xdc, 0x10, 
	0x74, 0x98, 0xfe, 0x66, 0xef, 0x64, 0xf2, 0x87, 
	0x8a, 0x75, 0x28, 0x52, 0x22, 0x44, 0xda, 0x55, 
	0x79, 0xb6, 0x65, 0x3b, 0x50, 0xe8, 0xb5, 0x15, 
	0xf4, 0xeb, 0x33, 0x1a, 0x0f, 0x88, 0x57, 0x5c, 
	0x11, 0x6d, 0xb4, 0x19, 0x77, 0x67, 0xd0, 0xa6, 
	0x95, 0x0d, 0x2a, 0xdf, 0x32, 0x9d, 0x37, 0x3f, 
	0x99, 0x8f, 0x7f, 0x8d, 0x12, 0x72, 0x7e, 0x9e
};

char *tencipher(const char *s, unsigned key)
{
	char c, *output = malloc(strlen(s) + 1), *pout = output;

	while (*s) {
		c = rotor_one(*s++, key);
		c = rotor_two(c, key);
		c = rotor_three(c, key);
		c = rotor_four(c, key);
		c = rotor_four(~c, ~key);
		c = rotor_three(c, ~key);
		c = rotor_two(c, ~key);
		c = rotor_one(c, ~key);
		*pout++ = c;
	}

	*pout = '\0';

	return output;
}

char rotor_one(char c, unsigned key)
{
	unsigned index = (key & 0xFF000000) >> 24;
	return c + key_table[index];
}

char rotor_two(char c, unsigned key)
{
	unsigned index = (key & 0xFF0000) >> 16;
	return c + key_table[index];
}

char rotor_three(char c, unsigned key)
{
	unsigned index = (key & 0xFF00) >> 8;
	return c + key_table[index];
}

char rotor_four(char c, unsigned key)
{
	unsigned index = key & 0xFF;
	return c + key_table[index];
}
