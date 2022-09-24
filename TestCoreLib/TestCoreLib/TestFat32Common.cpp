#include <stdlib.h>
#include "TestFat32Common.h"



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
char* AllocateStringBuffer(uint32 uiSize)
{
	char* szSource;
	char	c;
	uint32	i;

	szSource = (char*)malloc(uiSize);
	c = 'A';
	for (i = 0; i < uiSize; i++)
	{
		szSource[i] = c;
		c++;
		if (c == 127)
		{
			c = 'A';
		}
		if ((c == ' ') || (c == '\\') || (c == '"'))
		{
			c++;
		}
	}
	i--;
	szSource[i] = '\0';

	return szSource;

}

