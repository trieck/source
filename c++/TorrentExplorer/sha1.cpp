/////////////////////////////////////////////////////////////////////////////
//
// SHA1.CPP : Secure hash algorithm
//
// Derived from cryptoapi implementation, adapted for in-place
// scatterlist interface.  Originally based on the public domain
// implementation written by Steve Reid.
//
// Adapted for Win32
//
// Copyright (c) Alan Smithee.
// Copyright (c) Andrew McDonald <andrew@mcdonald.org.uk>
// Copyright (c) Jean-Francois Dive <jef@linuxbe.org>
//
// Copyright (C) 2006 Thomas A. Rieck, all rights reserved.
//

#include "stdafx.h"
#include "sha1.h"

namespace  	// anonymous
{

#define SHA1_HMAC_BLOCK_SIZE    64

inline unsigned int rol(unsigned int value, unsigned int bits)
{
    return (((value) << (bits)) | ((value) >> (32 - (bits))));
}

inline int to_big_endian(int d)
{
    unsigned char buffer[sizeof (int)];
    buffer [0] = (char) (d >> 24) & 0xff;
    buffer [1] = (char) (d >> 16) & 0xff;
    buffer [2] = (char) (d >> 8) & 0xff;
    buffer [3] = (char) d;
    return * (int*)buffer;
}

/* blk0() and blk() perform the initial expand. */
/* I got the idea of expanding during the round function from SSLeay */
# define blk0(i) block32[i]

#define blk(i) (block32[i&15] = rol(block32[(i+13)&15]^block32[(i+8)&15] \
     ^block32[(i+2)&15]^block32[i&15],1))

/* (R0+R1), R2, R3, R4 are the different operations used in SHA1 */
#define R0(v,w,x,y,z,i) z+=((w&(x^y))^y)+blk0(i)+0x5A827999+rol(v,5); \
                         w=rol(w,30);
#define R1(v,w,x,y,z,i) z+=((w&(x^y))^y)+blk(i)+0x5A827999+rol(v,5); \
                         w=rol(w,30);
#define R2(v,w,x,y,z,i) z+=(w^x^y)+blk(i)+0x6ED9EBA1+rol(v,5);w=rol(w,30);
#define R3(v,w,x,y,z,i) z+=(((w|x)&y)|(w&x))+blk(i)+0x8F1BBCDC+rol(v,5); \
                         w=rol(w,30);
#define R4(v,w,x,y,z,i) z+=(w^x^y)+blk(i)+0xCA62C1D6+rol(v,5);w=rol(w,30);

struct sha1_ctx {
    UINT64 count;
    unsigned int state[5];
    unsigned char buffer[64];
};

void sha1_init(void *ctx);
void sha1_transform(unsigned int *state, const unsigned char *in);
void sha1_update(void *ctx, const unsigned char *data, unsigned int len);
void sha1_final(void* ctx, unsigned char *out);

}	// anonymous

/////////////////////////////////////////////////////////////////////////////
SHA1::SHA1(const CString &s)
{
    digest[0] = '\0';
    sha1_ctx ctx;
    sha1_init(&ctx);
    sha1_update(&ctx, (LPBYTE)(LPCSTR)s, s.GetLength());
    sha1_final(&ctx, (LPBYTE)digest);
}

/////////////////////////////////////////////////////////////////////////////
SHA1::~SHA1()
{
}

/////////////////////////////////////////////////////////////////////////////
CString SHA1::toHexString() const
{
    char buf[SHA1_DIGEST_SIZE*2+1];
    sprintf(buf, "%.8x%.8x%.8x%.8x%.8x",
            to_big_endian(*(unsigned int*)(&digest[0])),
            to_big_endian(*(unsigned int*)(&digest[4])),
            to_big_endian(*(unsigned int*)(&digest[8])),
            to_big_endian(*(unsigned int*)(&digest[12])),
            to_big_endian(*(unsigned int*)(&digest[16])));
    return buf;
}

