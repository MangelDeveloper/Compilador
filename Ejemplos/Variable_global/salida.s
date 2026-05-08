###################
# Seccion de datos
	.data

str1:
	.asciiz "El valor devuelto de la función compiladores es: "
str2:
	.asciiz "\n"
str3:
	.asciiz "El valor de global es: "
_global:
	.word 400

###################
# Seccion de codigo
	.text
	.globl main
compiladores:
	addiu $sp,$sp,-44
	sw $ra,0($sp)
	sw $t0,4($sp)
	sw $t1,8($sp)
	sw $t2,12($sp)
	sw $t3,16($sp)
	sw $t4,20($sp)
	sw $t5,24($sp)
	sw $t6,28($sp)
	sw $t7,32($sp)
	sw $t8,36($sp)
	sw $t9,40($sp)
	move $v0,$zero
	move $t0,$a0
	move $v0,$t0
	b fin_funcion_0
fin_funcion_0:
	lw $t9,40($sp)
	lw $t8,36($sp)
	lw $t7,32($sp)
	lw $t6,28($sp)
	lw $t5,24($sp)
	lw $t4,20($sp)
	lw $t3,16($sp)
	lw $t2,12($sp)
	lw $t1,8($sp)
	lw $t0,4($sp)
	lw $ra,0($sp)
	addiu $sp,$sp,44
	jr $ra
main:
	addiu $sp,$sp,-44
	move $s0,$a0
	move $s1,$v0
	li $v0,4
	la $a0,str1
	syscall
	move $a0,$s0
	move $v0,$s1
	li $t0,10
	addiu $sp,$sp,-4
	sw $a0,0($sp)
	move $a0,$t0
	jal compiladores
	move $t1,$v0
	lw $a0,0($sp)
	addiu $sp,$sp,4
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
	move $s0,$a0
	move $s1,$v0
	li $v0,4
	la $a0,str3
	syscall
	move $a0,$s0
	move $v0,$s1
	lw $t1,_global
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
	addiu $sp,$sp,44

###################
# Fin
	li $v0,10
	syscall