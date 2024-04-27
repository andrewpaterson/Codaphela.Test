#ifndef __DEATH_TRACKER_H__
#define __DEATH_TRACKER_H__
#include "BaseLib/ArrayTemplateMinimal.h"


class CUnknownTestHelper;
class CKillList : public CArrayTemplateMinimal<CUnknownTestHelper*>
{
public:
	void AddKill(CUnknownTestHelper* pcKilled);
	bool Contains(CUnknownTestHelper* pcKilled);
};


#endif // __DEATH_TRACKER_H__

