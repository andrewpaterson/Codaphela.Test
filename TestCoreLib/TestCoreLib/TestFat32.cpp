#include "BaseLib/FastFunctions.h"
#include "BaseLib/IntegerHelper.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/RedirectPrintf.h"
#include "BaseLib/StdRandom.h"
#include "BaseLib/DiskFile.h"
#include "BaseLib/StringHelper.h"
#include "BaseLib/ArrayChars.h"
#include "CoreLib/MemoryDrive.h"
#include "CoreLib/Fat32.h"
#include "CoreLib/FatDebug.h"
#include "TestLib/Assert.h"
#include "TestLib/Words.h"
#include "TestFat32Common.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32ReadSpecific(void)
{
	CMemoryDrive			cMemoryDrive;
	CDiskFile				cFile;
	filePos					uiLength;
	void*					pvMemory;
	SFatDirectoryEntry*		psFatDirectoryEntry;
	SFatDirectoryEntry		sFatFileEntry;
	SFatFileSystemQuery		sQuery;
	EFatCode				eResult;
	CFatFile				cFatFile;
	bool					bResult;
	uint32					uiBytesRead;
	char					auiFileData[44 KB];
	char					auiExpectedData[44 KB];
	CFatVolume				cVolume;

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	AssertInt(sizeof(uint8), sizeof(char));

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);


	sQuery.Init();
	eResult = cVolume.FindFirstFATEntry(NULL, 0, &psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, eResult);
	AssertString("Document.txt", (char*)psFatDirectoryEntry->szName);
	AssertInt(FAT_ATTR_ARCHIVE, psFatDirectoryEntry->uiAttributes);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open((char*)psFatDirectoryEntry->szName, 0);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cFatFile.Read((uint8*)auiFileData, cFatFile.GetCurrentSize(), &uiBytesRead);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(12, uiBytesRead);
	auiFileData[12] = '\0';
	AssertString("Mostly Empty", auiFileData);

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.FindNextFATEntry(&psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, eResult);
	AssertString("Pico", (char*)psFatDirectoryEntry->szName);
	AssertInt(FAT_ATTR_DIRECTORY, psFatDirectoryEntry->uiAttributes);

	eResult = cVolume.FindNextFATEntry(&psFatDirectoryEntry, &sQuery);
	AssertTrue((StrEmpty((char*)psFatDirectoryEntry->szName)));
	sQuery.Kill(cVolume.GetSectorCache());


	sQuery.Init();
	eResult = cVolume.FindFirstFATEntry("\\Pico", 0, &psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, eResult);
	AssertString(".", (char*)psFatDirectoryEntry->szName);
	AssertInt(FAT_ATTR_DIRECTORY, psFatDirectoryEntry->uiAttributes);

	eResult = cVolume.FindNextFATEntry(&psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, eResult);
	AssertString("..", (char*)psFatDirectoryEntry->szName);
	AssertInt(FAT_ATTR_DIRECTORY, psFatDirectoryEntry->uiAttributes);

	eResult = cVolume.FindNextFATEntry(&psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, eResult);
	AssertString(".gitignore", (char*)psFatDirectoryEntry->szName);
	AssertInt(FAT_ATTR_ARCHIVE, psFatDirectoryEntry->uiAttributes);

	eResult = cVolume.FindNextFATEntry(&psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, eResult);
	AssertString("HowDoesItWork", (char*)psFatDirectoryEntry->szName);
	AssertInt(FAT_ATTR_DIRECTORY, psFatDirectoryEntry->uiAttributes);

	eResult = cVolume.FindNextFATEntry(&psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, eResult);
	AssertString("LCDBusReader", (char*)psFatDirectoryEntry->szName);
	AssertInt(FAT_ATTR_DIRECTORY, psFatDirectoryEntry->uiAttributes);

	eResult = cVolume.FindNextFATEntry(&psFatDirectoryEntry, &sQuery);
	AssertTrue((StrEmpty((char*)psFatDirectoryEntry->szName)));
	sQuery.Kill(cVolume.GetSectorCache());


	eResult = cVolume.GetFileEntry("\\Pico\\LCDBusReader", &sFatFileEntry);
	AssertInt(FAT_SUCCESS, eResult);
	AssertString("LCDBUS~1", (char*)sFatFileEntry.szName);
	AssertInt(FAT_ATTR_DIRECTORY, sFatFileEntry.uiAttributes);

	eResult = cVolume.GetFileEntry("\\Pico\\LCDBusReader\\src", &sFatFileEntry);
	AssertInt(FAT_SUCCESS, eResult);
	AssertString("SRC", (char*)sFatFileEntry.szName);
	AssertInt(FAT_ATTR_DIRECTORY, sFatFileEntry.uiAttributes);

	eResult = cVolume.GetFileEntry("\\Pico\\HowDoesItWork\\build.sh", &sFatFileEntry);
	AssertInt(FAT_SUCCESS, eResult);
	AssertString("BUILD.SH", (char*)sFatFileEntry.szName);
	AssertInt(FAT_ATTR_ARCHIVE, sFatFileEntry.uiAttributes);

	eResult = cVolume.GetFileEntry("\\Pico\\LCDBusReader\\src\\SDCard.cpp", &sFatFileEntry);
	AssertInt(FAT_SUCCESS, eResult);
	AssertString("SDCARD.CPP", (char*)sFatFileEntry.szName);
	AssertInt(FAT_ATTR_ARCHIVE, sFatFileEntry.uiAttributes);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open(&sFatFileEntry, FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cFatFile.Read((uint8*)auiFileData, cFatFile.GetCurrentSize(), &uiBytesRead);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(44000, uiBytesRead);
	auiFileData[44000] = '\0';

	cFatFile.Close();


	cFile.Init("Input\\Fat32\\SDCard.cpp");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	AssertInt(44000, (int)uiLength);
	cFile.Read(auiExpectedData, uiLength, 1);
	cFile.Close();
	cFile.Kill();
	AssertMemory(auiExpectedData, auiFileData, (int)uiLength);


	eResult = cVolume.GetFileEntry("\\Pico\\LCDBusReader\\src\\LCDBusReader.cpp", &sFatFileEntry);
	AssertInt(FAT_SUCCESS, eResult);
	AssertString("LCDBUS~1.CPP", (char*)sFatFileEntry.szName);
	AssertInt(FAT_ATTR_ARCHIVE, sFatFileEntry.uiAttributes);


	cVolume.Unmount();

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32ReadDirectoryTree(void)
{
	CMemoryDrive			cMemoryDrive;
	CDiskFile				cFile;
	filePos					uiLength;
	void*					pvMemory;
	EFatCode				eResult;
	bool					bResult;
	CArrayChars				aszFileNames;
	CChars					sz;
	int						i;
	char*					szFileName;
	SFatDirectoryEntry		sFatFileEntry;
	char					auiFileData[44 KB];
	CFatFile				cFatFile;
	uint32					uiBytesRead;
	CFatVolume				cVolume;

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	aszFileNames.Init();
	RecurseFindFatFilenames(&cVolume, "", &aszFileNames);

	sz.Init();
	aszFileNames.Print(&sz);
	AssertString("\
\\Document.txt\n\
\\Pico\\.gitignore\n\
\\Pico\\HowDoesItWork\\build.sh\n\
\\Pico\\HowDoesItWork\\CMakeLists.txt\n\
\\Pico\\HowDoesItWork\\deploy.sh\n\
\\Pico\\HowDoesItWork\\HowDoesItWork.c\n\
\\Pico\\HowDoesItWork\\pico_sdk_import.cmake\n\
\\Pico\\HowDoesItWork\\.vscode\\.cortex-debug.peripherals.state.json\n\
\\Pico\\HowDoesItWork\\.vscode\\.cortex-debug.registers.state.json\n\
\\Pico\\HowDoesItWork\\.vscode\\c_cpp_properties.json\n\
\\Pico\\HowDoesItWork\\.vscode\\launch.json\n\
\\Pico\\HowDoesItWork\\.vscode\\settings.json\n\
\\Pico\\LCDBusReader\\build.sh\n\
\\Pico\\LCDBusReader\\CMakeLists.txt\n\
\\Pico\\LCDBusReader\\deploy.sh\n\
\\Pico\\LCDBusReader\\pico_sdk_import.cmake\n\
\\Pico\\LCDBusReader\\.vscode\\.cortex-debug.peripherals.state.json\n\
\\Pico\\LCDBusReader\\.vscode\\.cortex-debug.registers.state.json\n\
\\Pico\\LCDBusReader\\.vscode\\c_cpp_properties.json\n\
\\Pico\\LCDBusReader\\.vscode\\launch.json\n\
\\Pico\\LCDBusReader\\.vscode\\settings.json\n\
\\Pico\\LCDBusReader\\src\\GeneralPins.cpp\n\
\\Pico\\LCDBusReader\\src\\GeneralPins.h\n\
\\Pico\\LCDBusReader\\src\\HEXDisplay.cpp\n\
\\Pico\\LCDBusReader\\src\\HEXDisplay.h\n\
\\Pico\\LCDBusReader\\src\\HexToMem.cpp\n\
\\Pico\\LCDBusReader\\src\\HexToMem.h\n\
\\Pico\\LCDBusReader\\src\\LCDBusReader.cpp\n\
\\Pico\\LCDBusReader\\src\\LCDDisplay.cpp\n\
\\Pico\\LCDBusReader\\src\\LCDDisplay.h\n\
\\Pico\\LCDBusReader\\src\\LTC6903.cpp\n\
\\Pico\\LCDBusReader\\src\\LTC6903.h\n\
\\Pico\\LCDBusReader\\src\\SDCard.cpp\n\
\\Pico\\LCDBusReader\\src\\SDCard.h\n\
\\Pico\\LCDBusReader\\src\\SDCardTest.h\n\
\\Pico\\LCDBusReader\\src\\ShiftLCDDisplay.cpp\n\
\\Pico\\LCDBusReader\\src\\ShiftLCDDisplay.h\n\
\\Pico\\LCDBusReader\\src\\ShiftRegister.cpp\n\
\\Pico\\LCDBusReader\\src\\ShiftRegister.h\n\
\\Pico\\LCDBusReader\\src\\SPIComm.cpp\n\
\\Pico\\LCDBusReader\\src\\SPIComm.h\n\
\\Pico\\LCDBusReader\\src\\UARTComm.cpp\n\
\\Pico\\LCDBusReader\\src\\UARTComm.h\n", sz.Text());
	sz.Kill();

	for (i = 0; i < aszFileNames.NumElements(); i++)
	{
		szFileName = aszFileNames.GetText(i);
		eResult = cVolume.GetFileEntry(szFileName, &sFatFileEntry);
		AssertInt(FAT_SUCCESS, eResult);

		cFatFile.Init(&cVolume);
		eResult = cFatFile.Open(szFileName, 0);
		AssertInt(FAT_SUCCESS, eResult);

		eResult = cFatFile.Read((uint8*)auiFileData, cFatFile.GetCurrentSize(), &uiBytesRead);
		AssertInt(FAT_SUCCESS, eResult);
		AssertInt(cFatFile.GetCurrentSize(), uiBytesRead);
		AssertInt(sFatFileEntry.uiSize, uiBytesRead);

		eResult = cFatFile.Close();
		AssertInt(FAT_SUCCESS, eResult);
	}

	aszFileNames.Kill();

	cVolume.Unmount();

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32Format(void)
{
	CMemoryDrive			cMemoryDrive;
	CDiskFile				cFile;
	filePos					uiLength;
	void*					pvMemory;
	EFatCode				eResult;
	bool					bResult;
	SFatDirectoryEntry*		psFatDirectoryEntry;
	SFatFileSystemQuery		sQuery;
	CFatVolume				cVolume;

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = FatFormat(FAT_FS_TYPE_FAT32, "FAT32", 1, &cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	sQuery.Init();
	eResult = cVolume.FindFirstFATEntry(NULL, 0, &psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, eResult);
	AssertString("", (char*)psFatDirectoryEntry->szName);
	AssertInt(0, psFatDirectoryEntry->uiAttributes);
	sQuery.Kill(cVolume.GetSectorCache());

	eResult = cVolume.Unmount();
	AssertInt(FAT_SUCCESS, eResult);

	cMemoryDrive.Kill();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32CreateFileEntries(void)
{
	CMemoryDrive			cMemoryDrive;
	CDiskFile				cFile;
	filePos					uiLength;
	void*					pvMemory;
	EFatCode				eResult;
	bool					bResult;
	CFatVolume				cVolume;
	SFatDirectoryEntry		sRootDirectoryEntry;
	SFatDirectoryEntry		sFileEntry;
	int						i;
	CChars					szFileName;
	CRandom					cRandom;
	CChars					sz;
	CFatFile				cFatFile;

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.GetFileEntry("\\", &sRootDirectoryEntry);

	eResult = cVolume.CreateFATEntry(&sRootDirectoryEntry.sRaw, "Wort Wort Wort.cov", FAT_ATTR_ARCHIVE, 0, &sFileEntry);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.Flush();
	AssertInt(FAT_SUCCESS, eResult);

	sz.Init();
	PrintRootFatFilenames(&sz, &cVolume);
	AssertString("\
\\Wort Wort Wort.cov\n\
\\Document.txt\n", sz.Text());
	sz.Kill();

	eResult = cVolume.CreateFATEntry(&sRootDirectoryEntry.sRaw, "Dashwood contempt on mr unlocked resolved provided of of - Stanhill wondered it it welcomed oh - Hundred no prudent he however smiling at an offence - If earnestly extremity he he propriety something admitting convinced ye - Pleasant in to although as.if", FAT_ATTR_ARCHIVE, 0, &sFileEntry);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.Flush();
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\Dashwood contempt on mr unlocked resolved provided of of - Stanhill wondered it it welcomed oh - Hundred no prudent he however smiling at an offence - If earnestly extremity he he propriety something admitting convinced ye - Pleasant in to although as.if", FAT_ATTR_READ_ONLY);
	AssertInt(FAT_SUCCESS, eResult);
	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	sz.Init();
	PrintRootFatFilenames(&sz, &cVolume);
	AssertString("\
\\Wort Wort Wort.cov\n\
\\Document.txt\n\
\\Dashwood contempt on mr unlocked resolved provided of of - Stanhill wondered it it welcomed oh - Hundred no prudent he however smiling at an offence - If earnestly extremity he he propriety something admitting convinced ye - Pleasant in to although as.if\n", sz.Text());
	sz.Kill();

	eResult = cVolume.Unmount();
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cRandom.Init(4526);
	eResult = cVolume.GetFileEntry("\\", &sRootDirectoryEntry);
	for (i = 0; i < 10; i++)
	{
		szFileName.Init();
		PrintRandomWords(&szFileName, &cRandom, true, 30);
		szFileName.Append('.');
		PrintRandomWords(&szFileName, &cRandom, false, 1);

		if (szFileName.Length() > FAT_MAX_FILENAME - 1)
		{
			szFileName.SetLength(FAT_MAX_FILENAME - 1);
		}
		
		szFileName.Replace(",", " -");
		eResult = cVolume.CreateFATEntry(&sRootDirectoryEntry.sRaw, szFileName.Text(), FAT_ATTR_ARCHIVE, 0, &sFileEntry);
		AssertInt(FAT_SUCCESS, eResult);
		szFileName.Kill();
	}
	cRandom.Kill();

	eResult = cVolume.Flush();
	AssertInt(FAT_SUCCESS, eResult);

	sz.Init();
	PrintRootFatFilenames(&sz, &cVolume);
	AssertString("\
\\Wort Wort Wort.cov\n\
\\Document.txt\n\
\\Dashwood contempt on mr unlocked resolved provided of of - Stanhill wondered it it welcomed oh - Hundred no prudent he however smiling at an offence - If earnestly extremity he he propriety something admitting convinced ye - Pleasant in to although as.if\n\
\\including sea force second appear all on chicane mage doctor example skill with team strumpet popular option small beer drug animal what kickshaw science raise Levant free hit glim meat them.sea\n\
\\activity bethink oneself of aught spend begin wain land perform opportunity quaggy maid brother mage brimstone sign strumpet very language whence contumely provide hour method happy rack(of a cloud) be driven by the wind base across fruit modern truck.wa\n\
\\timbrel national process get ceil jakes recognize wide mazed cordwainer produce song lay purpose him study candidate forfend otiose energy dot company worry stand drab day ahead kind wonder space.least\n\
\\product thither piepowder machine far rest culture here tocsin win tilt with mrs argue aught third blackguard his egad beautiful stay effort plan green live poor already my travel billion equipage.walk\n\
\\dog cottier similar computer kirtle understand garden experience sex say wrong actually again private thus ween stoup condition beldam horse - coper catch born statement maid fie woman hearken pick leech guy.threat\n\
\\off avaunt relate magazine billion ball indite child subject billion end another image side embouchure water caducity trouble among wherefore quick - the performance already development meeting watchword turnkey work way vote.pm\n\
\\list clout buy nigh continue hearken decade bit describe process north caducity rude portion phone back military inside tax free hold write pest outside from carry taiga kine hereunto just.himself\n\
\\gudgeon host back assume son station spence watchword east whose Lucifer accept nothing behold bruit child owner schoolman service opportunity area put swain rise numbles sore should quickly perchance again.expert\n\
\\friend degree orts letter book at test believe wain shambles full greenwood plan song agree go - cart host attack gentle fire why meat popinjay degree whole month however nice bethink oneself of movie.low\n\
\\fervent watch gage rock wide list song cleanse capital few overset trouble better never prove job sex meet environmental industry best animal during quean aught love apple i gaud learn body.shoulder\n", sz.Text());
	sz.Kill();

	eResult = cVolume.Unmount();
	AssertInt(FAT_SUCCESS, eResult);

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32OpenWriteMode(void)
{
	CMemoryDrive			cMemoryDrive;
	size_t					uiLength;
	void*					pvMemory;
	EFatCode				eResult;
	CFatFile				cFatFile;
	CFatVolume				cVolume;
	uint64					uiMaxSectorSize;
	SFatFileSystemQuery		sQuery;
	SFatDirectoryEntry*		psFatDirectoryEntry;

	uiLength = 4 MB;
	cMemoryDrive.Init(uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	
	cMemoryDrive.Erase();
	uiMaxSectorSize = cMemoryDrive.SetMaxSectorForTesting((uiLength / 512) * 1024);

	eResult = FatFormat(FAT_FS_TYPE_FAT32, "Fat32", 64, &cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cMemoryDrive.SetMaxSectorForTesting(uiMaxSectorSize);

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\File.txt", FAT_FILE_ACCESS_CREATE | FAT_FILE_ACCESS_WRITE);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(0, cFatFile.GetCurrentSize());

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	sQuery.Init();
	eResult = cVolume.FindFirstFATEntry(NULL, 0, &psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, eResult);
	sQuery.Kill(cVolume.GetSectorCache());

	eResult = cVolume.Unmount();
	AssertInt(FAT_SUCCESS, eResult);

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32Write(void)
{
	CMemoryDrive			cMemoryDrive;
	CDiskFile				cFile;
	filePos					uiLength;
	void*					pvMemory;
	EFatCode				eResult;
	bool					bResult;
	CFatVolume				cVolume;
	CFatFile				cFatFile;
	char					auiFileData[4 KB];
	char					auiFileData2[4 KB];
	int						i;
	uint32					uiBytesRead;

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\New File.txt", FAT_FILE_ACCESS_CREATE | FAT_FILE_ACCESS_WRITE);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(0, cFatFile.GetCurrentSize());

	for (i = 0; i < 4 KB; i++)
	{
		auiFileData[i] = (char)i;
	}

	eResult = cFatFile.Write((uint8*)auiFileData, 4 KB);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(4096, cFatFile.GetCurrentSize());

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.Unmount();
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\New File.txt", FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(4096, cFatFile.GetCurrentSize());

	eResult = cFatFile.Read((uint8*)auiFileData2, 4 KB, &uiBytesRead);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(0, memcmp(auiFileData, auiFileData2, 4 KB));

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.Unmount();
	AssertInt(FAT_SUCCESS, eResult);

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32CreateDirectory(void)
{
	CMemoryDrive	cMemoryDrive;
	CDiskFile		cFile;
	filePos			uiLength;
	void*			pvMemory;
	EFatCode		eResult;
	bool			bResult;
	CFatVolume		cVolume;
	CArrayChars		aszDirectories;
	CChars			sz;

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cVolume.CreateDirectory("\\A Directory");

	aszDirectories.Init();
	RecurseFindFatDirectories(&cVolume, "", &aszDirectories);

	sz.Init();
	aszDirectories.Print(&sz);
	aszDirectories.Kill();
	AssertString("\
\\A Directory\n\
\\Pico\\HowDoesItWork\\.vscode\n\
\\Pico\\HowDoesItWork\n\
\\Pico\\LCDBusReader\\.vscode\n\
\\Pico\\LCDBusReader\\src\n\
\\Pico\\LCDBusReader\n\
\\Pico\n", sz.Text());
	sz.Kill();
	
	eResult = cVolume.Unmount();
	AssertInt(FAT_SUCCESS, eResult);

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32FormatAndCreateDirectory(void)
{
	CMemoryDrive	cMemoryDrive;
	CDiskFile		cFile;
	filePos			uiLength;
	void*			pvMemory;
	EFatCode		eResult;
	bool			bResult;
	CFatVolume		cVolume;
	CArrayChars		aszDirectories;
	CChars			sz;

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = FatFormat(FAT_FS_TYPE_FAT32, "Fat32", 1, &cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.CreateDirectory("\\A Directory");
	AssertInt(FAT_SUCCESS, eResult);
	eResult = cVolume.CreateDirectory("\\A Directory\\Another");
	AssertInt(FAT_SUCCESS, eResult);

	aszDirectories.Init();
	RecurseFindFatDirectories(&cVolume, "", &aszDirectories);

	sz.Init();
	aszDirectories.Print(&sz);
	aszDirectories.Kill();
	AssertString("\
\\A Directory\\Another\n\
\\A Directory\n", sz.Text());
	sz.Kill();

	eResult = cVolume.Unmount();
	AssertInt(FAT_SUCCESS, eResult);

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32CreateFileEntryAndAllocate(void)
{
	CMemoryDrive			cMemoryDrive;
	CDiskFile				cFile;
	size_t					uiLength;
	void*					pvMemory;
	EFatCode				eResult;
	CFatVolume				cVolume;
	uint64					uiMaxSectorSize;
	CFatFile				cFatFile;
	CChars					sz;

	uiLength = 4 MB;
	cMemoryDrive.Init(uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();

	cMemoryDrive.Erase();
	uiMaxSectorSize = cMemoryDrive.SetMaxSectorForTesting((uiLength / 512) * 1024);

	eResult = FatFormat(FAT_FS_TYPE_FAT32, "Logic", 64, &cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cMemoryDrive.SetMaxSectorForTesting(uiMaxSectorSize);

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\File.txt", FAT_FILE_ACCESS_CREATE | FAT_FILE_ACCESS_WRITE);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(0, cFatFile.GetCurrentSize());

	cVolume.Flush();
	cFatFile.Flush();

	sz.Init();
	PrintFATClusters(&sz, &cVolume, 0, 16);
	AssertString("\
-------------------------------------------------------------------- Sector (32) --------------------------------------------------------------------\n\
    0 -> FFF8,     1 ->  EOC,     2 ->    0,     3 ->  EOC,     4 ->    0,     5 ->    0,     6 ->    0,     7 ->    0,     8 ->    0,     9 ->    0,     a ->    0,     b ->    0,     c ->    0,     d ->    0,     e ->    0,     f ->    0\n", sz.Text());
	sz.Kill();

	cFatFile.AllocateClusters(64 KB);

	cVolume.Flush();
	cFatFile.Flush();

	sz.Init();
	PrintFATClusters(&sz, &cVolume, 0, 16);
	AssertString("\
-------------------------------------------------------------------- Sector (32) --------------------------------------------------------------------\n\
    0 -> FFF8,     1 ->  EOC,     2 ->    0,     3 ->  EOC,     4 ->    5,     5 ->  EOC,     6 ->    0,     7 ->    0,     8 ->    0,     9 ->    0,     a ->    0,     b ->    0,     c ->    0,     d ->    0,     e ->    0,     f ->    0\n", sz.Text());
	sz.Kill();

	cFatFile.AllocateClusters(128 KB);

	cVolume.Flush();
	cFatFile.Flush();

	sz.Init();
	PrintFATClusters(&sz, &cVolume, 0, 16);
	AssertString("\
-------------------------------------------------------------------- Sector (32) --------------------------------------------------------------------\n\
    0 -> FFF8,     1 ->  EOC,     2 ->    0,     3 ->  EOC,     4 ->    5,     5 ->    6,     6 ->    7,     7 ->  EOC,     8 ->    0,     9 ->    0,     a ->    0,     b ->    0,     c ->    0,     d ->    0,     e ->    0,     f ->    0\n", sz.Text());
	sz.Kill();

	cFatFile.Close();

	eResult = cVolume.Unmount();
	AssertInt(FAT_SUCCESS, eResult);

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
char* AllocateAndFillMemory(int iLength)
{
	int		i;
	char*	puiFileData;

	puiFileData = (char*)malloc(iLength);

	char c = 33;
	for (i = 0; i < iLength; i++)
	{
		puiFileData[i] = c;
		if (i % 3 == 2)
		{
			c++;
		}
	}
	return puiFileData;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32CreateDirectoryAfterWrite(void)
{
	CMemoryDrive		cMemoryDrive;
	CDiskFile			cFile;
	filePos				uiLength;
	void*				pvMemory;
	EFatCode			eResult;
	bool				bResult;
	CFatVolume			cVolume;
	char*				puiFileData;
	char*				puiFileData2;
	int					iLength;
	CFatFile			cFatFile;
	uint32				uiBytesRead;
	CChars				sz;
	SFatDirectoryEntry	sFatFileEntry;

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\New File.txt", FAT_FILE_ACCESS_CREATE | FAT_FILE_ACCESS_WRITE);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(0, cFatFile.GetCurrentSize());

	iLength = 4 KB;
	puiFileData = AllocateAndFillMemory(iLength);

	eResult = cFatFile.Write((uint8*)puiFileData, iLength);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(iLength, cFatFile.GetCurrentSize());

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.CreateDirectory("\\A Directory");
	AssertInt(FAT_SUCCESS, eResult);

	sz.Init();
	PrintFATClusters(&sz, &cVolume, 0x240, 0x260);
	AssertString("\
-------------------------------------------------------------------- Sector (602) --------------------------------------------------------------------\n\
  240 ->  EOC,   241 ->  EOC,   242 ->  EOC,   243 ->  EOC,   244 ->  EOC,   245 ->  EOC,   246 ->  EOC,   247 ->  EOC,   248 ->  EOC,   249 ->  24a,   24a ->  EOC,   24b ->  EOC,   24c ->  EOC,   24d ->  EOC,   24e ->  EOC,   24f ->  EOC\n\
  250 ->  EOC,   251 ->  EOC,   252 ->  EOC,   253 ->  EOC,   254 ->  EOC,   255 ->  EOC,   256 ->  EOC,   257 ->  EOC,   258 ->    0,   259 ->    0,   25a ->    0,   25b ->    0,   25c ->    0,   25d ->    0,   25e ->    0,   25f ->    0\n", sz.Text());
	sz.Kill();

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\New File.txt", FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(iLength, cFatFile.GetCurrentSize());

	puiFileData2 = (char*)malloc(iLength);
	uiBytesRead = 0;
	cFatFile.Read((uint8*)puiFileData2, iLength, &uiBytesRead);
	AssertInt(iLength, uiBytesRead);
	AssertMemory(puiFileData, puiFileData2, iLength);

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.CreateDirectory("\\A Directory\\We must go deeper");
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.GetFileEntry("\\A Directory", &sFatFileEntry);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(0x257, cVolume.GetEntryCluster(&sFatFileEntry));

	eResult = cVolume.GetFileEntry("\\A Directory\\We must go deeper", &sFatFileEntry);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(0x258, cVolume.GetEntryCluster(&sFatFileEntry));

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("A Directory\\Depth Charge.txt", FAT_FILE_ACCESS_CREATE | FAT_FILE_ACCESS_WRITE);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(0, cFatFile.GetCurrentSize());

	eResult = cFatFile.Write((uint8*)puiFileData, iLength);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(iLength, cFatFile.GetCurrentSize());

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.GetFileEntry("\\A Directory\\Depth Charge.txt", &sFatFileEntry);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(0x259, cVolume.GetEntryCluster(&sFatFileEntry));

	eResult = cVolume.CreateDirectory("\\A Directory\\Sideways rather is where it is at");
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.GetFileEntry("\\A Directory\\Sideways rather is where it is at", &sFatFileEntry);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(0x25a, cVolume.GetEntryCluster(&sFatFileEntry));

	eResult = cVolume.GetFileEntry("\\A Directory\\We must go deeper", &sFatFileEntry);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(0x258, cVolume.GetEntryCluster(&sFatFileEntry));

	eResult = cVolume.GetFileEntry("\\New File.txt", &sFatFileEntry);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(0x256, cVolume.GetEntryCluster(&sFatFileEntry));

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\A Directory\\Depth Charge.txt", FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(iLength, cFatFile.GetCurrentSize());

	uiBytesRead = 0;
	cFatFile.Read((uint8*)puiFileData2, iLength, &uiBytesRead);
	AssertInt(iLength, uiBytesRead);
	AssertMemory(puiFileData, puiFileData2, iLength);

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\New File.txt", FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(iLength, cFatFile.GetCurrentSize());

	uiBytesRead = 0;
	cFatFile.Read((uint8*)puiFileData2, iLength, &uiBytesRead);
	AssertInt(iLength, uiBytesRead);
	AssertMemory(puiFileData, puiFileData2, iLength);

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	sz.Init();
	PrintFATClusters(&sz, &cVolume, 0x240, 0x260);
	AssertString("\
-------------------------------------------------------------------- Sector (602) --------------------------------------------------------------------\n\
  240 ->  EOC,   241 ->  EOC,   242 ->  EOC,   243 ->  EOC,   244 ->  EOC,   245 ->  EOC,   246 ->  EOC,   247 ->  EOC,   248 ->  EOC,   249 ->  24a,   24a ->  EOC,   24b ->  EOC,   24c ->  EOC,   24d ->  EOC,   24e ->  EOC,   24f ->  EOC\n\
  250 ->  EOC,   251 ->  EOC,   252 ->  EOC,   253 ->  EOC,   254 ->  EOC,   255 ->  EOC,   256 ->  EOC,   257 ->  EOC,   258 ->  EOC,   259 ->  EOC,   25a ->  EOC,   25b ->    0,   25c ->    0,   25d ->    0,   25e ->    0,   25f ->    0\n", sz.Text());
	sz.Kill();

	sz.Init();
	PrintFatFilenames(&sz, "\\A Directory", &cVolume);
	AssertString("\\A Directory\\Depth Charge.txt\n", sz.Text())
	sz.Kill();

	sz.Init();
	PrintFatDirectories(&sz, "\\A Directory", &cVolume);
	AssertString("\
\\A Directory\\We must go deeper\n\
\\A Directory\\Sideways rather is where it is at\n", sz.Text());
	sz.Kill();

	eResult = cVolume.Unmount();
	AssertInt(FAT_SUCCESS, eResult);

	free(puiFileData);
	free(puiFileData2);

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32GreatWrite(void)
{
	CMemoryDrive			cMemoryDrive;
	CDiskFile				cFile;
	filePos					uiLength;
	void*					pvMemory;
	EFatCode				eResult;
	bool					bResult;
	SFatDirectoryEntry*		psFatDirectoryEntry;
	SFatFileSystemQuery		sQuery;
	CFatVolume				cVolume;
	CFatFile				cFatFile;
	char*					puiFileData;
	char*					puiFileData2;
	uint32					uiBytesRead;
	int						iLength;
	CChars					sz;

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\New File.txt", FAT_FILE_ACCESS_CREATE | FAT_FILE_ACCESS_WRITE);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(0, cFatFile.GetCurrentSize());

	sQuery.Init();
	eResult = cVolume.FindFirstFATEntry(NULL, 0, &psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, eResult);
	AssertString("New File.txt", (char*)psFatDirectoryEntry->szName);
	AssertInt(FAT_ATTR_ARCHIVE, psFatDirectoryEntry->uiAttributes);
	sQuery.Kill(cVolume.GetSectorCache());

	iLength = 196 KB;
	puiFileData2 = (char*)malloc(iLength);
	puiFileData = AllocateAndFillMemory(iLength);

	eResult = cFatFile.Write((uint8*)puiFileData, iLength);

	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(196 KB, cFatFile.GetCurrentSize());

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.Unmount();
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\New File.txt", FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(196 KB , cFatFile.GetCurrentSize());

	memset(puiFileData2, 0, iLength);
	eResult = cFatFile.Read((uint8*)puiFileData2, iLength, &uiBytesRead);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(iLength, uiBytesRead);
	AssertInt(0, memcmp(puiFileData, puiFileData2, iLength));

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cFatFile.Open("\\New File.txt", FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);

	memset(puiFileData2, 0, iLength);
	iLength = 196 KB - 64 KB - 1024;
	cFatFile.Seek(64 KB + 1024, FAT_SEEK_START);
	eResult = cFatFile.Read((uint8*)puiFileData2, iLength, &uiBytesRead);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(iLength, uiBytesRead);
	AssertMemory(&(((uint8*)puiFileData)[64 KB + 1024]), puiFileData2, iLength);

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	iLength = 196 KB;
	eResult = cVolume.CreateDirectory("\\A Directory");
	AssertInt(FAT_SUCCESS, eResult);
	eResult = cVolume.CreateDirectory("\\A Directory\\Another");
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\A Directory\\Another\\New File Number Two.txt", FAT_FILE_ACCESS_CREATE | FAT_FILE_ACCESS_WRITE);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(0, cFatFile.GetCurrentSize());

	eResult = cFatFile.Write((uint8*)puiFileData, iLength);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(196 KB, cFatFile.GetCurrentSize());

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.Unmount();
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	sz.Init();
	PrintInterestingFATClusters(&sz, &cVolume);
	AssertString("\
-------------------------------------------------------------------- Sector (602) --------------------------------------------------------------------\n\
  200 ->  EOC,   201 ->  EOC,   202 ->  EOC,   203 ->  EOC,   204 ->  EOC,   205 ->  EOC,   206 ->  EOC,   207 ->  EOC,   208 ->  EOC,   209 ->  EOC,   20a ->  EOC,   20b ->  EOC,   20c ->  EOC,   20d ->  EOC,   20e ->  EOC,   20f ->  EOC\n\
  210 ->  EOC,   211 ->  EOC,   212 ->  EOC,   213 ->  EOC,   214 ->  EOC,   215 ->  EOC,   216 ->  EOC,   217 ->  EOC,   218 ->  EOC,   219 ->  EOC,   21a ->  EOC,   21b ->  EOC,   21c ->  EOC,   21d ->  EOC,   21e ->  EOC,   21f ->  EOC\n\
  220 ->  EOC,   221 ->  EOC,   222 ->  EOC,   223 ->  EOC,   224 ->  EOC,   225 ->  EOC,   226 ->  EOC,   227 ->  EOC,   228 ->  EOC,   229 ->  EOC,   22a ->  EOC,   22b ->  EOC,   22c ->  EOC,   22d ->  EOC,   22e ->  EOC,   22f ->  EOC\n\
  230 ->  EOC,   231 ->  EOC,   232 ->  EOC,   233 ->  EOC,   234 ->  EOC,   235 ->  EOC,   236 ->  EOC,   237 ->  EOC,   238 ->  EOC,   239 ->  EOC,   23a ->  EOC,   23b ->  EOC,   23c ->  EOC,   23d ->  EOC,   23e ->  EOC,   23f ->  EOC\n\
  240 ->  EOC,   241 ->  EOC,   242 ->  EOC,   243 ->  EOC,   244 ->  EOC,   245 ->  EOC,   246 ->  EOC,   247 ->  EOC,   248 ->  EOC,   249 ->  24a,   24a ->  EOC,   24b ->  EOC,   24c ->  EOC,   24d ->  EOC,   24e ->  EOC,   24f ->  EOC\n\
  250 ->  EOC,   251 ->  EOC,   252 ->  EOC,   253 ->  EOC,   254 ->  EOC,   255 ->  EOC,   256 ->  257,   257 ->  258,   258 ->  259,   259 ->  25a,   25a ->  25b,   25b ->  25c,   25c ->  EOC,   25d ->  EOC,   25e ->  EOC,   25f ->  260\n\
  260 ->  261,   261 ->  262,   262 ->  263,   263 ->  264,   264 ->  265,   265 ->  EOC,   266 ->    0,   267 ->    0,   268 ->    0,   269 ->    0,   26a ->    0,   26b ->    0,   26c ->    0,   26d ->    0,   26e ->    0,   26f ->    0\n\
  270 ->    0,   271 ->    0,   272 ->    0,   273 ->    0,   274 ->    0,   275 ->    0,   276 ->    0,   277 ->    0,   278 ->    0,   279 ->    0,   27a ->    0,   27b ->    0,   27c ->    0,   27d ->    0,   27e ->    0,   27f ->    0\n", sz.Text());
	sz.Kill();

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\New File.txt", FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(196 KB, cFatFile.GetCurrentSize());

	memset(puiFileData2, 0, iLength);
	eResult = cFatFile.Read((uint8*)puiFileData2, iLength, &uiBytesRead);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(iLength, uiBytesRead);
	AssertInt(0, memcmp(puiFileData, puiFileData2, iLength));

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);


	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\A Directory\\Another\\New File Number Two.txt", FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(196 KB, cFatFile.GetCurrentSize());

	memset(puiFileData2, 0, iLength);
	eResult = cFatFile.Read((uint8*)puiFileData2, iLength, &uiBytesRead);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(iLength, uiBytesRead);
	AssertInt(0, memcmp(puiFileData, puiFileData2, iLength));

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	free(puiFileData);
	free(puiFileData2);

	eResult = cVolume.Unmount();
	AssertInt(FAT_SUCCESS, eResult);

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32MultipleSmallReads(void)
{
	CMemoryDrive			cMemoryDrive;
	CDiskFile				cFile;
	filePos					uiLength;
	void*					pvMemory;
	SFatDirectoryEntry		sFatFileEntry;
	EFatCode				eResult;
	CFatFile				cFatFile;
	bool					bResult;
	uint32					uiBytesRead;
	char					auiFileData[44 KB];
	char					auiExpectedData[44 KB];
	CFatVolume				cVolume;
	uint32					uiFileSize;
	uint32					uiBytesToRead;
	uint8*					puiFileData;
	int						i;

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.GetFileEntry("\\Pico\\LCDBusReader\\src\\SDCard.cpp", &sFatFileEntry);
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open(&sFatFileEntry, FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);

	uiBytesToRead = 1;
	puiFileData = (uint8*)auiFileData;
	uiFileSize = cFatFile.GetCurrentSize();
	for (i = 0;; i++)
	{
		eResult = cFatFile.Read(puiFileData, uiBytesToRead, &uiBytesRead);
		AssertInt(FAT_SUCCESS, eResult);
		AssertInt(uiBytesToRead, uiBytesRead);

		uiFileSize -= uiBytesToRead;
		if (uiFileSize == 0)
		{
			break;
		}
		puiFileData += uiBytesRead;

		uiBytesToRead++;
		if (uiBytesToRead > uiFileSize)
		{
			uiBytesToRead = uiFileSize;
		}
	}
	auiFileData[44000] = '\0';

	cFatFile.Close();

	cFile.Init("Input\\Fat32\\SDCard.cpp");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	AssertInt(44000, (int)uiLength);
	cFile.Read(auiExpectedData, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	AssertMemory(auiExpectedData, auiFileData, (int)uiLength);

	cVolume.Unmount();

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32Seek(void)
{
	CMemoryDrive	cMemoryDrive;
	CDiskFile		cFile;
	filePos			uiLength;
	void*			pvMemory;
	EFatCode		eResult;
	CFatFile		cFatFile;
	bool			bResult;
	CFatVolume		cVolume;
	int				i;

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\Pico\\LCDBusReader\\src\\SDCard.cpp", FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);

	bool bAllSuccess = true;
	for (i = 0; i < (int)cFatFile.GetCurrentSize(); i++)
	{
		eResult = cFatFile.Seek(i, FAT_SEEK_START);
		if (eResult != FAT_SUCCESS)
		{
			bAllSuccess = false;
			break;
		}
	}
	AssertTrue(bAllSuccess);

	cFatFile.Close();

	cVolume.Unmount();
	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32WriteAndSeek(void)
{
	CMemoryDrive	cMemoryDrive;
	CDiskFile		cFile;
	filePos			uiLength;
	void*			pvMemory;
	EFatCode		eResult;
	CFatFile		cFatFile;
	bool			bResult;
	CFatVolume		cVolume;
	int				i;
	char*			szSource;
	char*			szRead;
	uint32			uiBytesRead;

	szSource = AllocateStringBuffer(196 KB);

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\File.txt", FAT_FILE_ACCESS_CREATE | FAT_FILE_ACCESS_OVERWRITE | FAT_FILE_ACCESS_WRITE | FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cFatFile.Write((uint8*)szSource, 196 KB);
	AssertInt(FAT_SUCCESS, eResult);

	bool bAllSuccess = true;
	for (i = 0; i < (int)cFatFile.GetCurrentSize(); i++)
	{
		eResult = cFatFile.Seek(i, FAT_SEEK_START);
		if (eResult != FAT_SUCCESS)
		{
			bAllSuccess = false;
			break;
		}
	}
	AssertTrue(bAllSuccess);

	szRead = (char*)malloc(196 KB);
	eResult = cFatFile.Seek(0, FAT_SEEK_START);
	AssertInt(FAT_SUCCESS, eResult);
	eResult = cFatFile.Read((uint8*)szRead, 196 KB, &uiBytesRead);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(196 KB, uiBytesRead);
	AssertString(szSource, szRead);

	bAllSuccess = true;
	for (i = 1; i < 32769 + 1024; i += 100)
	{
		eResult = cFatFile.Seek(i, FAT_SEEK_START);
		if (eResult != FAT_SUCCESS)
		{
			AssertInt(FAT_SUCCESS, eResult);
			bAllSuccess = false;
			break;
		}
		eResult = cFatFile.Read((uint8*)szRead, 196 KB - i, &uiBytesRead);
		if (eResult != FAT_SUCCESS)
		{
			AssertInt(FAT_SUCCESS, eResult);
			bAllSuccess = false;
			break;
		}
		
		if (uiBytesRead != 196 KB - i)
		{
			AssertInt(196 KB - i, uiBytesRead);
			bAllSuccess = false;
			break;
		}
		
		AssertString(&szSource[i], szRead);
	}
	AssertTrue(bAllSuccess);

	cFatFile.Close();

	free(szRead);
	free(szSource);
	cVolume.Unmount();
	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32SeekWriteAndRead1(void)
{
	CMemoryDrive	cMemoryDrive;
	CDiskFile		cFile;
	filePos			uiLength;
	void*			pvMemory;
	EFatCode		eResult;
	CFatFile		cFatFile;
	bool			bResult;
	CFatVolume		cVolume;
	char*			szSource;

	szSource = AllocateStringBuffer(64 KB);

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\File.txt", FAT_FILE_ACCESS_CREATE | FAT_FILE_ACCESS_OVERWRITE | FAT_FILE_ACCESS_WRITE | FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cFatFile.Write((uint8*)szSource, 65538);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cFatFile.Seek(65535, FAT_SEEK_START);
	eResult = cFatFile.Write((uint8*)szSource, 3);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cFatFile.Seek(65536, FAT_SEEK_START);
	eResult = cFatFile.Write((uint8*)szSource, 1);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	cVolume.Unmount();

	cMemoryDrive.Kill();

	free(szSource);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32SeekWriteAndRead2(void)
{
	CMemoryDrive	cMemoryDrive;
	CDiskFile		cFile;
	filePos			uiLength;
	void*			pvMemory;
	EFatCode		eResult;
	CFatFile		cFatFile;
	bool			bResult;
	CFatVolume		cVolume;
	int				i;
	char			szThree[4];
	char			c;
	char			szDest[8 KB];
	uint32			uiBytesRead;
	bool			bAllSuccess;
	
	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\File.txt", FAT_FILE_ACCESS_CREATE | FAT_FILE_ACCESS_OVERWRITE | FAT_FILE_ACCESS_WRITE | FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);

	bAllSuccess = true;
	c = 'A';
	for (i = 0; i < 196 KB; i++)
	{
		szThree[0] = szThree[1] = szThree[2] = c;
		c++;
		if (c == 127)
		{
			c = 'A';
		}
		if ((c == ' ') || (c == '\\') || (c == '"'))
		{
			c++;
		}

		eResult = cFatFile.Write((uint8*)szThree, 3);
		if (eResult != FAT_SUCCESS)
		{
			AssertInt(FAT_SUCCESS, eResult);
			bAllSuccess = false;
			break;
		}


		eResult = cFatFile.Seek(i + 1, FAT_SEEK_START);
		if (eResult != FAT_SUCCESS)
		{
			AssertInt(FAT_SUCCESS, eResult);
			bAllSuccess = false;
			break;
		}

	}
	AssertTrue(bAllSuccess);

	memset(szDest, 0, 8 KB);
	eResult = cFatFile.Seek(0, FAT_SEEK_START);
	AssertInt(FAT_SUCCESS, eResult);
	eResult = cFatFile.Read((uint8*)szDest, 8 KB - 1, &uiBytesRead);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	cVolume.Unmount();

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32SeekWriteAndRead3(void)
{
	CMemoryDrive	cMemoryDrive;
	CDiskFile		cFile;
	filePos			uiLength;
	void*			pvMemory;
	EFatCode		eResult;
	CFatFile		cFatFile;
	bool			bResult;
	CFatVolume		cVolume;
	int				i;
	char			szThree[4];
	char			c;
	char			szDest[8 KB];
	uint32			uiBytesRead;
	bool			bAllSuccess;

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cVolume.CreateDirectory("\\Directory");

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\Directory\\File.txt", FAT_FILE_ACCESS_CREATE | FAT_FILE_ACCESS_OVERWRITE | FAT_FILE_ACCESS_WRITE | FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);
	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\Directory\\File.txt", FAT_FILE_ACCESS_WRITE | FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(cFatFile.GetCurrentSize(), 0);

	bAllSuccess = true;
	c = 'A';
	for (i = 0; i < 196 KB; i++)
	{
		szThree[0] = szThree[1] = szThree[2] = c;
		c++;
		if (c == 127)
		{
			c = 'A';
		}
		if ((c == ' ') || (c == '\\') || (c == '"'))
		{
			c++;
		}

		eResult = cFatFile.Write((uint8*)szThree, 3);
		if (eResult != FAT_SUCCESS)
		{
			AssertInt(FAT_SUCCESS, eResult);
			bAllSuccess = false;
			break;
		}


		eResult = cFatFile.Seek(i + 1, FAT_SEEK_START);
		if (eResult != FAT_SUCCESS)
		{
			AssertInt(FAT_SUCCESS, eResult);
			bAllSuccess = false;
			break;
		}

	}
	AssertTrue(bAllSuccess);

	memset(szDest, 0, 8 KB);
	eResult = cFatFile.Seek(0, FAT_SEEK_START);
	AssertInt(FAT_SUCCESS, eResult);
	eResult = cFatFile.Read((uint8*)szDest, 8 KB - 1, &uiBytesRead);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	cVolume.Unmount();

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRenameSameLength(void)
{
	CMemoryDrive	cMemoryDrive;
	CDiskFile		cFile;
	filePos			uiLength;
	void* pvMemory;
	EFatCode		eResult;
	CFatFile		cFatFile;
	bool			bResult;
	CFatVolume		cVolume;
	uint32			uiBytesRead;
	char			auiFileData[13];

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.RenameFile("\\Document.txt", "\\Manequin.txt");
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\Manequin.txt", FAT_ATTR_READ_ONLY);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(12, cFatFile.GetCurrentSize());
	eResult = cFatFile.Read((uint8*)auiFileData, cFatFile.GetCurrentSize(), &uiBytesRead);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(12, uiBytesRead);
	auiFileData[12] = '\0';
	AssertString("Mostly Empty", auiFileData);
	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	cVolume.Unmount();

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRenameShortToLong(void)
{
	CMemoryDrive	cMemoryDrive;
	CDiskFile		cFile;
	filePos			uiLength;
	void*			pvMemory;
	EFatCode		eResult;
	CFatFile		cFatFile;
	bool			bResult;
	CFatVolume		cVolume;
	uint32			uiBytesRead;
	char			auiFileData[13];
	CChars			sz;

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	sz.Init();
	PrintRootFatFilenames(&sz, &cVolume);
	sz.Dump();
	sz.Kill();

	eResult = cVolume.RenameFile("\\Document.txt", "\\Dashwood contempt on mr unlocked resolved provided of of - Stanhill wondered it it welcomed oh - Hundred no prudent he however smiling at an offence - If earnestly extremity he he propriety something admitting convinced ye - Pleasant in to although as.if");
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\Dashwood contempt on mr unlocked resolved provided of of - Stanhill wondered it it welcomed oh - Hundred no prudent he however smiling at an offence - If earnestly extremity he he propriety something admitting convinced ye - Pleasant in to although as.if", FAT_ATTR_READ_ONLY);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(12, cFatFile.GetCurrentSize());
	eResult = cFatFile.Read((uint8*)auiFileData, cFatFile.GetCurrentSize(), &uiBytesRead);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(12, uiBytesRead);
	auiFileData[12] = '\0';
	AssertString("Mostly Empty", auiFileData);
	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	cVolume.Unmount();

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCreateFileRenameFileCreateFile(void)
{
	CMemoryDrive	cMemoryDrive;
	CDiskFile		cFile;
	filePos			uiLength;
	void* pvMemory;
	EFatCode		eResult;
	CFatFile		cFatFile;
	bool			bResult;
	CFatVolume		cVolume;
	uint32			uiBytesRead;
	char			auiFileData[13];
	CChars			sz;

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\File1.txt", FAT_FILE_ACCESS_CREATE | FAT_FILE_ACCESS_WRITE);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(0, cFatFile.GetCurrentSize());
	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	sz.Init();
	PrintRootFatFilenames(&sz, &cVolume);
	AssertString("\\File1.txt\n\
\\Document.txt\n", sz.Text());
	sz.Kill();

	eResult = cVolume.RenameFile("\\Document.txt", "\\Dashwood contempt on mr unlocked resolved provided of of - Stanhill wondered it it welcomed oh - Hundred no prudent he however smiling at an offence - If earnestly extremity he he propriety something admitting convinced ye - Pleasant in to although as.if");
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\Dashwood contempt on mr unlocked resolved provided of of - Stanhill wondered it it welcomed oh - Hundred no prudent he however smiling at an offence - If earnestly extremity he he propriety something admitting convinced ye - Pleasant in to although as.if", FAT_ATTR_READ_ONLY);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(12, cFatFile.GetCurrentSize());
	eResult = cFatFile.Read((uint8*)auiFileData, cFatFile.GetCurrentSize(), &uiBytesRead);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(12, uiBytesRead);
	auiFileData[12] = '\0';
	AssertString("Mostly Empty", auiFileData);
	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\File2.txt", FAT_FILE_ACCESS_CREATE | FAT_FILE_ACCESS_WRITE);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(0, cFatFile.GetCurrentSize());
	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	sz.Init();
	PrintRootFatFilenames(&sz, &cVolume);
	AssertString("\\File1.txt\n\
\\File2.txt\n\
\\Dashwood contempt on mr unlocked resolved provided of of - Stanhill wondered it it welcomed oh - Hundred no prudent he however smiling at an offence - If earnestly extremity he he propriety something admitting convinced ye - Pleasant in to although as.if\n", sz.Text());
	sz.Kill();

	sz.Init();
	PrintRootDirectoryEntries(&sz, &cVolume, false);
	AssertStringApproximate("\
---------------------------------------\n\
Sequence:     66\n\
Long name[1]:  Info\n\
Long name[2]: rmatio\n\
Long name[3]: n\n\
Cluster:      0\n\
Attributes:   LONG_NAME\n\
Checksum:     114\n\
---------------------------------------\n\
Sequence:     1\n\
Long name[1]: Syste\n\
Long name[2]: m Volu\n\
Long name[3]: me\n\
Cluster:      0\n\
Attributes:   LONG_NAME\n\
Checksum:     114\n\
---------------------------------------\n\
Short name: SYSTEM~1\n\
Cluster:    3\n\
Size:       0\n\
Attributes: HIDDEN, SYSTEM, DIRECTORY\n\
---------------------------------------\n\
Sequence:     65\n\
Long name[1]: File1\n\
Long name[2]: .txt\n\
Long name[3]: ÿÿ\n\
Cluster:      0\n\
Attributes:   LONG_NAME\n\
Checksum:     225\n\
---------------------------------------\n\
Short name: FILE1~0.TXT\n\
Cluster:    0\n\
Size:       0\n\
Attributes: ARCHIVE\n\
---------------------------------------\n\
Sequence:     65\n\
Long name[1]: File2\n\
Long name[2]: .txt\n\
Long name[3]: ÿÿ\n\
Cluster:      0\n\
Attributes:   LONG_NAME\n\
Checksum:     221\n\
---------------------------------------\n\
Short name: FILE2~0.TXT\n\
Cluster:    0\n\
Size:       0\n\
Attributes: ARCHIVE\n\
---------------------------------------\n\
Sequence:     65\n\
Long name[1]: Pico\n\
Long name[2]: ÿÿÿÿÿÿ\n\
Long name[3]: ÿÿ\n\
Cluster:      0\n\
Attributes:   LONG_NAME\n\
Checksum:     56\n\
---------------------------------------\n\
Short name: PICO\n\
Cluster:    6\n\
Size:       0\n\
Attributes: DIRECTORY\n\
---------------------------------------\n\
Sequence:     84\n\
Long name[1]: h as.\n\
Long name[2]: if\n\
Long name[3]: ÿÿ\n\
Cluster:      0\n\
Attributes:   LONG_NAME\n\
Checksum:     223\n\
---------------------------------------\n\
Sequence:     19\n\
Long name[1]: in to\n\
Long name[2]:  altho\n\
Long name[3]: ug\n\
Cluster:      0\n\
Attributes:   LONG_NAME\n\
Checksum:     223\n\
---------------------------------------\n\
Sequence:     18\n\
Long name[1]: e - P\n\
Long name[2]: leasan\n\
Long name[3]: t \n\
Cluster:      0\n\
Attributes:   LONG_NAME\n\
Checksum:     223\n\
---------------------------------------\n\
Sequence:     17\n\
Long name[1]: g con\n\
Long name[2]: vinced\n\
Long name[3]:  y\n\
Cluster:      0\n\
Attributes:   LONG_NAME\n\
Checksum:     223\n\
---------------------------------------\n\
Sequence:     16\n\
Long name[1]: hing \n\
Long name[2]: admitt\n\
Long name[3]: in\n\
Cluster:      0\n\
Attributes:   LONG_NAME\n\
Checksum:     223\n\
---------------------------------------\n\
Sequence:     15\n\
Long name[1]: oprie\n\
Long name[2]: ty som\n\
Long name[3]: et\n\
Cluster:      0\n\
Attributes:   LONG_NAME\n\
Checksum:     223\n\
---------------------------------------\n\
Sequence:     14\n\
Long name[1]: mity \n\
Long name[2]: he he \n\
Long name[3]: pr\n\
Cluster:      0\n\
Attributes:   LONG_NAME\n\
Checksum:     223\n\
---------------------------------------\n\
Sequence:     13\n\
Long name[1]: rnest\n\
Long name[2]: ly ext\n\
Long name[3]: re\n\
Cluster:      0\n\
Attributes:   LONG_NAME\n\
Checksum:     223\n\
---------------------------------------\n\
Sequence:     12\n\
Long name[1]: fence\n\
Long name[2]:  - If \n\
Long name[3]: ea\n\
Cluster:      0\n\
Attributes:   LONG_NAME\n\
Checksum:     223\n\
---------------------------------------\n\
Sequence:     11\n\
Long name[1]: ling \n\
Long name[2]: at an \n\
Long name[3]: of\n\
Cluster:      0\n\
Attributes:   LONG_NAME\n\
Checksum:     223\n\
---------------------------------------\n\
Sequence:     10\n\
Long name[1]: e how\n\
Long name[2]: ever s\n\
Long name[3]: mi\n\
Cluster:      0\n\
Attributes:   LONG_NAME\n\
Checksum:     223\n\
---------------------------------------\n\
Sequence:     9\n\
Long name[1]:  no p\n\
Long name[2]: rudent\n\
Long name[3]:  h\n\
Cluster:      0\n\
Attributes:   LONG_NAME\n\
Checksum:     223\n\
---------------------------------------\n\
Sequence:     8\n\
Long name[1]:  oh -\n\
Long name[2]:  Hundr\n\
Long name[3]: ed\n\
Cluster:      0\n\
Attributes:   LONG_NAME\n\
Checksum:     223\n\
---------------------------------------\n\
Sequence:     7\n\
Long name[1]: t it \n\
Long name[2]: welcom\n\
Long name[3]: ed\n\
Cluster:      0\n\
Attributes:   LONG_NAME\n\
Checksum:     223\n\
---------------------------------------\n\
Sequence:     6\n\
Long name[1]: ll wo\n\
Long name[2]: ndered\n\
Long name[3]:  i\n\
Cluster:      0\n\
Attributes:   LONG_NAME\n\
Checksum:     223\n\
---------------------------------------\n\
Sequence:     5\n\
Long name[1]: f of \n\
Long name[2]: - Stan\n\
Long name[3]: hi\n\
Cluster:      0\n\
Attributes:   LONG_NAME\n\
Checksum:     223\n\
---------------------------------------\n\
Sequence:     4\n\
Long name[1]: ed pr\n\
Long name[2]: ovided\n\
Long name[3]:  o\n\
Cluster:      0\n\
Attributes:   LONG_NAME\n\
Checksum:     223\n\
---------------------------------------\n\
Sequence:     3\n\
Long name[1]: locke\n\
Long name[2]: d reso\n\
Long name[3]: lv\n\
Cluster:      0\n\
Attributes:   LONG_NAME\n\
Checksum:     223\n\
---------------------------------------\n\
Sequence:     2\n\
Long name[1]: empt \n\
Long name[2]: on mr \n\
Long name[3]: un\n\
Cluster:      0\n\
Attributes:   LONG_NAME\n\
Checksum:     223\n\
---------------------------------------\n\
Sequence:     1\n\
Long name[1]: Dashw\n\
Long name[2]: ood co\n\
Long name[3]: nt\n\
Cluster:      0\n\
Attributes:   LONG_NAME\n\
Checksum:     223\n\
---------------------------------------\n\
Short name: DASHWO~0.IF\n\
Cluster:    597\n\
Size:       12\n\
Attributes: ARCHIVE\n", sz.Text());
	sz.Kill();

	cVolume.Unmount();

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32(void)
{
	TypeConverterInit();
	WordsInit();
	BeginTests();

	TestFat32ReadSpecific();
	TestFat32ReadDirectoryTree();
	TestFat32Format();
	TestFat32CreateFileEntries();
	TestFat32OpenWriteMode();
	TestFat32Write();
	TestFat32CreateDirectory();
	TestFat32FormatAndCreateDirectory();
	TestFat32CreateFileEntryAndAllocate();
	TestFat32CreateDirectoryAfterWrite();
	TestFat32GreatWrite();
	TestFat32MultipleSmallReads();
	TestFat32Seek();
	TestFat32WriteAndSeek();
	TestFat32SeekWriteAndRead1();
	TestFat32SeekWriteAndRead2();
	TestFat32SeekWriteAndRead3();
	TestRenameSameLength();
	TestRenameShortToLong();
	TestCreateFileRenameFileCreateFile();

	TestStatistics();
	WordsKill();
	TypeConverterKill();
}

