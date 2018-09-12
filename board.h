#ifndef BOARDH
#define BOARDH
#include"bitboard.h"
#include<iostream>
#include<map>
#include<string.h>
#include<vector>
#include<stdio.h>
#include<string>
#include<stdlib.h>
//#include<Windows.h>

#include"boardcn.h"
#include<math.h>
#define BLACK 0
#define WHITE 1
#define SEARCH 0
#define search 0
using namespace std;

class board
{
public:
    /*
    0  1  2  3  4
    5  6  7  8  9
    10 11 12 13 14
    15 16 17 18 19
    20 21 22 23 24
    */
    bitboard ban[2];
    bitboard notsafe[2];
    const static boardcn nb;// neighbor

#if SEARCH == 1
    static zhashtable ztable;
    unsigned long long zValue;
#endif
    static char bpath[BOARDSSIZE+10];
    static int bpsize;
    static char wpath[BOARDSSIZE+10];
    static int wpsize;
    bitboard bitb[2];	
    char parent[BOARDCUL*BOARDCUL];
    bitboard air[BOARDCUL*BOARDCUL];
    char countair[BOARDSSIZE];


    int findParent(int i);
    void unite(int x,int y);
    void getallair();
    bool check_is_end();
    void add(int i,bool j);
    bool check(int i,bool j);
	void showboard();
    void showParent();
    void showAir();
    board();
    board(bitboard bb,bitboard ww);
    void Initboard(bitboard bb = bitboard(),bitboard ww = bitboard());
    inline bool get(int i,bool j);
    bool just_play_color();
    void getv(int bone[BOARDSSIZE],int wone[BOARDSSIZE],int two[BOARDSSIZE] ,int &bsize,int &wsize ,int &tsize);
    void getvec(vector<char> &bone,vector<char> &wone ,vector<char> &two );
    void setdata();
    void clear();
    string inttostring(int i);
    double simulate(bool j,int bone[BOARDSSIZE],int wone[BOARDSSIZE],int two[BOARDSSIZE] ,int bsize,int wsize ,int tsize );
    bool isempty();
	inline void addbp(int k)
	{
		bpath[bpsize] = k;
		bpsize++;
	}
	inline void addwp(int k)
	{
		wpath[wpsize] = k;
		wpsize++;
	}
#if search == 2
    void getnogo()
    {
        nogo.clear();
        for(int i=0; i < BOARDSSIZE; i++)
        {
            if(!bitb[0].get(i) && !bitb[1].get(i) && !check(i,0) && !check(i,1) )
            {
                nogo.push_back(i);
            }
        }
    }
    void getConnectNogo()
    {
        getnogo();
        vector<char> bstack,wstack;
        bstack=wstack=nogo;
        int i,j,k,x,y;
        while(bstack.size() != 0)
        {
            i=bstack[bstack.size()-1];
            bstack.pop_back();
            if(CN[0].get(i))
            {
                continue;
            }
            CN[0].add(i);
            x=i/BOARDCUL; // ROW
            y=i%BOARDCUL; // CUL
            if( x != 0)
            {
                k=i-BOARDCUL;
                if(bitb[0].get(k) == true)
                {
                    bstack.push_back(k);
                }
                else if( check(k,0) && !check(k,1) )  // no go
                {
                    bstack.push_back(k);
                }
            }
            if( x != BOARDCUL - 1)
            {
                k=i+BOARDCUL;
                if(bitb[0].get(k) == true)
                {
                    bstack.push_back(k);
                }
                else if( check(k,0) && !check(k,1) )  // no go
                {
                    bstack.push_back(k);
                }
            }
            if( y != 0)
            {
                k=i-1;
                if(bitb[0].get(k) == true)
                {
                    bstack.push_back(k);
                }
                else if( check(k,0) && !check(k,1) )  // no go
                {
                    bstack.push_back(k);
                }
            }
            if(y != BOARDCUL - 1)
            {
                k=i+1;
                if(bitb[0].get(k) == true)
                {
                    bstack.push_back(k);
                }
                else if( check(k,0) && !check(k,1) )  // no go
                {
                    bstack.push_back(k);
                }
            }

        }
        while(wstack.size() != 0)
        {
            i=wstack[wstack.size()-1];
            wstack.pop_back();
            if(CN[1].get(i))
            {
                continue;
            }
            CN[1].add(i);
            x=i/BOARDCUL; // ROW
            y=i%BOARDCUL; // CUL
            if( x != 0)
            {
                k=i-BOARDCUL;
                if(bitb[1].get(k) == true)
                {
                    wstack.push_back(k);
                }
                else if( check(k,1) && !check(k,0) )  // no go
                {
                    wstack.push_back(k);
                }
            }
            if( x != BOARDCUL - 1)
            {
                k=i+BOARDCUL;
                if(bitb[1].get(k) == true)
                {
                    wstack.push_back(k);
                }
                else if( check(k,1) && !check(k,0) )  // no go
                {
                    wstack.push_back(k);
                }
            }
            if( y != 0)
            {
                k=i-1;
                if(bitb[1].get(k) == true)
                {
                    wstack.push_back(k);
                }
                else if( check(k,1) && !check(k,0) )  // no go
                {
                    wstack.push_back(k);
                }
            }
            if(y != BOARDCUL - 1)
            {
                k=i+1;
                if(bitb[1].get(k) == true)
                {
                    wstack.push_back(k);
                }
                else if( check(k,1) && !check(k,0) )  // no go
                {
                    wstack.push_back(k);
                }
            }

        }
        for(i=0; i<BOARDSSIZE; i++)
        {
            if(bitb[0].get(i) || bitb[1].get(i))
            {
                continue;
            }
            bool bF,wF;
            bF=wF=false;
            x=i/BOARDCUL; // ROW
            y=i%BOARDCUL; // CUL
            if( x != 0 )
            {
                k=i-BOARDCUL;
                if(CN[0].get(k)==true)bF=true;
                if(CN[1].get(k)==true)wF=true;
            }
            if( x != BOARDCUL - 1)
            {
                k=i+BOARDCUL;
                if(CN[0].get(k)==true)bF=true;
                if(CN[1].get(k)==true)wF=true;
            }
            if( y != 0)
            {
                k=i-1;
                if(CN[0].get(k)==true)bF=true;
                if(CN[1].get(k)==true)wF=true;
            }
            if(y != BOARDCUL - 1)
            {
                k=i+1;
                if(CN[0].get(k)==true)bF=true;
                if(CN[1].get(k)==true)wF=true;
            }
            if(bF && wF)
            {
                twoCN.add(i);
            }
        }
    }
    bool checkStar(int i,bool j)
    {
        int x,y,k;
        x=i/BOARDCUL; // ROW
        y=i%BOARDCUL; // CUL
        if(x != 0 )
        {
            k=i-BOARDCUL;
            if(!CN[0].get(k) && !CN[1].get(k) && !twoCN.get(k) && !bitb[j].get(k))return false;
        }
        if(x != BOARDCUL -1 )
        {
            k=i+BOARDCUL;
            if(!CN[0].get(k) && !CN[1].get(k) && !twoCN.get(k) && !bitb[j].get(k))return false;
        }
        if(y != 0 )
        {
            k=i-1;
            if(!CN[0].get(k) && !CN[1].get(k) && !twoCN.get(k) && !bitb[j].get(k))return false;
        }
        if(y != BOARDCUL -1 )
        {
            k=i+1;
            if(!CN[0].get(k) && !CN[1].get(k) && !twoCN.get(k) && !bitb[j].get(k))return false;
        }
        return true;
    }
    void getStar()
    {
        getConnectNogo();
        for(int i=0; i<BOARDSSIZE; i++)
        {
            bool f;
            int x,y,k;
            if( check(i,0) && !check(i,1) && checkStar(i,0) )
            {
                Star[0].add(i);
            }
            if( check(i,1) && !check(i,0) && checkStar(i,1) )
            {
                Star[1].add(i);
            }
        }
    }
    void showNST()
    {
        for(int i=0; i<BOARDCUL; i++)
        {
            for(int j=0; j<BOARDCUL; j++)
            {
                int k=i*BOARDCUL+j;
                if(bitb[0].get(k)) cout<<'@';
                else if(bitb[1].get(k)) cout<<'O';
                else if(Star[0].get(k))
                {
                    if(CN[0].get(k)) cout<<'T';
                    else cout<<'S';
                }
                else if(Star[1].get(k))
                {
                    if(CN[1].get(k)) cout<<'t';
                    else cout<<'s';
                }
                else cout<<'.';
            }
            cout<<endl;
        }
    }
    bool checkTriangle(int i,int j)
    {
        if(Star[j].get(i) && CN[j].get(i))return true;
        return false;
    }
#endif
};
#if SEARCH == 1
zhashtable board :: ztable;
#endif


#endif

