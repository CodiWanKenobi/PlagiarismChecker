//
// Created by shahm on 12/5/2018.
//

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <queue>

#include "HashTable.h"

using namespace std;

//Method provided in dir_help.cpp
//Fills a string vector with filenames from a directory input as a string
int getdir (string dir, vector<string> &files) {

    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

//Helper function that removes all spaces and extraneous
//characters from the string to aid in plagiarism catching.
//Also changes all uppercase letters to lowercase.
string fixString(string words)
{
    string fixedString = "";
    char letter;
    for(int i = 0; i < words.length(); i++)
    {

        letter = words[i];
        if(letter >= 'A' && letter <= 'Z')
        {
            letter = letter + (char) 32;
            fixedString = fixedString + letter;
        }

        else if(letter >= 'a' && letter <= 'z')
            fixedString = fixedString + letter;
        else if(letter >= '0' && letter <= '9')
            fixedString = fixedString + letter;

    }
    return fixedString;
}

//Creates a string key out of a queue containing n words
string createKey(queue<string> nwords)
{
    string buf;
    string key = "";
    for(int i = 0; i < (nwords.size()); i++)
    {
        buf = nwords.front();
        key = key + buf;
        nwords.pop();
        nwords.push(buf);
    }
    return fixString(key);
}

int main(int argc, char *argv[])
{

    //Creates a hash table
    HashClass h;
    ifstream inputFile;
    queue <string> nwords;
    int qSize = atoi(argv[2]);
    int numSims = atoi(argv[3]);
    string buffer;

    //Creates a string and a vector to use for the getdir method
    string dir = argv[1];
    vector<string> files = vector<string>();

    //Gets filenames from the directory input in the command line
    //and puts them in the "files" vector
    getdir(dir,files);
    vector<string> filesCopy = files;

    //Loops for each filename in the vector, except for the first two
    //This is because the first two are "." and ".."
    while((files.size()) > 2) {

        //Adds directory to front of filename in vector
        //This allows the file to be opened and read
        files[(files.size())-1] = dir + "/" + files[(files.size())-1];

        //Opens the file
        inputFile.open((files.back()).c_str());

        //cout << files.back() << endl;

        //Removes the filename from the end of the vector
        files.pop_back();
        if(inputFile.is_open())
        {
            while(inputFile)
            {

                inputFile >> buffer;

                if((nwords.size()) != qSize)
                {
                    nwords.push(buffer);   
                }
                else
                {
                    h.insert(h.hash(createKey(nwords)), (files.size()));
                    nwords.pop();
                    nwords.push(buffer);
                }
            }
            inputFile.close();
        }
        else
            cout << "Error: File could not be opened." << endl;
    }
    h.findCollisions(filesCopy, numSims);
    return 0;
}

