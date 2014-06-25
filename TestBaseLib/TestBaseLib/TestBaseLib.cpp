#include "TestLib/Assert.h"

void TestArrayPrimitiveTemplate(void);
void TestArrayInt(void);
void TestArrayLong(void);
void TestArrayTemplate(void);
void TestMapInt(void);
void TestMapPtr(void);
void TestDate(void);
void TestNumbers(void);
void TestArrayDenseTemplate(void);
void TestArraySparseTemplate(void);
void TestStringHelper(void);
void TestFileUtil(void);
void TestFreeList(void);
void TestIndexTreeNode(void);
void TestIndexTree(void);
void TestASCIITree(void);
void TestMemory(void);
void TestLinkListAligned(void);
void TestArrayInt2D(void);
void TestMD5File(void);
void TestDiskFile(void);
void TestBufferedFile(void);
void TestMemoryFile(void);
void TestChunkFile(void);
void TestChunkFileFile(void);
void TestPackFile(void);
void TestFileIO(void);
void TestFileSystem(void);
void TestSorting(void);
void TestIntegerHelper(void);
void TestFileFinder(void);
void TestArrayEmbedded(void);
void TestArrayBit(void);
void TestLinkListTemplate(void);
void TestTreeTemplate(void);
void TestCSVFileEditable(void);
void TestMemoryStack(void);
void TestMemoryCache(void);
void TestScratchPad(void);


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
	TestStringHelper();
	TestDate();
	TestNumbers();
	TestArrayTemplate();
	TestIndexTreeNode();
	TestIndexTree();
	TestASCIITree();
	TestArrayDenseTemplate();
	TestArraySparseTemplate();
	TestFileUtil();
	TestFileFinder();
	TestMemoryFile();
	TestDiskFile();
	TestBufferedFile();
	TestMD5File();
	TestChunkFile();
	TestChunkFileFile();
	TestPackFile();
	TestFileIO();
	TestFileSystem();
	TestSorting();
	TestArrayBit();
	TestArrayEmbedded();
	TestLinkListTemplate();
	TestTreeTemplate();
	TestCSVFileEditable();
	TestMemory();
	TestScratchPad();
	TestMemoryStack();
	TestMemoryCache();

	return TestTotalStatistics();
}

