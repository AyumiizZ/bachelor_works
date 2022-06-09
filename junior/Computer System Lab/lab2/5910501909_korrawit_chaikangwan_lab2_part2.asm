.data
	space: .asciiz " "
	endl: .asciiz "\n"
.text
	

.globl main

main:
	# init stack (4*12 = 48)
	addiu	$sp, $sp, -48

	# load data and save (t have 8 rigister)
    li		$t0, 132470
	li 		$t1, 3245453
	li 		$t2, 73245
	li 		$t3, 93245
    li 		$t4, 80324542
	li 		$t5, 244
	li 		$t6, 2
	li 		$t7, 66
    sw 		$t0, 0($sp)
	sw 		$t1, 4($sp)
	sw 		$t2, 8($sp)
	sw 		$t3, 12($sp)
    sw 		$t4, 16($sp)
	sw 		$t5, 20($sp)
	sw 		$t6, 24($sp)
	sw 		$t7, 28($sp)
    li 		$t0, 236
	li		$t1, 327
	li 		$t2, 236
	li 		$t3, 21544
    sw 		$t0, 32($sp)
	sw 		$t1, 36($sp)
	sw 		$t2, 40($sp)
	sw 		$t3, 44($sp)

	move 	$t0, $sp			# $t0 = sp
	li 		$t1, 12 			# t1 = 12

	addiu 	$sp, $sp, -8
	sw 		$t0, 0($sp) 		# store n 
	sw 		$t1, 4($sp) 		# store address of data[0]

	jal 	printArray

	jal 	insertionSortRecursive

	jal 	printArray

end:
    li 		$v0, 10 			# return 0
    syscall


insertionSortRecursive:
	addiu 	$sp, $sp, -8
	sw 		$ra, 4($sp) 		# store address of $ra
	sw 		$fp, 0($sp) 		# store address of $fp
	move 	$fp ,$sp
	
	lw 		$s0, 12($fp) 		# load n
	lw 		$s1, 8($fp) 		# load address of data[0]
	

	condition_if_else:
		li 	$s2, 1 				# set s2 = 1
		slt $s3, $s2, $s0 		# set $s3 = 1 if n > 1 else 0
		bne $s3, $zero, else 	# if n <= 1 goto else 
	if:
		lw 	$ra, 4($sp) 		# load address of $ra 
		lw 	$fp, 0($sp) 		# load address of $fp
		addiu $sp, $sp, 8
		jr 	$ra

	else:
		addiu $s0, $s0, -1 		# n = n - 1
	
		addiu $sp, $sp, -8 		# create empty new stack
		
		sw 	$s0, 4($sp) 			# stack n-1 to arr[1]
		sw $s1, 0($sp) 			# stack arr to arr[2]
		
		jal insertionSortRecursive # recustion inserctionSort(arr,n-1)
		
		lw $s0, 4($sp) 			# load n-1
		lw $s1, 0($sp) 			# load address of arr[0]
		addiu $sp, $sp, 8
		
		sll $s2, $s0, 2 		# convert (n-1) to word offset
		addu $s2, $s2, $s1 		# ptr = offset
		lw $s3, 0($s2) 			# load arr[prt]
		
		addiu $s4, $s0, -1 		# $s4 = n-2 (n-1-1 = n-2)


	whileLoop:
		# We have to load arr[j] first (for condition)
		sll $s2, $s4, 2 		# convert j to word offset
		addu $s2, $s2, $s1 		# ptr = offset
		lw $s5, 0($s2) 			# load arr[offset]
		
		slt $s6, $s4, $zero 	# if j < 0 set s6 = 1 else s6 = 0
		not $s6, $s6 			# change j < 0 to j >= 0
		slt $s7, $s3, $s5 		# if arr[j] > last set s7 = 1 else s7 = 0
		
		and $s7, $s6, $s7 		# j >= 0 and arr[j] > last
		beq $s7, $zero, exitInsertionSortRecursive

		addi $s6, $s4, 1 		# j = j + 1
		sll $s6, $s6, 2 		# convert j to word offset
		addu $s6, $s6, $s1 		# ptr = offset
		sw $s5, 0($s6) 			# store arr[offset]
		
		addi $s4, $s4, -1 		# j = j - 1
		j whileLoop
		
	exitInsertionSortRecursive:
		
		addi $s6, $s4, 1 		# j = j + 1
		sll $s6, $s6, 2 		# convert j to word offset
		addu $s6, $s6, $s1 		# ptr = offset
		sw $s3, 0($s6) 			# arr[j+1] = last
		
		lw $ra, 4($sp) 			# load address of $ra 
		lw $fp, 0($sp) 			# load address of $fp
		addiu $sp, $sp 8
		jr $ra 					# return


printArray:
	addiu $sp, $sp, -8
	sw $ra, 4($sp) 				# store address of $ra
	sw $fp, 0($sp) 				# store address of $fp
	move $fp, $sp
	
	lw $s0 12($fp) 				# load n
	lw $s1 8($fp) 				# load address of data[0]
	
	initLoop:
		add $s2, $zero, $zero 	# i = 0
	conditionLoop:
		slt $s3, $s2, $s0 		# if i < n set s3 = 1 else s3 = 0
		beq $s3, $zero, exitPrintArray # if i >= n goto exitPrintArray
	codeBlockLoop:
		sll $s4, $s2, 2 		# convert j to word offset
		addu $s4, $s4, $s1 		# ptr = offset
		lw $s5, 0($s4) 			# load arr[ptr]

		li $v0, 1 				# print int
		move $a0, $s5 			# printf("%d",arr[i]);
		syscall 
		
		li $v0, 4 				# print string
		la $a0, space 			# printf(" ");
		syscall
	incrementLoop:
		addi $s2, $s2, 1 		# i = i + 1
		j conditionLoop 		# jump to conditionLoop
		
	exitPrintArray:

		li $v0, 4 				# print string
		la $a0, endl 			# printf("\n")
		syscall
		
		lw $ra, 4($sp) 			# store address of $ra
		lw $fp, 0($sp) 			# store address of $fp
		addiu $sp, $sp 8
		
		jr $ra 					# jump to return
		
		
		
		
		