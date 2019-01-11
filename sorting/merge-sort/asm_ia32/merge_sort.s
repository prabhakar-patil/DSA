# parameter offses on stack w.r.t. esp reg while calling any function
.equ p1, 0
.equ p2, 4
.equ p3, 8
.equ p4, 12
.equ p5, 16

# local storage offsets on stack w.r.t. ebp reg while accessing local variables within function
.equ loc1, -4
.equ loc2, -8
.equ loc3, -12
.equ loc4, -16
.equ loc5, -20
.equ loc6, -24
.equ loc7, -28
.equ loc8, -32
.equ loc9, -36

# arguments received to functions, their offsets w.r.t. ebp reg 
.equ arg1, 8
.equ arg2, 12
.equ arg3, 16
.equ arg4, 20 

# constants
.equ TRUE, 1
.equ FALSE, 0

.equ EXIT_SUCCESS, 0
.equ EXIT_FAILURE, -1

.equ CAP, 1000000	# <= 1M

.section .rodata
	msg0:
		.string	"Usage: %s <number>\n"
	msg1:
		.string "A[%d]=%d\n"
	msg2:	
		.string "A=0x%x A[%d]=%d\n"

	dbg_msg:
		.string "Value=%d\n"

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
# 4(%ebp) = argc
# 8(%ebp) = argv
# void main(int argc, char *argv[])

main:
	# pro-logue
	pushl	%ebp
	movl	%esp, %ebp	

	andl	$-16, %esp
	subl	$16, %esp
	
	# if(argc == 2)	
	movl	4(%ebp), %eax
	cmpl	$2, %eax
	jne	mn_err_out	

	# N = atoi(argv[1])
	movl	12(%ebp), %eax		# eax = argv[1]
	movl	%eax, p1(%esp)
	call	atoi
	movl	%eax, loc1(%ebp)
	
	# int *A = (int*)x_calloc(N, sizeof(int))
	movl	%eax, p1(%esp)
	movl	$4, p2(%esp)
	call 	x_calloc
	movl	%eax, loc2(%ebp)
	
	# input(A, N)
	movl	loc2(%ebp), %eax
	movl	%eax, p1(%esp)
	movl	loc1(%ebp), %eax
	movl	%eax, p2(%esp)
	call	input
	
	# sort(A, N)
	movl	loc2(%ebp), %eax
	movl	%eax, p1(%esp)
	movl	loc1(%ebp), %eax
	movl	%eax, p2(%esp)
	call	sort

	# output(A, N)
	movl	loc2(%ebp), %eax
	movl	%eax, p1(%esp)
	movl	loc1(%ebp), %eax
	movl	%eax, p2(%esp)
	call	output

	# test_sort(A, N)
	movl	loc2(%ebp), %eax
	movl	%eax, p1(%esp)
	movl	loc1(%ebp), %eax
	movl	%eax, p2(%esp)
	call	test_sort

	# x_free(A)
	movl	loc2(%ebp), %eax
	movl	%eax, p1(%esp)
	call	x_free

	# exit()
	movl	$EXIT_SUCCESS, p1(%esp)
	jmp	mn_out
mn_err_out:
	movl	$msg0, p1(%esp)
	movl	8(%ebp), %ebx
	movl	%ebx, p2(%esp)
	call	printf
	movl	$EXIT_FAILURE, p1(%esp)
mn_out:
	call	exit


# void sort(int A[], int N)
.section .text
	.globl	sort
	.type	sort, @function
sort:
	# prologue
	pushl	%ebp
	movl	%esp, %ebp
	
	andl	$-16, %esp
	subl	$16, %esp

	# merge_sort(A, 0, N-1)
	movl	arg1(%ebp), %eax
	movl	%eax, p1(%esp)
	movl	$0, p2(%esp)
	movl	arg2(%ebp), %eax
	subl	$1, %eax
	movl	%eax, p3(%esp)
	call	merge_sort

	# epilogue
	movl	%ebp, %esp
	popl	%ebp
	ret

# void merge_sort(int A[], int p, int r)
.section .text
	.globl	merge_sort
	.type	merge_sort, @function
