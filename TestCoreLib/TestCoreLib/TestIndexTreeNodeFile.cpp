#include "BaseLib/FileUtil.h"
#include "BaseLib/SystemAllocator.h"
#include "TestLib/Assert.h"
#include "CoreLib/IndexTreeNodeFile.h"
#include "CoreLib/IndexTreeBlockFile.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeNodeFileSizeofs(void)
{
	AssertInt(4, sizeof(CIndexTreeNodeFile*));
	AssertInt(16, sizeof(CFileIndex));  //Sizeof is 16 but only the first 12 bytes are used.
	AssertInt(16, sizeof(SIndexTreeChildFile));  //Sizeof is 16 but only the last 4 bytes are used.
	AssertInt(16, sizeof(CIndexTreeChildNode));  //The above is why the union works 

	AssertTrue(sizeof(CIndexTreeNodeFile*) <= 12);  //The size of a memory pointer may not be more than 12 bytes.
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeNodeFileUnion(void)
{
	CIndexTreeChildNode		cChild;

	memset(&cChild, 0, sizeof(CIndexTreeChildNode));
	cChild.u.mcFile.Init();
	AssertInt(0, cChild.u.msType.iType);

	cChild.u.mpvMemory = (CIndexTreeNodeFile*)0x80808080;
	AssertInt(0, cChild.u.msType.iType);
	AssertFalse(cChild.IsValid());

	memset(&cChild, 1, sizeof(CIndexTreeChildNode));
	AssertTrue(cChild.IsValid());
	AssertTrue(cChild.IsMemory());
	AssertFalse(cChild.IsFile());

	memset(&cChild, 2, sizeof(CIndexTreeChildNode));
	AssertTrue(cChild.IsValid());
	AssertFalse(cChild.IsMemory());
	AssertTrue(cChild.IsFile());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeNodeFileInit(void)
{
	CIndexTreeNodeFile*		pcNode;
	CIndexTreeBlockFile		cIndex;

	cIndex.FakeInit();

	pcNode = (CIndexTreeNodeFile*)malloc(sizeof(CIndexTreeNodeFile) + sizeof(CIndexTreeChildNode));  //Node.  No object.  One child.
	pcNode->Init(&cIndex, NULL);

	free(pcNode);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeNodeFile(void)
{
	BeginTests();

	TestIndexTreeNodeFileSizeofs();
	TestIndexTreeNodeFileUnion();
	TestIndexTreeNodeFileInit();

	TestStatistics();
}


