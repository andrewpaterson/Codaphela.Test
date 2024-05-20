#include <stdlib.h>
#include "TestFat32Common.h"



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
char* AllocateStringBuffer(size uiSize)
{
	char*	 szSource;
	char	c;
	size	i;

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

