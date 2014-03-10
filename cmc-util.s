# this file contains useful methods

.comm buffer,80,32

.text
	dash:
	.string "-"

# function to print an integer
.globl __print_int
__print_int:
movl 4(%esp), %eax
xorl %esi, %esi

pushl %ebp
movl %esp, %ebp
subl $4, %esp	# get some stack space

# handle negative numbers
cmpl $0, %eax
jge loop
neg %eax

movl %eax, -4(%ebp)

movl $4, %eax
movl $1, %ebx
movl $dash, %ecx
movl $1, %edx
int $0x80

movl -4(%ebp), %eax

loop:
movl $0, %edx
movl $10, %ebx
divl %ebx
addl $48, %edx
pushl %edx
incl %esi
cmpl $0, %eax
jz   next
jmp loop

next:
cmpl $0, %esi
jz   exit
decl %esi

movl $4, %eax
movl %esp, %ecx
movl $1, %ebx
movl $1, %edx
int  $0x80

addl $4, %esp

jmp  next
exit:
leave
ret

# --------------------------------------------------------------------

# function to read an integer. the value is returned in %eax
# bugs: doesn't handle negative numbers
.globl __read_int
__read_int:

pushl %ebp
movl %esp, %ebp
subl $4, %esp	# get some stack space

# read input
movl $3, %eax # read code
movl $0, %ebx # stdin's handle is 0
leal buffer, %ecx # address of the input buffer
movl $80, %edx # chars to read
int $0x80

movl %eax, -4(%ebp)	# number of bytes read

# convert to an int
movl -4(%ebp), %ebx # that's the number of bytes read (including the '\n')
subl $2, %ebx		# so we must not count the '\n'. must also go to the last position
movl $1, %ecx		# ecx will contain the number we are multiplying with (1, 10, 100...)
movl $0, %edx		# edx will keep the result

__read_int_0:
cmpl $-1, %ebx
je __read_int_1
movl $0, %eax
movb buffer(%ebx), %al
subl $48, %eax
imul %ecx, %eax
addl %eax, %edx
subl $1, %ebx	# decrement counter
imul $10, %ecx
jmp __read_int_0
__read_int_1:

movl %edx, %eax # copy the result to %eax

leave
ret
