#include <Windows.h>
#include "TestLib/Assert.h"
#include "TestClass.h"
#include "TestClassStorage.h"
#include "TestUnknowns.h"
#include "TestArrayUnknown.h"
#include "TestSetUnknown.h"
#include "TestArrayType.h"
#include "TestSetType.h"
#include "TestEvent.h"
#include "TestActionEvent.h"
#include "TestChannels.h"
#include "TestChannelAccessor.h"
#include "TestSingleChannelAccessor.h"
#include "TestExternalChannels.h"
#include "TestChannelPadder.h"
#include "TestUnknowns.h"
#include "TestMapStringUnknown.h"
#include "TestChunkFileNames.h"
#include "TestParameters.h"
#include "TestObject.h"
#include "TestRoot.h"
#include "TestObjectGraphWriter.h"
#include "TestNamedIndexes.h"
#include "TestObjects.h"
#include "TestPointer.h"
#include "TestObjectConverter.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int FAR PASCAL WinMain(HINSTANCE hInstance,	HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	InitTotalStatistics();
	InitEmptyString();
	FastFunctionsInit();

	TestClass();
	TestClassStorage();
	TestUnknowns();
	TestArrayUnknown();
	TestSetUnknown();
	TestArrayType();
	TestSetType();
	TestMapStringUnknown();
	TestEvent();
	TestActionEvent();
	TestExternalChannels();
	TestExternalChannelPadder();
	TestChannels();
	TestChannelsAccessor();
	TestSingleChannelAccessor();
	TestChunkFileNames();
	TestParameters();
	TestObject();
	TestRoot();
	TestObjectGraphWriter();
	TestNamedIndexes();
	TestPointer();
	TestObjectConverter();
	TestObjects();

	FastFunctionsKill();
	KillEmptyString();
	return TestTotalStatistics();
}

