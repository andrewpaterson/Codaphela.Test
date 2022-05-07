#include "TestLib/Assert.h"
#include "JavaTokenAssert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CJavaToken* AssertKeyword(CJavaToken* pcToken, EJavaKeyword eKeyword)
{
	CJavaKeyword* pcKeyword;

	AssertNotNull(pcToken);
	if (pcToken)
	{
		AssertTrue(pcToken->IsKeyword());
		if (pcToken->IsKeyword())
		{
			pcKeyword = (CJavaKeyword*)pcToken;
			AssertTrue(pcKeyword->Is(eKeyword));
		}
		return pcToken->GetNext();
	}

	return NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CJavaToken* AssertIdentifier(CJavaToken* pcToken, char* szIdentifier)
{
	CJavaIdentifier* pcIdentifier;

	AssertNotNull(pcToken);
	if (pcToken)
	{
		AssertTrue(pcToken->IsIdentifier());
		if (pcToken->IsIdentifier())
		{
			pcIdentifier = (CJavaIdentifier*)pcToken;
			AssertTrue(pcIdentifier->Is(szIdentifier));
		}
		return pcToken->GetNext();
	}

	return NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CJavaToken* AssertSeparator(CJavaToken* pcToken, EJavaSeparator eSeparator)
{
	CJavaSeparator* pcSeparator;

	AssertNotNull(pcToken);
	if (pcToken)
	{
		AssertTrue(pcToken->IsSeparator());
		if (pcToken->IsSeparator())
		{
			pcSeparator = (CJavaSeparator*)pcToken;
			AssertTrue(pcSeparator->Is(eSeparator));
		}
		return pcToken->GetNext();
	}

	return NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CJavaToken* AssertOperator(CJavaToken* pcToken, EJavaOperator eOperator)
{
	CJavaOperator* pcOperator;

	AssertNotNull(pcToken);
	if (pcToken)
	{
		AssertTrue(pcToken->IsOperator());
		if (pcToken->IsOperator())
		{
			pcOperator = (CJavaOperator*)pcToken;
			AssertTrue(pcOperator->Is(eOperator));
		}
		return pcToken->GetNext();
	}

	return NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CJavaToken* AssertLiteral(CJavaToken* pcToken, char* szString)
{
	CJavaString* pcString;
	CJavaLiteral* pcLiteral;

	AssertNotNull(pcToken);
	if (pcToken)
	{
		AssertTrue(pcToken->IsLiteral());
		if (pcToken->IsLiteral())
		{
			pcLiteral = (CJavaLiteral*)pcToken;
			AssertTrue(pcLiteral->IsString());
			if (pcLiteral->IsString())
			{
				pcString = (CJavaString*)pcToken;
				AssertTrue(pcString->Is(szString));
			}
		}
		return pcToken->GetNext();
	}

	return NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CJavaToken* AssertLiteral(CJavaToken* pcToken, int64 lli)
{
	CJavaInteger* pcInteger;
	CJavaLiteral* pcLiteral;

	AssertNotNull(pcToken);
	if (pcToken)
	{
		AssertTrue(pcToken->IsLiteral());
		if (pcToken->IsLiteral())
		{
			pcLiteral = (CJavaLiteral*)pcToken;
			AssertTrue(pcLiteral->IsInteger());
			if (pcLiteral->IsInteger())
			{
				pcInteger = (CJavaInteger*)pcToken;
				AssertTrue(pcInteger->Is(lli));
			}
		}
		return pcToken->GetNext();
	}

	return NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CJavaToken* AssertLiteral(CJavaToken* pcToken, int32 i)
{
	CJavaInteger* pcInteger;
	CJavaLiteral* pcLiteral;

	AssertNotNull(pcToken);
	if (pcToken)
	{
		AssertTrue(pcToken->IsLiteral());
		if (pcToken->IsLiteral())
		{
			pcLiteral = (CJavaLiteral*)pcToken;
			AssertTrue(pcLiteral->IsInteger());
			if (pcLiteral->IsInteger())
			{
				pcInteger = (CJavaInteger*)pcToken;
				AssertTrue(pcInteger->Is(i));
			}
		}
		return pcToken->GetNext();
	}

	return NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CJavaToken* AssertLiteral(CJavaToken* pcToken, float64 d)
{
	CJavaFloat*		pcFloat;
	CJavaLiteral* pcLiteral;

	AssertNotNull(pcToken);
	if (pcToken)
	{
		AssertTrue(pcToken->IsLiteral());
		if (pcToken->IsLiteral())
		{
			pcLiteral = (CJavaLiteral*)pcToken;
			AssertTrue(pcLiteral->IsFloat());
			if (pcLiteral->IsFloat())
			{
				pcFloat = (CJavaFloat*)pcToken;
				AssertTrue(pcFloat->Is(d));
			}
		}
		return pcToken->GetNext();
	}

	return NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CJavaToken* AssertLiteral(CJavaToken* pcToken, float32 f)
{
	CJavaFloat* pcFloat;
	CJavaLiteral* pcLiteral;

	AssertNotNull(pcToken);
	if (pcToken)
	{
		AssertTrue(pcToken->IsLiteral());
		if (pcToken->IsLiteral())
		{
			pcLiteral = (CJavaLiteral*)pcToken;
			AssertTrue(pcLiteral->IsFloat());
			if (pcLiteral->IsFloat())
			{
				pcFloat = (CJavaFloat*)pcToken;
				AssertTrue(pcFloat->Is(f));
			}
		}
		return pcToken->GetNext();
	}

	return NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CJavaToken* AssertLiteral(CJavaToken* pcToken, char8 c)
{
	CJavaCharacter*		pcCharacter;
	CJavaLiteral*		pcLiteral;

	AssertNotNull(pcToken);
	if (pcToken)
	{
		AssertTrue(pcToken->IsLiteral());
		if (pcToken->IsLiteral())
		{
			pcLiteral = (CJavaLiteral*)pcToken;
			AssertTrue(pcLiteral->IsCharacter());
			if (pcLiteral->IsCharacter())
			{
				pcCharacter = (CJavaCharacter*)pcToken;
				AssertTrue(pcCharacter->Is(c));
			}
		}
		return pcToken->GetNext();
	}

	return NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CJavaToken* AssertLiteral(CJavaToken* pcToken, char16 c)
{
	CJavaCharacter* pcCharacter;
	CJavaLiteral* pcLiteral;

	AssertNotNull(pcToken);
	if (pcToken)
	{
		AssertTrue(pcToken->IsLiteral());
		if (pcToken->IsLiteral())
		{
			pcLiteral = (CJavaLiteral*)pcToken;
			AssertTrue(pcLiteral->IsCharacter());
			if (pcLiteral->IsCharacter())
			{
				pcCharacter = (CJavaCharacter*)pcToken;
				AssertTrue(pcCharacter->Is(c));
			}
		}
		return pcToken->GetNext();
	}

	return NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CJavaToken* AssertLiteral(CJavaToken* pcToken, bool b)
{
	CJavaBoolean* pcBoolean;
	CJavaLiteral* pcLiteral;

	AssertNotNull(pcToken);
	if (pcToken)
	{
		AssertTrue(pcToken->IsLiteral());
		if (pcToken->IsLiteral())
		{
			pcLiteral = (CJavaLiteral*)pcToken;
			AssertTrue(pcLiteral->IsBoolean());
			if (pcLiteral->IsBoolean())
			{
				pcBoolean = (CJavaBoolean*)pcToken;
				AssertTrue(pcBoolean->Is(b));
			}
		}
		return pcToken->GetNext();
	}

	return NULL;
}

