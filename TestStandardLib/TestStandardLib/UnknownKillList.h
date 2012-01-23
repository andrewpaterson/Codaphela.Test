#ifndef __DEATH_TRACKER_H__
#define __DEATH_TRACKER_H__
#include "BaseLib/ArraySimple.h"


class CUnknownTestHelper;
class CKillList : public CArraySimple<CUnknownTestHelper*>
{
public:
	void AddKill(CUnknownTestHelper* pcKilled);
	BOOL Contains(CUnknownTestHelper* pcKilled);
};


#endif // __DEATH_TRACKER_H__

