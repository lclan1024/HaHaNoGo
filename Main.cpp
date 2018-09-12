#include <iostream>
#include <set>
#include <map>
//#include <Windows.h>
#include <vector>
#include <stdio.h>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <string.h>
#include <sstream>
#include"MCTStree.h"
using namespace std;

string toSGFstring(int i)
{
	string s="aa";
	s[0] += (i/BOARDCUL);
	s[1] += (i%BOARDCUL);
	return s;
}

int GTPstringtoint(string s)
{
	if(s[0]>='a'&&s[0]<='z')
	{
		int x=s[0]-'a';
		if(s[0]>'i')x--;
		int y=s[1]-'1';
		return x*BOARDCUL+y;
	}else
	{
		int x=s[0]-'A';
		if(s[0]>'I')x--;
		int y=s[1]-'1';
		return x*BOARDCUL+y;
	}
	
}
string inttoGTPstring(int i)
{
	string s = "A1";
    s[0]+= i / 9;
    if(s[0]>='I')s[0]++;
    s[1]+= i % 9;
    return s;
}
MCTStree tree;

int main(int argc, char** argv)
{
	int i,k;
	int simulationCnt=50000;
	double t;
	string s,c,p;
	t=10000;
	if (argc == 2)
	{
		istringstream (string(argv[1])) >> simulationCnt;
		cerr << "set simulation cnt to: " << simulationCnt << endl;
	}
	bool j;
	board b;
	tree.clear();
	b.clear();
	srand(time(NULL)) ;
	vector<float> policy;
	float value;
	//freopen("0016086.txt","w",stdout);
	while(cin>>s)
	{
		if(s=="play"||s=="p")
		{
			cin>>c>>p;
			if(c[0]=='b' || c[0]=='B')j=0;
			else j=1;
			b.add(GTPstringtoint(p),j);
			cout<<"="<<endl<<endl;
		}
		else if(s[0]=='e')
		{
			cout<<b.isempty()<<endl<<endl;
		}
		else if(s[0]=='c')
		{
			b.clear();
			cout<<"="<<endl<<endl;
		}else if(s[0]=='g' || s == "reg_genmove")
		{
			bool j,f=false;
			int st,e;
			cin>>c;
			j=!b.just_play_color();
			for(i=0;i<BOARDSSIZE;i++)
			{
				if(b.check(i,j))
				{
					f=true;
					break;
				}
			}
			if(!f)
			{
				cout<<"=resign"<<endl<<endl;
				continue;
			}
			tree.reset(b);
			e = st = clock();
			int simulationFinishedCnt = 0;
			//while(e-st<t)
			while(simulationFinishedCnt < simulationCnt)
			{
				tree.run_a_cycle();
				tree.run_a_cycle();
				tree.run_a_cycle();
				tree.run_a_cycle();
				tree.run_a_cycle();
				tree.run_a_cycle();
				tree.run_a_cycle();
				tree.run_a_cycle();
				tree.run_a_cycle();
				tree.run_a_cycle();
				simulationFinishedCnt +=10;
				e=clock();
				if(simulationFinishedCnt %10000==0)
				{
					tree.show_path();
				}
			}
			k= tree.root -> getbestmove();
			ucbnode* tmp = tree.root -> childptr;
			int best_move = (tmp+k)->place;
			policy = tree.root->getPolicy();
			tree.root ->show_child();
			value = tree.root ->show_inf(k);
			cerr<<"simulation time : "<< (double)(e-st) / 1000.0<<endl;
			cerr<<"average deep : "<<(double)tree.total / (double)i<<endl;
			cerr<<"total node : "<< tree.totalnode<<endl;
			cerr<<"average speed : "<< (simulationFinishedCnt*1000) / (e-st) <<endl;
			tree.show_path();
			if(s != "reg_genmove")
				b.add(best_move, !b.just_play_color());
			if(value > 0.2)
			{
				cout<<"="<<inttoGTPstring(best_move)<<endl<<endl;
			}else
			{
				cout<<"=resign"<<endl<<endl;
			}
			
			tree.clear();

		}
		else if (s == "policy")
		{
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					cout << policy[i * 9 + j] << ' ';
				}
				cout << endl;
			}
			
		}
		else if (s == "value")
		{
			cout << value << endl;
		}
		else if (s == "protocol_version")
		{
			cout<<"=2\n\n";
		}
		else if (s == "rev")
		{
			int bsize, wsize, tsize;
			int bone[BOARDSSIZE], wone[BOARDSSIZE], two[BOARDSSIZE];
			float x;
			cin >> x;
			float sum = 0;
			for (int i = 0; i < x; i++)
			{
				board tmpb = b;
				tmpb.getv(bone, wone, two, bsize, wsize, tsize);
				sum += tmpb.simulate(!tmpb.just_play_color(), bone, wone, two, bsize, wsize, tsize);
			}
			cout << sum / x << endl;
		}
		else if(s== "name")
		{
			cout<<"=haha"<< UCB_WEIGHT * 100<<"_rn"<<ravenum<<"_bn"<<basenum << "\n\n";
		}else if(s== "time")
		{
			cin>>t;
			t*=1000;
			t++;
			cout<<"="<<endl<<endl;
		}else if(s == "boardsize")
		{
			cin>>s;
			cout<<"="<<endl<<endl;
		}else if(s == "komi")
		{
			cin>>s;
			cout<<"="<<endl<<endl;
		}else if(s == "time_left")
		{
			cin>>s>>s>>s;
			cout<<"="<<endl<<endl;
		}else if(s == "showboard" || s == "sb")
		{
			b.showboard();
			cout<<endl;
		}
		else
		{
			cout<<"="<<endl<<endl;
		}
	}
}
//
//int main()
//{
//	int i,j,cb,cw,d;
//	long long k,l;
//	bool r;
//	srand(time(NULL));
//	string s;
//	board a;
//	d=1;
//	while(1)
//	{
//		cb=cw=0;
//		a.clear();
//		for(i=0;i<BOARDROW;i++)
//		{
//			cin>>s;
//			for(j=0;j<s.size();j++)
//			{
//				k=i*BOARDCUL+j;
//				if(s[j]=='@')
//				{
//					cb++;
//					a.add(k,0);
//				}else if(s[j]=='O')
//				{
//					cw++;
//					a.add(k,1);
//				}
//			}
//			
//		}
//#if dolog ==1
//		freopen("log.txt","w",stdout);
//		cout<<"==PlayedSgf:AB";
//		for(i=0;i<BOARDSSIZE;i++)
//		{
//			if(a.get(i,0))
//			{
//				cout<<'['<<toSGFstring(i)<<']';
//			}
//		}
//		cout<<"AW";
//		for(i=0;i<BOARDSSIZE;i++)
//		{
//			if(a.get(i,1))
//			{
//				cout<<'['<<toSGFstring(i)<<']';
//			}
//		}
//		cout<<endl;
//#endif
//		
//		if(a.bitb[0].count() ==0 && a.bitb[1].count() == 0 )tree.newboard();
//		else tree.reset(a);
//		int ss,tt;
//		ss=clock();
//		for(i=1;i<=100000;i++)
//		{
//#if dolog ==1
//			cout<<'('<<i<<')';
//#endif
//			tree.run_a_cycle();
//		}
//		tt=clock();
//		cout<<tt-ss<<endl;
//		tree.getbestmove();
//		tree.clear();
//	}
//}
		/*
.@OOO@@OO
O@@OOO@OO
@@OO@O@@.
.@@O@O@@O
O@O.@@O.@
@O@@OO@@O
@.@.@OOO.
O.O@@O@@O
@@OOOO@.@


*/
// @.... .@... .O... .O... .... .... .... .... ....
// .@ @. ....O ....O . . . . .
// @ .	 . . . . . . .
//  . . . . . . . . .
/*

.........
.........
.........
.........
.........
.........
.........
.........
.........

@@OOO.@@.
.@@@...O@
@@@.O@@O.
@.OOO..O.
@O@.O@@.O
..O.OO.O@
@@@.OO.O@
.O....@.@
..OO..O..

.@@.@O.O@
.O..@@O..
@.O..@O.O
..@......
...O@.@.O
O...@.@..
O.O...O..
@.O...@.O
.@...O..@

..@O.....
@O.O@O@..
.........
.@..O....
.@.......
.O.O....@
....O....
.....@.O.
.....@..@

@....@@.O
.@OO.@.O@
..OOO@@..
O.@@.....
..@O...@O
.@@O@OOO.
O.OO...O.
O@......@
..@O...@@

O....OOO@
..@O.O...
....@@...
@.O....@.
OO@@.O.@O
.O@@.O.@.
.@..@..@.
.....@..@
@..@OOOOO

.@.....@.
@.......@
....O....
........
.........
....O....
.O.......
......O..
.........

.O.O.O.O.
O.O.O.O.O
.........
.........
.@.....O.
....@.O.O
.@.......
......@..
....@..O.






*/

