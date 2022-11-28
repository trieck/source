package org.pixielib.pixievm;

public class Opcodes {

    /* Generate the table of opcodes for all instructions */

    /**
     * The following rules are used in encoding instructions based on the
     * addressing mode used.
     * <p/>
     * Implied OC - R8 OC+R - M8 OC M8 IMM8 OC IW R16 OC+R - M16 OC MW IMM16 OC
     * IW R8, R8 OC R R8, IMM8 OC+R IB R16, R16 OC R M16, R16 OC R R16, M16 OC R
     * R16, IMM16 OC+R IW
     */
    private static final int AM_IMPLIED = 1 << 0;
    private static final Object[] BRK = {"BRK", AM_IMPLIED};
    private static final Object[] CLC = {"CLC", AM_IMPLIED};
    private static final Object[] CLI = {"CLI", AM_IMPLIED};
    private static final Object[] IRET = {"IRET", AM_IMPLIED};
    private static final Object[] NOP = {"NOP", AM_IMPLIED};
    private static final Object[] RET = {"RET", AM_IMPLIED};
    private static final Object[] SEC = {"SEC", AM_IMPLIED};
    private static final Object[] SEI = {"SEI", AM_IMPLIED};
    private static final int AM_R8 = 1 << 1;
    private static final int AM_M8 = 1 << 2;
    private static final int AM_IMM8 = 1 << 3;
    private static final Object[] JCC = {"JCC", AM_M8 | AM_IMM8};
    private static final Object[] JCS = {"JCS", AM_M8 | AM_IMM8};
    private static final Object[] JNZ = {"JNZ", AM_M8 | AM_IMM8};
    private static final Object[] JZ = {"JZ", AM_M8 | AM_IMM8};
    private static final int AM_R16 = 1 << 4;
    private static final int AM_M16 = 1 << 5;
    private static final Object[] DEC = {"DEC",
            AM_R8 | AM_R16 | AM_M8 | AM_M16};
    private static final Object[] INC = {"INC",
            AM_R8 | AM_R16 | AM_M8 | AM_M16};
    private static final Object[] POP = {"POP", AM_R16 | AM_M16};
    private static final Object[] ROL = {"ROL", AM_R8 | AM_M16};
    private static final Object[] ROR = {"ROR", AM_R8 | AM_M16};
    private static final Object[] SHL = {"SHL", AM_R8 | AM_M16};
    private static final Object[] SHR = {"SHR", AM_R8 | AM_M16};
    private static final int AM_IMM16 = 1 << 6;
    private static final Object[] CALL = {"CALL",
            AM_R16 | AM_M16 | AM_IMM8 | AM_IMM16};
    private static final Object[] JMP = {"JMP",
            AM_M8 | AM_IMM8 | AM_R16 | AM_R16 | AM_IMM16};
    private static final Object[] PUSH = {"PUSH", AM_R16 | AM_M16 | AM_IMM16};
    private static final int AM_R8_R8 = 1 << 7;
    private static final int AM_R8_IMM8 = 1 << 8;
    private static final int AM_R16_R16 = 1 << 9;
    private static final int AM_M16_R16 = 1 << 10;
    private static final int AM_R16_M16 = 1 << 11;
    private static final int AM_R16_IMM16 = 1 << 12;
    /* Addressing modes */
    private static final int[] MODES = {AM_IMPLIED, AM_R8, AM_M8, AM_IMM8,
            AM_R16, AM_M16, AM_IMM16, AM_R8_R8, AM_R8_IMM8, AM_R16_R16,
            AM_M16_R16, AM_R16_M16, AM_R16_IMM16};
    /* Many instructions support this general form */
    private static final int AM_GENERAL = AM_R8_R8 | AM_R8_IMM8 | AM_R16_R16
            | AM_M16_R16 | AM_R16_M16 | AM_R16_IMM16;
    /* The instructions and their addressing modes */
    private static final Object[] ADC = {"ADC", AM_GENERAL};
    private static final Object[] AND = {"AND", AM_GENERAL};
    private static final Object[] BIT = {"BIT", AM_GENERAL};
    private static final Object[] CMP = {"CMP", AM_GENERAL};
    private static final Object[] MOV = {"MOV", AM_GENERAL};
    private static final Object[] OR = {"OR", AM_GENERAL};
    private static final Object[] SBB = {"SBB", AM_GENERAL};
    private static final Object[] XOR = {"XOR", AM_GENERAL};

