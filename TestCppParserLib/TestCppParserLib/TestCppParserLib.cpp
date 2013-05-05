#include "stdafx.h"
#include "TestLib/Assert.h"
#include "TestASCIITree.h"
#include "TestPreprocessor.h"
#include "TestProject.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int _tmain(int argc, _TCHAR* argv[])
{
	InitTotalStatistics();

	TestASCIITree();
	TestPreprocessor();
	TestProject();

	return TestTotalStatistics();
}

	