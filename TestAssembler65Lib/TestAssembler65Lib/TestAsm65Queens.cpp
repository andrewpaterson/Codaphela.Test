#include "BaseLib/Chars.h"
#include "TestLib/Assert.h"
#include "TestAsm65Context.h"


#define QUEENS_COUNT	0x0100


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static void AssertQueens(int iN, int iSolutions)
{
	STestAsm65Run	sRun;
	CChars			szSource;

	szSource.Init("N = ");
	szSource.Append(iN);
	szSource.AppendNewLine();
	TestAsm65ReadSource(&szSource, "Queens.asm");
	AssertTrue(TestAsm65Begin(&sRun, szSource.Text(), 0x1000));
	AssertTrue(TestAsm65Run(&sRun, 1000000) < 1000000);
	AssertInt(iSolutions, sRun.pcContext->GetLong(QUEENS_COUNT));
	AssertIntHex(0x0001FFFF, TestAsm65MPU(&sRun)->GetS());
	TestAsm65End(&sRun);
	szSource.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65QueensSolutions(void)
{
	static const int	aiSolutions[9] = { 0, 1, 0, 0, 2, 10, 4, 40, 92 };
	int					iN;

	for (iN = 1; iN <= 8; iN++)
	{
		AssertQueens(iN, aiSolutions[iN]);
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65Queens(void)
{
	BeginTests();

	TestAsm65QueensSolutions();

	TestStatistics();
}
