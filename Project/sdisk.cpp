#include "sdisk.h"
#include "filesys.h"

Sdisk::Sdisk(string diskname, int numberofblocks, int blocksize)
{
  this->diskname = diskname;
  this->numberofblocks = numberofblocks;
  this->blocksize = blocksize;

  // Open Sdisk file
  fstream outfile;
  outfile.open(diskname.c_str(), ios::in | ios::out);

  if (!outfile.good()) // no exist
  {
    outfile.close();
    ofstream outfile;
    outfile.open(diskname.c_str(), ios::in | ios::out);
    for (int i = 0; i < (blocksize * numberofblocks); i++)
    {
      outfile.put('#');
    }
  }

  if (outfile.good())
  {
    cout << diskName << " exists.\n";
  }
  // outfile.close();
}

int Sdisk::getnumberofblocks()
{
  return numberofblocks;
}

int Sdisk::getblocksize()
{
  return blocksize;
}

int Sdisk::getblock(int blocknumber, string &buffer)
{
  fstream outfile;

  outfile.open(diskname.c_str(), ios::in | ios::out);

  // position of block
  outfile.seekg(blocknumber * blocksize);

  for (int i = 0; i < buffer.length(); i++)
  {

    char c = outfile.get();
    buffer.push_back(c);
  }
  return 1;
}

int Sdisk::putblock(int blocknumber, string buffer)
{
  fstream outfile;
  outfile.open(diskname.c_str(), ios::in | ios::out);

  // block's position
  outfile.seekg(blocknumber * blocksize);

  for (int i = 0; i < buffer.length(); i++)
  {
    outfile.put(buffer[i]);
  }
  outfile.close();
  return 1;
}
