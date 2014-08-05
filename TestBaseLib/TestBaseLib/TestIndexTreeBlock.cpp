#include "BaseLib/IndexTreeBlock.h"
#include "BaseLib/TrackingAllocator.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/MemoryFile.h"
#include "TestLib/Assert.h"
#include "TestIndexTreeObject.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockAdd(void)
{
	CIndexTreeBlock			cIndex;
	CTestIndexTreeObject	a;
	CTestIndexTreeObject	aa;
	CTestIndexTreeObject	temp;
	CArrayVoidPtr			avp;
	BOOL					bResult;
	CIndexTreeNode*			pcNode;
	CTestIndexTreeObject**	ppvTest;
	CTestIndexTreeObject***	ppvTestA;
	CTestIndexTreeObject***	ppvTestAA;

	cIndex.Init();
	a.Init("A");
	bResult = cIndex.PutPtr(&a, a.GetName());
	AssertTrue(bResult);

	pcNode = cIndex.GetIndexNode("A", 1);
	ppvTest = (CTestIndexTreeObject**)pcNode->GetObjectPtr();
	AssertPointer(&a, *ppvTest);

	aa.Init("AA");
	bResult = cIndex.PutPtr(&aa, aa.GetName());
	AssertTrue(bResult);

	pcNode = cIndex.GetIndexNode("A", 1);
	ppvTest = (CTestIndexTreeObject**)pcNode->GetObjectPtr();
	AssertPointer(&a, *ppvTest);

	pcNode = cIndex.GetIndexNode("AA", 2);
	ppvTest = (CTestIndexTreeObject**)pcNode->GetObjectPtr();
	AssertPointer(&aa, *ppvTest);

	avp.Init();
	cIndex.FindAll(&avp);
	AssertInt(2, avp.NumElements());
	ppvTestA = (CTestIndexTreeObject***)avp.Get(0);
	ppvTestAA = (CTestIndexTreeObject***)avp.Get(1);
	AssertPointer(&a, **ppvTestA);
	AssertPointer(&aa, **ppvTestAA);
	AssertString("A", (**ppvTestA)->mszName);
	AssertString("AA", (**ppvTestAA)->mszName);

	avp.Kill();
	cIndex.Kill();

	cIndex.Init();
	bResult = cIndex.PutPtr(&temp, NULL);
	AssertFalse(bResult);
	bResult = cIndex.PutPtr(&temp, "");
	AssertFalse(bResult);

	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockGet(void)
{
	CIndexTreeBlock			cIndex;
	CTestIndexTreeObject	andrew;
	CTestIndexTreeObject**	pcResult;
	CArrayVoidPtr			avp;
	CTestIndexTreeObject	batman;
	CTestIndexTreeObject	batmam;
	CTestIndexTreeObject	andre;
	CIndexTreeNode*			pcNodeBatman;
	CIndexTreeNode*			pcNodeBatmam;
	char*					szBatmam;

	cIndex.Init();

	andrew.Init("Andrew");
	cIndex.PutPtr(&andrew, andrew.GetName());
	pcResult = (CTestIndexTreeObject**)cIndex.Get("Andrew");
	AssertPointer(*pcResult, &andrew);
	avp.Init();
	cIndex.FindAll(&avp);
	AssertInt(1, avp.NumElements());
	avp.Kill();

	batman.Init("Batman");
	cIndex.PutPtr(&batman, batman.GetName());
	pcNodeBatman = cIndex.GetIndexNode("Batman", 6);
	AssertInt(0, pcNodeBatman->GetNumIndexes());
	pcResult = (CTestIndexTreeObject**)cIndex.Get("Batman");
	AssertPointer(*pcResult, &batman);
	avp.Init();
	cIndex.FindAll(&avp);
	AssertInt(2, avp.NumElements());
	avp.Kill();

	szBatmam = "Batmam";
	batmam.Init(szBatmam);
	cIndex.PutPtr(&batmam, szBatmam);
	pcNodeBatman = cIndex.GetIndexNode("Batman", 6);
	pcNodeBatmam = cIndex.GetIndexNode(szBatmam, 6);
	pcResult = (CTestIndexTreeObject**)cIndex.Get(szBatmam);
	AssertPointer(&batmam, *pcResult);
	avp.Init();
	cIndex.FindAll(&avp);
	AssertInt(3, avp.NumElements());
	avp.Kill();

	andre.Init("Andre");
	cIndex.PutPtr(&andre, andre.GetName());
	pcResult = (CTestIndexTreeObject**)cIndex.Get("Andre");
	AssertPointer(&andre, *pcResult);
	avp.Init();
	cIndex.FindAll(&avp);
	AssertInt(4, avp.NumElements());
	avp.Kill();

	AssertNull(cIndex.Get(NULL));
	AssertNull(cIndex.Get(""));
	AssertNull(cIndex.Get("Batma"));
	AssertNull(cIndex.Get("Batmano"));
	AssertNull(cIndex.Get("Batmao"));

	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockPutDuplicate(void)
{
	CIndexTreeBlock			cIndex;
	CTestIndexTreeObject	andrew;
	CTestIndexTreeObject	andrewToo;
	CTestIndexTreeObject**	pcResult;
	CArrayVoidPtr			avp;
	BOOL					bResult;

	cIndex.Init();

	andrew.Init("Andrew");
	bResult = cIndex.PutPtr(&andrew, andrew.mszName);
	AssertTrue(bResult);

	andrewToo.Init("Andrew");
	bResult = cIndex.PutPtr(&andrewToo, andrewToo.GetName());
	AssertFalse(bResult);

	pcResult = (CTestIndexTreeObject**)cIndex.Get("Andrew");
	AssertPointer(&andrew, *pcResult);

	avp.Init();
	cIndex.FindAll(&avp);
	AssertInt(1, avp.NumElements());
	avp.Kill();

	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockValidateInternalConsistency(void)
{
	CIndexTreeBlock			cIndex;
	CTestIndexTreeObject	cObject;
	CTestIndexTreeObject	cType;
	CArrayVoidPtr			avp;

	cIndex.Init();

	cObject.Init("");

	cIndex.PutPtr(&cObject, "tonic");
	cIndex.PutPtr(&cObject, "topia");
	cIndex.PutPtr(&cObject, "topic");
	cIndex.PutPtr(&cObject, "totem");
	cIndex.PutPtr(&cObject, "tower");
	cIndex.PutPtr(&cObject, "tracter");
	cIndex.PutPtr(&cObject, "traction");
	cIndex.PutPtr(&cObject, "trahend");
	cIndex.PutPtr(&cObject, "translucence");
	cIndex.PutPtr(&cObject, "translucency");
	cIndex.PutPtr(&cObject, "transparentness");
	cIndex.PutPtr(&cObject, "tread");
	cIndex.PutPtr(&cObject, "treasurer");
	cIndex.PutPtr(&cObject, "treasurership");
	cIndex.PutPtr(&cObject, "treasury");
	cIndex.PutPtr(&cObject, "trench");
	cIndex.PutPtr(&cObject, "triangularity");
	cIndex.PutPtr(&cObject, "tribe");
	cIndex.PutPtr(&cObject, "triplication");
	cIndex.PutPtr(&cObject, "truncation");
	cIndex.PutPtr(&cObject, "trunk");
	cIndex.PutPtr(&cObject, "tunic");
	cIndex.PutPtr(&cObject, "tunnel");
	cIndex.PutPtr(&cObject, "tutor");
	cIndex.PutPtr(&cObject, "tutorship");

	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("tonic"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("topia"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("topic"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("totem"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("tower"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("tracter"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("traction"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("trahend"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("translucence"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("translucency"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("transparentness"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("tread"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("treasurer"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("treasurership"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("treasury"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("trench"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("triangularity"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("tribe"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("triplication"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("truncation"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("trunk"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("tunic"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("tunnel"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("tutor"));
	AssertPointer(&cObject, *(CTestIndexTreeObject**)cIndex.Get("tutorship"));

	cType.Init("type");
	cIndex.PutPtr(&cType, cType.GetName());

	AssertPointer(&cType, *(CTestIndexTreeObject**)cIndex.Get("type"));

	avp.Init();
	cIndex.FindAll(&avp);
	AssertInt(26, avp.NumElements());
	avp.Kill();

	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockCountAllocatedNodes(void)
{
	CIndexTreeBlock			cIndex;
	CTestIndexTreeObject	cZebra;
	CTestIndexTreeObject	cAardvark;
	CTestIndexTreeObject	cAardvar;
	CTestIndexTreeObject	cAardvarc;
	CTestIndexTreeObject**	pvResult;

	cIndex.Init();

	AssertInt(1, cIndex.CountAllocatedNodes());

	cZebra.Init("Zebra");
	cAardvark.Init("Aardvark");
	cAardvar.Init("Aardvar");
	cAardvarc.Init("Aardvarc");

	cIndex.PutPtr(&cZebra, cZebra.GetName());
	pvResult = (CTestIndexTreeObject**)cIndex.Get("Zebra");
	AssertPointer(&cZebra, *pvResult);
	AssertInt(6, cIndex.CountAllocatedNodes());

	cIndex.PutPtr(&cAardvark, cAardvark.GetName());
	pvResult = (CTestIndexTreeObject**)cIndex.Get("Aardvark");
	AssertPointer(&cAardvark, *pvResult);
	AssertInt(14, cIndex.CountAllocatedNodes());

	cIndex.PutPtr(&cAardvar, cAardvar.GetName());
	pvResult = (CTestIndexTreeObject**)cIndex.Get("Aardvar");
	AssertPointer(&cAardvar, *pvResult);
	AssertInt(14, cIndex.CountAllocatedNodes());

	cIndex.PutPtr(&cAardvarc, cAardvarc.GetName());
	pvResult = (CTestIndexTreeObject**)cIndex.Get("Aardvarc");
	AssertPointer(&cAardvarc, *pvResult);
	AssertInt(15, cIndex.CountAllocatedNodes());

	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockRemoveByObject(void)
{
	CIndexTreeBlock			cIndex;
	CTestIndexTreeObject	object1;
	CTestIndexTreeObject	object2;
	CTestIndexTreeObject	object3;
	CTestIndexTreeObject**	ppcRemoved;

	cIndex.Init();

	AssertInt(1, cIndex.CountAllocatedNodes());

	object1.Init("denarii");
	cIndex.PutPtr(&object1, object1.GetName());
	AssertInt(8, cIndex.CountAllocatedNodes());

	object2.Init("dendrodra");
	cIndex.PutPtr(&object2, object2.GetName());

	object3.Init("dendrons");
	cIndex.PutPtr(&object3, object3.GetName());

	AssertInt(3, cIndex.NumElements());
	ppcRemoved = (CTestIndexTreeObject**)cIndex.Get(object2.GetName());
	AssertPointer(&object2, *ppcRemoved);
	AssertTrue(cIndex.Remove(object2.GetName()));
	ppcRemoved = (CTestIndexTreeObject**)cIndex.Get(object2.GetName());
	AssertNull(ppcRemoved);
	AssertInt(2, cIndex.NumElements());
	AssertFalse(cIndex.Remove(object2.GetName()));
	AssertInt(2, cIndex.NumElements());

	AssertInt(13, cIndex.CountAllocatedNodes());
	cIndex.Remove(object3.GetName());

	AssertInt(1, cIndex.NumElements());
	AssertInt(8, cIndex.CountAllocatedNodes());

	cIndex.PutPtr(&object3, object3.GetName());
	AssertInt(13, cIndex.CountAllocatedNodes());

	AssertInt(2, cIndex.NumElements());
	ppcRemoved = (CTestIndexTreeObject**)cIndex.Get(object3.GetName());
	AssertPointer(&object3, *ppcRemoved);
	AssertTrue(cIndex.Remove(object3.GetName()));
	ppcRemoved = (CTestIndexTreeObject**)cIndex.Get(object3.GetName());
	AssertNull(ppcRemoved);
	AssertInt(1, cIndex.NumElements());
	ppcRemoved = (CTestIndexTreeObject**)cIndex.Get(object1.GetName());
	AssertPointer(&object1, *ppcRemoved);
	AssertTrue(cIndex.Remove(object1.GetName()));
	ppcRemoved = (CTestIndexTreeObject**)cIndex.Get(object1.GetName());
	AssertNull(ppcRemoved);
	AssertInt(0, cIndex.NumElements());

	AssertFalse(cIndex.Remove(NULL));
	AssertFalse(cIndex.Remove(""));

	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockHasKey(void)
{
	CIndexTreeBlock			cIndex;
	CTestIndexTreeObject	cObject;

	cIndex.Init();
	cObject.Init("Not Important");

	cIndex.PutPtr(&cObject, "fabaceous");
	cIndex.PutPtr(&cObject, "fabled");
	cIndex.PutPtr(&cObject, "fabricative");
	cIndex.PutPtr(&cObject, "fabulous");
	cIndex.PutPtr(&cObject, "face-centered");
	cIndex.PutPtr(&cObject, "face-centred");
	cIndex.PutPtr(&cObject, "face-saving");
	cIndex.PutPtr(&cObject, "faceable");
	cIndex.PutPtr(&cObject, "faceless");
	cIndex.PutPtr(&cObject, "facete");
	cIndex.PutPtr(&cObject, "facetious");
	cIndex.PutPtr(&cObject, "facile");

	AssertFalse(cIndex.HasKey(NULL));
	AssertFalse(cIndex.HasKey(""));
	AssertFalse(cIndex.HasKey(" "));
	AssertFalse(cIndex.HasKey("fab"));
	AssertFalse(cIndex.HasKey("facilee"));

	AssertTrue(cIndex.HasKey("fabricative"));
	AssertTrue(cIndex.HasKey("fabled"));
	AssertTrue(cIndex.HasKey("fabulous"));
	AssertTrue(cIndex.HasKey("face-centered"));
	AssertTrue(cIndex.HasKey("fabaceous"));
	AssertTrue(cIndex.HasKey("face-centred"));
	AssertTrue(cIndex.HasKey("face-saving"));
	AssertTrue(cIndex.HasKey("faceable"));
	AssertTrue(cIndex.HasKey("faceless"));
	AssertTrue(cIndex.HasKey("facete"));
	AssertTrue(cIndex.HasKey("facetious"));
	AssertTrue(cIndex.HasKey("facile"));

	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockRemoveNullNode(void)
{
	CIndexTreeBlock			cIndex;
	CTestIndexTreeObject	cObject;

	cIndex.Init();
	cObject.Init("Not Important");

	cIndex.PutPtr(&cObject, "aaa");
	cIndex.PutPtr(&cObject, "aab");

	AssertInt(2, cIndex.NumElements());
	AssertInt(2, cIndex.RecurseSize());

	cIndex.Remove("a");

	AssertInt(2, cIndex.NumElements());
	AssertInt(2, cIndex.RecurseSize());

	cIndex.Remove("aaa");

	AssertInt(1, cIndex.NumElements());
	AssertInt(1, cIndex.RecurseSize());

	cIndex.Remove("aaa");

	AssertInt(1, cIndex.NumElements());
	AssertInt(1, cIndex.RecurseSize());

	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockAddLongLong(void)
{
	CIndexTreeBlock		cIndex;
	long long			li;
	long long*			pli;

	cIndex.Init();

	li = 0x88LL;
	cIndex.Put(&li, sizeof(long long), "GraphRoot");
	pli = (long long*)cIndex.Get("GraphRoot");
	AssertLongLongInt(li, *pli);

	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockRemoveResize(void)
{
	CIndexTreeBlock		cIndex;
	long long			li;
	CMemoryAllocator	cMemoryAlloc;
	CTrackingAllocator	cTrackingAlloc;
	int					iExpectedRootSize;

	cMemoryAlloc.Init();
	cTrackingAlloc.Init(&cMemoryAlloc);

	cIndex.Init(&cTrackingAlloc);
	AssertInt(1, cIndex.CountAllocatedNodes());
	AssertInt(0, cIndex.RecurseSize());
	iExpectedRootSize = sizeof(CIndexTreeNode*) * MAX_UCHAR + sizeof(CIndexTreeNode);
	AssertInt(1028, iExpectedRootSize);
	AssertInt(iExpectedRootSize, cTrackingAlloc.AllocatedSize());

	li = 0x77LL; cIndex.Put(&li, sizeof(long long), "M");
	AssertInt(2, cIndex.CountAllocatedNodes());
	AssertInt(1, cIndex.RecurseSize());
	AssertInt(1044, iExpectedRootSize + sizeof(CIndexTreeNode) + sizeof(long long));
	AssertInt(1044, cTrackingAlloc.AllocatedSize());

	li = 0x88LL; cIndex.Put(&li, sizeof(long long), "MA");
	AssertInt(1064, cTrackingAlloc.AllocatedSize());
	li = 0x99LL; cIndex.Put(&li, sizeof(long long), "MC");
	AssertInt(4, cIndex.CountAllocatedNodes());
	AssertInt(3, cIndex.RecurseSize());
	AssertInt(1088, cTrackingAlloc.AllocatedSize());

	li = 0xaaLL; cIndex.Put(&li, sizeof(long long), "MB");
	AssertInt(5, cIndex.CountAllocatedNodes());
	AssertInt(4, cIndex.RecurseSize());
	AssertInt(1104, cTrackingAlloc.AllocatedSize());

	li = 0xbbLL; cIndex.Put(&li, sizeof(long long), "MBP");
	AssertInt(6, cIndex.CountAllocatedNodes());
	AssertInt(5, cIndex.RecurseSize());
	AssertInt(5, cIndex.NumElements());
	AssertInt(1124, cTrackingAlloc.AllocatedSize());

	AssertLongLongInt(0xaaLL, *((long long*)cIndex.Get("MB")));
	cIndex.Remove("MB");
	AssertInt(6, cIndex.CountAllocatedNodes());
	AssertInt(4, cIndex.RecurseSize());
	AssertInt(4, cIndex.NumElements());
	AssertInt(1124, cTrackingAlloc.AllocatedSize());
	AssertNull(cIndex.Get("MB"));

	AssertLongLongInt(0xbbLL, *((long long*)cIndex.Get("MBP")));
	cIndex.Remove("MBP");
	AssertInt(4, cIndex.CountAllocatedNodes());
	AssertInt(3, cIndex.RecurseSize());
	AssertInt(3, cIndex.NumElements());
	AssertInt(1088, cTrackingAlloc.AllocatedSize());
	AssertNull(cIndex.Get("MBP"));

	AssertLongLongInt(0x99LL, *((long long*)cIndex.Get("MC")));
	AssertLongLongInt(0x88LL, *((long long*)cIndex.Get("MA")));
	cIndex.Remove("MA");
	AssertInt(3, cIndex.CountAllocatedNodes());
	AssertInt(2, cIndex.RecurseSize());
	AssertInt(2, cIndex.NumElements());
	AssertInt(1064, cTrackingAlloc.AllocatedSize());
	AssertNull(cIndex.Get("MA"));

	AssertLongLongInt(0x99LL, *((long long*)cIndex.Get("MC")));
	cIndex.Remove("MC");
	AssertInt(2, cIndex.CountAllocatedNodes());
	AssertInt(1, cIndex.RecurseSize());
	AssertInt(1, cIndex.NumElements());
	AssertInt(1044, cTrackingAlloc.AllocatedSize());
	AssertNull(cIndex.Get("MC"));

	AssertLongLongInt(0x77LL, *((long long*)cIndex.Get("M")));
	cIndex.Remove("M");
	AssertInt(1, cIndex.CountAllocatedNodes());
	AssertInt(0, cIndex.RecurseSize());
	AssertInt(0, cIndex.NumElements());
	AssertInt(1028, cTrackingAlloc.AllocatedSize());
	AssertNull(cIndex.Get("M"));

	cIndex.Kill();
	cTrackingAlloc.Kill();
	cMemoryAlloc.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockIterate(void)
{
	CFileBasic			cFile;
	CIndexTreeBlock		cIndex;
	SIndexTreeIterator	sIter;
	char*				szData;
	int					iDataSize;
	unsigned char		c;

	cIndex.Init();
	cIndex.Put("DENISA", 7, "AAA");
	cIndex.Put("FATJETA", 8, "AA");
	cIndex.Put("ARIANA", 7, "AAB");
	cIndex.Put("GEORGE", 7, "AAC");
	cIndex.Put("IRMA", 5, "AB");
	cIndex.Put("JULIANA", 8, "ABA");
	cIndex.Put("LULE", 5, "ABB");
	cIndex.Put("VENERA", 7, "C");
	cIndex.Put("PRANVERA", 9, "DDDD");
	cIndex.Put("PRIMERA", 8, "DD");
	AssertInt(14, cIndex.CountAllocatedNodes());
	AssertInt(10, cIndex.RecurseSize());
	AssertInt(10, cIndex.NumElements());

	AssertTrue(cIndex.StartIteration(&sIter, (void**)&szData, &iDataSize));
	AssertInt(8, iDataSize);
	AssertString("FATJETA", szData);

	AssertTrue(cIndex.Iterate(&sIter, (void**)&szData, &iDataSize));
	AssertInt(7, iDataSize);
	AssertString("DENISA", szData);

	AssertTrue(cIndex.Iterate(&sIter, (void**)&szData, &iDataSize));
	AssertInt(7, iDataSize);
	AssertString("ARIANA", szData);

	AssertTrue(cIndex.Iterate(&sIter, (void**)&szData, &iDataSize));
	AssertInt(7, iDataSize);
	AssertString("GEORGE", szData);

	AssertTrue(cIndex.Iterate(&sIter, (void**)&szData, &iDataSize));
	AssertInt(5, iDataSize);
	AssertString("IRMA", szData);

	AssertTrue(cIndex.Iterate(&sIter, (void**)&szData, &iDataSize));
	AssertInt(8, iDataSize);
	AssertString("JULIANA", szData);

	AssertTrue(cIndex.Iterate(&sIter, (void**)&szData, &iDataSize));
	AssertInt(5, iDataSize);
	AssertString("LULE", szData);

	AssertTrue(cIndex.Iterate(&sIter, (void**)&szData, &iDataSize));
	AssertInt(7, iDataSize);
	AssertString("VENERA", szData);

	AssertTrue(cIndex.Iterate(&sIter, (void**)&szData, &iDataSize));
	AssertInt(8, iDataSize);
	AssertString("PRIMERA", szData);

	AssertTrue(cIndex.Iterate(&sIter, (void**)&szData, &iDataSize));
	AssertInt(9, iDataSize);
	AssertString("PRANVERA", szData);

	AssertFalse(cIndex.Iterate(&sIter, (void**)&szData, &iDataSize));
	cIndex.Kill();

	cIndex.Init();
	AssertInt(1, cIndex.CountAllocatedNodes());
	AssertInt(0, cIndex.RecurseSize());
	AssertInt(0, cIndex.NumElements());

	AssertFalse(cIndex.StartIteration(&sIter, (void**)&szData, &iDataSize));
	cIndex.Kill();

	cIndex.Init();
	AssertInt(1, cIndex.CountAllocatedNodes());
	AssertInt(0, cIndex.RecurseSize());
	AssertInt(0, cIndex.NumElements());

	c = 255;
	cIndex.Put("Banks", 6, &c, 1);
	AssertString("Banks", (char*)cIndex.Get(&c, 1));
	AssertTrue(cIndex.StartIteration(&sIter, (void**)&szData, &iDataSize));
	AssertInt(6, iDataSize);
	AssertString("Banks", szData);

	AssertFalse(cIndex.Iterate(&sIter, (void**)&szData, &iDataSize));
	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlockReadWrite(void)
{
	CFileBasic			cFile;
	CIndexTreeBlock		cIndex;
	CIndexTreeBlock		cIndexIn;

	cIndex.Init();
	cIndex.Put("DENISA", 7, "AAA");
	cIndex.Put("FATJETA", 8, "AA");
	cIndex.Put("ARIANA", 7, "AAB");
	cIndex.Put("GEORGE", 7, "AAC");
	cIndex.Put("IRMA", 5, "AB");
	cIndex.Put("JULIANA", 8, "ABA");
	cIndex.Put("LULE", 5, "ABB");
	cIndex.Put("VENERA", 7, "C");
	cIndex.Put("PRANVERA", 9, "DDDD");
	cIndex.Put("PRIMERA", 8, "DD");
	AssertInt(14, cIndex.CountAllocatedNodes());
	AssertInt(10, cIndex.RecurseSize());
	AssertInt(10, cIndex.NumElements());

	cFile.Init(MemoryFile());
	cFile.Open(EFM_Write_Create);
	AssertTrue(cIndex.Write(&cFile));
	cIndex.Kill();
	cFile.Close();

	cFile.Open(EFM_Read);
	AssertTrue(cIndexIn.Read(&cFile));
	cFile.Close();

	AssertInt(14, cIndex.CountAllocatedNodes());
	AssertInt(10, cIndex.RecurseSize());
	AssertInt(10, cIndex.NumElements());
	AssertString("DENISA", (char*)cIndexIn.Get("AAA"));
	AssertString("FATJETA", (char*)cIndexIn.Get("AA"));
	AssertString("ARIANA", (char*)cIndexIn.Get("AAB"));
	AssertString("GEORGE", (char*)cIndexIn.Get("AAC"));
	AssertString("IRMA", (char*)cIndexIn.Get("AB"));
	AssertString("JULIANA", (char*)cIndexIn.Get("ABA"));
	AssertString("LULE", (char*)cIndexIn.Get("ABB"));
	AssertString("VENERA", (char*)cIndexIn.Get("C"));
	AssertString("PRANVERA", (char*)cIndexIn.Get("DDDD"));
	AssertString("PRIMERA", (char*)cIndexIn.Get("DD"));

	cIndexIn.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeBlock(void)
{
	BeginTests();
	FastFunctionsInit();
	MemoryInit();

	TestIndexTreeBlockAdd();
	TestIndexTreeBlockGet();
	TestIndexTreeBlockPutDuplicate();
	TestIndexTreeBlockValidateInternalConsistency();
	TestIndexTreeBlockCountAllocatedNodes();
	TestIndexTreeBlockRemoveResize();
	TestIndexTreeBlockRemoveByObject();
	TestIndexTreeBlockHasKey();
	TestIndexTreeBlockRemoveNullNode();
	TestIndexTreeBlockAddLongLong();
	TestIndexTreeBlockIterate();
	TestIndexTreeBlockReadWrite();

	MemoryKill();
	FastFunctionsKill();
	TestStatistics();
}

