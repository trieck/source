package org.pixielib.pixievm;

/**
 * 16-bit Big Endian Machine Support for 4 16-bit general purpose registers: A,
 * B, C, D. Register SP is a 16-bit stack pointer. Register IP is a 16-bit
 * instruction pointer. Flags register holds various CPU state flags ie. break,
 * interrupt disable, zero and carry.
 * <p/>
 * Each general purpose register can be referred to by it's high byte and low
 * byte:
 * <p/>
 * ----------- ----------- ----------- ----------- | AX | | BX | | CX | | DX |
 * ----------- ----------- ----------- ----------- | AH | AL | | BH | BL | | CH |
 * CL | | DH | DL | ----------- ----------- ----------- -----------
 */
public class CPU {

    private static final int BRK_FLAG = 0x08;
    private static final int INT_DISABLE_FLAG = 0x04;
    private static final int ZERO_FLAG = 0x02;
    private static final int CARRY_FLAG = 0x01;
    private static CPU instance = null;
    /* Registers */
    private char flags;

    private CPU() {
    }

    public static CPU getInstance() {
        if (instance == null) {
            instance = new CPU();
        }
        return instance;
    }

    public boolean getBreakFlag() {
        return ((flags & BRK_FLAG) >> 3) != 0;
    }

    public boolean getIntDisableFlag() {
        return ((flags & INT_DISABLE_FLAG) >> 2) != 0;
    }

    public boolean getZeroFlag() {
        return ((flags & ZERO_FLAG) >> 1) != 0;
    }

    /* Public ctor */

    public boolean getCarryFlag() {
        return getCarry() != 0;
    }

    private int getCarry() {
        return flags & CARRY_FLAG;
    }
}
