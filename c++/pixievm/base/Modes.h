#ifndef __MODES_H__
#define __MODES_H__

#define AM_RR8		(0)
#define AM_RR16		(AM_RR8 + 1)
#define AM_RM8		(AM_RR16 + 1)
#define AM_RM16		(AM_RM8 + 1)
#define AM_RA8		(AM_RM16 + 1)
#define AM_RA16		(AM_RA8 + 1)
#define AM_RI8		(AM_RA16 + 1)
#define AM_RI16		(AM_RI8 + 1)
#define AM_MR8		(AM_RI16 + 1)
#define AM_MR16		(AM_MR8 + 1)
#define AM_M8I8		(AM_MR16 + 1)
#define AM_M16I8	(AM_M8I8 + 1)
#define AM_MI16		(AM_M16I8 + 1)
#define AM_AR8		(AM_MI16 + 1)
#define AM_AR16		(AM_AR8 + 1)
#define AM_A8I8		(AM_AR16 + 1)
#define AM_A16I8	(AM_A8I8 + 1)
#define AM_AI16		(AM_A16I8 + 1)
#define AM_R8		(AM_AI16 + 1)
#define AM_R16		(AM_R8 + 1)
#define AM_M8		(AM_R16 + 1)
#define AM_M16		(AM_M8 + 1)
#define AM_A8		(AM_M16 + 1)
#define AM_A16		(AM_A8 + 1)
#define AM_IMPLIED	(AM_A16 + 1)
#define AM_I8		(AM_IMPLIED + 1)
#define AM_I16		(AM_I8 + 1)

#define NMODES		(AM_I16 + 1)	/* number of addressing modes */

#endif /* __MODES_H__ */
