#include "StandardLib/Objects.h"
#include "StandardLib/ObjectSerialiser.h"
#include "StandardLib/ObjectDeserialiser.h"
#include "ObjectWriterChunkedTestClasses.h"


Ptr<CTestWithArray> CTestWithArray::Init(char* szString, int x)
{
	mcArray = OMalloc(CArrayObject);
	mcArray->Init();
	mszString.Init(szString);
	mx = x;

	return Ptr<CTestWithArray>(this);
}

void CTestWithArray::Class(void)
{
	CObject::Class();
	Pointer(mcArray.This());
}

void CTestWithArray::KillData(void)
{
	mszString.Kill();
}

void CTestWithArray::Add(CPointer pcObject)
{
	mcArray->Add(pcObject);
}

BOOL CTestWithArray::Save(CObjectSerialiser* pcFile)
{
	ReturnOnFalse(pcFile->WritePointer(mcArray));
	ReturnOnFalse(pcFile->WriteString(&mszString));
	ReturnOnFalse(pcFile->WriteInt(mx));
	return TRUE;
}

BOOL CTestWithArray::Load(CObjectDeserialiser* pcFile)
{
	ReturnOnFalse(pcFile->ReadPointer(mcArray.This()));
	ReturnOnFalse(pcFile->ReadString(&mszString));
	ReturnOnFalse(pcFile->ReadInt(&mx));
	return TRUE;
}


Ptr<CTestInteger> CTestInteger::Init(int x, int y, int z)
{
	mx = x;
	my = y;
	mz = z;
	return Ptr<CTestInteger>(this);
}

void CTestInteger::Class(void)
{
	CObject::Class();
}


void CTestInteger::KillData(void)
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


Ptr<CTestNamedString> CTestNamedString::Init(Ptr<CString> szString, Ptr<CTestNamedString> pAnother, char* szEmbedded)
{
	mszString = szString;
	mpAnother = pAnother;
	mszEmbedded.Init(szEmbedded);

	return Ptr<CTestNamedString>(this);
}

void CTestNamedString::Class(void)
{
	CObject::Class();
	Pointer(mszString.This());
	Pointer(mpAnother.This());
}

void CTestNamedString::KillData(void)
{
}

BOOL CTestNamedString::Save(CObjectSerialiser* pcFile)
{
	ReturnOnFalse(pcFile->WritePointer(mszString));
	ReturnOnFalse(pcFile->WritePointer(mpAnother));
	ReturnOnFalse(pcFile->WriteString(&mszEmbedded));
	return TRUE;
}

BOOL CTestNamedString::Load(CObjectDeserialiser* pcFile)
{
	ReturnOnFalse(pcFile->ReadPointer(mszString.This()));
	ReturnOnFalse(pcFile->ReadPointer(mpAnother.This()));
	ReturnOnFalse(pcFile->ReadString(&mszEmbedded));
	return TRUE;
}


Ptr<CTestDoubleNamedString> CTestDoubleNamedString::Init(void)
{
	mszString = ONull;
	mpSplit1 = ONull;
	mpSplit2 = ONull;

	return Ptr<CTestDoubleNamedString>(this);
}

Ptr<CTestDoubleNamedString> CTestDoubleNamedString::Init(Ptr<CString> szString, Ptr<CTestNamedString> pSplit2, Ptr<CTestNamedString> pSplit1)
{
	mszString = szString;
	mpSplit1 = pSplit1;
	mpSplit2 = pSplit2;

	return Ptr<CTestDoubleNamedString>(this);
}

void CTestDoubleNamedString::Class(void)
{
	CObject::Class();
	Pointer(mszString.This());
	Pointer(mpSplit1.This());
	Pointer(mpSplit2.This());
}

void CTestDoubleNamedString::KillData(void)
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

