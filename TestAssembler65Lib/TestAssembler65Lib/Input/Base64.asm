; A feature level test: Base64.  Subcopy builds each 3 byte group (scp) and splits it
; into 6 bit fields (scb); decoding uses a table the program builds and scb to put the
; fields back.  The input follows the Input label and ends at InputEnd.
;
; Base64: encode Input to Encoded, then decode Encoded to Decoded.  Both outputs end
; with a zero.  Each 3 byte group is built in Y (first byte highest) with scp and split
; into four 6 bit fields with scb; decoding puts the fields back with scb.

DecodeTable	= $3000				; character -> 6 bit value (built by the program)
Encoded		= $4000
Decoded		= $5000
Left		= $0100				; input bytes left at the start of a group

		.org $1000
Start:
		wth B, 8
		wtth (A, X), 32
		wth Y, 32
		cpy W, Input
		cpy A, InputEnd - Input
		cpy V, Encoded

EncodeGroup:
		cmp A, 0
		bras z, EncodeDone
		cpy [Left], A
		cpy Y, 0
		cpy X, 2				; the byte of Y for the next input byte

EncodeByte:
		cpy B, 0				; a zero byte past the end of the input
		cmp A, 0
		bras z, EncodePut
		cpy B, [W]
		add W, 1
		sub A, 1

EncodePut:
		scp (B, 0), (Y, X), 1
		sub X, 1
		brac n, EncodeByte
		cpy X, 18				; the bit of Y for the next 6 bit field

EncodeCharacter:
		cpy B, 0
		scb (Y, X), (B, 0), 6
		cpy B, [Alphabet + B]
		cpy [V], B
		add V, 1
		sub X, 6
		brac n, EncodeCharacter
		cpy X, [Left]			; pad the last group with =
		cmp X, 3
		bras c, EncodeGroup
		cpy B, '='
		sub V, 1
		cpy [V], B
		cmp X, 2
		bras z, EncodePadded
		sub V, 1
		cpy [V], B
		add V, 1

EncodePadded:
		add V, 1
		bra EncodeGroup

EncodeDone:
		cpy B, 0
		cpy [V], B
		cpy X, 0				; build the decode table from the alphabet

BuildTable:
		cpy B, [Alphabet + X]
		cpy Y, B
		cpy B, X
		cpy [DecodeTable + Y], B
		add X, 1
		cmp X, 64
		brac c, BuildTable
		cpy W, Encoded
		cpy V, Decoded

DecodeGroup:
		cpy B, [W]
		bras z, DecodeDone
		cpy Y, 0
		cpy X, 18				; the bit of Y for the next 6 bit field
		cpy A, 3				; the bytes this group decodes to

DecodeCharacter:
		cpy B, [W]
		add W, 1
		cmp B, '='
		brac z, DecodeField
		sub A, 1				; padding: one byte fewer
		bra DecodeNext

DecodeField:
		cpy B, [DecodeTable + B]
		scb (B, 0), (Y, X), 6

DecodeNext:
		sub X, 6
		brac n, DecodeCharacter
		cpy X, 2				; the byte of Y for the next output byte

DecodeByte:
		cmp A, 0
		bras z, DecodeGroup
		scp (Y, X), (B, 0), 1
		cpy [V], B
		add V, 1
		sub A, 1
		sub X, 1
		bra DecodeByte

DecodeDone:
		cpy B, 0
		cpy [V], B
		stp

Alphabet:
		.byte "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

Input:
