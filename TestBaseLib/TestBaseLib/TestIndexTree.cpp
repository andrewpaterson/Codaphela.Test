#include "BaseLib/IndexTree.h"
#include "TestLib/Assert.h"
#include "TestIndexTreeObject.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeAdd(void)
{
	CIndexTree				cIndex;
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
void TestIndexTreeGet(void)
{
	CIndexTree				cIndex;
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
	cIndex.FindAll(&avp);
	AssertInt(3, avp.NumElements());
	avp.Kill();

	andre.Init("Andre");
	cIndex.PutPtr(&andre, andre.GetName());
	pcResult = (CTestIndexTreeObject**)cIndex.Get("Andre");
	AssertPointer(&andre, *pcResult);
	cIndex.FindAll(&avp);
	AssertInt(4, avp.NumElements());

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
void TestIndexTreePutDuplicate(void)
{
	CIndexTree				cIndex;
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
void TestIndexTreeValidateInternalConsistency(void)
{
	CIndexTree				cIndex;
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
void TestIndexTreeCountAllocatedNodes(void)
{
	CIndexTree				cIndex;
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
void TestIndexTreeRemoveByObject(void)
{
	CIndexTree cIndex;
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
	ppcRemoved = (CTestIndexTreeObject**)cIndex.Remove(object2.GetName());
	AssertPointer(&object2, *ppcRemoved);
	AssertInt(2, cIndex.NumElements());
	AssertNull(cIndex.Remove(object2.GetName()));
	AssertInt(2, cIndex.NumElements());

	AssertInt(13, cIndex.CountAllocatedNodes());
	cIndex.Remove(object3.GetName());

	AssertInt(1, cIndex.NumElements());
	AssertInt(8, cIndex.CountAllocatedNodes());

	cIndex.PutPtr(&object3, object3.GetName());
	AssertInt(13, cIndex.CountAllocatedNodes());

	AssertInt(2, cIndex.NumElements());
	ppcRemoved = (CTestIndexTreeObject**)cIndex.Remove(object3.GetName());
	AssertPointer(&object3, *ppcRemoved);
	AssertInt(1, cIndex.NumElements());
	ppcRemoved = (CTestIndexTreeObject**)cIndex.Remove(object1.GetName());
	AssertPointer(&object1, *ppcRemoved);
	AssertInt(0, cIndex.NumElements());

	AssertNull(cIndex.Remove(NULL));
	AssertNull(cIndex.Remove(""));

	cIndex.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeHasKey(void)
{
	CIndexTree				cIndex;
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
void TestIndexTreeRemoveNullNode(void)
{
	CIndexTree				cIndex;
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
void TestIndexTreeAddLongLong(void)
{
	CIndexTree		cIndex;
	long long		li;
	long long*		pli;

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
void TestIndexTree(void)
{
	BeginTests();

	TestIndexTreeAdd();
	TestIndexTreeGet();
	TestIndexTreePutDuplicate();
	TestIndexTreeValidateInternalConsistency();
	TestIndexTreeCountAllocatedNodes();
	TestIndexTreeRemoveByObject();
	TestIndexTreeHasKey();
	TestIndexTreeRemoveNullNode();
	TestIndexTreeAddLongLong();

	TestStatistics();
}

