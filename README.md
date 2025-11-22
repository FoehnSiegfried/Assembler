# Assembler
risc-v asm
一个RISC-V的汇编器，通过./compile <输入地址> <输出地址>执行

R
inst rd rs1 rs2
add x10 x11 x12
I
inst rd rs1 imm
addi x10 x11 0
S
inst rs2 imm rs1
sb x11 8 x10
B
inst rs1 rs2 imm
bne x10 x11 8
U
inst rd imm
lui x10 128
J
inst rd imm
jal x10 128