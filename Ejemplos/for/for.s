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
	li $t0,0
	sw $t0,4($sp)
for_start_2:
	lw $t0,4($sp)
	li $t1,5
	slt $t0,$t0,$t1
	beqz $t0,for_end_1
	lw $t1,4($sp)
	li $v0,1
	move $a0,$t1
	syscall
	move $s0,$a0
	move $s1,$v0
	li $v0,4
	la $a0,str1
	syscall
	move $a0,$s0
	move $v0,$s1
	lw $t1,4($sp)
	li $t2,1
	add $t1,$t1,$t2
	sw $t1,4($sp)
	b for_start_2
for_end_1:
	addiu $sp,$sp,4
	addiu $sp,$sp,44

###################
# Fin
	li $v0,10
	syscall