#ifndef __TEST_W65C816_CONTEXT_H__
#define __TEST_W65C816_CONTEXT_H__
#include "BaseLib/PrimitiveTypes.h"
#include "BaseLib/Chars.h"
#include "MicroprocessorLib/MetaW65C816.h"


class CTestW65C816Context
{
protected:
	uint8	muiBank;
	uint8*	mauiMemory;
	CChars	mszSequence;
	uint32	muiMemorySize;
	uint8	muiFill;

public:
	bool	mbPrintA;
	bool	mbPrintX;
	bool	mbPrintY;
	bool	mbPrintPC;
	bool	mbPrintS;
	bool	mbPrintDP; 
	bool	mbPrintDB;
	bool	mbPrintP;

public:
	void		Init(uint32 uiMemorySize, uint8 uiFill);
	void		SetPrint(bool bA, bool bX, bool bY, bool bPC, bool bS, bool bDP, bool bDB, bool bP);
	void		Kill(void);

	uint8		GetBank(void);
	void		SetBank(uint8 uiBank);
	uint8*		GetMemory(void);
	uint8		GetMemory(uint32 uiAddress);
	void		SetMemory(uint32 uiAddress, uint8 uiValue);
	CChars*		GetSequence(void);
	char*		SequenceText(void);
};


void TestW65C81ContextTickLow(CMetaW65C816* pcMPU, void* pvContext);
void TestW65C81ContextTickHigh(CMetaW65C816* pcMPU, void* pvContext);


#endif // __TEST_W65C816_CONTEXT_H__

