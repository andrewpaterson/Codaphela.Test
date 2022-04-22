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
void TestTokenParser(void)
{
	BeginTests();

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

	cTokenParser.Kill();

	TestStatistics();
}

