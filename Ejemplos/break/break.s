###################
# Seccion de datos
	.data


###################
# Seccion de codigo
	.text
	.globl main
main:
	addiu $sp,$sp,-44
	addiu $sp,$sp,-4
	li $t0,0
	sw $t0,4($sp)
do_while_start_2:
	b do_while_end_1
	lw $t0,4($sp)
	li $v0,1
	move $a0,$t0
	syscall
	li $t0,1
	bnez $t0,do_while_start_2
do_while_end_1:
	addiu $sp,$sp,4
	addiu $sp,$sp,44

###################
# Fin
	li $v0,10
	syscall