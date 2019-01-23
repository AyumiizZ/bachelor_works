.data
    newLine:   .asciiz "\n"
    sumAData: .asciiz "Sum a = "
    sumBData: .asciiz "Sum b = "
    sum: .space 4
    array_a: .word 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20
    array_b: .word 0x7fffffff, 0x7ffffffe, 0x7ffffffd, 0x7ffffffc, 0x7ffffffb, 0x7ffffffa, 0x7ffffff9, 0x7ffffff8, 0x7ffffff7, 0x7ffffff6

.text

.globl main

main:
    add $t0, $0, $0
    addi $t1, $0, 20 
    lw $t2, array_a($0)
    add $t3, $0, $0
loop1:  
    sll $t10, $t0, 2
    lw $t4, $t0($t2)
    add $t3, $t3, $t4
    addi $t0, $t0, 1
    slt $t5, $t0, $t1
    bne $t5, $0, loop1

printA:
    li $v0, 4
    la $a0, sumAData
    syscall

    li $v0, 1
    move $a0, $t3
    syscall

    li $v0, 4
    la $a0, newLine
    syscall

# and $t0, $0, $0

# loop2:

end:
    li $v0, 10
    syscall