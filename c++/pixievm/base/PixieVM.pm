#!/usr/bin/perl -w

package PixieVM;
use strict qw(vars warnings);

# addressing modes 
use constant RR8 		=> 0;	
use constant RR16 		=> RR8 + 1;
use constant RM8		=> RR16 + 1;
use constant RM16		=> RM8 + 1;
use constant RA8		=> RM16 + 1;
use constant RA16		=> RA8 + 1;
use constant RI8		=> RA16 + 1;
use constant RI16		=> RI8 + 1;
use constant MR8		=> RI16 + 1;
use constant MR16		=> MR8 + 1;
use constant M8I8		=> MR16 + 1;
use constant M16I8		=> M8I8 + 1;
use constant MI16		=> M16I8 + 1;
use constant AR8		=> MI16 + 1;
use constant AR16		=> AR8 + 1;
use constant A8I8		=> AR16 + 1;
use constant A16I8		=> A8I8 + 1;
use constant AI16		=> A16I8 + 1;
use constant R8			=> AI16 + 1;
use constant R16		=> R8 + 1;
use constant M8			=> R16 + 1;
use constant M16		=> M8 + 1;
use constant A8			=> M16 + 1;
use constant A16		=> A8 + 1;
use constant IMPLIED	=> A16 + 1;
use constant I8		 	=> IMPLIED + 1;
use constant I16		=> I8 + 1;

# addressing mode array
my @modes = qw(
	RR8
	RR16
	RM8
	RM16
	RA8
	RA16
	RI8
	RI16
	MR8
	MR16
	M8I8
	M16I8
	MI16
	AR8
	AR16
	A8I8
	A16I8
	AI16
	R8
	R16
	M8
	M16
	A8
	A16
	IMPLIED
	I8
	I16
);

# group one addressing modes
my @group_one = (
	RR8, RR16, RM8, RM16, RA8, RA16, RI8,
	RI16, MR8, MR16, M8I8, M16I8, MI16, AR8, AR16,
	A8I8, A16I8, AI16
);

# group two addressing modes
my @group_two = (R8, R16, M8, M16, A8, A16);

# group three addressing modes
my @group_three = (IMPLIED);

# group four addressing modes
my @group_four = (R16, M16, A16, I16);

# group five addressing modes
my @group_five = (I8);

# group six addressing modes
my @group_six = (R8, R16, M8, M16, A8, A16);

# group seven addressing modes
my @group_seven = (R8, R16, M8, M16, A8, A16, I8, I16);

# instructions
my %instr = (
	"ADC" => \@group_one,  
	"AND" => \@group_one, 
	"BIT" => \@group_one, 
	"BRK" => \@group_three, 
	"CALL" => \@group_four, 
	"CLC" => \@group_three, 
	"CLI" => \@group_three, 
	"CMP" => \@group_one, 
	"DEC" => \@group_two, 
	"DEX" => \@group_three,
	"INC" => \@group_two, 
	"INX" => \@group_three, 
	"IRET" => \@group_three, 
	"JCC" => \@group_five, 
	"JCS" => \@group_five, 
	"JMI" => \@group_five, 
	"JMP" => \@group_four, 
	"JNZ" => \@group_five, 
	"JPL" => \@group_five, 
	"JVC" => \@group_five, 
	"JVS" => \@group_five, 
	"JZ" => \@group_five, 
	"MOV" => \@group_one, 
	"NOP" => \@group_three, 
	"OR" => \@group_one, 
	"POP" => \@group_six, 
	"POPA" => \@group_three,
	"POPF" => \@group_three,
	"PUSH" => \@group_seven,
	"PUSHA" => \@group_three, 
	"PUSHF" => \@group_three,	
	"RET" => \@group_three, 
	"ROL" => \@group_two, 
	"ROR" => \@group_two, 
	"SBB" => \@group_one, 
	"SEC" => \@group_three, 
	"SEI" => \@group_three,
	"SHL" => \@group_two, 
	"SHR" => \@group_two, 
	"XOR" => \@group_one, 
);

#############################################################################
# EOF
1;  # so the require or use succeeds

