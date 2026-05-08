###################
# Seccion de datos
	.data

str1:
	.asciiz "El valor de c es: "
str2:
	.asciiz "\n"

###################
# Seccion de codigo
	.text
	.globl main
main:
	addiu $sp,$sp,-44
	addiu $sp,$sp,-12
	li $t0,2
	li $t1,3
	mul $t0,$t0,$t1
	sw $t0,4($sp)
	li $t0,2
	sw $t0,8($sp)
	li $t0,2
	sw $t0,12($sp)
	lw $t0,8($sp)
	lw $t1,4($sp)
	sgt $t0,$t0,$t1
	beqz $t0,else_1
	lw $t1,12($sp)
	li $t2,1
	sub $t1,$t1,$t2
	sw $t1,12($sp)
	b end_if_2
else_1:
	lw $t1,12($sp)
	li $t2,1
	add $t1,$t1,$t2
	sw $t1,12($sp)
end_if_2:
	move $s0,$a0
	move $s1,$v0
	li $v0,4
	la $a0,str1
	syscall
	move $a0,$s0
	move $v0,$s1
	lw $t0,12($sp)
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
	addiu $sp,$sp,12
	addiu $sp,$sp,44

###################
# Fin
	li $v0,10
	syscall