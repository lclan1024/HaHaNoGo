#ifndef UCBNODE_H
#define UCBNODE_H
#include "board.h"
#include <math.h>
#define basenum 0
#define ravenum 20

#define minusnum (basenum - 2)//不能減一
#define minusrnum (ravenum - 2)
const double UCB_WEIGHT = 0.25;
class ucbnode
{

public:
	char place;//此步下哪
	bool color;//誰下的
	char child[BOARDSSIZE+1];//找小孩
	int csize;
	ucbnode* childptr;
	double count;//basenum + real
	double mean; //1:color 贏 0:color 輸
	double ravecount;//ravenum +real
	double ravemean;// 1 color 贏  -1 color 輸
	double logc;

    void initucbnode(int i,bool j,double rm,double rn);
    void addresult(double result);
    void addraveresult(double result);
    int getbestmove();
	vector<float> getPolicy();
    void show_child();
    float show_inf(int child);
    void expansion(board &b,double rave_num[2][BOARDSSIZE] ,double rave_wnum[2][BOARDSSIZE]);
	string inttostring(int i);
    string inttoGTPstring(int i);
	ucbnode();
	~ucbnode();
	void setlogc();
};
#endif //UCBNODE_H