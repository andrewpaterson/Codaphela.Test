#include "BaseLib/FileUtil.h"
#include "BaseLib/DiskFile.h"
#include "BaseLib/GlobalMemory.h"
#include "TestLib/Assert.h"
#include "StandardLib/ChunkFileNames.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChunkFileNamesWriting(void)
{
	CChunkFile			cChunkFile;
	CChunkFileNames		cChunkFileNames;
	CDiskFile*			pcDiskFile;
	CChunkFile			cTestFile;
	int					iIndex;
	CChars				szText;
	CFileUtil			cFileUtil;

	cFileUtil.RemoveDir("Output" _FS_ "ChunkFileNames");
	AssertTrue(cFileUtil.TouchDir("Output" _FS_ "ChunkFileNames"));

	pcDiskFile = DiskFile("Output" _FS_ "ChunkFileNames" _FS_ "FrenchToast.DRG");
	cChunkFile.Init(pcDiskFile);
	cChunkFileNames.Init(&cChunkFile);

	AssertTrue(cChunkFileNames.WriteOpen());

	cChunkFileNames.WriteChunkBegin("new/age/violet/Tempest");
	cChunkFileNames.WriteString("No man, Mr. President, thinks more highly than I do of the patriotism");
	cChunkFileNames.WriteChunkEnd();

	cChunkFileNames.WriteChunkBegin("new/age/shrinking/daisy/Sunlight");
	cChunkFileNames.WriteString("The question before the House is one of awful moment to this country.");
	cChunkFileNames.WriteChunkEnd();

	cChunkFileNames.WriteChunkBegin("new/age/shrinking/daisy/Pusher");
	cChunkFileNames.WriteString("We are apt to shut our eyes against a painful truth");
	cChunkFileNames.WriteChunkEnd();

	cChunkFileNames.WriteChunkBegin("new/age/violet/Forensics");
	cChunkFileNames.WriteString("Shall we try argument?");
	cChunkFileNames.WriteChunkEnd();

	cChunkFileNames.WriteChunkBegin("Unknown");
	cChunkFileNames.WriteString("Sir, we have been trying that for the last ten years.");
	cChunkFileNames.WriteChunkEnd();

	cChunkFileNames.WriteChunkBegin("last/time/in/Paris");
	cChunkFileNames.WriteString("There is no longer any room for hope.");
	cChunkFileNames.WriteChunkEnd();

	cChunkFileNames.WriteChunkBegin("last/time/in/world/on/See");
	cChunkFileNames.WriteString("But when shall we be stronger?");
	cChunkFileNames.WriteChunkEnd();

	cChunkFileNames.WriteChunkBegin("last/Schism");
	cChunkFileNames.WriteString("Finally! Something with Doom!");
	cChunkFileNames.WriteChunkEnd();

	cChunkFileNames.WriteChunkBegin("last/Tragic");
	cChunkFileNames.WriteString("If you give me a one word text back, I'm gonna give you the same");
	cChunkFileNames.WriteChunkEnd();

	cChunkFileNames.WriteChunkBegin("Final");
	cChunkFileNames.WriteString("Countdown");
	cChunkFileNames.WriteChunkEnd();

	cChunkFileNames.WriteChunkBegin("new/really/Final");
	cChunkFileNames.WriteString("Seriously, how is it not possible to find text on the internet.");
	cChunkFileNames.WriteChunkEnd();

	AssertTrue(cChunkFileNames.WriteClose());
	cChunkFileNames.Kill();
	cChunkFile.Kill();

	//What's expected:
	//
	// 1:   new/age/violet/Tempest
	// 1:   new/age/shrinking/daisy/Sunlight
	// 1:   new/age/shrinking/daisy/Pusher
	// 1:   new/age/violet/Forensics
	// 2:   Unknown
	// 3:   last/time/in/world/on/See
	// 3:   last/Schism
	// 3:   last/Tragic
	// 4:   Final
	// 5:   new/really/Final

	pcDiskFile = DiskFile("Output" _FS_ "ChunkFileNames" _FS_ "FrenchToast.DRG");
	cTestFile.Init(pcDiskFile);
	AssertTrue(cTestFile.ReadOpen());

	AssertInt(5, cTestFile.GetNumChunks());

	iIndex = cTestFile.FindFirstChunkWithName("new");
	AssertInt(0, iIndex);
	AssertTrue(cTestFile.ReadChunkBegin(iIndex));
	AssertInt(1, cTestFile.GetNumChunks());

	iIndex = cTestFile.FindFirstChunkWithName("age");
	AssertInt(0, iIndex);
	AssertTrue(cTestFile.ReadChunkBegin(iIndex));
	AssertInt(3, cTestFile.GetNumChunks());

	iIndex = cTestFile.FindFirstChunkWithName("violet");
	AssertInt(0, iIndex);
	AssertTrue(cTestFile.ReadChunkBegin(iIndex));
	AssertInt(1, cTestFile.GetNumChunks());

	iIndex = cTestFile.FindFirstChunkWithName("Tempest");
	AssertInt(0, iIndex);
	AssertTrue(cTestFile.ReadChunkBegin(iIndex));
	AssertInt(0, cTestFile.GetNumChunks());
	AssertTrue(szText.ReadChars(&cTestFile));
	AssertString("No man, Mr. President, thinks more highly than I do of the patriotism", szText.Text());
	szText.Kill();

	AssertTrue(cTestFile.ReadChunkEnd(2));

	iIndex = cTestFile.FindFirstChunkWithName("shrinking");
	AssertInt(1, iIndex);
	AssertTrue(cTestFile.ReadChunkBegin(iIndex));
	AssertInt(1, cTestFile.GetNumChunks());

	iIndex = cTestFile.FindFirstChunkWithName("daisy");
	AssertInt(0, iIndex);
	AssertTrue(cTestFile.ReadChunkBegin(iIndex));
	AssertInt(2, cTestFile.GetNumChunks());

	iIndex = cTestFile.FindFirstChunkWithName("Sunlight");
	AssertInt(0, iIndex);
	cTestFile.ReadChunkBegin(iIndex);
	AssertInt(0, cTestFile.GetNumChunks());
	AssertTrue(szText.ReadChars(&cTestFile));
	AssertString("The question before the House is one of awful moment to this country.", szText.Text());
	szText.Kill();
	AssertTrue(cTestFile.ReadChunkEnd());

	iIndex = cTestFile.FindFirstChunkWithName("Pusher");
	AssertInt(1, iIndex);
	AssertTrue(cTestFile.ReadChunkBegin(iIndex));
	AssertInt(0, cTestFile.GetNumChunks());
	AssertTrue(szText.ReadChars(&cTestFile));
	AssertString("We are apt to shut our eyes against a painful truth", szText.Text());
	szText.Kill();
	AssertTrue(cTestFile.ReadChunkEnd(3));

	iIndex = cTestFile.FindFirstChunkWithName("violet");
	AssertInt(0, iIndex);
	iIndex = cTestFile.FindNextChunkWithName();
	AssertInt(2, iIndex);
	AssertTrue(cTestFile.ReadChunkBegin(iIndex));
	AssertInt(1, cTestFile.GetNumChunks());

	iIndex = cTestFile.FindFirstChunkWithName("Forensics");
	AssertInt(0, iIndex);
	AssertTrue(cTestFile.ReadChunkBegin(iIndex));
	AssertInt(0, cTestFile.GetNumChunks());
	AssertTrue(szText.ReadChars(&cTestFile));
	AssertString("Shall we try argument?", szText.Text());
	szText.Kill();
	AssertTrue(cTestFile.ReadChunkEnd(4));

	iIndex = cTestFile.FindFirstChunkWithName("Unknown");
	AssertInt(1, iIndex);
	AssertTrue(cTestFile.ReadChunkBegin(iIndex));
	AssertInt(0, cTestFile.GetNumChunks());
	AssertTrue(szText.ReadChars(&cTestFile));
	AssertString("Sir, we have been trying that for the last ten years.", szText.Text());
	szText.Kill();
	AssertTrue(cTestFile.ReadChunkEnd());
	AssertInt(5, cTestFile.GetNumChunks());

	iIndex = cTestFile.FindFirstChunkWithName("Final");
	AssertInt(3, iIndex);
	AssertTrue(cTestFile.ReadChunkBegin(iIndex));
	AssertInt(0, cTestFile.GetNumChunks());
	AssertTrue(szText.ReadChars(&cTestFile));
	AssertString("Countdown", szText.Text());
	szText.Kill();
	AssertTrue(cTestFile.ReadChunkEnd());
	AssertInt(5, cTestFile.GetNumChunks());

	iIndex = cTestFile.FindFirstChunkWithName("new");
	AssertInt(0, iIndex);
	iIndex = cTestFile.FindNextChunkWithName();
	AssertInt(4, iIndex);
	AssertTrue(cTestFile.ReadChunkBegin(iIndex));
	AssertInt(1, cTestFile.GetNumChunks());

	iIndex = cTestFile.FindFirstChunkWithName("really");
	AssertInt(0, iIndex);
	AssertTrue(cTestFile.ReadChunkBegin(iIndex));
	AssertInt(1, cTestFile.GetNumChunks());
	
	iIndex = cTestFile.FindFirstChunkWithName("Final");
	AssertInt(0, iIndex);
	AssertTrue(cTestFile.ReadChunkBegin(iIndex));
	AssertInt(0, cTestFile.GetNumChunks());
	AssertTrue(szText.ReadChars(&cTestFile));
	AssertString("Seriously, how is it not possible to find text on the internet.", szText.Text());
	szText.Kill();
	AssertTrue(cTestFile.ReadChunkEnd(3));
	AssertInt(5, cTestFile.GetNumChunks());

	cTestFile.ReadClose();
	cTestFile.Kill();

	cFileUtil.RemoveDir("Output" _FS_ "ChunkFileNames");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChunkFileNamesReading(void)
{
	CChunkFile			cChunkFile;
	CChunkFileNames		cChunkFileNames;
	CDiskFile*			pcDiskFile;
	CChars				szText;

	pcDiskFile = DiskFile("Input" _FS_ "FrenchToast.DRG");
	cChunkFile.Init(pcDiskFile);
	cChunkFileNames.Init(&cChunkFile);

	AssertTrue(cChunkFileNames.ReadOpen());

	AssertTrue(cChunkFileNames.ReadChunkBegin("new/age/violet/Tempest"));
	AssertTrue(szText.ReadChars(&cChunkFileNames));
	AssertString("No man, Mr. President, thinks more highly than I do of the patriotism", szText.Text());
	AssertTrue(cChunkFileNames.ReadChunkEnd());

	AssertFalse(cChunkFileNames.ReadChunkBegin("new/age/Duke"));

	AssertTrue(cChunkFileNames.ReadChunkBegin("new/age/shrinking/daisy/Sunlight"));
	AssertTrue(szText.ReadChars(&cChunkFileNames));
	AssertString("The question before the House is one of awful moment to this country.", szText.Text());
	AssertTrue(cChunkFileNames.ReadChunkEnd());

	AssertFalse(cChunkFileNames.ReadChunkBegin("new/age/Duke"));

	AssertTrue(cChunkFileNames.ReadChunkBegin("new/age/shrinking/daisy/Pusher"));
	AssertTrue(szText.ReadChars(&cChunkFileNames));
	AssertString("We are apt to shut our eyes against a painful truth", szText.Text());
	AssertTrue(cChunkFileNames.ReadChunkEnd());

	AssertTrue(cChunkFileNames.ReadChunkBegin("new/age/violet/Forensics"));
	AssertTrue(szText.ReadChars(&cChunkFileNames));
	AssertString("Shall we try argument?", szText.Text());
	AssertTrue(cChunkFileNames.ReadChunkEnd());

	AssertTrue(cChunkFileNames.ReadChunkBegin("Unknown"));
	AssertTrue(szText.ReadChars(&cChunkFileNames));
	AssertString("Sir, we have been trying that for the last ten years.", szText.Text());
	AssertTrue(cChunkFileNames.ReadChunkEnd());

	AssertTrue(cChunkFileNames.ReadChunkBegin("last/time/in/Paris"));
	AssertTrue(szText.ReadChars(&cChunkFileNames));
	AssertString("There is no longer any room for hope.", szText.Text());
	AssertTrue(cChunkFileNames.ReadChunkEnd());

	AssertTrue(cChunkFileNames.ReadChunkBegin("last/time/in/world/on/See"));
	AssertTrue(szText.ReadChars(&cChunkFileNames));
	AssertString("But when shall we be stronger?", szText.Text());
	AssertTrue(cChunkFileNames.ReadChunkEnd());

	AssertTrue(cChunkFileNames.ReadChunkBegin("last/Schism"));
	AssertTrue(szText.ReadChars(&cChunkFileNames));
	AssertString("Finally! Something with Doom!", szText.Text());
	AssertTrue(cChunkFileNames.ReadChunkEnd());

	AssertTrue(cChunkFileNames.ReadChunkBegin("last/Tragic"));
	AssertTrue(szText.ReadChars(&cChunkFileNames));
	AssertString("If you give me a one word text back, I'm gonna give you the same", szText.Text());
	AssertTrue(cChunkFileNames.ReadChunkEnd());

	AssertTrue(cChunkFileNames.ReadChunkBegin("Final"));
	AssertTrue(szText.ReadChars(&cChunkFileNames));
	AssertString("Countdown", szText.Text());
	AssertTrue(cChunkFileNames.ReadChunkEnd());

	AssertTrue(cChunkFileNames.ReadChunkBegin("new/really/Final"));
	AssertTrue(szText.ReadChars(&cChunkFileNames));
	AssertString("Seriously, how is it not possible to find text on the internet.", szText.Text());
	AssertTrue(cChunkFileNames.ReadChunkEnd());

	AssertFalse(cChunkFileNames.ReadChunkBegin(""));
	AssertFalse(cChunkFileNames.ReadChunkBegin("CCC//XX/xx"));
	AssertFalse(cChunkFileNames.ReadChunkBegin(NULL));
	AssertFalse(cChunkFileNames.ReadChunkBegin("/"));

	AssertTrue(cChunkFileNames.ReadChunkBegin("new/age/shrinking/daisy/Sunlight"));
	AssertTrue(szText.ReadChars(&cChunkFileNames));
	AssertString("The question before the House is one of awful moment to this country.", szText.Text());
	AssertTrue(cChunkFileNames.ReadChunkEnd());

	AssertTrue(cChunkFileNames.ReadChunkBegin("new/age/violet/Tempest"));
	AssertTrue(szText.ReadChars(&cChunkFileNames));
	AssertString("No man, Mr. President, thinks more highly than I do of the patriotism", szText.Text());
	AssertTrue(cChunkFileNames.ReadChunkEnd());

	AssertTrue(cChunkFileNames.ReadChunkBegin("new/age/shrinking/daisy/Pusher"));
	AssertTrue(szText.ReadChars(&cChunkFileNames));
	AssertString("We are apt to shut our eyes against a painful truth", szText.Text());
	AssertTrue(cChunkFileNames.ReadChunkEnd());

	AssertTrue(cChunkFileNames.ReadChunkBegin("last/Schism"));
	AssertTrue(szText.ReadChars(&cChunkFileNames));
	AssertString("Finally! Something with Doom!", szText.Text());
	AssertTrue(cChunkFileNames.ReadChunkEnd());

	AssertTrue(cChunkFileNames.ReadChunkBegin("new/age/violet/Forensics"));
	AssertTrue(szText.ReadChars(&cChunkFileNames));
	AssertString("Shall we try argument?", szText.Text());
	AssertTrue(cChunkFileNames.ReadChunkEnd());

	AssertTrue(cChunkFileNames.ReadChunkBegin("last/Tragic"));
	AssertTrue(szText.ReadChars(&cChunkFileNames));
	AssertString("If you give me a one word text back, I'm gonna give you the same", szText.Text());
	AssertTrue(cChunkFileNames.ReadChunkEnd());

	AssertTrue(cChunkFileNames.ReadChunkBegin("new/really/Final"));
	AssertTrue(szText.ReadChars(&cChunkFileNames));
	AssertString("Seriously, how is it not possible to find text on the internet.", szText.Text());
	AssertTrue(cChunkFileNames.ReadChunkEnd());

	AssertTrue(cChunkFileNames.ReadChunkBegin("Final"));
	AssertTrue(szText.ReadChars(&cChunkFileNames));
	AssertString("Countdown", szText.Text());
	AssertTrue(cChunkFileNames.ReadChunkEnd());

	AssertTrue(cChunkFileNames.ReadChunkBegin("last/time/in/world/on/See"));
	AssertTrue(szText.ReadChars(&cChunkFileNames));
	AssertString("But when shall we be stronger?", szText.Text());
	AssertTrue(cChunkFileNames.ReadChunkEnd());
	
	AssertTrue(cChunkFileNames.ReadChunkBegin("last/time/in/Paris"));
	AssertTrue(szText.ReadChars(&cChunkFileNames));
	AssertString("There is no longer any room for hope.", szText.Text());
	AssertTrue(cChunkFileNames.ReadChunkEnd());

	AssertTrue(cChunkFileNames.ReadChunkBegin("Unknown"));
	AssertTrue(szText.ReadChars(&cChunkFileNames));
	AssertString("Sir, we have been trying that for the last ten years.", szText.Text());
	AssertTrue(cChunkFileNames.ReadChunkEnd());

	cChunkFileNames.ReadClose();
	cChunkFileNames.Kill();
	cChunkFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChunkFileNamesNameIteration(void)
{
	CChunkFile				cChunkFile;
	CChunkFileNames			cChunkFileNames;
	CDiskFile*				pcDiskFile;
	SChunkFileNameIterator	sIter;
	char*					szName;

	pcDiskFile = DiskFile("Input" _FS_ "FrenchToast.DRG");
	cChunkFile.Init(pcDiskFile);
	cChunkFileNames.Init(&cChunkFile);

	cChunkFileNames.ReadOpen();


	szName = cChunkFileNames.StartNameIteration(&sIter);
	AssertString("new/age/violet/Tempest", szName);

	szName = cChunkFileNames.IterateName(&sIter);
	AssertString("new/age/shrinking/daisy/Sunlight", szName);

	szName = cChunkFileNames.IterateName(&sIter);
	AssertString("new/age/shrinking/daisy/Pusher", szName);

	szName = cChunkFileNames.IterateName(&sIter);
	AssertString("new/age/violet/Forensics", szName);

	szName = cChunkFileNames.IterateName(&sIter);
	AssertString("Unknown", szName);
	
	szName = cChunkFileNames.IterateName(&sIter);
	AssertString("last/time/in/Paris", szName);

	szName = cChunkFileNames.IterateName(&sIter);
	AssertString("last/time/in/world/on/See", szName);

	szName = cChunkFileNames.IterateName(&sIter);
	AssertString("last/Schism", szName);

	szName = cChunkFileNames.IterateName(&sIter);
	AssertString("last/Tragic", szName);

	szName = cChunkFileNames.IterateName(&sIter);
	AssertString("Final", szName);

	szName = cChunkFileNames.IterateName(&sIter);
	AssertString("new/really/Final", szName);

	szName = cChunkFileNames.IterateName(&sIter);
	AssertNull(szName);

	cChunkFileNames.StopIteration(&sIter);

	cChunkFileNames.ReadClose();
	cChunkFileNames.Kill();
	cChunkFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChunkFileNames(void)
{
	BeginTests();
	MemoryInit();

	TestChunkFileNamesWriting();
	TestChunkFileNamesReading();
	TestChunkFileNamesNameIteration();

	MemoryKill();
	TestStatistics();
}
