
#include<stdlib.h>
#include<Windows.h>
#include<time.h>
#include<iostream>
using namespace std;
class zhashtable
{
public :
	unsigned long long ZHT[2][BOARDSSIZE];
	
	zhashtable()
	{
		srand((unsigned int)time(NULL));
		for(int i=0;i<BOARDSSIZE;i++)
		{
			ZHT[0][i]=rand()*(RAND_MAX+1)+rand()+((rand()&1)<<30);
			ZHT[0][i]=ZHT[0][i]<<32;
			ZHT[0][i]+=rand()*(RAND_MAX+1)+rand()+((rand()&3)<<30);
			ZHT[1][i]=rand()*(RAND_MAX+1)+rand()+((rand()&1)<<30);
			ZHT[1][i]=ZHT[1][i]<<32;
			ZHT[1][i]+=rand()*(RAND_MAX+1)+rand()+((rand()&3)<<30);
		}
	}

};
