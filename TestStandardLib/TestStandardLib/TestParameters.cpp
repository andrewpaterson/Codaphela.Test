#include "BaseLib/FunctionCaller.h"
#include "StandardLib/Unknown.h"
#include "TestLib/Assert.h"


struct SParams
{
	int		_iParamSize;
};


#define PARAM4(f, t1, a1, t2, a2, t3, a3, t4, a4) \
struct f : SParams { \
	t1 a1; t2 a2; t3 a3; t4 a4; \
	f::f(t1 a1, t2 a2, t3 a3, t4 a4) \
{ _iParamSize=sizeof(f); this->a1 = a1; this->a2 = a2; this->a3 = a3; this->a4 = a4; } \
};



class CTestClassFunctionParams : public CUnknown
{
CONSTRUCTABLE(CTestClassFunctionParams);
public:

	struct SFuncParams : SParams
	{
		int q;
		char c;
		uint64 ulli;
		char c2;

		SFuncParams::SFuncParams(int q, char c, uint64 ulli, char c2)
		{
			_iParamSize = sizeof(SFuncParams);
			this->q = q;
			this->c = c;
			this->ulli = ulli;
			this->c2 = c2;
		}
	};

	void Func(SFuncParams* s);
};


struct SGlobalFuncParams : SParams
{
	float x;
	float y;
	float z;
	CChars argz;

	SGlobalFuncParams::SGlobalFuncParams(float x, float y, float z, CChars argz)
	{
		_iParamSize = sizeof(SGlobalFuncParams);
		this->x = x;
		this->y = y;
		this->z = z;
		this->argz = argz;
	}
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
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


