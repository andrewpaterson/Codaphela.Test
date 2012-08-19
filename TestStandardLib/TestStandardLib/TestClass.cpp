#include "BaseLib/FastFunctions.h"
#include "CoreLib/FunctionCaller.h"
#include "CoreLib/TypeConverter.h"
#include "StandardLib/ClassStorage.h"
#include "TestLib/Assert.h"


class CTestCallMethodClass
{
public:
	int		x;
	int		y;

	void Init(void) { x = y = 0; }
	void Kill(void) { x = y = -1; }
	void SetX(int x) {this->x = x; }
	void SetY(int y) {this->y = y; }
	int Add(void) {return x + y; }
};



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAddStructType(void)
{
	CAbstractClass*		pcClass;
	BOOL		bResult;

	ClassStorageInit();

	bResult = gcClassStorage.Add("Struct1", &pcClass);
	AssertTrue(bResult);

	pcClass->AddField(PT_int, "AnInt");

	gcClassStorage.PrivateResolve(pcClass->miID);

	AssertInt(4, pcClass->miSize);

	ClassStorageKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCallMethod(void)
{
	TypeConverterInit();
	ClassStorageInit();

	CAbstractClass*					pcClass;
	SFunctionPointer		pvInit;
	SFunctionPointer		pvKill;
	SFunctionPointer		pvSetX;
	SFunctionPointer		pvSetY;
	SFunctionPointer		pvAdd;
	CTestCallMethodClass	cTestCall;
	CConcreteClass*		pcInstanceClass;
	SInstancedClassMethod*	psMethod;
	int						iResult;

	
	pvInit = GetThisCall(&CTestCallMethodClass::Init);
	pvKill = GetThisCall(&CTestCallMethodClass::Kill);
	pvSetX = GetThisCall(&CTestCallMethodClass::SetX);
	pvSetY = GetThisCall(&CTestCallMethodClass::SetY);
	pvAdd = GetThisCall(&CTestCallMethodClass::Add);

	gcClassStorage.AddGenericMethod(0, PT_void, PT_void, "Init");
	gcClassStorage.AddGenericMethod(1, PT_void, PT_void, "Kill");
	gcClassStorage.Add("CTestCallMethodClass", &pcClass);
	pcClass->AddMethod(0, MC_ThisCall, pvInit);
	pcClass->AddMethod(1, MC_ThisCall, pvKill);
	pcClass->AddMethod(PT_int, PT_void, MC_ThisCall, pvSetX, "SetX");
	pcClass->AddMethod(PT_int, PT_void, MC_ThisCall, pvSetY, "SetY");
	pcClass->AddMethod(PT_void, PT_int, MC_ThisCall, pvAdd, "Add");
	
	gcClassStorage.ResolveAll();

	pcInstanceClass = pcClass->GetInstanced();
	AssertTrue(pcInstanceClass != NULL);

	psMethod = pcInstanceClass->GetGenericMethod(0);
	AssertTrue(psMethod != NULL);
	(((CFunctionCaller*)&cTestCall)->*psMethod->mpvFunction.thisCall)();
	AssertInt(0, cTestCall.x);
	AssertInt(0, cTestCall.y);

	psMethod = pcInstanceClass->GetGenericMethod(1);
	AssertTrue(psMethod != NULL);
	(((CFunctionCaller*)&cTestCall)->*psMethod->mpvFunction.thisCall)();
	AssertInt(-1, cTestCall.x);
	AssertInt(-1, cTestCall.y);

	psMethod = pcInstanceClass->GetMethod("SetX");
	AssertTrue(psMethod != NULL);
	(((CFunctionCaller*)&cTestCall)->*(ThisCall_Void_Int)(psMethod->mpvFunction.thisCall))(7);
	AssertInt(7, cTestCall.x);

	psMethod = pcInstanceClass->GetMethod("SetY");
	AssertTrue(psMethod != NULL);
	(((CFunctionCaller*)&cTestCall)->*(ThisCall_Void_Int)(psMethod->mpvFunction.thisCall))(11);

	AssertInt(11, cTestCall.y);

	psMethod = pcInstanceClass->GetMethod("Add");
	AssertTrue(psMethod != NULL);
	iResult = (((CFunctionCaller*)&cTestCall)->*(ThisCall_Int_Void)(psMethod->mpvFunction.thisCall))();
	AssertInt(18, iResult);

	ClassStorageKill();
	TypeConverterKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestClass(void)
{
	BeginTests();

	TestAddStructType();
	TestCallMethod();

	TestStatistics();
}

