#ifndef CHESS_H
#define CHESS_H
#define Size_x 15
#define Size_y 15
//α-β剪枝算法的迭代深度
#define limited_depth 2
#include<string.h>
#include<vector>
//定义棋盘上每个点的状态
enum state { Empty = 0, Human = -1, Machine = 1 };

struct Action {
    int chessX;
    int chessY;
    state who=state::Empty;

};
//棋盘状态的数据结构
class chess
{
    using vet = int(*)[Size_x];
    //存放棋盘先前状态以悔棋

    static std::vector<vet> prev;
    static vet now;
    //指向存放棋盘现状态的二维数组
private:
    vet chessboard;
    //指向存放棋盘现状态的后继状态
    std::vector<chess*> successors;
    //指向存放棋盘状态的评估值
    int evaluation;
    std::vector<Action> action;
public:
    //生成棋盘初始状态
    chess();
    //由棋盘现状态拓展后继状态
    chess(const chess& parent,const Action a);
    //释放棋盘状态空间及后续状态空间
    ~chess();
    //人落子
    void chess_setxy_H(const int chessX, const int chessY);
    //机器落子
    void chess_setxy_M(const int chessX, const int chessY)const;
    //返回(chessX，chessY)点的落子状态
    int chess_check(const int chessX, const int chessY)const;
    //对于五子棋双方效用值的评估函数
    void chess_evalue();
    //α-β剪枝算法
    void chess_Alpha_Beta_search();
    //α-β剪枝算法中机器选择走棋
    int chess_Machine_value(chess& c, int Alpha, int Beta, int depth);
    //α-β剪枝算法中人选择走棋
    int chess_Human_value(chess& c,int Alpha, int Beta, int depth);
    //检查游戏是否达到终结状态
    state exam_end()const;
    //游戏重开
    void chess_restart();
    //悔棋操作
    void chess_withdraw();
};

#endif // CHESS_H
