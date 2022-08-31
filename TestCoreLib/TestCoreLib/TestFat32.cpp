#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeConverter.h"
#include "CoreLib/Fat32.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32(void)
{
	TypeConverterInit();
	BeginTests();

	TFFile* pFile;

	char	sz[] = "Blue";

	tf_initializeMedia(64);
	tf_init();


	//pFile = tf_fopen("Hexafile.txt", "wb");
	//AssertNull(pFile);

	tf_create("/");

	pFile = tf_fopen("/Hexafile.txt", "w");
	AssertNotNull(pFile);

	tf_fwrite((uint8_t*)sz, 5, 1, pFile);
	tf_fclose(pFile);

	TestStatistics();
	TypeConverterKill();
}

