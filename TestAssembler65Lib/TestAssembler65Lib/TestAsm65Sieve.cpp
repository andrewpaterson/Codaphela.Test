#include <stdlib.h>
#include <string.h>
#include "TestLib/Assert.h"
#include "TestAsm65Context.h"


#define SIEVE_N			10000
#define SIEVE_ADDRESS	0x10000
#define SIEVE_PRIMES	0x20000
#define SIEVE_COUNT		0x0100


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65SievePrimes(void)
{
	STestAsm65Run	sRun;
	uint8*			pbPrime;
	uint32			i;
	uint32			j;
	uint32			uiCount;
	int				iMismatches;

	pbPrime = (uint8*)malloc(SIEVE_N);
	memset(pbPrime, 1, SIEVE_N);
	pbPrime[0] = 0;
	pbPrime[1] = 0;
	for (i = 2; i * i < SIEVE_N; i++)
	{
		if (pbPrime[i])
		{
			for (j = i * i; j < SIEVE_N; j += i)
			{
				pbPrime[j] = 0;
			}
		}
	}

	AssertTrue(TestAsm65BeginFile(&sRun, "Sieve.asm", 0x1000));
	AssertTrue(TestAsm65Run(&sRun, 1000000) < 1000000);

	//The sieve itself, and the block copy stopped at its end.
	iMismatches = 0;
	for (i = 0; i < SIEVE_N; i++)
	{
		if (sRun.pcContext->GetByte(SIEVE_ADDRESS + i) != pbPrime[i])
		{
			iMismatches++;
		}
	}
	AssertInt(0, iMismatches);
	AssertInt(0, sRun.pcContext->GetByte(SIEVE_ADDRESS + SIEVE_N));

	//The primes in order, then nothing.
	uiCount = 0;
	iMismatches = 0;
	for (i = 0; i < SIEVE_N; i++)
	{
		if (pbPrime[i])
		{
			if (sRun.pcContext->GetLong(SIEVE_PRIMES + 4 * uiCount) != i)
			{
				iMismatches++;
			}
			uiCount++;
		}
	}
	AssertInt(0, iMismatches);
	AssertInt(1229, uiCount);
	AssertInt(1229, sRun.pcContext->GetLong(SIEVE_COUNT));
	AssertInt(2, sRun.pcContext->GetLong(SIEVE_PRIMES));
	AssertInt(9973, sRun.pcContext->GetLong(SIEVE_PRIMES + 4 * 1228));
	AssertInt(0, sRun.pcContext->GetLong(SIEVE_PRIMES + 4 * 1229));

	TestAsm65End(&sRun);
	free(pbPrime);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65Sieve(void)
{
	BeginTests();

	TestAsm65SievePrimes();

	TestStatistics();
}
