#include <iostream>
using namespace std;
struct hashNode{
  int data;
  hashNode* next;
  hashNode(){
      data=-100;
      next= nullptr;
  }
};
class hashTable{
    hashNode *ht;
    int m;
public:
    hashTable();
    hashTable(int l);
    bool search(int key,int &pos);
    void insert(int ins,int &pos);
    void deleteKey(int key);
};
hashTable::hashTable() {
    ht= nullptr;
    m=0;
}
hashTable::hashTable(int l) {
    m=l;
    ht=new hashNode[l];
}

bool hashTable::search(int key, int &pos) {
    int index=key%m;

    if(ht[index].data==key)
    {
        pos=index;
        return true;
    }
    else
    {
        hashNode* cur=&ht[index];
        while(cur->next!= nullptr)
        {
            cur=cur->next;
            if(cur->data==key)
            {
                pos=index;
                return true;
            }
        }
    }
    return false;
}
void hashTable::insert(int ins, int &pos) {
    int a;
    if(search(ins,a))
    {
        cout<<"The elememt has already existed,it's at index"<<a<<endl;
        pos=a;
        return;
    }
    int index=ins%m;
    if(ht[index].data==-100)
    {
        ht[index].data=ins;
        pos=index;
        cout<<"The elememt has already inserted,it's exactly on index"<<index<<endl;
        return;
    }
    else
    {
        pos=index;
        hashNode* cur=&ht[index];
        while(cur->next!= nullptr)
        {
            cur=cur->next;
        }
        cur->next=new hashNode;
        cur->next->data=ins;
        cout<<"The elememt has already inserted,it's on the link after index"<<index<<endl;
        return;
    }
}

void hashTable::deleteKey(int key) {
    int a;
    if(!search(key,a))
    {
        cout<<"It's not in the hash table now"<<endl;
        return;
    }
    else
    {
        if(ht[a].data==key)
        {
            hashNode* cur=&ht[a];
            while(cur->next!= nullptr)
            {
                cur->data=cur->next->data;
                cur=cur->next;
            }
            delete cur;
            return;
        }
        if(ht[a].data!=key)
        {
            hashNode* cur=&ht[a];
            while(cur->next->data!=key)
            {
                cur=cur->next;
            }
            hashNode* temp=cur->next;
            cur->next=cur->next->next;
            delete temp;
        }
    }
}
int main()
{
    int pos;
    hashTable test(7);
    test.insert(49,pos);test.insert(50,pos);
    test.insert(56,pos);test.insert(80,pos);
    test.insert(100,pos);test.insert(13,pos);
    test.insert(70,pos);
    bool f=test.search(50,pos);
    cout<<f<<" "<<pos<<endl;
    test.deleteKey(56);
    f=test.search(56,pos);
    cout<<f<<endl;
    return 0;
}
