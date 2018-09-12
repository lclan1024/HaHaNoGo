#ifndef BOARDCN_H
#define BOARDCN_H
using namespace std;

class boardcn
{
public:
    char nb[BOARDSSIZE][4];
    char nbsize[BOARDSSIZE];
    boardcn()
    {
        for(int i=0; i<BOARDCUL; i++)
        {
            for(int j=0; j<BOARDCUL; j++)
            {
                int k=i*BOARDCUL+j;
                int r=0;
                if(i>0)nb[k][r]=k-BOARDCUL,r++;
                if(j>0)nb[k][r]=k-1,r++;;
                if(i<BOARDCUL-1)nb[k][r]=k+BOARDCUL,r++;;
                if(j<BOARDCUL-1)nb[k][r]=k+1,r++;;
                nbsize[k]=r;

            }
        }
    }

};
#endif