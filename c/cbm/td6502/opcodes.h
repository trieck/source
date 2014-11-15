/*
 * opcodes.h
 *
 * opcode definitions
 *
 */
#ifndef __OPCODES_H__
#define __OPCODES_H__
#define INSTRUCTIONS 256
/*
 * instruction structure
 */
typedef struct {
    const char **name;
    addrmode mode;
} Instr;
extern const Instr* instructions[INSTRUCTIONS];
#endif // __OPCODES_H__