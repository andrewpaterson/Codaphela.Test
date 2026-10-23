#include "TestLib/Assert.h"
#include "TestAsm65Context.h"


#define RELOCATE_DESTINATION	0x8000
#define RELOCATE_ORIGIN			0x0200
#define RELOCATE_SUM			0x0208
#define RELOCATE_FIBONACCI		0x0210
#define RELOCATE_WHERE			0x0218


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65RelocateRun(void)
{
	STestAsm65Run	sRun;
	uint32			uiOrigin;
	uint32			uiLength;
	uint32			uiWhere;
	uint32			i;
	int				iDifferent;

	//The loader copies the payload to 0000:8000 and it runs there.
	AssertTrue(TestAsm65BeginFile(&sRun, "Relocate.asm", 0x1000));
	AssertTrue(TestAsm65Run(&sRun, 10000) < 10000);
	uiOrigin = sRun.pcContext->GetLong(RELOCATE_ORIGIN);
	uiLength = TestAsm65MPU(&sRun)->GetV() - RELOCATE_DESTINATION;
	uiWhere = sRun.pcContext->GetLong(RELOCATE_WHERE);
	AssertTrue(uiOrigin > 0x1000);
	AssertTrue(uiLength > 0);
	iDifferent = 0;
	for (i = 0; i < uiLength; i++)
	{
		if (sRun.pcContext->GetByte(RELOCATE_DESTINATION + i) != sRun.pcContext->GetByte(uiOrigin + i))
		{
			iDifferent++;
		}
	}
	AssertInt(0, iDifferent);
	AssertInt(5050, sRun.pcContext->GetLong(RELOCATE_SUM));
	AssertInt(6765, sRun.pcContext->GetLong(RELOCATE_FIBONACCI));
	AssertTrue((uiWhere > RELOCATE_DESTINATION) && (uiWhere < RELOCATE_DESTINATION + uiLength));
	AssertTrue((TestAsm65MPU(&sRun)->GetProgramCounter() > RELOCATE_DESTINATION) && (TestAsm65MPU(&sRun)->GetProgramCounter() <= RELOCATE_DESTINATION + uiLength));
	TestAsm65End(&sRun);

	//The same payload run where it was assembled.
	AssertTrue(TestAsm65BeginFile(&sRun, "Relocate.asm", uiOrigin));
	AssertTrue(TestAsm65Run(&sRun, 10000) < 10000);
	AssertInt(5050, sRun.pcContext->GetLong(RELOCATE_SUM));
	AssertInt(6765, sRun.pcContext->GetLong(RELOCATE_FIBONACCI));
	AssertIntHex(uiWhere - RELOCATE_DESTINATION + uiOrigin, sRun.pcContext->GetLong(RELOCATE_WHERE));
	AssertIntHex(0, sRun.pcContext->GetLong(RELOCATE_ORIGIN));
	AssertTrue(TestAsm65MPU(&sRun)->GetProgramCounter() < RELOCATE_DESTINATION);
	TestAsm65End(&sRun);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65Relocate(void)
{
	BeginTests();

	TestAsm65RelocateRun();

	TestStatistics();
}
