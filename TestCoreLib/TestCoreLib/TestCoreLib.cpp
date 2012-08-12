// TestCoreLib.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BaseLib/Logger.h"
#include "TestNumber.h"
#include "TestMap.h"
#include "TestTextParser.h"
#include "TestChars.h"
#include "TestArraySimple.h"
#include "TestFastFunctions.h"
#include "TestIntegerHelper.h"
#include "TestIndexedFile.h"
#include "TestIndexes.h"
#include "TestIndexedData.h"
#include "TestIndexedDataSmart.h"
#include "TestDurableFile.h"
#include "TestTransactionData.h"
#include "TestTransactionController.h"
#include "TestDurableSet.h"
#include "TestTransientIndexedFile.h"
#include "TestIndexedHuge.h"
#include "TestOperators.h"
#include "TestFunctionCaller.h"
#include "TestFloatHelper.h"
#include "TestXMLParser.h"
#include "TestXMLFile.h"
#include "TestFiles.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
	InitTotalStatistics();

	TestFloatHelper();
	TestIntegerHelper();
	TestFastFunctions();
	TestArraySimple();
	TestChars();
	TestMap();
	TestTextParser();
	TestXMLParser();
	TestXMLFile();
	TestDurableFile();
	TestIndexedFile();
	TestIndexes();
	TestIndexedHuge();
	TestIndexedData();
	TestIndexedDataSmart();
	TestTransientIndexedFile();
	TestTransactionData();
	TestTransactionController();
	TestDurableSet();
	TestOperators();
	TestFunctionCaller();
	TestNumber();
	TestFiles();

	return TestTotalStatistics();
}

