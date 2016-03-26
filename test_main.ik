assign &0, 42
assign &1, 23
add 1, 2
pop &2
mul 2, 3
add ~0, 4
pop &3

print &0
print &1
print &2
print &3

append &4, 1
append &4, 2
append &4, 3

print &4

set_index 0
emplace &4, 42

print &4

add &0, &1
pop &5

print &5