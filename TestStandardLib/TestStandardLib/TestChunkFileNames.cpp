#include "BaseLib/FileUtil.h"
#include "BaseLib/DiskFile.h"
#include "TestLib/Assert.h"
#include "StandardLib/ChunkFileNames.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestWriting(void)
{
	CChunkFileNames		cChunkFile;
	CDiskFile*			pcDiskFile;
	CChunkFile			cTestFile;
	int					iIndex;
	CChars				szText;

	pcDiskFile = DiskFile("Output/ChunkFileNames/FrenchToast.DRG");
	cChunkFile.Init(pcDiskFile);

	cChunkFile.WriteOpen();

	cChunkFile.WriteChunkBegin("new/age/violet/Tempest");
	cChunkFile.WriteString("No man, Mr. President, thinks more highly than I do of the patriotism");
	cChunkFile.WriteChunkEnd();

	cChunkFile.WriteChunkBegin("new/age/shrinking/daisy/Sunlight");
	cChunkFile.WriteString("The question before the House is one of awful moment to this country.");
	cChunkFile.WriteChunkEnd();

	cChunkFile.WriteChunkBegin("new/age/shrinking/daisy/Pusher");
	cChunkFile.WriteString("We are apt to shut our eyes against a painful truth");
	cChunkFile.WriteChunkEnd();

	cChunkFile.WriteChunkBegin("new/age/violet/Forensics");
	cChunkFile.WriteString("Shall we try argument?");
	cChunkFile.WriteChunkEnd();

	cChunkFile.WriteChunkBegin("Unknown");
	cChunkFile.WriteString("Sir, we have been trying that for the last ten years.");
	cChunkFile.WriteChunkEnd();

	cChunkFile.WriteChunkBegin("last/time/in/Paris");
	cChunkFile.WriteString("There is no longer any room for hope.");
	cChunkFile.WriteChunkEnd();

	cChunkFile.WriteChunkBegin("last/time/in/world/on/See");
	cChunkFile.WriteString("But when shall we be stronger?");
	cChunkFile.WriteChunkEnd();

	cChunkFile.WriteChunkBegin("last/Schism");
	cChunkFile.WriteString("Finally! Something with Doom!");
	cChunkFile.WriteChunkEnd();

	cChunkFile.WriteChunkBegin("last/Tragic");
	cChunkFile.WriteString("If you give me a one word text back, I'm gonna give you the same");
	cChunkFile.WriteChunkEnd();

	cChunkFile.WriteChunkBegin("Final");
	cChunkFile.WriteString("Countdown");
	cChunkFile.WriteChunkEnd();

	cChunkFile.WriteChunkBegin("new/really/Final");
	cChunkFile.WriteString("Seriously, how is it not possible to find text on the internet.");
	cChunkFile.WriteChunkEnd();

	cChunkFile.WriteClose();
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

	pcDiskFile = DiskFile("Output/ChunkFileNames/FrenchToast.DRG");
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
	AssertTrue(szText.ReadString(&cTestFile, FALSE));
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
	AssertTrue(szText.ReadString(&cTestFile, FALSE));
	AssertString("The question before the House is one of awful moment to this country.", szText.Text());
	szText.Kill();
	AssertTrue(cTestFile.ReadChunkEnd());

	iIndex = cTestFile.FindFirstChunkWithName("Pusher");
	AssertInt(1, iIndex);
	AssertTrue(cTestFile.ReadChunkBegin(iIndex));
	AssertInt(0, cTestFile.GetNumChunks());
	AssertTrue(szText.ReadString(&cTestFile, FALSE));
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
	AssertTrue(szText.ReadString(&cTestFile, FALSE));
	AssertString("Shall we try argument?", szText.Text());
	szText.Kill();
	AssertTrue(cTestFile.ReadChunkEnd(4));

	iIndex = cTestFile.FindFirstChunkWithName("Unknown");
	AssertInt(1, iIndex);
	AssertTrue(cTestFile.ReadChunkBegin(iIndex));
	AssertInt(0, cTestFile.GetNumChunks());
	AssertTrue(szText.ReadString(&cTestFile, FALSE));
	AssertString("Sir, we have been trying that for the last ten years.", szText.Text());
	szText.Kill();
	AssertTrue(cTestFile.ReadChunkEnd());
	AssertInt(5, cTestFile.GetNumChunks());

	iIndex = cTestFile.FindFirstChunkWithName("Final");
	AssertInt(3, iIndex);
	AssertTrue(cTestFile.ReadChunkBegin(iIndex));
	AssertInt(0, cTestFile.GetNumChunks());
	AssertTrue(szText.ReadString(&cTestFile, FALSE));
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
	AssertTrue(szText.ReadString(&cTestFile, FALSE));
	AssertString("Seriously, how is it not possible to find text on the internet.", szText.Text());
	szText.Kill();
	AssertTrue(cTestFile.ReadChunkEnd(3));
	AssertInt(5, cTestFile.GetNumChunks());

	cTestFile.ReadClose();
	cTestFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestReading(void)
{
	CChunkFileNames		cChunkFile;
	CDiskFile*			pcDiskFile;
	CChars				szText;

	pcDiskFile = DiskFile("Input/FrenchToast.DRG");
	cChunkFile.Init(pcDiskFile);

	cChunkFile.ReadOpen();

	AssertTrue(cChunkFile.ReadChunkBegin("new/age/violet/Tempest"));
	AssertTrue(szText.ReadString(&cChunkFile, FALSE));
	AssertString("No man, Mr. President, thinks more highly than I do of the patriotism", szText.Text());
	AssertTrue(cChunkFile.ReadChunkEnd());

	AssertFalse(cChunkFile.ReadChunkBegin("new/age/Duke"));

	AssertTrue(cChunkFile.ReadChunkBegin("new/age/shrinking/daisy/Sunlight"));
	AssertTrue(szText.ReadString(&cChunkFile, FALSE));
	AssertString("The question before the House is one of awful moment to this country.", szText.Text());
	AssertTrue(cChunkFile.ReadChunkEnd());

	AssertFalse(cChunkFile.ReadChunkBegin("new/age/Duke"));

	AssertTrue(cChunkFile.ReadChunkBegin("new/age/shrinking/daisy/Pusher"));
	AssertTrue(szText.ReadString(&cChunkFile, FALSE));
	AssertString("We are apt to shut our eyes against a painful truth", szText.Text());
	AssertTrue(cChunkFile.ReadChunkEnd());

	AssertTrue(cChunkFile.ReadChunkBegin("new/age/violet/Forensics"));
	AssertTrue(szText.ReadString(&cChunkFile, FALSE));
	AssertString("Shall we try argument?", szText.Text());
	AssertTrue(cChunkFile.ReadChunkEnd());

	AssertTrue(cChunkFile.ReadChunkBegin("Unknown"));
	AssertTrue(szText.ReadString(&cChunkFile, FALSE));
	AssertString("Sir, we have been trying that for the last ten years.", szText.Text());
	AssertTrue(cChunkFile.ReadChunkEnd());

	AssertTrue(cChunkFile.ReadChunkBegin("last/time/in/Paris"));
	AssertTrue(szText.ReadString(&cChunkFile, FALSE));
	AssertString("There is no longer any room for hope.", szText.Text());
	AssertTrue(cChunkFile.ReadChunkEnd());

	AssertTrue(cChunkFile.ReadChunkBegin("last/time/in/world/on/See"));
	AssertTrue(szText.ReadString(&cChunkFile, FALSE));
	AssertString("But when shall we be stronger?", szText.Text());
	AssertTrue(cChunkFile.ReadChunkEnd());

	AssertTrue(cChunkFile.ReadChunkBegin("last/Schism"));
	AssertTrue(szText.ReadString(&cChunkFile, FALSE));
	AssertString("Finally! Something with Doom!", szText.Text());
	AssertTrue(cChunkFile.ReadChunkEnd());

	AssertTrue(cChunkFile.ReadChunkBegin("last/Tragic"));
	AssertTrue(szText.ReadString(&cChunkFile, FALSE));
	AssertString("If you give me a one word text back, I'm gonna give you the same", szText.Text());
	AssertTrue(cChunkFile.ReadChunkEnd());

	AssertTrue(cChunkFile.ReadChunkBegin("Final"));
	AssertTrue(szText.ReadString(&cChunkFile, FALSE));
	AssertString("Countdown", szText.Text());
	AssertTrue(cChunkFile.ReadChunkEnd());

	AssertTrue(cChunkFile.ReadChunkBegin("new/really/Final"));
	AssertTrue(szText.ReadString(&cChunkFile, FALSE));
	AssertString("Seriously, how is it not possible to find text on the internet.", szText.Text());
	AssertTrue(cChunkFile.ReadChunkEnd());

	AssertFalse(cChunkFile.ReadChunkBegin(""));
	AssertFalse(cChunkFile.ReadChunkBegin("CCC//XX/xx"));
	AssertFalse(cChunkFile.ReadChunkBegin(NULL));
	AssertFalse(cChunkFile.ReadChunkBegin("/"));

	AssertTrue(cChunkFile.ReadChunkBegin("new/age/shrinking/daisy/Sunlight"));
	AssertTrue(szText.ReadString(&cChunkFile, FALSE));
	AssertString("The question before the House is one of awful moment to this country.", szText.Text());
	AssertTrue(cChunkFile.ReadChunkEnd());

	AssertTrue(cChunkFile.ReadChunkBegin("new/age/violet/Tempest"));
	AssertTrue(szText.ReadString(&cChunkFile, FALSE));
	AssertString("No man, Mr. President, thinks more highly than I do of the patriotism", szText.Text());
	AssertTrue(cChunkFile.ReadChunkEnd());

	AssertTrue(cChunkFile.ReadChunkBegin("new/age/shrinking/daisy/Pusher"));
	AssertTrue(szText.ReadString(&cChunkFile, FALSE));
	AssertString("We are apt to shut our eyes against a painful truth", szText.Text());
	AssertTrue(cChunkFile.ReadChunkEnd());

	AssertTrue(cChunkFile.ReadChunkBegin("last/Schism"));
	AssertTrue(szText.ReadString(&cChunkFile, FALSE));
	AssertString("Finally! Something with Doom!", szText.Text());
	AssertTrue(cChunkFile.ReadChunkEnd());

	AssertTrue(cChunkFile.ReadChunkBegin("new/age/violet/Forensics"));
	AssertTrue(szText.ReadString(&cChunkFile, FALSE));
	AssertString("Shall we try argument?", szText.Text());
	AssertTrue(cChunkFile.ReadChunkEnd());

	AssertTrue(cChunkFile.ReadChunkBegin("last/Tragic"));
	AssertTrue(szText.ReadString(&cChunkFile, FALSE));
	AssertString("If you give me a one word text back, I'm gonna give you the same", szText.Text());
	AssertTrue(cChunkFile.ReadChunkEnd());

	AssertTrue(cChunkFile.ReadChunkBegin("new/really/Final"));
	AssertTrue(szText.ReadString(&cChunkFile, FALSE));
	AssertString("Seriously, how is it not possible to find text on the internet.", szText.Text());
	AssertTrue(cChunkFile.ReadChunkEnd());

	AssertTrue(cChunkFile.ReadChunkBegin("Final"));
	AssertTrue(szText.ReadString(&cChunkFile, FALSE));
	AssertString("Countdown", szText.Text());
	AssertTrue(cChunkFile.ReadChunkEnd());

	AssertTrue(cChunkFile.ReadChunkBegin("last/time/in/world/on/See"));
	AssertTrue(szText.ReadString(&cChunkFile, FALSE));
	AssertString("But when shall we be stronger?", szText.Text());
	AssertTrue(cChunkFile.ReadChunkEnd());
	
	AssertTrue(cChunkFile.ReadChunkBegin("last/time/in/Paris"));
	AssertTrue(szText.ReadString(&cChunkFile, FALSE));
	AssertString("There is no longer any room for hope.", szText.Text());
	AssertTrue(cChunkFile.ReadChunkEnd());

	AssertTrue(cChunkFile.ReadChunkBegin("Unknown"));
	AssertTrue(szText.ReadString(&cChunkFile, FALSE));
	AssertString("Sir, we have been trying that for the last ten years.", szText.Text());
	AssertTrue(cChunkFile.ReadChunkEnd());

	cChunkFile.ReadClose();
	cChunkFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNameIteration(void)
{
	CChunkFileNames			cChunkFile;
	CDiskFile*				pcDiskFile;
	SChunkFileNameIterator	sIter;
	char*					szName;

	pcDiskFile = DiskFile("Input/FrenchToast.DRG");
	cChunkFile.Init(pcDiskFile);

	cChunkFile.ReadOpen();


	szName = cChunkFile.StartNameIteration(&sIter);
	AssertString("new/age/violet/Tempest", szName);

	szName = cChunkFile.IterateName(&sIter);
	AssertString("new/age/shrinking/daisy/Sunlight", szName);

	szName = cChunkFile.IterateName(&sIter);
	AssertString("new/age/shrinking/daisy/Pusher", szName);

	szName = cChunkFile.IterateName(&sIter);
	AssertString("new/age/violet/Forensics", szName);

	szName = cChunkFile.IterateName(&sIter);
	AssertString("Unknown", szName);
	
	szName = cChunkFile.IterateName(&sIter);
	AssertString("last/time/in/Paris", szName);

	szName = cChunkFile.IterateName(&sIter);
	AssertString("last/time/in/world/on/See", szName);

	szName = cChunkFile.IterateName(&sIter);
	AssertString("last/Schism", szName);

	szName = cChunkFile.IterateName(&sIter);
	AssertString("last/Tragic", szName);

	szName = cChunkFile.IterateName(&sIter);
	AssertString("Final", szName);

	szName = cChunkFile.IterateName(&sIter);
	AssertString("new/really/Final", szName);

	szName = cChunkFile.IterateName(&sIter);
	AssertNull(szName);

	cChunkFile.StopIteration(&sIter);

	cChunkFile.ReadClose();
	cChunkFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChunkFileNames(void)
{
	CFileUtil	cFileUtil;

	cFileUtil.RemoveDir("Output");
	cFileUtil.MakeDir("Output/ChunkFileNames");

	BeginTests();

	TestWriting();
	TestReading();
	TestNameIteration();

	TestStatistics();
	cFileUtil.RemoveDir("Output");
}
