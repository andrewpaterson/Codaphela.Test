#include "TestLib/Assert.h"


void TestPrimitiveTypes(void);
void TestFloat4(void);
void TestArraySizer(void);
void TestArrayTemplatePrimitive(void);
void TestArrayInt(void);
void TestArrayLong(void);
void TestArrayTemplate(void);
void TestArrayVoidPtrGet(void);
void TestArrayMinimalTemplate(void);
void TestMapBlock(void);
void TestMapInt(void);
void TestMapPtr(void);
void TestMapString(void);
void TestMap(void);
void TestListBlock(void);
void TestListTemplate(void);
void TestListCharsMinimal(void);
void TestConstructors(void);
void TestConstructorCall(void);
void TestDate(void);
void TestNumbers(void);
void TestArrayDenseTemplate(void);
void TestArraySparseTemplate(void);
void TestArrayBlockSorted(void);
void TestChars(void);
void TestStringHelper(void);
void TestTextParser(void);
void TestFileUtil(void);
void TestAllocator(void);
void TestMemoryBlock(void);
void TestFreeList(void);
void TestFreeListAllocator(void);
void TestIndexTreeNodeMemory(void);
void TestIndexTreeMemory(void);
void TestIndexTreeTemplate(void);
void TestIndexTreeIterator(void);
void TestGeneralMemory(void);
void TestDataMemory(void);
void TestLinkedListBlockAligned(void);
void TestListVariable(void);
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
void TestTrackingAllocator(void);
void TestMemoryStack(void);
void TestMemoryCache(void);
void TestScratchPad(void);
void TestScratchPadAllocator(void);
void TestTemporaryMemory(void);
void TestStackMemoryCompilation(void);
void TestCSVFileImmutable(void);


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int main(void)
{
	InitTotalStatistics();

	TestPrimitiveTypes();
	TestIntegerHelper();
	TestFloat4();
	TestArrayInt();
	TestArrayLong();
	TestArrayInt2D();
	TestArrayVoidPtrGet();
	TestArrayTemplatePrimitive();
	TestArrayMinimalTemplate();
	TestArrayBlockSorted();
	TestArraySizer();
	TestMapBlock();
	TestMapString();
	TestMapInt();
	TestMapPtr();
	TestMap();
	TestListBlock();
	TestListTemplate();
	TestListCharsMinimal();
	TestListVariable();
	TestConstructors();
	TestConstructorCall();
	TestLinkedListBlockAligned();
	TestAllocator();
	TestFreeList();
	TestFreeListAllocator();
	TestChars();
	TestStringHelper();
	TestTextParser();
	TestDate();
	TestNumbers();
	TestArrayTemplate();
	TestIndexTreeNodeMemory();
	TestIndexTreeMemory();
	TestIndexTreeTemplate();
	TestIndexTreeIterator();
	TestArrayDenseTemplate();
	TestArraySparseTemplate();
	TestMemoryFile();
	TestDiskFile();
	TestBufferedFile();
	TestMD5File();
	TestSorting();
	TestArrayBit();
	TestArrayTemplateEmbedded();
	TestLinkedListTemplate();
	TestTreeTemplate();
	TestCSVFileEditable();
	TestGeneralMemory();
	TestDataMemory();
	TestMemoryAllocator();
	TestTrackingAllocator();
	TestScratchPad();
	TestScratchPadAllocator();
	TestMemoryStack();
	TestMemoryCache();
	TestMemoryBlock();
	TestTemporaryMemory();
	TestStackMemoryCompilation();
	TestFileUtil();
	TestFileFinder();
	TestChunkFile();
	TestChunkFileFile();
	TestPackFile();
	TestFileIO();
	TestFileSystem();
	TestCSVFileImmutable();

	return TestTotalStatistics();
}

