addi $s0, $zero, 64
addi $s1, $zero, 1
addi $s2, $zero, 2
addi $s3, $zero, 4
addi $t1, $zero, 1

ENQUANTO:
	addi $s1, $s1, 1
	addi $s2, $s2, 2
	add $s3, $s3, $s2
	addi $s3, $s3, 1
	beq $s0, $s3, ENQUANTO
	slt $t1, $s0, $s3
	bne $t1, $zero, FIM
	j ENQUANTO
FIM: