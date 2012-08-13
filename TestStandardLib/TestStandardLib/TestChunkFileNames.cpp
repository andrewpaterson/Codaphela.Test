#include "BaseLib/FileUtil.h"
#include "BaseLib/DiskFile.h"
#include "TestLib/Assert.h"
#include "StandardLib/ChunkFileNames.h"
#include "TestChunkFileNames.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestXXX(void)
{
	CChunkFileNames		cChunkFile;
	CDiskFile*			pcDiskFile;

	pcDiskFile = DiskFile("Output/ChunkFileNames/FrenchToast.DRG");
	cChunkFile.Init(pcDiskFile);

	cChunkFile.Kill();

	AssertTrue(FALSE);
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

	TestXXX();

	TestStatistics();
	cFileUtil.RemoveDir("Output");
}