.data

.text

.globl main

main:
    li $t0, 999

    addi $sp, $sp, -4
    sw $t0, 0($sp)                  # store n
    jal numDigits
    add $s0, $zero, $v0
    addi $sp, $sp, 4

    li $v0, 1
    move $a0, $s0
    syscall

end:
    li      $v0, 10                 # return 0
    syscall

numDigits:
    addi    $sp, $sp, -8            # decrease stack pointer
    sw      $fp, 0($sp)
    sw      $ra, 4($sp)
    move    $fp, $sp
    lw      $t0, 8($fp)             # n

    slti    $t1, $t0, 10            # if t0 < 10 set $t1 = 1 else $t1 = 0
    bne		$t1, $zero, exitRecur	# if $t1 != 0 ($t0 >= 10) then exitRecur

    recur:
        # return numDigits(n/10)
        addi    $sp, $sp, -8        # decrease stack pointer
        sw      $t0, 4($sp)         # push n to stack
        li      $t2, 10
        div		$t0, $t2			# $t0 / $t2
        mflo    $t3
        sw      $t3, 0($sp)         # store n/10
        jal     numDigits
        addi    $sp, $sp, 8         # increase stack pointer
        lw      $fp, 0($sp)
        lw      $ra, 4($sp)
        addi    $sp, $sp, 8         # increase stack pointer
        addi    $v0, $v0, 1
        jr      $ra                 # jump to return

    exitRecur:
        # return m
        lw      $ra, 4($fp)
        lw      $fp, 0($fp)
        addi    $sp, $sp, 8         # increase stack pointer
        li      $v0, 1		        # $v0 = 1 (set return 1)
        jr      $ra                 # jump to return

     

# if(n < 10) return 1
# return 1 + numDigits(n/10)
