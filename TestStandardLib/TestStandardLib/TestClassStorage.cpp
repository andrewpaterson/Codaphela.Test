#include "BaseLib/Logger.h"
#include "BaseLib/FastFunctions.h"
#include "CoreLib/FunctionCaller.h"
#include "CoreLib/TypeConverter.h"
#include "StandardLib/ClassStorage.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestResolve(void)
{
	TypeConverterInit();

	CClassStorage	cClassStorage;
	CAbstractClass*			pcClass;
	BOOL			bResult;

	cClassStorage.Init();
	cClassStorage.Add("Test", &pcClass);
	pcClass->AddField(PT_int, "anInt");

	bResult = cClassStorage.ResolveAll();
	AssertTrue(bResult);

	//Oi, this is tested in the wrong file!
	gcLogger.Disable();
	bResult = pcClass->AddField("Undefined", "anUnkown");
	AssertFalse(bResult);

	gcLogger.Disable();
	bResult = pcClass->AddSuperClass("Undefined");
	AssertFalse(bResult);
	gcLogger.Enable();

	cClassStorage.Kill();

	TypeConverterKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestClassStorage(void)
{
	BeginTests();

	TestResolve();

	TestStatistics();
}

