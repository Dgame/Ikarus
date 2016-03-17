assign &0, 8
assign &1, 1
L1:
    is_lower &0, 2
    goto_if L2
    mul &1, &0
    pop &1
    dec &0
    pop &0
    goto L1
L2:
    print &1

exit
