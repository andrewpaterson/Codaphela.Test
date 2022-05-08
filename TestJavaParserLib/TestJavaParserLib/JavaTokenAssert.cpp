#include "BaseLib/LogString.h"
#include "JavaParserLib/JavaTokenParser.h"
#include "TestLib/Assert.h"
#include "JavaTokenAssert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CJavaToken* PrivateAssertKeyword(CJavaTokenDefinitions* pcDefinitions, CJavaToken* pcToken, EJavaKeyword eKeyword, int iLine, char* szFile)
{
	CJavaKeyword*			pcKeyword;
	CChars					sz;
	CJavaKeywordDefinition* pcDefinition;

	AssertNotNull(pcToken);
	if (pcToken)
	{
		AssertTrue(pcToken->IsKeyword());
		if (pcToken->IsKeyword())
		{
			pcKeyword = (CJavaKeyword*)pcToken;
			if (!pcKeyword->Is(eKeyword))
			{
				sz.Init();
				pcKeyword->Print(&sz);
				pcDefinition = pcDefinitions->GetKeyword(eKeyword);
				Failed((const char*)pcDefinition->GetName(), (const char*)sz.Text(), iLine, szFile);
				sz.Kill();
				BREAK();
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
CJavaToken* PrivateAssertIdentifier(CJavaTokenDefinitions* pcDefinitions, CJavaToken* pcToken, char* szIdentifier, int iLine, char* szFile)
{
	CJavaIdentifier*			pcIdentifier;
	CChars						sz;

	AssertNotNull(pcToken);
	if (pcToken)
	{
		AssertTrue(pcToken->IsIdentifier());
		if (pcToken->IsIdentifier())
		{
			pcIdentifier = (CJavaIdentifier*)pcToken;
			if (!pcIdentifier->Is(szIdentifier))
			{
				sz.Init();
				pcIdentifier->Print(&sz);
				Failed((const char*)szIdentifier, (const char*)sz.Text(), iLine, szFile);
				sz.Kill();
				BREAK();
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
CJavaToken* PrivateAssertComment(CJavaTokenDefinitions* pcDefinitions, CJavaToken* pcToken, char* szComment, int iLine, char* szFile)
{
	CJavaComment*	pcComment;
	CChars			sz;

	AssertNotNull(pcToken);
	if (pcToken)
	{
		AssertTrue(pcToken->IsComment());
		if (pcToken->IsComment())
		{
			pcComment = (CJavaComment*)pcToken;
			if (!pcComment->Is(szComment))
			{
				sz.Init();
				pcComment->GetComment(&sz);
				Failed((const char*)szComment, (const char*)sz.Text(), iLine, szFile);
				sz.Kill();
				BREAK();
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
CJavaToken* PrivateAssertSeparator(CJavaTokenDefinitions* pcDefinitions, CJavaToken* pcToken, EJavaSeparator eSeparator, int iLine, char* szFile)
{
	CJavaSeparator*				pcSeparator;
	CChars						sz;
	CJavaSeparatorDefinition*	pcDefinition;

	AssertNotNull(pcToken);
	if (pcToken)
	{
		AssertTrue(pcToken->IsSeparator());
		if (pcToken->IsSeparator())
		{
			pcSeparator = (CJavaSeparator*)pcToken;
			if (!pcSeparator->Is(eSeparator))
			{
				sz.Init();
				pcSeparator->Print(&sz);
				pcDefinition = pcDefinitions->GetSeparator(eSeparator);
				Failed((const char*)pcDefinition->GetName(), (const char*)sz.Text(), iLine, szFile);
				sz.Kill();
				BREAK();
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
CJavaToken* PrivateAssertOperator(CJavaTokenDefinitions* pcDefinitions, CJavaToken* pcToken, EJavaOperator eOperator, int iLine, char* szFile)
{
	CJavaOperator*				pcOperator;
	CChars						sz;
	CJavaOperatorDefinition*	pcDefinition;

	AssertNotNull(pcToken);
	if (pcToken)
	{
		pcOperator = (CJavaOperator*)pcToken;
		AssertTrue(pcToken->IsOperator());
		if (pcToken->IsOperator())
		{
			if (!pcOperator->Is(eOperator))
			{
				sz.Init();
				pcOperator->Print(&sz);
				pcDefinition = pcDefinitions->GetOperator(eOperator);
				Failed((const char*)pcDefinition->GetName(), (const char*)sz.Text(), iLine, szFile);
				sz.Kill();
				BREAK();
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
CJavaToken* PrivateAssertLiteral(CJavaTokenDefinitions* pcDefinitions, CJavaToken* pcToken, char* szString, int iLine, char* szFile)
{
	CJavaString*	pcString;
	CJavaLiteral*	pcLiteral;
	CChars			sz;

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
				if (!pcString->Is(szString))
				{
					sz.Init();
					pcString->Print(&sz);
					Failed((const char*)szString, (const char*)sz.Text(), iLine, szFile);
					sz.Kill();
					BREAK();
				}
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
CJavaToken* PrivateAssertLiteral(CJavaTokenDefinitions* pcDefinitions, CJavaToken* pcToken, int64 lli, int iLine, char* szFile)
{
	CJavaInteger*	pcInteger;
	CJavaLiteral*	pcLiteral;
	CChars			sz;

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
				if (!pcInteger->Is(lli))
				{
					sz.Init();
					pcInteger->Print(&sz);
					Failed(LongLongToString(lli), (const char*)sz.Text(), iLine, szFile);
					sz.Kill();
					BREAK();
				}
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
CJavaToken* PrivateAssertLiteral(CJavaTokenDefinitions* pcDefinitions, CJavaToken* pcToken, int32 i, int iLine, char* szFile)
{
	CJavaInteger*	pcInteger;
	CJavaLiteral*	pcLiteral;
	CChars			sz;

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
				if (!pcInteger->Is(i))
				{
					sz.Init();
					pcInteger->Print(&sz);
					Failed(IntToString(i), (const char*)sz.Text(), iLine, szFile);
					sz.Kill();
					BREAK();
				}
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
CJavaToken* PrivateAssertLiteral(CJavaTokenDefinitions* pcDefinitions, CJavaToken* pcToken, float64 d, int iLine, char* szFile)
{
	CJavaFloat*		pcFloat;
	CJavaLiteral*	pcLiteral;
	CChars			sz;

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
				if (!pcFloat->Is(d))
				{
					sz.Init();
					pcFloat->Print(&sz);
					Failed(DoubleToString(d), (const char*)sz.Text(), iLine, szFile);
					sz.Kill();
					BREAK();
				}
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
CJavaToken* PrivateAssertLiteral(CJavaTokenDefinitions* pcDefinitions, CJavaToken* pcToken, float32 f, int iLine, char* szFile)
{
	CJavaFloat*		pcFloat;
	CJavaLiteral*	pcLiteral;
	CChars			sz;

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
				if (!pcFloat->Is(f))
				{
					sz.Init();
					pcFloat->Print(&sz);
					Failed(FloatToString(f), (const char*)sz.Text(), iLine, szFile);
					sz.Kill();
					BREAK();
				}
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
CJavaToken* PrivateAssertLiteral(CJavaTokenDefinitions* pcDefinitions, CJavaToken* pcToken, char8 c, int iLine, char* szFile)
{
	CJavaCharacter*	pcCharacter;
	CJavaLiteral*	pcLiteral;
	CChars			sz;

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
				if (!pcCharacter->Is(c))
				{
					sz.Init();
					pcCharacter->Print(&sz);
					Failed(CharToString(c), (const char*)sz.Text(), iLine, szFile);
					sz.Kill();
					BREAK();
				}
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
CJavaToken* PrivateAssertLiteral(CJavaTokenDefinitions* pcDefinitions, CJavaToken* pcToken, char16 c, int iLine, char* szFile)
{
	CJavaCharacter*		pcCharacter;
	CJavaLiteral*		pcLiteral;
	CChars				sz;

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
				if (!pcCharacter->Is(c))
				{
					sz.Init();
					pcCharacter->Print(&sz);
					Failed(CharToString(c), (const char*)sz.Text(), iLine, szFile);
					sz.Kill();
					BREAK();
				}
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
CJavaToken* PrivateAssertLiteral(CJavaTokenDefinitions* pcDefinitions, CJavaToken* pcToken, bool b, int iLine, char* szFile)
{
	CJavaBoolean*	pcBoolean;
	CJavaLiteral*	pcLiteral;
	CChars			sz;

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
				if (!pcBoolean->Is(b))
				{
					sz.Init();
					pcBoolean->Print(&sz);
					Failed(BoolToString(b), (const char*)sz.Text(), iLine, szFile);
					sz.Kill();
					BREAK();
				}
			}
		}
		return pcToken->GetNext();
	}

	return NULL;
}

