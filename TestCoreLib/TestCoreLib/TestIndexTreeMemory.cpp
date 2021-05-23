#include "BaseLib/Logger.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/SystemAllocator.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/IndexTreeNodeMemory.h"
#include "BaseLib/IndexTreeMemory.h"
#include "BaseLib/MemoryAllocator.h"
#include "BaseLib/PrimitiveTypes.h"
#include "BaseLib/IndexTreeMemoryAccess.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemorySizeOfs(void)
{
	CIndexTreeMemory	cIndexTree;
	size_t				tRootNodeSize;
	size_t				tNodeSize;
	size_t				tNodePointer;

	cIndexTree.Init();
	tRootNodeSize = cIndexTree.CalculateRootNodeSize();
	tNodeSize = cIndexTree.SizeofNode();
	tNodePointer = cIndexTree.SizeofNodePtr();

	AssertInt(1040, tRootNodeSize);
	AssertInt(16, tNodeSize);
	AssertInt(4, tNodePointer);

	cIndexTree.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryPutValidation(void)
{
	CIndexTreeMemory		cIndexTree;
	CIndexTreeMemoryAccess	cAccess;


	cIndexTree.Init();
	cAccess.Init(&cIndexTree);

	AssertTrue(cAccess.PutStringString("\2\3", "Data"));
	AssertTrue(cIndexTree.ValidateIndexTree());
	AssertTrue(cAccess.PutStringString("\2\2", "Data"));
	AssertTrue(cAccess.PutStringString("\2\4", "Data"));
	AssertTrue(cIndexTree.ValidateIndexTree());

	cAccess.Kill();
	cIndexTree.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryAllocation(void)
{
	CMemoryAllocator	cMemoryAllocator;
	CIndexTreeMemory	cIndexTree;
	int64				lliKey1;
	char*				pvData1;
	CGeneralMemory*		pcMemory;
	size_t				tRootNodeSize;
	size_t				tNodeSize;
	size_t				tDataNodeSize;
	size_t				tNoDataSize;

	cMemoryAllocator.Init(16);
	pcMemory = cMemoryAllocator.GetMemory();
	AssertLongLongInt(0, pcMemory->GetTotalAllocatedMemory());
	AssertLongLongInt(0, pcMemory->GetTotalAllocations());

	cIndexTree.Init(LifeLocal<CMallocator>(&cMemoryAllocator), IKR_No);
	tRootNodeSize = cIndexTree.CalculateRootNodeSize();
	tNodeSize = cIndexTree.SizeofNode();
	tDataNodeSize = cIndexTree.SizeofDataNode();
	tNoDataSize = cIndexTree.SizeofNodePtr();

	AssertLongLongInt(1 /* root node (256 children) */, pcMemory->GetTotalAllocations());
	AssertLongLongInt(tRootNodeSize, pcMemory->GetTotalAllocatedMemory());
	
	lliKey1 = 1;
	pvData1 = (char*)cIndexTree.Put(&lliKey1, sizeof(int64), NULL, 103);
	AssertLongLongInt(1 /* root node (256 children) */ + 7 /* empty nodes with child */ + 1 /* node with no children but with data */, pcMemory->GetTotalAllocations());
	Pass();
	AssertLongLongInt(tRootNodeSize + (tNodeSize + tNoDataSize) * 7 + (tDataNodeSize + 103), pcMemory->GetTotalAllocatedMemory());
	Pass();

	cIndexTree.Kill();
	AssertLongLongInt(0, pcMemory->GetTotalAllocations());
	AssertLongLongInt(0, pcMemory->GetTotalAllocatedMemory());

	cMemoryAllocator.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryComplexGlobalAllocator(void)
{
	CIndexTreeMemory		cIndexTree;
	CIndexTreeMemoryAccess	cAccess;
	char					sz[MAX_UCHAR];
	CArrayVoidPtr			avp;
	SLogConfig				sLogConfig;

	cIndexTree.Init(LifeLocal<CMallocator>(&gcSystemAllocator), IKR_No, 255, MAX_KEY_SIZE);
	cAccess.Init(&cIndexTree);

	AssertTrue(cAccess.PutLongString(0x0000000000000000LL, "Zero"));
	AssertInt(1, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertString("Zero", cAccess.GetLongString(0x0000000000000000LL, sz));

	AssertNull(cAccess.GetLongString(1LL, sz));

	sLogConfig = gcLogger.SetSilent();
	AssertFalse(cAccess.PutLongString(0x23BB45CC67DD89EELL, "Character Count & Word Count Tool is a free character counter tool that provides instant character count & word count statistics for a given text. The tool reports the number of character with spaces and without spaces, also the number of words and sente."));
	gcLogger.SetConfig(&sLogConfig);
	AssertTrue(cAccess.PutLongString(0x23BB45CC67DD89EELL, "Character Count & Word Count Tool is a free character counter tool that provides instant character count & word count statistics for a given text. The tool reports the number of character with spaces and without spaces, also the number of words and sent."));
	AssertInt(2, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertNotNull(cAccess.GetLongString(0x23BB45CC67DD89EELL, sz));
	AssertString("Character Count & Word Count Tool is a free character counter tool that provides instant character count & word count statistics for a given text. The tool reports the number of character with spaces and without spaces, also the number of words and sent.", sz);

	AssertTrue(cAccess.PutLongString(0x23BB45CC67DD9800LL, "MORE node DATA"));
	AssertInt(3, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertNotNull(cAccess.GetLongString(0x23BB45CC67DD9800LL, sz));
	AssertString("MORE node DATA", sz);

	AssertTrue(cAccess.PutLongString(0x23BB54CC00DD0000LL, "Another DATUM of doom"));
	AssertInt(4, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertNotNull(cAccess.GetLongString(0x23BB54CC00DD0000LL, sz));
	AssertString("Another DATUM of doom", sz);

	AssertTrue(cAccess.PutLongString(0x23BB45CC67DD9800LL, "Changed your data lengh"));
	AssertInt(4, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertNotNull(cAccess.GetLongString(0x23BB45CC67DD9800LL, sz));
	AssertString("Changed your data lengh", sz);
	AssertNotNull(cAccess.GetLongString(0x0000000000000000LL, sz));
	AssertString("Zero", sz);
	AssertNotNull(cAccess.GetLongString(0x23BB45CC67DD89EELL, sz));
	AssertString("Character Count & Word Count Tool is a free character counter tool that provides instant character count & word count statistics for a given text. The tool reports the number of character with spaces and without spaces, also the number of words and sent.", sz);
	AssertNotNull(cAccess.GetLongString(0x23BB54CC00DD0000LL, sz));
	AssertString("Another DATUM of doom", sz);

	AssertTrue(cAccess.PutLongString(0x23BB45CC67DD89EELL, "Make the long int16."));
	AssertInt(4, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertNotNull(cAccess.GetLongString(0x23BB45CC67DD9800LL, sz));
	AssertString("Changed your data lengh", sz);
	AssertNotNull(cAccess.GetLongString(0x0000000000000000LL, sz));
	AssertString("Zero", sz);
	AssertNotNull(cAccess.GetLongString(0x23BB45CC67DD89EELL, sz));
	AssertString("Make the long int16.", sz);
	AssertNotNull(cAccess.GetLongString(0x23BB54CC00DD0000LL, sz));
	AssertString("Another DATUM of doom", sz);

	AssertFalse(cAccess.DeleteLong(0x0000000000000001LL));
	AssertFalse(cAccess.DeleteLong(0xFF00000000000000LL));
	AssertTrue(cAccess.DeleteLong(0x0000000000000000LL));
	AssertInt(3, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertNotNull(cAccess.GetLongString(0x23BB45CC67DD9800LL, sz));
	AssertString("Changed your data lengh", sz);
	AssertNotNull(cAccess.GetLongString(0x23BB45CC67DD89EELL, sz));
	AssertString("Make the long int16.", sz);
	AssertNotNull(cAccess.GetLongString(0x23BB54CC00DD0000LL, sz));
	AssertString("Another DATUM of doom", sz);

	AssertTrue(cAccess.DeleteLong(0x23BB45CC67DD9800LL));
	AssertInt(2, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree());
	AssertNull(cAccess.GetLongString(0x23BB45CC67DD9800LL, sz));

	AssertNotNull(cAccess.GetLongString(0x23BB45CC67DD89EELL, sz));
	AssertString("Make the long int16.", sz);
	AssertNotNull(cAccess.GetLongString(0x23BB54CC00DD0000LL, sz));
	AssertString("Another DATUM of doom", sz);

	avp.Init();
	cIndexTree.FindAll(&avp);
	AssertString("Another DATUM of doom", (char*)avp[0]);
	AssertString("Make the long int16.", (char*)avp[1]);
	AssertInt(2, avp.NumElements());
	avp.Kill();

	AssertTrue(cAccess.DeleteLong(0x23BB54CC00DD0000LL));
	AssertInt(1, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree());
	AssertNull(cAccess.GetLongString(0x23BB54CC00DD0000LL, sz));

	avp.Init();
	cIndexTree.FindAll(&avp);
	AssertInt(1, avp.NumElements());
	AssertString("Make the long int16.", (char*)avp[0]);
	avp.Kill();

	AssertNotNull(cAccess.GetLongString(0x23BB45CC67DD89EELL, sz));
	AssertString("Make the long int16.", sz);

	AssertTrue(cAccess.DeleteLong(0x23BB45CC67DD89EELL));
	AssertInt(0, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree());
	AssertNull(cAccess.GetLongString(0x23BB45CC67DD89EELL, sz));

	cAccess.Kill();
	cIndexTree.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryComplexMemoryAllocatorBigEndian(void)
{
	CMemoryAllocator		cMemoryAllocator;
	CIndexTreeMemory		cIndexTree;
	CIndexTreeMemoryAccess	cAccess;
	CGeneralMemory*			pcMemory;
	char					sz[MAX_UCHAR];
	CArrayVoidPtr			avp;
	SLogConfig				sLogConfig;

	cMemoryAllocator.Init(16);
	pcMemory = cMemoryAllocator.GetMemory();

	cIndexTree.Init(LifeLocal<CMallocator>(&cMemoryAllocator), IKR_Yes, 255, MAX_KEY_SIZE);
	cAccess.Init(&cIndexTree);

	AssertTrue(cAccess.PutLongString(0x0000000000000000LL, "Zero"));
	AssertInt(1, cIndexTree.NumElements());

	AssertNotNull(cAccess.GetLongString(0x0000000000000000LL, sz));
	AssertString("Zero", sz);

	AssertNull(cAccess.GetLongString(1LL, sz));

	sLogConfig = gcLogger.SetSilent();
	AssertFalse(cAccess.PutLongString(0x23BB45CC67DD89EELL, "Character Count & Word Count Tool is a free character counter tool that provides instant character count & word count statistics for a given text. The tool reports the number of character with spaces and without spaces, also the number of words and sente."));
	gcLogger.SetConfig(&sLogConfig);
	AssertTrue(cAccess.PutLongString(0x23BB45CC67DD89EELL, "Character Count & Word Count Tool is a free character counter tool that provides instant character count & word count statistics for a given text. The tool reports the number of character with spaces and without spaces, also the number of words and sent."));
	AssertInt(2, cIndexTree.NumElements());

	AssertNotNull(cAccess.GetLongString(0x23BB45CC67DD89EELL, sz));
	AssertString("Character Count & Word Count Tool is a free character counter tool that provides instant character count & word count statistics for a given text. The tool reports the number of character with spaces and without spaces, also the number of words and sent.", sz);

	AssertTrue(cAccess.PutLongString(0x23BB45CC67DD9800LL, "MORE node DATA"));
	AssertInt(3, cIndexTree.NumElements());

	AssertNotNull(cAccess.GetLongString(0x23BB45CC67DD9800LL, sz));
	AssertString("MORE node DATA", sz);

	AssertTrue(cAccess.PutLongString(0x23BB54CC00DD0000LL, "Another DATUM of doom"));
	AssertInt(4, cIndexTree.NumElements());

	AssertNotNull(cAccess.GetLongString(0x23BB54CC00DD0000LL, sz));
	AssertString("Another DATUM of doom", sz);

	AssertTrue(cAccess.PutLongString(0x23BB45CC67DD9800LL, "Changed your data lengh"));
	AssertInt(4, cIndexTree.NumElements());
	AssertLongLongInt(25, pcMemory->GetTotalAllocations());

	AssertNotNull(cAccess.GetLongString(0x23BB45CC67DD9800LL, sz));
	AssertString("Changed your data lengh", sz);
	AssertNotNull(cAccess.GetLongString(0x0000000000000000LL, sz));
	AssertString("Zero", sz);
	AssertNotNull(cAccess.GetLongString(0x23BB45CC67DD89EELL, sz));
	AssertString("Character Count & Word Count Tool is a free character counter tool that provides instant character count & word count statistics for a given text. The tool reports the number of character with spaces and without spaces, also the number of words and sent.", sz);
	AssertNotNull(cAccess.GetLongString(0x23BB54CC00DD0000LL, sz));
	AssertString("Another DATUM of doom", sz);

	AssertTrue(cAccess.PutLongString(0x23BB45CC67DD89EELL, "Make the long int16."));
	AssertInt(4, cIndexTree.NumElements());
	AssertLongLongInt(25, pcMemory->GetTotalAllocations());

	AssertNotNull(cAccess.GetLongString(0x23BB45CC67DD9800LL, sz));
	AssertString("Changed your data lengh", sz);
	AssertNotNull(cAccess.GetLongString(0x0000000000000000LL, sz));
	AssertString("Zero", sz);
	AssertNotNull(cAccess.GetLongString(0x23BB45CC67DD89EELL, sz));
	AssertString("Make the long int16.", sz);
	AssertNotNull(cAccess.GetLongString(0x23BB54CC00DD0000LL, sz));
	AssertString("Another DATUM of doom", sz);

	AssertFalse(cAccess.DeleteLong(0x0000000000000001LL));
	AssertFalse(cAccess.DeleteLong(0xFF00000000000000LL));
	AssertTrue(cAccess.DeleteLong(0x0000000000000000LL));
	AssertInt(3, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertNotNull(cAccess.GetLongString(0x23BB45CC67DD9800LL, sz));
	AssertString("Changed your data lengh", sz);
	AssertNotNull(cAccess.GetLongString(0x23BB45CC67DD89EELL, sz));
	AssertString("Make the long int16.", sz);
	AssertNotNull(cAccess.GetLongString(0x23BB54CC00DD0000LL, sz));
	AssertString("Another DATUM of doom", sz);
	AssertLongLongInt(17, pcMemory->GetTotalAllocations());

	AssertTrue(cAccess.DeleteLong(0x23BB45CC67DD9800LL));
	AssertInt(2, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree());
	AssertNull(cAccess.GetLongString(0x23BB45CC67DD9800LL, sz));

	AssertNotNull(cAccess.GetLongString(0x23BB45CC67DD89EELL, sz));
	AssertString("Make the long int16.", sz);
	AssertNotNull(cAccess.GetLongString(0x23BB54CC00DD0000LL, sz));
	AssertString("Another DATUM of doom", sz);
	AssertLongLongInt(15, pcMemory->GetTotalAllocations());

	avp.Init();
	cIndexTree.FindAll(&avp);
	AssertInt(2, avp.NumElements());
	avp.Kill();

	AssertTrue(cAccess.DeleteLong(0x23BB54CC00DD0000LL));
	AssertInt(1, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree());
	AssertNull(cAccess.GetLongString(0x23BB54CC00DD0000LL, sz));

	avp.Init();
	cIndexTree.FindAll(&avp);
	AssertInt(1, avp.NumElements());
	avp.Kill();

	AssertNotNull(cAccess.GetLongString(0x23BB45CC67DD89EELL, sz));
	AssertString("Make the long int16.", sz);
	AssertLongLongInt(9, pcMemory->GetTotalAllocations());

	AssertTrue(cAccess.DeleteLong(0x23BB45CC67DD89EELL));
	AssertInt(0, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree());
	AssertNull(cAccess.GetLongString(0x23BB45CC67DD89EELL, sz));
	AssertLongLongInt(1, pcMemory->GetTotalAllocations());

	cAccess.Kill();
	cIndexTree.Kill();
	AssertLongLongInt(0, pcMemory->GetTotalAllocations());
	AssertLongLongInt(0, pcMemory->GetTotalAllocatedMemory());

	cMemoryAllocator.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryComplexMemoryAllocatorLittleEndian(void)
{
	//This is Intel style.  The most significant part of the key goes at the end of the long.

	CMemoryAllocator		cMemoryAllocator;
	CIndexTreeMemory		cIndexTree;
	CIndexTreeMemoryAccess	cAccess;
	CGeneralMemory*			pcMemory;
	char					sz[MAX_UCHAR];
	CArrayVoidPtr			avp;
	SLogConfig				sLogConfig;

	cMemoryAllocator.Init(16);
	pcMemory = cMemoryAllocator.GetMemory();

	cIndexTree.Init(LifeLocal<CMallocator>(&cMemoryAllocator), IKR_Yes, 255, MAX_KEY_SIZE);
	cAccess.Init(&cIndexTree);

	AssertTrue(cAccess.PutLongString(0x0000000000000000LL, "Zero"));
	AssertInt(1, cIndexTree.NumElements());

	AssertNotNull(cAccess.GetLongString(0x0000000000000000LL, sz));
	AssertString("Zero", sz);

	AssertNull(cAccess.GetLongString(0x0100000000000000LL, sz));
		
	sLogConfig = gcLogger.SetSilent();
	AssertFalse(cAccess.PutLongString(0xEE89DD67CC45BB23LL, "Character Count & Word Count Tool is a free character counter tool that provides instant character count & word count statistics for a given text. The tool reports the number of character with spaces and without spaces, also the number of words and sente."));
	gcLogger.SetConfig(&sLogConfig);
	AssertTrue(cAccess.PutLongString(0xEE89DD67CC45BB23LL, "Character Count & Word Count Tool is a free character counter tool that provides instant character count & word count statistics for a given text. The tool reports the number of character with spaces and without spaces, also the number of words and sent."));
	AssertInt(2, cIndexTree.NumElements());

	AssertNotNull(cAccess.GetLongString(0xEE89DD67CC45BB23LL, sz));
	AssertString("Character Count & Word Count Tool is a free character counter tool that provides instant character count & word count statistics for a given text. The tool reports the number of character with spaces and without spaces, also the number of words and sent.", sz);
	
	AssertTrue(cAccess.PutLongString(0x0098DD67CC45BB23LL, "MORE node DATA"));
	AssertInt(3, cIndexTree.NumElements());

	AssertNotNull(cAccess.GetLongString(0x0098DD67CC45BB23LL, sz));
	AssertString("MORE node DATA", sz);
	
	AssertTrue(cAccess.PutLongString(0x0000DD00CC54BB23LL, "Another DATUM of doom"));
	AssertInt(4, cIndexTree.NumElements());

	AssertNotNull(cAccess.GetLongString(0x0000DD00CC54BB23LL, sz));
	AssertString("Another DATUM of doom", sz);

	AssertTrue(cAccess.PutLongString(0x0098DD67CC45BB23LL, "Changed your data lengh"));
	AssertInt(4, cIndexTree.NumElements());
	AssertLongLongInt(30, pcMemory->GetTotalAllocations());

	AssertNotNull(cAccess.GetLongString(0x0098DD67CC45BB23LL, sz));
	AssertString("Changed your data lengh", sz);
	AssertNotNull(cAccess.GetLongString(0x0000000000000000LL, sz));
	AssertString("Zero", sz);
	AssertNotNull(cAccess.GetLongString(0xEE89DD67CC45BB23LL, sz));
	AssertString("Character Count & Word Count Tool is a free character counter tool that provides instant character count & word count statistics for a given text. The tool reports the number of character with spaces and without spaces, also the number of words and sent.", sz);
	AssertNotNull(cAccess.GetLongString(0x0000DD00CC54BB23LL, sz));
	AssertString("Another DATUM of doom", sz);

	AssertTrue(cAccess.PutLongString(0xEE89DD67CC45BB23LL, "Make the long int16."));
	AssertInt(4, cIndexTree.NumElements());
	AssertLongLongInt(30, pcMemory->GetTotalAllocations());

	AssertNotNull(cAccess.GetLongString(0x0098DD67CC45BB23LL, sz));
	AssertString("Changed your data lengh", sz);
	AssertNotNull(cAccess.GetLongString(0x0000000000000000LL, sz));
	AssertString("Zero", sz);
	AssertNotNull(cAccess.GetLongString(0xEE89DD67CC45BB23LL, sz));
	AssertString("Make the long int16.", sz);
	AssertNotNull(cAccess.GetLongString(0x0000DD00CC54BB23LL, sz));
	AssertString("Another DATUM of doom", sz);

	AssertFalse(cAccess.DeleteLong(0x0100000000000000LL));
	AssertFalse(cAccess.DeleteLong(0x00000000000000FFLL));
	AssertTrue(cAccess.DeleteLong(0x0000000000000000LL));
	AssertInt(3, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree());

	AssertNotNull(cAccess.GetLongString(0x0098DD67CC45BB23LL, sz));
	AssertString("Changed your data lengh", sz);
	AssertNotNull(cAccess.GetLongString(0xEE89DD67CC45BB23LL, sz));
	AssertString("Make the long int16.", sz);
	AssertNotNull(cAccess.GetLongString(0x0000DD00CC54BB23LL, sz));
	AssertString("Another DATUM of doom", sz);
	AssertLongLongInt(24, pcMemory->GetTotalAllocations());

	AssertTrue(cAccess.DeleteLong(0x0098DD67CC45BB23LL));
	AssertInt(2, cIndexTree.NumElements());
	AssertTrue(cIndexTree.ValidateIndexTree());
	AssertNull(cAccess.GetLongString(0x0098DD67CC45BB23LL, sz));

	AssertNotNull(cAccess.GetLongString(0xEE89DD67CC45BB23LL, sz));
	AssertString("Make the long int16.", sz);
	AssertNotNull(cAccess.GetLongString(0x0000DD00CC54BB23LL, sz));
	AssertString("Another DATUM of doom", sz);
	AssertLongLongInt(17, pcMemory->GetTotalAllocations());

	avp.Init();
	cIndexTree.FindAll(&avp);
	AssertInt(2, avp.NumElements());
	avp.Kill();

	AssertTrue(cAccess.DeleteLong(0x0000DD00CC54BB23LL));
	AssertTrue(cIndexTree.ValidateIndexTree());
	AssertInt(1, cIndexTree.NumElements());
	AssertNull(cAccess.GetLongString(0x0000DD00CC54BB23LL, sz));

	avp.Init();
	cIndexTree.FindAll(&avp);
	AssertInt(1, avp.NumElements());
	avp.Kill();

	AssertNotNull(cAccess.GetLongString(0xEE89DD67CC45BB23LL, sz));
	AssertString("Make the long int16.", sz);
	AssertLongLongInt(9, pcMemory->GetTotalAllocations());

	AssertTrue(cAccess.DeleteLong(0xEE89DD67CC45BB23LL));
	AssertTrue(cIndexTree.ValidateIndexTree());
	AssertInt(0, cIndexTree.NumElements());
	AssertNull(cAccess.GetLongString(0xEE89DD67CC45BB23LL, sz));
	AssertLongLongInt(1, pcMemory->GetTotalAllocations());

	cAccess.Kill();
	cIndexTree.Kill();
	AssertLongLongInt(0, pcMemory->GetTotalAllocations());
	AssertLongLongInt(0, pcMemory->GetTotalAllocatedMemory());

	cMemoryAllocator.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemoryPutResize(void)
{
	CIndexTreeMemory		cIndexTree;
	CIndexTreeMemoryAccess	cAccess;
	char					sz120[] = "A0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567";
	char					sz100[] = "B01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567";
	char					sz80[] =  "C012345678901234567890123456789012345678901234567890123456789012345678901234567";
	char					sz60[] =  "D0123456789012345678901234567890123456789012345678901234567";
	char					szStuff[] = "Stuff";
	char					szResult[256];
	char*					pszEmpty;

	cIndexTree.Init(IKR_Yes);
	cAccess.Init(&cIndexTree);

	cAccess.PutStringString("555", sz120);
	cAccess.GetStringString("555", szResult);
	AssertString(sz120, szResult);

	cAccess.PutStringString("555", sz100);
	cAccess.GetStringString("555", szResult);
	AssertString(sz100, szResult);

	cAccess.PutStringString("555", sz80);
	cAccess.GetStringString("555", szResult);
	AssertString(sz80, szResult);

	cAccess.PutStringString("555", sz60);
	cAccess.GetStringString("555", szResult);
	AssertString(sz60, szResult);

	cAccess.PutStringString("555", sz80);
	cAccess.GetStringString("555", szResult);
	AssertString(sz80, szResult);

	cAccess.PutStringString("555", sz100);
	cAccess.GetStringString("555", szResult);
	AssertString(sz100, szResult);

	cAccess.PutStringString("555", sz120);
	cAccess.GetStringString("555", szResult);
	AssertString(sz120, szResult);


	cAccess.PutStringString("5555", szStuff);
	cAccess.GetStringString("5555", szResult);
	AssertString(szStuff, szResult);

	cAccess.PutStringString("555", sz100);
	cAccess.GetStringString("555", szResult);
	AssertString(sz100, szResult);

	cAccess.PutStringString("555", sz80);
	cAccess.GetStringString("555", szResult);
	AssertString(sz80, szResult);

	cAccess.PutStringString("555", sz60);
	cAccess.GetStringString("555", szResult);
	AssertString(sz60, szResult);

	cAccess.GetStringString("5555", szResult);
	AssertString(szStuff, szResult);


	cAccess.PutStringString("555", sz80);
	cAccess.GetStringString("555", szResult);
	AssertString(sz80, szResult);

	cAccess.PutStringString("555", sz100);
	cAccess.GetStringString("555", szResult);
	AssertString(sz100, szResult);

	cAccess.PutStringString("555", sz120);
	cAccess.GetStringString("555", szResult);
	AssertString(sz120, szResult);

	cAccess.GetStringString("5555", szResult);
	AssertString(szStuff, szResult);

	cAccess.DeleteString("5555");
	pszEmpty = cAccess.GetStringString("5555", szResult);
	AssertNull(pszEmpty);

	cAccess.PutStringString("555", sz100);
	cAccess.GetStringString("555", szResult);
	AssertString(sz100, szResult);

	cAccess.PutStringString("555", sz80);
	cAccess.GetStringString("555", szResult);
	AssertString(sz80, szResult);

	cAccess.PutStringString("555", sz60);
	cAccess.GetStringString("555", szResult);
	AssertString(sz60, szResult);

	cAccess.Kill();
	cIndexTree.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeMemory(void)
{
	//Most of the tests for IndexTreeMemory are done in the BaseLib.
	//This test just exists to remind me of that fact.

	FastFunctionsInit();
	TypeConverterInit();
	BeginTests();

	TestIndexTreeMemorySizeOfs();
	TestIndexTreeMemoryPutValidation();
	TestIndexTreeMemoryAllocation();
	TestIndexTreeMemoryComplexGlobalAllocator();
	TestIndexTreeMemoryComplexMemoryAllocatorLittleEndian();
	TestIndexTreeMemoryComplexMemoryAllocatorBigEndian();
	TestIndexTreeMemoryPutResize();

	TestStatistics();
	FastFunctionsKill();
	TypeConverterKill();
}

