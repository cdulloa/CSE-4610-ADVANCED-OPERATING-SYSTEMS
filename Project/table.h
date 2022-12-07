#ifndef TABLE_H
#define TABLE_H
#include<iostream>
#include<string>
#include<sstream>
#include<cstdlib>
#include "Filesys.h"
#include "Sdisk.h"
using namespace std;

class Table : public Filesys
{
public:
    Table(string diskname, string flatfile, string indexfile, int numberofblocks);
    int Build_Table(string input_file);
    int Search(string value);
private:
    string flatfile;
    string indexfile;
    int numberofrecords; 
    Filesys filesystem;
    int IndexSearch(string value);
};

#endif