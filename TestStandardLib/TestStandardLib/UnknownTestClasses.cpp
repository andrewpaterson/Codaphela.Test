#include "UnknownTestClasses.h"


BOOL CTestUnknown::Save(CFileWriter* pcFile)
{
	ReturnOnFalse(pcFile->WriteInt(miCount));
	return TRUE;
}
BOOL CTestUnknown::Load(CFileReader* pcFile)
{
	ReturnOnFalse(pcFile->ReadInt(&miCount));
	return TRUE;
}


BOOL CTestUnknownJobbie::Save(CFileWriter* pcFile)
{
	ReturnOnFalse(pcFile->WriteInt(miANumber));
	ReturnOnFalse(mszText.WriteString(pcFile));
	return TRUE;
}
BOOL CTestUnknownJobbie::Load(CFileReader* pcFile)
{
	ReturnOnFalse(pcFile->ReadInt(&miANumber));
	ReturnOnFalse(mszText.ReadString(pcFile));
	return TRUE;
}
