#include "stdafx.h"
#include "SupportLib/Mesh.h"
#include "SupportLib/MeshEditor.h"
#include "SupportLib/MeshBoxEditor.h"
#include "SupportLib/MeshSmoothGroups.h"
#include "SupportLib/MeshSmoothFaces.h"
#include "SupportLib/MeshFlatFaces.h"
#include "SupportLib/MeshWriter.h"
#include "TestLib/Assert.h"
#include "TestNormalGeneration.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMeshSmoothGroupsOneAndZero(void)
{
	CMesh				cMesh;
	SFloat3				sXDirection;
	SFloat3				sYDirection;
	SFloat3				sZDirection;
	SFloat3				sStart;
	CMeshBoxEditor*		pcBoxEditor;
	CMeshEditor			cMeshEditor;
	CMeshSmoothGroups*	pcSmoothing;
	int					i;
	SMeshNormalFace*	psFaceNormal;
	CMeshFace*			pcFace;

	cMesh.Init();
	cMesh.mcNormals.mbInUse = TRUE;
	cMeshEditor.Init(&cMesh);

	sXDirection.Init(1, 0, 0);
	sYDirection.Init(0, 1, 0);
	sZDirection.Init(0, 0, 1);
	sStart.Init(-0.5f, -0.5f, -0.5f);

	pcBoxEditor = cMeshEditor.AddModifier<CMeshBoxEditor>();
	pcBoxEditor->Init(&sXDirection, &sYDirection, &sZDirection, &sStart, 2, 2, 2);

	pcSmoothing = cMeshEditor.AddModifier<CMeshSmoothGroups>();
	pcSmoothing->Init(1);

	cMeshEditor.Touch();

	AssertInt(48, cMesh.NumFaces());
	AssertInt(48, pcSmoothing->mcSmoothingGroups.NumElements());
	AssertInt(26, cMesh.NumCorners());
	AssertInt(48 + 26, cMesh.mcNormals.mcNormals.NumElements());

	for (i = 0; i < 48; i++)
	{
		psFaceNormal = cMesh.mcNormals.mcFaces.Get(i);
		pcFace = cMesh.GetFace(i);

		AssertInt(pcFace->asCorner[0] + 48, psFaceNormal->aiCornerNormals[0]);
		AssertInt(pcFace->asCorner[1] + 48, psFaceNormal->aiCornerNormals[1]);
		AssertInt(pcFace->asCorner[2] + 48, psFaceNormal->aiCornerNormals[2]);

		AssertInt(i, psFaceNormal->iFaceNormal);
	}

	WriteMesh(&cMesh, "Output/NormalsOne2x2x2.OBJ");

	pcSmoothing->SetAllGroups(0);

	cMeshEditor.Touch();

	AssertInt(48, cMesh.NumFaces());
	AssertInt(48, pcSmoothing->mcSmoothingGroups.NumElements());
	AssertInt(26, cMesh.NumCorners());
	AssertInt(48, cMesh.mcNormals.mcNormals.NumElements());

	for (i = 0; i < 48; i++)
	{
		psFaceNormal = cMesh.mcNormals.mcFaces.Get(i);

		AssertInt(i, psFaceNormal->aiCornerNormals[0]);
		AssertInt(i, psFaceNormal->aiCornerNormals[1]);
		AssertInt(i, psFaceNormal->aiCornerNormals[2]);

		AssertInt(i, psFaceNormal->iFaceNormal);
	}

	WriteMesh(&cMesh, "Output/NormalsZero2x2x2.OBJ");

	cMeshEditor.RemoveModifiers();

	cMesh.Kill();
	cMeshEditor.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMeshSmoothGroupsNamed(void)
{
	CMesh				cMesh;
	SFloat3				sXDirection;
	SFloat3				sYDirection;
	SFloat3				sZDirection;
	SFloat3				sStart;
	CMeshBoxEditor*		pcBoxEditor;
	CMeshEditor			cMeshEditor;
	CMeshSmoothGroups*	pcSmoothing;

	cMesh.Init();
	cMesh.mcNormals.mbInUse = TRUE;
	cMeshEditor.Init(&cMesh);

	sXDirection.Init(1, 0, 0);
	sYDirection.Init(0, 1, 0);
	sZDirection.Init(0, 0, 1);
	sStart.Init(-0.5f, -0.5f, -0.5f);

	pcBoxEditor = cMeshEditor.AddModifier<CMeshBoxEditor>();
	pcBoxEditor->Init(&sXDirection, &sYDirection, &sZDirection, &sStart, 2, 2, 2);

	pcSmoothing = cMeshEditor.AddModifier<CMeshSmoothGroups>();
	pcSmoothing->Init();
	pcSmoothing->meGenerationStyle = SGS_Name;

	cMeshEditor.Touch();

	AssertInt(48, cMesh.NumFaces());
	AssertInt(48, pcSmoothing->mcSmoothingGroups.NumElements());
	AssertInt(26, cMesh.NumCorners());
	AssertInt(72, cMesh.NumEdges());
	AssertInt(48, cMeshEditor.NumVisibleEdges(1));
	AssertInt(6, cMeshEditor.mcPolygons.NumUniqueNames());
	AssertInt(48 + 54, cMesh.mcNormals.mcNormals.NumElements());

	WriteMesh(&cMesh, "Output/NormalsNamed2x2x2.OBJ");

	cMeshEditor.RemoveModifiers();

	cMesh.Kill();
	cMeshEditor.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMeshSmoothFaces(void)
{
	CMesh				cMesh;
	SFloat3				sXDirection;
	SFloat3				sYDirection;
	SFloat3				sZDirection;
	SFloat3				sStart;
	CMeshBoxEditor*		pcBoxEditor;
	CMeshEditor			cMeshEditor;
	CMeshSmoothFaces*	pcSmoothing;
	int					i;
	SMeshNormalFace*	psFaceNormal;
	CMeshFace*			pcFace;

	cMesh.Init();
	cMesh.mcNormals.mbInUse = TRUE;
	cMeshEditor.Init(&cMesh);

	sXDirection.Init(1, 0, 0);
	sYDirection.Init(0, 1, 0);
	sZDirection.Init(0, 0, 1);
	sStart.Init(-0.5f, -0.5f, -0.5f);

	pcBoxEditor = cMeshEditor.AddModifier<CMeshBoxEditor>();
	pcBoxEditor->Init(&sXDirection, &sYDirection, &sZDirection, &sStart, 2, 2, 2);

	pcSmoothing = cMeshEditor.AddModifier<CMeshSmoothFaces>();
	pcSmoothing->Init();

	cMeshEditor.Touch();

	AssertInt(48, cMesh.NumFaces());
	AssertInt(26, cMesh.NumCorners());
	AssertInt(48 + 26, cMesh.mcNormals.mcNormals.NumElements());

	for (i = 0; i < 48; i++)
	{
		psFaceNormal = cMesh.mcNormals.mcFaces.Get(i);
		pcFace = cMesh.GetFace(i);

		AssertInt(pcFace->asCorner[0] + 48, psFaceNormal->aiCornerNormals[0]);
		AssertInt(pcFace->asCorner[1] + 48, psFaceNormal->aiCornerNormals[1]);
		AssertInt(pcFace->asCorner[2] + 48, psFaceNormal->aiCornerNormals[2]);

		AssertInt(i, psFaceNormal->iFaceNormal);
	}

	WriteMesh(&cMesh, "Output/NormalsSmooth2x2x2.OBJ");

	cMeshEditor.RemoveModifiers();

	cMesh.Kill();
	cMeshEditor.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMeshFlatFaces(void)
{
	CMesh				cMesh;
	SFloat3				sXDirection;
	SFloat3				sYDirection;
	SFloat3				sZDirection;
	SFloat3				sStart;
	CMeshBoxEditor*		pcBoxEditor;
	CMeshEditor			cMeshEditor;
	CMeshFlatFaces*		pcSmoothing;
	int					i;
	SMeshNormalFace*	psFaceNormal;

	cMesh.Init();
	cMesh.mcNormals.mbInUse = TRUE;
	cMeshEditor.Init(&cMesh);

	sXDirection.Init(1, 0, 0);
	sYDirection.Init(0, 1, 0);
	sZDirection.Init(0, 0, 1);
	sStart.Init(-0.5f, -0.5f, -0.5f);

	pcBoxEditor = cMeshEditor.AddModifier<CMeshBoxEditor>();
	pcBoxEditor->Init(&sXDirection, &sYDirection, &sZDirection, &sStart, 2, 2, 2);

	pcSmoothing = cMeshEditor.AddModifier<CMeshFlatFaces>();
	pcSmoothing->Init();

	cMeshEditor.Touch();

	AssertInt(48, cMesh.NumFaces());
	AssertInt(26, cMesh.NumCorners());
	AssertInt(48, cMesh.mcNormals.mcNormals.NumElements());

	for (i = 0; i < 48; i++)
	{
		psFaceNormal = cMesh.mcNormals.mcFaces.Get(i);

		AssertInt(i, psFaceNormal->aiCornerNormals[0]);
		AssertInt(i, psFaceNormal->aiCornerNormals[1]);
		AssertInt(i, psFaceNormal->aiCornerNormals[2]);

		AssertInt(i, psFaceNormal->iFaceNormal);
	}

	WriteMesh(&cMesh, "Output/NormalsFlat2x2x2.OBJ");

	cMeshEditor.RemoveModifiers();

	cMesh.Kill();
	cMeshEditor.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNormalGeneration(void)
{
	BeginTests();

	TestMeshSmoothGroupsOneAndZero();
	TestMeshSmoothGroupsNamed();
	TestMeshSmoothFaces();
	TestMeshFlatFaces();

	TestStatistics();
}

