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
for_start_2:
	lw $t0,4($sp)
	li $t1,5
	slt $t0,$t0,$t1
	beqz $t0,for_end_1
	lw $t1,4($sp)
	li $v0,1
	move $a0,$t1
	syscall
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