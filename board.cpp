#include "board.h"

const boardcn board :: nb;
char board ::bpath[BOARDSSIZE+10];
int board ::bpsize;
char board ::wpath[BOARDSSIZE+10];
int board ::wpsize;


int board ::findParent(int i)
{
    char &j=parent[i];
    if(j==parent[j])return j;
    return j=findParent(j);
}

void board ::unite(int x,int y)
{
    char i = findParent(x),j = findParent(y);
    if(i<j)parent[j]=i;
    else parent[i]=j;
}
 void board ::add(int i,bool j)//j=0 black j=1 white
{
    int k,l,lp;
    bitboard tmp;
#if SEARCH == 1
    zValue ^= ztable.ZHT[j][i];
#endif
    ban[0].add(i);
    ban[1].add(i);
    bitb[j].add(i);
    for(k=0; k<nb.nbsize[i]; k++)
    {
        l=nb.nb[i][k];
        if(bitb[j].get(l))
        {
            lp = findParent(l);
            tmp |= air[lp];
            air[lp].clear();
            countair[lp]=0;
            unite(i,lp);
        }
        else if(bitb[!j].get(l))
        {
            lp = findParent(l);
            air[lp].minus(i);
            countair[lp]=air[lp].count();
            if(countair[lp] == 1)
            {
                ban[j] |= air[lp];
                notsafe[!j] |= air[lp];
            }
        }
        else
        {
            notsafe[!j].add(l);
            tmp.add(l);
        }
    }
    tmp.minus(i);
    k=findParent(i);
    air[k] = tmp;
    countair[k]= air[k].count();
    if(countair[k] == 1)
    {
        ban[!j] |= air[k];
        notsafe[j] |= air[k];
    }

}

bool board::check(int i,bool j)//j=0 =>b
{
    //cout<<"check"<<i<<endl;
    bool flag=false;
    int l,k;
    if(ban[j].get(i))return false;
    else if(notsafe[j].get(i)==0)return true;
    notsafe[j].minus(i);
#if search == 2
    // if(checkTriangle(i,j))return true;
#endif
    for(k=0; k<nb.nbsize[i]; k++)
    {
        l=nb.nb[i][k];
        if(bitb[j].get(l))
        {
            if(countair[findParent(l)]!=1)return true;
        }
        else if(!bitb[!j].get(l))
        {
            return true;
        }
    }
    ban[j].add(i);
    return false;
}

bool board :: check_is_end()
{
    bool black,white;
    black=white=false;
	getallair();
    for(int i=0; i<BOARDSSIZE; i++)
    {
        if(bitb[0].get(i)||bitb[1].get(i))
        {
            if(air[findParent(i)].count()==0)
            {
                cout<<"block unsafe : "<<i<<endl;
                return false;
            }
        }
        else
        {
            if(check(i,0))black=true;
            if(check(i,1))white=true;
        }
    }
    if(black&&white)return false;
    return true;
}


void board :: getallair()
{
    int i,j,t,u,r,d,l;
    memset(air,0,sizeof(air));
    memset(countair,0,sizeof(countair));
    for(i=0; i<BOARDCUL; i++)
    {
        for(j=0; j<BOARDCUL; j++)
        {
            u=r=d=l=-1;
            t=i*BOARDCUL+j;
            if(!bitb[0].get(t) && !bitb[1].get(t))//ªÅ¥Õ
            {
                if(i!=0)
                {
                    if(bitb[0].get(t-BOARDCUL)||bitb[1].get(t-BOARDCUL))
                    {
                        u=findParent(t-BOARDCUL);
                        air[u].add(t);
                    }
                }
                if(i!=(BOARDCUL-1))
                {
                    if(bitb[0].get(t+BOARDCUL)||bitb[1].get(t+BOARDCUL))
                    {
                        d=findParent(t+BOARDCUL);
                        if(d!=u)air[d].add(t);
                    }
                }
                if(j!=0)
                {
                    if(bitb[0].get(t-1)||bitb[1].get(t-1))
                    {
                        r=findParent(t-1);
                        if(r!=u && r!=d)air[r].add(t);
                    }
                }
                if(j!=(BOARDCUL -1))
                {
                    if(bitb[0].get(t+1)||bitb[1].get(t+1))
                    {
                        l=findParent(t+1);
                        if(l!=u && l!=d && l!=r)air[l].add(t);
                    }
                }
            }
        }
    }
    for(i=0; i<BOARDSSIZE; i++)
    {
        if(bitb[0].get(i)||bitb[1].get(i))
        {
            if(parent[i]==i)countair[i]=air[i].count();
        }
    }
}

void board::showboard()
{
    int i;
    for(i=0; i<BOARDCUL*BOARDCUL; i++)
    {
        if(bitb[0].get(i))
        {
            cout<<'@';
        }
        else if(bitb[1].get(i))
        {
            cout<<'O';
        }
        else
        {
            cout<<'.';
        }
        if(i%BOARDCUL == BOARDCUL -1)
        {
            cout<<endl;
        }
    }
}


void board::showParent()
{
    for(int i=0; i<BOARDCUL*BOARDCUL; i++)
    {
        printf("%3d ",(int)parent[i]);
        if(i%BOARDCUL == BOARDCUL -1)
        {
            cout<<endl;
        }
    }
}

board::board()
{
#if SEARCH == 1
    zValue = 0;
#endif
    //clear();
}

