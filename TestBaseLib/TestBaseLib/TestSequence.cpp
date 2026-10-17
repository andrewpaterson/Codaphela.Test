#include "BaseLib/Logger.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/Sequence.h"
#include "BaseLib/ValueSequenceConfig.h"
#include "BaseLib/TextFile.h"
#include "BaseLib/FileUtil.h"
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

	cConfig = CValueSequenceConfig::Create(szDirectory, DS_Yes);
	cSequence.Init(cConfig);

	oi = cSequence.GetNext();
	AssertLong(1LL, oi);

	oi = cSequence.GetNext();
	AssertLong(2LL, oi);

	cSequence.Kill();

	cConfig = CValueSequenceConfig::Create(szDirectory, DS_Yes);
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
void TestSequenceCrashRecovery(bool bRewriteMark)
{
	CSequence					cSequence;
	CLifeInit<CSequenceConfig>	cConfig;
	char						szDirectory[] = "Output" _FS_ "SequenceCrash";
	CFileUtil					cFileUtil;
	CTextFile					cMark;
	SLogConfig					sLogConfig;

	cFileUtil.RemoveDir(szDirectory);

	cConfig = CValueSequenceConfig::Create(szDirectory, DS_Yes);
	AssertTrue(cSequence.Init(cConfig));
	AssertLong(1LL, cSequence.GetNext());
	AssertLong(2LL, cSequence.GetNext());
	AssertLong(3LL, cSequence.GetNext());
	cSequence.Kill();
	AssertTrue(cFileUtil.Copy("Output" _FS_ "SequenceCrash" _FS_ "Backup" _FS_ "_Sequence.DAT", "Output" _FS_ "SequenceCrash" _FS_ "Saved.DAT"));

	cConfig = CValueSequenceConfig::Create(szDirectory, DS_Yes);
	AssertTrue(cSequence.Init(cConfig));
	AssertLong(4LL, cSequence.GetNext());
	AssertLong(5LL, cSequence.GetNext());
	cSequence.Kill();

	//Put the backup back to 4 as if the process died while writing 6, with the primary already written.
	AssertTrue(cFileUtil.Copy("Output" _FS_ "SequenceCrash" _FS_ "Saved.DAT", "Output" _FS_ "SequenceCrash" _FS_ "Backup" _FS_ "_Sequence.DAT"));
	cMark.Init();
	cMark.mcText.Append("Output" _FS_ "SequenceCrash" _FS_ "Primary" _FS_ "Sequence.DAT");
	cMark.mcText.AppendNewLine();
	cMark.mcText.Append("Output" _FS_ "SequenceCrash" _FS_ "Backup" _FS_ "_Sequence.DAT");
	cMark.mcText.AppendNewLine();
	cMark.mcText.Append("#End");
	cMark.mcText.AppendNewLine();
	AssertTrue(cMark.Write("Output" _FS_ "SequenceCrash" _FS_ "Primary" _FS_ "Mark1.Write"));
	cMark.Kill();
	if (bRewriteMark)
	{
		AssertTrue(cFileUtil.Touch("Output" _FS_ "SequenceCrash" _FS_ "Backup" _FS_ "Mark2.Rewrite"));
	}

	//The sequence continues from the recovered value.  It must never start again from the first index.
	cConfig = CValueSequenceConfig::Create(szDirectory, DS_Yes);
	sLogConfig = gcLogger.SetSilent();
	AssertTrue(cSequence.Init(cConfig));
	gcLogger.SetConfig(&sLogConfig);
	if (bRewriteMark)
	{
		AssertLong(6LL, cSequence.GetNext());
	}
	else
	{
		AssertLong(4LL, cSequence.GetNext());
	}
	cSequence.Kill();
	AssertFalse(cFileUtil.Exists("Output" _FS_ "SequenceCrash" _FS_ "Primary" _FS_ "Mark1.Write"));
	AssertFalse(cFileUtil.Exists("Output" _FS_ "SequenceCrash" _FS_ "Backup" _FS_ "Mark2.Rewrite"));

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
	TestSequenceCrashRecovery(false);
	TestSequenceCrashRecovery(true);

	TestStatistics();
	DataMemoryKill();
	MemoryKill();
	TypeConverterKill();
}

