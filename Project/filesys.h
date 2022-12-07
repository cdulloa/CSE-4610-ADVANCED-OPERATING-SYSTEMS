#ifndef FILESYS_H
#define FILESYS_H
#include <string>
#include <vector>
#include "sdisk.h"

class Filesys : public Sdisk
{
public:
    Filesys(string diskname, int numberofblocks, int blocksize);
    int fsclose();
    int newfile(string file);
    int rmfile(string file);
    int getfirstblock(string file);
    int addblock(string file, string block);
    int delblock(string file, int blocknumber);
    int readblock(string file, int blocknumber, string &buffer);
    int writeblock(string file, int blocknumber, string buffer);
    int nextblock(string file, int blocknumber);

    vector<string> ls(); // saves names of files in ROOT to a vector

private:
    int rootsize;            // maximum number of entries in ROOT
    int fatsize;             // number of blocks occupied by FAT
    vector<string> filename; // filenames in ROOT
    vector<int> firstblock;  // firstblocks in ROOT
    vector<int> fat;         // FAT
    int buildfs();           // builds the file system
    int readfs();            // reads the file system
    int fssynch();           // writes the FAT and ROOT to the sdisk
};

#endif 