#include "Lines.h"
#include<iostream>
#include<fstream>
#include<Windows.h>
#include<conio.h>
#include<string>

using namespace std;
Lines::Lines()
{
	Size = 1;
	Cs = new char[1]{ '\0' };
}
Lines ::Lines(const Lines& A)
{
	Size = strLEN(A);
	Cs = new char[Size + 1];
	for (int h = 0; h <= Size; h++)
	{
		Cs[h] = A.Cs[h];
	}
}
int Lines::strLEN(const Lines A)
{
	if (A.Cs == nullptr)
		return 0;
	int c = 0;
	while (A.Cs[c] != '\0')
	{
		c++;
	}
	return c;
}
int Lines::givelent()
{
	return strlen(Cs);

}
 void Lines::insertCharAt_i(int inpos, char ch)
 {
 	int a= strlen(Cs);
	 char* HA = new char[strlen(Cs) + 3];
	 int newi = 0, i = 0;
	 for (i = 0; i < strlen(Cs); i++, newi++)
	 {
		 if (i == inpos)
			 break;
		 HA[newi] = Cs[i];
	 }
	 HA[newi] = ch;
	 newi++;
	 for (;i<=strlen(Cs);i++,newi++)
		 HA[newi] = Cs[i];
	 Size++;
	 delete[]Cs;
	 Cs = HA;
 }
 void Lines::CharRemoverAt_i(int inpos)
 {
	 if (this->Cs[inpos - 1] != '\0' && this->Size > 0)
	 {
		 int a = strlen(Cs);
		 char* HA = new char[strlen(Cs)];
		 int newi = 0, i = 0;
		 for (i = 0; i < strlen(Cs); i++, newi++)
		 {
			 if (i + 1 == inpos)
				 break;
			 HA[newi] = Cs[i];
		 }
		 i++;
		 for (; i <= strlen(Cs); i++, newi++)
			 HA[newi] = Cs[i];
		 delete[]Cs;
		 Size--;
		 Cs = HA;
	 }

 }
 void Lines::ToUpper(int li, int ci)
 {
	 for (int i = ci; (Cs[i] != ' ' && Cs[i] != '\0'); i++)
	 {
		 if (Cs[i] >= 'a' && Cs[i] <= 'z')
			 Cs[i] -= 32;
	}
	 for (int i = ci; (Cs[i] != ' ' && Cs[i] != '\0'); i--)
	 {
		 if (Cs[i] >= 'a' && Cs[i] <= 'z')
			 Cs[i] -= 32;
	 }
 }
 void Lines::ToLower(int li, int ci)
 {
	 for (int i = ci; (Cs[i] != ' ' && Cs[i] != '\0'); i++)
	 {
		 if (Cs[i] >= 'A' && Cs[i] <= 'Z')
			 Cs[i] += 32;
	 }
	 for (int i = ci; (Cs[i] != ' ' && Cs[i] != '\0'); i--)
	 {
		 if (Cs[i] >= 'A' && Cs[i] <= 'Z')
			 Cs[i] += 32;
	 }
 }
 bool Lines::sizelimit()const
 {
	 if (this->Size <= 80)
		 return false;
	 else
		 return true;
 }
 int* Lines::SubStrings(string Tofind,int& size)
 {
	 int* Ptr = nullptr;
	 size = 0;
	 int strsize = Tofind.length();
	 for (int i = 0; i < strlen(Cs); i++)
	 {
		 bool subfound = true;
		 for (int y = 0; y < strsize; y++)
		 {
			 if (Cs[i] != Tofind[y])
			 {
				 subfound = false;
				 break;
			 }
			 i++;
		 }
		 if (subfound)
		 {
			 i -= strsize;
					 int* Hptr = new int[size + 1];
					 for (int z = 0; z < size; z++)
						 Hptr[z] = Ptr[z];
					 Hptr[size] = i;
					 size++;
					 delete[]Ptr;
					 Ptr = Hptr;
			i += strsize-1;
		 }
	 }

	 return Ptr;
 }
 int* Lines::IncaseSubStrings(string Tofind, int& size)
 {
	 int* Ptr = nullptr;
	 size = 0;
	 int strsize = Tofind.length();
	 for (int i = 0; i < strlen(Cs); i++)
	 {
		 bool subfound = true;
		 for (int y = 0; y < strsize; y++)
		 {
			 if ( (Cs[i] != Tofind[y]) && ( ((Cs[i] != (Tofind[y] - 32)) && (Cs[i] != (Tofind[y] + 32))) ) )
			 {
				 subfound = false;
				 break;
			 }
			 i++;
		 }
		 if (subfound)
		 {
			 i -= strsize;
			 int* Hptr = new int[size + 1];
			 for (int z = 0; z < size; z++)
				 Hptr[z] = Ptr[z];
			 Hptr[size] = i;
			 size++;
			 delete[]Ptr;
			 Ptr = Hptr;
			 i += strsize - 1;
		 }
	 }

	 return Ptr;
 }
 void Lines::Replacefirst(string toFind, string toReplace,bool & foundandreplace)
 {
	 int findstrsize = toFind.length();
	 int rplcstrsize=toReplace.length();
	  foundandreplace = false;
	 for (int i = 0; i < strlen(Cs); i++)
	 {
		 bool subfound = true;
		 for (int y = 0; y < findstrsize; y++)
		 {
			 if (Cs[i] != toFind[y])
			 {
				 subfound = false;
				 break;
			 }
			 i++;
		 }
		 if (subfound)
		 {
			 i -= findstrsize;
			 for (int y = 0; y < findstrsize; y++)
			 {
				 CharRemoverAt_i(i);
			 }
			 for (int y = 0; y < rplcstrsize; y++)
			 {
				 insertCharAt_i(i,toReplace[y]);
				 i++;
				 if (y == 0)
					 foundandreplace = true;
			 }
			 break;
		 }
	 }
 }
 void Lines::ReplaceAll(string toFind, string toReplace)
 {
	 int findstrsize = toFind.length();
	 int rplcstrsize = toReplace.length();
	 for (int i = 0; i < strlen(Cs); i++)
	 {
		 bool subfound = true;
		 for (int y = 0; y < findstrsize; y++)
		 {
			 if (Cs[i] != toFind[y])
			 {
				 subfound = false;
				 break;
			 }
			 i++;
		 }
		 if (subfound)
		 {
			 i -= findstrsize;
			 for (int y = 0; y < findstrsize; y++)
			 {
				 CharRemoverAt_i(i);
			 }
			 for (int y = 0; y < rplcstrsize; y++)
			 {
				 insertCharAt_i(i, toReplace[y]);
				 i++;
			 }
		 }
	 }
 }
 void Lines::AddPrefix(string ToFind, string Prefix,int* ptr,int size)
 {
	 int findstrsize = ToFind.length();
	 int pfxstrsize = Prefix.length();
	 int plus_cntr = 0;
	 for (int i = 0; i < size; i++)
	 {
		 int y = ptr[i]+ plus_cntr;
		 for (int z = y,k=0; k < pfxstrsize; z++,k++)
		 {
				 insertCharAt_i(z, Prefix[k]);
				 plus_cntr++;
				 if (k == pfxstrsize - 1)
				 {
					 z++;
					 insertCharAt_i(z, ' ');
					 plus_cntr++;
				 }
		 }
	 }
 }
 void Lines::AddPostfix(string ToFind, string Prefix, int* ptr, int size)
 {
	 int findstrsize = ToFind.length();
	 int pfxstrsize = Prefix.length();
	 int plus_cntr = 0;
	 for (int i = 0; i < size; i++)
	 {
		 int y = ptr[i] + plus_cntr + findstrsize;
		 for (int z = y, k = 0; k < pfxstrsize; z++, k++)
		 {
			 if (k == 0)
			 {
				 insertCharAt_i(z, ' ');
				 plus_cntr++;
				 z++;
			 }
			 insertCharAt_i(z, Prefix[k]);
			 plus_cntr++;
		 }
	 }
 }
 int Lines::FindNextOnly(string toFind,int ccpos)
 {
	 int findstrsize = toFind.length();
	 for (int i = ccpos; i < strlen(Cs); i++)
	 {
		 bool subfound = true;
		 for (int y = 0; y < findstrsize; y++)
		 {
			 if (Cs[i] != toFind[y])
			 {
				 subfound = false;
				 break;
			 }
			 i++;
		 }
		 if (subfound)
		 {
			 i -= findstrsize;
			 return i;
		 }
	 }
	 return NULL;
 }
 int Lines::FindPrevOnly(string toFind, int ccpos)
 {
	 int findstrsize = toFind.length();
	 for (int i = ccpos; i >= 0; i--)
	 {
		 bool subfound = true;
		 for (int y = findstrsize-1; y >= 0; y--)
		 {
			 if (Cs[i] != toFind[y])
			 {
				 subfound = false;
				 break;
			 }
			 i--;
		 }
		 if (subfound)
		 {
			 i += 1;
			 return i;
		 }
	 }
	 return NULL;
 }
 int* Lines::FindNextAll(string toFind, int ccpos,int& size)
 {
	 int* Ptr = nullptr;
	 size = 0;
	 int strsize = toFind.length();
	 for (int i = ccpos; i < strlen(Cs); i++)
	 {
		 bool subfound = true;
		 for (int y = 0; y < strsize; y++)
		 {
			 if (Cs[i] != toFind[y])
			 {
				 subfound = false;
				 break;
			 }
			 i++;
		 }
		 if (subfound)
		 {
			 i -= strsize;
			 int* Hptr = new int[size + 1];
			 for (int z = 0; z < size; z++)
				 Hptr[z] = Ptr[z];
			 Hptr[size] = i;
			 size++;
			 delete[]Ptr;
			 Ptr = Hptr;
			 i += strsize - 1;
		 }
	 }
	 return Ptr;
 }
 int* Lines::FindPrevAll(string toFind, int ccpos, int& size)
 {
	 int* Ptr = nullptr;
	 size = 0;
	 int findstrsize = toFind.length();
	 for (int i = ccpos; i >=0; i--)
	 {
		 bool subfound = true;
		 for (int y = findstrsize - 1; y >= 0; y--)
		 {
			 if (Cs[i] != toFind[y])
			 {
				 subfound = false;
				 break;
			 }
			 i--;
		 }
		 if (subfound)
		 {
			 i += 1;
			 int* Hptr = new int[size + 1];
			 for (int z = 0; z < size; z++)
				 Hptr[z] = Ptr[z];
			 Hptr[size] = i;
			 size++;
			 delete[]Ptr;
			 Ptr = Hptr;
			 i -= 1;
		 }
	 }
	 return Ptr;
 }
 void Lines::FindAndReplaceNextOnly(string toFind,string toReplace, int ccpos,int& pos,bool&replace)
 {
	 int findstrsize = toFind.length();
	 int rplcstrsize = toReplace.length();
	 bool subfound = true;
	 int i = ccpos;
	 for (i = ccpos; i < strlen(Cs); i++)
	 {
		 subfound = true;
		 for (int y = 0; y < findstrsize; y++)
		 {
			 if (Cs[i] != toFind[y])
			 {
				 subfound = false;
				 break;
			 }
			 i++;
		 }
		 if (subfound)
		 {
			 i -= findstrsize;
			 for (int y = 0; y < findstrsize; y++)
			 {
				 CharRemoverAt_i(i);
			 }
			 for (int y = 0; y < rplcstrsize; y++)
			 {
				 insertCharAt_i(i, toReplace[y]);
				 i++;
				 if (y == 0)
					 replace = true;
			 }
			 i -= rplcstrsize;
			 break;
		 }
	 }
	 pos = i;
 }
 void Lines::FindAndReplacePrevOnly(string toFind, string toReplace, int ccpos, int& pos,bool& replace)
 {
	 int findstrsize = toFind.length();
	 int rplcstrsize = toReplace.length();
	 int i = ccpos;
	 for (i = ccpos; i >=0; i--)
	 {
		 bool subfound = true;
		 for (int y = findstrsize - 1; y >= 0; y--)
		 {
			 if (Cs[i] != toFind[y])
			 {
				 subfound = false;
				 break;
			 }
			 i--;
		 }
		 if (subfound)
		 {
			 i += 1;
			 for (int y = 0; y < findstrsize; y++)
			 {
				 CharRemoverAt_i(i);
			 }
			 for (int y = 0; y < rplcstrsize; y++)
			 {
				 insertCharAt_i(i, toReplace[y]);
				 i++;
				 if (y == 0)
					 replace = true;
			 }
			 break;
		 }
	 }
	 pos = i;
 }
 void Lines::FindAndReplaceNextAll(string toFind, string toReplace, int ccpos)
 {
	 int* Ptr = nullptr;
	 int size = 0;
	 int findstrsize = toFind.length();
	 int rplcstrsize = toReplace.length();
	 for (int i = ccpos; i < strlen(Cs); i++)
	 {
		 bool subfound = true;
		 for (int y = 0; y < findstrsize; y++)
		 {
			 if (Cs[i] != toFind[y])
			 {
				 subfound = false;
				 break;
			 }
			 i++;
		 }
		 if (subfound)
		 {
			 i -= findstrsize;
			 int* Hptr = new int[size + 1];
			 for (int z = 0; z < size; z++)
				 Hptr[z] = Ptr[z];
			 Hptr[size] = i;
			 size++;
			 delete[]Ptr;
			 Ptr = Hptr;
		 }
		 if (subfound)
		 {
			 for (int y = 0; y < findstrsize; y++)
			 {
				 CharRemoverAt_i(i);
			 }
			 for (int y = 0; y < rplcstrsize; y++)
			 {
				 insertCharAt_i(i, toReplace[y]);
				 i++;
			 }
			 i += findstrsize - 1;
		 }
	 }
 }
 void Lines::FindAndReplacePrevAll(string toFind, string toReplace, int ccpos)
 {
	 int* Ptr = nullptr;
	 int size = 0;
	 int findstrsize = toFind.length();
	 int rplcstrsize = toReplace.length();
	 for (int i = ccpos; i >= 0; i--)
	 {
		 bool subfound = true;
		 for (int y = findstrsize - 1; y >= 0; y--)
		 {
			 if (Cs[i] != toFind[y])
			 {
				 subfound = false;
				 break;
			 }
			 i--;
		 }
		 if (subfound)
		 {
			 i++;
			 int* Hptr = new int[size + 1];
			 for (int z = 0; z < size; z++)
				 Hptr[z] = Ptr[z];
			 Hptr[size] = i;
			 size++;
			 delete[]Ptr;
			 Ptr = Hptr;
		 }
		 if (subfound)
		 {
			 for (int y = 0; y < findstrsize; y++)
			 {
				 CharRemoverAt_i(i);
			 }
			 for (int y = 0; y < rplcstrsize; y++)
			 {
				 insertCharAt_i(i, toReplace[y]);
				 i++;
			 }
			 i -= rplcstrsize -2;
		 }
	 }
 }
 int Lines::smallestwordlenline()
 {
	 int len = 0;
	 int first_len = 0;
	 int non_first_len = 0;
	 bool first_word = true;
	 bool first_cycle = true;
	 for (int i = 0; this->Cs[i] != '\0';)
	 {
		 for (; ((this->Cs[i] != '\0') || (this->Cs[1] != ',') || (this->Cs[i] != '.') || (this->Cs[i] != ' ')); i++)
		 {
			 if (first_word)
				 first_len++;
			 if (!first_word)
				 non_first_len++;
		 }
		 first_word = false;
		 if (first_cycle)
			 len = first_len;
		 if (!first_cycle)
		 {
			 if (non_first_len < first_len)
				 len = non_first_len;
		 }
		 first_cycle = false;
	 }
	 return len;
 }
 void Lines::Writer(ofstream& wtr)
 {
	 for (int i = 0; this->Cs[i]!='\0'; i++)
		 wtr << this->Cs[i];
 }
 void Lines::EncodedWriter(ofstream& wtr)
 {
	 for (int i = 0; this->Cs[i] != '\0'; i++)
	 {
		 char s;
		 if(this->Cs[i] != '\0')
		 s = this->Cs[i] - 5;
		 wtr << s;
		 if (this->Cs[i+1] == '\0')
		 {
			 s = 145;
			 wtr << s;
		 }
	 }
 }
 void Lines::PrintLine(int cci)
 {
	 int i = cci;
	 for (i = cci; i < strlen(Cs); i++)
	 {
		 cout << Cs[i];
	 }
	 for (i = strlen(Cs); i <= 80; i++)
	 {
		 cout << " ";
	 }
 }
 Lines::~Lines()
 {
	 Size = 0;
	 delete[]Cs;
 }