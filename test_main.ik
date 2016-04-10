assign &0, 42
assign &1, 23
add 1, 2
pop &2
mul 2, 3
add ~0, 4
pop &3
append &4, 1
append &4, 2
append &4, 3
add &0, &1
pop &5
fetch &4, 0
assign &6, ~1
assign &4, 1337
assign &7, 1
is_lower 2, 3
pop &8
is_lower_or_equal 2012, &4
pop &9
assign &10, 2
assign &11, 3
L0_1:
    is_lower_or_equal &11, 1
    goto_if L0_2
        dec &11
        pop &11
        mul &10, 2
        pop &10
    goto L0_1
L0_2:
print &11
print &10