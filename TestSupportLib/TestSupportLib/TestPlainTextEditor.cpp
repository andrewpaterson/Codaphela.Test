#include "stdafx.h"
#include "CoreLib/PlainTextEditor.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPlainTextEditorInsertionAndTypeOver(void)
{
	CPlainTextEditor	cEditor;
	int					iChars;

	cEditor.Init("");
	cEditor.Printable('H');
	cEditor.Printable('e');
	cEditor.Printable('l');
	cEditor.Printable('l');
	cEditor.Printable('o');
	AssertString("Hello", cEditor.Text());
	AssertInt(5, cEditor.miEditPos);

	cEditor.Left();
	cEditor.Printable('x');
	AssertString("Hellxo", cEditor.Text());
	AssertInt(5, cEditor.miEditPos);

	cEditor.Backspace();
	AssertString("Hello", cEditor.Text());
	AssertInt(4, cEditor.miEditPos);

	cEditor.Home();
	cEditor.Paste("World ");
	AssertString("World Hello", cEditor.Text());
	AssertInt(6, cEditor.miEditPos);

	cEditor.Backspace();
	cEditor.Enter();
	AssertString("World\nHello", cEditor.Text());
	AssertInt(6, cEditor.miEditPos);

	cEditor.Right();
	cEditor.Right();
	cEditor.Right();
	cEditor.Right();
	cEditor.Right();
	cEditor.Enter();
	AssertString("World\nHello\n", cEditor.Text());
	AssertInt(12, cEditor.miEditPos);

	cEditor.Tab();
	cEditor.Printable('X');
	iChars = cEditor.GetCharCountAlongLine(cEditor.miEditPos);
	AssertInt(5, iChars);
	iChars = cEditor.GetCharCountAlongLine(cEditor.miEditPos-1);
	AssertInt(4, iChars);
	iChars = cEditor.GetCharCountAlongLine(cEditor.miEditPos-2);
	AssertInt(0, iChars);

	cEditor.Left();
	cEditor.Up();
	AssertString("World\nHello\n\tX", cEditor.Text());
	AssertInt(10, cEditor.miEditPos);

	cEditor.Printable('O', false);
	cEditor.Printable('!', false);
	AssertString("World\nHellO!\n\tX", cEditor.Text());
	cEditor.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPlainTextEditorSimpleNavigation(void)
{
	CPlainTextEditor	cEditor;
	int					iChars;

	cEditor.Init("");
	cEditor.Printable('H');
	cEditor.Printable('e');
	cEditor.Printable('l');
	cEditor.Printable('l');
	cEditor.Printable('o');
	AssertString("Hello", cEditor.Text());
	AssertInt(5, cEditor.miEditPos);

	cEditor.Left();
	cEditor.Printable('x');
	AssertString("Hellxo", cEditor.Text());
	AssertInt(5, cEditor.miEditPos);

	cEditor.Backspace();
	AssertString("Hello", cEditor.Text());
	AssertInt(4, cEditor.miEditPos);

	cEditor.Home();
	cEditor.Paste("World ");
	AssertString("World Hello", cEditor.Text());
	AssertInt(6, cEditor.miEditPos);

	cEditor.Backspace();
	cEditor.Enter();
	AssertString("World\nHello", cEditor.Text());
	AssertInt(6, cEditor.miEditPos);

	cEditor.Right();
	cEditor.Right();
	cEditor.Right();
	cEditor.Right();
	cEditor.Right();
	cEditor.Enter();
	AssertString("World\nHello\n", cEditor.Text());
	AssertInt(12, cEditor.miEditPos);

	cEditor.Tab();
	cEditor.Printable('X');
	iChars = cEditor.GetCharCountAlongLine(cEditor.miEditPos);
	AssertInt(5, iChars);
	iChars = cEditor.GetCharCountAlongLine(cEditor.miEditPos-1);
	AssertInt(4, iChars);
	iChars = cEditor.GetCharCountAlongLine(cEditor.miEditPos-2);
	AssertInt(0, iChars);

	cEditor.Left();
	cEditor.Up();
	AssertString("World\nHello\n\tX", cEditor.Text());
	AssertInt(10, cEditor.miEditPos);

	cEditor.Printable('O', false);
	cEditor.Printable('!', false);
	AssertString("World\nHellO!\n\tX", cEditor.Text());
	cEditor.Kill();

	cEditor.Init("\tX");
	cEditor.Home();
	cEditor.Printable('a', false);
	AssertString("a\tX", cEditor.Text());
	cEditor.Printable('b', false);
	AssertString("ab\tX", cEditor.Text());
	cEditor.Printable('c', false);
	AssertString("abc\tX", cEditor.Text());
	cEditor.Printable('d', false);
	AssertString("abcdX", cEditor.Text());
	cEditor.Printable('Y', false);
	AssertString("abcdY", cEditor.Text());
	cEditor.Left();
	cEditor.Delete();
	AssertString("abcd", cEditor.Text());
	cEditor.Delete();
	AssertString("abcd", cEditor.Text());

	cEditor.Home();
	AssertInt(0, cEditor.miEditPos);
	cEditor.End();
	AssertInt(4, cEditor.miEditPos);
	cEditor.Enter();
	cEditor.Paste("efgh");
	AssertString("abcd\nefgh", cEditor.Text());
	cEditor.Home();
	AssertInt(5, cEditor.miEditPos);
	cEditor.Up();
	AssertInt(0, cEditor.miEditPos);
	cEditor.End();
	AssertInt(4, cEditor.miEditPos);
	cEditor.Down();
	AssertInt(9, cEditor.miEditPos);
	cEditor.End();
	AssertInt(9, cEditor.miEditPos);
	cEditor.Left();
	cEditor.End();
	AssertInt(9, cEditor.miEditPos);
	cEditor.Home();
	cEditor.Up();
	cEditor.Right();
	cEditor.Down();
	AssertInt(6, cEditor.miEditPos);
	cEditor.Down();
	AssertInt(9, cEditor.miEditPos);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPlainTextEditorUpDownNavigation(void)
{
	CPlainTextEditor	cEditor;

	cEditor.Init("\
zzzzzzz\n\
\n\
zzz\n\
zzzzzzz\n\
zzz\n\
zz\n\
zzzz\n\
\n\
zzzzzzz");

	cEditor.Right();
	cEditor.Right();
	cEditor.Right();
	cEditor.Right();
	AssertInt(4, cEditor.miEditPos);

	cEditor.Down();
	AssertInt(8, cEditor.miEditPos);
	cEditor.Down();
	AssertInt(12, cEditor.miEditPos);
	cEditor.Down();
	AssertInt(17, cEditor.miEditPos);

	cEditor.Up();
	AssertInt(12, cEditor.miEditPos);
	cEditor.Up();
	AssertInt(8, cEditor.miEditPos);
	cEditor.Up();
	AssertInt(4, cEditor.miEditPos);
	cEditor.Down();
	cEditor.Down();
	cEditor.Left();
	cEditor.Down();
	AssertInt(15, cEditor.miEditPos);

	cEditor.DocumentHome();
	cEditor.Down();
	cEditor.Down();
	AssertInt(9, cEditor.miEditPos);

	cEditor.DocumentEnd();
	cEditor.PageUp();
	AssertInt(7, cEditor.miEditPos);

	cEditor.Left();
	cEditor.Left();
	cEditor.Left();
	cEditor.SetPageLength(3);
	cEditor.PageDown();
	AssertInt(17, cEditor.miEditPos);
	cEditor.PageDown();
	AssertInt(32, cEditor.miEditPos);
	cEditor.PageUp();
	AssertInt(17, cEditor.miEditPos);
	cEditor.PageDown();
	cEditor.PageDown();
	AssertInt(38, cEditor.miEditPos);
	cEditor.PageUp();
	AssertInt(27, cEditor.miEditPos);
	cEditor.PageUp();
	AssertInt(12, cEditor.miEditPos);
	cEditor.PageUp();
	AssertInt(4, cEditor.miEditPos);

	cEditor.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPlainTextEditorWordNavigation(void)
{
	CPlainTextEditor	cEditor;

	cEditor.Init("\t\tHello World()\n\t\tEndOfLine;Nah!");

	cEditor.WordRight();
	AssertInt(2, cEditor.miEditPos);
	cEditor.WordRight();
	AssertInt(7, cEditor.miEditPos);
	cEditor.WordRight();
	AssertInt(8, cEditor.miEditPos);	
	cEditor.WordRight();
	AssertInt(13, cEditor.miEditPos);
	cEditor.WordRight();
	AssertInt(14, cEditor.miEditPos);
	cEditor.WordRight();
	AssertInt(15, cEditor.miEditPos);
	cEditor.WordRight();
	AssertInt(18, cEditor.miEditPos);
	cEditor.WordRight();
	AssertInt(27, cEditor.miEditPos);
	cEditor.WordRight();
	AssertInt(28, cEditor.miEditPos);
	cEditor.WordRight();
	AssertInt(31, cEditor.miEditPos);
	cEditor.WordRight();
	AssertInt(32, cEditor.miEditPos);
	cEditor.WordRight();
	AssertInt(32, cEditor.miEditPos);

	cEditor.WordLeft();
	AssertInt(31, cEditor.miEditPos);
	cEditor.WordLeft();
	AssertInt(28, cEditor.miEditPos);
	cEditor.WordLeft();
	AssertInt(27, cEditor.miEditPos);	
	cEditor.WordLeft();
	AssertInt(18, cEditor.miEditPos);
	cEditor.WordLeft();
	AssertInt(15, cEditor.miEditPos);
	cEditor.WordLeft();
	AssertInt(14, cEditor.miEditPos);
	cEditor.WordLeft();
	AssertInt(13, cEditor.miEditPos);
	cEditor.WordLeft();
	AssertInt(8, cEditor.miEditPos);
	cEditor.WordLeft();
	AssertInt(7, cEditor.miEditPos);
	cEditor.WordLeft();
	AssertInt(2, cEditor.miEditPos);
	cEditor.WordLeft();
	AssertInt(0, cEditor.miEditPos);
	cEditor.WordLeft();
	AssertInt(0, cEditor.miEditPos);

	cEditor.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPlainTextEditorSelection(void)
{
	CPlainTextEditor	cEditor;
	CChars				szSelection;

	cEditor.Init("ABCDE\nFGHIJ\nKLMNO\nPQRST\nUVWXY");

	cEditor.SelectRight();
	AssertInt(1, cEditor.miEditPos);
	AssertInt(0, cEditor.miSelectionAnchor);
	AssertInt(1, cEditor.miSelectionFloating);

	cEditor.SelectRight();
	AssertInt(2, cEditor.miEditPos);
	AssertInt(0, cEditor.miSelectionAnchor);
	AssertInt(2, cEditor.miSelectionFloating);

	cEditor.Right();
	AssertInt(3, cEditor.miEditPos);
	AssertInt(-1, cEditor.miSelectionAnchor);
	AssertInt(-1, cEditor.miSelectionFloating);

	cEditor.SelectDown();
	cEditor.SelectDown();
	AssertInt(15, cEditor.miEditPos);
	AssertInt(3, cEditor.miSelectionAnchor);
	AssertInt(15, cEditor.miSelectionFloating);
	
	szSelection.Init();
	cEditor.Copy(&szSelection);
	AssertString("DE\nFGHIJ\nKLM", szSelection.Text());
	szSelection.Kill();

	cEditor.DocumentHome();
	cEditor.SelectDocumentEnd();
	AssertInt(0, cEditor.miSelectionAnchor);
	AssertInt(29, cEditor.miSelectionFloating);

	szSelection.Init();
	cEditor.Copy(&szSelection);
	AssertString("ABCDE\nFGHIJ\nKLMNO\nPQRST\nUVWXY", szSelection.Text());
	szSelection.Kill();

	cEditor.SetPosition(8);
	cEditor.SelectWholeWord();
	szSelection.Init();
	cEditor.Copy(&szSelection);
	AssertString("FGHIJ", szSelection.Text());
	szSelection.Kill();
	AssertInt(6, cEditor.miSelectionAnchor);
	AssertInt(11, cEditor.miSelectionFloating);

	cEditor.SetPageLength(2);
	cEditor.SelectPageDown();
	szSelection.Init();
	cEditor.Copy(&szSelection);
	AssertString("FGHIJ\nKLMNO\nPQRST", szSelection.Text());
	szSelection.Kill();
	AssertInt(6, cEditor.miSelectionAnchor);
	AssertInt(23, cEditor.miSelectionFloating);

	cEditor.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPlainTextEditorCopyPaste(void)
{
	CPlainTextEditor	cEditor;
	CChars				szSelection;

	cEditor.Init("ABCDE\nFGHIJ\nKLMNO\nPQRST\nUVWXY");
	cEditor.SetPosition(8);
	szSelection.Init();
	cEditor.CutLine(&szSelection);
	AssertString("FGHIJ\n", szSelection.Text());
	szSelection.Kill();
	AssertInt(8, cEditor.miEditPos);
	AssertInt(2, cEditor.GetCharCountAlongLine(cEditor.miEditPos));

	cEditor.Down();
	cEditor.Down();

	szSelection.Init();
	cEditor.CutLine(&szSelection);
	AssertString("UVWXY", szSelection.Text());
	szSelection.Kill();
	AssertInt(20, cEditor.miEditPos);
	AssertInt(2, cEditor.GetCharCountAlongLine(cEditor.miEditPos));

	cEditor.DocumentHome();
	cEditor.Right();

	szSelection.Init();
	cEditor.CutLine(&szSelection);
	AssertString("ABCDE\n", szSelection.Text());
	szSelection.Kill();
	AssertInt(1, cEditor.miEditPos);
	AssertInt(1, cEditor.GetCharCountAlongLine(cEditor.miEditPos));

	AssertString("KLMNO\nPQRST\n", cEditor.Text());
	cEditor.Kill();

	cEditor.Init("ABCDE\nFGHIJ\nKLMNO\nPQRST\nUVWXY");
	cEditor.SetPosition(8);
	cEditor.SelectDown();
	cEditor.SelectDown();
	cEditor.SelectRight();
	cEditor.DeleteLine();

	AssertString("ABCDE\nUVWXY", cEditor.Text());
	AssertInt(9, cEditor.miEditPos);
	AssertInt(3, cEditor.GetCharCountAlongLine(cEditor.miEditPos));

	cEditor.SetPosition(2);
	cEditor.SelectDown();
	cEditor.DeleteLine();
	AssertString("", cEditor.Text());

	cEditor.Kill();

	cEditor.Init("ABCDE\nFGHIJ\nKLMNO");
	cEditor.Right();
	cEditor.DeleteWordRemainingRight();
	AssertString("A\nFGHIJ\nKLMNO", cEditor.Text());
	cEditor.DeleteWordRemainingRight();
	AssertString("AFGHIJ\nKLMNO", cEditor.Text());
	cEditor.DeleteWordRemainingRight();
	AssertString("A\nKLMNO", cEditor.Text());
	cEditor.DeleteWordRemainingRight();
	AssertString("AKLMNO", cEditor.Text());
	cEditor.DeleteWordRemainingRight();
	AssertString("A", cEditor.Text());

	cEditor.Kill();

	cEditor.Init("ABCDE\nFGHIJ\nKLMNO");
	
	cEditor.SetPosition(8);
	cEditor.Duplicate();
	AssertString("ABCDE\nFGHIJ\nFGHIJ\nKLMNO", cEditor.Text());
	AssertInt(8, cEditor.miEditPos);

	cEditor.SetPosition(1);
	cEditor.SelectRight();
	cEditor.SelectRight();
	cEditor.SelectRight();
	cEditor.Duplicate();
	AssertString("ABCDBCDE\nFGHIJ\nFGHIJ\nKLMNO", cEditor.Text());
	AssertInt(4, cEditor.miEditPos);

	cEditor.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPlainTextEditorSelectionOverwrite(void)
{
	CPlainTextEditor	cEditor;
	CChars				szTemp;

	cEditor.Init("The Quick Brown Fox Blah, Blah, Blah.");
	cEditor.WordRight();
	cEditor.WordRight();
	cEditor.SelectWordRight();

	szTemp.Init();
	cEditor.Cut(&szTemp);
	cEditor.Delete();
	cEditor.WordRight();
	cEditor.WordRight();
	cEditor.SelectWordRight();
	cEditor.Paste(szTemp.Text());
	szTemp.Kill();
	AssertString("The Brown Quick Blah, Blah, Blah.", cEditor.Text());

	cEditor.Right();
	cEditor.Right();
	cEditor.SelectWholeWord();
	cEditor.Printable('X');
	AssertString("The Brown Quick X, Blah, Blah.", cEditor.Text());

	cEditor.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPlainTextEditorDeleteLine(void)
{
	CPlainTextEditor	cEditor;

	cEditor.Init("A scary tale.");
	cEditor.End();
	cEditor.Enter();
	cEditor.Paste("Fairy folk and evil doers.");
	cEditor.DeleteLine();
	cEditor.Paste("Black Jack and Henry.");
	AssertString("A scary tale.\nBlack Jack and Henry.", cEditor.Text());

	AssertInt(35, cEditor.miEditPos);
	AssertInt(21, cEditor.GetCharCountAlongLine(cEditor.miEditPos));
	cEditor.Up();
	AssertInt(13, cEditor.miEditPos);
	AssertInt(21, cEditor.miUpDownCharCount);

	cEditor.DeleteLine();
	AssertString("Black Jack and Henry.", cEditor.Text());
	AssertInt(13, cEditor.miEditPos);
	cEditor.Home();
	cEditor.Paste("A terrifying tale:");
	cEditor.Enter();
	AssertString("A terrifying tale:\nBlack Jack and Henry.", cEditor.Text());
	AssertInt(19, cEditor.miEditPos);

	cEditor.DeleteLine();
	AssertString("A terrifying tale:\n", cEditor.Text());
	AssertInt(19, cEditor.miEditPos);
	cEditor.DeleteLine();
	AssertString("A terrifying tale:\n", cEditor.Text());
	AssertInt(19, cEditor.miEditPos);

	cEditor.Left();
	cEditor.DeleteLine();
	AssertString("", cEditor.Text());
	AssertInt(0, cEditor.miEditPos);

	cEditor.DeleteLine();
	AssertString("", cEditor.Text());
	AssertInt(0, cEditor.miEditPos);

	cEditor.Paste("Once upon a time.");
	cEditor.Enter();
	cEditor.Paste("There was an Astrogat.");
	cEditor.DocumentHome();
	AssertInt(0, cEditor.miEditPos);

	cEditor.DeleteLine();
	AssertString("There was an Astrogat.", cEditor.Text());
	cEditor.DeleteLine();
	AssertString("", cEditor.Text());
	AssertInt(0, cEditor.miEditPos);
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPlainTextEditorLeftRightDelete(void)
{
	CPlainTextEditor	cEditor;

	cEditor.Init();
	cEditor.Printable('H');
	cEditor.Left();
	cEditor.Delete();

	AssertString("", cEditor.Text());
	AssertInt(0, cEditor.miEditPos);

	cEditor.Left();
	AssertInt(0, cEditor.miEditPos);

	cEditor.Delete();
	AssertInt(0, cEditor.miEditPos);

	cEditor.Right();
	AssertInt(0, cEditor.miEditPos);


	cEditor.Printable('H');
	AssertString("H", cEditor.Text());
	cEditor.Left();
	AssertInt(0, cEditor.miEditPos);
	cEditor.Backspace();
	AssertInt(0, cEditor.miEditPos);
	cEditor.Right();
	AssertInt(1, cEditor.miEditPos);
	cEditor.Delete();
	AssertInt(1, cEditor.miEditPos);
	AssertString("H", cEditor.Text());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPlainTextEditor(void)
{
	BeginTests();

	//TestPlainTextEditorInsertionAndTypeOver();
	//TestPlainTextEditorSimpleNavigation();
	//TestPlainTextEditorUpDownNavigation();
	//TestPlainTextEditorWordNavigation();
	//TestPlainTextEditorSelection();
	//TestPlainTextEditorCopyPaste();
	//TestPlainTextEditorSelectionOverwrite();
	//TestPlainTextEditorDeleteLine();
	TestPlainTextEditorLeftRightDelete();

	TestStatistics();
}
