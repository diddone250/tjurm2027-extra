#include <iostream>
#include <vector>
#include <string>
#include <cstring> 
#include <queue>
#include <utility>
#include<array>

/*
 	现在你有一个类MAP_BASE，请编写他的子类，继承于MAP_BASE
 	可以看到map_in是一张地图，定义.是空地，#是障碍物，现在有一个的机器人想从左上角到达右下角，请在子类中写一个函数完成这件事情
 	要求：1.将机器人中心走过的路用C表示出来并输出整个地图
		  2.机器人是四向移动的，即只能向上下左右移动
      	  3.机器人走过的路线为所有可行的路线中最短的
	
	注意：答案不唯一，只要输出一种答案就可
	加分条件：现实中机器人是有大小的，不可能完全让中心靠墙移动，现在假设机器人需要3x3的空地才能安全移动，请给出能让机器人安全移动的路径

	示例：

	#############################	#############################			#############################
	#..............###..........#	#.C............###..........#			#.C............###..........#
	#........###................#	#.C......###................#			#.C......###................#
	#.........................###	#.C.......................###			#.C.......................###	
	#.........................###	#.CCCCCCCCCCCCCCCCCC......###			#.C.......................###
	#....................########	#..................C.########			#.C..................########
	#.....#####.................#	#.....#####........C........#			#.C...#####.................#
	#...........................#	#..................CCCCCCCC.#			#.CCCCCCCCCCCCCCCCCCCCCCCCC.#
	#...........................#	#...........................#			#...........................#
	#############################中	#############################是安全的而	 #############################是不安全的因为通过了2x2的空地
	同时
	#############################	           #############################
	#.C............###..........#	           #.C............###..........#
	#.C......###................#	           #.C......###................#
	#.C.......................###	           #.C.......................###	
	#.CCCCCCCCCCCCCC..........###	           #.CCCCCCCCCCCC.CCCCC......###
	#..............C.....########	           #............C.C...C.########
	#.....#####....C............#	           #.....#####..C.C...C........#
	#..............CCCCCCCCCCCC.#	           #............CCC...CCCCCCCC.#
	#...........................#			   #...........................#
	#############################也是可行的而	#############################是不可行的因为这不是最短路

*/
class MAP_BASE
{
	public:
		MAP_BASE()
		{
			map_in = {
	        "#######################################################################",
	        "#.............................................######...........##.....#",
	        "#...........#############........................######.......#########",
	        "#...........#####...........................###...####.......##########",
	        "##.............##.............#######.................................#",
	        "###...................................................................#",
	        "#.........####................######.......................####.......#",
	        "#..........##.........#.##...................######...................#",
	        "#.....................................................................#",
	        "#.............................##................................#######",
	        "#.....................................................................#",
	        "##########.............#######..########......#########...............#",
	        "#...............................###############.......................#",
	        "#######################################################################"
			};
			std::memset(visit, false, sizeof(visit));
		}
		std::vector<std::string> print_map(){
			return map_in;
		}
		bool vis(){
			return visit;
		}
		
		void print(std::vector<std::string> map_in)
		{
			for (const auto& line : map_in)
		        std::cout << line << '\n';
		}
	protected:
		std::vector<std::string> map_in;
		bool visit[100][100];
};

/**
*在map_in中将'.'替换成'C'表示机器人的路径。将最终的结果像示例里那样输出出来
*
* 提示：
* (1) 没有思路的同学可以先去了解一下深度优先搜索算法和广度优先搜索算法，思考应该用哪种方法。
* (2) 考虑使用队列queue数据结构
*
* 考点：
* (1) 类的使用。
* (2) 搜索算法。
*/

//IMPLEMENT YOUR CODE HERE

void bfs(){
	int dx[4]={-1,1,0,0};
	int dy[4]={0,0,-1,1};
	MAP_BASE map1;
	std::vector<std::string> tu=map1.print_map();
	int x0=1,y0=1;
	int n=tu.size();
	int m=tu[0].size();
	int xt=n-2,yt=m-2;
	std::vector<std::vector<int>> vis(n,std::vector<int>(m,-1));
	std::vector<std::vector<std::pair<int,int>>> pre(n,std::vector<std::pair<int,int>>(m,{-1,-1}));
	std::queue<std::pair<int,int>> q;
	q.push({1,1});
	while(!q.empty()){
		int x=q.front().first,y=q.front().second;
		q.pop();
		for(int d=0;d<4;d++){
			int nx=x+dx[d];
			int ny=y+dy[d];
			if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
			if(vis[nx][ny] != -1) continue;
			if(tu[nx][ny]=='#') continue;
			pre[nx][ny]={x,y};
			vis[nx][ny]=0;
			q.push({nx,ny});
		}
	}
	if(vis[xt][yt] == -1) std::cout<<"无以抵达"<<'\n';
	else{
		for(auto pl=std::make_pair(xt,yt);pl != std::make_pair(x0,y0);pl=pre[pl.first][pl.second]){
			tu[pl.first][pl.second]='@';
		}
		tu[x0][y0]='@';
		for(int i=0;i<n;i++){
			std::cout<<tu[i]<<'\n';
		}
	}
}


