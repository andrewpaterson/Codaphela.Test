#include "StandardLib/Objects.h"
#include "StandardLib/ObjectSerialiser.h"
#include "StandardLib/ObjectDeserialiser.h"
#include "ObjectWriterChunkedTestClasses.h"


void CTestWithArray::Init(char* szString, int x)
{
	Pointer(mcArray.This());
	mcArray = OMalloc(CArray);
	mcArray->Init();
	mszString.Init(szString);
	mx = x;
}

void CTestWithArray::Kill(void)
{
	mszString.Kill();
	CObject::Kill();
}

void CTestWithArray::Add(CPointerObject pcObject)
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
	ReturnOnFalse(pcFile->ReadPointer(Pointer(mcArray.This())));
	ReturnOnFalse(pcFile->ReadString(&mszString));
	ReturnOnFalse(pcFile->ReadInt(&mx));
	return TRUE;
}


void CTestInteger::Init(int x, int y, int z)
{
	mx = x;
	my = y;
	mz = z;
}

void CTestInteger::Kill(void)
{
	CObject::Kill();
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


void CTestNamedString::Init(CPointer<CString> szString, CPointer<CTestNamedString> pAnother, char* szEmbedded)
{
	Pointer(mszString.This());
	Pointer(mpAnother.This());
	mszString = szString;
	mpAnother = pAnother;
	mszEmbedded.Init(szEmbedded);
}

void CTestNamedString::Kill(void)
{
	mszString = NULL;;
	CObject::Kill();
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
	ReturnOnFalse(pcFile->ReadPointer(Pointer(mszString.This())));
	ReturnOnFalse(pcFile->ReadPointer(Pointer(mpAnother.This())));
	ReturnOnFalse(pcFile->ReadString(&mszEmbedded));
	return TRUE;
}


void CTestDoubleNamedString::Init(CPointer<CString> szString, CPointer<CTestNamedString> pSplit2, CPointer<CTestNamedString> pSplit1)
{
	Pointer(mszString.This());
	Pointer(mpSplit1.This());
	Pointer(mpSplit2.This());
	mszString = szString;
	mpSplit1 = pSplit1;
	mpSplit2 = pSplit2;
}

void CTestDoubleNamedString::Kill(void)
{
	CObject::Kill();
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
	ReturnOnFalse(pcFile->ReadPointer(Pointer(mszString.This())));
	ReturnOnFalse(pcFile->ReadPointer(Pointer(mpSplit1.This())));
	ReturnOnFalse(pcFile->ReadPointer(Pointer(mpSplit2.This())));
	return TRUE;
}

