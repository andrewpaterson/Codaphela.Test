#include "stdafx.h"
#include "SupportLib/Mesh.h"
#include "SupportLib/MeshReader.h"
#include "SupportLib/MeshWriter.h"
#include "TestLib/Assert.h"
#include "TestMeshOBJReader.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMeshOBJReader(void)
{
	CMesh				cMesh;
	BOOL				bResult;
	int					i;
	CMeshFace*			pcFace;
	BOOL				bOutOfBounds;
	int					iNumCorners;
	int					iNumNormals;
	SMeshNormalFace*	psNormalFace;

	cMesh.Init();
	bResult = ReadMesh(&cMesh, "Input/Smoothing.OBJ");

	iNumCorners = cMesh.NumCorners();
	iNumNormals = cMesh.mcNormals.mcNormals.NumElements();

	AssertBool(TRUE, bResult);
	AssertInt(162, iNumCorners);
	AssertInt(320, cMesh.NumFaces());
	AssertInt(320 + 394, iNumNormals);

	bOutOfBounds = FALSE;
	for (i = 0; i < cMesh.NumFaces(); i++)
	{
		pcFace = cMesh.GetFace(i);
		if (pcFace->asCorner[0] >= iNumCorners)
		{
			bOutOfBounds = TRUE;
			break;
		}
		if (pcFace->asCorner[1] >= iNumCorners)
		{
			bOutOfBounds = TRUE;
			break;
		}
		if (pcFace->asCorner[2] >= iNumCorners)
		{
			bOutOfBounds = TRUE;
			break;
		}
	}
	AssertBool(FALSE, bOutOfBounds);

	bOutOfBounds = FALSE;
	for (i = 0; i < cMesh.NumFaces(); i++)
	{
		psNormalFace = cMesh.mcNormals.mcFaces.Get(i);
		if (psNormalFace->aiCornerNormals[0] >= iNumNormals)
		{
			bOutOfBounds = TRUE;
			break;
		}
		psNormalFace = cMesh.mcNormals.mcFaces.Get(i);
		if (psNormalFace->aiCornerNormals[1] >= iNumNormals)
		{
			bOutOfBounds = TRUE;
			break;
		}
		psNormalFace = cMesh.mcNormals.mcFaces.Get(i);
		if (psNormalFace->aiCornerNormals[2] >= iNumNormals)
		{
			bOutOfBounds = TRUE;
			break;
		}
	}
	AssertBool(FALSE, bOutOfBounds);

	WriteMesh(&cMesh, "Output/Reader.OBJ");

	cMesh.Kill();
}

