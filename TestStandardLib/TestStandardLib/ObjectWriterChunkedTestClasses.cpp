#include "StandardLib/Objects.h"
#include "StandardLib/ObjectSerialiser.h"
#include "StandardLib/ObjectDeserialiser.h"
#include "ObjectWriterChunkedTestClasses.h"


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
	CObject::Class();
	Pointer(mcArray.This(), "mcArray");
	Unmanaged(&mszString, "mszString");
	Unmanaged(&mx, "mx");;

}


void CTestWithArray::Free(void)
{
	mszString.Kill();
}


void CTestWithArray::Add(CPointer& pcObject)
{
	mcArray->Add(pcObject);
}


BOOL CTestWithArray::Save(CObjectSerialiser* pcFile)
{
	ReturnOnFalse(mszString.WriteString(pcFile));
	ReturnOnFalse(pcFile->WriteInt(mx));
	return TRUE;
}


BOOL CTestWithArray::Load(CObjectDeserialiser* pcFile)
{
	ReturnOnFalse(mszString.ReadString(pcFile));
	ReturnOnFalse(pcFile->ReadInt(&mx));
	return TRUE;
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
	CObject::Class();
	Unmanaged(&mx, "mx");
	Unmanaged(&my, "my");
	Unmanaged(&mz, "mz");
}


void CTestInteger::Free(void)
{
}


BOOL CTestInteger::Save(CObjectSerialiser* pcFile)
{
	ReturnOnFalse(pcFile->WriteInt(mx));
	ReturnOnFalse(pcFile->WriteInt(my));
	ReturnOnFalse(pcFile->WriteInt(mz));
	return TRUE;
}


BOOL CTestInteger::Load(CObjectDeserialiser* pcFile)
{
	ReturnOnFalse(pcFile->ReadInt(&mx));
	ReturnOnFalse(pcFile->ReadInt(&my));
	ReturnOnFalse(pcFile->ReadInt(&mz));
	return TRUE;
}


void CTestNamedString::Init(void)
{
	PreInit();
	mszString = NULL;
	mpAnother = NULL;
	mszEmbedded.Zero();
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
	CObject::Class();
	Pointer(mszString.This(), "mszString");
	Pointer(mpAnother.This(), "mpAnother");
	Unmanaged(&mszEmbedded, "mszEmbedded");
}


void CTestNamedString::Free(void)
{
}


BOOL CTestNamedString::Save(CObjectSerialiser* pcFile)
{
	ReturnOnFalse(pcFile->WritePointer(mszString));
	ReturnOnFalse(pcFile->WritePointer(mpAnother));
	ReturnOnFalse(mszEmbedded.WriteString(pcFile));
	return TRUE;
}


BOOL CTestNamedString::Load(CObjectDeserialiser* pcFile)
{
	ReturnOnFalse(pcFile->ReadPointer(mszString.This()));
	ReturnOnFalse(pcFile->ReadPointer(mpAnother.This()));
	ReturnOnFalse(mszEmbedded.ReadString(pcFile));
	return TRUE;
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
	CObject::Class();
	Pointer(mszString.This(), "mszString");
	Pointer(mpSplit1.This(), "mpSplit1");
	Pointer(mpSplit2.This(), "mpSplit2");
}


void CTestDoubleNamedString::Free(void)
{
}

