#include "BaseLib/TextParser.h"
#include "BaseLib/Numbers.h"


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
void TestSkipComments(void)
{
	CTextParser		cParser;
	char			szIdentifier[1 KB];
	int				iLength;
	TRISTATE		tResult;

	xxx
	cParser.Init("  /* Hello */  X");
	cParser.SkipWhiteSpace();
	tResult = cParser.GetIdentifier(szIdentifier, &iLength, TRUE, FALSE);
	cParser.Kill();
}