void bfs_sup(){
	int dx[8]={-1,1,0,0,-1,-1,1,1};
	int dy[8]={0,0,-1,1,-1,1,-1,1};
	MAP_BASE map1;
	std::vector<std::string> tu=map1.print_map();
	int x0=2,y0=2;
	int n=tu.size();
	int m=tu[0].size();
	int xt=n-3,yt=m-3;
	std::vector<std::vector<int>> vis(n,std::vector<int>(m,-1));
	std::vector<std::vector<std::pair<int,int>>> pre(n,std::vector<std::pair<int,int>>(m,{-1,-1}));
	std::queue<std::pair<int,int>> q;
	q.push({2,2});
	while(!q.empty()){
		int x=q.front().first,y=q.front().second;
		q.pop();
		for(int d=0;d<4;d++){
			int nx=x+dx[d];
			int ny=y+dy[d];
			if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
			if(vis[nx][ny] != -1) continue;
			if(tu[nx][ny]=='#') continue;
			bool flag=1;
			for(int i=0;i<8;i++){//与bfs不同的只有这一段，也就是判断八方向
				if(nx+dx[i] < 0 || nx+dx[i] >= n || ny+dy[i] < 0 || ny+dy[i] >= m) {
    				flag=false;
					break;
				}
				if(tu[nx+dx[i]][ny+dy[i]]=='#') {
					flag= false;
					break;
				}
			}
			if(!flag) continue;
			pre[nx][ny]={x,y};
			vis[nx][ny]=0;
			q.push({nx,ny});
		}
	}
	if(vis[xt][yt] == -1) std::cout<<"无以抵达"<<'\n';
	else{
		
		auto pl=std::make_pair(xt,yt);
		do{
            tu[pl.first][pl.second]='@';
			for(int i=0;i<8;i++){
				tu[pl.first+dx[i]][pl.second+dy[i]]='@' ;
			}
            pl=pre[pl.first][pl.second];
        }while(pl != std::make_pair(x0,y0));
		for(int i=0;i<8;i++){
			tu[x0+dx[i]][y0+dy[i]]='@' ;
		}
		for(int i=0;i<n;i++){
			std::cout<<tu[i]<<'\n';
		}
	}

}
void bfs_sup_turnmin(){
	int dx[8]={-1,1,0,0,-1,-1,1,1};
	int dy[8]={0,0,-1,1,-1,1,-1,1};
	
	MAP_BASE map1;
	std::vector<std::string> tu=map1.print_map();

	int x0=2,y0=2;
	int n=tu.size();
	int m=tu[0].size();
	int xt=n-3,yt=m-3;

	std::vector<std::vector<std::array<int,4>>> dist(n,std::vector<std::array<int,4>>(m));
	std::vector<std::vector<std::array<std::array<int,3>,4>>> pre(n,std::vector<std::array<std::array<int,3>,4>>(m));
	std::deque<std::array<int,3>> dq;
	for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            dist[i][j].fill(1e9);
	// [&]指代要引用的变量 ->表示输出形式为bool 感觉其实和函数挺像的
	auto valid = [&](int x, int y) -> bool {//这个是lambda,可以在函数内部出现的函数
        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i], ny = y + dy[i];
			if (tu[x][y] == '#') return false;
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) return false;
            if (tu[nx][ny] == '#') return false;
        }
        return true;
    };

	//first step
	for(int d=0;d<4;d++){
		int nx=x0+dx[d];
		int ny=y0+dy[d];
		if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
		if(!valid(nx,ny)) continue;
		pre[nx][ny][d]={x0,y0,-1};//用-1表示没有前置节点
		dist[nx][ny][d]=0;
		dq.push_front({nx,ny,d});
	}
	//start running
	while(!dq.empty()){//正常bfs,但是要有方向
		auto cur=dq.front();
		dq.pop_front();
		int x=cur[0],y=cur[1],d=cur[2];
		int curd=dist[x][y][d];
		for(int d2=0;d2<4;d2++){
			int nx=x+dx[d2],ny=y+dy[d2];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (!valid(nx, ny)) continue;
			int cost= (d == d2)? 0:1;
			if(dist[nx][ny][d2]>(cost+curd)){//判断方向，用权重表示：0表示不转，1表示转
				dist[nx][ny][d2]=(cost+curd);
				pre[nx][ny][d2]={x,y,d};
				if(cost == 0) dq.push_front({nx,ny,d2});
				else dq.push_back({nx,ny,d2});
			}
		}
	}


	int mini=1e9,minid;
	for(int d=0;d<4;d++){
		if(mini>dist[xt][yt][d]){
			mini=dist[xt][yt][d];
			minid=d;
		}
	}
	if(mini == 1e9)  std::cout<<"无以抵达"<<'\n';
	
	else{
		int curx=xt,cury=yt;
		int curd = minid;
		do{
            tu[curx][cury]='@';
			for(int i=0;i<8;i++){
				tu[curx+dx[i]][cury+dy[i]]='@' ;
			}
			auto p=pre[curx][cury][curd];//一定要先提取旧的值，然后再更新，不然会出现curx先更新后再更新cury导致错误
            curx = p[0];
			cury = p[1];
			curd = p[2];
        }while(!(curx==x0 &&cury == y0));//少一个最初的判断，直接暴力加上了
		for(int i=0;i<8;i++){
			tu[x0+dx[i]][y0+dy[i]]='@' ;
		}
		for(int i=0;i<n;i++){
			std::cout<<tu[i]<<'\n';
		}
	}
}
int main(){
	bfs_sup_turnmin();
	return 0;

}
