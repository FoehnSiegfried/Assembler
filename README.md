# RVX Assembler
risc-v asm
一个RISC-V的汇编器，通过./compile <输入地址> <输出地址>执行
###### 每次发布整体版本自动更新编译器版本至最新版
###### 因在开发测试期，当新版本出现时极可能老版本无法直接使用，推荐使用默认最新版

## 整体分层：
编译实指令         RealInst
编译伪指令         PseudoInst
编译汇编器处理指令  AsmInst

Temp: 缓存区

## 汇编器之优化：
常数折叠优化：连续对一个寄存器加加减减自动合并成一个操作

## 命名之法：
#### 对于表高组：语境中相对更靠近根本的，本源性的，放在读取起始位靠前的位置，逐级进位，中间以"_"（下划线）隔开
#### 对于表低组：连贯系内以单词首字母大写为分割，不加"_"（下划线）
### 例子：
#### 表RVX之类型的Assembler汇编器
#### isSignedInteger分支工具函数命名

## 实指令：
### RV32I：
#### R：
##### inst rd rs1 rs2
##### add x10 x11 x12
#### I：
##### inst rd rs1 imm
##### addi x10 x11 0
#### S：
##### inst rs2 imm rs1
##### sb x11 8 x10
#### B：
##### inst rs1 rs2 imm
##### bne x10 x11 8
#### U：
##### inst rd imm
##### lui x10 128
#### J：
##### inst rd imm
##### jal x10 128

## 伪指令：（以下列了几个目前便仅支持这几个）
#### li rd imm   //加载32位立即数imm到rd寄存器中

##问题：
1.有的报错返回值都是NEG，如cllectLabel这样，和verify都是NEG，尽可能区分开
2.！inst简单提供给处理类太草率，应分类为rd，opcode，rs1...
3.命名法需要更清晰
