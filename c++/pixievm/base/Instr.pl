#!/bin/perl -w 

use strict 'vars';

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

# generate source files
write_modes();			# generate addressing modes
write_opcodes();		# generate opcodes
write_instr_h();		# generate instructions.h
write_instr_cpp();		# generate instructions.cpp
write_opinfo_h();		# generate opinfo.h
write_opinfo_cpp();		# generate opinfo.cpp
write_fetchex_cpp();	# generate fetchex.cpp

# generate modes.h
#
sub write_modes {
	my ($m, $last, $t);
	
	open FH, ">Modes.h" || die "unable to open file Modes.h";		
	print FH "#ifndef __MODES_H__\n";
	print FH "#define __MODES_H__\n\n";
	
	foreach $m (@modes) {
		$t = "AM_$m";
		print FH "#define $t\t";
		print FH "\t" if (length $t < 8);
		print FH "(";
		print FH $last ? "$last + 1" : "0";
		print FH ")\n";
		$last = $t;	
	}
	print FH "\n#define NMODES\t\t($last + 1)	/* number of addressing modes */\n";
	print FH "\n#endif /* __MODES_H__ */\n";
	
	close FH;
}

# generate opcodes.h
#
sub write_opcodes {
	my $n = 0; my $last = 0;
	my ($key, $val, $cnt);
	
	open FH, ">Opcodes.h" || die "unable to open file Opcodes.h";		
	print FH "#ifndef __OPCODES_H__\n";
	print FH "#define __OPCODES_H__\n\n";
	
	foreach $key (sort keys %instr) {
		$cnt = scalar @{$instr{$key}};		
		foreach $val (@{$instr{$key}}) {
			my $op = $cnt == 1 ? "$key" : "$key\_$modes[$val]";
			print FH "#define $op\t";
			print FH "\t" if (length $op < 8);
			print FH "(";
			print FH $last ? "$last + 1" : "0";
			print FH ")\n";
			$last = $op;
		}
		print FH "\n";
	}
	
	print FH "#endif /* __OPCODES_H__ */\n";		
	close FH;	
}

# generate instructions.h
#
sub write_instr_h {
	
	open FH, ">Instructions.h" || die "unable to open file Instructions.h";		
	print FH "#ifndef __INSTRUCTIONS_H__\n";
	print FH "#define __INSTRUCTIONS_H__\n\n";
	
	print FH "typedef const byte *Instr[NMODES];\n\n";
	
	my $key;
	foreach $key (sort keys %instr) {
		print FH "extern const Instr INS_$key;\n";
	}
	
	print FH "\n#endif /* __INSTRUCTIONS_H__ */\n";
	close FH;
}

# generate instructions.cpp
#
sub write_instr_cpp {
	
	open FH, ">Instructions.cpp" || die "unable to open file Instructions.cpp";		
	
	my $n = 0;
	my ($key, $val, $cnt, $m, $i);
	
	print FH "#include \"Common.h\"\n";
	print FH "#include \"Opcodes.h\"\n";
	print FH "#include \"Modes.h\"\n";
	print FH "#include \"Instructions.h\"\n";
	
	print FH "\nconst byte opcodes[] = {";
	foreach $key (sort keys %instr) {
		$cnt = scalar @{$instr{$key}};
		foreach $val (@{$instr{$key}}) {
			if (($n++ % 6) == 0) { print FH "\n\t"; }
			my $op = $cnt == 1 ? "$key" : "$key\_$modes[$val]";
			print FH "$op, ";
		}
	}
	print FH "\n};\n";
	
	$n = 0;
	foreach $key (sort keys %instr) {
		print FH "\nconst Instr INS_$key = {\n";
		for ($m = 0; $m < scalar @modes; $m++) {
			my @vals = @{$instr{$key}};
			for ($i = 0; $i < scalar @vals; $i++) {
				if ($vals[$i] == $m) {
					print FH "\t&opcodes[";
					print FH sprintf("0x%.2X", $n++);
					print FH "],\t/* $modes[$m] */\n";							
					last;
				}
			}	
			if ($i == scalar @vals) {	# no match
				print FH "\tNULL,\t\t\t/* $modes[$m] */\n";
			}	
		}		
		print FH "};\n";	
	}
	
	close FH;
}

# generate opinfo.h
#
sub write_opinfo_h {
	open FH, ">Opinfo.h" || die "unable to open file Opinfo.h";	

	print FH "#ifndef __OPINFO_H__\n";
	print FH "#define __OPINFO_H__\n\n";

	print FH "/* opcode info structure */\n";
	print FH "typedef struct Opinfo {\n";
	print FH "\tconst char **mnemonic;\t/* pointer to mnemonic */\n";
	print FH "\tbyte mode;\t\t\t/* addressing mode */\n";
	print FH "} *LPOPINFO;\n\n";

	printf FH "extern LPOPINFO opinfo[";
	print FH 1 << 8;
	print FH "];\n";
		
	print FH "\n#endif /* __OPINFO_H__ */\n";

	close FH;
}

# generate opinfo.cpp
#
sub write_opinfo_cpp {
	open FH, ">Opinfo.cpp" || die "unable to open file Opinfo.cpp";	

	print FH "#include \"Common.h\"\n";
	print FH "#include \"Modes.h\"\n";
	print FH "#include \"Opinfo.h\"\n\n";

	print FH "namespace { /* anonymous */\n\nconst char *mnemonics[] = {";
	my ($key, $val, $m, $n);
	foreach $key (sort keys %instr) {
		if (($n++ % 6) == 0) { print FH "\n\t"; }
		print FH "\"";
		print FH lc $key;
		print FH "\",";
	}
	print FH "\n};\n\n";

	$n = 0;
	foreach $key (sort keys %instr) {
		print FH "#define $key (&mnemonics[$n])\n";
		$n++;
	}
	
	print FH "\n";

	foreach $key (sort keys %instr) {
		foreach $val (@{$instr{$key}}) {
			print FH "Opinfo $key\_$modes[$val]";
			print FH " = { $key, AM_$modes[$val] };\n";
		}
	}

	print FH "\n} /* anonymous */\n\n";

	print FH "LPOPINFO opinfo[";
	print FH 1 << 8;
	print FH "] = {\n";

	$n = 0;
	foreach $key (sort keys %instr) {
		foreach $val (@{$instr{$key}}) {
			print FH "\t&$key\_$modes[$val],";
			print FH "\t /*";
			print FH sprintf("0x%.2X", $n++);
			print FH " */\n";
		}
	}

	for ( ; $n < (1 << 8);$n++) {
		print FH "\tNULL,";
		print FH "\t /*";
		print FH sprintf("0x%.2X", $n);
		print FH " */\n";
	}

	print FH "};\n";

	close FH;
}

# generate fetch /execute switch
#
sub write_fetchex_cpp {
	open FH, ">FetchEx.cpp" || die "unable to open file FetchEx.cpp";	
	
	my ($key, $val, $cnt);
	foreach $key (sort keys %instr) {
		$cnt = scalar @{$instr{$key}};
		foreach $val (@{$instr{$key}}) {
			my $op = $cnt == 1 ? "$key" : "$key\_$modes[$val]";
			print FH "case $op:\n";
			print FH "\tDO_$op();\n";
			print FH "\tbreak;\n";
		}
	}
	
	print FH "default:\n";
	print FH "\tbreak;\n";
	close FH;
}

