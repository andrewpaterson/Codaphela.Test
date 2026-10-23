#include "TestLib/Assert.h"
#include "TestAsm65Context.h"


//////////////////////////////////////////////////////////////////////////
//
// Assembled programs run on the 65C64 simulator from reset to stp.
//
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//
// The first example on the Example Block Move sheet: V is the source, A the
// destination and W the number of bytes (pulled from the stack).  The branch uses the
// sheet's raw offset.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65ProgramsBlockMove(void)
{
	STestAsm65Run	sRun;
	int				i;

	AssertTrue(TestAsm65Begin(&sRun,
		".org $1000\n"
		"	wth A, 4\n"
		"	wth B, 8\n"
		"	pul (A, V, W), S\n"
		"Loop:\n"
		"	cpy B, [V + W]\n"
		"	cpy [A + W], B\n"
		"	sub W, 8\n"
		"	brac z, -8\n"
		"	stp\n"
		"\n"
		".org $20000\n"
		"	.long 32, Source - 8, Destination - 8\n"
		"\n"
		".org $3000\n"
		"Source:\n"
		"	.quad $1111111111111111, $2222222222222222, $3333333333333333, $4444444444444444\n"
		"Destination:\n"
		"	.quad 0, 0, 0, 0\n", 0x1000));

	AssertSize(20, TestAsm65Run(&sRun, 100));
	for (i = 0; i < 4; i++)
	{
		AssertLongLongIntHex(0x1111111111111111LL * (i + 1), sRun.pcContext->GetQuad(0x3020 + 8 * i));
	}
	AssertLongLongIntHex(0, TestAsm65MPU(&sRun)->GetW());
	TestAsm65End(&sRun);
}


//////////////////////////////////////////////////////////////////////////
//
// The second example on the Example Block Move sheet: W is the source, V the
// destination and A + 1 the number of 64 bit values.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65ProgramsVectorMove(void)
{
	STestAsm65Run	sRun;
	int				i;

	AssertTrue(TestAsm65Begin(&sRun,
		".org $1000\n"
		"	wtth (X, Y), 4\n"
		"	wth A, 4\n"
		"	pul (A, V, W), S\n"
		"	vcpy W, V, +1, A, 64\n"
		"	stp\n"
		"\n"
		".org $20000\n"
		"	.long Source, Destination, 3\n"
		"\n"
		".org $3000\n"
		"Source:\n"
		"	.quad 1, 2, 3, 4\n"
		"Destination:\n"
		"	.quad 0, 0, 0, 0, 99\n", 0x1000));

	TestAsm65Run(&sRun, 100);
	for (i = 0; i < 4; i++)
	{
		AssertLong(i + 1, sRun.pcContext->GetQuad(0x3020 + 8 * i));
	}
	AssertLong(99, sRun.pcContext->GetQuad(0x3040));
	TestAsm65End(&sRun);
}


//////////////////////////////////////////////////////////////////////////
//
// The Example Arithmetic Shift sheet: shift A right by X bits keeping its sign.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65ProgramsArithmeticShift(void)
{
	STestAsm65Run	sRun;

	AssertTrue(TestAsm65Begin(&sRun,
		".org $1000\n"
		"	wtth (A, X), 8\n"
		"	cpy A, -64\n"
		"	cpy X, 3\n"
		"	shr A, X\n"
		"	gwth Y, (A, -1)\n"
		"	stab (A, Y, X, -1), n\n"
		"	stp\n", 0x1000));

	TestAsm65Run(&sRun, 100);
	AssertLongLongIntHex(-8LL, TestAsm65MPU(&sRun)->GetA());
	AssertLong(63, TestAsm65MPU(&sRun)->GetY());
	TestAsm65End(&sRun);
}


//////////////////////////////////////////////////////////////////////////
//
// A negative 16 bit immediate sign extends to A's width (32 bits here).
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65ProgramsSignExtend(void)
{
	STestAsm65Run	sRun;

	AssertTrue(TestAsm65Begin(&sRun,
		".org $1000\n"
		"	wth A, 4\n"
		"	cpy A, -32768:16\n"
		"	stp\n", 0x1000));

	TestAsm65Run(&sRun, 10);
	AssertLongLongIntHex(0xFFFF8000LL, TestAsm65MPU(&sRun)->GetA());
	TestAsm65End(&sRun);
}


//////////////////////////////////////////////////////////////////////////
//
// stab without a repeat writes one bit, at an index that needs an operand word (6 to 63 or a register) too.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65ProgramsStatusToBit(void)
{
	STestAsm65Run	sRun;

	AssertTrue(TestAsm65Begin(&sRun,
		".org $1000\n"
		"	wtth (A, X), 4\n"
		"	cpy A, 0\n"
		"	cpy X, 9\n"
		"	stab (A, 31), 1\n"
		"	stab (A, X), 1\n"
		"	stab (A, 2), 1\n"
		"	stp\n", 0x1000));

	TestAsm65Run(&sRun, 10);
	AssertLongLongIntHex(0x80000204LL, TestAsm65MPU(&sRun)->GetA());
	TestAsm65End(&sRun);
}


//////////////////////////////////////////////////////////////////////////
//
// A subroutine that sums a table of bytes, with forward references.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65ProgramsSubroutine(void)
{
	STestAsm65Run	sRun;

	AssertTrue(TestAsm65Begin(&sRun,
		".org $1000\n"
		"	wtth (A, X), 8\n"
		"	cpy X, 0\n"
		"	jsr Sum\n"
		"	wth A, 4\n"
		"	psh A\n"
		"	pul [Result]\n"
		"	stp\n"
		"\n"
		"Sum:\n"
		"	cpy A, 0\n"
		"Next:\n"
		"	cpy B, [Table + X]\n"
		"	add A, B\n"
		"	add X, 1\n"
		"	cmp X, Count\n"
		"	brac z, Next\n"
		"	ret\n"
		"\n"
		"Table:\n"
		"	.byte 1, 2, 3, 4, 5, 250\n"
		"TableEnd:\n"
		"Count = TableEnd - Table\n"
		".org $2000\n"
		"Result:\n"
		"	.long 0\n", 0x1000));

	TestAsm65Run(&sRun, 100);
	AssertLong(265, TestAsm65MPU(&sRun)->GetA());
	AssertLong(6, TestAsm65MPU(&sRun)->GetX());
	AssertIntHex(0x0001FFFF, TestAsm65MPU(&sRun)->GetS());
	AssertIntHex(265, sRun.pcContext->GetLong(0x2000));
	TestAsm65End(&sRun);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65Programs(void)
{
	BeginTests();

	TestAsm65ProgramsBlockMove();
	TestAsm65ProgramsVectorMove();
	TestAsm65ProgramsArithmeticShift();
	TestAsm65ProgramsSignExtend();
	TestAsm65ProgramsStatusToBit();
	TestAsm65ProgramsSubroutine();

	TestStatistics();
}
