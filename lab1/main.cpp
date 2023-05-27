#include <iostream>
using namespace std;
struct node{
    int data;
    node* next;
    node(int a,node* n):data(a),next(n){}
};
//void init()
//{
//    node n(0, nullptr);
//
//}
class linkWithouthead
{
public:
    node* first= nullptr;
    linkWithouthead();
    linkWithouthead(const linkWithouthead & copy);

    node* getelemPtr(int pos)const;
    int size()const;
    bool empty();

    void clear();
    bool getElem(int pos,int &e);
    bool deletepos(int pos, int &e);

    bool insert(int pos, int &e);

    node* linkBind(node* b);
};
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
node *linkWithouthead::getelemPtr(int pos)const { //posӦ���Ǵ�0��ʼ��
    node* cur=first;
    while(pos--)
    {
        cur=cur->next;
    }
    return cur;
}

int linkWithouthead::size()const{
    int l=0;
    if(first!= nullptr)l++;
    node* cur=first;
    while(cur->next!= nullptr)
    {
        l++;
        cur = cur->next;
    }

    return l;
}

bool linkWithouthead::empty() {
    return first== nullptr;
}

void linkWithouthead::clear()
{
    int dispos;
    int i=0;
    while(!empty())
    {
        deletepos(i,dispos);
    }
}

bool linkWithouthead::getElem(int pos, int &e){
    node* cur=first;
    if(0<=pos && pos<=size()-1)
    {
        while(pos--)
        {
            cur=cur->next;
        }
        e=cur->data;
        return true;
    }
    else{cout<<pos <<"pos doesn't exist";return false;}
}

bool linkWithouthead::deletepos(int pos, int &e){ //ע�⿼��ɾ�����ǲ��ǵ�һ���ڵ㣡
    if(pos==0)
    {
        e=first->data;
        node* temp=first;
        first=first->next;
        delete temp;
        return true;
    }
    if(0<pos && pos<size()-1)
    {
        node* cur=first;
//        for(int i=0;i<pos-1;i++)
//        {
//            cur=cur->next;
//        }
        node* before=getelemPtr(pos-1);
        node* temp=before->next;//pos
        before->next=before->next->next;
        e=temp->data;
        delete temp;
        return true;
    }
    if(pos=size()-1)
    {
        node* before=getelemPtr(pos-1);
        delete before->next;
        before->next= nullptr;
    }
    else{cout<<pos<<"doesn't exist";return false;}
}

bool linkWithouthead::insert(int pos, int &e) {
    if(pos==0)
    {
//        node h(e, nullptr);//
        node* h=new node(e, nullptr);
        first=h;
        return true;
    }
    else if(pos>0 && pos<=size())
    {
        node* in=new node(e, nullptr);
//        node in(e, nullptr);
        node* before=getelemPtr(pos-1);
        node* t=before->next;
        before->next=in;
        in->next=t;
        return true;
    }
    else
    {
        cout<<"insert failed"<<endl;
        return false;
    }
}
node *linkWithouthead::linkBind(node *b) {
    node* cura=first,*curb=b;
    while((cura->data)!=(curb->data))
    {
        cura=cura==NULL?b:cura->next;   //�ǡ�cura==NULL�������ǡ�cura->next==NULL��
        curb=curb==NULL?first:curb->next;
    }
    return cura;
}
int main(){
    //����1����һ�������࣬��indexΪ0~5������1��6, 8, 9, 16, 36
    linkWithouthead link1;
    int input;
    for(int i=0;i<6;i++)
    {
     cin>>input;
     link1.insert(i,input);
//     cout<<link1.size()<<""<<endl;
    }
    //����size()
    cout<<"link1�ĳ���Ϊ"<<link1.size()<<endl;
//    ����getelem����ʼ�����
//    for(int i=0;i<link1.size();i++)
//    {
//     int num;
//     if(link1.getElem(i,num))cout<<num<<" ";
//     else cout<<"������Ŷ"<<endl;
//    }
    cout<<endl;
    //���ÿ������캯����ʼ��link2
//    linkWithouthead link2(link1);
//    //����getelem����ʼ�����
//    for(int i=0;i<link2.size();i++)
//    {
//        int num;
//        if(link1.getElem(i,num))cout<<num<<" ";
//        else cout<<"������Ŷ"<<endl;
//    }
//    cout<<endl;
////    cout<<link2.size()<<endl;
//    //���Բ����ɾ��
//    int ins=36,del;
//    link1.insert(1,ins);
//    link1.deletepos(5,del);
////        cout<<link1.size()<<endl;
//    for(int i=0;i<link1.size();i++) //�鿴���
//    {
//        int num;
//        if(link1.getElem(i,num))cout<<num<<" ";
//        else cout<<"������Ŷ"<<endl;
//    }
////    ����clear
//    link2.clear();
//    if(link2.first== nullptr)cout<<"ɾ���ɹ�"<<endl;

    //����bind ��link1(1 6 8 9 16 36) ���½���link3(2 7 16 36)
    //Ԥ�ڽ���� ���ص������нڵ� 16 ��36
    linkWithouthead link3;
    for(int i=0;i<4;i++)
    {
        cin>>input;
        link3.insert(i,input);
//     cout<<link1.size()<<""<<endl;
    }
    node* cur=link1.linkBind(link3.getelemPtr(0));
    node* temp=cur;
    while(temp->next!= nullptr)
    {
     cout<<temp->data<<" ";
     temp=temp->next;
    }

    return 0;
}