merge_sort:
	# prologue
	pushl	%ebp
	movl	%esp, %ebp
	
	andl 	$-16, %esp
	subl	$16, %esp

	# if(p<r)
	movl	arg2(%ebp), %ecx	# ecx = p
	movl	arg3(%ebp), %eax	# eax = r
	cmpl	%eax, %ecx		# p - r ? +ve/0 jg
	jge	ms_out

	# q = (r-p)/2 + p
	subl	%ecx, %eax		# eax = r-p
	movl	$2, %ecx		# ecx = 2
	xorl	%edx, %edx		# edx = 0
	divl	%ecx			# eax/2

	movl	arg2(%ebp), %ecx	# ecx = p
	addl	%ecx, %eax		# eax = eax + p = (r-2)/2 + p
	movl	%eax, loc1(%ebp)	# q = eax

	# merge_sort(A, p, q)
	movl	arg1(%ebp), %ebx
	movl	%ebx, p1(%esp)
	movl	arg2(%ebp), %ebx
	movl	%ebx, p2(%esp)
	movl	loc1(%ebp), %eax
	movl	%eax, p3(%esp)	
	call	merge_sort		# recursive call

	# merge_sort(A, q+1, r)
	movl	arg1(%ebp), %ebx
	movl	%ebx, p1(%esp)
	movl	loc1(%ebp), %eax
	addl	$1, %eax
	movl	%eax, p2(%esp)
	movl	arg3(%ebp), %eax
	movl	%eax, p3(%esp)
	call	merge_sort		# recursive call

	# merge(A, p, q, r)
	movl	arg1(%ebp), %eax
	movl	%eax, p1(%esp)
	movl	arg2(%ebp), %eax
	movl	%eax, p2(%esp)
	movl	loc1(%ebp), %eax
	movl	%eax, p3(%esp)
	movl	arg3(%ebp), %eax
	movl	%eax, p4(%esp)
	call	merge
	
ms_out:

	# epilogue
	movl	%ebp, %esp
	popl	%ebp
	ret

# void merge(int A[], int p, int q, int r)
.section .text 
	.globl	merge
	.type	merge, @function
	
merge:
	# prologue
	pushl	%ebp
	movl	%esp, %ebp
	
	andl	$-16, %esp
	subl	$64, %esp	# 64 byte local storage, 36 bytes required(4B each)--> i,j,k,fromA1,fromA2, N1, N2, A1[], A2[]
				# max parameters to function call = 5 x 4B = 20B
				# 36 + 20 = 56B
		
	# initialization
	# fromA1 = fromA2 =FALSE
	movl	$FALSE, loc4(%ebp)
	movl	$FALSE, loc5(%ebp)
	# N1 = q-p+1
	movl	arg3(%ebp), %eax	# eax = q
	subl	arg2(%ebp), %eax	# eax = q-p
	addl	$1, %eax
	movl	%eax, loc6(%ebp)	# N1 = q-p+1
	# A1 = (int*)x_calloc(N1, sizeof(int))
	movl	%eax, p1(%esp)
	movl	$4, p2(%esp)
	call	x_calloc
	movl	%eax, loc8(%ebp)	# A1 = x_calloc()
	
	# N2 = r-q
	movl	arg4(%ebp), %eax	# eax = r
	subl	arg3(%ebp), %eax	# eax = r-q
	movl	%eax, loc7(%ebp)	# N2 = r-q
	# A2 = (int*)x_calloc(N2, sizeof(int))
	movl	%eax, p1(%esp)
	movl	$4, p2(%esp)	
	call	x_calloc	
	movl	%eax, loc9(%ebp)	# A2 = x_calloc()
	
	# copy left array in A1[]
	# int i=0
	movl	$0, loc1(%ebp)
	# for(i=0; i<N1; i++)
	jmp	m_for1_cond
m_for1:
	# A1[i] = A[p+i]
	# = A[p+i]
	movl	arg1(%ebp), %ebx	# ebx = A
	movl	arg2(%ebp), %edx	# edx = p
	addl 	%ecx, %edx		# edx = p+i, ecx contains i from m_for1_cond
	movl	(%ebx, %edx, 4), %eax	# eax = A[p+i]

	# A1[i] =
	movl	loc8(%ebp), %ebx
	movl	%eax, (%ebx, %ecx, 4)	# A1[i] = eax = A[p+i]	
	
	addl	$1, loc1(%ebp)
