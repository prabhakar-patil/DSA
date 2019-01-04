# parameter offses on stack w.r.t. esp reg while calling any function
.equ p1, 0
.equ p2, 4
.equ p3, 8
.equ p4, 12

# local storage offsets on stack w.r.t. ebp reg while accessing local variables within function
.equ loc1, -4
.equ loc2, -8
.equ loc3, -12

# arguments received to functions, their offsets w.r.t. ebp reg 
.equ arg1, 8
.equ arg2, 12
.equ arg3, 16

# constants
.equ EXIT_SUCCESS, 0
.equ EXIT_FAILURE, -1

.equ CAP, 1000

.section .rodata
	msg1:
		.string "A[%d]=%d\n"
	msg2:	
		.string "A=0x%x A[%d]=%d\n"

	err1:
		.string "calloc() failed. Cannot allocate memory\n"
	err2:
		.string "x_free(): cannot free null pointer\n"

	success_msg:
		.string	"SUCCESS\n"
	failure_msg:
		.string	"FAILURE\n"

.section .text 
	.globl 	main
	.type 	main, @function
# main(int argc, char *argv[])
# 12(%ebp)= argv[1]
# 8(%ebp) = argv[0]
# 4(%ebp) = argc
main:
	#pro-logue
	pushl 	%ebp		# push ebp reg value to current stack pointer position
	movl	%esp, %ebp	# ebp = esp(current stack pointer)
	
	#align esp to 16 byte and create local storage of 16 byte
	andl	$-16, %esp	# align esp to 16 byte boundary, -16D = 0xFFFF FFF0
	subl	$16,  %esp
	
	# int N = atoi(argv[1])
	movl	12(%ebp), %eax	# eax=arg[1] 
	movl	%eax, p1(%esp)
	call	atoi
	movl 	%eax, loc1(%ebp) # N = atoi(argv[1])
	 
	# A = (int*) x_calloc(N, sizeof(int))
	movl	loc1(%ebp), %eax # eax = N
	movl	%eax, p1(%esp)	 
	movl	$4, p2(%esp)	 # sizeof(int) as 2nd argument
	call	x_calloc
	movl	%eax, loc2(%ebp) # A = eax, Base array address in local stack storage
	
	# input(A, N)
	movl	loc2(%ebp), %eax	# eax = Base address of A
	movl	%eax, p1(%esp)
	movl	loc1(%ebp), %eax	# eax = N
	movl	%eax, p2(%esp)
	call	input

	# sort(A, N)
	movl	loc2(%ebp), %eax	# eax = Base address of A
	movl	%eax, p1(%esp)		# 1st parameter to sort() function
	movl	loc1(%ebp), %eax	# eax = N
	movl	%eax, p2(%esp)		# 2nd parameter to sort() function
	call	sort


	# output(A,N)
	movl	loc2(%ebp), %eax	# eax = Base address of A
	movl	%eax, p1(%esp)
	movl	loc1(%ebp), %edx	# edx = N
	movl	%edx, p2(%esp)
	call	output	

	# test_sort(A,N)
	movl	loc2(%ebp), %eax	# eax = Base address of A
	movl	%eax, p1(%esp)		# 1st para to stack
	movl	loc1(%ebp), %eax	# eax = N
	movl	%eax, p2(%esp)		# 2nd para to stack
	call	test_sort

	# x_free(A)
	movl	loc2(%ebp), %eax
	movl	%eax, p1(%esp)
	call	x_free

	#exit(EXIT_SUCCESS)
	movl	$EXIT_SUCCESS, p1(%esp)
	call 	exit

.section .text
	.globl	sort
	.type	sort, @function

# void sort(int *A, int N)
sort:
	pushl	%ebp		# save previous function ebp, when return from this function, will restore it
	movl	%esp, %ebp	# equate curret stack top to ebp

	andl	$-16, %esp	# align stack pointer to 16 byte boundary
	subl	$16, %esp	# Allocate 16 byte stack storage for this function
	
	# insertion sort functionality
	# i(local1), j(local2), key(local3)

	# for(j=1; j<N, j++)
	# j = 1
	movl	$1, loc2(%ebp)
	movl	arg1(%ebp), %ebx	# ebx = base address of Array = A, So dont use ebx other than base address for next calc
	jmp	sort_for_cond
