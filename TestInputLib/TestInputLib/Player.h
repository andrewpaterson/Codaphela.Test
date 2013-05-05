#ifndef __TEST_PLAYER_H__
#define __TEST_PLAYER_H__
#include "BaseLib/ArrayString.h"
#include "StandardLib/Action.h"
#include "PlayerListener.h"


class CPlayer : public CPlayerListener
{
BASE_FUNCTIONS(CPlayer);
protected:
	CArrayString	maszEvents;

public:
	void 			Init(void);
	void 			Kill(void);
	void 			Up(CUnknown* pcSource, void* pvContext);
	void 			Down(CUnknown* pcSource, void* pvContext);
	void 			Left(CUnknown* pcSource, void* pvContext);
	void 			Right(CUnknown* pcSource, void* pvContext);
	void 			Fire(CUnknown* pcSource, void* pvContext);
	void 			RecordAction(CAction* pcAction, char* szText, void* pvContext);
	CArrayString*	GetEvents(void);
};


#endif // __TEST_PLAYER_H__