m_for1_cond:
	movl	loc1(%ebp), %ecx
	cmpl	loc6(%ebp), %ecx	# i - N1 ? -ve
	jl	m_for1		

	# copy right arry in A2[]
	# i=0
	movl	$0, loc1(%ebp)
	jmp	m_for2_cond
m_for2:
	# A2[i] = A[q+i+1]	
	movl	arg1(%ebp), %ebx	# ebx = &A[0]	
	movl	arg3(%ebp), %edx	# edx = q
	addl	$1, %edx		# edx = q = q+1
	addl	%ecx, %edx		# edx = q+1+i
	movl	(%ebx, %edx, 4), %eax	# eax = A[q+i+1]

	movl	loc9(%ebp), %ebx	# ebx = &A2[0]
	movl	%eax, (%ebx, %ecx, 4)	# A2[i] = eax = A[q+i+1]

	addl 	$1, loc1(%ebp)
m_for2_cond:
	movl	loc1(%ebp), %ecx
	cmpl	loc7(%ebp), %ecx	# i - N2 ? -ve
	jl	m_for2

	# k = p; loc3, index used to point to A[] original buffer
	# i = 0; loc1, index used to point into A1[]
	# j = 0; loc2, index used to point into A2[]
	movl	arg2(%ebp), %eax	
	movl	%eax, loc3(%ebp)	# k = p
	movl	$0, loc1(%ebp)		# i = 0
	movl	$0, loc2(%ebp)		# j = 0

	# while (TRUE)
	jmp	m_while1_cond
m_while1:
	# if(i == N1)	// A1[] traversing done ?
	movl	loc1(%ebp), %eax
	cmpl	loc6(%ebp), %eax	# i - N1 ? 0 --> break
	jne	m_while1_next1
	# i == N1
	movl	$TRUE, loc4(%ebp)	# fromA1 = TRUE
	jmp	m_while1_break

m_while1_next1:
	# if(j == N2)	//A2[] traversing done ?
	movl	loc2(%ebp), %eax
	cmpl	loc7(%ebp), %eax	# j - N2 ? 0 --> break
	jne	m_while1_next2
	# j == N2
	movl	$TRUE, loc5(%ebp)	# fromA2 = TRUE
	jmp	m_while1_break

m_while1_next2:
	# if(A1[i] <= A2[j])
	# A2[j]
	movl	loc9(%ebp), %ebx	# ebx = &A2[0]
	movl	loc2(%ebp), %ecx	# ecx = j
	movl	(%ebx, %ecx, 4), %eax	# eax = A[j]
	# A1[i]
	movl	loc8(%ebp), %ebx	# ebx = &A1[0]
	movl	loc1(%ebp), %ecx	# ecx = i
	movl	(%ebx, %ecx, 4), %edx	# edx = A[i]
	# A1[i] <= A2[j] --> ?
	cmpl	%eax, %edx		# A1[i] - A2[j] ? +ve --> jump
	jg	m_while1_else	
	# A[k] = A1[i++] 
	# edx still contains A1[i]
	movl	arg1(%ebp), %ebx	# ebx = &A[0]
	movl	loc3(%ebp), %ecx	# ecx = k
	movl	%edx, (%ebx, %ecx, 4)	# A[k] = A1[i]	
	addl	$1, loc1(%ebp)		# i = i+1
	jmp	m_while1_next3

m_while1_else:
	# A[k] = A2[j++]
	# eax still contains A2[j]
	movl	arg1(%ebp), %ebx	# ebx = &A[0]
	movl	loc3(%ebp), %ecx	# ecx = k
	movl	%eax, (%ebx, %ecx, 4)	# A[k] = A[j]
	addl	$1, loc2(%ebp)		# j=j+1

m_while1_next3:
	# k = k+1;
	addl	$1, loc3(%ebp)	

m_while1_cond:
	jmp	m_while1

