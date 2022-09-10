#include "StandardLib/Objects.h"
#include "StandardLib/ObjectWriter.h"
#include "StandardLib/ObjectReader.h"
#include "ChunkFileObjectWriterTestClasses.h"


void CTestWithArray::Init(const char* szString, int x)
{
	PreInit();
	mcArray = OMalloc<CArrayObject>();
	mszString.Init(szString);
	mx = x;
	PostInit();
}


void CTestWithArray::Class(void)
{
	Pointer(mcArray.This(), "mcArray");
	UnmanagedString(&mszString, "mszString");
	UnmanagedInt(&mx, "mx");;

}


void CTestWithArray::Free(void)
{
	mszString.Kill();
}


void CTestWithArray::Add(CPointer& pcObject)
{
	mcArray->Add(pcObject);
}


bool CTestWithArray::Save(CObjectWriter* pcFile)
{
	ReturnOnFalse(mszString.WriteString(pcFile));
	ReturnOnFalse(pcFile->WriteInt(mx));
	return true;
}


bool CTestWithArray::Load(CObjectReader* pcFile)
{
	ReturnOnFalse(mszString.ReadString(pcFile));
	ReturnOnFalse(pcFile->ReadInt(&mx));
	return true;
}


void CTestInteger::Init(int x, int y, int z)
{
	PreInit();
	mx = x;
	my = y;
	mz = z;
	PostInit();
}


void CTestInteger::Class(void)
{
	UnmanagedInt(&mx, "mx");
	UnmanagedInt(&my, "my");
	UnmanagedInt(&mz, "mz");
}


void CTestInteger::Free(void)
{
}


bool CTestInteger::Save(CObjectWriter* pcFile)
{
	ReturnOnFalse(pcFile->WriteInt(mx));
	ReturnOnFalse(pcFile->WriteInt(my));
	ReturnOnFalse(pcFile->WriteInt(mz));
	return true;
}


bool CTestInteger::Load(CObjectReader* pcFile)
{
	ReturnOnFalse(pcFile->ReadInt(&mx));
	ReturnOnFalse(pcFile->ReadInt(&my));
	ReturnOnFalse(pcFile->ReadInt(&mz));
	return true;
}


void CTestNamedString::Init(void)
{
	PreInit();
	mszString = NULL;
	mpAnother = NULL;
	mszEmbedded._Init();
	PostInit();
}


void CTestNamedString::Init(Ptr<CString> szString, Ptr<CTestNamedString> pAnother, const char* szEmbedded)
{
	PreInit();
	Set(szString, pAnother, szEmbedded);
	PostInit();
}


void CTestNamedString::Set(Ptr<CString> szString, Ptr<CTestNamedString> pAnother, const char* szEmbedded)
{
	mszString = szString;
	mpAnother = pAnother;
	mszEmbedded.Init(szEmbedded);
}


void CTestNamedString::Class(void)
{
	Pointer(mszString.This(), "mszString");
	Pointer(mpAnother.This(), "mpAnother");
	UnmanagedString(&mszEmbedded, "mszEmbedded");
}


void CTestNamedString::Free(void)
{
}


bool CTestNamedString::Save(CObjectWriter* pcFile)
{
	ReturnOnFalse(mszEmbedded.WriteString(pcFile));
	return true;
}


bool CTestNamedString::Load(CObjectReader* pcFile)
{
	ReturnOnFalse(mszEmbedded.ReadString(pcFile));
	return true;
}


void CTestDoubleNamedString::Init(void)
{
	PreInit();
	mszString = Null();
	mpSplit1 = Null();
	mpSplit2 = Null();
	PostInit();
}


void CTestDoubleNamedString::Init(Ptr<CString> szString, Ptr<CTestNamedString> pSplit2, Ptr<CTestNamedString> pSplit1)
{
	PreInit();
	mszString = szString;
	mpSplit1 = pSplit1;
	mpSplit2 = pSplit2;
	PostInit();
}


void CTestDoubleNamedString::Class(void)
{
	Pointer(mszString.This(), "mszString");
	Pointer(mpSplit1.This(), "mpSplit1");
	Pointer(mpSplit2.This(), "mpSplit2");
}


void CTestDoubleNamedString::Free(void)
{
}

