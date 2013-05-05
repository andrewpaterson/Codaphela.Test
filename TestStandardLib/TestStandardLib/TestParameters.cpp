#include "CoreLib/FunctionCaller.h"
#include "StandardLib/Parameters.h"
#include "StandardLib/Unknown.h"
#include "TestLib/Assert.h"


class CTestClassFunctionParams : public CUnknown
{
BASE_FUNCTIONS(CTestClassFunctionParams);
public:
	PARAM4(SFuncParams, int,q, char,c, unsigned long long int,ulli, char,c2);
	void Func(SFuncParams* s);
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
PARAM4(SGlobalFuncParams, float,x, float,y, float,z, CChars,argz);
void TestGlobalFunc(SGlobalFuncParams* arg)
{
	float	fTotal;
	CChars	argz2;

	fTotal = 0.0f;
	fTotal += arg->x;
	fTotal += arg->y;
	fTotal += arg->z;

	argz2.Init(arg->argz);
	argz2.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CTestClassFunctionParams::Func(CTestClassFunctionParams::SFuncParams* arg)
{
	CChars	sz;

	sz.Init();
	sz.Append(arg->c2);

	TestGlobalFunc(&SGlobalFuncParams((float)arg->q, (float)arg->c, (float)arg->ulli, sz));

	sz.Kill();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestParameters(void)
{
	BeginTests();

	CTestClassFunctionParams	c;

	ThisMultiCall_Void_Pointer pBlurgFunc = (ThisMultiCall_Void_Pointer)&CTestClassFunctionParams::Func;
	((CFunctionCallerMultipleInheritance*)&c->*pBlurgFunc)(&CTestClassFunctionParams::SFuncParams(6, 't', 8LL, '2'));

	TestStatistics();
}

