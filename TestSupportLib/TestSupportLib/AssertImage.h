#ifndef __ASSERT_IMAGE_H__
#include "SupportLib/Image.h"


#define AssertChannel(eip, ect, ept, c) Validate(PrivateAssertChannel(eip, ect, ept, c, __LINE__, __FILE__))


bool PrivateAssertChannel(EImagePurpose ePurpose, EChannelType eType, EPrimitiveType ePrimitive, SChannel* psChannel, size iLine, char* szFile);


#endif // !__ASSERT_IMAGE_H__

