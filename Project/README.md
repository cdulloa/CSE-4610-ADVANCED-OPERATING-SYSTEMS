<h1 align="center">CSE 4610 - Advanced Operating Systems</h1>
<p align="center"><strong>Remote GitHub Repository for CSE 4610 Course Assignments</strong>
<br>By Corbin Ulloa</p>
<br/>
<h2>About</h2>
What is SDisk?
-
SDisk is a virtual representation of a physical hard disk.  This is simply being emulated within a flat file.  Each SDisk will have two essential parameters, Block Numbers and Block Size.  These two numbers are used to calculate the full size of the virtual disk (SDisk).  This implementation will allow data to be written to "Blocks" of memory within the disk.

What is FileSystem?
-
FileSystem is a simple Disk Operating System (DOS) written to inherit the SDisk and adding useful features and functions that are common is storage system.  This is the ability to read and write files to the disk.  The two main features in the FileSystem include the Root and FAT tables.

- Root Table
	- This stores the data for each file located on the FileSystem.  This data includes the File Name and the starting Block Number which would represent a black of data that can be accessed from the SDisk.
- FAT Table
	- This keeps track of all blocks within the FileSystem and therefore available within the SDisk.  It allows for a quick and convenient way to locate if a Free Block (one that is not in use) is available.  This also links multiple blocks together through a Vector of Integer style method allowing one to looked Block Number "x" and see which Block number"y" succeeds it.

<h2>Course Information</h2>

- Student: Corbin Ulloa
- Instructor: Dr. Owen Murphy
- Course: CSE 4610 Advanced Operating Systems
- Session: CSUSB Spring 2023

<h2>Labs</h2>

1. *Lab 1:*. Maintain a username-password system by storing the usernames and passwords in a file. The file will consist of a single username and password per line with a space in between.
2. *Lab 2:*. Create the class Sdisk. Work on the constructor that creates Sdisk, putBlock to open the file and write a block, and getBlock to open the file and get a block.
3. *Lab 3:*. Create the class Filesys. Work on the constructor where it creates the ROOT directory and the FAT. Additionally, work on fssynch that writes the ROOT and FAT to the disk.
4. *Lab 4:*. Continue working on the Filesys class. Work on newFile, rmFile, getFirstBlock, addBlock, and delBlock.
5. *Lab 5:*. Continue working on the Filesys class. Work on checkBlock to check if a block belongs to a file, readBlock, writeBlock, and nextBlock.
6. *Lab 6:*. Create the class Shell. Work on the constructor, the add function, delete function, the type function which displays the content of a file, and the copy function which copies the content of one file to another.
7. *Lab 7:* Create the class Table. Work on the constructor and the buildTable function.
8. *Lab 8:* Continue working on the Table class. Work on the indexSearch function and search function.

<h2>Project</h2>

1. *Project Part 1:* The first part of the project requires the implementation of class that will be used to simulate a disk drive. 
2. *Project Part 2:* The second part of the project requires the implementation of a simple file system. In particular, it should include software which will handle dynamic file management.
3. *Project Part 3:* The third part of the project requires the implementation of a simple shell that uses the file system.
4. *Project Part 4:* The fourth part of the project requires the implementation of a database system with a single table which uses the file system from Project Part 2.

<h2>Project status</h2>
Completed

<h2>Credits</h2>

- README.md template: https://gist.github.com/r4dixx/43e51e7d59027b26fefec2b389fc9e53#file-readme-student-md
- Class website: http://cse.csusb.edu/murphy/cse4610/
