; A feature level test: the sieve of Eratosthenes.  The program fills the sieve with a
; block copy of 8 byte elements, changes register widths to work on single bytes,
; finds p * p with mul, crosses out multiples through absolute + register addresses
; and writes the primes it finds through a register address.
;
; Sieve of Eratosthenes: the primes below N.
; Sieve holds one byte per number, 1 while it may be prime.  The primes found are
; written to Primes as 32 bit values and their number to Count.

N		= 10000
LIMIT	= 100					; the square root of N
Sieve	= $10000
Primes	= $20000
Count	= $0100

		.org $1000
Start:
		wtth (A, X), 4
		wth Y, 4
		wth B, 8
		cpy B, $0101010101010101	; fill the sieve with 1s, 8 bytes a step
		cpy V, Sieve
		cpy A, N / 8 - 1		; the block copy runs until A goes negative
		bcpy B, V, +1, A
		wth B, 1				; B is one byte from here on
		cpy B, 0				; 0 and 1 are not prime
		cpy [Sieve], B
		cpy [Sieve + 1], B
		cpy X, 2				; X is the candidate p

Outer:
		cpy B, [Sieve + X]		; z when p is already crossed out
		bras z, NextCandidate
		cpy A, X				; Y = p * p (p fits in B's byte)
		cpy B, X
		cpy W, 0
		mul
		cpy A, Y				; cross out p * p, p * p + p, ... below N
		cpy B, 0

Mark:
		cpy [Sieve + A], B
		add A, X
		cmp A, N
		brac c, Mark

NextCandidate:
		add X, 1
		cmp X, LIMIT
		brac c, Outer

		cpy X, 2				; collect the primes
		cpy W, Primes
		cpy Y, 0

Collect:
		cpy B, [Sieve + X]
		bras z, NotPrime
		cpy [W], X
		add W, 4
		add Y, 1

NotPrime:
		add X, 1
		cmp X, N
		brac c, Collect
		cpy [Count], Y
		stp
