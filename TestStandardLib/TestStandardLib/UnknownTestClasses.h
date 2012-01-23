#include "StandardLib/Unknowns.h"


class CTestUnknown : public CUnknown
{
BASE_FUNCTIONS(CTestUnknown)
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
BASE_FUNCTIONS(CTestNamedUnknown)
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
BASE_FUNCTIONS(CTestIterableUnknown)
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
BASE_FUNCTIONS(CTestUnknownJobbie);
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

