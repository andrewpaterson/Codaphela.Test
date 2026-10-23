#include <string.h>
#include "BaseLib/Chars.h"
#include "TestLib/Assert.h"
#include "TestAsm65Context.h"


#define LIFE_SIZE	16
#define LIFE_STRIDE	(LIFE_SIZE + 2)
#define LIFE_GRID	0x3000


//A glider, a blinker, a block and a vertical blinker.
static const char* gaszLifePattern[LIFE_SIZE] =
{
	".O..............",
	"..O.............",
	"OOO.............",
	"................",
	"................",
	"..........OOO...",
	"................",
	"................",
	"....OO..........",
	"....OO..........",
	"................",
	"................",
	"............O...",
	"............O...",
	"............O...",
	"................",
};


//////////////////////////////////////////////////////////////////////////
//
// The same rule in C++: cells outside the grid are dead.
//
//////////////////////////////////////////////////////////////////////////
static void LifeGeneration(uint8 aauiGrid[LIFE_SIZE][LIFE_SIZE])
{
	uint8	aauiNext[LIFE_SIZE][LIFE_SIZE];
	int		r;
	int		c;
	int		dr;
	int		dc;
	int		iCount;

	for (r = 0; r < LIFE_SIZE; r++)
	{
		for (c = 0; c < LIFE_SIZE; c++)
		{
			iCount = 0;
			for (dr = -1; dr <= 1; dr++)
			{
				for (dc = -1; dc <= 1; dc++)
				{
					if (((dr != 0) || (dc != 0)) && (r + dr >= 0) && (r + dr < LIFE_SIZE) && (c + dc >= 0) && (c + dc < LIFE_SIZE))
					{
						iCount += aauiGrid[r + dr][c + dc];
					}
				}
			}
			aauiNext[r][c] = ((iCount == 3) || ((iCount == 2) && aauiGrid[r][c])) ? 1 : 0;
		}
	}
	memcpy(aauiGrid, aauiNext, sizeof(aauiNext));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static void AssertLife(int iGenerations)
{
	STestAsm65Run	sRun;
	CChars			szSource;
	uint8			aauiGrid[LIFE_SIZE][LIFE_SIZE];
	int				r;
	int				c;
	int				i;
	int				iDifferent;

	szSource.Init("GENERATIONS = ");
	szSource.Append(iGenerations);
	szSource.AppendNewLine();
	TestAsm65ReadSource(&szSource, "Life.asm");
	for (r = 0; r < LIFE_SIZE; r++)
	{
		szSource.Append("\t\t.org Grid + ");
		szSource.Append(r + 1);
		szSource.Append(" * STRIDE + 1\n\t\t.byte ");
		for (c = 0; c < LIFE_SIZE; c++)
		{
			aauiGrid[r][c] = (gaszLifePattern[r][c] == 'O') ? 1 : 0;
			szSource.Append(c == 0 ? "" : ", ");
			szSource.Append((int)aauiGrid[r][c]);
		}
		szSource.AppendNewLine();
	}
	for (i = 0; i < iGenerations; i++)
	{
		LifeGeneration(aauiGrid);
	}

	AssertTrue(TestAsm65Begin(&sRun, szSource.Text(), 0x1000));
	AssertTrue(TestAsm65Run(&sRun, 1000000) < 1000000);

	iDifferent = 0;
	for (r = 0; r < LIFE_STRIDE; r++)
	{
		for (c = 0; c < LIFE_STRIDE; c++)
		{
			if ((r == 0) || (r == LIFE_STRIDE - 1) || (c == 0) || (c == LIFE_STRIDE - 1))
			{
				iDifferent += sRun.pcContext->GetByte(LIFE_GRID + r * LIFE_STRIDE + c) != 0;
			}
			else
			{
				iDifferent += sRun.pcContext->GetByte(LIFE_GRID + r * LIFE_STRIDE + c) != aauiGrid[r - 1][c - 1];
			}
		}
	}
	AssertInt(0, iDifferent);

	TestAsm65End(&sRun);
	szSource.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65LifeGenerations(void)
{
	AssertLife(1);
	AssertLife(4);
	AssertLife(9);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65Life(void)
{
	BeginTests();

	TestAsm65LifeGenerations();

	TestStatistics();
}
