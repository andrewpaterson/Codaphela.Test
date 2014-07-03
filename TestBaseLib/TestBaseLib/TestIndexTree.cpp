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
	bResult = cIndex.Put(&a, sizeof(void*), a.GetName());
	AssertTrue(bResult);

	pcNode = cIndex.GetIndexNode("A");
	ppvTest = (CTestIndexTreeObject**)pcNode->GetObjectPtr();
	AssertPointer(&a, *ppvTest);

	aa.Init("AA");
	bResult = cIndex.Put(&aa, sizeof(void*), aa.GetName());
	AssertTrue(bResult);

	pcNode = cIndex.GetIndexNode("A");
	ppvTest = (CTestIndexTreeObject**)pcNode->GetObjectPtr();
	AssertPointer(&a, *ppvTest);

	pcNode = cIndex.GetIndexNode("AA");
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
	bResult = cIndex.Put(&temp, sizeof(void*), NULL);
	AssertFalse(bResult);
	bResult = cIndex.Put(&temp, sizeof(void*), "");
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
	cIndex.Put(&andrew, sizeof(void*), andrew.GetName());
	pcResult = (CTestIndexTreeObject**)cIndex.Get("Andrew");
	AssertPointer(*pcResult, &andrew);
	avp.Init();
	cIndex.FindAll(&avp);
	AssertInt(1, avp.NumElements());
	avp.Kill();

	batman.Init("Batman");
	cIndex.Put(&batman, sizeof(void*), batman.GetName());
	pcNodeBatman = cIndex.GetIndexNode("Batman");
	AssertInt(0, pcNodeBatman->GetNumIndexes());
	pcResult = (CTestIndexTreeObject**)cIndex.Get("Batman");
	AssertPointer(*pcResult, &batman);
	cIndex.FindAll(&avp);
	AssertInt(2, avp.NumElements());
	avp.Kill();

	szBatmam = "Batmam";
	batmam.Init(szBatmam);
	cIndex.Put(&batmam, sizeof(void*), szBatmam);
	pcNodeBatman = cIndex.GetIndexNode("Batman");
	pcNodeBatmam = cIndex.GetIndexNode(szBatmam);
	pcResult = (CTestIndexTreeObject**)cIndex.Get(szBatmam);
	AssertPointer(&batmam, *pcResult);
	cIndex.FindAll(&avp);
	AssertInt(3, avp.NumElements());
	avp.Kill();

	andre.Init("Andre");
	cIndex.Put(&andre, sizeof(void*), andre.GetName());
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
	bResult = cIndex.Put(&andrew, sizeof(void*), andrew.mszName);
	AssertTrue(bResult);

	andrewToo.Init("Andrew");
	bResult = cIndex.Put(&andrewToo, sizeof(void*), andrewToo.GetName());
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

	cIndex.Put(&cObject, sizeof(void*), "tonic");
	cIndex.Put(&cObject, sizeof(void*), "topia");
	cIndex.Put(&cObject, sizeof(void*), "topic");
	cIndex.Put(&cObject, sizeof(void*), "totem");
	cIndex.Put(&cObject, sizeof(void*), "tower");
	cIndex.Put(&cObject, sizeof(void*), "tracter");
	cIndex.Put(&cObject, sizeof(void*), "traction");
	cIndex.Put(&cObject, sizeof(void*), "trahend");
	cIndex.Put(&cObject, sizeof(void*), "translucence");
	cIndex.Put(&cObject, sizeof(void*), "translucency");
	cIndex.Put(&cObject, sizeof(void*), "transparentness");
	cIndex.Put(&cObject, sizeof(void*), "tread");
	cIndex.Put(&cObject, sizeof(void*), "treasurer");
	cIndex.Put(&cObject, sizeof(void*), "treasurership");
	cIndex.Put(&cObject, sizeof(void*), "treasury");
	cIndex.Put(&cObject, sizeof(void*), "trench");
	cIndex.Put(&cObject, sizeof(void*), "triangularity");
	cIndex.Put(&cObject, sizeof(void*), "tribe");
	cIndex.Put(&cObject, sizeof(void*), "triplication");
	cIndex.Put(&cObject, sizeof(void*), "truncation");
	cIndex.Put(&cObject, sizeof(void*), "trunk");
	cIndex.Put(&cObject, sizeof(void*), "tunic");
	cIndex.Put(&cObject, sizeof(void*), "tunnel");
	cIndex.Put(&cObject, sizeof(void*), "tutor");
	cIndex.Put(&cObject, sizeof(void*), "tutorship");

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
	cIndex.Put(&cType, sizeof(void*), cType.GetName());

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

	cIndex.Put(&cZebra, sizeof(void*), cZebra.GetName());
	pvResult = (CTestIndexTreeObject**)cIndex.Get("Zebra");
	AssertPointer(&cZebra, *pvResult);
	AssertInt(6, cIndex.CountAllocatedNodes());

	cIndex.Put(&cAardvark, sizeof(void*), cAardvark.GetName());
	pvResult = (CTestIndexTreeObject**)cIndex.Get("Aardvark");
	AssertPointer(&cAardvark, *pvResult);
	AssertInt(14, cIndex.CountAllocatedNodes());

	cIndex.Put(&cAardvar, sizeof(void*), cAardvar.GetName());
	pvResult = (CTestIndexTreeObject**)cIndex.Get("Aardvar");
	AssertPointer(&cAardvar, *pvResult);
	AssertInt(14, cIndex.CountAllocatedNodes());

	cIndex.Put(&cAardvarc, sizeof(void*), cAardvarc.GetName());
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
	cIndex.Put(&object1, sizeof(void*), object1.GetName());
	AssertInt(8, cIndex.CountAllocatedNodes());

	object2.Init("dendrodra");
	cIndex.Put(&object2, sizeof(void*), object2.GetName());

	object3.Init("dendrons");
	cIndex.Put(&object3, sizeof(void*), object3.GetName());

	AssertInt(3, cIndex.GetSize());
	ppcRemoved = (CTestIndexTreeObject**)cIndex.Remove(object2.GetName());
	AssertPointer(&object2, *ppcRemoved);
	AssertInt(2, cIndex.GetSize());
	AssertNull(cIndex.Remove(object2.GetName()));
	AssertInt(2, cIndex.GetSize());

	AssertInt(13, cIndex.CountAllocatedNodes());
	cIndex.Remove(object3.GetName());

	AssertInt(1, cIndex.GetSize());
	AssertInt(8, cIndex.CountAllocatedNodes());

	cIndex.Put(&object3, sizeof(void*), object3.GetName());
	AssertInt(13, cIndex.CountAllocatedNodes());

	AssertInt(2, cIndex.GetSize());
	ppcRemoved = (CTestIndexTreeObject**)cIndex.Remove(object3.GetName());
	AssertPointer(&object3, *ppcRemoved);
	AssertInt(1, cIndex.GetSize());
	ppcRemoved = (CTestIndexTreeObject**)cIndex.Remove(object1.GetName());
	AssertPointer(&object1, *ppcRemoved);
	AssertInt(0, cIndex.GetSize());

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

	cIndex.Put(&cObject, sizeof(void*), "fabaceous");
	cIndex.Put(&cObject, sizeof(void*), "fabled");
	cIndex.Put(&cObject, sizeof(void*), "fabricative");
	cIndex.Put(&cObject, sizeof(void*), "fabulous");
	cIndex.Put(&cObject, sizeof(void*), "face-centered");
	cIndex.Put(&cObject, sizeof(void*), "face-centred");
	cIndex.Put(&cObject, sizeof(void*), "face-saving");
	cIndex.Put(&cObject, sizeof(void*), "faceable");
	cIndex.Put(&cObject, sizeof(void*), "faceless");
	cIndex.Put(&cObject, sizeof(void*), "facete");
	cIndex.Put(&cObject, sizeof(void*), "facetious");
	cIndex.Put(&cObject, sizeof(void*), "facile");

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

	cIndex.Put(&cObject, sizeof(void*), "aaa");
	cIndex.Put(&cObject, sizeof(void*), "aab");

	AssertInt(2, cIndex.GetSize());
	AssertInt(2, cIndex.RecurseSize());

	cIndex.Remove("a");

	AssertInt(2, cIndex.GetSize());
	AssertInt(2, cIndex.RecurseSize());

	cIndex.Remove("aaa");

	AssertInt(1, cIndex.GetSize());
	AssertInt(1, cIndex.RecurseSize());

	cIndex.Remove("aaa");

	AssertInt(1, cIndex.GetSize());
	AssertInt(1, cIndex.RecurseSize());

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

	TestStatistics();
}

