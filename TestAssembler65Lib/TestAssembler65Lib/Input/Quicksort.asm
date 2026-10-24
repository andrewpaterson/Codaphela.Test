; A feature level test: quicksort.  The program makes its data with mul (a linear
; congruential generator), then sorts it recursively with jsr, keeping registers over
; the first call with psh (W, X) and reaching the values through register addresses.
; The test adds COUNT, SEED and MASK.
;
; Quicksort.  COUNT pseudo random 32 bit values (x = x * 1664525 + 1013904223, and MASK)
; are made with mul and sorted in place, unsigned and ascending, by a recursive
; quicksort (Lomuto partition, the last element as the pivot).

Data	= $4000

		.org $1000
Start:
		wtth (A, B), 32
		wtth (X, Y), 32
		cpy V, Data				; fill Data
		cpy X, SEED

Generate:
		cpy A, X
		cpy B, 1664525
		cpy W, 0
		mul
		add Y, 1013904223
		cpy X, Y
		and Y, MASK
		cpy [V], Y
		add V, 4
		cmp V, Data + 4 * COUNT
		brac c, Generate
		cpy V, Data
		cpy W, Data + 4 * (COUNT - 1)
		jsr QuickSort
		stp

; Sorts the values from [V] to [W] (inclusive).  Changes A, B, V, W, X and Y.
QuickSort:
		cmp V, W
		bras c, Sorted			; one value or none
		cpy A, [W]				; A = the pivot
		cpy X, V				; X = where the next value below the pivot goes
		cpy Y, V				; Y = the value being looked at

Partition:
		cmp Y, W
		bras c, Partitioned
		cpy B, [Y]
		cmp B, A
		bras c, NotBelow
		psh A					; swap [X] and [Y]
		cpy A, [X]
		cpy [Y], A
		cpy [X], B
		pul A
		add X, 4

NotBelow:
		add Y, 4
		bra Partition

Partitioned:
		cpy B, [X]				; the pivot goes to X
		cpy [X], A
		cpy [W], B
		psh (W, X)
		cpy W, X				; sort the values below the pivot
		sub W, 4
		jsr QuickSort
		pul (W, X)
		cpy V, X				; then the values above it
		add V, 4
		jsr QuickSort

Sorted:
		ret
