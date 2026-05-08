###################
# Seccion de datos
	.data

str1:
	.asciiz "Valor de a: "
str2:
	.asciiz "\nValor de b: "
str3:
	.asciiz "\n"

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
	sw $v0,4($sp)
	move $a0,$s0
	move $v0,$s1
	move $s0,$a0
	move $s1,$v0
	li $v0,5
	syscall
	sw $v0,8($sp)
	move $a0,$s0
	move $v0,$s1
	move $s0,$a0
	move $s1,$v0
	li $v0,4
	la $a0,str1
	syscall
	move $a0,$s0
	move $v0,$s1
	lw $t0,4($sp)
	li $v0,1
	move $a0,$t0
	syscall
	move $s0,$a0
	move $s1,$v0
	li $v0,4
	la $a0,str2
	syscall
	move $a0,$s0
	move $v0,$s1
	lw $t0,8($sp)
	li $v0,1
	move $a0,$t0
	syscall
	move $s0,$a0
	move $s1,$v0
	li $v0,4
	la $a0,str3
	syscall
	move $a0,$s0
	move $v0,$s1
	addiu $sp,$sp,8
	addiu $sp,$sp,44

###################
# Fin
	li $v0,10
	syscall