//Libc65/softfloat.cpp compiled natively: the reference that Libc65/softfloat.asm is checked against.
#ifdef _MSC_VER
static int __builtin_clzll(unsigned long long ulli)
{
	int	i;

	for (i = 0; (ulli & 0x8000000000000000ULL) == 0; i++)
	{
		ulli <<= 1;
	}
	return i;
}
#endif // _MSC_VER

#include "Libc65/softfloat.cpp"