board::board(bitboard bb,bitboard ww)
{
    Initboard(bb,ww);

}
void board::Initboard(bitboard bb ,bitboard ww )
{
    bitb[0]=bb;
    bitb[1]=ww;
    setdata();
}
inline bool board::get(int i,bool j)
{
    return bitb[j].get(i);
}
bool board::just_play_color()
{
    int bc=bitb[0].count();
    int wc=bitb[1].count();
    if(bc==wc)return 1;
    return 0;
}

void board::getv(int bone[BOARDSSIZE],int wone[BOARDSSIZE],int two[BOARDSSIZE] ,int &bsize,int &wsize ,int &tsize)
{
    bool bc,wc;
    bsize=wsize=tsize=0;
    for(int i=0; i<BOARDSSIZE; i++)
    {
        if(!bitb[0].get(i)&&!bitb[1].get(i))
        {
            bc=check(i,0);
            wc=check(i,1);
            if(bc)
            {
                if(wc)
                {
                    two[tsize]=i;
                    tsize++;
                }
                else
                {
                    bone[bsize]=i;
                    bsize++;
                }
            }
            else if(wc)
            {
                wone[wsize]=i;
                wsize++;
            }
        }
    }
}

void board::getvec(vector<char> &bone,vector<char> &wone ,vector<char> &two )
{
    bool bc,wc;
    for(int i=0; i<BOARDSSIZE; i++)
    {
        if(!bitb[0].get(i)&&!bitb[1].get(i))
        {
            bc=check(i,0);
            wc=check(i,1);
            if(bc)
            {
                if(wc)
                {
                    two.push_back(i);
                }
                else
                {
                    bone.push_back(i);
                }
            }
            else if(wc)
            {
                wone.push_back(i);
            }
        }
    }
}

void board::setdata()
{
    int i,j,k;
    memset(air,0,sizeof(air));
#if SEARCH == 1
    zValue = 0;
#endif
    for(i=0; i<BOARDSSIZE; i++)
    {
#if SEARCH == 1
        if(bitb[0].get(i))
        {
            zValue ^= ztable.ZHT[0][i];
        }
        else if(bitb[1].get(i))
        {
            zValue ^= ztable.ZHT[1][i];
        }
#endif
        parent[i]=i;
    }
    for(i=0; i<BOARDCUL; i++)
    {
        for(j=1; j<BOARDCUL; j++)
        {
            k=i*BOARDCUL + j;
            if(bitb[0].get(k) && bitb[0].get(k-1) )
            {
                parent[k] = parent[k-1];
            }
            else if(bitb[1].get(k) && bitb[1].get(k -1) )
            {
                parent[k] = parent[k-1];
            }
        }
    }
    for(j=0; j<BOARDCUL; j++)
    {
        for(i=1; i <BOARDCUL; i++)
        {
            k =i*BOARDCUL + j;
            if(bitb[0].get(k) && bitb[0].get(k-BOARDCUL) )
            {
                unite(k,k-BOARDCUL);
            }
            else if(bitb[1].get(k) && bitb[1].get(k -BOARDCUL) )
            {
                unite(k,k-BOARDCUL);
            }
        }
    }
    getallair();
}

void board::clear()
{
    int i;
    for(i=0; i<BOARDSSIZE; i++)
    {
        parent[i]=i;
    }
#if SEARCH ==1
	zvalue = 0;
#endif
    bitb[0].clear();
    bitb[1].clear();
    ban[0].clear();
    ban[1].clear();
    notsafe[0].clear();
    notsafe[1].clear();
    memset(air,0,sizeof(air));
    memset(countair,0,sizeof(countair));
}


string board::inttostring(int i)
{
    string s = "A1";
    s[0]+= i / BOARDCUL;
    if(s[0]>='H')s[0]++;
    s[1]+= i % BOARDCUL;
    return s;
}

double board::simulate(bool j,int bone[BOARDSSIZE],int wone[BOARDSSIZE],int two[BOARDSSIZE] ,int bsize,int wsize ,int tsize )
{
    int i,k;
    bool bc,wc;
FLAG:
	// showboard();
	// system("pause");
    while(tsize>0)
    {
        i=rand()%tsize;
        k=two[i];
        two[i]=two[tsize-1];
        tsize--;
        bc=check(k,0);
        wc=check(k,1);
        if(check(k,j) )
        {
            if(j==0)
            {
                bpath[bpsize] = k;
                bpsize++;
            }
            else
            {
                wpath[wpsize] = k;
                wpsize++;
            }
            add(k,j);
            j=!j;
#if dolog ==1
            cout<<inttostring(k);
#endif
            goto FLAG;
        }else{
            if(!bc && wc)
            {
                wone[wsize]=k;
                wsize++;
            }
            else if(bc && !wc)
            {
                bone[bsize]=k;
                bsize++;
            }
        }
    }
FLAG2 :
    if(j==0)
    {

        while(bsize>0)
        {
            i=rand()%bsize;
            k=bone[i];
            bone[i]=bone[bsize-1];
            bsize--;
            if(check(k,j))
            {
                add(k,j);
                // bpath[bpsize] = k;
                // bpsize++;
                j=!j;
#if dolog ==1
                cout << inttostring(k);
#endif
                goto FLAG2;
            }
        }
    }
    else
    {
        while(wsize>0)
        {
            i=rand()%wsize;
            k=wone[i];
            wone[i]=wone[wsize-1];
            wsize--;
            if(check(k,j))
            {
                add(k,j);
                j=!j;
                //  wpath[wpsize] = k;
                //  wpsize++;
#if dolog ==1
                cout<<inttostring(k);
#endif
                goto FLAG2;
            }
        }
    }
    return (j==1)?1:-1;
}

bool board::isempty()
{
    return (bitb[0].isempty())&&(bitb[1].isempty());
}

