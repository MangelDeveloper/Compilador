###################
# Seccion de datos
	.data

str1:
	.asciiz "El valor de b es: "
str2:
	.asciiz "\n"

###################
# Seccion de codigo
	.text
	.globl main
main:
	addiu $sp,$sp,-44
	addiu $sp,$sp,-8
	li $t0,0
	sw $t0,4($sp)
	li $t0,6
	sw $t0,8($sp)
while_start_2:
	lw $t0,8($sp)
	lw $t1,4($sp)
	sgt $t0,$t0,$t1
	beqz $t0,while_end_1
	move $s0,$a0
	move $s1,$v0
	li $v0,4
	la $a0,str1
	syscall
	move $a0,$s0
	move $v0,$s1
	lw $t1,8($sp)
	li $v0,1
	move $a0,$t1
	syscall
	move $s0,$a0
	move $s1,$v0
	li $v0,4
	la $a0,str2
	syscall
	move $a0,$s0
	move $v0,$s1
	lw $t1,8($sp)
	li $t2,1
	sub $t1,$t1,$t2
	sw $t1,8($sp)
	b while_start_2
while_end_1:
	addiu $sp,$sp,8
	addiu $sp,$sp,44

###################
# Fin
	li $v0,10
	syscall
