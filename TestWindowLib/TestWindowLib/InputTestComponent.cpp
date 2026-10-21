#include "StandardLib/ClassDefines.h"
#include "WindowLib/Window.h"
#include "InputTestComponent.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CInputTestComponent::Init(Ptr<CWindow> pWindow, const char* szName, CChars* pszLog, bool bCanGetFocus)
{
	PreInit();

	CComponent::Init(pWindow);
	mszName.Init(szName);
	mpszLog = pszLog;
	SetCanGetFocus(bCanGetFocus);

	PostInit();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CInputTestComponent::Class(void)
{
	CComponent::Class();

	U_String(mszName);
	U_Pointer(mpszLog);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CInputTestComponent::Free(void)
{
	mszName.Kill();
	CComponent::Free();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CInputTestComponent::Log(const char* szCall)
{
	mpszLog->Append(&mszName);
	mpszLog->Append(':');
	mpszLog->Append(szCall);
	mpszLog->Append(';');
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CInputTestComponent::Log(const char* szCall, int x, int y)
{
	mpszLog->Append(&mszName);
	mpszLog->Append(':');
	mpszLog->Append(szCall);
	mpszLog->Append('(');
	mpszLog->Append((int32)x);
	mpszLog->Append(',');
	mpszLog->Append((int32)y);
	mpszLog->Append(");");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CInputTestComponent::Printable(char c, bool bInsert)
{
	mpszLog->Append(&mszName);
	mpszLog->Append(":Printable(");
	mpszLog->Append(c);
	mpszLog->Append(bInsert ? ",Insert);" : ",Overwrite);");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CInputTestComponent::Space(bool bInsert) { Log(bInsert ? "Space(Insert)" : "Space(Overwrite)"); }
void CInputTestComponent::Paste(char* szSource) { Log(szSource[0] == '\0' ? "Paste()" : "Paste(...)"); }
void CInputTestComponent::FocusGained(void) { Log("Gained"); }
void CInputTestComponent::FocusLost(void) { Log("Lost"); }
void CInputTestComponent::MovedInto(void) { Log("Into"); }
void CInputTestComponent::MovedOutof(void) { Log("Outof"); }
void CInputTestComponent::Up(void) { Log("Up"); }
void CInputTestComponent::Left(void) { Log("Left"); }
void CInputTestComponent::WordLeft(void) { Log("WordLeft"); }
void CInputTestComponent::End(void) { Log("End"); }
void CInputTestComponent::LineUp(void) { Log("LineUp"); }
void CInputTestComponent::LineDown(void) { Log("LineDown"); }
void CInputTestComponent::SelectUp(void) { Log("SelectUp"); }
void CInputTestComponent::SelectAll(void) { Log("SelectAll"); }
void CInputTestComponent::Tab(bool bInsert) { Log(bInsert ? "Tab(Insert)" : "Tab(Overwrite)"); }
void CInputTestComponent::BackTab(void) { Log("BackTab"); }
void CInputTestComponent::Enter(void) { Log("Enter"); }
void CInputTestComponent::EndEnter(void) { Log("EndEnter"); }
void CInputTestComponent::Copy(CChars* pszDest) { Log("Copy"); }
void CInputTestComponent::ActivateComponent(int x, int y) { Log("Activate", x, y); }
void CInputTestComponent::ExecuteComponent(int x, int y) { Log("Execute", x, y); }
void CInputTestComponent::ContextMenu(int x, int y) { Log("ContextMenu", x, y); }
void CInputTestComponent::StartDragScroll(int x, int y) { Log("StartDragScroll", x, y); }
void CInputTestComponent::ContDragScroll(int x, int y) { Log("ContDragScroll", x, y); }
void CInputTestComponent::StopDragScroll(int x, int y) { Log("StopDragScroll", x, y); }
void CInputTestComponent::StartDragSelect(int x, int y) { Log("StartDragSelect", x, y); }
void CInputTestComponent::ContDragSelect(int x, int y) { Log("ContDragSelect", x, y); }
void CInputTestComponent::StopDragSelect(int x, int y) { Log("StopDragSelect", x, y); }
void CInputTestComponent::Hover(int x, int y) { Log("Hover", x, y); }

