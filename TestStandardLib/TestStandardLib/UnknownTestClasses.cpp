#include "UnknownTestClasses.h"


bool CTestUnknown::Save(CFileWriter* pcFile)
{
	ReturnOnFalse(pcFile->WriteInt(miCount));
	return true;
}
bool CTestUnknown::Load(CFileReader* pcFile)
{
	ReturnOnFalse(pcFile->ReadInt(&miCount));
	return true;
}


bool CTestUnknownJobbie::Save(CFileWriter* pcFile)
{
	ReturnOnFalse(pcFile->WriteInt(miANumber));
	ReturnOnFalse(mszText.WriteString(pcFile));
	return true;
}
bool CTestUnknownJobbie::Load(CFileReader* pcFile)
{
	ReturnOnFalse(pcFile->ReadInt(&miANumber));
	ReturnOnFalse(mszText.ReadString(pcFile));
	return true;
}