m_while1_break:	# out of 1st while(TRUE) loop
m_fromA1_check: # A1[] array traversing done, copy remaining sorted items from A2 to A. This is dummy/alias tag
	# if(fromA1 == TRUE)
	cmpl	$TRUE, loc4(%ebp)	# fromA1 - 1 ? !0 --> jmp
	jne	m_fromA2_check
	# equal
	# while(j<N2)
	jmp	m_while2_cond
m_while2:
	# A[k++] = A2[j++]
	# = A2[j]
	movl	loc9(%ebp), %ebx	# ebx = &A2[0]
	# movl	loc2(%ebp), %ecx	# ecx = j	already exist from m_while2_cond
	movl	(%ebx, %ecx, 4), %eax	# eax = A2[j]
	# A[k] =
	movl	arg1(%ebp), %ebx	# ebx = &A[0]
	movl	loc3(%ebp), %ecx	# ecx = k
	movl	%eax, (%ebx, %ecx, 4)	# A[k] = A2[j]
	
	addl	$1, loc2(%ebp)		# j = j+1
	addl	$1, loc3(%ebp)		# k = k+1
	
m_while2_cond:
	movl	loc2(%ebp), %ecx	# ecx = j
	cmpl	loc7(%ebp), %ecx	# j - N2 ? -ve --> jl
	jl	m_while2
	 

m_fromA2_check: # A2[] array traversing done, copy remaining sorted items from A1 to A
	# if(fromA2 == TRUE)
	cmpl	$TRUE, loc5(%ebp)	# fromA2 - 1 ? !0 --> jmp
	jne	m_out
	# equal
	# while(i<N1)
	jmp	m_while3_cond
m_while3:
	# A[k++] = A1[i++]
	# evaluate A1[i]
	movl	loc8(%ebp), %ebx 	# ebx = &A1[0]
	#movl	loc1(%ebp), %ecx	# ecx		already exist from m_while3_cond	
	movl	(%ebx, %ecx, 4), %eax	# eax = A1[i]
	# evaluate &A[k]
	movl	arg1(%ebp), %ebx	# ebx = &A[0]
	movl	loc3(%ebp), %ecx	# ecx = k
	movl	%eax, (%ebx, %ecx, 4)	# A[k] = A1[i]

	addl	$1, loc1(%ebp)		# i=i+1
	addl	$1, loc3(%ebp)		# k=k+1
m_while3_cond:
	movl	loc1(%ebp), %ecx	# ecx = i
	cmpl	loc6(%ebp), %ecx	# i - N1 ? -ve --> jl
	jl	m_while3
	
m_out:
	# x_free(A1)
	movl	loc8(%ebp), %eax
	movl	%eax, p1(%esp)
	call 	x_free
	# x_free(A2)
	movl	loc9(%ebp), %eax
	movl	%eax, p1(%esp)
	call	x_free

	# epilogue
	movl	%ebp, %esp
	popl	%ebp
	ret

# void test_sort(int A[], int N)
.section .text
	.globl	test_sort
	.type	test_sort, @function

test_sort:
	# prologue
	pushl	%ebp
	movl	%esp, %ebp

	andl	$-16, %esp
	subl	$16, %esp

	# int i = 0
	movl	$0, loc1(%ebp)

	# int j = N-1
	movl	arg2(%ebp), %eax
	subl	$1, %eax
	movl	%eax, loc2(%ebp)	

	# for(i=0; i<(N-1); i++)
	jmp	ts_for_cond

ts_for:
	# if(A[i] > A[i+1])
	# ebx = &A[0]
	movl	arg1(%ebp), %ebx
	
	# eax = A[i]
	movl	(%ebx, %ecx, 4), %eax
	
	# edx = A[i+1] 
	addl	$1, %ecx
	movl	(%ebx, %ecx, 4), %edx
	
	cmpl	%edx, %eax 
	jg	ts_fail		# >
	addl	$1, loc1(%ebp)

ts_for_cond:
	movl	loc1(%ebp), %ecx	# ecx = i
	cmpl	loc2(%ebp), %ecx	# i < (N-1)
	jl	ts_for
	jmp	ts_success

