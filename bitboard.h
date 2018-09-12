#ifndef BITBOARDH
#define BITBOARDH
#define BOARDROW 9
#define BOARDCUL 9
#define BOARDSSIZE  81
#define dolog 0
#define RAVE 1
#include<string.h>
#include<iostream>
#include<cstdio>
using namespace std;
class bitboard
{
public:
	unsigned long long x[(BOARDSSIZE/64)+1];
	bitboard()
	{
		x[0]=0LL;
		x[1]=0LL;
	}
	int num(int i)
	{
		unsigned long long v;
		v = (x[i] & 0x5555555555555555LL)+( (x[i]>>1) &0x5555555555555555LL);
		v = (v & 0x3333333333333333LL)+( (v>>2) &0x3333333333333333LL);
		v = (v & 0x0f0f0f0f0f0f0f0fLL)+( (v>>4) &0x0f0f0f0f0f0f0f0fLL);
		v = (v & 0x00ff00ff00ff00ffLL)+( (v>>8) &0x00ff00ff00ff00ffLL);
		v = (v & 0x0000ffff0000ffffLL)+( (v>>16) &0x0000ffff0000ffffLL);
		return (int)( (v & 0x00000000fffffffffLL)+( (v>>32) &0x00000000ffffffffLL) );
	}
	void clear()
	{
		x[0]=0;x[1]=0;
	}
	int count()
	{
		unsigned long long v,v1;
		v = (x[0] & 0x5555555555555555LL)+( (x[0]>>1) &0x5555555555555555LL);
		v1 = (x[1] & 0x5555555555555555LL)+( (x[1]>>1) &0x5555555555555555LL);
		v = (v & 0x3333333333333333LL)+( (v>>2) &0x3333333333333333LL);
		v1 = (v1 & 0x3333333333333333LL)+( (v1>>2) &0x3333333333333333LL);
		v += v1;
		v = (v & 0x0f0f0f0f0f0f0f0fLL)+( (v>>4) &0x0f0f0f0f0f0f0f0fLL);
		v = (v & 0x00ff00ff00ff00ffLL)+( (v>>8) &0x00ff00ff00ff00ffLL);
		v = (v & 0x0000ffff0000ffffLL)+( (v>>16) &0x0000ffff0000ffffLL);
		return (int)( (v & 0x00000000fffffffffLL)+( (v>>32) &0x00000000ffffffffLL) );
	}
	bool get(int i)
	{
		return (x[i>>6]&(1LL<<(i&63)))!=0;
	}
	void minus(int i)
	{
		x[i>>6]  &= ~ (1LL << (i &63));
	}
	void add(int i)
	{
		x[i>>6] |= (1LL<<(i & 63));
	}
    void operator |= (bitboard b)
	{
		x[0]|=b.x[0];
		x[1]|=b.x[1];
		return ;
	}
	void showboard(bool j=0)
	{
		int i;
		for(i=0;i<BOARDCUL*BOARDCUL;i++)
		{
			if(get(i))
			{
				if(j==0)cout<<'@';
				else cout<<'O';
			}else
			{
				cout<<'.';
			}
			if(i%BOARDCUL == BOARDCUL -1)
			{
				cout<<endl;
			}
		}
	}
	bool isempty()
	{
		return (x[0]==0)&&(x[1]==0);
	}
};


#endif
