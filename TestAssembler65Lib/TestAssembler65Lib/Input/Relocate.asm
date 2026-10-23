; A feature level test: position independent code.  The payload uses only relative
; branches and brsr (C is never an assembled value), so it gives the same results
; copied to 0000:8000 or run where it was assembled.  psh C records where it ran.
;
; Position independent code.  The loader copies Payload to Destination and jumps to
; it.  Payload only uses relative branches and brsr, so it runs at any address.  It
; records where it ran with psh C.

Destination	= $8000
Origin		= $0200				; the loader stores Payload's address here
Sum			= $0208				; 1 + 2 + ... + 100
Fibonacci20	= $0210				; the 20th Fibonacci number
Where		= $0218				; C as the payload ran (the address after its psh C)

		.org $1000
Loader:
		wth A, 4
		cpy W, Payload
		cpy [Origin], W
		cpy V, Destination
		cpy A, (PayloadEnd - Payload) / 2 - 1	; words to copy, less one
		vcpy W, V, +1, A, 16
		jmp Destination

Payload:
		wtth (X, Y), 8
		wtth (A, B), 8
		cpy X, 0
		cpy Y, 100

SumLoop:
		add X, Y
		sub Y, 1
		brac z, SumLoop
		cpy [Sum], X
		cpy A, 20
		brsr Fibonacci
		cpy [Fibonacci20], X
		psh C
		pul [Where]
		stp

; X = the A-th Fibonacci number.  Changes A, B and Y.
Fibonacci:
		cpy X, 0
		cpy Y, 1

FibonacciLoop:
		cpy B, X
		add B, Y
		cpy X, Y
		cpy Y, B
		sub A, 1
		brac z, FibonacciLoop
		ret

PayloadEnd:
