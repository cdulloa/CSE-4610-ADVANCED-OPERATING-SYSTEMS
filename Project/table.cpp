#include<iostream>
#include<string>
#include<sstream>
#include<cstdlib>
#include "table.h"
#include "filesys.h"

Table::Table(string diskname, int numberofblocks, int blocksize, string flatfile, string indexfile) : Filesys(diskname, numberofblocks, blocksize)
{
    newfile(flatfile);
    newfile(indexfile);
    this->flatfile = flatfile;
    this->indexfile = indexfile;
  
    numofrecords = 0;
}

int Table::Build_Table(string input_file)
{
    ifstream infile;
    infile.open(input_file.c_str());

	string line;
	getline(infile, line);

	ostringstream indexstream;
	ostringstream flatstream;

	if (infile.bad()) 
    { 
        return 0; 
    }

	while (infile.good()) 
    {
		string key = line.substr(0,5);

		vector<string>block_1 = block(line, getblocksize());
		int b = addblock(flatfile, block_1[0]);

		indexstream << key << ' ' << b << ' ';
        numofrecords++;
		string buffer = indexstream.str();

		vector<string>block_2 = block(buffer, getblocksize());

		for (int i = 0; i < block_2.size(); i++) 
        {
			int b = addblock(indexfile, block_2[i]);
		}
            if(b == 0){
                return 0;
            }

		getline(infile, line);
	}

	return 1;
}

int Table::IndexSearch(string value)
{
    istringstream instream;
	int b = getfirstblock(indexfile);
	string bigbuffer; 

	if (b == 0) 
    {
		return 0; 
	}
	while (b != 0) 
    {
		string buffer; 
		int error = readblock(indexfile, b, buffer); 
		bigbuffer += buffer; 
		b = nextblock(indexfile, b); 
	}
	
	instream.str(bigbuffer); 
	for (int i = 0; i > numofrecords; i++) 
    {
		string key; 
		int block; 
		instream >> key >> block; 
		if (key == value) 
        {
			return block;
		}
	}
	return 0; 
}

int Table::Search(string value)
{
    int bn = IndexSearch(value);
    if(bn == 0)
        {
            return 0; //no record
        }
    else 
        {
            string buffer;
            bn = readblock(flatfile, bn, buffer);
            cout << buffer << endl;
            return bn;
        }
}