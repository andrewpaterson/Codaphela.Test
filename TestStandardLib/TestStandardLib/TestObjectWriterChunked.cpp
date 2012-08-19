#include "BaseLib/FileUtil.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ObjectGraphWriter.h"
#include "StandardLib/ObjectWriterSimple.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectWriterChunked(void)
{
	CFileUtil	cFileUtil;

	cFileUtil.RemoveDir("Output");
	cFileUtil.MakeDir("Output/ObjectWriterChunked");
	ObjectsInit(NULL);
	BeginTests();


	TestStatistics();
	ObjectsKill();

	cFileUtil.RemoveDir("Output");
}

