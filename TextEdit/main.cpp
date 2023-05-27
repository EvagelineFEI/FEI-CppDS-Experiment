#include <iostream>
#include <vector>
#include "storeLink.h"
#include <string>
using namespace std;


storeInlink::storeInlink() {
    dummyhead.line=" ";
    dummyhead.back= nullptr;
    dummyhead.before= nullptr;
    customCur= nullptr;
    where=0;
}

void storeInlink::storeAndcover(string name) {   //
    fstream get(name,ios::in);  //不用加“”
    if(!get.is_open()) {
        cout << "open failed" << endl;return;
    }
    if(dummyhead.back== nullptr)dummyhead.back=new getLine();

    getLine* temp=dummyhead.back;
    getLine* tempB=&dummyhead;
    customCur=temp;

    while(!get.eof())
    {
        string aline;
        std::getline(get,aline);
        cout<<aline<<endl;
        temp->line=aline;
        temp->before=tempB;
        if(temp->back== nullptr)temp->back=new getLine();
        tempB=temp;
        temp=temp->back;
        customCur=temp;
    }
    cout<<"store finish!"<<endl;
}

void storeInlink::storeDontcover(string name) {
    fstream get;
    get.open(name);
    getLine* temp;
    if(dummyhead.back!= nullptr)
    {
     temp=dummyhead.back;
     while(temp->back!= nullptr)
     {
      temp=temp->back;
     }
     temp->back=new getLine();
     temp=temp->back;
     customCur=temp;
    }
    else
    {
        dummyhead.back=new getLine();
        temp=dummyhead.back;
        customCur=temp;
    }
    getLine* tempB=temp;
    while(!get.eof())
    {
        string aline;
        getline(get,aline);

        temp->line=aline;
        temp->before=tempB;
        temp->back=new getLine();

        tempB=temp;
        temp=temp->back;
        customCur=temp;
    }

}

void storeInlink::showAll(){
    getLine* temp=&dummyhead;
    if(temp->back== nullptr)cout<<"no content to show!"<<endl;
    while(temp->back!= nullptr)
    {
     cout<<temp->line<<endl;
     temp=temp->back;
    }
}

void storeInlink::movePOinted(int line) {
     int i=0;
     customCur=&dummyhead;
     while(i<line)
     {
       customCur=customCur->back;
       i++;
     }
     cout<<"you have moved to "<<i<<"line"<<endl;

}

void storeInlink::moveFirst() {
    customCur=&dummyhead;
    customCur=customCur->back;
    where=1;
}

void storeInlink::moveLast() {
    while(customCur->back!= nullptr)customCur=customCur->back,where++;

}
void storeInlink::moveBefore(){
    customCur=customCur->before;
    where--;
}

void storeInlink::moveNext() {
    customCur=customCur->back;
    where++;
}

void storeInlink::insertLine(int i, string n) {
    customCur=&dummyhead;
    int idx=0;//
    while(idx<i)
    {
        customCur=customCur->back;
        idx++;
    }
    getLine* ins=new getLine();
    ins->line=n;
    ins->back=customCur;  // 注意这个指针变化方式，要变四根指针，不要漏掉了！
    ins->before=customCur->before;
    customCur->before=ins;
    ins->before->back=ins;
}
void storeInlink::deleteLine(int i){
    customCur=&dummyhead;
    int idx=0;
    while(idx<i)
    {
     customCur=customCur->back;
     idx++;
    }
    getLine* temp=customCur;
    temp->back->before=temp->before;
    temp->before->back=temp->back;
    delete temp;
}


void storeInlink::statics(int &line, int &num) {
    getLine* temp=&dummyhead;
    while(temp->back!= nullptr)
    {
        line++;
        num+=temp->line.size();
        temp=temp->back;
    }
}

void storeInlink::findStr(string str) {
    getLine* temp=&dummyhead;
    int i=0;
    while(temp->back!= nullptr)
    {
        i++;
        if(temp->line.find(str)!=string::npos)
        {
            cout<<"line "<<i<<" : "<<temp->line<<endl;
        }
        temp=temp->back;
    }
}

void operation::welcome(){
    cout<<"please enter the filename you want to deal:"<<endl;
    cin>>name;
    storeInlink serve;
    cout<<"please enter the command you want to deal(if you want to quit,you can input 'Q'):"<<endl;
    while(scanf("%c",&command)!='Q')
    {
        deal(command,serve);
    }
    cout<<"operation end"<<endl;
}

void operation::deal(char c,storeInlink& serve){
//    storeInlink serve;
    switch (c) {
        case 'R':serve.storeAndcover(name);break;
        case 'W':serve.storeDontcover(name);break;
        case 'G':serve.showAll();break;
        case 'S':
            int l;cout<<"please tell me which line you wantna move to";
            cin>>l;
            serve.movePOinted(l);break;
        case 'B':serve.moveFirst();break;
        case 'E':serve.moveLast();break;
        case 'P':serve.moveBefore();break;
        case 'N':serve.moveNext();break;

        case 'I':
        {
            int l1;cout<<"please tell me you want to insert the new line before which line"<<endl;
            cin.sync();
            cin.clear();
            //sh
            cin>>l1;
            string n;cout<<"please enter the content of the new line";
//            cin>>n;
            cin.sync();
            cin.clear();
            getline(cin,n);
//            cout<<n;
            serve.insertLine(l1,n);break;
        }
        case 'D':
        {
            int l2;cout<<"please tell me which line you wanna delete";
            cin>>l2;
            serve.deleteLine(l2);
        }
    }
}
int main() {
    operation serveBegin;

    serveBegin.welcome();
    return 0;
}