ts_fail:
	movl 	$failure_msg, p1(%esp)
	jmp 	ts_out

ts_success:
	movl	$success_msg, p1(%esp)
ts_out:
	call	printf

	# epilogue
	movl	%ebp, %esp
	popl	%ebp
	ret
	

# void input(int A[], int N)
.section .text
	.globl	input
	.type	input, @function
input:
	# prologue
	pushl	%ebp
	movl	%esp, %ebp
	
	andl 	$-16, %esp
	subl	$16, %esp

	# srand(time(0))
	movl	$0, p1(%esp)
	call	time
	movl	%eax, p1(%esp)
	call	srand

	# int i = 0
	movl	$0, loc1(%ebp)
	
	# for(i=0; i<N, i++)
	jmp	in_for_cond

in_for:
	# A[i] = rand() % CAP 
	call	rand
	xorl	%edx, %edx
	movl	$CAP, %ecx	# ecx = divisor
	divl	%ecx		# eax/ecx = eax; eax % ecx = edx
	
	# A[i] = %eax
	movl	arg1(%ebp), %ebx	
	movl	loc1(%ebp), %ecx
	movl	%edx, (%ebx, %ecx, 4)	# remainder put in 

	addl	$1, loc1(%ebp)

in_for_cond:
	movl	loc1(%ebp), %eax
	cmpl	arg2(%ebp), %eax
	jl	in_for
	
	# epilogue
	movl	%ebp, %esp
	popl	%ebp
	ret
	
# void output(int A[], int N)
.section .text
	.globl 	output
	.type 	output, @function
output:
	# pro-logue
	pushl	%ebp
	movl	%esp, %ebp
	
	andl	$-16, %esp
	subl	$16, %esp

	# int i
	movl	$0, loc1(%ebp)

	# ebx = &A[0]
	movl	arg1(%ebp), %ebx

	# for(i=0; i<N, i++)
	jmp	op_for_cond
	
op_for:
	# printf("A[%d]=%d\n", i, A[i])
	movl	$msg1, p1(%esp)
	movl	%ecx, p2(%esp)
	movl	(%ebx, %ecx, 4), %eax
	movl	%eax, p3(%esp)
	call	printf
	addl 	$1, loc1(%ebp)

op_for_cond:
	movl	loc1(%ebp), %ecx
	cmpl	arg2(%ebp), %ecx
	jl	op_for		

	# epi-logue
	movl	%ebp, %esp
	popl	%ebp
	ret

# void *x_calloc(int nr_elements, int size_per_element)
.section .text
	.globl	x_calloc
	.type	x_calloc, @function

x_calloc:
	#pro-logue
	pushl	%ebp
	movl	%esp, %ebp
	
	andl	$-16, %esp
	subl	$16, %esp
	
	# tmp = calloc(nr_elements, size_per_element)
	movl	arg1(%ebp), %eax
	movl	%eax, p1(%esp)
	movl	arg2(%ebp), %eax
	movl	%eax, p2(%esp)
	call	calloc
	movl	%eax, loc1(%ebp)
	
	# error handling
	cmpl 	$0, %eax
	jne	xc_out
	movl	$err1, p1(%esp)
	call	printf
	movl	$EXIT_FAILURE, p1(%esp)
	call	exit
	
xc_out:	
	#epi-logue	
	movl	%ebp, %esp
	popl	%ebp
	ret

# void x_freei(void *ptr)
.section .text
	.globl x_free
	.type x_free, @function
x_free:
	# pro-logue
	pushl	%ebp
	movl	%esp, %ebp

	andl	$-16, %esp
	subl	$16, %esp
	
	movl	arg1(%ebp), %ebx
	cmpl	$0, %ebx
	jne	xf_free
	# printf("x_free() cannot free null pointer\n")
	movl	$err2, p1(%esp)
	call	printf
	jmp	xf_out

xf_free:
	# free(ptr)
	movl	arg1(%ebp), %ebx
	movl	%ebx, p1(%esp)
	call	free	

xf_out:
	# epi-logue
	movl	%ebp, %esp
	popl 	%ebp
	ret
