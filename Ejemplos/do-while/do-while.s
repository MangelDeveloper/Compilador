###################
# Seccion de datos
	.data

str1:
	.asciiz "\n"

###################
# Seccion de codigo
	.text
	.globl main
main:
	addiu $sp,$sp,-44
	addiu $sp,$sp,-4
	li $t0,5
	sw $t0,4($sp)
do_while_start_2:
	lw $t0,4($sp)
	li $v0,1
	move $a0,$t0
	syscall
	move $s0,$a0
	move $s1,$v0
	li $v0,4
	la $a0,str1
	syscall
	move $a0,$s0
	move $v0,$s1
	lw $t0,4($sp)
	li $t1,1
	sub $t0,$t0,$t1
	sw $t0,4($sp)
	lw $t0,4($sp)
	li $t1,0
	sge $t0,$t0,$t1
	bnez $t0,do_while_start_2
do_while_end_1:
	addiu $sp,$sp,4
	addiu $sp,$sp,44

###################
# Fin
	li $v0,10
	syscall