#include <chrono>
#include <iostream>
#include <fstream>
#include "avltree.h"

//Katarzyna Jaremek 303863

using namespace std;
using namespace std::chrono;

bool testTreeIntInt()
{
    cout<<"    testTreeIntInt()"<<endl;
    cout<<" Basic tests "<<endl;
    Dictionary<int,int> tested;
    if(tested.doesExist(4)!=false)
    {
        cout<<"Test 1: Error "<<endl;
        return false;
    }
    if(tested.getSize()!=0)
    {
        cout<<"Test 2: Error "<<endl;
        return false;
    }
    if(tested.isEmpty()==false)
    {
        cout<<"Test 3: Error "<<endl;
        return false;
    }

// all three nodes are added in ''correct'' order - tree is balanced
// add nodes 2,1,3
cout<<" Insert nodes 2,1,3"<<endl;
    tested.insert(2,2);
    if(tested.isEmpty()==true)
    {
        cout<<"Test 4: Error "<<endl;
        return false;
    }
    if(tested.getSize()!=1)
    {
        cout<<"Test 5: Error "<<endl;
        return false;
    }
    if(tested.doesExist(2)==false)
    {
        cout<<"Test 6: Error "<<endl;
        return false;
    }

    tested.insert(1,1);
    if(tested.isEmpty()==true)
    {
        cout<<"Test 7: Error "<<endl;
        return false;
    }
    if(tested.getSize()!=2)
    {
        cout<<"Test 8: Error "<<endl;
        return false;
    }
     if(tested.doesExist(1)==false)
    {
        cout<<"Test 9: Error "<<endl;
        return false;
    }


    tested.insert(3,3);
    if(tested.isEmpty()==true)
    {
        cout<<"Test 10: Error "<<endl;
        return false;
    }
    if(tested.getSize()!=3)
    {
        cout<<"Test 11: Error "<<endl;
        return false;
    }
     if(tested.doesExist(3)==false)
    {
        cout<<"Test 12: Error "<<endl;
        return false;
    }

    //insert node with the same key
    tested.insert(3,3);
    if(tested.isEmpty()==true)
    {
        cout<<"Test 13: Error "<<endl;
        return false;
    }
    if(tested.getSize()!=3)
    {
        cout<<"Test 14: Error "<<endl;
        return false;
    }
     if(tested.doesExist(3)==false)
    {
        cout<<"Test 15: Error "<<endl;
        return false;
    }
    tested.print();
//is tree cleared correctly
    tested.clear();
    if(tested.isEmpty()==false)
    {
        cout<<"Test 16: Error "<<endl;
        return false;
    }
    if(tested.doesExist(4)!=false)
    {
        cout<<"Test 17: Error "<<endl;
        return false;
    }
    if(tested.getSize()!=0)
    {
        cout<<"Test 18: Error "<<endl;
        return false;
    }
    //tested.print();

cout<<" Insert nodes 1,2,3"<<endl;
// add nodes 1,2,3 left rotation
    tested.insert(1,101);
    tested.insert(2,102);
    tested.insert(3,103);
    tested.print();
    tested.clear();
cout<<" Insert nodes 1,3,2"<<endl;
// add nodes 1,3,2 right-left rotation
    tested.insert(1,101);
    tested.insert(3,103);
    tested.insert(2,102);
    tested.print();
    tested.clear();
cout<<" Insert nodes 3,2,1"<<endl;
// add nodes 3,2,1 right rotation
    tested.insert(3,103);
    tested.insert(2,102);
    tested.insert(1,101);
    tested.print();
    tested.clear();
cout<<" Insert nodes 3,1,2"<<endl;
// add nodes 3,1,2 left-right rotation
    tested.insert(3,103);
    tested.insert(1,101);
    tested.insert(2,102);
    tested.print();
    tested.clear();
    return true;
}

bool testBiggerTreeIntInt()
{
    //add nodes 51,35,81,31,60,90,100
    cout<<"    testBiggerTreeIntInt()"<<endl;
    cout<<"Insert 51,35,81,31,60,90,100,1,24,31 "<<endl;
    Dictionary<int,int> testedTree;
    testedTree.insert(51,15);
    testedTree.insert(35,53);
    testedTree.print();
    testedTree.insert(81,18);
    testedTree.print();
    testedTree.insert(31,13);
    testedTree.print();
    testedTree.insert(60,6);
    testedTree.print();
    testedTree.insert(90,9);
    testedTree.print();
    testedTree.insert(100,1);
    testedTree.print();
    testedTree.insert(1,10);
    testedTree.print();
    testedTree.insert(24,11);
    testedTree.print();
    testedTree.insert(31,11);
    if(testedTree.getSize()!=9)
    {
        cout<<"Test 1: Error "<<endl;
        return false;
    }
    return true;
}

bool testIndexOperator()
{
    cout<<"    testIndexOperator()"<<endl;
    cout<<"Insert 3,4,3,5,10,1 "<<endl;
    Dictionary<int,int> indexTest;
    indexTest[3];
     if(indexTest.doesExist(3)==false)
    {
        cout<<"Test 1: Error "<<endl;
        return false;
    }
    if(indexTest.getSize()!=1)
    {
        cout<<"Test 2: Error "<<endl;
        return false;
    }
    if(indexTest.isEmpty()==true)
    {
        cout<<"Test 3: Error "<<endl;
        return false;
    }
    indexTest[4];
    indexTest[3];
    indexTest[5];
    indexTest[10];
    indexTest[1];
    indexTest.print();
    return true;
}

int main()
{
   //Dictionary basic tests

    if(testTreeIntInt() && testBiggerTreeIntInt() && testIndexOperator())
        cout<<"Class Dictionary works correctly"<<endl<<endl;
    else
        cout<<"Error: Class Dictionary does not work correctly"<<endl;


   //Slightly larger test


    string beagle_file = "TheVoyageofBeagle.txt";
    ifstream is(beagle_file);
    if (!is.good())
    {
        cout << "Cannot open input file: " << beagle_file << endl;
        return -1;
    }

    high_resolution_clock::time_point start = high_resolution_clock::now();
    Dictionary<string, int> word_counter;
    string word;
    while (is >> word)
        word_counter[word]++;

    high_resolution_clock::time_point now = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(now - start);

    cout << "Counting in " << time_span.count() << " seconds." << endl;
    cout << word_counter.getSize() << " unique words found." << endl;
    return 0;
}
