#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/Codabase.h"
#include "BaseLib/CodabaseFactory.h"
#include "BaseLib/SequenceFactory.h"
#include "BaseLib/ValueIndexedDataConfig.h"
#include "BaseLib/ValueNamedIndexesConfig.h"
#include "BaseLib/NamedIndexedHeader.h"
#include "StandardLib/Objects.h"
#include "StandardLib/FreeObjects.h"
#include "TestLib/Assert.h"
#include "TestLib/AssertFile.h"
#include "ObjectTestClasses.h"
#include "ChunkFileObjectWriterTestClasses.h"
#include "UnknownObjectHolderTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsFreeUnknownOnly(void)
{
	Ptr<CFreeObjects>		pFree;
	CUnknownObjectHolder	cUnknown;
	CChars					sz;

	ObjectsInit();
	{
		ORoot();
		AssertSize(2, gcObjects.NumMemoryIndexes());
		cUnknown.Init();
		AssertSize(5, gcObjects.NumMemoryIndexes());
		sz.Init();
		gcObjects.PrintGraph(&sz, false);
		AssertString("\
-------------------------- Graph --------------------------- \n\
 [ 0]:CRoot(176) Index:1 Name:GraphRoot Froms:0,1\n\
    [ 1]:CSetObject(168) Index:2 Froms:1,0\n\
       [ 2]:CObject(160) Index:4 Name:GraphFreeObjects Froms:1,0\n\
          [ 3]:CSetObject(168) Index:5 Froms:1,0\n\
             [ 4]:CTestObject(184) Index:3 Froms:1,0\n\
------------------------------------------------------------ \n", sz.Text());
		sz.Kill();

		cUnknown.Kill();
		AssertSize(4, gcObjects.NumMemoryIndexes());
		sz.Init();
		gcObjects.PrintGraph(&sz, false);
		AssertString("\
-------------------------- Graph --------------------------- \n\
 [ 0]:CRoot(176) Index:1 Name:GraphRoot Froms:0,1\n\
    [ 1]:CSetObject(168) Index:2 Froms:1,0\n\
       [ 2]:CObject(160) Index:4 Name:GraphFreeObjects Froms:1,0\n\
          [ 3]:CSetObject(168) Index:5 Froms:1,0\n\
------------------------------------------------------------ \n", sz.Text());
		sz.Kill();	
	}
	ObjectsFlush();
	ObjectsKill(false);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFreeObjects(void)
{
	BeginTests();
	MemoryInit();
	FastFunctionsInit();
	TypesInit();
	DataIOInit();

	TestObjectsFreeUnknownOnly();

	DataIOKill();
	TypesKill();
	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

