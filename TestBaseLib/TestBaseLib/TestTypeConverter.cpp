#include "BaseLib/TypeConverter.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTypeConverterFloat64ScaleTruncateToInt8(void)
{
	int8	i8;
	float64	f64;

	f64 = -2;		gcTypeConverter.Do(PT_int8, &i8, PT_float64, &f64);
	AssertInt(-128, i8);

	f64 = -1.5;		gcTypeConverter.Do(PT_int8, &i8, PT_float64, &f64);
	AssertInt(-128, i8);

	f64 = -1;		gcTypeConverter.Do(PT_int8, &i8, PT_float64, &f64);
	AssertInt(-128, i8);

	f64 = -0.999;	gcTypeConverter.Do(PT_int8, &i8, PT_float64, &f64);
	AssertInt(-127, i8);

	f64 = -0.9922;	gcTypeConverter.Do(PT_int8, &i8, PT_float64, &f64);
	AssertInt(-127, i8);

	f64 = -0.9921;	gcTypeConverter.Do(PT_int8, &i8, PT_float64, &f64);
	AssertInt(-126, i8);

	f64 = -0.99;	gcTypeConverter.Do(PT_int8, &i8, PT_float64, &f64);
	AssertInt(-126, i8);

	f64 = -0.5;		gcTypeConverter.Do(PT_int8, &i8, PT_float64, &f64);
	AssertInt(-64, i8);

	f64 = -0.01;	gcTypeConverter.Do(PT_int8, &i8, PT_float64, &f64);
	AssertInt(-1, i8);

	f64 = -0.001;	gcTypeConverter.Do(PT_int8, &i8, PT_float64, &f64);
	AssertInt(0, i8);

	f64 = -0.0;		gcTypeConverter.Do(PT_int8, &i8, PT_float64, &f64);
	AssertInt(0, i8);


	f64 = 2;		gcTypeConverter.Do(PT_int8, &i8, PT_float64, &f64);
	AssertInt(127, i8);

	f64 = 1.5;		gcTypeConverter.Do(PT_int8, &i8, PT_float64, &f64);
	AssertInt(127, i8);

	f64 = -1;		gcTypeConverter.Do(PT_int8, &i8, PT_float64, &f64);
	AssertInt(-128, i8);

	f64 = 0.999;	gcTypeConverter.Do(PT_int8, &i8, PT_float64, &f64);
	AssertInt(126, i8);

	f64 = 0.9922;	gcTypeConverter.Do(PT_int8, &i8, PT_float64, &f64);
	AssertInt(126, i8);

	f64 = 0.9921;	gcTypeConverter.Do(PT_int8, &i8, PT_float64, &f64);
	AssertInt(125, i8);

	f64 = 0.9842;	gcTypeConverter.Do(PT_int8, &i8, PT_float64, &f64);
	AssertInt(124, i8);

	f64 = 0.5;		gcTypeConverter.Do(PT_int8, &i8, PT_float64, &f64);
	AssertInt(63, i8);

	f64 = 0.01;		gcTypeConverter.Do(PT_int8, &i8, PT_float64, &f64);
	AssertInt(1, i8);

	f64 = 0.001;	gcTypeConverter.Do(PT_int8, &i8, PT_float64, &f64);
	AssertInt(0, i8);

	f64 = 0.0;		gcTypeConverter.Do(PT_int8, &i8, PT_float64, &f64);
	AssertInt(0, i8);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTypeConverterFloat32ScaleTruncateToInt8(void)
{
	int8	i8;
	float32	f32;

	f32 = -2;		gcTypeConverter.Do(PT_int8, &i8, PT_float32, &f32);
	AssertInt(-128, i8);

	f32 = -1.5;		gcTypeConverter.Do(PT_int8, &i8, PT_float32, &f32);
	AssertInt(-128, i8);

	f32 = -1;		gcTypeConverter.Do(PT_int8, &i8, PT_float32, &f32);
	AssertInt(-128, i8);

	f32 = -0.999;	gcTypeConverter.Do(PT_int8, &i8, PT_float32, &f32);
	AssertInt(-127, i8);

	f32 = -0.9922;	gcTypeConverter.Do(PT_int8, &i8, PT_float32, &f32);
	AssertInt(-127, i8);

	f32 = -0.9921;	gcTypeConverter.Do(PT_int8, &i8, PT_float32, &f32);
	AssertInt(-126, i8);

	f32 = -0.99;	gcTypeConverter.Do(PT_int8, &i8, PT_float32, &f32);
	AssertInt(-126, i8);

	f32 = -0.5;		gcTypeConverter.Do(PT_int8, &i8, PT_float32, &f32);
	AssertInt(-64, i8);

	f32 = -0.75;	gcTypeConverter.Do(PT_int8, &i8, PT_float32, &f32);
	AssertInt(-96, i8);

	f32 = -0.01;	gcTypeConverter.Do(PT_int8, &i8, PT_float32, &f32);
	AssertInt(-1, i8);

	f32 = -0.001;	gcTypeConverter.Do(PT_int8, &i8, PT_float32, &f32);
	AssertInt(0, i8);

	f32 = -0.0;		gcTypeConverter.Do(PT_int8, &i8, PT_float32, &f32);
	AssertInt(0, i8);

	f32 = 0.75;		gcTypeConverter.Do(PT_int8, &i8, PT_float32, &f32);
	AssertInt(95, i8);

	f32 = 2;		gcTypeConverter.Do(PT_int8, &i8, PT_float32, &f32);
	AssertInt(127, i8);

	f32 = 1.5;		gcTypeConverter.Do(PT_int8, &i8, PT_float32, &f32);
	AssertInt(127, i8);

	f32 = -1;		gcTypeConverter.Do(PT_int8, &i8, PT_float32, &f32);
	AssertInt(-128, i8);

	f32 = 0.999;	gcTypeConverter.Do(PT_int8, &i8, PT_float32, &f32);
	AssertInt(126, i8);

	f32 = 0.9922;	gcTypeConverter.Do(PT_int8, &i8, PT_float32, &f32);
	AssertInt(126, i8);

	f32 = 0.9921;	gcTypeConverter.Do(PT_int8, &i8, PT_float32, &f32);
	AssertInt(125, i8);

	f32 = 0.9842;	gcTypeConverter.Do(PT_int8, &i8, PT_float32, &f32);
	AssertInt(124, i8);

	f32 = 0.5;		gcTypeConverter.Do(PT_int8, &i8, PT_float32, &f32);
	AssertInt(63, i8);

	f32 = 0.01;		gcTypeConverter.Do(PT_int8, &i8, PT_float32, &f32);
	AssertInt(1, i8);

	f32 = 0.001;	gcTypeConverter.Do(PT_int8, &i8, PT_float32, &f32);
	AssertInt(0, i8);

	f32 = 0.0;		gcTypeConverter.Do(PT_int8, &i8, PT_float32, &f32);
	AssertInt(0, i8);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTypeConverterUInt16ScaleTruncateToUInt8(void)
{
	uint8	ui8;
	uint16	ui16;

	ui16 = 0;		gcTypeConverter.Do(PT_uint8, &ui8, PT_uint16, &ui16);
	AssertInt(0, ui8);

	ui16 = 0xfeff;	gcTypeConverter.Do(PT_uint8, &ui8, PT_uint16, &ui16);
	AssertInt(0xfe, ui8);

	ui16 = 0xfe00;	gcTypeConverter.Do(PT_uint8, &ui8, PT_uint16, &ui16);
	AssertInt(0xfe, ui8);

	ui16 = 0x100;	gcTypeConverter.Do(PT_uint8, &ui8, PT_uint16, &ui16);
	AssertInt(0x1, ui8);

	ui16 = 0x0ff;	gcTypeConverter.Do(PT_uint8, &ui8, PT_uint16, &ui16);
	AssertInt(0x0, ui8);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTypeConverterUInt16ScaleTruncateToInt8(void)
{
	int8	i8;
	uint16	ui16;

	ui16 = 0;		gcTypeConverter.Do(PT_int8, &i8, PT_uint16, &ui16);
	AssertInt(0, i8);

	ui16 = 0xffff;	gcTypeConverter.Do(PT_int8, &i8, PT_uint16, &ui16);
	AssertInt(0x7f, i8);

	ui16 = 0xff00;	gcTypeConverter.Do(PT_int8, &i8, PT_uint16, &ui16);
	AssertInt(0x7f, i8);

	ui16 = 0xfeff;	gcTypeConverter.Do(PT_int8, &i8, PT_uint16, &ui16);
	AssertInt(0x7f, i8);

	ui16 = 0xfe00;	gcTypeConverter.Do(PT_int8, &i8, PT_uint16, &ui16);
	AssertInt(0x7f, i8);

	ui16 = 0xfdff;	gcTypeConverter.Do(PT_int8, &i8, PT_uint16, &ui16);
	AssertInt(0x7e, i8);

	ui16 = 0xfc00;	gcTypeConverter.Do(PT_int8, &i8, PT_uint16, &ui16);
	AssertInt(0x7e, i8);

	ui16 = 0x200;	gcTypeConverter.Do(PT_int8, &i8, PT_uint16, &ui16);
	AssertInt(0x1, i8);

	ui16 = 0x1ff;	gcTypeConverter.Do(PT_int8, &i8, PT_uint16, &ui16);
	AssertInt(0x0, i8);

	ui16 = 0x100;	gcTypeConverter.Do(PT_int8, &i8, PT_uint16, &ui16);
	AssertInt(0x0, i8);

	ui16 = 0x0ff;	gcTypeConverter.Do(PT_int8, &i8, PT_uint16, &ui16);
	AssertInt(0x0, i8);

	ui16 = 0x0;	gcTypeConverter.Do(PT_int8, &i8, PT_uint16, &ui16);
	AssertInt(0x0, i8);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTypeConverterInt16ScaleTruncateToUInt8(void)
{
	uint8	ui8;
	int16	i16;

	i16 = 0;		gcTypeConverter.Do(PT_uint8, &ui8, PT_int16, &i16);
	AssertInt(0, ui8);

	i16 = 0x7fff;	gcTypeConverter.Do(PT_uint8, &ui8, PT_int16, &i16);
	AssertInt(0xff, ui8);

	i16 = 0x7f80;	gcTypeConverter.Do(PT_uint8, &ui8, PT_int16, &i16);
	AssertInt(0xff, ui8);

	i16 = 0x7f7f;	gcTypeConverter.Do(PT_uint8, &ui8, PT_int16, &i16);
	AssertInt(0xfe, ui8);

	i16 = 0x7f00;	gcTypeConverter.Do(PT_uint8, &ui8, PT_int16, &i16);
	AssertInt(0xfe, ui8);

	i16 = -0x8000;	gcTypeConverter.Do(PT_uint8, &ui8, PT_int16, &i16);
	AssertInt(0x0, ui8);

	i16 = -0x7fff;	gcTypeConverter.Do(PT_uint8, &ui8, PT_int16, &i16);
	AssertInt(0x0, ui8);

	i16 = -0x7f00;	gcTypeConverter.Do(PT_uint8, &ui8, PT_int16, &i16);
	AssertInt(0x0, ui8);

	i16 = -0x7eff;	gcTypeConverter.Do(PT_uint8, &ui8, PT_int16, &i16);
	AssertInt(0x0, ui8);

	i16 = 0x200;	gcTypeConverter.Do(PT_uint8, &ui8, PT_int16, &i16);
	AssertInt(4, ui8);

	i16 = 0x1ff;	gcTypeConverter.Do(PT_uint8, &ui8, PT_int16, &i16);
	AssertInt(3, ui8);

	i16 = 0x101;	gcTypeConverter.Do(PT_uint8, &ui8, PT_int16, &i16);
	AssertInt(2, ui8);

	i16 = 0x100;	gcTypeConverter.Do(PT_uint8, &ui8, PT_int16, &i16);
	AssertInt(2, ui8);

	i16 = 0x0ff;	gcTypeConverter.Do(PT_uint8, &ui8, PT_int16, &i16);
	AssertInt(1, ui8);

	i16 = 0x080;	gcTypeConverter.Do(PT_uint8, &ui8, PT_int16, &i16);
	AssertInt(0x1, ui8);

	i16 = 0x07f;	gcTypeConverter.Do(PT_uint8, &ui8, PT_int16, &i16);
	AssertInt(0x0, ui8);

	i16 = 0x0;		gcTypeConverter.Do(PT_uint8, &ui8, PT_int16, &i16);
	AssertInt(0x0, ui8);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTypeConverter(void)
{
	BeginTests();
	TypeConverterInit();

	TestTypeConverterUInt16ScaleTruncateToUInt8();
	TestTypeConverterUInt16ScaleTruncateToInt8();
	TestTypeConverterInt16ScaleTruncateToUInt8();
	TestTypeConverterFloat32ScaleTruncateToInt8();
	TestTypeConverterFloat64ScaleTruncateToInt8();
	
	TypeConverterKill();
	TestStatistics();
}

