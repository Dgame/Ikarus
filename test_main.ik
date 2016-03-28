assign &0, 42
print &0

assign &1, 23
print &1

add 1, 2
pop &2
print &2

mul 2, 3
add ~0, 4
pop &3
print &3

append &4, 1
append &4, 2
append &4, 3
print &4

add &0, &1
pop &5
print &5

fetch &4, 0
assign &6, ~1
print &6

assign &4, 1337
print &4

assign &7, 1
print &7

is_lower 2, 3
pop &8
print &8

is_lower 2012, &4
pop &9
print &9