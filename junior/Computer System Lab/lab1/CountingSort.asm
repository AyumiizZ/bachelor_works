.data
    RANGE: .word 255
    str: .asciiz "cadljgarhtoxAHdgdsJKhYEasduwBRLsdgHoptxnaseurh"
    outputstr: .asciiz "Sorted string is "
    endl: .asciiz "\n"
    output: .byte 0:1000
    count: .byte 0:256

.text

.globl main

main:
    lw $s0, RANGE($zero) # $s0 = 255

InitLoop1:
    add $t0, $zero , $zero # i = 0
ConditionLoop1:
    slt $t4, $s0, $t0  # if RANGE < i set $t4 = 1 else $t4 = 0
    bne $t4, $zero, InitLoop2 # if RANGE < i goto InitLoop2
CodeBlockLoop1:
    sb	$zero, count($t0)	# store 0 to 
IncrementLoop1:
    addi $t0, $t0, 1 # i = i + 1
    j ConditionLoop1 # jump to ConditionLoop1

InitLoop2:
    add $t0, $zero , $zero # i = 0
ConditionLoop2:
    lb $t1, str($t0) # $t1 = str[i]
    beq $t1, $zero, InitLoop3 # if str[i] == 0 goto InitLoop3
CodeBlockLoop2:
    lb $t2, count($t1) # $t2 = count[str[i]]
    addi $t2, $t2, 1 # $t2 = 1
    sb $t2, count($t1) # count[str[i]] = $t2
IncrementLoop2:
    addi $t0, $t0, 1 # i = i + 1
    j ConditionLoop2 # jump to ConditionLoop2

InitLoop3:
    addi $t0, $zero , 1 # i = 1
ConditionLoop3:
    slt $t4, $s0, $t0  # if RANGE < i set $t4 = 1 else $t4 = 0
    bne $t4, $zero, InitLoop4 # if RANGE < i goto InitLoop4
CodeBlockLoop3:
    addi $t1, $t0, -1 # $t1 = $t0 - 1
    lb $t2, count($t0) # $t2 = count[t0]
    lb $t3, count($t1) # $t3 = count[t1]
    add $t2, $t2, $t3 # count[t0] = count[t0] + count[t1]
    sb $t2, count($t0) # count[t0] = $t2
IncrementLoop3:
    addi $t0, $t0, 1 # i = i + 1
    j ConditionLoop3 # jump to ConditionLoop3

InitLoop4:
    add $t0, $zero , $zero # i = 0
ConditionLoop4:
    lb $t1, str($t0) # $t1 = str[i]
    beq $t1, $zero, InitLoop5 # if str[i] == 0 goto InitLoop5
CodeBlockLoop4:
    lb $t1, str($t0) # $t1 = set[t0]
    lb $t2, count($t1) # $t2 = count[t1]
    addi $t3, $t2, -1 # $t3 = $t2 - 1
    sb $t1, output($t3) # output[t3] = $t1
    addi $t2, $t2, -1 # $t2 = $t2 - 1
    sb $t2, count($t1) # count[t1] = $t2
IncrementLoop4:
    addi $t0, $t0, 1 # i = i + 1
    j ConditionLoop4 # jump to ConditionLoop4

InitLoop5:
    add $t0, $zero , $zero # i = 0
ConditionLoop5:
    lb $t1, str($t0) # $t1 = str[i]
    beq $t1, $zero, printRes # if str[i] == 0 goto printRes
CodeBlockLoop5:
    lb $t1, output($t0) # $t1 = output[t0]
    sb $t1, str($t0) # str[t0] = t1
IncrementLoop5:
    addi $t0, $t0, 1 # i = i + 1
    j ConditionLoop5 # jump to ConditionLoop5

printRes:
    li $v0, 4 # print string
    la $a0, outputstr # printf("Sorted string is ");
    syscall

    li $v0, 4 # print string
    la $a0, str # printf("%s",str);
    syscall

    li $v0, 4 # print string
    la $a0, endl # printf("\n");
    syscall

end:
    li $v0, 10 # return 0
    syscall
