#include "Player.h"

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPlayer::Init(void)
{
	maszEvents.Init();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPlayer::Kill(void)
{
	maszEvents.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPlayer::Up(CUnknown* pcSource, void* pvContext) 
{
	RecordAction((CAction*)pcSource, "Up", pvContext);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPlayer::Down(CUnknown* pcSource, void* pvContext) 
{
	RecordAction((CAction*)pcSource, "Down", pvContext);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPlayer::Left(CUnknown* pcSource, void* pvContext)
{
	RecordAction((CAction*)pcSource, "Left", pvContext);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPlayer::Right(CUnknown* pcSource, void* pvContext)
{
	RecordAction((CAction*)pcSource, "Right", pvContext);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPlayer::Fire(CUnknown* pcSource, void* pvContext)
{
	RecordAction((CAction*)pcSource, "Fire", pvContext);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPlayer::RecordAction(CAction* pcAction, char* szText, void* pvContext)
{
	CChars*		psz;

	psz = maszEvents.Add(pcAction->GetName());
	psz->Append(": ");
	psz->Append(szText);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CArrayChars* CPlayer::GetEvents(void) { return &maszEvents; }

