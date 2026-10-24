; A feature level test: a bytecode interpreter.  The interpreter dispatches each
; Brainfuck instruction through a jump table with jmp [Table + X] and matches brackets
; by scanning the program.  The program to run follows the Code label.
;
; A Brainfuck interpreter.  Each program byte from '+' to ']' is dispatched through a
; jump table (jmp [Table + X] jumps to the address read from the table); other bytes
; are comments.  The output is written to Output and ends with a zero.
;   V: the next program byte   W: the tape cell   Y: the next output byte
;   B: a byte (a cell or a program byte)   A: the bracket depth   X: the table index

Tape	= $30000
Output	= $40000

		.org $1000
Start:
		wth B, 8
		wtth (A, X), 32
		wth Y, 32
		cpy V, Code
		cpy W, Tape
		cpy Y, Output

Fetch:
		cpy B, [V]
		bras z, Done
		add V, 1
		cpy X, B
		sub X, '+'
		cmp X, TableEnd - Table >> 2
		bras c, Fetch			; not an instruction
		shl X, 2
		jmp [Table + X]

Table:
		.long Increment, Fetch, Decrement, Print			; + , - .
		.long Fetch, Fetch, Fetch, Fetch, Fetch, Fetch, Fetch	; / 0 to 5
		.long Fetch, Fetch, Fetch, Fetch, Fetch, Fetch		; 6 to 9 : ;
		.long Left, Fetch, Right							; < = >
		.long Fetch, Fetch, Fetch, Fetch, Fetch, Fetch, Fetch	; ? @ A to E
		.long Fetch, Fetch, Fetch, Fetch, Fetch, Fetch, Fetch	; F to L
		.long Fetch, Fetch, Fetch, Fetch, Fetch, Fetch, Fetch	; M to S
		.long Fetch, Fetch, Fetch, Fetch, Fetch, Fetch, Fetch	; T to Z
		.long Open, Fetch, Close							; [ \ ]
TableEnd:

Increment:
		cpy B, [W]
		add B, 1
		cpy [W], B
		bra Fetch

Decrement:
		cpy B, [W]
		sub B, 1
		cpy [W], B
		bra Fetch

Left:
		sub W, 1
		bra Fetch

Right:
		add W, 1
		bra Fetch

Print:
		cpy B, [W]
		cpy [Y], B
		add Y, 1
		bra Fetch

; [ with a zero cell skips forward past the matching ].
Open:
		cpy B, [W]
		brac z, Fetch
		cpy A, 1

OpenScan:
		cpy B, [V]
		add V, 1
		cmp B, '['
		brac z, OpenNotOpen
		add A, 1
		bra OpenScan

OpenNotOpen:
		cmp B, ']'
		brac z, OpenScan
		sub A, 1
		brac z, OpenScan
		bra Fetch

; ] with a non-zero cell goes back to just after the matching [.
Close:
		cpy B, [W]
		bras z, Fetch
		cpy A, 1
		sub V, 1

CloseScan:
		sub V, 1
		cpy B, [V]
		cmp B, ']'
		brac z, CloseNotClose
		add A, 1
		bra CloseScan

CloseNotClose:
		cmp B, '['
		brac z, CloseScan
		sub A, 1
		brac z, CloseScan
		add V, 1
		bra Fetch

Done:
		cpy B, 0
		cpy [Y], B
		stp

Code:
