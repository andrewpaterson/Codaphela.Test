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
	Pointer(mcArray.This());
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
	ReturnOnFalse(pcFile->WritePointer(mcArray));
	ReturnOnFalse(mszString.WriteString(pcFile));
	ReturnOnFalse(pcFile->WriteInt(mx));
	return TRUE;
}


BOOL CTestWithArray::Load(CObjectDeserialiser* pcFile)
{
	ReturnOnFalse(pcFile->ReadPointer(mcArray.This()));
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

	PreInit();
}


void CTestInteger::Class(void)
{
	CObject::Class();
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
	mszString = szString;
	mpAnother = pAnother;
	mszEmbedded.Init(szEmbedded);
	PostInit();
}


void CTestNamedString::Class(void)
{
	CObject::Class();
	Pointer(mszString.This());
	Pointer(mpAnother.This());
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
	mszString = ONull;
	mpSplit1 = ONull;
	mpSplit2 = ONull;
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
	Pointer(mszString.This());
	Pointer(mpSplit1.This());
	Pointer(mpSplit2.This());
}


void CTestDoubleNamedString::Free(void)
{
}


BOOL CTestDoubleNamedString::Save(CObjectSerialiser* pcFile)
{
	ReturnOnFalse(pcFile->WritePointer(mszString));
	ReturnOnFalse(pcFile->WritePointer(mpSplit1));
	ReturnOnFalse(pcFile->WritePointer(mpSplit2));
	return TRUE;
}


BOOL CTestDoubleNamedString::Load(CObjectDeserialiser* pcFile)
{
	ReturnOnFalse(pcFile->ReadPointer(mszString.This()));
	ReturnOnFalse(pcFile->ReadPointer(mpSplit1.This()));
	ReturnOnFalse(pcFile->ReadPointer(mpSplit2.This()));
	return TRUE;
}

