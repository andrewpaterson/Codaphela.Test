#include "TestLib/Assert.h"
#include "TestArrayPrimitiveTemplate.h"
#include "TestArrayInt.h"
#include "TestArrayLong.h"
#include "TestArrayTemplate.h"
#include "TestMapInt.h"
#include "TestMapPtr.h"
#include "TestNumbers.h"
#include "TestDenseArrayTemplate.h"
#include "TestSparseArrayTemplate.h"
#include "TestStringHelper.h"
#include "TestFileUtil.h"
#include "TestFreeList.h"
#include "TestASCIITree.h"
#include "TestMemory.h"
#include "TestLinkListAligned.h"
#include "TestArrayInt2D.h"
#include "TestMD5File.h"
#include "TestDiskFile.h"
#include "TestBufferedFile.h"
#include "TestMemoryFile.h"
#include "TestChunkFile.h"
#include "TestPackFile.h"
#include "TestFileSystem.h"
#include "TestSorting.h"
#include "TestIntegerHelper.h"
#include "TestFileFinder.h"
#include "TestArrayEmbedded.h"
#include "TestArrayBit.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
	InitTotalStatistics();

	TestIntegerHelper();
	TestArrayInt();
	TestArrayLong();
	TestArrayInt2D();
	TestArrayPrimitiveTemplate();
	TestMapInt();
	TestMapPtr();
	TestLinkListAligned();
	TestFreeList();
	TestASCIITree();
	TestStringHelper();
	TestNumbers();
	TestArrayTemplate();
	TestArrayDenseTemplate();
	TestArraySparseTemplate();
	TestFileUtil();
	TestFileFinder();
	TestMemoryFile();
	TestDiskFile();
	TestBufferedFile();
	TestMD5File();
	TestChunkFile();
	TestPackFile();
	TestFileSystem();
	TestMemory();
	TestSorting();
	TestArrayBit();
	TestArrayEmbedded();

	return TestTotalStatistics();
}

