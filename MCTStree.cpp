#include "MCTStree.h"

double MCTStree::getscore( ucbnode* nodeptr, int child)
{
	ucbnode *tmp = (nodeptr->childptr)+child;
	char &p = tmp->place;
	bool &c = tmp->color;
	double &N = tmp->count ;
	double &NR = tmp->ravecount;
	double ret = tmp->ravemean*NR + tmp->mean*N +  sqrt( nodeptr->logc * N )* UCB_WEIGHT;
	//cout<<tmp->ravemean<<' '<<ret/(N+NR)<<' '<<N<<' '<<NR<<' '<<nodeptr->logc<<endl;
	//return tmp->mean + UCB_WEIGHT * sqrt(nodeptr->logc / (N + 1));
	return ret / (N+NR);
}

ucbnode* MCTStree::getbestchild(ucbnode* nodeptr)
{
	if(nodeptr->csize == 0)return NULL;
	int i,ret=0;
	double ans,tmp = getscore(nodeptr,0),tma;//tmp minus anwser
	ans=tmp;
	selectlist[0]=0;
	slsize = 1;
	for(i=1;i<(nodeptr->csize);i++)
	{
		tmp = getscore(nodeptr,i);
		tma = tmp-ans;
		if( tma > -0.0001 )//tmp >= ans
		{
			if(tma > 0.0001) // tmp > ans
			{
				selectlist[0]=i;
				slsize = 1;
				ans = tmp;
			}else  //tmp == ans
			{
				selectlist[slsize]=i;
				slsize ++ ;
			}
		}
	}
	//for(i=0;i<slsize;i++)
	//{
	//	cout<<selectlist[i]<<' ';
	//}
	//cout<<endl;
	ret = selectlist[ rand() % slsize ];
	return (nodeptr->childptr +ret);
}

void MCTStree::select(board &b)
{
	
	bool j = ! b.just_play_color();//next to play
	ucbnode* nodeptr = root;
	b.bpsize=0;
	b.wpsize=0;
	path.clear();
	path.push_back(nodeptr);
	while(nodeptr->childptr != NULL && nodeptr->csize != 0)
	{
		nodeptr = getbestchild(nodeptr);
		path.push_back(nodeptr);
	//	cout<<inttostring(nodeptr->place)<<' ';
		if(nodeptr->color == BLACK)
		{
			b.addbp(nodeptr->place);
			sbnum++;
		}else
		{
			b.addwp(nodeptr->place);
			swnum++;
		}
		b.add(nodeptr->place,nodeptr->color);
	}
//	b.showboard();
	//system("pause");
}
void MCTStree::update(double result,board& b)
{
	for(int i=0;i<path.size();i++)
	{
		path[i]->addresult(result);
		if(path[i] -> color ==0)
		{
			for(int j=0;j<b.wpsize;j++)
			{
				int k = (path[i]->child[b.wpath[j]]);
				if( k !=-1)
					((path[i]->childptr)+k)->addraveresult(result);
			}
		}else
		{
			for(int j=0;j<b.bpsize;j++)
			{
				int k = (path[i]->child[b.bpath[j]]);
				if( k != -1)
					((path[i]->childptr)+k)->addraveresult(result);
			}
		}
	}
}
void MCTStree::run_a_cycle()
{
	board b;
	double result;
	b =rboard;
	sbnum=swnum=0;
	select(b);
	ucbnode &last=(*(path.back()));
	ucbnode *nodeptr;
	if(last.csize==0 && last.count > basenum )//¦Ü¤Ösimulate 1 ¦¸
	{
		last.expansion(b,rave_num,rave_wnum);
		if(last.csize!=0)
		{
			totalnode+=last.csize;
			nodeptr = getbestchild(&last);
			path.push_back(nodeptr);
			if(nodeptr->color == 0)
			{
				b.addbp(nodeptr->place);
				sbnum++;
			}else
			{
				b.addwp(nodeptr->place);
				swnum++;
			}
			b.add(nodeptr->place,nodeptr->color);
			
		}
	}
	total += sbnum;
	total += swnum;
	b.getv(bone,wone,two,bsize,wsize,tsize);
	
	if((b.just_play_color()==BLACK) && (wsize + tsize)==0)
	{
		result = 1;
	}else if(b.just_play_color()==WHITE && (bsize + tsize)==0)
	{
		result = -1;
	}else
	{
		result=b.simulate(!b.just_play_color(),bone,wone,two,bsize,wsize,tsize);
	}
	update(result,b);
}
void MCTStree::reset(board &b)
{
	rboard=b;
	root = new ucbnode;
	root -> color = rboard.just_play_color();
	root -> place = 81;
	root -> count = basenum;
	root -> logc = 1;
	memset(root -> child,-1,sizeof(root -> child)  );
	root-> expansion(b,rave_num,rave_wnum);
	total = 0;
	totalnode =0;
}

void MCTStree::show_path()
{
	ucbnode* nodeptr = root;
	int i,k;
	i=0;
	while( nodeptr->childptr != NULL && i<10)
	{
		k=nodeptr ->getbestmove();
		nodeptr = nodeptr->childptr +k;
		i++;
		if(nodeptr != NULL){
			if(nodeptr->color == BLACK)
				cerr<<"B(";
			else
				cerr<<"W(";
			cerr<<inttostring(nodeptr -> place)<<") ";
		}
	}
	cerr<<endl;
}
void MCTStree::clear()
{
	if( root != NULL)delete root;
}
string MCTStree::inttoGTPstring(int i)
{
    string s = "A1";
    s[0]+= i / 9;
    if(s[0]>='I')s[0]++;
    s[1]+= i % 9;
    return s;
}
string MCTStree::inttostring(int i)
{
    return inttoGTPstring(i);
}

MCTStree::MCTStree()
{
	;
}

MCTStree::~MCTStree()
{
	;
}