sort_for:
	# key = A[j]
	movl	loc2(%ebp), %ecx	# ecx = j
	movl	(%ebx, %ecx, 4), %eax	# eax = ebx + ecx*4 = A[j]
	movl	%eax, loc3(%ebp)	# key = eax = A[j]
	# i = j - 1
	subl	$1, %ecx		# ecx = ecx - 1
	movl	%ecx, loc1(%ebp)	# i = ecx

	# while(i>-1 && A[i]>key)
	jmp	sort_inner_while_cond
	movl	arg1(%ebp), %ebx	# ebx = Base addres of A
	movl	loc1(%ebp), %ecx 	# ecx = i
	sort_inner_while:
		# A[i+1] = A[i]
		movl	(%ebx, %ecx, 4), %eax 	# eax = A[i]
		movl	%ecx, %edx		# edx = ecx = i
		addl	$1, %edx		# edx = i + 1
		movl	%eax, (%ebx, %edx, 4)	# A[i+1] = eax = A[i]

		# i = i - 1
		subl	$1, %ecx

	sort_inner_while_cond:
		# while(i>-1 && A[i]>key)
		cmpl	$-1, %ecx		# i - (-1) > +ve(continue loop) or -ve/0(break loop)
		jng	inner_break_loop
		movl	(%ebx, %ecx, 4), %eax	# (ebx + ecx*4) --> eax, eax = A[i]
		cmpl	%eax, loc3(%ebp)	# key - A[i] ? -ve(continue loop), +ve/0(break loop)
		jl	sort_inner_while	# if key < A[i] --> continue loop
	inner_break_loop:
		# A[i+1] = key
		movl	loc3(%ebp), %eax	# eax = key
		addl	$1, %ecx		# ecx = ecx + 1 = i + 1
		movl	%eax, (%ebx, %ecx, 4)	# A[i+1] = key	
		
	addl 	$1, loc2(%ebp)			# j = j + 1

sort_for_cond:
	movl	loc2(%ebp), %eax	# eax = j
	movl	arg2(%ebp), %ecx	# ecx = N
	cmpl	%ecx, %eax	# j - N ? -ve(loop continue) or +ve(terminate loop)
	jl	sort_for

	movl	%ebp, %esp	# discard current function stack, now esp will point to ebp. 
				# Its like retriving exactly same state of stack pointer when we entered this fuction
	popl	%ebp		# get previous funtion (caller of this function) ebp 
	ret

.section .rodata
	str1:
		.string	"A[%d]=%d, A[%d]=%d\n"

.section .text
	.globl 	test_sort
	.type	test_sort, @function
# void test_sort(int *A, int N)

test_sort:
	pushl	%ebp		# store caller ebp
	movl	%esp, %ebp	# bring ebp to current stack top

	andl	$-16, %esp	# align stack pointer to 16 byte boundary
	subl	$16, %esp	# allocate 16 byte local/stack storage

	# int i = 0
	movl	$0, loc1(%ebp)

	# ebx = Base address of A
	movl	arg1(%ebp), %ebx	# dont use ebx for other use

	# for(i=0; i<N-1; i++)
	jmp	test_sort_for_cond
test_sort_for:
	# if (A[i] > A[i+1])
	# 	break;
	movl	loc1(%ebp), %eax	# eax = i
	movl	(%ebx, %eax, 4), %edx	# edx = A[i]

	addl	$1, %eax		# eax = i+1

	cmpl	%edx, (%ebx, %eax, 4)	# A[i+1] - A[i] ? -ve(break the loop, +ve/0(continue loop)
	jl	test_sort_failure
	addl	$1, loc1(%ebp)		# i = i+1

test_sort_for_cond:
	movl	arg2(%ebp), %edx	# edx = N
	subl	$1, %edx		# edx = N - 1
	cmpl	%edx, loc1(%ebp)	# i - (N-1) ? -ve(less, continue loop), +ve(break loop)
	jl	test_sort_for
	jmp	test_sort_success

test_sort_failure:
	# printf("FAILURE\n")
	movl	$failure_msg, p1(%esp)
	jmp	test_sort_print

test_sort_success:
	# printf("SUCCESS\n")
	movl	$success_msg, p1(%esp)

test_sort_print:
	call	printf

	movl	%ebp, %esp	# discard current function stack
	popl	%ebp		# retrieve caller ebp
	ret


.section .text
	.globl	input
	.type	input, @function
# intput(int *A, int N)
input:
	pushl	%ebp
	movl	%esp, %ebp

	andl	$-16, %esp
	subl	$16,  %esp	#16bytes local storage on stack

	# eax = time(0)
	movl	$0, p1(%esp)
	call	time
	# srand(time(0))
	movl	%eax, p1(%esp)
	call	srand
	
	# int i = 0
	movl	$0, loc1(%ebp)
	jmp	input_cond
