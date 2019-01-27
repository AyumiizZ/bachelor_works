.data
    newLine: .asciiz "\n"
    
    str: 	.byte 'c', 'a', 'd', 'l', 'j', 'g' ,'a', 'r', 'h', 't', 'o', 'x', 'A', 'H', 'd'
            .byte 'g', 'd', 's', 'J', 'K', 'h', 'Y', 'E', 'a', 's', 'd', 'u', 'w', 'B', 'R'
            .byte 'L', 's', 'd', 'g', 'H', 'o', 'p', 't', 'x', 'n', 'a', 's', 'e', 'u', 'r', 'h'
    # blank: .space 4
    outputstr: .asciiz "Sorted string is "
    output: .space 1000
    range: .word 255
    count: .space 1000

.text

.globl main

main:
    add $t0, $0, $0
    add $t1, $0, $0
loop:
    sll $t2, $t1, 2

    li $v0, 4
    lb $t2, str($t2)
    syscall

    addi $t1, $t1, 1
    slti $t2,$t1, 20
    bne $t2, $0, loop1

end:
    li $v0, 10
    syscall