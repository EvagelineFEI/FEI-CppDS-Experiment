//
// Created by yys on 2022-11-08.
//

#ifndef TEXTEDIT_STORELINK_H
#define TEXTEDIT_STORELINK_H
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
struct getLine{
    string line;
    getLine* before;
    getLine* back;
//    getLine(string l,getLine* b,getLine* ba):line(l),before(b),back(ba){};
};

class storeInlink{
    getLine dummyhead;
    getLine* customCur; //track user's position
    int where;
public:
    storeInlink();
    void storeAndcover(  string name);
    void storeDontcover(string name);

    void showAll();

    void movePOinted(int line);
    void moveFirst();
    void moveLast();
    void moveBefore();
    void moveNext();

    void insertLine(int i,string n);
    void deleteLine(int i);

    void findStr(string str);

    void statics(int &line,int &num);

//    void reload();
//
//    void saveCur();
};

class operation{
public:
    char command;
    string name;

    void welcome();
    void deal(char c,storeInlink& serve);
};

#endif //TEXTEDIT_STORELINK_H
