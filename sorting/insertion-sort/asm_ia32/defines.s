# main function arguments offsets
.equ argc, 4
.equ argv0, 8	# argv[0]
.equ argv1, 12 	# argv[1]
.equ argv2, 16	# argv[2]
.equ argv3, 20	# argv[3]
.equ argv4, 24	# argv[4]
.equ argv5, 28	# argv[5]
.equ argv6, 32	# argv[6]
.equ argv7, 36	# argv[7]
.equ argv8, 40	# argv[8]
.equ argv9, 44	# argv[9]
.equ argv10,48	# argv[10]

# parameter offsets on stack w.r.t. esp reg while calling any function
.equ p1, 0
.equ p2, 4
.equ p3, 8
.equ p4, 12
.equ p5, 16
.equ p6, 20
.equ p7, 24
.equ p8, 28
.equ p9, 32
.equ p10, 36

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
.equ loc10,-40

# arguments received to functions, their offsets w.r.t. ebp reg 
.equ arg1, 8
.equ arg2, 12
.equ arg3, 16
.equ arg4, 20
.equ arg5, 24
.equ arg6, 28
.equ arg7, 32
.equ arg8, 36
.equ arg9, 40
.equ arg10,44

# constants
.equ EXIT_SUCCESS, 0
.equ EXIT_FAILURE, -1