//int main()
//{
//	int i,j,cb,cw,d;
//	long long k,l;
//	bool r;
//	srand(time(NULL));
//	string s;
//	board a;
//	d=1;
//	//freopen("output.txt","w",stdout);
//	while(1)
//	{
//		cb=cw=0;
//		a.clear();
//		for(i=0;i<BOARDROW;i++)
//		{
//			cin>>s;
//			for(j=0;j<s.size();j++)
//			{
//				k=i*BOARDCUL+j;
//				if(s[j]=='@')
//				{
//					cb++;
//					a.add(k,0);
//				}else if(s[j]=='O')
//				{
//					cw++;
//					a.add(k,1);
//				}
//			}
//			
//		}
//		int bsize,wsize,tsize;
//		int bone[BOARDSSIZE],wone[BOARDSSIZE],two[BOARDSSIZE],x[BOARDSSIZE],y[BOARDSSIZE],z[BOARDSSIZE];
//		a.getv(bone,wone,two,bsize,wsize,tsize);
//		/*for(i=0;i<two.size();i++)
//		{
//			cout<<two[i]<<' ';
//		}
//		cout<<endl;
//		for(i=0;i<bone.size();i++)
//		{
//			cout<<bone[i]<<' ';
//		}
//		cout<<endl;
//		for(i=0;i<wone.size();i++)
//		{
//			cout<<wone[i]<<' ';
//		}
//		cout<<endl;*/
//		
//		k=0;
//		l=0;
//		if(cb>cw)
//		{
//			r=1;
//		}else
//		{
//			r=0;
//		}
//		board tmp;
//		for(i=0;i<9;i++){
//			for(j=0;j<9;j++)
//			{
//				k=i*9+j;
//				cout<<a.checkgetblock(k,1)<<' ';
//			}
//			cout<<endl;
//		}
//		i=j=clock();
//		while(i-j<1001)
//		{
//			tmp = a;
//			memcpy(x,bone,sizeof(bone));
//			memcpy(y,wone,sizeof(wone));
//			memcpy(z,two,sizeof(two));
//			k++;
//			if(!tmp.simulate(r,x,y,z,bsize,wsize,tsize) )l++;
//			i=clock();
//		}
//		//cout<<"Playout Cnt:"<<k<<endl;
//		if(r==0)printf("Black win rate : %.4f\n",(double)l/(double)k);
//		else printf("White win rate : %.4f\n",1.00-(double)l/(double)k);
//		cout<<d<<":"<<k<<endl;
//		d++;
//	}
	
//}
