#ifndef __JAVA_TOKEN_ASSERT_H__
#define __JAVA_TOKEN_ASSERT_H__
#include "BaseLib/PrimitiveTypes.h"
#include "JavaParserLib/JavaTokenMemory.h"


CJavaToken* AssertKeyword(CJavaToken* pcToken, EJavaKeyword eKeyword);
CJavaToken* AssertIdentifier(CJavaToken* pcToken, char* szIdentifier);
CJavaToken* AssertSeparator(CJavaToken* pcToken, EJavaSeparator eSeparator);
CJavaToken* AssertOperator(CJavaToken* pcToken, EJavaOperator eOperator);
CJavaToken* AssertLiteral(CJavaToken* pcToken, char* szString);
CJavaToken* AssertLiteral(CJavaToken* pcToken, int64 lli);
CJavaToken* AssertLiteral(CJavaToken* pcToken, int32 i);
CJavaToken* AssertLiteral(CJavaToken* pcToken, float32 f);
CJavaToken* AssertLiteral(CJavaToken* pcToken, float64 d);
CJavaToken* AssertLiteral(CJavaToken* pcToken, char8 c);
CJavaToken* AssertLiteral(CJavaToken* pcToken, char16 c);
CJavaToken* AssertLiteral(CJavaToken* pcToken, bool b);


#endif // !__JAVA_TOKEN_ASSERT_H__

