#include "stdafx.h"
#include "TestLib/Assert.h"
#include "TestTriangleShape.h"
#include "BaseLib/FastFunctions.h"
#include "SupportLib/Triangle.h"



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTriangleShape(void)
{
	BeginTests();
	FastFunctionsInit();


	FastFunctionsKill();
	TestStatistics();
}
