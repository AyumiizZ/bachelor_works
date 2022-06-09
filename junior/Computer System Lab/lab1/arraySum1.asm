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
    add $t1, $0, $0

loop1:
    sll $t2, $t1, 2
    lw $t2, array_a($t2)
    add $t0, $t0, $t2
    addi $t1, $t1, 1
    slti $t2,$t1, 20
    bne $t2, $0, loop1

    li $v0, 4
    la $a0, sumAData
    syscall
    
    li $v0, 1
    move $a0, $t0
    syscall

    li $v0, 4
    la $a0, newLine
    syscall

    add $t0, $0, $0
    add $t1, $0, $0

loop2:
    sll $t2, $t1, 2
    lw $t2, array_b($t2)
    addu $t0, $t0, $t2
    addi $t1, $t1, 1
    slti $t2,$t1, 20
    bne $t2, $0, loop2

    li $v0, 4
    la $a0, sumBData
    syscall
    
    li $v0, 1
    move $a0, $t0
    syscall

    li $v0, 4
    la $a0, newLine
    syscall

end:
    li $v0, 10
    syscall