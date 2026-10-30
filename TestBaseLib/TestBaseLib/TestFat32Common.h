#ifndef __TEST_FAT_32_COMMON_H__
#define __TEST_FAT_32_COMMON_H__
#include <stdlib.h>
#include <string.h>
#include "BaseLib/PrimitiveTypes.h"
#include "BaseLib/FileDrive.h"


#define FAT_TEST_PAGE_SECTORS		64
#define FAT_TEST_PAGE_BYTES			((uint32)FAT_TEST_PAGE_SECTORS * 512)


char* AllocateStringBuffer(lsize uiSize);


//A drive that keeps only the pages of sectors written to (the others read as zeros), so it can be as big as FAT32
//needs (65525 clusters) in a little memory.  Its pages are smaller than 64KB (a W65C816 size).
class CFatTestDrive : public CFileDrive
{
protected:
	uint8**	mapuiPages;
	uint32	muiPages;

public:
	void Init(uint64 uiSectors)
	{
		CFileDrive::Init(512);
		muiMaxSector = uiSectors;
		muiPages = (uint32)((uiSectors + FAT_TEST_PAGE_SECTORS - 1) / FAT_TEST_PAGE_SECTORS);
		mapuiPages = (uint8**)malloc(muiPages * sizeof(uint8*));
		memset(mapuiPages, 0, muiPages * sizeof(uint8*));
	}

	void Kill(void)
	{
		uint32	i;

		for (i = 0; i < muiPages; i++)
		{
			free(mapuiPages[i]);
		}
		free(mapuiPages);
	}

	bool Read(uint64 uiSector, void* pvData)
	{
		return Read(uiSector, 1, pvData);
	}

	bool Read(uint64 uiSector, uint32 uiNumSectors, void* pvData)
	{
		uint8*	puiPage;
		uint32	i;

		if (uiSector + uiNumSectors > muiMaxSector)
		{
			return false;
		}
		for (i = 0; i < uiNumSectors; i++)
		{
			puiPage = mapuiPages[(uint32)((uiSector + i) / FAT_TEST_PAGE_SECTORS)];
			if (puiPage)
			{
				memcpy((uint8*)pvData + i * 512, &puiPage[(uint32)((uiSector + i) % FAT_TEST_PAGE_SECTORS) * 512], 512);
			}
			else
			{
				memset((uint8*)pvData + i * 512, 0, 512);
			}
		}
		return true;
	}

	bool Write(uint64 uiSector, void* pvData)
	{
		return Write(uiSector, 1, pvData);
	}

	bool Write(uint64 uiSector, uint32 uiNumSectors, void* pvData)
	{
		uint8**	ppuiPage;
		uint32	i;

		if (uiSector + uiNumSectors > muiMaxSector)
		{
			return false;
		}
		for (i = 0; i < uiNumSectors; i++)
		{
			ppuiPage = &mapuiPages[(uint32)((uiSector + i) / FAT_TEST_PAGE_SECTORS)];
			if (*ppuiPage == NULL)
			{
				*ppuiPage = (uint8*)malloc(FAT_TEST_PAGE_BYTES);
				memset(*ppuiPage, 0, FAT_TEST_PAGE_BYTES);
			}
			memcpy(&(*ppuiPage)[(uint32)((uiSector + i) % FAT_TEST_PAGE_SECTORS) * 512], (uint8*)pvData + i * 512, 512);
		}
		return true;
	}

	bool Erase(uint64 uiStartSector, uint64 uiStopSectorInclusive)
	{
		uint8	auiZero[512];
		uint64	uiSector;

		memset(auiZero, 0, 512);
		for (uiSector = uiStartSector; uiSector <= uiStopSectorInclusive; uiSector++)
		{
			if (mapuiPages[(uint32)(uiSector / FAT_TEST_PAGE_SECTORS)] && !Write(uiSector, auiZero))
			{
				return false;
			}
		}
		return true;
	}
};


#endif // __TEST_FAT_32_COMMON_H__

