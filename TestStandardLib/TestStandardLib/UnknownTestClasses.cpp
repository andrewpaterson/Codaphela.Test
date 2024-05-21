#include "UnknownTestClasses.h"


bool CTestUnknown::Save(CFileWriter* pcFile)
{
	ReturnOnFalse(pcFile->WriteInt32(miCount));
	return true;
}
bool CTestUnknown::Load(CFileReader* pcFile)
{
	ReturnOnFalse(pcFile->ReadInt32(&miCount));
	return true;
}


bool CTestUnknownJobbie::Save(CFileWriter* pcFile)
{
	ReturnOnFalse(pcFile->WriteInt32(miANumber));
	ReturnOnFalse(mszText.WriteString(pcFile));
	return true;
}
bool CTestUnknownJobbie::Load(CFileReader* pcFile)
{
	ReturnOnFalse(pcFile->ReadInt32(&miANumber));
	ReturnOnFalse(mszText.ReadString(pcFile));
	return true;
}