    private static final Object[][] INSTR = {ADC, AND, BIT, BRK, CALL, CLC,
            CLI, CMP, DEC, INC, IRET, JCC, JCS, JMP, JNZ, JZ, MOV, NOP, OR,
            POP, PUSH, RET, ROL, ROR, SBB, SEC, SEI, SHL, SHR, XOR};

    /**
     * Register encoding
     * <p/>
     * 16bit 8bit Binary Decimal ------------------------------------- A AL 0000
     * 00 B AH 0001 01 C BL 0010 02 D BH 0011 03 SP CL 0100 04 IP CH 0101 05
     * FLAGS DL 0110 06 -- DH 0111 07
     */

    /*
      *
      *
      * We need to write a computer program that generates the following:
      *
      * ADC_BASE_OPCODE 0x00
      *
      * ADC_R8_R8 = ADC_BASE_OPCODE ADC_R8_IMM8 = ADC_BASE_OPCODE + 1 ADC_R16_R16 =
      * ADC_R8_IMM8 + MAX_REG_ENCODING ADC_M16_R16 = ADC_R16_R16 + 1 ADC_R16_M16 =
      * ADC_M16_R16 + 1 ADC_R16_IMM16 = ADC_16_M16 ...
      *
      */

    /*
      * Here is an example of encoding an opcode and it's operands. Consider the
      * general form of ADC with two 8-bit registers:
      *
      * ADC R8, R8 0x00 R
      *
      * Now considering the specific example:
      *
      * ADC AL, BL 0x00 0000 0010 0x00 0x02
      *
      * We have now fully encoded this instruction. We have stored the opcode
      * Plus an encoding of the register operands.
      *
      * Next consider the following form:
      *
      * ADC R8, IMM8 0x01+R IB
      *
      * And a specific example:
      *
      * ADC CL, 34h 0x01+2 0x34 0x03 0x34
      *
      * And another:
      *
      * Here we assume the byte 0xC0 is used for the opcode "ADC M16, R16"
      *
      * ADC [A], B 0xC0 0000 0001 0xC0 0x01
      */
    public static void main(String[] args) {
        for (final Object[] element : INSTR) {
            for (final int element2 : MODES) {
                final int mode = (Integer) element[1];
                if ((mode & element2) != 0) {
                    switch (element2) {
                        case AM_IMPLIED:
                            System.out.println(element[0]);
                            break;
                        case AM_R8:
                            System.out.println(element[0] + " R8");
                            break;
                        case AM_M8:
                            System.out.println(element[0] + " M8");
                            break;
                        case AM_IMM8:
                            System.out.println(element[0] + " IMM8");
                            break;
                        case AM_R16:
                            System.out.println(element[0] + " R16");
                            break;
                        case AM_M16:
                            System.out.println(element[0] + " M16");
                            break;
                        case AM_IMM16:
                            System.out.println(element[0] + " IMM16");
                            break;
                        case AM_R8_R8:
                            System.out.println(element[0] + " R8, R8");
                            break;
                        case AM_R8_IMM8:
                            System.out.println(element[0] + " R8, IMM8");
                            break;
                        case AM_R16_R16:
                            System.out.println(element[0] + " R16, R16");
                            break;
                        case AM_M16_R16:
                            System.out.println(element[0] + " M16, R16");
                            break;
                        case AM_R16_M16:
                            System.out.println(element[0] + " R16, M16");
                            break;
                        case AM_R16_IMM16:
                            System.out.println(element[0] + " R16, IMM16");
                            break;
                    }
                }
            }
        }
    }
}
