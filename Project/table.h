#ifndef TABLE_H
#define TABLE_H
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "filesys.h"


class Table : public Filesys
{
public:
    Table(string diskname, int numberofblocks, int blocksize, string flatfile, string indexfile);
    int Build_Table(string input_file);
    int Search(string value);
private:
    string flatfile;
    string indexfile;
    int numofrecords; 
    // Filesys filesystem;
    int IndexSearch(string value);
};

#endif