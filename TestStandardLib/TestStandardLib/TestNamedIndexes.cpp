#include "CoreLib/DurableFileController.h"
#include "StandardLib/NamedIndexes.h"
#include "StandardLib/BaseObject.h"
#include "TestLib/Assert.h"
#include "TestNamedIndexes.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAdd(void)
{
	CNamedIndexes			cNamedIndexes;
	CDurableFileController	cController;
	CFileUtil				cFileUtil;

	cFileUtil.RemoveDir("NamedIndexes1");
	cFileUtil.MakeDir("NamedIndexes1");
	cController.Init("NamedIndexes1", TRUE);
	cNamedIndexes.Init(&cController, 10 MB, 4);

	cNamedIndexes.Add(45LL, "Berty");
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));

	cNamedIndexes.Add(73LL, "Alfred");
	AssertLongLongInt(45LL, cNamedIndexes.GetIndex("Berty"));
	AssertLongLongInt(73LL, cNamedIndexes.GetIndex("Alfred"));
	AssertLongLongInt(INVALID_OBJECT_IDENTIFIER, cNamedIndexes.GetIndex(""));
	AssertLongLongInt(INVALID_OBJECT_IDENTIFIER, cNamedIndexes.GetIndex("Ax"));
	AssertLongLongInt(INVALID_OBJECT_IDENTIFIER, cNamedIndexes.GetIndex((char*)NULL));

	cFileUtil.RemoveDir("NamedIndexes1");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexes(void)
{
	BeginTests();

	TestAdd();

	TestStatistics();
}