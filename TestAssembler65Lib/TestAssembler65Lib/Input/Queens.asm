; A feature level test: recursion.  The N queens solver calls itself once per placed
; queen, saving its registers with psh (A, B, W, X, Y) and the status with psh P (fsbi's
; carry must survive the call).  fsbi finds each free column.  N is defined by the test.
;
; N queens: count the ways to place N queens on an N x N board, none attacking another.
; Solve is recursive.  A holds the columns used, B the diagonals going one way and Y
; the other, all as bit masks shifted to the current row.  fsbi finds each free column.

ALL		= (1 << N) - 1
Count	= $0100

		.org $1000
Start:
		wtth (A, B), 4
		wtth (X, Y), 4
		cpy [Count], 0
		cpy A, 0
		cpy B, 0
		cpy Y, 0
		jsr Solve
		stp

Solve:
		cmp A, ALL
		brac z, Search
		add [Count], 1			; every column is used: a solution
		ret

Search:
		cpy W, A				; W = the free columns in this row
		or W, B
		or W, Y
		xor W, -1
		and W, ALL
		cpy X, 0
		cep c					; the first fsbi starts at bit 0

Next:
		fsbi W, X				; X = the next free column (past X when c is set)
		bras v, Return			; no free column left
		psh (A, B, W, X, Y)
		psh P					; c is set: the next fsbi moves past X
		cpy V, 1
		shl V, X				; V = the column's bit
		or A, V
		or B, V
		shl B, 1
		or Y, V
		shr Y, 1
		jsr Solve
		pul P
		pul (A, B, W, X, Y)
		bra Next

Return:
		ret
