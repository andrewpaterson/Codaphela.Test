#include "StandardLib/Unknowns.h"


class CTestUnknown : public CUnknown
{
CONSTRUCTABLE(CTestUnknown)
public:

	int	miCount;

	void	Init(void);
	void	Init(int iCount);
	void	Kill(void);
	bool	Save(CFileWriter* pcFile);
	bool	Load(CFileReader* pcFile);
};


class CTestNamedUnknown : public CUnknown
{
CONSTRUCTABLE(CTestNamedUnknown)
public:
	CChars	mszName;

	void	Init(char* szName);
	void	Kill(void);
	char*	GetName(void);
	bool	Iterable(void);
};


class CTestIterableUnknown : public CTestUnknown
{
CONSTRUCTABLE(CTestIterableUnknown)
public:
	int	miID;

	void	Init(int iID);
	bool	Iterable(void);
	char*	GetClassName(void);
};


class CTestUnknownJobbie : public CUnknown
{
CONSTRUCTABLE(CTestUnknownJobbie)
public:
	int		miANumber;
	CChars	mszText;

	void 	Init(int iNumber, char* pszText);
	void 	Kill(void);
	bool	Save(CFileWriter* pcFile);
	bool	Load(CFileReader* pcFile);
};

