###################
# Seccion de datos
	.data


###################
# Seccion de codigo
	.text
	.globl main
main:
	addiu $sp,$sp,-44
	addiu $sp,$sp,-8
	move $s0,$a0
	move $s1,$v0
	li $v0,5
	syscall
	sw $v0,_a
	move $a0,$s0
	move $v0,$s1
	move $s0,$a0
	move $s1,$v0
	li $v0,5
	syscall
	sw $v0,_b
	move $a0,$s0
	move $v0,$s1
	addiu $sp,$sp,8
	addiu $sp,$sp,44

###################
# Fin
	li $v0,10
	syscall