input_for:
	# A[i]=rand()
	call 	rand
	movl	loc1(%ebp), %ecx	# ecx = i
	movl	arg1(%ebp), %ebx	# ebx = Base Address of A
	movl	%eax, (%ebx, %ecx, 4)	# A[i] = eax = rand()

	# debug
	#movl	$msg1, p1(%esp)
	#movl	%ecx, p2(%esp)
	#movl	%eax, p3(%esp)
	#call printf

	# i = i + 1
	addl	$1, loc1(%ebp)

input_cond:
	movl	loc1(%ebp), %eax	# eax = i
	cmpl	arg2(%ebp), %eax	# arg2(%ebp)=N, eax=i
	jl	input_for		# eax-edx = i - N = -ve , jump if less	

	#Epilogue
	movl	%ebp, %esp		# jump esp to ebp location, discard this function stack
	popl	%ebp			# retriev previous ebp
	ret

	
.section .text
	.globl 	output
	.type 	output, @function

#void output(*A,N)
output:
	# Prologue
	pushl 	%ebp		# save previous ebp reg value to current stack position
	movl	%esp, %ebp	# bring ebp to esp. Here ebp will work as pivote to access function parameters and local stack

	andl	$-16, %esp	# align esp to 16 byte boundary
	subl	$16, %esp	# 16 byte local storage
	
	# int i=0
	movl	$0, loc1(%ebp)
	jmp	output_cond
output_for:
	movl	loc1(%ebp), %ecx	# ecx = i
	movl	arg1(%ebp), %ebx	# ebx = Base address of A
	movl	(%ebx, %ecx, 4), %eax   # eax = A[i]

	#print("A=0x%x [%d]=%d",A, i, A[i])
	movl	$msg2, p1(%esp)
	leal	(%ebx, %ecx, 4), %edx
	movl	%edx, p2(%esp)	
	movl	%ecx, p3(%esp)		
	movl	%eax, p4(%esp)
	call	printf	
	
	# i = i + 1
	addl	$1, loc1(%ebp)
output_cond:
	movl	loc1(%ebp), %eax	# eax = i
	cmpl	arg2(%ebp), %eax	# N - i > ? 
	jl	output_for
	
	# Epilogue
	movl	%ebp, %esp	# Discard current function stack by jumping to stack position when entered to this function
	popl	%ebp		# Retrive previous function ebp

	ret

.section .text
	.globl	x_calloc
	.type	x_calloc, @function

# void *x_calloc(int nr_elements, int size_per_element)
x_calloc:
	# Prologue
	pushl	%ebp		# save previous function ebp
	movl	%esp, %ebp	# copy currect stack position to ebp, as a pivote

	andl	$-16, %esp	# align esp to 16byte boundary
	subl	$16, %esp	# allocate 16 byte local stack storage

	# void *tmp = calloc(nr_elements, size_per_elements)
	movl	arg1(%ebp), %eax 	# eax = nr_elements
	movl	%eax, p1(%esp)		# calloc 1st parameter pushed to stack
	movl	arg2(%ebp), %eax	# eax = size_per_elements
	movl	%eax, p2(%esp)		# calloc 2nd parameter pushed to stack
	call	calloc	
	
	cmpl	$0, %eax
	jne	x_calloc_next
	movl	$err1, p1(%esp)
	call	printf	

x_calloc_next:
	# now %eax has returned addess from calloc, which we can return
	movl	%ebp, %esp	# Discard current function stack
	popl	%ebp		# retrive previous function ebp, pivot pos
	ret

.section .text
	.globl	x_free
	.type	x_free, @function

# void x_free(void *ptr)
x_free:
	pushl	%ebp		# save prevous function ebp
	movl	%esp, %ebp	# ebp will point to same stack address where esp is pointing

	andl	$-16, %esp	# esp aligned to 16 byte boundary
	subl	$16, %esp	# create local storage of 16 byte
	
	# if(A)
	#  free(A)
	movl	arg1(%ebp), %eax
	cmpl	$0, %eax
	je	x_free_err
	movl	%eax, p1(%esp)
	call	free
	jmp	x_free_out

x_free_err:
	movl	$err2, p1(%esp)
	call 	printf

x_free_out:
	movl	%ebp, %esp	# Discard current function stack
	popl	%ebp		# Retrive previous function base pointer address
	ret
