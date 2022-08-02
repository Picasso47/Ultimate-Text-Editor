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
class Lines
{
private:
	friend class TextEditor;
	friend class Document;
	char* Cs;
	int Size;
public:

	Lines();
	int strLEN(const Lines A);
	Lines(const Lines& A);
	bool sizelimit()const;
	void insertCharAt_i(int i, char ch);
	void PrintLine(int cci);
	void CharRemoverAt_i(int i);
	void ToUpper(int li, int ci);
	void ToLower(int li, int ci);
	int* SubStrings(string Tofind, int& size);
	int* IncaseSubStrings(string Tofind, int& size);
	void AddPrefix(string ToFind, string Prefix, int* ptr, int size);
	void AddPostfix(string ToFind, string Prefix, int* ptr, int size);
	void Replacefirst(string toFind, string toReplace,bool& foundandreplace);
	void ReplaceAll(string toFind, string toReplace);
	int FindNextOnly(string toFind, int ccpos);
	int FindPrevOnly(string toFind, int ccpos);
	int* FindNextAll(string toFind, int ccpos, int& size);
	int* FindPrevAll(string toFind, int ccpos, int& size);
	void FindAndReplaceNextOnly(string toFind, string toReplace, int ccpos, int& pos,bool&replace);
	void FindAndReplacePrevOnly(string toFind, string toReplace, int ccpos, int& pos,bool& replace);
	void FindAndReplaceNextAll(string toFind, string toReplace, int ccpos);
	void FindAndReplacePrevAll(string toFind, string toReplace, int ccpos);
	void Writer(ofstream& wtr);
	void EncodedWriter(ofstream& wtr);
	int smallestwordlenline();
	int givelent();
	~Lines();
};

