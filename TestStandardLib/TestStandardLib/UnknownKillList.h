#ifndef __UNKNOWN_KILL_LIST_H__
#define __UNKNOWN_KILL_LIST_H__
#include "BaseLib/ArrayTemplateMinimal.h"


class CUnknownTestHelper;
class CKillList : public CArrayTemplateMinimal<CUnknownTestHelper*>
{
public:
	void AddKill(CUnknownTestHelper* pcKilled);
	bool Contains(CUnknownTestHelper* pcKilled);
};


#endif // __UNKNOWN_KILL_LIST_H__

