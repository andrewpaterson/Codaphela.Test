#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

#include "TestLib/Assert.h"


void TestPrimitiveTypes(void);
void TestFloat4(void);
void TestFloatHelper(void);
void TestArraySizer(void);
void TestArrayTemplatePrimitive(void);
void TestArrayInt(void);
void TestArrayLong(void);
void TestArrayTemplate(void);
void TestArrayVoidPtrGet(void);
void TestArrayMinimalTemplate(void);
void TestLogger(void);
void TestMapBlock(void);
void TestMapInt(void);
void TestMapLong(void);
void TestMapPtr(void);
void TestMapString(void);
void TestMap(void);
void TestIndexBlock(void);
void TestIndexAccess(void);
void TestMapAccess(void);
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
void TestCharsHelper(void);
void TestTextParser(void);
void TestFileUtil(void);
void TestAllocator(void);
void TestMemoryBlock(void);
void TestFreeList(void);
void TestFreeListAllocator(void);
void TestIndexTreeNodeMemory(void);
void TestIndexTreeMemory(void);
void TestIndexTreeMemoryIterator(void);
void TestIndexString(void);
void TestGeneralMemory(void);
void TestDataMemory(void);
void TestLinkedList(void);
void TestLinkedListBlock(void);
void TestLinkedListTemplate(void);
void TestLinkedListBlockAligned(void);
void TestListVariable(void);
void TestArrayInt2D(void);
void TestTreeTemplate(void);
void TestWindowsFilesTruncate(void);
void TestMD5File(void);
void TestDiskFile(void);
void TestBufferedFile(void);
void TestMemoryFile(void);
void TestChunkFile(void);
void TestChunkFileFile(void);
void TestChunkFileFileSystem(void);
void TestPackFile(void);
void TestFileIO(void);
void TestFileSystem(void);
void TestSorting(void);
void TestIntegerHelper(void);
void TestFileFinder(void);
void TestArrayTemplateEmbedded(void);
void TestArrayBit(void);
void TestCSVFileEditable(void);
void TestMemoryAllocator(void);
void TestTrackingAllocator(void);
void TestCountingAllocator(void);
void TestMemoryStack(void);
void TestMemoryCache(void);
void TestMemoryQueue(void);
void TestScratchPad(void);
void TestScratchPadAllocator(void);
void TestTemporaryMemory(void);
void TestStackMemoryCompilation(void);
void TestCSVFileImmutable(void);
void TestIndexTreeDataOrderer(void);
void TestIndexTreeMemoryConfig(void);
void TestDataTypesIO(void);
void TestGlobalDataTypesIO(void);


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int __cdecl main(void)
{
	int iResult;

	_CrtSetBreakAlloc(0);
	InitTotalStatistics();

	TestPrimitiveTypes();
	TestIntegerHelper();
	TestFloatHelper();
	TestFloat4();
	TestStringHelper();
	TestArrayInt();
	TestArrayLong();
	TestArrayInt2D();
	TestArrayVoidPtrGet();
	TestArrayTemplatePrimitive();
	TestArrayMinimalTemplate();
	TestArrayBlockSorted();
	TestArraySizer();
	TestChars();
	TestLogger();
	TestMapBlock();
	TestMapString();
	TestMapInt();
	TestMapLong();
	TestMapPtr();
	TestMap();
	TestIndexAccess();
	TestMapAccess();
	TestListBlock();
	TestListTemplate();
	TestListCharsMinimal();
	TestListVariable();
	TestTreeTemplate();
	TestConstructors();
	TestConstructorCall();
	TestAllocator();
	TestFreeList();
	TestFreeListAllocator();
	TestCharsHelper();
	TestTextParser();
	TestDate();
	TestNumbers();
	TestArrayTemplate();
	TestIndexTreeNodeMemory();
	TestIndexTreeMemoryIterator();
	TestArrayDenseTemplate();
	TestArraySparseTemplate();
	TestMemoryFile();
	TestWindowsFilesTruncate();
	TestDiskFile();
	TestBufferedFile();
	TestMD5File();
	TestSorting();
	TestArrayBit();
	TestArrayTemplateEmbedded();
	TestLinkedList();
	TestLinkedListBlock();
	TestLinkedListTemplate();
	TestLinkedListBlockAligned();
	TestIndexTreeMemory();
	TestIndexBlock();
	TestIndexString();
	TestCSVFileEditable();
	TestGeneralMemory();
	TestDataMemory();
	TestMemoryAllocator();
	TestCountingAllocator();
	TestTrackingAllocator();
	TestScratchPad();
	TestScratchPadAllocator();
	TestMemoryStack();
	TestMemoryCache();
	TestMemoryQueue();
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
	TestChunkFileFileSystem();
	TestCSVFileImmutable();
	TestIndexTreeDataOrderer();
	TestIndexTreeMemoryConfig();
	TestDataTypesIO();
	TestGlobalDataTypesIO();
	iResult = TestTotalStatistics();
	_CrtDumpMemoryLeaks();
	return iResult;
}

