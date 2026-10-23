#include "BaseLib/Quaternion.h"


//The results go to 0010:0000, a long each.
unsigned*	gpuiResult = (unsigned*)0x100000;


void QuaternionResult(SQuaternion q)
{
	*gpuiResult++ = *(unsigned*)&q.x;
	*gpuiResult++ = *(unsigned*)&q.y;
	*gpuiResult++ = *(unsigned*)&q.z;
	*gpuiResult++ = *(unsigned*)&q.w;
}


void IntegerResult(int i)
{
	*gpuiResult++ = (unsigned)i;
}


#define QUATERNION(x)	QuaternionResult(x)
#define INTEGER(x)		IntegerResult(x)


int main()
{
#include "QuaternionCalls.h"
	return (int)(gpuiResult - (unsigned*)0x100000);
}

