/*
 * CODE.C
 *
 * code disassembly
 *
 */
#include "common.h"
#include "code.h"

static void immediate(const Instr* p);
static void zeropage(const Instr* p);
static void zeropgx(const Instr* p);
static void zeropgy(const Instr* p);
static void absolute(const Instr* p);
static void abslx(const Instr* p);
static void absly(const Instr* p);
static void relative(const Instr* p);
static void indirect(const Instr* p);
static void indrctx(const Instr* p);
static void indrcty(const Instr* p);
static void accumulator(const Instr* p);
static void implied(const Instr* p);

#define getbyte(b) fread(&(b), sizeof(byte), 1, fp)
#define getword(w) fread(&(w), sizeof(word), 1, fp)

word pc;         /* program counter */
extern FILE* fp; /* input file pointer */

/*
 * disassemble an instruction
 */
void instruction(const Instr* p)
{
    if (NULL == p) {
        printf("\t\t???");
        ++pc;
        return;
    }

    switch (p->mode) {
    case acc:
        accumulator(p);
        break;
    case imm:
        immediate(p);
        break;
    case zpg:
        zeropage(p);
        break;
    case zpx:
        zeropgx(p);
        break;
    case zpy:
        zeropgy(p);
        break;
    case absl:
        absolute(p);
        break;
    case abx:
        abslx(p);
        break;
    case aby:
        absly(p);
        break;
    case imp:
        implied(p);
        break;
    case rel:
        relative(p);
        break;
    case ind:
        indirect(p);
        break;
    case idx:
        indrctx(p);
        break;
    case idy:
        indrcty(p);
        break;
    default:
        error("unrecognized addressing mode: %d", p->mode);
        break;
    }
}

/*
 * immediate mode instruction
 */
void immediate(const Instr* p)
{
    byte b;
    if (!getbyte(b))
        return; /* EOF */
    printf(" %.2x\t\t%s\t#%.2x", b, *p->name, b);
    pc += 2; /* opcode, value */
}

/*
 * zero page instruction
 */
void zeropage(const Instr* p)
{
    byte b;
    if (!getbyte(b))
        return; /* EOF */
    printf(" %.2x\t\t%s\t$%.2x", b, *p->name, b);
    pc += 2; /* opcode, zero page address */
}

/*
 * zero page, x instruction
 */
void zeropgx(const Instr* p)
{
    byte b;
    if (!getbyte(b))
        return; /* EOF */
    printf(" %.2x\t\t%s\t$%.2x, x", b, *p->name, b);
    pc += 2; /* opcode, zero page address */
}

/*
 * zero page, y instruction
 */
void zeropgy(const Instr* p)
{
    byte b;
    if (!getbyte(b))
        return; /* EOF */
    printf(" %.2x\t\t%s\t$%.2x, y", b, *p->name, b);
    pc += 2; /* opcode, zero page address */
}

/*
 * absolute instruction
 */
void absolute(const Instr* p)
{
    word A;
    if (!getword(A))
        return; /* EOF */
    printf(" %.2x %.2x\t%s\t$%.4hx",
           lobyte(A), hibyte(A), *p->name, A);
    pc += 3; /* opcode, address */
}

/*
 * absolute, x instruction
 */
void abslx(const Instr* p)
{
    word A;
    if (!getword(A))
        return; /* EOF */
    printf(" %.2x %.2x\t%s\t$%.4hx, x",
           lobyte(A), hibyte(A), *p->name, A);
    pc += 3; /* opcode, address */
}

/*
 * absolute, y instruction
 */
void absly(const Instr* p)
{
    word A;
    if (!getword(A))
        return; /* EOF */
    printf(" %.2x %.2x\t%s\t$%.4hx, y",
           lobyte(A), hibyte(A), *p->name, A);
    pc += 3; /* opcode, address */
}

/*
 * relative instruction
 */
void relative(const Instr* p)
{
    /*
     * we must convert the relative address
     * to an absolute address for disassembly
     */
    byte b;
    word A;
    if (!getbyte(b))
        return; /* EOF */
    if (b < 0x80)
        A = (word)(pc + 2 + b);
    else
        A = (word)(pc + 2 - (0x100 - b));
    printf(" %.2x \t\t%s\t$%.4hx",
           b, *p->name, A);
    pc += 2; /* opcode, relative address */
}

/*
 * indirect instruction
 */
void indirect(const Instr* p)
{
    word A;
    if (!getword(A))
        return; /* EOF */
    printf(" %.2x %.2x\t%s\t($%.4hx)",
           lobyte(A), hibyte(A), *p->name, A);
    pc += 3; /* opcode, address */
}

/*
 * indirect, x instruction
 */
void indrctx(const Instr* p)
{
    byte b;
    if (!getbyte(b))
        return; /* EOF */
    printf(" %.2x\t\t%s\t($%.2x, x)", b, *p->name, b);
    pc += 2; /* opcode, address */
}

/*
 * indirect, y instruction
 */
void indrcty(const Instr* p)
{
    byte b;
    if (!getbyte(b))
        return; /* EOF */
    printf(" %.2x\t\t%s\t($%.2x), y", b, *p->name, b);
    pc += 2; /* opcode, address */
}

/*
 * accumulator instruction
 */
void accumulator(const Instr* p)
{
    printf("\t\t%s", *p->name);
    ++pc;
}

/*
 * implied instruction
 */
void implied(const Instr* p)
{
    printf("\t\t%s", *p->name);
    ++pc;
}
