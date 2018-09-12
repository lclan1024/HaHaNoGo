#include "ucbnode.h"


void ucbnode::setlogc()
{
    logc = log(count);
}
ucbnode::ucbnode()
{
    
}
ucbnode::~ucbnode()
{
    if(childptr != NULL) {delete [] childptr;childptr=NULL;}
}


void ucbnode::initucbnode(int i,bool j,double rmean,double rnum)
{
    color=j;
    place=i;
    mean = 0.5;
    count = basenum;
    csize=0;
    ravecount = rnum;
    ravemean = rmean;
    memset(child,-1,sizeof(child));
    childptr=NULL;
    logc=1;
}

void ucbnode::addresult(double result)
{
    if((result > 0 && color==BLACK) || (result < 0 && color==WHITE) )
    {
        mean = (mean*count+1.00)/(count+1);
    }else
    {
        mean = (mean*count)/(count+1);
    }
    count+=1;
    setlogc();
}
void ucbnode::addraveresult(double result)//result:-1 ¥ÕÄ¹ 1 ¶ÂÄ¹
{
    if((result > 0 && color==BLACK) || (result < 0 && color==WHITE) )
    {
        ravemean = (ravemean*ravecount+1.00)/(ravecount+1);
    }else
    {
        ravemean = (ravemean*ravecount)/(ravecount+1);
    }
    ravecount+=1;
}
void ucbnode::expansion(board &b,double rave_num[2][BOARDSSIZE] ,double rave_wnum[2][BOARDSSIZE])
{
	int i,k;
	bool j;
	j=!b.just_play_color();
	csize=0;
	for(i=0;i<BOARDSSIZE;i++)
	{
		if(b.check(i,j))
		{
			csize++;
		}
	}
	if(csize==0)
	{
		return;
	}
	childptr = new ucbnode [csize];
	double rmean,rnum;
	k=0;
	for(i=0;i<BOARDSSIZE;i++)
	{
		if(b.check(i,j))
		{
			child[i]=k;
			rmean = 0.5;
			rnum = ravenum;
			childptr[k].initucbnode(i,j,rmean,rnum);
			k++;
		}
	}
}
int ucbnode::getbestmove()
{
	int ret = -1;
	double ans=-100,tmp;
	for(int i = 0;i<csize;i++)
	{
		tmp = childptr[i].count;// * childptr[i].mean;
		if(tmp > ans)
		{
			ans = tmp;
			ret=i;
		}
	}
	return ret;
}

vector<float> ucbnode::getPolicy()
{
	vector<float> ret(BOARDSSIZE, 0);
	float sum = 0;
	for (int i = 0; i < csize; i++)
	{
		sum+= childptr[i].count;
	}
	for (int i = 0; i < csize; i++)
	{
		ret[childptr[i].place] = childptr[i].count / sum;
	}
	return ret;
}

void ucbnode::show_child()
{
	for(int i=0;i<csize;i++)
	{
		if(childptr[i].count<10)continue;
		cerr<< inttoGTPstring((int)childptr[i].place)<<' '<<childptr[i].mean<<' '<<childptr[i].count<<' ';
		//cerr<<sqrt( logc / ((childptr[i].count) - minusnum))* UCB_WEIGHT<<' ' ;
		cerr<<(childptr[i].ravemean)<<' '<<(childptr[i].ravecount)<<endl;
	}
}
float ucbnode::show_inf(int best)
{
		cerr<<"total : "<< count -basenum <<endl<<"winrate :"<<(childptr[best].mean);
		//cerr<<"\nlog : "<<sqrt( logc / ((childptr[best].count) - minusnum))* UCB_WEIGHT ;
		cerr<<"\nrave : "<<(childptr[best].ravemean)<<' '<<(childptr[best].ravecount)<<endl;
		return childptr[best].mean;
}

string ucbnode::inttoGTPstring(int i)
{
    string s = "A1";
    s[0]+= i / 9;
    if(s[0]>='I')s[0]++;
    s[1]+= i % 9;
    return s;
}
string ucbnode::inttostring(int i)
{
    return inttoGTPstring(i);
}