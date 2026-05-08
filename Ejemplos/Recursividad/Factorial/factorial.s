###################
# Seccion de datos
	.data

str1:
	.asciiz "factorial de 5 es: "
str2:
	.asciiz "\n"

###################
# Seccion de codigo
	.text
	.globl main
factorial:
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
	li $t1,0
	seq $t0,$t0,$t1
	beqz $t0,end_if_1
	li $t1,1
	move $v0,$t1
	b fin_funcion_0
end_if_1:
	move $t0,$a0
	move $t1,$a0
	li $t2,1
	sub $t1,$t1,$t2
	addiu $sp,$sp,-4
	sw $a0,0($sp)
	move $a0,$t1
	jal factorial
	move $t2,$v0
	lw $a0,0($sp)
	addiu $sp,$sp,4
	mul $t0,$t0,$t2
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
	addiu $sp,$sp,-4
	li $t0,5
	addiu $sp,$sp,-4
	sw $a0,0($sp)
	move $a0,$t0
	jal factorial
	move $t2,$v0
	lw $a0,0($sp)
	addiu $sp,$sp,4
	sw $t2,4($sp)
	move $s0,$a0
	move $s1,$v0
	li $v0,4
	la $a0,str1
	syscall
	move $a0,$s0
	move $v0,$s1
	lw $t2,4($sp)
	li $v0,1
	move $a0,$t2
	syscall
	move $s0,$a0
	move $s1,$v0
	li $v0,4
	la $a0,str2
	syscall
	move $a0,$s0
	move $v0,$s1
	addiu $sp,$sp,4
	addiu $sp,$sp,44

###################
# Fin
	li $v0,10
	syscall