assign &0, 8
print &0
push &0
push 2
call Lpow
pop &0
print &0
exit

Lpow:
    pop &2
    pop &1

    L1:
        is_lower &2, 2
        goto_if Lend
        mul &1, &1
        pop &1
        dec &2
        pop &2
        goto L1
    Lend:
        push &1
        return