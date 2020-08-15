#include "BaseLib/IndexTreeMemory.h"
#include "BaseLib/IndexTreeMemoryAccess.h"
#include "BaseLib/IndexTreeConfig.h"
#include "BaseLib/CreationDataOrderer.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/MemoryAllocator.h"
#include "BaseLib/GlobalMemoryAllocator.h"
#include "BaseLib/DiskFile.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/IndexTreeDataOrdererConstructors.h"
#include "BaseLib/LocalMallocatorConstructors.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryConfigGlobalMallocatorReading(void)
{
	CIndexTreeMemory					cIndexTree;
	CIndexTreeMemoryAccess				cAccess;
	CLifeInit<CIndexTreeDataOrderer>	cOrderer;
	CFileBasic							cConfigFile;
	BOOL								bResult;
	CFileUtil							cFileUtil;
	CFileBasic							cTreeFile;
	CIndexTreeMemoryConfig				cTreeConfig;
	CLifeInit<CMallocator>				cMallocator;

	cMallocator.Init(&gcMemoryAllocator, FALSE, FALSE);
	cOrderer = CCreationDataOrderer::Create();

	cIndexTree.Init(cMallocator, IKR_Yes, 512, 8, cOrderer);
	cAccess.Init(&cIndexTree);

	cFileUtil.MakeDir("Output" _FS_ "IndexTreeConfig1");
	cConfigFile.Init(DiskFile("Output" _FS_ "IndexTreeConfig1" _FS_ "Tree.cfg"));
	cConfigFile.Open(EFM_ReadWrite_Create);
	bResult = cIndexTree.WriteConfig(&cConfigFile);
	AssertTrue(bResult);
	cConfigFile.Close();
	cConfigFile.Kill();

	cAccess.PutStringChar("0000", 'a');
	cAccess.PutStringChar("0100", 'b');
	cAccess.PutStringChar("0010", 'c');
	cAccess.PutStringChar("0110", 'd');

	cTreeFile.Init(DiskFile("Output" _FS_ "IndexTreeConfig1" _FS_ "Tree.dat"));
	cTreeFile.Open(EFM_ReadWrite_Create);
	bResult = cIndexTree.Write(&cTreeFile);
	AssertTrue(bResult);
	cTreeFile.Close();
	cTreeFile.Kill();

	cIndexTree.Kill();
	cAccess.Kill();

	cConfigFile.Init(DiskFile("Output" _FS_ "IndexTreeConfig1" _FS_ "Tree.cfg"));
	cConfigFile.Open(EFM_Read);
	bResult = cTreeConfig.Init(&cConfigFile);
	AssertTrue(bResult);
	cConfigFile.Close();
	cConfigFile.Kill();

	cIndexTree.Init(&cTreeConfig);
	cAccess.Init(&cIndexTree);

	cTreeFile.Init(DiskFile("Output" _FS_ "IndexTreeConfig1" _FS_ "Tree.dat"));
	cTreeFile.Open(EFM_Read);
	bResult = cIndexTree.Read(&cTreeFile);
	AssertTrue(bResult);
	cTreeFile.Close();
	cTreeFile.Kill();

	cIndexTree.Kill();
	cAccess.Kill();

	cFileUtil.RemoveDir("Output" _FS_ "IndexTreeConfig1");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryConfigLocalMallocatorReading(void)
{
	CIndexTreeMemory					cIndexTree;
	CIndexTreeMemoryAccess				cAccess;
	CLifeInit<CIndexTreeDataOrderer>	cOrderer;
	CFileBasic							cConfigFile;
	BOOL								bResult;
	CFileUtil							cFileUtil;
	CFileBasic							cTreeFile;
	CIndexTreeMemoryConfig				cTreeConfig;
	CLifeInit<CMallocator>				cMallocator;

	cMallocator = CMemoryAllocator::Create();
	cOrderer = CCreationDataOrderer::Create();

	cIndexTree.Init(cMallocator, IKR_Yes, 512, 8, cOrderer);
	cAccess.Init(&cIndexTree);

	cFileUtil.MakeDir("Output" _FS_ "IndexTreeConfig2");
	cConfigFile.Init(DiskFile("Output" _FS_ "IndexTreeConfig2" _FS_ "Tree.cfg"));
	cConfigFile.Open(EFM_ReadWrite_Create);
	bResult = cIndexTree.WriteConfig(&cConfigFile);
	AssertTrue(bResult);
	cConfigFile.Close();
	cConfigFile.Kill();

	cAccess.PutStringChar("0000", 'a');
	cAccess.PutStringChar("0100", 'b');
	cAccess.PutStringChar("0010", 'c');
	cAccess.PutStringChar("0110", 'd');

	cTreeFile.Init(DiskFile("Output" _FS_ "IndexTreeConfig2" _FS_ "Tree.dat"));
	cTreeFile.Open(EFM_ReadWrite_Create);
	bResult = cIndexTree.Write(&cTreeFile);
	AssertTrue(bResult);
	cTreeFile.Close();
	cTreeFile.Kill();

	cIndexTree.Kill();
	cAccess.Kill();

	cConfigFile.Init(DiskFile("Output" _FS_ "IndexTreeConfig2" _FS_ "Tree.cfg"));
	cConfigFile.Open(EFM_Read);
	bResult = cTreeConfig.Init(&cConfigFile);
	AssertTrue(bResult);
	cConfigFile.Close();
	cConfigFile.Kill();

	cIndexTree.Init(&cTreeConfig);
	cAccess.Init(&cIndexTree);

	cTreeFile.Init(DiskFile("Output" _FS_ "IndexTreeConfig2" _FS_ "Tree.dat"));
	cTreeFile.Open(EFM_Read);
	bResult = cIndexTree.Read(&cTreeFile);
	AssertTrue(bResult);
	cTreeFile.Close();
	cTreeFile.Kill();

	cIndexTree.Kill();
	cAccess.Kill();

	cFileUtil.RemoveDir("Output" _FS_ "IndexTreeConfig2");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryConfig(void)
{
	BeginTests();
	FastFunctionsInit();
	MemoryInit();
	LocalMallocatorsInit(&gcConstructors, &gcMallocators);
	IndexTreeDataOrdererInit(&gcConstructors);

	TestIndexTreeMemoryConfigLocalMallocatorReading();
	TestIndexTreeMemoryConfigGlobalMallocatorReading();

	MemoryKill();
	FastFunctionsKill();
	TestStatistics();
}

