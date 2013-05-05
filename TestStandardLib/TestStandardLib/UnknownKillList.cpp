#include "UnknownKillList.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CKillList::AddKill(CUnknownTestHelper* pcKilled)
{
	Add(&pcKilled);
}

BOOL CKillList::Contains(CUnknownTestHelper* pcKilled)
{
	int						i;
	CUnknownTestHelper*		pcTest;

	for (i = 0; i < miUsedElements; i++)
	{
		pcTest = *Get(i);
		if (pcTest == pcKilled)
		{
			return TRUE;
		}
	}
	return FALSE;
}

