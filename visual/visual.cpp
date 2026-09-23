/*本题目主要考查类的使用,不了解类的同学建议先去学习相关知识。

    背景介绍：在Robomaster比赛中，一个机器人在进行自瞄的时候有时会同时识别到多个敌方目标。此时机器人需要
    选择其中一个来作为最佳打击目标并进行打击。通常我们会锁定距离准心（操作手端的屏幕中心）最近的目标。
    示例    ————————————————————————————————————————————
            |                       T                  |
            |        H            (1,4)                |
            |      (-9,3)                              |         
            |                                          |
            |                     +                    |      此时应当锁定S目标
            |                S                         |
            |              (-3,1)                      |
            |                              I           |
            |                            (7,-3)        |
            ————————————————————————————————————————————

    题目：编写一个程序，记录4个敌方目标的二维坐标，锁定距离准心最近的目标并输出对应的兵种ID。
    
    要求：采用面向对象的方法，设计两个类：
    Enemy 类：包含敌人的坐标和兵种ID，以及相应的设置和获取函数。
    Target 类：包含一个 Enemy 类的对象数组，并具备选择并返回最佳打击目标和输出的功能。

    PS：获取输入数据的框架已经替各位实现好了，在对应的地方调用你们编写的设置函数即可。
*/

#include <iostream>
#include <cmath>

using namespace std;

// ==================== 在此处编写 Enemy和Target 类 ====================
class Enemy{
private:
    char id;
    double x;
    double y;
public:
    void jilu(char id_1,double x1,double y1){
        id=id_1;
        x=x1;
        y=y1;
    }
    void check_dis(double *dis , char *t){
        if(*dis>x*x+y*y){
            *t = id;
            *dis = x*x+y*y;
        }
    }
};
//其实不知道什么要放到private里面，但是感觉如果全public那就没意义了？（不知）
class Target{
public:
    char check_t(Enemy e1,double &mini){
        char t;
        e1.check_dis(&mini,&t);
        return t;
    }
    
};

// ====================================================================


int main() {
    Target target;
    Enemy enemy[4];

    for (int i = 0; i < 4; i++) {//直接保证只有四个数据还是太仁慈了
        double x, y;
        char id;
        cout << "请输入第 " << i + 1 << " 个目标的兵种ID和坐标(x y): ";
        cin >> id >> x >> y;
        enemy[i].jilu(id,x,y);
        //在此处调用你的Enemy的设置函数，传入id,x,y
        
    }

    // 调用查找并输出最佳目标
    char ans='\0';
    double mini=1e9;
    int n=4;
    for(int i=0;i<n;i++){
        ans=target.check_t(enemy[i],mini);
    }
    cout<<"answer: "<<ans<<'\n';
    return 0;
}
