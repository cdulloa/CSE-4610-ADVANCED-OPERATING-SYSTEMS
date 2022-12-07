#include "shell.h"
#include "filesys.h"

Shell::Shell(string diskname, int numberofblocks, int blocksize ) : Filesys( diskname, numberofblocks, blocksize )

{

}

int Shell::dir()
{ 
  vector<string> flist=ls();
    for (int i=0; i<flist.size(); i++)
    {
    cout << flist[i] << endl;
    }
}

int Shell::add(string filename, string buffer)
{
    int code = newfile(filename);

    if (code >= 0)
    {
        cout << "File does exist" << endl;
        return 0;
    }

    vector<string>blocks=block(buffer,getblocksize());
    for(int i =0; i < blocks.size(); i++)
    {
        addblock(filename,blocks[i]);
    }
    return 1;
}

int Shell::del(string file)
{
    while(getfirstblock(file) != 0)
    {
        delblock(file, getfirstblock(file));
    }
    rmfile(file);
    return 1;
}

int Shell::copy(string file1,string file2)
{
    int block=getfirstblock(file1);
    int code = newfile(file2);

    string buffer;

    if (block < 0) 
    {
        cout << "No file exists";
        return 0;
    }

    while(block != 0)
    {
       readblock (file1,block,buffer);
       addblock(file2,buffer);
       block = nextblock(file1,block);
   
    }
    return 1;
}

int Shell::type(string file)
{
    int block =getfirstblock(file);
    string buffer;
    string temp;

    while(block != 0)
    {
        readblock(file, block, temp);
        buffer += temp;
        block = nextblock(file,block);
    }
    
    cout<< buffer <<endl;
    return 1;
}