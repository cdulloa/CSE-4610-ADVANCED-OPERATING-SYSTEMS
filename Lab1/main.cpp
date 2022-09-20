#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class PasswordFile
{
 public:
 PasswordFile(string filename);// opens the file and reads the names/passwords in the vectors user and password.
 void addpw(string newuser, string newpassword); //this adds a new user/password to the vectors and writes the vectors to the file filename
 bool checkpw(string user, string passwd); // returns true if user exists and password matches
 private:
 string filename; // the file that contains password information
 vector<string> user; // the list of usernames
 vector<string> password; // the list of passwords
 void synch(); //writes the user/password vectors to the password file
};

// opens the file and reads the names/passwords in the vector entry
PasswordFile::PasswordFile(string filename) 
{
    this->filename = filename;
    ifstream infile(filename.c_str());
   
        string userName, userPassword;
        while (infile >> userName >> userPassword)
        {
            user.push_back(userName);
            password.push_back(userPassword);
        }
        infile.close();
        cout << user.size() << " user information loaded from file " << filename << endl;
}

// this adds a new user/password to entry and writes entry to the file filename
void PasswordFile::addpw(string newuser, string newpassword) 
{
    int index = -1;
    for (int i = 0; i < user.size(); i++)
    {
        if (user[i] == newuser)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        user.push_back(newuser);
        password.push_back(newpassword);
    }
    else
        password[index] = newpassword; 

    synch();
    cout << "new user " << newuser << " added to file" << endl;
}

// Checks to see if user and password match
bool PasswordFile::checkpw(string usr, string passwd) 
{
    for (int i = 0; i < usr.size(); i++)
    {
        if (user[i] == usr)
        {
            return password[i] == passwd;
        }
    }

    return false;
}

void PasswordFile::synch()
{
    ofstream outfile(filename.c_str());

    for (int i = 0; i < user.size(); i++)
    {
        outfile << user[i] << " " << password[i] << endl;
    }

    outfile.close();
}



int main()
{
    PasswordFile passfile("password.txt");
    passfile.addpw("dbotting", "123qwe");
    passfile.addpw("egomez", "qwerty");
    passfile.addpw("testUser", "testPass");
    passfile.addpw("tongyu", "liberty");
    
    // write some lines to see if passwords match users
    string userName, userPassword;
    cout << "Enter a user name: ";
    cin >> userName;
    cout << "Enter password: ";
    cin >> userPassword;
    if (passfile.checkpw(userName, userPassword))
        printf("%d", true);
    else
        printf("%d", false);
}