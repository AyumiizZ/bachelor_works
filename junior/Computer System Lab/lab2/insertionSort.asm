.data
    N: .word 12
    data: .word 132470, 324545, 73245, 93245, 80324542, 244, 2, 66, 236, 327, 236, 21544
    temp: .word 1, 2, 3, 4, 5
    space: .asciiz " "
    endl: .asciiz "\n"

.text

.globl main

main:
    lw $t0, data
    lw $t1, N

    # call printArray
    addi    $sp, $sp, -8            # decrease stack pointer
    sw      $t1, 0($sp)             # push data to stack
    sw      $t0, 4($sp)             # push N to stack
    jal     printArray              # jump to printArray
    add     $s0, $0, $v0            # get return value to s0
    addi    $sp, $sp, 8             # increase stack pointer

end:
    li $v0, 10 # return 0
    syscall
    

printArray:
    addi    $sp, $sp, -8            # decrease stack pointer
    sw      $fp, 0($sp)
    sw      $ra, 4($sp)
    move    $fp, $sp
    lw      $t0, data               # arg 1 (data)
    lw      $t1, 8($fp)             # arg 2 (N)

    InitLoop:
        add $t2, $zero, $zero      # i = 0
    ConditionLoop:
        slt $t3, $t2, $t1           # if RANGE < i set $t3 = 1 else $t3 = 0
        beq $t3, $zero, endPrint    # if RANGE >= i goto endPrint
    CodeBlockLoop:
        move $t4, $t0($t2)
        # lw $t4, $t0            # lw arr[i]
        li $v0, 1                   # print integer
        move $a0, $t4               # printf("%d",arr[i]);
        syscall

        li $v0, 4                   # print string
        la $a0, space               # printf(" ");
        syscall
    IncrementLoop:
        addi $t2, $t2, 1            # i = i + 1
        j ConditionLoop             # jump to ConditionLoop5

    endPrint:
        li $v0, 4                   # print string
        la $a0, endl                # printf("\n");
        syscall

        lw      $ra, 4($fp)
        lw      $fp, 0($fp)
        addi    $sp, $sp, 8         # increase stack pointer
        jr $ra