; A feature level test: big numbers.  100! uses mul limb by limb; printing uses div
; (base 16 long division) limb by limb; F(300) adds limb by limb with the carry kept by
; hand (stat f, c) because add has no carry in.  Vector copies move the limbs.
;
; Big numbers in little endian 32 bit limbs.
;   100! by multiplying limb by limb (mul), printed by dividing by 10 (div).
;   F(300), the 300th Fibonacci number, by adding limb by limb.  add has no carry in, so
;   the carry is kept by hand.
; Each result is printed as decimal text ending with a zero; FactorialText and
; FibonacciText hold the address of its first digit.

LIMBS			= 8				; Fibonacci limbs
Number			= $2000			; 100!
FibonacciOld	= $3000
FibonacciNew	= $3100
FibonacciSum	= $3200
FactorialDigits	= $4100			; the digits end here (the zero is already there)
FibonacciDigits	= $4200

Base			= $0100			; ToDecimal's number (from Base to End)
End				= $0108
Digits			= $0110			; ToDecimal's next digit goes before this
Steps			= $0118
FactorialText	= $0120
FibonacciText	= $0128

		.org $1000
Start:
		wth A, 32
		wth B, 8
		wtth (X, Y), 64
		cpy [Number], 1			; 1! = 1
		cpy V, Number + 4
		cpy [End], V
		cpy B, 2				; B = k: Number = Number * k

Factorial:
		cpy V, Number
		cpy X, 0				; X = the carry

MultiplyLimb:
		cpy A, [V]
		cpy W, 0
		mul						; Y = limb * k
		add Y, X
		cpy A, Y
		cpy [V], A
		cpy X, Y
		shr X, 32
		add V, 4
		cmp V, [End]
		brac c, MultiplyLimb
		cmp X, 0				; a carry out makes a new top limb
		bras z, FactorialNext
		cpy A, X
		cpy [V], A
		add V, 4
		cpy [End], V

FactorialNext:
		add B, 1
		cmp B, 101
		brac c, Factorial
		cpy V, Number
		cpy [Base], V
		cpy V, FactorialDigits
		cpy [Digits], V
		jsr ToDecimal
		cpy V, [Digits]
		cpy [FactorialText], V

		cpy [FibonacciNew], 1	; F(0) = 0, F(1) = 1
		cpy Y, 299
		cpy [Steps], Y

Fibonacci:
		cpy X, 0				; X = the byte offset of the limb
		cpy B, 0				; B = the carry in

AddLimb:
		cpy A, [FibonacciOld + X]
		add A, [FibonacciNew + X]
		stat f, c				; f = the carry out of the first add
		add A, B
		bras c, CarryOut
		bras f, CarryOut
		cpy B, 0
		bra StoreLimb

CarryOut:
		cpy B, 1

StoreLimb:
		cpy [FibonacciSum + X], A
		add X, 4
		cmp X, LIMBS * 4
		brac c, AddLimb
		cpy W, FibonacciNew		; Old = New, New = Sum
		cpy V, FibonacciOld
		cpy A, LIMBS - 1
		vcpy W, V, +1, A, 32
		cpy W, FibonacciSum
		cpy V, FibonacciNew
		cpy A, LIMBS - 1
		vcpy W, V, +1, A, 32
		cpy Y, [Steps]
		sub Y, 1
		cpy [Steps], Y
		brac z, Fibonacci

		cpy V, FibonacciNew
		cpy [Base], V
		cpy V, FibonacciNew + LIMBS * 4
		cpy [End], V
		cpy V, FibonacciDigits
		cpy [Digits], V
		jsr ToDecimal
		cpy V, [Digits]
		cpy [FibonacciText], V
		stp

; Writes the decimal digits of the number from [Base] to [End] before [Digits] and moves
; [Digits] to the first digit.  Each pass divides the number by 10, from the top limb
; down, with the remainder carried into the next limb's dividend.  The number becomes 0.
ToDecimal:
		cpy V, [End]
		cpy X, 0				; X = the remainder

DivideLimb:
		sub V, 4
		cpy Y, X				; Y = remainder * 2^32 + limb
		shl Y, 32
		cpy A, [V]
		or Y, A
		cpy A, 10
		cpy B, 0
		cpy W, 0
		div						; Y = Y / 10, B = the remainder
		cpy A, Y
		cpy [V], A
		cpy X, B
		cmp V, [Base]
		brac z, DivideLimb
		add X, '0'
		cpy V, [Digits]
		sub V, 1
		cpy B, X
		cpy [V], B
		cpy [Digits], V
		cpy V, [End]			; drop a zero top limb
		sub V, 4
		cpy A, [V]
		cmp A, 0
		brac z, ToDecimalNext
		cpy [End], V

ToDecimalNext:
		cpy V, [End]
		cmp V, [Base]
		brac z, ToDecimal
		ret
