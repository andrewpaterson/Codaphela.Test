#include "BaseLib/DebugOutput.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/PackFilePacker.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPackFilesPackerSimple(void)
{
	CFileUtil			cFileUtil;
	CPackFilePacker		cPacker;
	
	cFileUtil.RemoveDir("Output/Packer");
	cFileUtil.MakeDir("Output/Packer");
	cFileUtil.MakeDir("Output/Packer/Sounds");

	cPacker.Pack("Output/Packer/Sounds/Cheese.PAK", "Input/Game/PAK/Cheese");
	AssertFile("Game/Sounds/Cheese.PAK", "Output/Packer/Sounds/Cheese.PAK");

	cPacker.Pack("Output/Packer/Sounds/Santa.PAK", "Input/Game/PAK/Santa");
	AssertFile("Game/Sounds/Santa.PAK", "Output/Packer/Sounds/Santa.PAK");

	cPacker.Pack("Output/Packer/Models.PAK", "Input/Game/PAK/Models");
	AssertFile("Game/Models.PAK", "Output/Packer/Models.PAK");

	cPacker.Pack("Output/Packer/Sounds.PAK", "Input/Game/PAK/Sounds");
	AssertFile("Game/Sounds.PAK", "Output/Packer/Sounds.PAK");

	cPacker.Pack("Output/Packer/Textures.PAK", "Input/Game/PAK/Textures");
	AssertFile("Game/Textures.PAK", "Output/Packer/Textures.PAK");

	cPacker.Pack("Output/Packer/Videos.PAK", "Input/Game/PAK/Videos");
	AssertFile("Game/Videos.PAK", "Output/Packer/Videos.PAK");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPackFilesPackerCopyDir(void)
{
	CFileUtil	cFileUtil;

	cFileUtil.CopyDir("Input/Game/files", "Output/Packer");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPackFilesPacker(void)
{
	BeginTests();

	FastFunctionsInit();
	MemoryInit();

	TestPackFilesPackerSimple();
	TestPackFilesPackerCopyDir();

	MemoryKill();
	FastFunctionsKill();

	TestStatistics();
}

