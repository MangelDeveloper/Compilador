###################
# Seccion de datos
	.data

str1:
	.asciiz "Inicio del programa\n"
str2:
	.asciiz "a"
str3:
	.asciiz "\n"
str4:
	.asciiz "No a y b\n"
str5:
	.asciiz "c = "
str6:
	.asciiz "Final"

###################
# Seccion de codigo
	.text
	.globl main
main:
	addiu $sp,$sp,-44
	addiu $sp,$sp,-12
	li $t0,0
	sw $t0,4($sp)
	li $t0,0
	sw $t0,8($sp)
	move $s0,$a0
	move $s1,$v0
	li $v0,4
	la $a0,str1
	syscall
	move $a0,$s0
	move $v0,$s1
	li $t0,5
	li $t1,2
	add $t0,$t0,$t1
	li $t1,2
	sub $t0,$t0,$t1
	sw $t0,12($sp)
	lw $t0,4($sp)
	beqz $t0,else_5
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
	b end_if_6
else_5:
	lw $t1,8($sp)
	beqz $t1,else_3
	move $s0,$a0
	move $s1,$v0
	li $v0,4
	la $a0,str4
	syscall
	move $a0,$s0
	move $v0,$s1
	b end_if_4
else_3:
while_start_2:
	lw $t2,12($sp)
	beqz $t2,while_end_1
	move $s0,$a0
	move $s1,$v0
	li $v0,4
	la $a0,str5
	syscall
	move $a0,$s0
	move $v0,$s1
	lw $t3,12($sp)
	li $v0,1
	move $a0,$t3
	syscall
	move $s0,$a0
	move $s1,$v0
	li $v0,4
	la $a0,str3
	syscall
	move $a0,$s0
	move $v0,$s1
	lw $t3,12($sp)
	li $t4,2
	sub $t3,$t3,$t4
	li $t4,1
	add $t3,$t3,$t4
	sw $t3,12($sp)
	b while_start_2
while_end_1:
end_if_4:
end_if_6:
	move $s0,$a0
	move $s1,$v0
	li $v0,4
	la $a0,str6
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
	addiu $sp,$sp,12
	addiu $sp,$sp,44

###################
# Fin
	li $v0,10
	syscall