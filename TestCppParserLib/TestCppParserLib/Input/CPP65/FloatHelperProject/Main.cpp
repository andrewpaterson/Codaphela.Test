#include "BaseLib/FloatHelper.h"


//The results go to 0010:0000, a long or two each.
unsigned*	gpuiResult = (unsigned*)0x100000;


void Float32Result(float32 f)
{
	*gpuiResult++ = *(unsigned*)&f;
}


void Float64Result(float64 d)
{
	unsigned long long	ulli;

	ulli = *(unsigned long long*)&d;
	*gpuiResult++ = (unsigned)ulli;
	*gpuiResult++ = (unsigned)(ulli >> 32);
}


void IntegerResult(int i)
{
	*gpuiResult++ = (unsigned)i;
}


#define FLOAT32(x)	Float32Result(x)
#define FLOAT64(x)	Float64Result(x)
#define INTEGER(x)	IntegerResult(x)


int main()
{
#include "FloatHelperCalls.h"
	return (int)(gpuiResult - (unsigned*)0x100000);
}

