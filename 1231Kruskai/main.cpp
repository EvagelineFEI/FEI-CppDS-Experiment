#include <iostream>
#include <cmath>
#include <queue>
using namespace std;
struct enode{
    char st,ed;
    int w;
    enode* nex= nullptr;
    bool operator == (enode& p)const{
     return w==p.w;
    }
    bool operator < (enode& p)const{
        return w<p.w;
    }
};
struct vnode{
    char c;
    enode* first= nullptr;
    int idx;
};
class mapTotree{
    int numv,nume;
    vnode* arrv;
    enode* arre;
//    int* treeidx;

public:
    ~mapTotree();
    mapTotree();
    void heapsort();
    void heapajust(int st,int ed);
    void kruskal();
};
mapTotree::~mapTotree(){
    delete arrv;
    delete arre;
}
mapTotree::mapTotree() {
    int a,b;
    cout<<"请输入总的顶点数和边数:"<<endl;
    cin>>a>>b;
    numv=a;nume=b;
    arrv=new vnode[numv];
    arre=new enode[nume];
    cout<<"请各个顶点的编号:"<<endl;
    char tag;
    for(int i=0;i<numv;i++)
    {
      cin>>tag;
      arrv[i].c=tag;
      arrv[i].idx=i;
    }
    char t1,t2;int w0;
    cout<<"请输入各条边的信息，依次输入出发点，终点，权值三个信息:"<<endl;
    for(int i=0;i<nume;i++)
    {
//        cout<<"第"<<i+1<<"条边"<<endl;
        cin>>t1>>t2>>w0;
        arre[i].w=w0;
        arre[i].st=t1;arre[i].ed=t2;
        int idx=0;
        while(arrv[idx].c!=t1)
        {
            idx++;
        }
        arre[i].nex=arrv[idx].first;
        arrv[idx].first=&arre[i];
    }
    heapsort();
}

void mapTotree::heapajust(int st,int ed) {
    int f=st,ch=2*f+1;
    while(ch<ed)
    {
      if(ch+1<ed && arre[ch+1]<arre[ch])ch++;
      if(arre[ch]<arre[f])
      {
          swap(arre[ch],arre[f]);
          f=ch;ch=2*ch+1;
      }
      else break;
    }
}
void mapTotree::heapsort(){
    for(int i=nume/2;i>=1;i--)
    {
        heapajust(i-1,nume);
    }

    for(int i=0;i<nume;i++)cout<<arre[i].w<<" ";
    cout<<endl;
}

void mapTotree::kruskal()
{
    int num=0,s=0; //边的数目,寻找的次数
    queue<enode> final;
    while(num<numv-1)
    {
     enode temp=arre[0];
     s++;
     arre[0]=arre[nume-s-1];
     heapajust(0,nume-s-1-1);
     for(int i=0;i<nume-i;i++)cout<<arre[i].w<<" ";
     cout<<endl;
     int idx1=-1,idx2=-1;
     for(int i=0;i<numv;i++)
     {
         if(arrv[i].c==temp.st)idx1=arrv[i].idx;
         if(arrv[i].c==temp.ed)idx2=arrv[i].idx;
         if(idx1!=-1 && idx2!=-1)break;
     }
     if(idx1!=idx2)
     {
      final.push(temp);
      num++;
      int oldex=idx2;
      for(int i=0;i<numv;i++)
      {
          if(arrv[i].idx==oldex)arrv[i].idx=idx1;
      }
     }
    }
    enode show;
    while(!final.empty())
    {
        cout<<final.front().st<<"to"<<final.front().ed<<" "<<final.front().w<<endl;
        final.pop();
    }
}
int main() {
    mapTotree serve;
    serve.kruskal();
    return 0;
}
