#include <iostream>
#include <vector>
#include <string>
using namespace std;
const int N=0x1fffffff;
struct haffumannode{
    int parent;
    int leftc,rightc;
    int w;
    int f;//select标记
//    char c;
    haffumannode()
    {
        parent=leftc=rightc=w=f=0;
//        c='*';
    }
    haffumannode(int p,int l,int r,int ww)
    {
        parent=p;
        leftc=l;
        rightc=r;
        w=ww;
        f=0;
    }
};
int getIndex(string s,char& c)
{
    int i=0;
    while(s[i]!=c)i++;
    return i;
}
class haffumanTree{
    char* leafchars;
    int * leafweight;
    haffumannode* nodes;

    string *leafcharcode;
    int num;
    int curnode;

public:
    haffumanTree(vector<char> &chars, vector<int>& w, int num);
//    void create(char* chars, vector<int> w, int num);

    string encode(char c);

    string dcode(string s);

    void select(int pos,int &a,int &b); //在nodes[1:pos]寻找两个权值最小且parent为0的点，用a，b返回他们的位置。

    int (*charIndex)(string s,char &);
};
haffumanTree::haffumanTree(vector<char>& chars,vector<int> &w,int num) {
//    create(chars,w,num);
    this->num=num;
    int all=2*num-1;
    leafchars=new char[num+1];
    leafweight=new int[num+1];
    leafcharcode=new string[num+1];

    nodes=new haffumannode[all+1];
    curnode=all;
    charIndex=getIndex;

    for(int i=1;i<=num;i++)  //完成树内部的初始化
    {
        leafchars[i]=chars[i-1];
        leafweight[i]=w[i-1];
        nodes[i].w=w[i-1];
    }
    for(int i=1;i<=num;i++)cout<< leafchars[i]<<" "<< leafweight[i]<<endl;

    for(int i=num+1;i<=all;i++) //①
    {
        int a=0,b=0;
        select(i-1,a,b);
        cout<<a<<" "<<b<<endl;
        haffumannode nparent(0,a,b,nodes[a].w+nodes[b].w);
        nodes[i]=nparent;
        nodes[a].parent=i;nodes[b].parent=i;
    }

    for(int i=1;i<=num;i++)  //求叶子结点字符编码，左0，右1 ②不太熟练
    {
        string code;
        int l=0;
//        cout<<"hi"<<i<<endl;
        for(int child=i,parent=nodes[child].parent;parent!=0;child=parent,parent=nodes[child].parent)
        {
            if(child==nodes[parent].leftc)code.push_back('0');
            else code.push_back('1');
            l++;
        }

        string code_reverse;
        for(int i=code.size()-1;i>=0;i--)code_reverse.push_back(code[i]);
        cout<<code_reverse<<endl;
        leafcharcode[i]=code_reverse;

    }
    curnode=all;
    cout<<"建立成功"<<endl;
}

void haffumanTree::select(int pos, int &a, int &b){
   int min1,min2;
   min1=N;
   a=1;
   for(int i=1;i<=pos;i++)
   {
       if(nodes[i].w<min1 && nodes[i].parent==0)min1=nodes[i].w,a=i;
   }
   min2=N;
    for(int i=1;i<=pos;i++)
    {
        if(nodes[i].w<min2 &&nodes[i].parent==0 && nodes[i].w!=min1)min2=nodes[i].w,b=i;
    }
}

string haffumanTree::encode(char c) {
    return leafcharcode[(*charIndex)(leafchars,c)];
}

string haffumanTree::dcode(string s) {
    string charList;
    for(int i=0;i<s.size();i++)
    {
        if(s[i]=='0')curnode=nodes[curnode].leftc;
        else curnode=nodes[curnode].rightc;

        if(nodes[curnode].leftc==0 && nodes[curnode].rightc==0)
        {
            charList.push_back(leafchars[curnode]);
            curnode=2*num-1;
        }

    }
    return charList;
}


int main() {
//    string chars;
//    char chars1[30];
    vector<char> chars;
//    int w[30];
    vector<int> w;
    int num=0;
    cout << "请输入要放入哈夫曼树的字母个数:" << endl;
    cin>>num;
    cout << "请输入要放入哈夫曼树的字母:" << endl;
    char temp;
    for(int i=0;i<num;i++)
    {
        cin>>temp;
        chars.push_back(temp);
    }

    cout << "请输入各个字母的权值:" << endl;
    int a;
    for(int i=0;i<num;i++)
    {
        cin>>a;
        w.push_back(a);
    }
    haffumanTree tree(chars,w,num);

    for(int i=0;i<num;i++)
    {
        cout<<tree.encode(chars[i])<<endl;
    }

    cout<<tree.dcode("101100011")<<endl;
    return 0;
}
