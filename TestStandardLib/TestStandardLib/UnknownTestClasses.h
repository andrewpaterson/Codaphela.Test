#include "StandardLib/Unknowns.h"


class CTestUnknown : public CUnknown
{
CONSTRUCTABLE(CTestUnknown)
public:

	int	miCount;

	void Init(void)
	{
		miCount = 1;
	}

	void Init(int iCount)
	{
		miCount = iCount;
	}

	void Kill(void)
	{
		miCount --;
		CUnknown::Kill();
	}

	BOOL	Save(CFileWriter* pcFile);
	BOOL	Load(CFileReader* pcFile);
};


class CTestNamedUnknown : public CUnknown
{
CONSTRUCTABLE(CTestNamedUnknown)
public:
	CChars	mszName;

	void Init(char* szName)
	{
		mszName.Init(szName);
	}

	void Kill(void)
	{
		mszName.Kill();
		CUnknown::Kill();
	}

	char* GetName(void)
	{
		return mszName.Text();
	}

	BOOL Iterable(void)
	{
		return TRUE;
	}
};


class CTestIterableUnknown : public CTestUnknown
{
CONSTRUCTABLE(CTestIterableUnknown)
public:
	int	miID;

	void Init(int iID)
	{
		CTestUnknown::Init();
		miID = iID;
	}

	BOOL Iterable(void)
	{
		return TRUE;
	}

	char* GetClassName(void)
	{
		return "TestIterableUnknown";
	}
};


class CTestUnknownJobbie : public CUnknown
{
CONSTRUCTABLE(CTestUnknownJobbie);
public:
	int		miANumber;
	CChars	mszText;

	void 	Init(int iNumber, char* pszText) 
	{ 
		miANumber = iNumber; 
		mszText.Init(pszText); 
	}

	void 	Kill(void) 
	{ 
		mszText.Kill();
		CUnknown::Kill();
	}

	BOOL	Save(CFileWriter* pcFile);
	BOOL	Load(CFileReader* pcFile);
};

