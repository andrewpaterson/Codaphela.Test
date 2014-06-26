#ifndef __FILE_IO_TEST_OBJECTS_H__
#define __FILE_IO_TEST_OBJECTS_H__
#include "BaseLib/Define.h"


class CFileIOTest
{
protected:
	char	msz[17];
	int		miNumber;

public:
	void Init(int iNumber);
	void Kill(void);

	BOOL IsOkay(int iNumber);
};


#endif // __FILE_IO_TEST_OBJECTS_H__

