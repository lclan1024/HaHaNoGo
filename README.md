HaHaNoGo
===============
This is the NoGo program that won against HappyNoGo and got the first place in TAAI 2016. (http://www.cs.nthu.edu.tw/~taai2016/game.html) 

| Gold | Silver | Bronze |
| -------- | -------- | -------- |
| HaHaNoGo    | HappyNoGo     | Deep Nikita     |

HaHaNoGo uses the same algorithm as HappyNoGo (https://ir.nctu.edu.tw/handle/11536/73344), which was the champion of the Computer Olympiad of NoGo in 2013 and 2015.

## NoGo
NoGo is a combinatorial game that has similar rules as Go. The full definition is described in the following website https://webdocs.cs.ualberta.ca/~mmueller/nogo/index.html. 

## Design
MCTS and Rapid Action Value Estimation (RAVE) are the base of our program. We also use the same rollout policy as HappyNoGo. However, we do not use the prior knowledge mentioned in the paper to initial the unvisited nodes.
Another difference is that we implement a faster way to check the illegal moves of a game state. This makes our program almost two times faster than using a naive way. 

## Usage
Our program is a very light weighted program that only needs basic c++ compiler to compile it. We also add a cmakeList to allow people to compile it with cmake.
Since NoGo is similar to Go, the command of our program is the same as Go Text Protocol (GTP) (http://www.gnu.org/software/gnugo/gnugo_19.html). We recommend using GoGui (https://sourceforge.net/projects/gogui/) or any other program that support GTP to play with our program. 

## Results
Our program plays almost the same as HappyNoGo but much faster since we do not need to compute the prior knowledge and our rollout is faster. The followings are self-play games played by our program with 1k, 10k, 100k simulations. More examples are in the self-play directory. 

![](https://i.imgur.com/UntgrcE.png)[1k, black wins]

![](https://i.imgur.com/z9F5fM7.png)[10k, black wins]

![](https://i.imgur.com/q4jjAAJ.png)[100k, white wins]

