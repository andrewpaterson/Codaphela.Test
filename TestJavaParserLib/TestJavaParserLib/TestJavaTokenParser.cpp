#include "BaseLib/FastFunctions.h"
#include "BaseLib/PointerRemapper.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/TypeConverter.h"
#include "CoreLib/Operators.h"
#include "TestLib/Assert.h"
#include "JavaParserLib/JavaTokenParser.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTokenParserEndOfFile(void)
{
	CJavaTokenParser	cTokenParser;

	cTokenParser.Init("{\n}");
	cTokenParser.Parse();
	cTokenParser.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTokenParserStartAndEndWithComment(void)
{
	CJavaTokenParser	cTokenParser;
	
	cTokenParser.Init("\
  // Tickable Pins Start\n\
package net.simulation.common;\n\
\n\
{\n\
  protected int x;\n\
} // Tickable Pins End\
");

	cTokenParser.Parse();

	cTokenParser.GetFirstToken();

	cTokenParser.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTokenParserComplexGeneric(void)
{
	CJavaTokenParser	cTokenParser;

	cTokenParser.Init("\
  // Tickable Pins\n\
package net.simulation.common;\n\
\n\
import net.common.*;\n\
\n\
import java.util.Set; \n\
\n\
public abstract class TickablePins<\n\
	SNAPSHOT extends Snapshot,\n\
	PINS extends Pins<SNAPSHOT, PINS, ? extends IntegratedCircuit<SNAPSHOT, PINS>>,\n\
	INTEGRATED_CIRCUIT extends IntegratedCircuit<SNAPSHOT, PINS>>\n\
{\n\
  protected INTEGRATED_CIRCUIT integratedCircuit;\n\
  protected SNAPSHOT snapshot;\n\
}\
");

	cTokenParser.Parse();
	cTokenParser.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTokenParser(void)
{
	BeginTests();

	TestTokenParserEndOfFile();
	TestTokenParserStartAndEndWithComment();
	TestTokenParserComplexGeneric();

	TestStatistics();
}

