/*
 * 	CODE.H	code generation
 *
 * 	Copyright (C) 2001 Thomas A. Rieck <trieck@bellsouth.net>
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
 */
#pragma once

#include "common.h"
#include "opcodes.h"

/***************************************************************************/
void abs_code(const Instr* instr, word operand);
void abx_code(const Instr* instr, word operand);
void aby_code(const Instr* instr, word operand);
void branch_fixup(const char* name);
void byte_code(byte value);
void decl_hibyte_fixup(const char* name);
void decl_lobyte_fixup(const char* name);
void declword_fixup(const char* name);
void defbase(word address);
void deflabel(const char* name);
void idx_code(const Instr* instr, byte operand);
void idy_code(const Instr* instr, byte operand);
void imm_code(const Instr* instr, byte operand);
void imp_acc_code(const Instr* instr);
void ind_code(const Instr* instr, word operand);
void op_fixup(const char* name);
void op_hibyte_fixup(const char* name);
void op_lobyte_fixup(const char* name);
void rel_code(const Instr* instr, word operand);
void resolve_fixups(void);
void text_code(const char* value);
void word_code(word value);
void write_code(void);
void zp_code(const Instr* instr, byte operand);
void zpx_code(const Instr* instr, byte operand);
void zpy_code(const Instr* instr, byte operand);
void ztext_code(const char* value);
/***************************************************************************/
