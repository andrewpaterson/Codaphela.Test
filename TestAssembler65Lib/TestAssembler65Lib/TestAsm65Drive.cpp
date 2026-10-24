#include "BaseLib/MemoryDrive.h"
#include "TestLib/Assert.h"
#include "TestAsm65Context.h"


#define DRIVE_SECTORS		16
#define DRIVE_SECTOR_SIZE	512


//////////////////////////////////////////////////////////////////////////
//
// A drive whose bytes are their sector number times 7 plus their offset.
//
//////////////////////////////////////////////////////////////////////////
static void TestAsm65DriveInit(CMemoryDrive* pcDrive)
{
	uint8*	puiData;
	size	i;

	pcDrive->Init(DRIVE_SECTORS * DRIVE_SECTOR_SIZE, DRIVE_SECTOR_SIZE);
	puiData = (uint8*)pcDrive->GetMemory();
	for (i = 0; i < DRIVE_SECTORS * DRIVE_SECTOR_SIZE; i++)
	{
		puiData[i] = (uint8)((i / DRIVE_SECTOR_SIZE) * 7 + i);
	}
}


//////////////////////////////////////////////////////////////////////////
//
// A program that runs one drive command (szCommand is 1 or 2) and stops with the
// status in A.
//
//////////////////////////////////////////////////////////////////////////
static void TestAsm65DriveCommand(CChars* pszSource, uint32 uiSector, uint32 uiAddress, uint32 uiCount, const char* szCommand)
{
	pszSource->Init(
		"	.org $1000\n"
		"	wtth (A, X), 32\n"
		"	cpy A, ");
	pszSource->Append(uiSector);
	pszSource->Append("\n	cpy [$FF0000], A\n	cpy A, ");
	pszSource->Append(uiAddress);
	pszSource->Append("\n	cpy [$FF0004], A\n	cpy A, ");
	pszSource->Append(uiCount);
	pszSource->Append("\n	cpy [$FF0008], A\n	cpy A, ");
	pszSource->Append(szCommand);
	pszSource->Append(
		"\n	cpy [$FF000C], A\n"
		"	cpy A, [$FF0010]\n"
		"	stp\n");
}


//////////////////////////////////////////////////////////////////////////
//
// A program reads sectors 2 and 3 into memory.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65DriveRead(void)
{
	CMemoryDrive	cDrive;
	STestAsm65Run	sRun;
	CChars			szSource;
	uint8*			puiData;
	size			i;
	int				iMismatches;

	TestAsm65DriveInit(&cDrive);
	TestAsm65DriveCommand(&szSource, 2, 0x20000, 2, "1");
	AssertTrue(TestAsm65Begin(&sRun, szSource.Text(), 0x1000));
	szSource.Kill();
	sRun.pcContext->SetDrive(&cDrive);
	AssertTrue(TestAsm65Run(&sRun, 1000) < 1000);

	AssertLong(0, TestAsm65MPU(&sRun)->GetA());
	AssertSize(1, sRun.pcContext->NumDriveReads());
	puiData = (uint8*)cDrive.GetMemory();
	iMismatches = 0;
	for (i = 0; i < 2 * DRIVE_SECTOR_SIZE; i++)
	{
		if (sRun.pcContext->GetByte(0x20000 + (uint32)i) != puiData[2 * DRIVE_SECTOR_SIZE + i])
		{
			iMismatches++;
		}
	}
	AssertInt(0, iMismatches);
	AssertInt(0, sRun.pcContext->GetByte(0x20000 + 2 * DRIVE_SECTOR_SIZE));
	AssertInt(DRIVE_SECTOR_SIZE, sRun.pcContext->GetLong(ASM65_DRIVE_BASE + ASM65_DRIVE_SECTOR_SIZE));

	TestAsm65End(&sRun);
	cDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A program writes memory to sector 5.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65DriveWrite(void)
{
	CMemoryDrive	cDrive;
	STestAsm65Run	sRun;
	CChars			szSource;
	uint8*			puiData;
	size			i;
	int				iMismatches;

	TestAsm65DriveInit(&cDrive);
	TestAsm65DriveCommand(&szSource, 5, 0x30000, 1, "2");
	AssertTrue(TestAsm65Begin(&sRun, szSource.Text(), 0x1000));
	szSource.Kill();
	sRun.pcContext->SetDrive(&cDrive);
	for (i = 0; i < DRIVE_SECTOR_SIZE; i++)
	{
		sRun.pcContext->SetByte(0x30000 + (uint32)i, (uint8)(255 - i));
	}
	AssertTrue(TestAsm65Run(&sRun, 1000) < 1000);

	AssertLong(0, TestAsm65MPU(&sRun)->GetA());
	AssertSize(0, sRun.pcContext->NumDriveReads());
	puiData = (uint8*)cDrive.GetMemory();
	iMismatches = 0;
	for (i = 0; i < DRIVE_SECTOR_SIZE; i++)
	{
		if (puiData[5 * DRIVE_SECTOR_SIZE + i] != (uint8)(255 - i))
		{
			iMismatches++;
		}
	}
	AssertInt(0, iMismatches);
	AssertInt((uint8)(6 * 7 * DRIVE_SECTOR_SIZE / DRIVE_SECTOR_SIZE + 6 * DRIVE_SECTOR_SIZE), puiData[6 * DRIVE_SECTOR_SIZE]);

	TestAsm65End(&sRun);
	cDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Sectors past the end of the drive and unknown commands fail with status 1.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65DriveErrors(void)
{
	CMemoryDrive	cDrive;
	STestAsm65Run	sRun;
	CChars			szSource;

	TestAsm65DriveInit(&cDrive);
	TestAsm65DriveCommand(&szSource, DRIVE_SECTORS - 1, 0x20000, 2, "1");
	AssertTrue(TestAsm65Begin(&sRun, szSource.Text(), 0x1000));
	szSource.Kill();
	sRun.pcContext->SetDrive(&cDrive);
	AssertTrue(TestAsm65Run(&sRun, 1000) < 1000);
	AssertLong(1, TestAsm65MPU(&sRun)->GetA());
	AssertInt(0, sRun.pcContext->GetByte(0x20000));
	TestAsm65End(&sRun);

	TestAsm65DriveCommand(&szSource, 0, 0x20000, 1, "3");
	AssertTrue(TestAsm65Begin(&sRun, szSource.Text(), 0x1000));
	szSource.Kill();
	sRun.pcContext->SetDrive(&cDrive);
	AssertTrue(TestAsm65Run(&sRun, 1000) < 1000);
	AssertLong(1, TestAsm65MPU(&sRun)->GetA());
	TestAsm65End(&sRun);

	cDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65Drive(void)
{
	BeginTests();

	TestAsm65DriveRead();
	TestAsm65DriveWrite();
	TestAsm65DriveErrors();

	TestStatistics();
}
