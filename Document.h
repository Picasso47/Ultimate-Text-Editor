#pragma once
#include<iostream>
#include<fstream>
#include<Windows.h>
#include<conio.h>
#include<string>
#include "Lines.h"
#include "Document.h"
#include "TextEditor.h"

using namespace std;
class Document
{
private:
	friend class Lines;
	friend class TextEditor;
	Lines* Ls;
	int NOLs;
	string Dname;
	int dri = 0, dci = 0;
	void Deepcopy(Lines& NLs, const Lines& L)
	{

	}
public:
	Document();
	Document(Document&);
	Document(int);
	void SimpleUpdater(string fname);
	void load(string fname);
	void Enter_AddNewLine(int ri, int ci);
	void BackSpace_LineRemover(int Ln,int &row_p);
	void FindCaseSens(string Tofind);
	void FindInCaseSens(string Tofind);
	int SmallestWordLen();
	int LargestWordLength();
	int WordCount();
	double AvgWordLen();
	int SpecialCharCount();
	int SentencesCount(); 
	int paragraphcount();
	void Prefix(string Tofind, string PreFix);
	void PostFix(string Tofind, string PostFix);
	void FindAndReplaceFirst(string tofind, string toreplace);
	void FindAndReplaceAll(string tofind, string toreplace);
	void FindReplaceAllNext(string find, string replace, int cr, int cc);
	void FindReplaceAllPrev(string find, string replace, int cr, int cc);
	void FindReplaceNext(string find, string replace, int cr, int cc);
	void FindReplacePrev(string find, string replace, int cr, int cc);
	void FindingSentence(string a);
	void LoadEncodedFile(string Fname);
	void SaveasEncodedFile(string Fname);
	void ExitDocument();
	~Document();
	void PrintDocument();
	void wordgame();
};

