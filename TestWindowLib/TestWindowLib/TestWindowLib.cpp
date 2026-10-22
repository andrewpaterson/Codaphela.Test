#include "BaseLib/LeakDetector.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"


void TestRefWindow(void);
void TestFlowContainer(void);
void TestFillContainer(void);
void TestGridContainer(void);
void TestNestedContainers(void);
void TestBorderLayoutHelper(void);
void TestCanvas(void);
void TestLabel(void);
void TestTextArea(void);
void TestScrollPane(void);
void TestComponentInput(void);
void TestComponentInputDevices(void);
void TestComponentInputWinRaw(void);
void TestButton(void);
void TestButtonBar(void);
void TestList(void);
void TestMenu(void);


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int __cdecl main(void)
{
	CFileUtil	cFileUtil;
	int			iResult;

	BreakOnAllocation(0);
	InitTotalStatistics();

	FastFunctionsInit();
	TypesInit();
	TypeConverterInit();
	MemoryInit();
	DataIOInit();

	cFileUtil.RemoveDir("Output");
	cFileUtil.MakeDir("Output");

	TestRefWindow();
	TestFlowContainer();
	TestFillContainer();
	TestGridContainer();
	TestNestedContainers();
	TestBorderLayoutHelper();
	TestCanvas();
	TestLabel();
	TestTextArea();
	TestScrollPane();
	TestComponentInput();
	TestComponentInputDevices();
	TestComponentInputWinRaw();
	TestButton();
	TestButtonBar();
	TestList();
	TestMenu();

	cFileUtil.RemoveDir("Output");

	DataIOKill();
	MemoryKill();
	TypeConverterKill();
	TypesKill();
	FastFunctionsKill();

	iResult = TestTotalStatistics();
	LeakDetection();
	return iResult;
}

