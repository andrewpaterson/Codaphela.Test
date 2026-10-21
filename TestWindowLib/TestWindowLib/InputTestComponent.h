#ifndef __INPUT_TEST_COMPONENT_H__
#define __INPUT_TEST_COMPONENT_H__
#include "BaseLib/Chars.h"
#include "WindowLib/Component.h"


//Appends every focus and input call it is given to a log shared by all the
//components in a test, as "Name:Call;", so the order of calls can be asserted.
class CInputTestComponent : public CComponent
{
CONSTRUCTABLE(CInputTestComponent);
DESTRUCTABLE(CInputTestComponent);
protected:
	CChars		mszName;
	CChars*		mpszLog;

public:
	void	Init(Ptr<CWindow> pWindow, const char* szName, CChars* pszLog, bool bCanGetFocus);
	void	Class(void) override;
	void	Free(void) override;

	void	FocusGained(void) override;
	void	FocusLost(void) override;
	void	MovedInto(void) override;
	void	MovedOutof(void) override;

	void	Up(void) override;
	void	Left(void) override;
	void	WordLeft(void) override;
	void	End(void) override;
	void	LineUp(void) override;
	void	LineDown(void) override;
	void	SelectUp(void) override;
	void	SelectAll(void) override;
	void	Tab(bool bInsert) override;
	void	BackTab(void) override;
	void	Enter(void) override;
	void	EndEnter(void) override;
	void	Copy(CChars* pszDest) override;
	void	Printable(char c, bool bInsert) override;
	void	Space(bool bInsert) override;
	void	Paste(char* szSource) override;

	void	ActivateComponent(int x, int y) override;
	void	ExecuteComponent(int x, int y) override;
	void	ContextMenu(int x, int y) override;
	void	StartDragScroll(int x, int y) override;
	void	ContDragScroll(int x, int y) override;
	void	StopDragScroll(int x, int y) override;
	void	StartDragSelect(int x, int y) override;
	void	ContDragSelect(int x, int y) override;
	void	StopDragSelect(int x, int y) override;
	void	Hover(int x, int y) override;

protected:
	void	Log(const char* szCall);
	void	Log(const char* szCall, int x, int y);
};


#endif // __INPUT_TEST_COMPONENT_H__

