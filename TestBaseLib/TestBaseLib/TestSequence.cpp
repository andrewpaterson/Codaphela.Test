#include "BaseLib/Logger.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/Sequence.h"
#include "BaseLib/ValueSequenceConfig.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSequenceNext(void)
{
	CSequence					cSequence;
	CLifeInit<CSequenceConfig>	cConfig;
	char						szDirectory[] = "Output" _FS_ "Sequence" ;
	OIndex						oi;
	CFileUtil					cFileUtil;

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.TouchDir(szDirectory);

	AssertLong(1LL, FIRST_O_INDEX);

	cConfig = CValueSequenceConfig::Create(szDirectory);
	cSequence.Init(cConfig);

	oi = cSequence.GetNext();
	AssertLong(1LL, oi);

	oi = cSequence.GetNext();
	AssertLong(2LL, oi);

	cSequence.Kill();

	cConfig = CValueSequenceConfig::Create(szDirectory);
	cSequence.Init(cConfig);

	oi = cSequence.GetNext();
	AssertLong(3LL, oi);

	oi = cSequence.GetNext();
	AssertLong(4LL, oi);

	cSequence.Kill();

	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSequence(void)
{
	TypeConverterInit();
	MemoryInit();
	DataMemoryInit();
	BeginTests();

	TestSequenceNext();

	TestStatistics();
	DataMemoryKill();
	MemoryKill();
	TypeConverterKill();
}

