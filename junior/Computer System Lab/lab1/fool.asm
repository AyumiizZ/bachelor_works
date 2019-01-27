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
    # set $t0 = i
initLoop1:
    add $t0, $zero , $zero # i = 0
Loop1:
    slt $t4, $s0, $t0  # if RANGE < i set $t4 = 1 else $t4 = 0
    bne $t4, $zero, initLoop2 # if RANGE < i goto initLoop2
    sb	$zero, count($t0)	# store 0 to 
    addi $t0, $t0, 1 # i = i + 1
    j Loop1 # jump to Loop1

initLoop2:
    add $t0, $zero , $zero # i = 0
Loop2:
    lb $t1, str($t0) # $t1 = str[i]
    beq $t1, $zero, initLoop3 # if str[i] == 0 goto initLoop3
    lb $t2, count($t1) # $t2 = count[str[i]]
    addi $t2, $t2, 1 # $t2 = 1
    sb $t2, count($t1) # count[str[i]] = $t2
    addi $t0, $t0, 1 # i = i + 1
    j Loop2 # jump to Loop2

initLoop3:
    addi $t0, $zero , 1 # i = 1
Loop3:
    slt $t4, $s0, $t0  # if RANGE < i set $t4 = 1 else $t4 = 0
    bne $t4, $zero, initLoop4 # if RANGE < i goto initLoop4
    addi $t1, $t0, -1 # $t1 = $t0 - 1
    lb $t2, count($t0) # $t2 = count[t0]
    lb $t3, count($t1) # $t3 = count[t1]
    add $t2, $t2, $t3 # count[t0] = count[t0] + count[t1]
    sb $t2, count($t0) # count[t0] = $t2
    addi $t0, $t0, 1 # i = i + 1
    j Loop3 # jump to Loop3

initLoop4:
    add $t0, $zero , $zero # i = 0
Loop4:
    lb $t1, str($t0) # $t1 = str[i]
    beq $t1, $zero, initLoop5 # if str[i] == 0 goto initLoop5
    lb $t1, str($t0) # $t1 = set[t0]
    lb $t2, count($t1) # $t2 = count[t1]
    addi $t3, $t2, -1 # $t3 = $t2 - 1
    sb $t1, output($t3) # output[t3] = $t1
    addi $t2, $t2, -1 # $t2 = $t2 - 1
    sb $t2, count($t1) # count[t1] = $t2
    addi $t0, $t0, 1 # i = i + 1
    j Loop4 # jump to Loop4

initLoop5:
    add $t0, $zero , $zero # i = 0
Loop5:
    lb $t1, str($t0) # $t1 = str[i]
    beq $t1, $zero, printRes # if str[i] == 0 goto printRes
    lb $t1, output($t0) # $t1 = output[t0]
    sb $t1, str($t0) # str[t0] = t1
    addi $t0, $t0, 1 # i = i + 1
    j Loop5 # jump to Loop5

printRes:
    li $v0, 4
    la $a0, outputstr
    syscall

    li $v0, 4
    la $a0, str
    syscall

    li $v0, 4
    la $a0, endl
    syscall

end:
    li $v0, 10
    syscall
