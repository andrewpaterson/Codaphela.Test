#include "TestLib/Assert.h"


void TestArrayTemplatePrimitive(void);
void TestArrayInt(void);
void TestArrayLong(void);
void TestArrayTemplate(void);
void TestMapBlock(void);
void TestMapInt(void);
void TestMapPtr(void);
void TestMapString(void);
void TestConstructors(void);
void TestDate(void);
void TestNumbers(void);
void TestArrayDenseTemplate(void);
void TestArraySparseTemplate(void);
void TestArrayBlockSorted(void);
void TestStringHelper(void);
void TestFileUtil(void);
void TestAllocator(void);
void TestMemoryBlock(void);
void TestFreeList(void);
void TestFreeListAllocator(void);
void TestIndexTreeNode(void);
void TestIndexTree(void);
void TestIndexTreeTemplate(void);
void TestMemory(void);
void TestLinkedListBlockAligned(void);
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
void TestArrayTemplateEmbedded(void);
void TestArrayBit(void);
void TestLinkedListTemplate(void);
void TestTreeTemplate(void);
void TestCSVFileEditable(void);
void TestMemoryAllocator(void);
void TestMemoryStack(void);
void TestMemoryCache(void);
void TestScratchPad(void);
void TestScratchPadAllocator(void);


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
	TestArrayTemplatePrimitive();
	TestMapBlock();
	TestMapString();
	TestMapInt();
	TestMapPtr();
	TestConstructors();
	TestLinkedListBlockAligned();
	TestAllocator();
	TestFreeList();
	TestFreeListAllocator();
	TestStringHelper();
	TestDate();
	TestNumbers();
	TestArrayTemplate();
	TestArrayBlockSorted();
	TestIndexTreeNode();
	TestIndexTree();
	TestIndexTreeTemplate();
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
	TestArrayTemplateEmbedded();
	TestLinkedListTemplate();
	TestTreeTemplate();
	TestCSVFileEditable();
	TestMemory();
	TestMemoryAllocator();
	TestScratchPad();
	TestScratchPadAllocator();
	TestMemoryStack();
	TestMemoryCache();
	TestMemoryBlock();

	return TestTotalStatistics();
}

