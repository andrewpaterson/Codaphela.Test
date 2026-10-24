; A feature level test: a Mandelbrot set drawn by a 65C64 program.  The program uses
; Q24 fixed point in 64 bit registers, a signed multiply subroutine built on the
; unsigned mul, memory variables at one word offsets, scp to build the colour and a
; 32 bit W to store each pixel.  Labels are on their own lines.
;
; Mandelbrot set, WIDTH x HEIGHT pixels of 32 bit ARGB at Image.
; Fixed point Q24 (24 fraction bits) in 64 bit registers.
; c runs from -2.0 to 0.5 across and -1.25 to 1.25 down.

WIDTH	= 100
HEIGHT	= 100
MAXITER	= 64
ONE		= 1 << 24
XMIN	= -2 * ONE
YMIN	= -5 * ONE / 4
XSTEP	= 5 * ONE / (2 * WIDTH)
YSTEP	= 5 * ONE / (2 * HEIGHT)
FOUR	= 4 * ONE
Image	= $100000

; Variables, 64 bit, in the first 64KB (one word offset addresses).
CX		= $0100
CY		= $0108
ZX		= $0110
ZY		= $0118
ZX2		= $0120
ZY2		= $0128
COLS	= $0130
ROWS	= $0138

		.org $1000
Start:
		wtth (A, B), 64
		wtth (X, Y), 64
		cpy V, Image			; V points at the next pixel
		cpy A, YMIN
		cpy [CY], A
		cpy A, HEIGHT
		cpy [ROWS], A

Row:
		cpy A, XMIN
		cpy [CX], A
		cpy A, WIDTH
		cpy [COLS], A

Pixel:
		cpy [ZX], 0				; z = 0
		cpy [ZY], 0
		cpy X, 0				; X counts the iterations

Iterate:
		cpy A, [ZX]				; ZX2 = ZX * ZX
		cpy B, A
		jsr Multiply
		cpy [ZX2], Y
		cpy A, [ZY]				; ZY2 = ZY * ZY
		cpy B, A
		jsr Multiply
		cpy [ZY2], Y
		add Y, [ZX2]			; escaped when ZX2 + ZY2 >= 4
		cmp Y, FOUR
		bras c, Escaped
		cpy A, [ZX]				; ZY = 2 * ZX * ZY + CY
		cpy B, [ZY]
		jsr Multiply
		shl Y, 1
		add Y, [CY]
		cpy [ZY], Y
		cpy Y, [ZX2]			; ZX = ZX2 - ZY2 + CX
		sub Y, [ZY2]
		add Y, [CX]
		cpy [ZX], Y
		add X, 1
		cmp X, MAXITER
		brac z, Iterate

		cpy W, $FF000000		; inside the set: black
		bra Store

Escaped:
		cpy W, X				; outside: grey from the iteration count
		shl W, 2
		scp (W, 0), (W, 1), 1
		scp (W, 0), (W, 2), 1
		or W, $FF000000

Store:
		cpy [V], W				; W is 32 bits wide
		add V, 4
		cpy A, [CX]
		add A, XSTEP
		cpy [CX], A
		cpy A, [COLS]
		sub A, 1
		cpy [COLS], A
		brac z, Pixel

		cpy A, [CY]
		add A, YSTEP
		cpy [CY], A
		cpy A, [ROWS]
		sub A, 1
		cpy [ROWS], A
		brac z, Row
		stp

; Y = (A * B) >> 24, signed.  Changes A, B, W and f.
Multiply:
		cpy W, 0				; mul counts in W
		abs A					; n = A was negative
		stat f, n
		abs B					; n = B was negative
		mul						; Y = A * B (leaves n alone)
		braso (f, n), Negative
		shr Y, 24
		ret
Negative:
		shr Y, 24
		neg Y
		ret
