#ifndef __TEST_W65C816_CONTEXT_H__
#define __TEST_W65C816_CONTEXT_H__
#include "BaseLib/PrimitiveTypes.h"
#include "BaseLib/Chars.h"


class CTestW65C816Context
{
protected:
	uint8	muiBank;
	uint8*	mauiMemory;
	CChars	mszSequence;
	uint32	muiMemorySize;
	uint8	muiFill;

public:
	void		Init(uint32 uiMemorySize, uint8 uiFill);
	void		Kill(void);

	uint8		GetBank(void);
	void		SetBank(uint8 uiBank);
	uint8*		GetMemory(void);
	uint8		GetMemory(uint32 uiAddress);
	void		SetMemory(uint32 uiAddress, uint8 uiValue);
	CChars*		GetSequence(void);
	char*		SequenceText(void);
};


#endif // __TEST_W65C816_CONTEXT_H__

