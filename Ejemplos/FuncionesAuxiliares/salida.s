###################
# Seccion de datos
	.data

str1:
	.asciiz "He entrado a la función patata\n"
str2:
	.asciiz "El valor del parámetro es "
str3:
	.asciiz "\n"
str4:
	.asciiz "Inicio del programa\n"
str5:
	.asciiz "a"
str6:
	.asciiz "No a y b\n"
str7:
	.asciiz "c = "
str8:
	.asciiz "Valor de resultado "
str9:
	.asciiz "Valor de la función compiladores(): "
str10:
	.asciiz "Final"

###################
# Seccion de codigo
	.text
	.globl main
patata:
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
	move $s0,$a0
	move $s1,$v0
	li $v0,4
	la $a0,str1
	syscall
	move $a0,$s0
	move $v0,$s1
	move $s0,$a0
	move $s1,$v0
	li $v0,4
	la $a0,str2
	syscall
	move $a0,$s0
	move $v0,$s1
	move $t0,$a0
	move $t1,$a1
	add $t0,$t0,$t1
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
	li $t0,4
	move $v0,$t0
	b fin_funcion_1
fin_funcion_1:
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
	addiu $sp,$sp,-20
	li $t0,0
	sw $t0,4($sp)
	li $t0,0
	sw $t0,8($sp)
	move $s0,$a0
	move $s1,$v0
	li $v0,4
	la $a0,str4
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
	beqz $t0,else_7
	move $s0,$a0
	move $s1,$v0
	li $v0,4
	la $a0,str5
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
	b end_if_8
else_7:
	lw $t1,8($sp)
	beqz $t1,else_5
	move $s0,$a0
	move $s1,$v0
	li $v0,4
	la $a0,str6
	syscall
	move $a0,$s0
	move $v0,$s1
	b end_if_6
else_5:
while_start_4:
	lw $t2,12($sp)
	beqz $t2,while_end_3
	addiu $sp,$sp,-8
	li $t3,0
	sw $t3,4($sp)
	li $t3,4
	li $t4,3
	li $t5,5
	mul $t4,$t4,$t5
	add $t3,$t3,$t4
	sw $t3,8($sp)
	move $s0,$a0
	move $s1,$v0
	li $v0,4
	la $a0,str7
	syscall
	move $a0,$s0
	move $v0,$s1
	lw $t3,20($sp)
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
	lw $t3,20($sp)
	li $t4,2
	sub $t3,$t3,$t4
	li $t4,1
	add $t3,$t3,$t4
	sw $t3,20($sp)
	lw $t3,8($sp)
	li $t4,1
	add $t3,$t3,$t4
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
	addiu $sp,$sp,8
	b while_start_4
while_end_3:
end_if_6:
end_if_8:
	li $t0,7
	sw $t0,16($sp)
	lw $t0,16($sp)
	li $t1,3
	li $t2,10
	add $t1,$t1,$t2
	addiu $sp,$sp,-8
	sw $a0,0($sp)
	sw $a1,4($sp)
	move $a0,$t0
	move $a1,$t1
	jal patata
	lw $a0,0($sp)
	lw $a1,4($sp)
	addiu $sp,$sp,8
	jal compiladores
	move $t2,$v0
	sw $t2,20($sp)
	move $s0,$a0
	move $s1,$v0
	li $v0,4
	la $a0,str8
	syscall
	move $a0,$s0
	move $v0,$s1
	lw $t2,20($sp)
	li $v0,1
	move $a0,$t2
	syscall
	move $s0,$a0
	move $s1,$v0
	li $v0,4
	la $a0,str3
	syscall
	move $a0,$s0
	move $v0,$s1
	move $s0,$a0
	move $s1,$v0
	li $v0,4
	la $a0,str9
	syscall
	move $a0,$s0
	move $v0,$s1
	jal compiladores
	move $t2,$v0
	li $v0,1
	move $a0,$t2
	syscall
	move $s0,$a0
	move $s1,$v0
	li $v0,4
	la $a0,str10
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
	addiu $sp,$sp,20
	addiu $sp,$sp,44

###################
# Fin
	li $v0,10
	syscall