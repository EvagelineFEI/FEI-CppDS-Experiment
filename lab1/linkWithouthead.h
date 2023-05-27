//
// Created by yys on 2022-10-26.
//

#ifndef LAB1_LINKWITHOUTHEAD_H
#define LAB1_LINKWITHOUTHEAD_H

linkWithouthead::linkWithouthead(){
//    node head(0, nullptr);
    first= nullptr;
}
linkWithouthead::linkWithouthead(const linkWithouthead &copy) {
    int l=copy.size();
    if(first== nullptr)
    {
     for(int i=0;i<l;i++)
     {
      node *in=copy.getelemPtr(i);
      this->insert(i,in->data);
     }
    }
    else
    {
        clear();
        for(int i=0;i<l;i++)
        {
            node *in=copy.getelemPtr(i);
            this->insert(i,in->data);
        }
    }
}
node *linkWithouthead::getelemPtr(int pos)const { //pos应该是从0开始的
    node* cur=first;
    while(pos--)
    {
     cur=first->next;
    }
    return cur;
}

int linkWithouthead::size()const {
    int l=1;
    node* cur=first;
    while(cur->next!= nullptr)
    {
        l++;
    }
    return l;
}

bool linkWithouthead::empty() {
    return first== nullptr;
}

void linkWithouthead::clear()
{
  int dispos;
  while(!empty())
  {
      deletepos(0,dispos);
  }
}

bool linkWithouthead::getElem(int pos, int &e){
    node* cur=first;
    if(0<pos && pos<=size()-1)
    {
        while(pos--)
        {
            cur=first->next;
        }

        e=cur->data;
        return true;
    }
    else{cout<<"pos doesn't exist";return false;}
}

bool linkWithouthead::deletepos(int pos, int &e) { //注意考虑删除的是不是第一个节点！
    if(pos==0)
    {
        e=first->data;
        node* temp=first;
        first=first->next;
        delete temp;
        return true;
    }
    if(0<pos && pos<=size()-1)
    {
        node* cur=first;
        for(int i=0;i<pos-1;i++)
        {
            cur=cur->next;
        }
        node* temp=cur->next;//pos
        cur->next=cur->next->next;
        e=temp->data;
        delete temp;
        return true;
    }
    else{cout<<"pos doesn't exist";return false;}
}

bool linkWithouthead::insert(int pos, int &e) {
    if(pos==0)
    {
     node h(e, nullptr);
     first=&h;
    }
    else if(pos>0 && pos<=size()-1)
    {
        node in(e, nullptr);
        node* before=getelemPtr(pos-1);
        node* t=before->next;
        before->next=&in;
        in.next=t;
    }
}
node *linkWithouthead::linkBind(node *a, node *b) {
    node* cura=a,*curb=b;
    while(cura!=curb)
    {
        cura=cura==NULL?b:cura->next;   //是“cura==NULL”而不是“cura->next==NULL”
        curb=curb==NULL?a:curb->next;
    }
    return cura;
}
#endif //LAB1_LINKWITHOUTHEAD_H
