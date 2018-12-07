//
// Created by shahm on 12/7/2018.
//
#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

const int MAX_VAL = 279421;

class HashClass
{
public:
    HashClass();
    void insert(const unsigned int key, const int value);
    void findCollisions(vector<string> fileName, int compSize);
    unsigned int hash(const string& key);
    int search_index(const int key, bool dupKeyFlag);

private:
    const static unsigned int MAX_SIZE = MAX_VAL;
    int keys[MAX_SIZE];
    vector<int> values[MAX_SIZE];
};

HashClass::HashClass()
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        keys[i] = -1;   //make the whole table invalid at the beginning
        vector<int> myHash;
        values[i] = myHash;
    }
}

unsigned int HashClass::hash(const string& k)
{
    unsigned int value = 0 ;
    for (int i = 0; i < k.length() - 1; i++)
    {
            value = 11 * value + k[i];
    }

    return  value;
}

int HashClass::search_index(const int key, bool dupKeyFlag = true)
{
    unsigned int h = hash(to_string(static_cast<long long>(key))) % MAX_SIZE;
    unsigned int offset = 0;
    unsigned int index;

    while (offset < MAX_SIZE)
    {
        index = (h % MAX_SIZE + offset) % MAX_SIZE;

        //if the flag is false, return a new, used in HashTable
        if (keys[index] == -1 || (dupKeyFlag && keys[index] == key))
            return index;
        offset++;
    }
    return -1;
}

void HashClass::insert(const unsigned int key, const int value)
{

    int index = search_index(key);
    if (index == -1)
    {
        cerr << "Table has been filled." << endl;
        return;
    }
    keys[index] = key;
    values[index].push_back(value);
}

void HashClass::findCollisions(vector<string> fileName, int compSize)
{
    int map[fileName.size()][fileName.size()];
    for (int i = 0; i < fileName.size(); i++)
    {
        for (int j = 0; j < fileName.size(); j++)
            map[i][j] = 0;
    }

    for (int i = 0; i < MAX_SIZE; i++)
    {
        for (int j = 0; !values[i].empty() && (j < (values[i]).size()); j++)
        {
            for (int k = j + 1; k < (values[i]).size(); k++)
            {
                map[values[i][k]][values[i][j]]++;
            }
        }
    }

    vector<int> numCols;
    vector<string> firstFile;
    vector<string> secondFile;

    for(int i = 1; i < fileName.size(); i++)
    {
        for(int j = (i+1); j < fileName.size(); j++)
        {
            if(map[i][j] >= compSize)
            {
                numCols.push_back(map[i][j]);
                firstFile.push_back(fileName[i]);
                secondFile.push_back(fileName[j]);
            }
        }
    }

    //Selection Sort
    int data = 0, tempData = 0, minIdx = 0;
    string minPath1, minPath2, tempPath1, tempPath2;
    bool swapVar;
    for(int i = 0; i < numCols.size(); i++)
    {
        data = numCols[i];
        minPath1 = firstFile[i];
        minPath2 = secondFile[i];

        tempData = numCols[i];
        tempPath1 = firstFile[i];
        tempPath2 = secondFile[i];

        swapVar = false;

        for (int j = i + 1; j < numCols.size(); j++)
        {
            // gets smallest in unsorted portion
            if (data > numCols[j])
            {
                data = numCols[j];
                minPath1 = firstFile[j];
                minPath2 = secondFile[j];
                minIdx = j;
                swapVar = true;
            }
        }

        if(swapVar)
        {
        numCols[i] = data;
        firstFile[i] = minPath1;
        secondFile[i] = minPath2;
        numCols[minIdx] = tempData;
        firstFile[minIdx] = tempPath1;
        secondFile[minIdx] = tempPath2;
        }
    }
    cout << endl;
    for(int i = 1; i <= numCols.size(); i++) //print out the collisions
    {
        cout << numCols[numCols.size() - i] << ": "
             << firstFile[numCols.size() - i] << " and " 
             << secondFile[numCols.size() - i] << endl;
    }
    cout << endl;
}
