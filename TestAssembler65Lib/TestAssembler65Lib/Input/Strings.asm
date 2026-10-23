; A feature level test: string routines that are each one block or vector operation
; ended by its stop condition (btst, bcmp, bpand with z and n, vcpy and vcmp), and
; overlapping moves copied in both directions.
;
; String routines, each one block or vector operation ended by its stop condition.

Copy			= $3000
Length			= $0100
Found			= $0108
MarkedLength	= $0110
Compare			= $0118
CompareSame		= $0120

		.org $1000
Start:
		wth A, 4
		wth B, 1

; strlen(Text): btst stops at the zero (D = [V] and $FF is zero).  V is then past it.
		cpy B, $FF
		cpy V, Text
		cpy A, 1000
		btst B, V, +1, A, z
		sub V, Text + 1
		cpy [Length], V

; strcpy(Copy, Text): vcpy stops once it has copied the zero.
		cpy W, Text
		cpy V, Copy
		cpy A, 1000
		vcpy W, V, +1, A, 8, z

; strchr(Text, 'q'): bcmp stops when [V] - 'q' is zero.
		cpy B, 'q'
		cpy V, Text
		cpy A, 1000
		bcmp B, V, +1, A, z
		sub V, 1
		cpy [Found], V

; Upper case Lower in place: bpand takes n and z from the byte it read, so it stops at
; the zero.
		cpy B, $DF
		cpy V, Lower
		cpy A, 1000
		bpand B, V, +1, A, z

; Strip the end marker (bit 7) from Marked: bpand stops at the marked byte, after
; clearing its bit 7.
		cpy B, $7F
		cpy V, Marked
		cpy A, 1000
		bpand B, V, +1, A, n
		sub V, Marked
		cpy [MarkedLength], V

; memmove(Up + 2, Up, 8): the regions overlap upwards so copy from the end down.
		cpy W, Up + 7
		cpy V, Up + 9
		cpy A, 7
		vcpy W, V, -1, A, 8

; memmove(Down, Down + 2, 8): the regions overlap downwards so copy from the start up.
		cpy W, Down + 2
		cpy V, Down
		cpy A, 7
		vcpy W, V, +1, A, 8

; strcmp(Text, Other): vcmp (D = [V] - [W], nothing stored) stops at the first
; difference, or after the zero when they are the same.
		cpy V, Text
		cpy W, Other
		cpy A, [Length]
		vcmp W, V, +1, A, 8, !z
		bras z, Same
		bras n, Less
		cpy [Compare], 1
		bra Compared

Less:
		cpy [Compare], -1
		bra Compared

Same:
		cpy [Compare], 0

Compared:
		cpy V, Text				; strcmp(Text, Copy) is 0
		cpy W, Copy
		cpy A, [Length]
		vcmp W, V, +1, A, 8, !z
		cpy [CompareSame], 1
		brac z, Done
		cpy [CompareSame], 0

Done:
		stp

		.org $2000
Text:
		.byte "The quick brown fox jumps over the lazy dog", 0

		.org $2040
Other:
		.byte "The quick red fox", 0

		.org $2060
Lower:
		.byte "hello", 0

		.org $2070
Marked:
		.byte "HELL", 'O' | $80, '!'

		.org $2080
Up:
		.byte "ABCDEFGHIJ"

		.org $2090
Down:
		.byte "ABCDEFGHIJ"