namespace  	// anonymous
{

/////////////////////////////////////////////////////////////////////////////
void sha1_init(void *ctx)
{
    struct sha1_ctx *sctx = static_cast<struct sha1_ctx*>(ctx);
    static const struct sha1_ctx initstate = {
        0,
        { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0 },
        { 0, }
    };

    *sctx = initstate;
}

/* Hash a single 512-bit block. This is the core of the algorithm. */
void sha1_transform(unsigned int *state, const unsigned char *in)
{
    unsigned int a, b, c, d, e;
    unsigned int block32[16];

    /* convert/copy data to workspace */
    for (a = 0; a < sizeof(block32)/sizeof(unsigned int); a++) {
        block32[a] = to_big_endian((((const unsigned int *)in)[a]));
    }

    /* Copy context->state[] to working vars */
    a = state[0];
    b = state[1];
    c = state[2];
    d = state[3];
    e = state[4];

    /* 4 rounds of 20 operations each. Loop unrolled. */
    R0(a,b,c,d,e, 0);
    R0(e,a,b,c,d, 1);
    R0(d,e,a,b,c, 2);
    R0(c,d,e,a,b, 3);
    R0(b,c,d,e,a, 4);
    R0(a,b,c,d,e, 5);
    R0(e,a,b,c,d, 6);
    R0(d,e,a,b,c, 7);
    R0(c,d,e,a,b, 8);
    R0(b,c,d,e,a, 9);
    R0(a,b,c,d,e,10);
    R0(e,a,b,c,d,11);
    R0(d,e,a,b,c,12);
    R0(c,d,e,a,b,13);
    R0(b,c,d,e,a,14);
    R0(a,b,c,d,e,15);
    R1(e,a,b,c,d,16);
    R1(d,e,a,b,c,17);
    R1(c,d,e,a,b,18);
    R1(b,c,d,e,a,19);
    R2(a,b,c,d,e,20);
    R2(e,a,b,c,d,21);
    R2(d,e,a,b,c,22);
    R2(c,d,e,a,b,23);
    R2(b,c,d,e,a,24);
    R2(a,b,c,d,e,25);
    R2(e,a,b,c,d,26);
    R2(d,e,a,b,c,27);
    R2(c,d,e,a,b,28);
    R2(b,c,d,e,a,29);
    R2(a,b,c,d,e,30);
    R2(e,a,b,c,d,31);
    R2(d,e,a,b,c,32);
    R2(c,d,e,a,b,33);
    R2(b,c,d,e,a,34);
    R2(a,b,c,d,e,35);
    R2(e,a,b,c,d,36);
    R2(d,e,a,b,c,37);
    R2(c,d,e,a,b,38);
    R2(b,c,d,e,a,39);
    R3(a,b,c,d,e,40);
    R3(e,a,b,c,d,41);
    R3(d,e,a,b,c,42);
    R3(c,d,e,a,b,43);
    R3(b,c,d,e,a,44);
    R3(a,b,c,d,e,45);
    R3(e,a,b,c,d,46);
    R3(d,e,a,b,c,47);
    R3(c,d,e,a,b,48);
    R3(b,c,d,e,a,49);
    R3(a,b,c,d,e,50);
    R3(e,a,b,c,d,51);
    R3(d,e,a,b,c,52);
    R3(c,d,e,a,b,53);
    R3(b,c,d,e,a,54);
    R3(a,b,c,d,e,55);
    R3(e,a,b,c,d,56);
    R3(d,e,a,b,c,57);
    R3(c,d,e,a,b,58);
    R3(b,c,d,e,a,59);
    R4(a,b,c,d,e,60);
    R4(e,a,b,c,d,61);
    R4(d,e,a,b,c,62);
    R4(c,d,e,a,b,63);
    R4(b,c,d,e,a,64);
    R4(a,b,c,d,e,65);
    R4(e,a,b,c,d,66);
    R4(d,e,a,b,c,67);
    R4(c,d,e,a,b,68);
    R4(b,c,d,e,a,69);
    R4(a,b,c,d,e,70);
    R4(e,a,b,c,d,71);
    R4(d,e,a,b,c,72);
    R4(c,d,e,a,b,73);
    R4(b,c,d,e,a,74);
    R4(a,b,c,d,e,75);
    R4(e,a,b,c,d,76);
    R4(d,e,a,b,c,77);
    R4(c,d,e,a,b,78);
    R4(b,c,d,e,a,79);
    /* Add the working vars back into context.state[] */
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
    /* Wipe variables */
    a = b = c = d = e = 0;
    memset (block32, 0x00, sizeof(block32));
}

/////////////////////////////////////////////////////////////////////////////
void sha1_update(void *ctx, const unsigned char*data, unsigned int len)
{
    struct sha1_ctx *sctx = static_cast<struct sha1_ctx*>(ctx);
    unsigned int i, j;

    j = (sctx->count >> 3) & 0x3f;
    sctx->count += len << 3;

    if ((j + len) > 63) {
        memcpy(&sctx->buffer[j], data, (i = 64-j));
        sha1_transform(sctx->state, sctx->buffer);
        for ( ; i + 63 < len; i += 64) {
            sha1_transform(sctx->state, &data[i]);
        }
        j = 0;
    } else i = 0;
    memcpy(&sctx->buffer[j], &data[i], len - i);
}

/* Add padding and return the message digest. */
void sha1_final(void* ctx, unsigned char *out)
{
    struct sha1_ctx *sctx = static_cast<sha1_ctx*>(ctx);
    unsigned int i, j, index, padlen;
    UINT64 t;
    unsigned char bits[8] = { 0, };
    static const unsigned char padding[64] = { 0x80, };
    t = sctx->count;
    bits[7] = 0xff & t;
    t>>=8;
    bits[6] = 0xff & t;
    t>>=8;
    bits[5] = 0xff & t;
    t>>=8;
    bits[4] = 0xff & t;
    t>>=8;
    bits[3] = 0xff & t;
    t>>=8;
    bits[2] = 0xff & t;
    t>>=8;
    bits[1] = 0xff & t;
    t>>=8;
    bits[0] = 0xff & t;

    /* Pad out to 56 mod 64 */
    index = (sctx->count >> 3) & 0x3f;
    padlen = (index < 56) ? (56 - index) : ((64+56) - index);
    sha1_update(sctx, padding, padlen);

    /* Append length */
    sha1_update(sctx, bits, sizeof bits);

    /* Store state in digest */
    for (i = j = 0; i < 5; i++, j += 4) {
        unsigned int t2 = sctx->state[i];
        out[j+3] = t2 & 0xff;
        t2>>=8;
        out[j+2] = t2 & 0xff;
        t2>>=8;
        out[j+1] = t2 & 0xff;
        t2>>=8;
        out[j  ] = t2 & 0xff;
    }

    /* Wipe context */
    memset(sctx, 0, sizeof *sctx);
}


}	// anonymous
