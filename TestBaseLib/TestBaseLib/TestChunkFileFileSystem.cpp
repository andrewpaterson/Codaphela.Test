#include "BaseLib/FileUtil.h"
#include "BaseLib/DiskFile.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/ChunkFileFileSystem.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChunkFileFileSystemWriting(void)
{
	CChunkFile				cChunkFile;
	CChunkFileFileSystem	cChunkFileFileSystem;
	CDiskFile*				pcDiskFile;
	CChunkFile				cTestFile;
	int						iIndex;
	CChars					szText;
	CFileUtil				cFileUtil;

	cFileUtil.RemoveDir("Output" _FS_ "ChunkFileFileSystem");
	AssertTrue(cFileUtil.TouchDir("Output" _FS_ "ChunkFileFileSystem"));

	pcDiskFile = DiskFile("Output" _FS_ "ChunkFileFileSystem" _FS_ "FrenchToast.DRG");
	cChunkFile.Init(pcDiskFile);
	cChunkFileFileSystem.Init(&cChunkFile);

	AssertTrue(cChunkFileFileSystem.WriteOpen());

	cChunkFileFileSystem.WriteChunkBegin("new/age/violet/Tempest");
	cChunkFileFileSystem.WriteString("No man, Mr. President, thinks more highly than I do of the patriotism");
	cChunkFileFileSystem.WriteChunkEnd();

	cChunkFileFileSystem.WriteChunkBegin("new/age/shrinking/daisy/Sunlight");
	cChunkFileFileSystem.WriteString("The question before the House is one of awful moment to this country.");
	cChunkFileFileSystem.WriteChunkEnd();

	cChunkFileFileSystem.WriteChunkBegin("new/age/shrinking/daisy/Pusher");
	cChunkFileFileSystem.WriteString("We are apt to shut our eyes against a painful truth");
	cChunkFileFileSystem.WriteChunkEnd();

	cChunkFileFileSystem.WriteChunkBegin("new/age/violet/Forensics");
	cChunkFileFileSystem.WriteString("Shall we try argument?");
	cChunkFileFileSystem.WriteChunkEnd();

	cChunkFileFileSystem.WriteChunkBegin("Unknown");
	cChunkFileFileSystem.WriteString("Sir, we have been trying that for the last ten years.");
	cChunkFileFileSystem.WriteChunkEnd();

	cChunkFileFileSystem.WriteChunkBegin("last/time/in/Paris");
	cChunkFileFileSystem.WriteString("There is no longer any room for hope.");
	cChunkFileFileSystem.WriteChunkEnd();

	cChunkFileFileSystem.WriteChunkBegin("last/time/in/world/on/See");
	cChunkFileFileSystem.WriteString("But when shall we be stronger?");
	cChunkFileFileSystem.WriteChunkEnd();

	cChunkFileFileSystem.WriteChunkBegin("last/Schism");
	cChunkFileFileSystem.WriteString("Finally! Something with Doom!");
	cChunkFileFileSystem.WriteChunkEnd();

	cChunkFileFileSystem.WriteChunkBegin("last/Tragic");
	cChunkFileFileSystem.WriteString("If you give me a one word text back, I'm gonna give you the same");
	cChunkFileFileSystem.WriteChunkEnd();

	cChunkFileFileSystem.WriteChunkBegin("Final");
	cChunkFileFileSystem.WriteString("Countdown");
	cChunkFileFileSystem.WriteChunkEnd();

	cChunkFileFileSystem.WriteChunkBegin("new/really/Final");
	cChunkFileFileSystem.WriteString("Seriously, how is it not possible to find text on the internet.");
	cChunkFileFileSystem.WriteChunkEnd();

	AssertTrue(cChunkFileFileSystem.WriteClose());
	cChunkFileFileSystem.Kill();
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

	pcDiskFile = DiskFile("Output" _FS_ "ChunkFileFileSystem" _FS_ "FrenchToast.DRG");
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

	cFileUtil.RemoveDir("Output" _FS_ "ChunkFileFileSystem");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChunkFileFileSystemReading(void)
{
	CChunkFile				cChunkFile;
	CChunkFileFileSystem	cChunkFileFileSystem;
	CDiskFile*				pcDiskFile;
	CChars					szText;

	pcDiskFile = DiskFile("Input" _FS_ "FrenchToast.DRG");
	cChunkFile.Init(pcDiskFile);
	cChunkFileFileSystem.Init(&cChunkFile);

	AssertTrue(cChunkFileFileSystem.ReadOpen());

	AssertTrue(cChunkFileFileSystem.ReadChunkBegin("new/age/violet/Tempest"));
	AssertTrue(szText.ReadChars(&cChunkFileFileSystem));
	AssertString("No man, Mr. President, thinks more highly than I do of the patriotism", szText.Text());
	AssertTrue(cChunkFileFileSystem.ReadChunkEnd());
	szText.Kill();

	AssertFalse(cChunkFileFileSystem.ReadChunkBegin("new/age/Duke"));

	AssertTrue(cChunkFileFileSystem.ReadChunkBegin("new/age/shrinking/daisy/Sunlight"));
	AssertTrue(szText.ReadChars(&cChunkFileFileSystem));
	AssertString("The question before the House is one of awful moment to this country.", szText.Text());
	AssertTrue(cChunkFileFileSystem.ReadChunkEnd());
	szText.Kill();

	AssertFalse(cChunkFileFileSystem.ReadChunkBegin("new/age/Duke"));

	AssertTrue(cChunkFileFileSystem.ReadChunkBegin("new/age/shrinking/daisy/Pusher"));
	AssertTrue(szText.ReadChars(&cChunkFileFileSystem));
	AssertString("We are apt to shut our eyes against a painful truth", szText.Text());
	AssertTrue(cChunkFileFileSystem.ReadChunkEnd());
	szText.Kill();

	AssertTrue(cChunkFileFileSystem.ReadChunkBegin("new/age/violet/Forensics"));
	AssertTrue(szText.ReadChars(&cChunkFileFileSystem));
	AssertString("Shall we try argument?", szText.Text());
	AssertTrue(cChunkFileFileSystem.ReadChunkEnd());
	szText.Kill();

	AssertTrue(cChunkFileFileSystem.ReadChunkBegin("Unknown"));
	AssertTrue(szText.ReadChars(&cChunkFileFileSystem));
	AssertString("Sir, we have been trying that for the last ten years.", szText.Text());
	AssertTrue(cChunkFileFileSystem.ReadChunkEnd());
	szText.Kill();

	AssertTrue(cChunkFileFileSystem.ReadChunkBegin("last/time/in/Paris"));
	AssertTrue(szText.ReadChars(&cChunkFileFileSystem));
	AssertString("There is no longer any room for hope.", szText.Text());
	AssertTrue(cChunkFileFileSystem.ReadChunkEnd());
	szText.Kill();

	AssertTrue(cChunkFileFileSystem.ReadChunkBegin("last/time/in/world/on/See"));
	AssertTrue(szText.ReadChars(&cChunkFileFileSystem));
	AssertString("But when shall we be stronger?", szText.Text());
	AssertTrue(cChunkFileFileSystem.ReadChunkEnd());
	szText.Kill();

	AssertTrue(cChunkFileFileSystem.ReadChunkBegin("last/Schism"));
	AssertTrue(szText.ReadChars(&cChunkFileFileSystem));
	AssertString("Finally! Something with Doom!", szText.Text());
	AssertTrue(cChunkFileFileSystem.ReadChunkEnd());
	szText.Kill();

	AssertTrue(cChunkFileFileSystem.ReadChunkBegin("last/Tragic"));
	AssertTrue(szText.ReadChars(&cChunkFileFileSystem));
	AssertString("If you give me a one word text back, I'm gonna give you the same", szText.Text());
	AssertTrue(cChunkFileFileSystem.ReadChunkEnd());
	szText.Kill();

	AssertTrue(cChunkFileFileSystem.ReadChunkBegin("Final"));
	AssertTrue(szText.ReadChars(&cChunkFileFileSystem));
	AssertString("Countdown", szText.Text());
	AssertTrue(cChunkFileFileSystem.ReadChunkEnd());
	szText.Kill();

	AssertTrue(cChunkFileFileSystem.ReadChunkBegin("new/really/Final"));
	AssertTrue(szText.ReadChars(&cChunkFileFileSystem));
	AssertString("Seriously, how is it not possible to find text on the internet.", szText.Text());
	AssertTrue(cChunkFileFileSystem.ReadChunkEnd());
	szText.Kill();

	AssertFalse(cChunkFileFileSystem.ReadChunkBegin(""));
	AssertFalse(cChunkFileFileSystem.ReadChunkBegin("CCC//XX/xx"));
	AssertFalse(cChunkFileFileSystem.ReadChunkBegin(NULL));
	AssertFalse(cChunkFileFileSystem.ReadChunkBegin("/"));

	AssertTrue(cChunkFileFileSystem.ReadChunkBegin("new/age/shrinking/daisy/Sunlight"));
	AssertTrue(szText.ReadChars(&cChunkFileFileSystem));
	AssertString("The question before the House is one of awful moment to this country.", szText.Text());
	AssertTrue(cChunkFileFileSystem.ReadChunkEnd());
	szText.Kill();

	AssertTrue(cChunkFileFileSystem.ReadChunkBegin("new/age/violet/Tempest"));
	AssertTrue(szText.ReadChars(&cChunkFileFileSystem));
	AssertString("No man, Mr. President, thinks more highly than I do of the patriotism", szText.Text());
	AssertTrue(cChunkFileFileSystem.ReadChunkEnd());
	szText.Kill();

	AssertTrue(cChunkFileFileSystem.ReadChunkBegin("new/age/shrinking/daisy/Pusher"));
	AssertTrue(szText.ReadChars(&cChunkFileFileSystem));
	AssertString("We are apt to shut our eyes against a painful truth", szText.Text());
	AssertTrue(cChunkFileFileSystem.ReadChunkEnd());
	szText.Kill();

	AssertTrue(cChunkFileFileSystem.ReadChunkBegin("last/Schism"));
	AssertTrue(szText.ReadChars(&cChunkFileFileSystem));
	AssertString("Finally! Something with Doom!", szText.Text());
	AssertTrue(cChunkFileFileSystem.ReadChunkEnd());
	szText.Kill();

	AssertTrue(cChunkFileFileSystem.ReadChunkBegin("new/age/violet/Forensics"));
	AssertTrue(szText.ReadChars(&cChunkFileFileSystem));
	AssertString("Shall we try argument?", szText.Text());
	AssertTrue(cChunkFileFileSystem.ReadChunkEnd());
	szText.Kill();

	AssertTrue(cChunkFileFileSystem.ReadChunkBegin("last/Tragic"));
	AssertTrue(szText.ReadChars(&cChunkFileFileSystem));
	AssertString("If you give me a one word text back, I'm gonna give you the same", szText.Text());
	AssertTrue(cChunkFileFileSystem.ReadChunkEnd());
	szText.Kill();

	AssertTrue(cChunkFileFileSystem.ReadChunkBegin("new/really/Final"));
	AssertTrue(szText.ReadChars(&cChunkFileFileSystem));
	AssertString("Seriously, how is it not possible to find text on the internet.", szText.Text());
	AssertTrue(cChunkFileFileSystem.ReadChunkEnd());
	szText.Kill();

	AssertTrue(cChunkFileFileSystem.ReadChunkBegin("Final"));
	AssertTrue(szText.ReadChars(&cChunkFileFileSystem));
	AssertString("Countdown", szText.Text());
	AssertTrue(cChunkFileFileSystem.ReadChunkEnd());
	szText.Kill();

	AssertTrue(cChunkFileFileSystem.ReadChunkBegin("last/time/in/world/on/See"));
	AssertTrue(szText.ReadChars(&cChunkFileFileSystem));
	AssertString("But when shall we be stronger?", szText.Text());
	AssertTrue(cChunkFileFileSystem.ReadChunkEnd());
	szText.Kill();

	AssertTrue(cChunkFileFileSystem.ReadChunkBegin("last/time/in/Paris"));
	AssertTrue(szText.ReadChars(&cChunkFileFileSystem));
	AssertString("There is no longer any room for hope.", szText.Text());
	AssertTrue(cChunkFileFileSystem.ReadChunkEnd());
	szText.Kill();

	AssertTrue(cChunkFileFileSystem.ReadChunkBegin("Unknown"));
	AssertTrue(szText.ReadChars(&cChunkFileFileSystem));
	AssertString("Sir, we have been trying that for the last ten years.", szText.Text());
	AssertTrue(cChunkFileFileSystem.ReadChunkEnd());
	szText.Kill();

	cChunkFileFileSystem.ReadClose();
	cChunkFileFileSystem.Kill();
	cChunkFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChunkFileFileSystemNameIteration(void)
{
	CChunkFile					cChunkFile;
	CChunkFileFileSystem		cChunkFileFileSystem;
	CDiskFile*					pcDiskFile;
	SChunkFilenameIterator		sIter;
	char*						szName;

	pcDiskFile = DiskFile("Input" _FS_ "FrenchToast.DRG");
	cChunkFile.Init(pcDiskFile);
	cChunkFileFileSystem.Init(&cChunkFile);

	cChunkFileFileSystem.ReadOpen();


	szName = cChunkFileFileSystem.StartNameIteration(&sIter);
	AssertString("new/age/violet/Tempest", szName);

	szName = cChunkFileFileSystem.IterateName(&sIter);
	AssertString("new/age/shrinking/daisy/Sunlight", szName);

	szName = cChunkFileFileSystem.IterateName(&sIter);
	AssertString("new/age/shrinking/daisy/Pusher", szName);

	szName = cChunkFileFileSystem.IterateName(&sIter);
	AssertString("new/age/violet/Forensics", szName);

	szName = cChunkFileFileSystem.IterateName(&sIter);
	AssertString("Unknown", szName);
	
	szName = cChunkFileFileSystem.IterateName(&sIter);
	AssertString("last/time/in/Paris", szName);

	szName = cChunkFileFileSystem.IterateName(&sIter);
	AssertString("last/time/in/world/on/See", szName);

	szName = cChunkFileFileSystem.IterateName(&sIter);
	AssertString("last/Schism", szName);

	szName = cChunkFileFileSystem.IterateName(&sIter);
	AssertString("last/Tragic", szName);

	szName = cChunkFileFileSystem.IterateName(&sIter);
	AssertString("Final", szName);

	szName = cChunkFileFileSystem.IterateName(&sIter);
	AssertString("new/really/Final", szName);

	szName = cChunkFileFileSystem.IterateName(&sIter);
	AssertNull(szName);

	cChunkFileFileSystem.StopIteration(&sIter);

	cChunkFileFileSystem.ReadClose();
	cChunkFileFileSystem.Kill();
	cChunkFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChunkFileFileSystem(void)
{
	BeginTests();
	MemoryInit();

	TestChunkFileFileSystemWriting();
	TestChunkFileFileSystemReading();
	TestChunkFileFileSystemNameIteration();

	MemoryKill();
	TestStatistics();
}
