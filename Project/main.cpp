#include<iostream>
#include<sstream>
#include<vector>
#include<string>
#include "sdisk.h"
#include "filesys.h"
#include "shell.h"
#include "table.h"

using namespace std;

int main()
{
    //
    // This main program inputs commands to the shell.
    // It inputs commands as : command op1 op2
    // You should modify it to work for your implementation.
    //

    // From http://cse.csusb.edu/murphy/cse4610/main2.cpp.txt
    Sdisk sdisk = Sdisk("sdisk.txt", 256, 128);
    Fsys fsys=Fsys("sdisk.txt",256,128);
    Shell shell = Shell("sdisk.txt", 256, 128);
    Table table=Table("sdisk.txt",256,128);
    table.BuildTable("data.txt");

    string s;
    string command = "go";
    string op1, op2;

    while (command != "quit")
    {
        command.clear();
        op1.clear();
        op2.clear();
        cout << "$";
        getline(cin, s);
        int firstblank = s.find(' ');

        if (firstblank < s.length())
            s[firstblank] = '#';
        int secondblank = s.find(' ');
        command = s.substr(0, firstblank);

        if (firstblank < s.length())
            op1 = s.substr(firstblank + 1, secondblank - firstblank - 1);

        if (secondblank < s.length())
            op2 = s.substr(secondblank + 1);

        if (command == "dir")
        {
            // use the ls function
            Shell.dir();
        }
        if (command == "add")
        {
            // The variable op1 is the new file and op2 is the file data
            Shell.add(op1, op2);
        }
        if (command == "del")
        {
            // The variable op1 is the file
            Shell.del(op1)
        }
        if (command == "type")
        {
            // The variable op1 is the file
            shell.type(op1);
        }
        if (command == "copy")
        {
            // The variable op1 is the source file and the variable op2 is the destination file.
            Shell.copy(op1, op2);
        }
        if (command == "search")
        {
            // This is the command for Project 4
            // The variable op1 is the date
            Table.search(op1)
        }
    }

    return 0;
}

// ******  You can use this to test your Filesys class  *****

// int main()
// {
//   Sdisk disk1("disk1",256,128);
//   Filesys fsys("disk1",256,128);
//   fsys.newfile("file1");
//   fsys.newfile("file2"};

//   string bfile1;
//   string bfile2;

//   for (int i=1; i<=1024; i++)
//      {
//        bfile1+="1";
//      }

//   vector<string> blocks=block(bfile1,128); 

//   int blocknumber=0

//   for (int i=0; i< blocks.size(); i++)
//      {
//        blocknumber=fsys.addblock("file1",blocks[i]);
//      }

//   fsys.delblock("file1",fsys.getfirstblock("file1"));

//   for (int i=1; i<=2048; i++)
//      {
//        bfile2+="2";
//      }

//   blocks=block(bfile2,128); 

//   for (int i=0; i< blocks.size(); i++)
//      {
//        blocknumber=fsys.addblock("file2",blocks[i]);
//      }

//   fsys.delblock("file2",blocknumber);

// }
