; A feature level test: SHA-256.  The program pads the message, byte swaps big endian
; words with scp, builds rotates from shr, shl and xor in a subroutine, and moves the
; working variables down with an overlapping vector copy.  The message follows the
; Message label and the test adds the MessageEnd label.
;
; SHA-256 of the bytes from Message to MessageEnd.  The digest is left in Hash as eight
; 32 bit words.
; The message is padded in Block: the bytes, $80, zeros and the length in bits (big
; endian) to a multiple of 64 bytes.  Words are big endian so each one is byte swapped
; with scp.  There is no rotate so XorRotate builds one from shr and shl.

MESSAGE_LENGTH	= MessageEnd - Message
BLOCKS			= (MESSAGE_LENGTH + 9 + 63) / 64

Hash		= $0200				; H0 to H7
Vars		= $0240				; a to h
VarA		= Vars
VarB		= Vars + 4
VarC		= Vars + 8
VarD		= Vars + 12
VarE		= Vars + 16
VarF		= Vars + 20
VarG		= Vars + 24
VarH		= Vars + 28
T1			= $0260
T2			= $0264
BlockPtr	= $0268
BlocksLeft	= $026C
Block		= $3000				; the padded message
Schedule	= $3800				; W[0] to W[63]

		.org $1000
Start:
		wtth (A, B), 4
		wtth (X, Y), 4
		cpy W, Message			; Block = the message, $80, zeros, the length
		cpy V, Block
		cpy A, MESSAGE_LENGTH - 1
		vcpy W, V, +1, A, 8
		wth B, 1
		cpy B, $80
		cpy [Block + MESSAGE_LENGTH], B
		wth B, 4
		cpy A, MESSAGE_LENGTH * 8
		jsr Swap
		cpy [Block + BLOCKS * 64 - 4], B
		cpy W, InitialHash		; Hash = the initial hash values
		cpy V, Hash
		cpy A, 7
		vcpy W, V, +1, A, 32
		cpy A, Block
		cpy [BlockPtr], A
		cpy A, BLOCKS
		cpy [BlocksLeft], A

NextBlock:
		cpy W, [BlockPtr]		; W[0] to W[15]: the block's words, byte swapped
		cpy V, 0

LoadWord:
		cpy A, [V + W]
		jsr Swap
		cpy [Schedule + V], B
		add V, 4
		cmp V, 64
		brac c, LoadWord

ExpandWord:
		cpy A, [Schedule - 8 + V]	; W[t] = s1(W[t-2]) + W[t-7] + s0(W[t-15]) + W[t-16]
		cpy Y, 0
		cpy X, 17
		jsr XorRotate
		cpy X, 19
		jsr XorRotate
		cpy B, A
		shr B, 10
		xor Y, B
		cpy A, [Schedule - 28 + V]
		add Y, A
		cpy A, [Schedule - 64 + V]
		add Y, A
		cpy [Schedule + V], Y
		cpy A, [Schedule - 60 + V]
		cpy Y, 0
		cpy X, 7
		jsr XorRotate
		cpy X, 18
		jsr XorRotate
		cpy B, A
		shr B, 3
		xor Y, B
		cpy A, [Schedule + V]
		add Y, A
		cpy [Schedule + V], Y
		add V, 4
		cmp V, 256
		brac c, ExpandWord
		cpy W, Hash				; a to h = H0 to H7
		cpy V, Vars
		cpy A, 7
		vcpy W, V, +1, A, 32
		cpy V, 0				; V = 4 t

Round:
		cpy A, [VarE]			; T1 = h + S1(e) + Ch(e, f, g) + K[t] + W[t]
		cpy Y, 0
		cpy X, 6
		jsr XorRotate
		cpy X, 11
		jsr XorRotate
		cpy X, 25
		jsr XorRotate
		add Y, [VarH]
		and A, [VarF]
		cpy B, [VarE]
		xor B, -1
		and B, [VarG]
		xor A, B
		add Y, A
		cpy A, [K + V]
		add Y, A
		cpy A, [Schedule + V]
		add Y, A
		cpy [T1], Y
		cpy A, [VarA]			; T2 = S0(a) + Maj(a, b, c)
		cpy Y, 0
		cpy X, 2
		jsr XorRotate
		cpy X, 13
		jsr XorRotate
		cpy X, 22
		jsr XorRotate
		and A, [VarB]
		cpy B, [VarA]
		and B, [VarC]
		xor A, B
		cpy B, [VarB]
		and B, [VarC]
		xor A, B
		add Y, A
		cpy [T2], Y
		psh V					; h, g, ... b = g, f, ... a (overlapping, so from the top down)
		cpy W, VarG
		cpy V, VarH
		cpy A, 6
		vcpy W, V, -1, A, 32
		pul V
		cpy A, [T1]				; e = d + T1, a = T1 + T2
		add [VarE], A
		cpy Y, [T2]
		add Y, A
		cpy [VarA], Y
		add V, 4
		cmp V, 256
		brac c, Round
		cpy X, 0				; H0 to H7 += a to h

AddHash:
		cpy A, [Vars + X]
		add A, [Hash + X]
		cpy [Hash + X], A
		add X, 4
		cmp X, 32
		brac c, AddHash
		cpy A, [BlockPtr]
		add A, 64
		cpy [BlockPtr], A
		cpy A, [BlocksLeft]
		sub A, 1
		cpy [BlocksLeft], A
		brac z, NextBlock
		stp

; Y = Y xor (A rotated right by X).  Changes B and W.
XorRotate:
		cpy B, A
		shr B, X
		xor Y, B
		cpy W, 32
		sub W, X
		cpy B, A
		shl B, W
		xor Y, B
		ret

; B = A with its bytes reversed.
Swap:
		scp (A, 0), (B, 3), 1
		scp (A, 1), (B, 2), 1
		scp (A, 2), (B, 1), 1
		scp (A, 3), (B, 0), 1
		ret

InitialHash:
		.long $6a09e667, $bb67ae85, $3c6ef372, $a54ff53a, $510e527f, $9b05688c, $1f83d9ab, $5be0cd19

K:
		.long $428a2f98, $71374491, $b5c0fbcf, $e9b5dba5, $3956c25b, $59f111f1, $923f82a4, $ab1c5ed5
		.long $d807aa98, $12835b01, $243185be, $550c7dc3, $72be5d74, $80deb1fe, $9bdc06a7, $c19bf174
		.long $e49b69c1, $efbe4786, $0fc19dc6, $240ca1cc, $2de92c6f, $4a7484aa, $5cb0a9dc, $76f988da
		.long $983e5152, $a831c66d, $b00327c8, $bf597fc7, $c6e00bf3, $d5a79147, $06ca6351, $14292967
		.long $27b70a85, $2e1b2138, $4d2c6dfc, $53380d13, $650a7354, $766a0abb, $81c2c92e, $92722c85
		.long $a2bfe8a1, $a81a664b, $c24b8b70, $c76c51a3, $d192e819, $d6990624, $f40e3585, $106aa070
		.long $19a4c116, $1e376c08, $2748774c, $34b0bcb5, $391c0cb3, $4ed8aa4a, $5b9cca4f, $682e6ff3
		.long $748f82ee, $78a5636f, $84c87814, $8cc70208, $90befffa, $a4506ceb, $bef9a3f7, $c67178f2

Message:
