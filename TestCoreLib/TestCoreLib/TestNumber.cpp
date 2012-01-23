#include "TestLib/Assert.h"
#include "TestNumber.h"
#include "BaseLib/NumberControl.h"
#include "BaseLib/FastFunctions.h"
#include "CoreLib/TypeConverter.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAdd(void)
{
	CNumber cNumber1;
	CNumber cNumber2;
	CNumber cNumber3;

	cNumber1.Init("123.45");
	cNumber2.Init("98.76");
	cNumber3.Init(cNumber1.Add(&cNumber2));
	AssertNumber("222.21", &cNumber3);
	AssertNumber("222.21", &cNumber1);
	AssertNumber("98.76", &cNumber2);

	AssertNumber("12345.6789", cNumber1.Init("12345")->Add(cNumber2.Init("0.6789")));
	AssertNumber("1.0", cNumber1.Init("0.5")->Add(cNumber2.Init("0.5")));
	AssertNumber("100", cNumber1.Init("99")->Add(cNumber2.Init("1")));
	AssertNumber("0", cNumber1.Init("20")->Add(cNumber2.Init("-20")));
	AssertNumber("-10", cNumber1.Init("20")->Add(cNumber2.Init("-30")));
	AssertNumber("10", cNumber1.Init("30")->Add(cNumber2.Init("-20")));
	AssertNumber("-10", cNumber1.Init("-30")->Add(cNumber2.Init("20")));
	AssertNumber("10", cNumber1.Init("-20")->Add(cNumber2.Init("30")));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSubtract(void)
{
	CNumber cNumber1;
	CNumber cNumber2;
	CNumber cNumber3;

	cNumber1.Init("123");
	cNumber2.Init("97");
	cNumber3.Init(cNumber1.Subtract(&cNumber2));
	AssertNumber("26", &cNumber3);
	AssertNumber("26", &cNumber1);
	AssertNumber("97", &cNumber2);
	AssertNumber("1", cNumber1.Init("100")->Subtract(cNumber2.Init("99")));
	AssertNumber("12344.3211", cNumber1.Init("12345")->Subtract(cNumber2.Init("0.6789")));
	AssertNumber("0", cNumber1.Init("0.5")->Subtract(cNumber2.Init("0.5")));
	AssertNumber("-10", cNumber1.Init("20")->Subtract(cNumber2.Init("30")));
	AssertNumber("10", cNumber1.Init("30")->Subtract(cNumber2.Init("20")));
	AssertNumber("-10", cNumber1.Init("-30")->Subtract(cNumber2.Init("-20")));
	AssertNumber("10", cNumber1.Init("-20")->Subtract(cNumber2.Init("-30")));
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGreaterThan(void)
{
	CNumber cNumber1;
	CNumber cNumber2;

	AssertBool(TRUE, cNumber1.Init("123")->GreaterThan(cNumber2.Init("122")));
	AssertBool(FALSE, cNumber1.Init("23")->GreaterThan(cNumber2.Init("122")));
	AssertBool(TRUE, cNumber1.Init("123")->GreaterThan(cNumber2.Init("22")));
	AssertBool(TRUE, cNumber1.Init("123.5")->GreaterThan(cNumber2.Init("123")));
	AssertBool(FALSE, cNumber1.Init("123")->GreaterThan(cNumber2.Init("123.5")));
	AssertBool(TRUE, cNumber1.Init("1")->GreaterThan(cNumber2.Init("0")));
	AssertBool(FALSE, cNumber1.Init("0")->GreaterThan(cNumber2.Init("1")));
	AssertBool(TRUE, cNumber1.Init("1")->GreaterThan(cNumber2.Init("-1")));
	AssertBool(FALSE, cNumber1.Init("-1")->GreaterThan(cNumber2.Init("1")));
	AssertBool(TRUE, cNumber1.Init("456")->GreaterThan(cNumber2.Init("-7921")));
	AssertBool(FALSE, cNumber1.Init("-7921")->GreaterThan(cNumber2.Init("456")));
	AssertBool(TRUE, cNumber1.Init("-456")->GreaterThan(cNumber2.Init("-456.34")));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGreaterThanOrEquals(void)
{
	CNumber cNumber1;
	CNumber cNumber2;

	AssertBool(TRUE, cNumber1.Init("123")->GreaterThanOrEquals(cNumber2.Init("122")));
	AssertBool(TRUE, cNumber1.Init("123")->GreaterThanOrEquals(cNumber2.Init("123")));
	AssertBool(FALSE, cNumber1.Init("23")->GreaterThanOrEquals(cNumber2.Init("122")));
	AssertBool(TRUE, cNumber1.Init("123")->GreaterThanOrEquals(cNumber2.Init("22")));
	AssertBool(TRUE, cNumber1.Init("123.5")->GreaterThanOrEquals(cNumber2.Init("123")));
	AssertBool(FALSE, cNumber1.Init("123")->GreaterThanOrEquals(cNumber2.Init("123.5")));
	AssertBool(TRUE, cNumber1.Init("0")->GreaterThanOrEquals(cNumber2.Init("0")));
	AssertBool(TRUE, cNumber1.Init("1")->GreaterThanOrEquals(cNumber2.Init("-1")));
	AssertBool(FALSE, cNumber1.Init("-1")->GreaterThanOrEquals(cNumber2.Init("1")));
	AssertBool(TRUE, cNumber1.Init("456")->GreaterThanOrEquals(cNumber2.Init("-7921")));
	AssertBool(FALSE, cNumber1.Init("-7921")->GreaterThanOrEquals(cNumber2.Init("456")));
	AssertBool(TRUE, cNumber1.Init("-456")->GreaterThanOrEquals(cNumber2.Init("-456.34")));
	AssertBool(TRUE, cNumber1.Init("-99999.9999")->GreaterThanOrEquals(cNumber2.Init("-99999.9999")));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMultiply(void)
{
	CNumber	cNumber1;
	CNumber	cNumber2;

	AssertNumber("4.6512088272417014", cNumber1.Init("2.2360679774997896")->Multiply(cNumber2.Init("2.0800838230519041")));

	AssertNumber("3", cNumber1.Init("6")->Multiply(cNumber2.Init("0.5")));
	AssertNumber("0", cNumber1.Init("0.000000001")->Multiply(cNumber2.Init("0.00000001")));
	AssertBool(TRUE, cNumber1.IsUnderflow());

	AssertNumber("6", cNumber1.Init("2")->Multiply(cNumber2.Init("3")));
	AssertNumber("1", cNumber1.Init("1000")->Multiply(cNumber2.Init("0.001")));
	AssertNumber("891", cNumber1.Init("99")->Multiply(cNumber2.Init("9")));
	AssertNumber("891", cNumber1.Init("9")->Multiply(cNumber2.Init("99")));
	AssertNumber("99999999999999999999800000.0000000000000001", cNumber1.Init("9999999999999.99999999")->Multiply(cNumber2.Init("9999999999999.99999999")));

	cNumber1.Init("999999999999999.99999999")->Multiply(cNumber2.Init("9999999999999.99999999"));
	AssertBool(TRUE, cNumber1.IsOverflow());
	AssertBool(FALSE, cNumber1.IsUnderflow());

	AssertNumber("49", cNumber1.Init("7")->Multiply(cNumber2.Init("7")));
	AssertNumber("-49", cNumber1.Init("7")->Multiply(cNumber2.Init("-7")));
	AssertNumber("-49", cNumber1.Init("-7")->Multiply(cNumber2.Init("7")));
	AssertNumber("49", cNumber1.Init("-7")->Multiply(cNumber2.Init("-7")));
	AssertNumber("0.0000000000000001", cNumber1.Init("0.00000001")->Multiply(cNumber2.Init("0.00000001")));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDivide(void)
{
	CNumber				cNumber1;
	CNumber				cNumber2;
	UNumber(26, 21)		uNumber3;
	UNumber(26, 21)		uNumber4;
	UNumber(26, 21)		uResult;

	AssertBool(TRUE, uResult.c.Init("1.471517764685769286382", 26, 21)->Equals(uNumber3.c.Init("4", 26, 21)->Divide(uNumber4.c.Init("2.71828182845904523536", 26, 21))));
	AssertNumber("1.15672535316593280000", cNumber1.Init("11.5672535316593283")->Divide(cNumber2.Init("10")));
	AssertNumber("0.9999999999999999", cNumber1.Init("99999999999999999999")->Divide(cNumber2.Init("100000000000000000000")));
	AssertNumber("3.3333333333333333", cNumber1.Init("0.001")->Divide(cNumber2.Init("0.0003")));
	AssertNumber("0.005", cNumber1.Init("0.001")->Divide(cNumber2.Init("0.2")));
	AssertNumber("-9", cNumber1.Init("-27")->Divide(cNumber2.Init("3")));
	AssertNumber("-9", cNumber1.Init("27")->Divide(cNumber2.Init("-3")));
	AssertNumber("2", cNumber1.Init("88888888888888888888888888.8888888888888888")->Divide(cNumber2.Init("44444444444444444444444444.4444444444444444")));
	AssertNumber("2.001", cNumber1.Init("6.003")->Divide(cNumber2.Init("3")));
	AssertNumber("100000", cNumber1.Init("100")->Divide(cNumber2.Init("0.001")));
	AssertNumber("1", cNumber1.Init("1")->Divide(cNumber2.Init("1")));
	AssertNumber("1", cNumber1.Init("123.456")->Divide(cNumber2.Init("123.456")));
	AssertNumber("0.00001", cNumber1.Init("0.001")->Divide(cNumber2.Init("100")));
	AssertNumber("2", cNumber1.Init("6")->Divide(cNumber2.Init("3")));
	AssertNumber("25.5555555555555555", cNumber1.Init("230")->Divide(cNumber2.Init("9")));

	AssertNumber("1", cNumber1.Init("99999999999999999999999999.9999999999999999")->Divide(cNumber2.Init("99999999999999999999999999.9999999999999999")));
	AssertBool(FALSE, cNumber1.IsOverflow());
	AssertBool(FALSE, cNumber1.IsUnderflow());

	AssertNumber("3.1428571428571428", cNumber1.Init("22")->Divide(cNumber2.Init("7")));
	AssertBool(FALSE, cNumber1.IsOverflow());
	AssertBool(TRUE, cNumber1.IsUnderflow());

	cNumber1.Init("10000000000000000000")->Divide(cNumber2.Init("0.0000000000000001"));
	AssertBool(TRUE, cNumber1.IsOverflow());

	cNumber1.Init("1")->Divide(cNumber2.Init("0"));
	AssertBool(TRUE, cNumber1.IsDivisionByZero());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestInit(void)
{
	CNumber cNumber;

	cNumber.Init(123);
	AssertInt(3, cNumber.GetFirstNonZeroDigit());
	AssertInt(1, cNumber.GetLastNonZeroDigit());
	AssertChar(1, cNumber.GetDigit(3));
	AssertChar(2, cNumber.GetDigit(2));
	AssertChar(3, cNumber.GetDigit(1));

	cNumber.Init(6.5f);
	AssertNumber("6.5", &cNumber);

	cNumber.Init(0.065f);
	AssertNumber("0.064999998", &cNumber);

	cNumber.Init(768.32476f);
	AssertNumber("768.32477", &cNumber);

	cNumber.Init(768.0f);
	AssertNumber("768", &cNumber);

	cNumber.Init("99999999999999999999999999.9999999999999999");
	AssertInt(26, cNumber.GetFirstNonZeroDigit());
	AssertInt(-16, cNumber.GetLastNonZeroDigit());
	AssertBool(FALSE, cNumber.IsNegative());
	AssertBool(FALSE, cNumber.IsOverflow());
	AssertBool(FALSE, cNumber.IsUnderflow());

	cNumber.Init("-99999999999999999999999999.9999999999999999");
	AssertInt(26, cNumber.GetFirstNonZeroDigit());
	AssertInt(-16, cNumber.GetLastNonZeroDigit());
	AssertBool(TRUE, cNumber.IsNegative());

	cNumber.Init("199999999999999999999999999.9999999999999999");
	AssertInt(0, cNumber.GetFirstNonZeroDigit());
	AssertInt(0, cNumber.GetLastNonZeroDigit());
	AssertBool(FALSE, cNumber.IsNegative());
	AssertBool(TRUE, cNumber.IsOverflow());
	AssertBool(FALSE, cNumber.IsUnderflow());

	cNumber.Init("99999999999999999999999999.99999999999999991");
	AssertInt(26, cNumber.GetFirstNonZeroDigit());
	AssertInt(-16, cNumber.GetLastNonZeroDigit());
	AssertBool(FALSE, cNumber.IsNegative());
	AssertBool(FALSE, cNumber.IsOverflow());
	AssertBool(TRUE, cNumber.IsUnderflow());

	cNumber.Init("-001.23", 1, 2);
	AssertNumber("-1.23", &cNumber);
	AssertBool(TRUE, cNumber.IsNegative());
	AssertBool(FALSE, cNumber.IsOverflow());
	AssertBool(FALSE, cNumber.IsUnderflow());

	cNumber.Init("091.23", 1, 2);
	AssertBool(FALSE, cNumber.IsNegative());
	AssertBool(TRUE, cNumber.IsOverflow());
	AssertBool(FALSE, cNumber.IsUnderflow());

	cNumber.Init("-091.23", 1, 2);
	AssertBool(TRUE, cNumber.IsNegative());
	AssertBool(TRUE, cNumber.IsOverflow());
	AssertBool(FALSE, cNumber.IsUnderflow());


	cNumber.Init("-001.2300", 1, 2);
	AssertNumber("-1.23", &cNumber);
	AssertBool(TRUE, cNumber.IsNegative());
	AssertBool(FALSE, cNumber.IsOverflow());
	AssertBool(FALSE, cNumber.IsUnderflow());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNumbersErrors(void)
{
	CNumber	cNumber1;
	CNumber	cNumber2;

	cNumber1.Init("1")->Divide(cNumber2.Init("0"));
	AssertBool(TRUE, cNumber1.IsDivisionByZero());

	cNumber1.Multiply(cNumber2.Init("1"));
	AssertBool(TRUE, cNumber1.IsDivisionByZero());
	AssertBool(FALSE, cNumber2.IsError());

	cNumber2.Multiply(&cNumber1);
	AssertBool(TRUE, cNumber1.IsDivisionByZero());
	AssertBool(TRUE, cNumber2.IsError());

}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPower(void)
{
	CNumber	cNumber1;
	CNumber	cNumber2;

	AssertNumber(" 25", cNumber1.Init(5)->Power(cNumber2.Init(2)));
	AssertNumber("729", cNumber1.Init(9)->Power(cNumber2.Init(3)));
	AssertNumber("  8",	cNumber1.Init(2)->Power(cNumber2.Init("3")));
	AssertNumber("26482031752276.027747734827837459050898194354857686747138225447207675556779521628404198058413736336629356579385228078", cNumber1.Init("456.214")->Power(cNumber2.Init("5.0478")));
	AssertNumber("             2.236067977499789696409173668731276235440618359611525724270897245410520925637804899414414408378782274969", cNumber1.Init("5")->Power(cNumber2.Init("0.5")));
	AssertNumber("             2.080083823051904114530056824357885386337805340373262109697591080200106311397268773606056636790757486728", cNumber1.Init("9")->Power(cNumber2.Init("3")->Inverse()));
	AssertNumber("          1995.460686346360438056032799000705183394248095614408274664005291694081779900040419742672518120493194499915", cNumber1.Init("23")->Power(cNumber2.Init("2.42342345412")));
	AssertNumber("          7619.415663011393769338092362785817856820470691782379719888602900314907664288619635533486179059377792725474", cNumber1.Init("17.1933")->Power(cNumber2.Init("3.14234235451299")));
	AssertNumber("          1.185828776582884967590566309155445492893928890197092099264602396268423886155337590929478679094445890360450", cNumber1.Init("234")->Power(cNumber2.Init("0.03124324234")));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRoot(void)
{
	CNumber	cNumber1;
	CNumber	cNumber2;

	AssertNumber("26482031752276.118682314600539665918167991694787993761730712614644342606699238096562695893599972054023910509019880531", cNumber1.Init("456.214")->Root(cNumber2.Init("0.1981061056301755")));
	AssertNumber("			  10.691917936236095954607065583259788252257327917845876143777040163997185591541961845746875603610447251017", cNumber1.Init("823478.1238912")->Root(cNumber2.Init("5.7486223")));
	AssertNumber("			  15.245103937181455626521994248356566202221147126112043145794045435628192973472945303695861960225213247323", cNumber1.Init("823478.1238912")->Root(cNumber2.Init("5.0000001")));
	AssertNumber("			  15.245104767813526902640501729473222184360145676229679891311842535008668782995604283538894948010318752470", cNumber1.Init("823478.1238912")->Root(cNumber2.Init("5")));
	AssertNumber("             2.236067977499789696409173668731276235440618359611525724270897245410520925637804899414414408378782274969", cNumber1.Init("5")->Root(cNumber2.Init("2")));
	AssertNumber("             2.080083823051904114530056824357885386337805340373262109697591080200106311397268773606056636790757486728", cNumber1.Init("9")->Root(cNumber2.Init("3")));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNaturalLogarithm(void)
{
	UNumber(26, 30)		uNumber1;

	AssertNumber(" 0.693147180559945309417232121458", uNumber1.c.Init(2, 26, 30)->NaturalLogarithm());
	AssertNumber("46.051701859880913680349829093687", uNumber1.c.Init("99999999999999999999", 26, 30)->NaturalLogarithm());
	AssertNumber("-0.693147180559945309417232121458", uNumber1.c.Init("0.5", 26, 30)->NaturalLogarithm());
	AssertNumber("59.832099999999959348204946348859", uNumber1.c.Init("96549687107865177125153989.7228030628", 26, 30)->NaturalLogarithm());
	AssertNumber("-0.761426021313239740524443075318", uNumber1.c.Init("0.467", 26, 30)->NaturalLogarithm());
	AssertNumber(" 0.607589292198298721215760207503", uNumber1.c.Init("1.836", 26, 30)->NaturalLogarithm());
	AssertNumber(" 0.210721023218417341672392615930", uNumber1.c.Init("1.2345678912379812", DEFAULT_WHOLE_NUMBERS, 30)->NaturalLogarithm());

	UNumber(26, 60)		uNumber2;

	AssertNumber(" 0.693147180559945309417232121458176568075500134360255254120680", uNumber2.c.Init(2, 26, 60)->NaturalLogarithm());
	AssertNumber("46.051701859880913680349829093687284152021979772575459520666557", uNumber2.c.Init("99999999999999999999", 26, 60)->NaturalLogarithm());
	AssertNumber("-0.693147180559945309417232121458176568075500134360255254120680", uNumber2.c.Init("0.5", 26, 60)->NaturalLogarithm());
	AssertNumber("59.832099999999959348204946348859395584510264049665522611580253", uNumber2.c.Init("96549687107865177125153989.7228030628", 26, 60)->NaturalLogarithm());
	AssertNumber("-0.761426021313239740524443075318823636652462475325747369485896", uNumber2.c.Init("0.467", 26, 60)->NaturalLogarithm());
	AssertNumber(" 0.607589292198298721215760207503964162878370488888184722642697", uNumber2.c.Init("1.836", 26, 60)->NaturalLogarithm());
	AssertNumber(" 0.210721023218417341672392615930853311767258874872887732536673", uNumber2.c.Init("1.2345678912379812", DEFAULT_WHOLE_NUMBERS, 60)->NaturalLogarithm());

	UNumber(26, 102)	uNumber3;

	AssertNumber(" 0.693147180559945309417232121458176568075500134360255254120680009493393621969694715605863326996418687542", uNumber3.c.Init(2, DEFAULT_WHOLE_NUMBERS, 102)->NaturalLogarithm());
	AssertNumber("46.051701859880913680349829093687284152021979772575459520666557686018118860213716268886610768458632633486", uNumber3.c.Init("99999999999999999999", DEFAULT_WHOLE_NUMBERS, 102)->NaturalLogarithm());
	AssertNumber("-0.693147180559945309417232121458176568075500134360255254120680009493393621969694715605863326996418687542", uNumber3.c.Init("0.5", DEFAULT_WHOLE_NUMBERS, 102)->NaturalLogarithm());
	AssertNumber("59.832099999999959348204946348859395584510264049665522611580253566029875921038191976969958986177991457508", uNumber3.c.Init("96549687107865177125153989.7228030628", DEFAULT_WHOLE_NUMBERS, 102)->NaturalLogarithm());
	AssertNumber("-0.761426021313239740524443075318823636652462475325747369485896032915659385841000090585731967273138949168", uNumber3.c.Init("0.467", DEFAULT_WHOLE_NUMBERS, 102)->NaturalLogarithm());
	AssertNumber(" 0.607589292198298721215760207503964162878370488888184722642697054878844870364090172036677171202741693940", uNumber3.c.Init("1.836", DEFAULT_WHOLE_NUMBERS, 102)->NaturalLogarithm());
	AssertNumber(" 0.210721023218417341672392615930853311767258874872887732536673787994647093653812636130792225811993635713", uNumber3.c.Init("1.2345678912379812", DEFAULT_WHOLE_NUMBERS, 102)->NaturalLogarithm());

}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIntValue(void)
{
	CNumber	cNumber;

	AssertInt(1, cNumber.Init("1")->IntValue());
	AssertInt(432, cNumber.Init("432")->IntValue());
	AssertInt(-2001002003, cNumber.Init("-2001002003")->IntValue());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestExponential(void)
{
	CNumber				cNumber1;
	UNumber(26, 31)		uNumber2;

	AssertNumber("26482031752276.1186823146005396645852508560782", uNumber2.c.Init("30.90748757185891757704924054275433", 26, 31)->Exponential());

	AssertNumber("96549687107869102043246792.881487012600969979831239710780438424009808501178245743863380701665895170306393466959990912491863259372", cNumber1.Init("59.8321")->Exponential());
	AssertNumber("42012104037905142549565934.307191617684111119732990967864642572942002240687862729011536316183005458402504475753279726535480078011", cNumber1.Init("59")->Exponential());
	AssertNumber("						  12.553506136668231408032023200075414193717622965101179168023245861897281591674985311360149034187825761394", cNumber1.Init("2.53")->Exponential());
	AssertNumber("                        12.182493960703473438070175951167966183182767790063161311560398341838185126143314410060255523006295788741", cNumber1.Init("2.5")->Exponential());
	AssertNumber("						  26.084936444643848091923461155293805374010294539402766117792640720767691777557023277915148043083052572453", cNumber1.Init("3.261358")->Exponential());
	AssertNumber("						   4.481689070338064822602055460119275819005749868369667056772650082785936674466713772981053831382453391388", cNumber1.Init("1.5")->Exponential());
	AssertNumber("						   1.648721270700128146848650787814163571653776100710148011575079311640661021194215608632776520056366643002", cNumber1.Init("0.5")->Exponential());
	AssertNumber("						   7.389056098930650227230427460575007813180315570551847324087127822522573796079057763384312485079121794773", cNumber1.Init("2")->Exponential());
	AssertNumber("						   2.718281828459045235360287471352662497757247093699959574966967627724076630353547594571382178525166427427", cNumber1.Init("1")->Exponential());
	AssertNumber("						   1.0",																									  cNumber1.Init("0")->Exponential());
	AssertNumber("						   0.367879441171442321595523770161460867445811131031767834507836801697461495744899803357147274345919643746", cNumber1.Init("-1")->Exponential());
	AssertNumber("						   0.223130160148429828933280470764012521342171629361079328743835318760325166631314441177563730332577590775", cNumber1.Init("-1.5")->Exponential());
	AssertNumber("						   0.135335283236612691893999494972484403407631545909575881468158872654073374101487689937098122490657048755", cNumber1.Init("-2")->Exponential());
	AssertNumber("						   0.082084998623898795169528674467159807837804121015436648845758410515224756880410971309751571521236465908", cNumber1.Init("-2.5")->Exponential());
	AssertNumber("						   0.079659020285898025765054906486419252919652649639156599073334469541971122866572869567513044307632946859", cNumber1.Init("-2.53")->Exponential());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCopy(void)
{
	CNumber				cNumber1;
	UNumber(100, 60)	uNumber2;
	CNumber				cNumber3;
	UNumber(1, 10)		uNumber4;

	cNumber1.Init("10.56");
	uNumber2.c.Init("10.56", 100, 60);

	cNumber3.E();
	AssertNumber("2.7182818284590452", &cNumber3);
	AssertInt(1, cNumber3.GetFirstNonZeroDigit());
	AssertInt(-16, cNumber3.GetLastNonZeroDigit());
	AssertInt(26, cNumber3.mcMaxWholeNumbers);
	AssertInt(16, cNumber3.mcMaxDecimals);

	uNumber4.c.Copy(&cNumber3, 1, 10);
	AssertNumber("2.7182818284", &uNumber4.c);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArithmeticGeometricMean(void)
{
	CNumber				cNumber1;
	CNumber				cNumber2;

	AssertNumber("   13.4581714817256152", cNumber1.Init(24)->ArithmeticGeometricMean(cNumber2.Init(6)));
	AssertNumber("43622.5572810216407774", cNumber1.Init("23536.0287471352662497")->ArithmeticGeometricMean(cNumber2.Init("69995.9574966967627724")));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPrivateSubtract(void)
{
	CNumber	cNumber1;
	CNumber	cNumber2;

	cNumber1.Init("10.02")->PrivateSubtract(cNumber2.Init("0.3322"));
	AssertNumber("9.6878", &cNumber1);

	cNumber1.Init("10.3322")->PrivateSubtract(cNumber2.Init("0.02"));
	AssertNumber("10.3122", &cNumber1);

	cNumber1.Init("10.02")->PrivateSubtract(cNumber2.Init("10.01"));
	AssertNumber("0.01", &cNumber1);

	cNumber1.Init("10.02")->PrivateSubtract(cNumber2.Init("10.02"));
	AssertNumber("0", &cNumber1);

	cNumber1.Init("100")->PrivateSubtract(cNumber2.Init("0.001"));
	AssertNumber("99.999", &cNumber1);

	cNumber1.Init("1")->PrivateSubtract(cNumber2.Init("0"));
	AssertNumber("1", &cNumber1);

	cNumber1.Init("12345")->PrivateSubtract(cNumber2.Init("0.6789"));
	AssertNumber("12344.3211", &cNumber1);

	CNumber		cNumber3;
	CNumber		cNumber4;

	cNumber3.Init("54.76", 2, 2)->PrivateSubtract(cNumber4.Init("5.448", 1, 3));
	AssertNumber("49.32", &cNumber3);
	AssertBool(FALSE, cNumber3.IsOverflow());
	AssertBool(TRUE, cNumber3.IsUnderflow());

	cNumber3.Init("540", 3, 0)->PrivateSubtract(cNumber4.Init("0.432", 0, 3));
	AssertNumber("540", &cNumber3);
	AssertBool(FALSE, cNumber3.IsOverflow());
	AssertBool(TRUE, cNumber3.IsUnderflow());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNumber(void)
{
	BeginTests();

	FastFunctionsInit();
	TypeConverterInit();
	NumberInit();

	TestPrivateSubtract();
	TestInit();
	TestCopy();
	TestIntValue();
	TestGreaterThan();
	TestGreaterThanOrEquals();
	TestAdd();
	TestSubtract();
	TestMultiply();
	TestDivide();
	TestNumbersErrors();
	TestArithmeticGeometricMean();
	TestNaturalLogarithm();
	//TestExponential();
	//TestRoot();
	//TestPower();

	NumberKill();
	FastFunctionsKill();
	TypeConverterKill();

	TestStatistics();
}

