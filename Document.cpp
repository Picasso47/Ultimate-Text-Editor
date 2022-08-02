#pragma once
#include<iostream>
#include<fstream>
#include<Windows.h>
#include<conio.h>
#include<string>
#include "Lines.h"
#include "Document.h"
#include "TextEditor.h"
#define RED 4
#define WHITE 15
#define BLINK 1286
#define LIGHTGREY 7
using namespace std;
void gotoRowCol_docu(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void setclr_docu(int clr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}
Document::Document()
{
	NOLs = 1;
	Ls = new Lines[1];
}
Document::Document(int nols)
{
	NOLs = nols;
	Ls = new Lines[NOLs];
}
Document::Document(Document& AD)
{
	this->NOLs=AD.NOLs;
	this->Ls = new Lines[this->NOLs];
	for (int i = 0; i < this->NOLs; i++)
	{
		for (int z = 0;z<AD.Ls[i].Size; z++)
		{
				this->Ls[i].insertCharAt_i(this->Ls[i].Cs[z + 1], AD.Ls[i].Cs[z]);
				if(i== AD.Ls[i].Size-1)
					this->Enter_AddNewLine(i, z + 1);
				if (i == AD.Ls[i].Size - 1 && i==this->NOLs-1)
					this->Ls[i].insertCharAt_i(this->Ls[i].Cs[z + 1], '\0');
		}

	}
}

void Document::load(string fname)
{
	bool pass = false;
	string a;
	string b;
	gotoRowCol_docu(0, 0);
	ifstream rdr(fname);
	rdr >> this->NOLs;
	this->Ls = new Lines[this->NOLs];
	rdr >> pass;
	if (pass)
	{
		rdr >> a;
		do
		{
			system("cls");
			cout << "Enter Password :";
			cin >> b;
		} while ((a != b));	
	}
	for (int i = 0; i < 1; i++)
		rdr.ignore();
	for (int i = 0; i < this->NOLs; i++)
	{	
		for (int z = 0;; z++)
		{
			char *s=new char[1];
			rdr.read(s, 1);
			if (s[0] != '\n')
			this->Ls[i].insertCharAt_i(this->Ls[i].Cs[z+1], s[0]);
			if ( (s[0] == '\n') || (s[0]== 'Í'))
			{
				this->Ls[i].insertCharAt_i(this->Ls[i].Cs[z + 1], '\0');
				this->Enter_AddNewLine(i,z+1);
				this->Ls->Size--;
				this->NOLs--;
				break;
			}
		}
	}
	PrintDocument();
}
void Document::LoadEncodedFile(string Fname)
{
	gotoRowCol_docu(0, 0);
	ifstream rdr(Fname);
	rdr >> this->NOLs;
	this->NOLs -= 786969;
	this->Ls = new Lines[this->NOLs];
	for (int i = 0; i < 1; i++)
		rdr.ignore();
	for (int i = 0; i < this->NOLs; i++)
	{
		for (int z = 0;; z++)
		{
			char* s = new char[1];
			rdr.read(s, 1);
			s[0] += 5;
			if (s[0] != -106)
				this->Ls[i].insertCharAt_i(this->Ls[i].Cs[z + 1], s[0]);
			if ((s[0] == -106))
			{
				this->Ls[i].insertCharAt_i(this->Ls[i].Cs[z + 1], '\0');
				this->Enter_AddNewLine(i, z + 1);
				this->NOLs--;
				rdr.ignore();
				break;
			}
		}
	}
	PrintDocument();
}
void Document:: SimpleUpdater(string fname)
{
	gotoRowCol_docu(0, 0);
	ofstream wtr(fname);
	wtr << this->NOLs;
	wtr << endl;
	for (int i = 0; i < this->NOLs; i++)
	{
		this->Ls[i].Writer(wtr);
		wtr << endl;
	}
	PrintDocument();
}
void Document::SaveasEncodedFile(string Fname)
{
	gotoRowCol_docu(0, 0);
	ofstream wtr(Fname);
	wtr << this->NOLs + 786969;
	wtr << endl;
	for (int i = 0; i < this->NOLs; i++)
	{
		this->Ls[i].EncodedWriter(wtr);
		wtr << endl;
	}
	PrintDocument();
}
void Document::Enter_AddNewLine(int ri, int ci)
{
	Lines* tl = new Lines[NOLs+1];
	int i = 0;
	int x = 0;
	for ( i = 0; i < ri; i++,x++)
	{
		tl[i] = this->Ls[i];
	}
	Lines* temp1 = new Lines[2];
	for (int y = 0; y < ci ; y++)
	{
		temp1[0].insertCharAt_i(y,this->Ls[i].Cs[y]);
		if (y == ci - 1)
		{
			y++;
			temp1->Cs[y] = '\0';
		}
	}
	for (int y = ci,ni=0; this->Ls[i].Cs[y] != '\0'; ni++, y++)
	{
		temp1[1].insertCharAt_i(y,this->Ls[i].Cs[y]);
		if (this->Ls[i].Cs[y + 1] == '\0')
		{
			ni++;
			temp1[1].Cs[ni] = '\0';
		}
	}

	for (int z = 0; z < 2; z++,x++)
	{
		tl[x] = temp1[z];
	}
	i++;
	for (; i < NOLs; i++,x++)
	{
		tl[x] = this->Ls[i];
	}
	this->Ls[ri].~Lines();
	this->Ls = tl;
	NOLs++;
}
void Document::BackSpace_LineRemover(int Ln,int& row_p)
{
	Lines* tl = new Lines[NOLs];
	int i = 0;
	int x = 0;
	int y = 0;
	int wrdcntr = 0;
	bool allow = false;
	bool linedel = false;
	for (i = 0; i < Ln - 1; i++, x++)
	{
		tl[i] = this->Ls[i];
	}
	for (int c = 0; ((this->Ls[i + 1].Cs[c] != '\0') && (this->Ls[i + 1].Cs[c] != ' ')); c++,wrdcntr++)
	{
	}
	allow=(this->Ls[i].Size+wrdcntr<=80?true:false);
		if (allow)
		{
			for (int p = 0; p < this->Ls[i].Size; p++)
				tl[x].insertCharAt_i(p, this->Ls[i].Cs[p]);
				for (int g = 0,m=1; g < wrdcntr; g++,m++)
				{
					if (m == 1)
					{
						tl[x].insertCharAt_i(tl[x].Size, ' ');
						g--;
						continue;
					}
					tl[x].insertCharAt_i(tl[x].Size+g,this->Ls[i+1].Cs[g]);
				}
				//linedel = (this->Ls[i + 1].Size == wrdcntr+2 ? true : false);
				i++;
				for (int g = 1,p=0; p <= wrdcntr;p++)
				{
					this->Ls[i ].CharRemoverAt_i(g);
					if (this->Ls[i].Cs[g] == '\0' || this->Ls[i].Cs[g - 1] == '\0')
						linedel = true;
				}
				if (!linedel)
				{
					x++;
					for (int b = wrdcntr+1, h = 0; h < this->Ls[i].Size-2; b++, h++)
					{
						tl[x].insertCharAt_i(h, this->Ls[i].Cs[h]);
					}
					x++; i++;
			    }
				else
				{
					x++; i++;
				}
		}
		if (linedel)
		{
			//this->Ls[Ln - 1].~Lines();
			this->Ls[Ln].~Lines();
			NOLs--;
		}
	for (; i <= NOLs ; i++, x++)
	{
		tl[x] = this->Ls[i];
	}
	this->Ls = tl;
}
void Document::FindCaseSens(string Tofind)
{
	for (int i = 0; i < NOLs; i++)
	{
		int size = 0;
		gotoRowCol_docu(0, 0);
		int* ptr=this->Ls[i].SubStrings(Tofind,size);
		for (int y = 0; y < size; y++)
		{
			gotoRowCol_docu(i, ptr[y]);
			setclr_docu(RED);
			cout << Tofind;
		}
		delete ptr;
	}
	setclr_docu(LIGHTGREY);
}
void Document::FindInCaseSens(string Tofind)
{
	for (int i = 0; i < NOLs; i++)
	{
		int size = 0;
		gotoRowCol_docu(0, 0);
		int* ptr = this->Ls[i].IncaseSubStrings(Tofind, size);
		for (int y = 0; y < size; y++)
		{
			gotoRowCol_docu(i, ptr[y]);
			for (int z = 0; z < Tofind.length(); z++)
			{
				setclr_docu(RED);
				cout << this->Ls[i].Cs[ptr[y] + z];
			}
		}
		delete ptr;
	}
	setclr_docu(LIGHTGREY);
}
int Document::SmallestWordLen()
{
	int smol_len = 0;
	int first_len = 0;
	bool first_word = true;
	bool first_cycle = true;
	for (int i = 0; i < NOLs; i++)
	{
		for (int y = 0;y< this->Ls[i].Size-1; y++)
		{
			int non_first_len = 0;
			for (; ( (this->Ls[i].Cs[y] != '\0') && (this->Ls[i].Cs[y] != ',') && (this->Ls[i].Cs[y] != '.') && (this->Ls[i].Cs[y] != ' ') ); y++)
			{
				if (first_word)
					first_len++;
				if (!first_word)
					non_first_len++;
			}
			first_word = false;
			if (first_cycle)
				smol_len = first_len;
			if (!first_cycle)
			{
				if ( (non_first_len < smol_len) && non_first_len!=0 )
					smol_len = non_first_len;
			}
			first_cycle = false;
		}

	}
	setclr_docu(LIGHTGREY);
	return smol_len;
}
int Document::LargestWordLength()
{
	int largest_len = 0;
	int first_len = 0;
	bool first_word = true;
	bool first_cycle = true;
	for (int i = 0; i < NOLs; i++)
	{
		for (int y = 0; y < this->Ls[i].Size - 1; y++)
		{
			int non_first_len = 0;
			for (; ((this->Ls[i].Cs[y] != '\0') && (this->Ls[i].Cs[y] != ',') && (this->Ls[i].Cs[y] != '.') && (this->Ls[i].Cs[y] != ' ')); y++)
			{
				if (first_word)
					first_len++;
				if (!first_word)
					non_first_len++;
			}
			first_word = false;
			if (first_cycle)
				largest_len = first_len;
			if (!first_cycle)
			{
				if ((non_first_len > largest_len) && non_first_len != 0)
					largest_len = non_first_len;
			}
			first_cycle = false;
		}

	}
	setclr_docu(LIGHTGREY);
	return largest_len;
}
int Document::WordCount()
{
	
	int wc = 0;
	for (int i = 0; i < NOLs; i++)
	{
		for (int y = 0; y < this->Ls[i].Size - 1; y++)
		{
			int non_first_len = 0;
			for (; ((this->Ls[i].Cs[y] != '\0') && (this->Ls[i].Cs[y] != ',') && (this->Ls[i].Cs[y] != '.') && (this->Ls[i].Cs[y] != ' ')); y++)
			{
				
			}
			wc++;
		}
	}
	setclr_docu(LIGHTGREY);
	return wc;
}
double Document::AvgWordLen()
{
	double wc = 0;
	double lc = 0;
	for (int i = 0; i < NOLs; i++)
	{
		for (int y = 0; y < this->Ls[i].Size - 1; y++)
		{
			int non_first_len = 0;
			for (; ((this->Ls[i].Cs[y] != '\0') && (this->Ls[i].Cs[y] != ',') && (this->Ls[i].Cs[y] != '.') && (this->Ls[i].Cs[y] != ' ')); y++)
			{
				lc++;
			}
			wc++;
		}
	}
	setclr_docu(LIGHTGREY);
	wc = lc / wc;
	return wc;
}
int Document::SpecialCharCount()
{
	int spec_char = 0;
	for (int i = 0; i < NOLs; i++)
	{
		for (int y = 0; y < this->Ls[i].Size - 1; y++)
		{
			if ( ((this->Ls[i].Cs[y] > 57) || (this->Ls[i].Cs[y] < 48)) && ((this->Ls[i].Cs[y] < 65) || (this->Ls[i].Cs[y] > 90) ) && this->Ls[i].Cs[y]!=' ' &&((this->Ls[i].Cs[y] > 122) || (this->Ls[i].Cs[y] < 97)))
				spec_char++;
		}

	}
	setclr_docu(LIGHTGREY);
	return spec_char;
}
int Document::SentencesCount()
{
	int sen_cnt = 0;
	char q = '?';
	char e = '!';
	char p = '.';
	for (int i = 0; i < NOLs; i++)
	{
		for (int y = 0; y < this->Ls[i].Size - 1; y++)
		{
			if(((this->Ls[i].Cs[y]=='.') || (this->Ls[i].Cs[y] == '!') || (this->Ls[i].Cs[y] == '?')) && ( ((this->Ls[i].Cs[y-1]) != this->Ls[i].Cs[y]) && ((this->Ls[i].Cs[y + 1]) != (this->Ls[i].Cs[y]))))
				sen_cnt++;
			if((( this->Ls[i].Cs[y+1] == ' ') || (this->Ls[i].Cs[y + 1] == '\0')) && (((this->Ls[i].Cs[y] == '.') && ((this->Ls[i].Cs[y - 1] == '?') || (this->Ls[i].Cs[y - 1] == '!')))))
				sen_cnt--;
			if ((( (this->Ls[i].Cs[y] == '?') && ((this->Ls[i].Cs[y - 1] == '!')|| (this->Ls[i].Cs[y + 1] == '!')))))
				sen_cnt--;
			if ((((this->Ls[i].Cs[y] == '!') && ((this->Ls[i].Cs[y - 1] == '?')|| (this->Ls[i].Cs[y + 1] == '?')))))
				sen_cnt--;
		}

	}

	setclr_docu(LIGHTGREY);
	return sen_cnt;
}
int Document::paragraphcount()
{
	int para_cnt = 0;
	char q = '?';
	char e = '!';
	char p = '.';
	for (int i = 0; i < NOLs; i++)
	{
		for (int y = 0; y < this->Ls[i].Size - 1; y++)
		{
			if (((this->Ls[i].Size==2)))
				para_cnt++;
		}
	}

	setclr_docu(LIGHTGREY);
	return para_cnt;
}
void Document::PrintDocument()
{
	gotoRowCol_docu(0, 0);
	system("cls");
	for ( int z = 0; z < NOLs; z++)
	{
		this->Ls[z].PrintLine(0);
		cout  << endl;
	}
}
void Document::wordgame()
{
	string toFind;
	system("cls");
	cout << "Enter the word for word game";
	cin >> toFind;
	int* Ptr = nullptr;
	int strsize = toFind.length();
	for (int y = 0; y < this->NOLs; y++)
	{
		int i = 0;
		for (; i < this->Ls[y].Size; i++)//for line
		{
			bool subfound = true;
			for (int z = 0; z < strsize; z++)//for string to be found
			{
				if (this->Ls[y].Cs[i] != toFind[z])
				{
					subfound = false;
					break;
				}
				i++;
			}
			if (subfound)
			{
				i -= strsize;
				for (;this->Ls[y].Cs[i] != ' ' ; i++)
				{
					if (i > this->Ls[y].Size)
						break;
					cout << this->Ls[y].Cs[i];
				}
				cout << '\n';
			}
		}
	}
}
void Document::Prefix(string Tofind, string PreFix)
{
	int size = 0;
	for (int cri = 0; cri < NOLs; cri++)
	{
		int* ptr = this->Ls[cri].SubStrings(Tofind, size);
		this->Ls[cri].AddPrefix(Tofind, PreFix, ptr, size);
		gotoRowCol_docu(cri, 0);
		this->Ls[cri].PrintLine(0);
	}
	
}
void Document::PostFix(string Tofind, string PostFix)
{
	int size = 0;
	for (int cri = 0; cri < NOLs; cri++)
	{
		int* ptr = this->Ls[cri].SubStrings(Tofind, size);
		this->Ls[cri].AddPostfix(Tofind, PostFix, ptr, size);
		gotoRowCol_docu(cri, 0);
		this->Ls[cri].PrintLine(0);
	}
}
void Document::FindAndReplaceFirst(string tofind, string toreplace)
{
	bool replaced = false;
	for (int i = 0; i < NOLs; i++)
	{
		if(!replaced)
		{
			this->Ls[i].Replacefirst(tofind, toreplace,replaced);
		}
	}
	PrintDocument();
}
void Document::FindReplaceNext(string find, string replace, int cr, int cc)
{
	bool replaced = false;
	int pos = 0;
	for (int i = cr; i < NOLs; i++)
	{
		if (replaced)
			break;
		if (!replaced)
		{
			this->Ls[i].FindAndReplaceNextOnly(find, replace,cc,pos, replaced);
		}
		if (i < NOLs - 1)
			cc = 0;
	}
	PrintDocument();
}
void Document::FindReplacePrev(string find, string replace, int cr, int cc)
{
	bool replaced = false;
	int pos = 0;
	for (int i = cr; i >= 0; i--)
	{
		if (replaced)
			break;
		if (!replaced)
		{
			this->Ls[i].FindAndReplacePrevOnly(find, replace, cc, pos, replaced);
		}
		if (i > 0)
		{
			cc = this->Ls[i - 1].Size;
		}
	}
	PrintDocument();
}
void Document::FindAndReplaceAll(string tofind, string toreplace)
{
	for (int i = 0; i < NOLs; i++)
	{
		this->Ls[i].ReplaceAll(tofind, toreplace);
	}
	PrintDocument();
}
void Document::FindReplaceAllNext(string find, string replace, int cr, int cc)
{
	for (int i = cr; i < NOLs; i++)
	{
		if(i==cr)
		this->Ls[i].FindAndReplaceNextAll(find, replace, cc);
		cc = 0;
	}
	PrintDocument();
}
void Document::FindReplaceAllPrev(string find, string replace, int cr, int cc)
{
	for (int i = cr; i >=0; i--)
	{
		if (i == cr)
			this->Ls[i].FindAndReplacePrevAll(find, replace, cc);
        if(i!=cr)
			this->Ls[i].FindAndReplacePrevAll(find, replace, cc);
		if (i > 0)
		{
			cc = this->Ls[i - 1].Size;
		}
	}
	PrintDocument();
}
void Document::FindingSentence(string a)
{
	int* Ptr = nullptr;
	int size = 0;
	int v = 0;
	int findstrsize = a.length();
	for (int i = 0; i < NOLs; i++)
	{
		int* ptrl1 = new int[2];
		int* ptrl2 = new int[2];
			for (int x = 0; x < strlen(this->Ls[i].Cs); x++)
			{
				bool subfound = true;
				bool moreline = false;
				int ifmorelinecntr = 0;
				for (int z = 0; z < findstrsize; z++)
				{
					if ((this->Ls[i].Cs[x] != a[z]) && this->Ls[i].Cs[x]!='\0')
					{
						subfound = false;
						break;
					}
					if (z > 0 && this->Ls[i].Cs[x] == '\0')
					{
						i++;
						ptrl1[1] = x;
						x -= ifmorelinecntr;
						ptrl1[0] = x;
						x = 0;
						moreline=true;
						ifmorelinecntr = 0;
						z--;
						continue;
					}
					ifmorelinecntr++;
					x++;
				}
				if (subfound && moreline)
				{
					for (int d = ptrl1[0]; d < ptrl1[1]; d++)
					{
						gotoRowCol_docu(i-1, d);
						setclr_docu(RED);
						cout << this->Ls[i-1].Cs[d];
					}
					ptrl2[1] = x;
					ptrl2[0]=x-ifmorelinecntr;
					for (int d = ptrl2[0]; d < ptrl2[1]; d++)
					{
						gotoRowCol_docu(i, d);
						setclr_docu(RED);
						cout << this->Ls[i].Cs[d];
					}
				}
				if (subfound && !moreline )
				{
					x -= findstrsize;
				    v = x;
				}
				if (subfound && !moreline)
				{
					x += findstrsize - 1;
					setclr_docu(RED);
					gotoRowCol_docu(i, v);
					cout << a;
				}
			}
	}
	setclr_docu(LIGHTGREY);\
}
void Document::ExitDocument()
{
	for (int i = 0; i < NOLs; i++)
	{
		this->Ls[i].~Lines();
	}
}
Document::~Document()
{
	delete[]Ls;
}