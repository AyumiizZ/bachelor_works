.data
    outputstr: .asciiz "gcd of 1890 and 3315 is "
    endl: .asciiz "\n"
    m: .word 1890
    n: .word 3315

.text

.globl main

main:
    lw      $t0, m($zero)           # load m to t0
    lw      $t1, n($zero)           # load n to t1
    
    li      $v0, 4                  # print string
    la      $a0, outputstr          # printf("gcd of 1890 and 3315 is ");
    syscall

    # call gcd
    addi    $sp, $sp, -8            # decrease stack pointer
    sw      $t0, 0($sp)             # push m to stack
    sw      $t1, 4($sp)             # push n to stack
    jal     gcd                     # jumptore n to jal
    add     $s0, $0, $v0            # get return value to s0
    addi    $sp, $sp, 8             # increase stack pointer

    li      $v0, 1                  # print integer
    move    $a0, $s0                # print return value from gcd function
    syscall

    li      $v0, 4                  # print string
    la      $a0, endl               # printf("\n");
    syscall

end:
    li      $v0, 10                 # return 0
    syscall

gcd:
    addi    $sp, $sp, -8            # decrease stack pointer
    sw      $fp, 0($sp)
    sw      $ra, 4($sp)
    move    $fp, $sp
    lw      $t0, 12($fp)            # m 
    lw      $t1, 8($fp)             # n

    beq     $t0, $t1, exitRecur     # if m == n return m
    
    slt     $t2, $t1, $t0           # if n < m set t2 = 1 else set t2 = 0
    bne     $t2, $zero, recur1      # if n < m (t2 != 0) return gcd(m-n,n)
    
    # else return gcd(m,n-m)
    recur2:
        # return gcd(m,n-m)
        addi    $sp, $sp, -8        # decrease stack pointer
        sw      $t0, 4($sp)         # push m to stack
        sub     $t1, $t1, $t0       # n = n - m
        sw      $t1, 0($sp)         # push n to stack
        jal     gcd                 # jump to gcd
        addi    $sp, $sp, 8         # increase stack pointer
        lw      $fp, 0($sp)
        lw      $ra, 4($sp)
        addi    $sp, $sp, 8         # increase stack pointer
        jr      $ra                 # jump to return
        

    recur1:
        # return gcd(m-n,n)
        addi    $sp, $sp, -8        # decrease stack pointer
        sub	    $t0, $t0, $t1       # set m = m - n
        sw      $t0, 4($sp)         # push m to stack
        sw      $t1, 0($sp)         # push n to stack
        jal     gcd                 # jump to gcd
        addi    $sp, $sp, 8         # increase stack pointer
        lw      $fp, 0($sp)         
        lw      $ra, 4($sp)
        addi    $sp, $sp, 8         # increase stack pointer
        jr      $ra                 # jump to return

    exitRecur:
        # return m
        lw      $ra, 4($fp)
        lw      $fp, 0($fp)
        addi    $sp, $sp, 8         # increase stack pointer
        move    $v0, $t0		    # $v0 = $t0 (set return = m)
        jr      $ra                 # jump to return

