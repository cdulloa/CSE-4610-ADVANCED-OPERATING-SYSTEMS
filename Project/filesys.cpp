#include <sstream>
#include "filesys.h"
#include "sdisk.h"
#include "block.h"

// using namespace std;

Filesys::Filesys(string diskname, int numberofblocks, int blocksize) : Sdisk(diskname, numberofblocks, blocksize)
{

  rootsize = getblocksize() / 12;
  fatsize = ((getnumberofblocks() * 5) / getblocksize()) + 1;

  string buffer;
  getblock(1, buffer);
  if (buffer[0] == '#') // No File System
  {
    buildfs();
    fssynch();
  }
  else
  {
    readfs(); // Read existing File System
  }
}

int Filesys::buildfs()
{
  for (int i = 0; i < rootsize; i++)
  {
    filename.push_back("xxxxxx");
    firstblock.push_back(0);
  }
  ostringstream ostream;

  string buffer = ostream.str();
  vector<string> blocks = block(buffer, getblocksize());
  putblock(1, blocks[0]);

  // 2+ fatsize is the first data block
  fat.push_back(fatsize + 2);
  fat.push_back(-1);
  for (int i = 0; i < fatsize; i++)
  {
    fat.push_back(-1);
  }

  for (int i = fatsize + 2; i < getnumberofblocks(); i++)
  {
    fat.push_back(i + 1);
  }

  fat[fat.size() - 1] = 0;
  fssynch();
  return 1;
}

int Filesys::newfile(string file)
{
  for (int i = 0; i < filename.size(); i++)
  {
    if (filename[i] == file)
    {
      cout << "File exists" << endl;
      cout << " " << endl;
      return 0;
    }
  }

  for (int i = 0; i < filename.size(); i++)
  {
    if (filename[i] == "XXXX")
    {
      cout << "Creating new file: " << file << endl;
      filename[i] = file;
      firstblock[i] = 0;
      fssynch();
      return 1;
    }
  }
  cout << "No space in root" << endl;
  return 0;
}

bool Filesys::checkblock(string file, int blocknumber)
{

  int b = getfirstblock(file);
  if (b == -1)
  {
    return false;
  }

  while (b != 0)
  {
    if (b == blocknumber)
    {
      return true;
    }
    b = fat[b];
  }
  return false;
}

int Filesys::addblock(string file, string block)
{
  // return allocated block number
  int block_id = getfirstblock(file);
  if (block_id == -1)
  {
    return 0; // file doesn't exist'
  }

  int allocate = fat[0];
  if (allocate == 0)
  {
    cout << "Error no space" << endl;
    cout << " " << endl;
    return 0;
  }

  fat[0] = fat[fat[0]];
  fat[allocate] = 0;

  if (block_id == 0)
  {
    for (int i = 0; i < rootsize; i++)
    {
      if (filename[i] == file)
      {
        firstblock[i] = allocate;
      }
    }
  }
  else
  {
    int b = block_id;
    while (fat[b] != 0)
    {
      b = fat[b];
    }
    fat[b] = allocate;
  }
  putblock(allocate, block);
  fssynch();
  return allocate;
}

int Filesys::delblock(string file, int blocknumber)
{
  if (blocknumber == getfirstblock(file))
  {
    for (int i = 0; i < filename.size(); ++i)
    {
      if (filename[i] == file)
      {
        firstblock[i] = fat[blocknumber];
      }
    }
  }

  if (blocknumber == getfirstblock(file))
  {
    for (int i = 0; i < filename.size(); ++i)
    {
      if (file == filename[i])
      {
        if (nextblock(file, blocknumber) != -1)
        {
          firstblock[i] = nextblock(file, blocknumber);
        }
        else
        {
          firstblock[i] = fat[blocknumber];
          break;
        }
      }
    }
  }
  else
  {
    int temp = getfirstblock(file);
    while (fat[temp] != blocknumber)
    {
      temp = fat[temp];
    }
    fat[temp] = fat[blocknumber];
  }
  fat[blocknumber] = fat[0];
  fat[0] = blocknumber;
  fssynch();
  return 1;

  // else
  // {
  //   return 0;
  // }
}

int Filesys::fssynch()
{
  // sync the file system
  ostringstream outsream_1;
  for (int i = 0; i < firstblock.size(); i++)
  {
    outsream_1 << filename[i] << " " << firstblock[i] << " ";
  }

  ostringstream outsream_2;

  for (int i = 0; i < fat.size(); i++)
  {
    outsream_2 << fat[i] << " ";
  }

  string buffer1 = outsream_1.str(); // converts to string
  string buffer2 = outsream_2.str();

  vector<string> block_1 = block(buffer1, getblocksize()); // block it here
  vector<string> block_2 = block(buffer2, getblocksize());

  putblock(1, block_1[0]);
  for (int i = 0; i < block_2.size(); i++)
  {
    putblock(fatsize + 2 + i, block_2[i]);
  }
  return 1;
}

int Filesys::readfs()
{
  istringstream istream;
  string buffer1, buffer2;
  istringstream istream1, istream2;
  istream.str(buffer1);
  istream2.str(buffer2);

  getblock(1, buffer1);
  string tempbuffer;

  for (int i = 0; i < rootsize; i++)
  {

    getblock(2 + i, tempbuffer);
    buffer2 += tempbuffer;
    tempbuffer.clear();

    string f;
    int t;

    istream >> f;
    istream2 >> t;

    filename.push_back(f);
    firstblock.push_back(t);
  }

  for (int i = 0; i < fatsize; i++)
  {
    string b;
    getblock(i + 2, b);

    buffer2 += b;
  }

  for (int i = 0; i < getnumberofblocks(); i++)
  {
    int k;
    istream2 >> k;
    fat.push_back(k);
  }
  return 1;
}

int Filesys::getfirstblock(string file)
{
  // returns 0 if file is empty or returns 0 for nonexistent file
  for (int i = 0; i < filename.size(); i++)
  {
    if (filename[i] == file)
    {
      return firstblock[i];
    }
  }
  cout << "file doesn'y exist" << endl;
  return 0;
}

int Filesys::readblock(string file, int blocknumber, string &buffer)
{
  if (checkblock(file, blocknumber))
  {
    getblock(blocknumber, buffer);
    return 1;
  }
  else
  {
    return 0;
  }
}

int Filesys::writeblock(string file, int blocknumber, string buffer)
{
  if (checkblock(file, blocknumber))
  {
    putblock(blocknumber, buffer);
    return 1;
  }
  else
  {
    return 0;
  }
}

int Filesys::nextblock(string file, int blocknumber)
{
  if (checkblock(file, blocknumber))
  {
    return fat[blocknumber];
  }
  else
  {
    return 0;
  }
}

int Filesys::fsclose()
{
  return 1;
}

int Filesys::rmfile(string file)
{
  for (int i = 0; i < filename.size(); i++)
  {
    if (filename[i] == file && firstblock[i] == 0)
    {
      filename[i] = "XXXXX";
      firstblock[i] = 0;
    }
  }
  fssynch();
  return 1;
}

// This function is part of the Filesys class
// Prototype: vector<string> ls();
vector<string> Filesys::ls()
{
  vector<string> flist;
  for (int i = 0; i < filename.size(); i++)
  {
    if (filename[i] != "XXXXX")
    {
      flist.push_back(filename[i]);
    }
  }
  return flist;
}