
.data
label: .dword 12,10,125,50,32,16

.text

la x3, label

li x2, 0x100000100

initial:

ld t3, 0(x3)
ld t4, 8(x3)
addi x3,x3,16

add a0 ,x0,x0
beq x0, t3, l3
beq x0, t4, l3

jal x1, GCD

l3:
sd a0, 0(x2)
addi x2, x2,8
beq x0,x0 ,initial

GCD:  
#t3 and t4 contain the values
l1:
beq t3, t4, exit

blt t3, t4, l2

sub t3,t3,t4
beq x0,x0, l1

l2:
    sub t4,t4,t3
    beq x0,x0, l1

exit:
    add a0, x0,t4  #preserving the return value
    jalr x0, x1, 0


