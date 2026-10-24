; A feature level test: Conway's Game of Life.  Each row's neighbour counts come from a
; vector copy and seven vector adds of the rows above, beside and below; the rule uses
; register + register addresses.  The test adds GENERATIONS and the starting pattern.
;
; Conway's Game of Life on a SIZE x SIZE grid of bytes (1 alive, 0 dead) with a border of
; dead cells, so each row is STRIDE bytes.  For each row the neighbour counts are built
; with vector operations: a copy of the row above shifted one left, then adds of the
; other seven neighbours.  The rule writes Next, which is copied back to Grid.

SIZE		= 16
STRIDE		= SIZE + 2
Grid		= $3000				; the border row and column come first
Next		= $3200
Counts		= $3400				; Counts + 1 to Counts + SIZE
Row			= $0100				; the address of the row's border cell
Generation	= $0108

		.org $1000
Start:
		wtth (A, X), 32
		wth B, 8
		cpy A, GENERATIONS
		cpy [Generation], A

NextGeneration:
		cpy A, Grid + STRIDE
		cpy [Row], A

NextRow:
		cpy W, [Row]			; above left
		sub W, STRIDE
		cpy V, Counts + 1
		cpy A, SIZE - 1
		vcpy W, V, +1, A, 8
		sub W, SIZE - 1			; above
		cpy V, Counts + 1
		cpy A, SIZE - 1
		vadd W, V, +1, A, 8
		sub W, SIZE - 1			; above right
		cpy V, Counts + 1
		cpy A, SIZE - 1
		vadd W, V, +1, A, 8
		cpy V, Counts + 1		; left (W is already there: the next row's border)
		cpy A, SIZE - 1
		vadd W, V, +1, A, 8
		sub W, SIZE - 2			; right
		cpy V, Counts + 1
		cpy A, SIZE - 1
		vadd W, V, +1, A, 8
		cpy V, Counts + 1		; below left
		cpy A, SIZE - 1
		vadd W, V, +1, A, 8
		sub W, SIZE - 1			; below
		cpy V, Counts + 1
		cpy A, SIZE - 1
		vadd W, V, +1, A, 8
		sub W, SIZE - 1			; below right
		cpy V, Counts + 1
		cpy A, SIZE - 1
		vadd W, V, +1, A, 8
		cpy A, [Row]			; A = this row in Grid, V = this row in Next
		cpy V, A
		add V, Next - Grid
		cpy X, 1

Cell:
		cpy B, [Counts + X]
		cmp B, 3
		bras z, Live
		cmp B, 2
		brac z, Dead
		cpy B, [A + X]			; two neighbours: unchanged
		bra Store

Live:
		cpy B, 1
		bra Store

Dead:
		cpy B, 0

Store:
		cpy [V + X], B
		add X, 1
		cmp X, SIZE + 1
		brac c, Cell
		cpy A, [Row]
		add A, STRIDE
		cpy [Row], A
		cmp A, Grid + (SIZE + 1) * STRIDE
		brac c, NextRow
		cpy W, Next				; Grid = Next
		cpy V, Grid
		cpy A, STRIDE * STRIDE - 1
		vcpy W, V, +1, A, 8
		cpy A, [Generation]
		sub A, 1
		cpy [Generation], A
		brac z, NextGeneration
		stp
