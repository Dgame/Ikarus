assign &0, 8
print &0
push &0
push 3
call Lpow
pop &0
print &0
exit

Lpow:
    pop &2
    pop &1

    assign &3, &1

    L1:
        is_lower &2, 2
        goto_if L2
        mul &3, &1
        pop &3
        dec &2
        pop &2
        goto L1
    L2:
        push &3
        return