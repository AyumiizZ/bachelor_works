.data
    a: .space 80

.text

.globl main 

main:
    InitLoop:
        # Register t0 should store the incrementor
        add $t0, $zero , $zero # i = 0
    ConditionLoop:
        li $t1, 20
        slti $t1, $t0, 20  # if t0 < 20 then t1 = 1 else t1 = 0
        beq $t1, $zero, end # if t1 = 0 goto end
    CodeBlockLoop:
        not $t2, $t0 # not $t2 so $t2 % 2 == 1 if $t0 % 2 == 0 else $t2 % 2 == 0
        andi $t2, $t2, 1 # $t2 % 2 = $t2 & 1
        sll $t0, $t0, 2
        sw $t2, a($t0)
        srl $t0, $t0, 2
    IncrementLoop:
        addi $t0, $t0, 1 # i = i + 1
        j ConditionLoop # jump to ConditionLoop       

end:
    li $v0, 10 # return 0
    syscall                                                                        
