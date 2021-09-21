#include "chess.h"
std::vector<chess::vet> chess::prev;
chess::vet chess::now;
//生成棋盘初始状态
chess::chess()
{
    chessboard = new int[Size_y][Size_x];
    now = new int[Size_y][Size_x];
    memset(chessboard, Empty, Size_y * Size_x * sizeof(int));
    memset(now, Empty, Size_y * Size_x * sizeof(int));
}
//由棋盘现状态拓展后继状态
chess::chess(const chess& parent, const Action a)
{
    chessboard = new int[Size_y][Size_x];
    action=parent.action;
    action.push_back(a);
    memcpy(chessboard, now, Size_y * Size_x * sizeof(int));
    for (auto it = this->action.begin(); it != this->action.end(); it++) {
        chessboard[it->chessY][it->chessX] = it->who;
    }
}
//释放棋盘状态空间及后续状态空间
chess::~chess()
{
    //释放后续状态空间
    for (auto it = successors.begin(); it != successors.end(); it++){
        chess* p = *it;
        delete p;
    }
    while (!successors.empty())
        successors.pop_back();
    while (!action.empty())
        action.pop_back();
}
//人落子
void chess::chess_setxy_H(const int chessX, const int chessY)
{
    //先前状态存入prev容器
    vet temp = new int[Size_y][Size_x];
    memcpy(temp,chessboard, Size_y * Size_x * sizeof(int));
    prev.push_back(temp);
    chessboard[chessY][chessX] = Human;
    memcpy(now, chessboard, Size_y * Size_x * sizeof(int));
}
//机器落子
void chess::chess_setxy_M(const int chessX, const int chessY)const
{
    chessboard[chessY][chessX] = Machine;
}
//返回棋盘某一点的状态
int chess::chess_check(const int chessX, const int chessY)const
{
    return chessboard[chessY][chessX];
}
//棋盘共有横、竖、斜三种情况可能连成5颗棋子，其中斜着又分为左斜和右斜。而考虑到黑白两种情况，则总共可以分为8种情况来讨论。
//对于每一种情况，所分析的五个位置中首先不能有异色棋子，然后根据棋子的位置（如活3，活4等情况）进行分类，分别增加或减少不同的 evaluation值 。当黑棋优势时，增加evaluation；当白棋优势时，减少evaluation
//同时，我们考虑到，有些情况（如01111）可能会由周围的第六颗棋子对其产生影响，于是在上述分类的基础上，对由第六颗棋子影响的情况额外增加或减少evaluation值。
//最终得到的evaluation，用于进行评估。
void chess::chess_evalue()
{
    if (exam_end() == state::Machine)
        evaluation = INT32_MAX-10;
    else if (exam_end() == state::Human)
        evaluation = INT32_MIN+10;
    else {
        evaluation = 0;
        //横着
        for (int i = 0; i <= 10; i++)
        {
            for (int j = 0; j <= 10; j++)
            {
                if (chessboard[i][j] != -1 && chessboard[i][j + 1] != -1 && chessboard[i][j + 2] != -1 && chessboard[i][j + 3] != -1 && chessboard[i][j + 4] != -1) {
                    if (chessboard[i][j] != 1 && chessboard[i][j + 1] == 1 && chessboard[i][j + 2] == 1 && chessboard[i][j + 3] != 1 && chessboard[i][j + 4] != 1
                        || chessboard[i][j] != 1 && chessboard[i][j + 1] != 1 && chessboard[i][j + 2] == 1 && chessboard[i][j + 3] == 1 && chessboard[i][j + 4] != 1
                        || chessboard[i][j] != 1 && chessboard[i][j + 1] == 1 && chessboard[i][j + 2] != 1 && chessboard[i][j + 3] == 1 && chessboard[i][j + 4] != 1) {
                        evaluation += 10;
                    }
                    else if (chessboard[i][j] == 1 && chessboard[i][j + 1] == 1 && chessboard[i][j + 2] != 1 && chessboard[i][j + 3] == 1 && chessboard[i][j + 4] != 1
                        || chessboard[i][j] != 1 && chessboard[i][j + 1] == 1 && chessboard[i][j + 2] != 1 && chessboard[i][j + 3] == 1 && chessboard[i][j + 4] == 1) {
                        evaluation += 80;
                    }
                    else if (chessboard[i][j] != 1 && chessboard[i][j + 1] != 1 && chessboard[i][j + 2] == 1 && chessboard[i][j + 3] == 1 && chessboard[i][j + 4] == 1
                        || chessboard[i][j] == 1 && chessboard[i][j + 1] == 1 && chessboard[i][j + 2] == 1 && chessboard[i][j + 3] != 1 && chessboard[i][j + 4] != 1) {
                        evaluation += 100;
                    }
                    else if (chessboard[i][j] != 1 && chessboard[i][j + 1] == 1 && chessboard[i][j + 2] == 1 && chessboard[i][j + 3] == 1 && chessboard[i][j + 4] != 1)
                    {
                        evaluation += 2000;
                    }
                    else if (chessboard[i][j] == 1 && chessboard[i][j + 1] == 1 && chessboard[i][j + 2] == 1 && chessboard[i][j + 3] == 1 && chessboard[i][j + 4] != 1
                        || chessboard[i][j] == 1 && chessboard[i][j + 1] == 1 && chessboard[i][j + 2] == 1 && chessboard[i][j + 3] != 1 && chessboard[i][j + 4] == 1
                        || chessboard[i][j] == 1 && chessboard[i][j + 1] == 1 && chessboard[i][j + 2] != 1 && chessboard[i][j + 3] == 1 && chessboard[i][j + 4] == 1
                        || chessboard[i][j] == 1 && chessboard[i][j + 1] != 1 && chessboard[i][j + 2] == 1 && chessboard[i][j + 3] == 1 && chessboard[i][j + 4] == 1
                        || chessboard[i][j] != 1 && chessboard[i][j + 1] == 1 && chessboard[i][j + 2] == 1 && chessboard[i][j + 3] == 1 && chessboard[i][j + 4] == 1) {
                        evaluation += 2500;
                    }
                }
                if (j > 0 && chessboard[i][j - 1] == 0 && chessboard[i][j] == 1 && chessboard[i][j + 1] == 1 && chessboard[i][j + 2] == 0 && chessboard[i][j + 3] == 1 && chessboard[i][j + 4] == 0
                    || j < 10 && chessboard[i][j] == 0 && chessboard[i][j + 1] == 1 && chessboard[i][j + 2] == 0 && chessboard[i][j + 3] == 1 && chessboard[i][j + 4] == 1 && chessboard[i][j + 5] == 0) {
                    evaluation += 1800;
                    if (j > 0 && chessboard[i][j - 1] == 0 && chessboard[i][j] == 1 && chessboard[i][j + 1] == 1 && chessboard[i][j + 2] == 1 && chessboard[i][j + 3] == 1 && chessboard[i][j + 4] == 0
                        || j < 10 && chessboard[i][j] == 0 && chessboard[i][j + 1] == 1 && chessboard[i][j + 2] == 1 && chessboard[i][j + 3] == 1 && chessboard[i][j + 4] == 1 && chessboard[i][j + 5] == 0) {
                        evaluation += 1500;
                    }
                    if (j < 10 && chessboard[i][j + 5] == -1) {
                        if (j < 5) {
                            j = j + 5;
                        }
                        else {
                            j = 11;
                        }
                    }
                }
            }
            for (int i = 0; i <= 10; i++)
            {
                for (int j = 0; j <= 10; j++)
                {
                    if (chessboard[i][j] != 1 && chessboard[i][j + 1] != 1 && chessboard[i][j + 2] != 1 && chessboard[i][j + 3] != 1 && chessboard[i][j + 4] != 1) {


                        if (chessboard[i][j] != -1 && chessboard[i][j + 1] == -1 && chessboard[i][j + 2] == -1 && chessboard[i][j + 3] != -1 && chessboard[i][j + 4] != -1
                            || chessboard[i][j] != -1 && chessboard[i][j + 1] != -1 && chessboard[i][j + 2] == -1 && chessboard[i][j + 3] == -1 && chessboard[i][j + 4] != -1
                            || chessboard[i][j] != -1 && chessboard[i][j + 1] == -1 && chessboard[i][j + 2] != -1 && chessboard[i][j + 3] == -1 && chessboard[i][j + 4] != -1) {
                            evaluation -= 10;
                        }
                        else if (chessboard[i][j] == -1 && chessboard[i][j + 1] == -1 && chessboard[i][j + 2] != -1 && chessboard[i][j + 3] == -1 && chessboard[i][j + 4] != -1
                            || chessboard[i][j] != -1 && chessboard[i][j + 1] == -1 && chessboard[i][j + 2] != -1 && chessboard[i][j + 3] == -1 && chessboard[i][j + 4] == -1) {
                            evaluation -= 80;
                        }
                        else if (chessboard[i][j] != -1 && chessboard[i][j + 1] != -1 && chessboard[i][j + 2] == -1 && chessboard[i][j + 3] == -1 && chessboard[i][j + 4] == -1
                            || chessboard[i][j] == -1 && chessboard[i][j + 1] == -1 && chessboard[i][j + 2] == -1 && chessboard[i][j + 3] != -1 && chessboard[i][j + 4] != -1) {
                            evaluation -= 100;
                        }
                        else if (chessboard[i][j] != -1 && chessboard[i][j + 1] == -1 && chessboard[i][j + 2] == -1 && chessboard[i][j + 3] == -1 && chessboard[i][j + 4] != -1) {
                            evaluation -= 2000;
                        }
                        else if (chessboard[i][j] == -1 && chessboard[i][j + 1] == -1 && chessboard[i][j + 2] == -1 && chessboard[i][j + 3] == -1 && chessboard[i][j + 4] != -1
                            || chessboard[i][j] == -1 && chessboard[i][j + 1] == -1 && chessboard[i][j + 2] == -1 && chessboard[i][j + 3] != -1 && chessboard[i][j + 4] == -1
                            || chessboard[i][j] == -1 && chessboard[i][j + 1] == -1 && chessboard[i][j + 2] != -1 && chessboard[i][j + 3] == -1 && chessboard[i][j + 4] == -1
                            || chessboard[i][j] == -1 && chessboard[i][j + 1] != -1 && chessboard[i][j + 2] == -1 && chessboard[i][j + 3] == -1 && chessboard[i][j + 4] == -1
                            || chessboard[i][j] != -1 && chessboard[i][j + 1] == -1 && chessboard[i][j + 2] == -1 && chessboard[i][j + 3] == -1 && chessboard[i][j + 4] == -1) {
                            evaluation -= 2500;
                        }
                    }
                    if (j > 0 && chessboard[i][j - 1] == 0 && chessboard[i][j] == -1 && chessboard[i][j + 1] == -1 && chessboard[i][j + 2] == 0 && chessboard[i][j + 3] == -1 && chessboard[i][j + 4] == 0
                        || j < 10 && chessboard[i][j] == 0 && chessboard[i][j + 1] == -1 && chessboard[i][j + 2] == 0 && chessboard[i][j + 3] == -1 && chessboard[i][j + 4] == -1 && chessboard[i][j + 5] == 0) {
                        evaluation -= 1800;
                    }
                    if (j > 0 && chessboard[i][j - 1] == 0 && chessboard[i][j] == -1 && chessboard[i][j + 1] == -1 && chessboard[i][j + 2] == -1 && chessboard[i][j + 3] == -1 && chessboard[i][j + 4] == 0
                        || j < 10 && chessboard[i][j] == 0 && chessboard[i][j + 1] == -1 && chessboard[i][j + 2] == -1 && chessboard[i][j + 3] == -1 && chessboard[i][j + 4] == -1 && chessboard[i][j + 5] == 0) {
                        evaluation -= 1500;
                    }
                    if (j < 10 && chessboard[i][j + 5] == 1) {
                        if (j < 5) {
                            j = j + 5;
                        }
                        else {
                            j = 11;
                        }
                    }
                }
            }
            //竖着
            for (int j = 0; j <= 10; j++)
            {
                for (int i = 0; i <= 10; i++)
                {
                    if (chessboard[i][j] != -1 && chessboard[i + 1][j] != -1 && chessboard[i + 2][j] != -1 && chessboard[i + 3][j] != -1 && chessboard[i + 4][j] != -1) {
                        if (chessboard[i][j] != 1 && chessboard[i + 1][j] == 1 && chessboard[i + 2][j] == 1 && chessboard[i + 3][j] != 1 && chessboard[i + 4][j] != 1
                            || chessboard[i][j] != 1 && chessboard[i + 1][j] != 1 && chessboard[i + 2][j] == 1 && chessboard[i + 3][j] == 1 && chessboard[i + 4][j] != 1
                            || chessboard[i][j] != 1 && chessboard[i + 1][j] == 1 && chessboard[i + 2][j] != 1 && chessboard[i + 3][j] == 1 && chessboard[i + 4][j] != 1) {
                            evaluation += 10;
                        }
                        else if (chessboard[i][j] == 1 && chessboard[i + 1][j] == 1 && chessboard[i + 2][j] != 1 && chessboard[i + 3][j] == 1 && chessboard[i + 4][j] != 1
                            || chessboard[i][j] != 1 && chessboard[i + 1][j] == 1 && chessboard[i + 2][j] != 1 && chessboard[i + 3][j] == 1 && chessboard[i + 4][j] == 1) {
                            evaluation += 80;
                        }
                        else if (chessboard[i][j] != 1 && chessboard[i + 1][j] != 1 && chessboard[i + 2][j] == 1 && chessboard[i + 3][j] == 1 && chessboard[i + 4][j] == 1
                            || chessboard[i][j] == 1 && chessboard[i + 1][j] == 1 && chessboard[i + 2][j] == 1 && chessboard[i + 3][j] != 1 && chessboard[i + 4][j] != 1) {
                            evaluation += 100;
                        }
                        else if (chessboard[i][j] != 1 && chessboard[i + 1][j] == 1 && chessboard[i + 2][j] == 1 && chessboard[i + 3][j] == 1 && chessboard[i + 4][j] != 1) {
                            evaluation += 2000;
                        }
                        else if (chessboard[i][j] == 1 && chessboard[i + 1][j] == 1 && chessboard[i + 2][j] == 1 && chessboard[i + 3][j] == 1 && chessboard[i + 4][j] != 1
                            || chessboard[i][j] == 1 && chessboard[i + 1][j] == 1 && chessboard[i + 2][j] == 1 && chessboard[i + 3][j] != 1 && chessboard[i + 4][j] == 1
                            || chessboard[i][j] == 1 && chessboard[i + 1][j] == 1 && chessboard[i + 2][j] != 1 && chessboard[i + 3][j] == 1 && chessboard[i + 4][j] == 1
                            || chessboard[i][j] == 1 && chessboard[i + 1][j] != 1 && chessboard[i + 2][j] == 1 && chessboard[i + 3][j] == 1 && chessboard[i + 4][j] == 1
                            || chessboard[i][j] != 1 && chessboard[i + 1][j] == 1 && chessboard[i + 2][j] == 1 && chessboard[i + 3][j] == 1 && chessboard[i + 4][j] == 1) {
                            evaluation += 2500;
                        }
                    }
                    if (i > 0 && chessboard[i - 1][j] == 0 && chessboard[i][j] == 1 && chessboard[i + 1][j] == 1 && chessboard[i + 2][j] == 0 && chessboard[i + 3][j] == 1 && chessboard[i + 4][j] == 0
                        || i < 10 && chessboard[i][j] == 0 && chessboard[i + 1][j] == 1 && chessboard[i + 2][j] == 0 && chessboard[i + 3][j] == 1 && chessboard[i + 4][j] == 1 && chessboard[i + 5][j] == 0) {
                        evaluation += 1800;
                    }
                    if (i > 0 && chessboard[i - 1][j] == 0 && chessboard[i][j] == 1 && chessboard[i + 1][j] == 1 && chessboard[i + 2][j] == 1 && chessboard[i + 3][j] == 1 && chessboard[i + 4][j] == 0
                        || i < 10 && chessboard[i][j] == 0 && chessboard[i + 1][j] == 1 && chessboard[i + 2][j] == 1 && chessboard[i + 3][j] == 1 && chessboard[i + 4][j] == 1 && chessboard[i + 5][j] == 0) {
                        evaluation += 1500;
                    }
                    if (i < 10 && chessboard[i + 5][j] == -1) {
                        if (i < 5) {
                            i = i + 5;
                        }
                        else {
                            i = 11;
                        }
                    }
                }
            }
            for (int j = 0; j <= 10; j++)
            {
                for (int i = 0; i <= 10; i++)
                {
                    if (chessboard[i][j] != 1 && chessboard[i + 1][j] != 1 && chessboard[i + 2][j] != 1 && chessboard[i + 3][j] != 1 && chessboard[i + 4][j] != 1) {
                        if (chessboard[i][j] != -1 && chessboard[i + 1][j] == -1 && chessboard[i + 2][j] == -1 && chessboard[i + 3][j] != -1 && chessboard[i + 4][j] != -1
                            || chessboard[i][j] != -1 && chessboard[i + 1][j] != -1 && chessboard[i + 2][j] == -1 && chessboard[i + 3][j] == -1 && chessboard[i + 4][j] != -1
                            || chessboard[i][j] != -1 && chessboard[i + 1][j] == -1 && chessboard[i + 2][j] != -1 && chessboard[i + 3][j] == -1 && chessboard[i + 4][j] != -1) {
                            evaluation -= 10;
                        }
                        else if (chessboard[i][j] == -1 && chessboard[i + 1][j] == -1 && chessboard[i + 2][j] != -1 && chessboard[i + 3][j] == -1 && chessboard[i + 4][j] != -1
                            || chessboard[i][j] != -1 && chessboard[i + 1][j] == -1 && chessboard[i + 2][j] != -1 && chessboard[i + 3][j] == -1 && chessboard[i + 4][j] == -1) {
                            evaluation -= 80;
                        }
                        else if (chessboard[i][j] != -1 && chessboard[i + 1][j] != -1 && chessboard[i + 2][j] == -1 && chessboard[i + 3][j] == -1 && chessboard[i + 4][j] == -1
                            || chessboard[i][j] == -1 && chessboard[i + 1][j] == -1 && chessboard[i + 2][j] == -1 && chessboard[i + 3][j] != -1 && chessboard[i + 4][j] != -1) {
                            evaluation -= 100;
                        }
                        else if (chessboard[i][j] != -1 && chessboard[i + 1][j] == -1 && chessboard[i + 2][j] == -1 && chessboard[i + 3][j] == -1 && chessboard[i + 4][j] != -1) {
                            evaluation -= 2000;
                        }
                        else if (chessboard[i][j] == -1 && chessboard[i + 1][j] == -1 && chessboard[i + 2][j] == -1 && chessboard[i + 3][j] == -1 && chessboard[i + 4][j] != -1
                            || chessboard[i][j] == -1 && chessboard[i + 1][j] == -1 && chessboard[i + 2][j] == -1 && chessboard[i + 3][j] != -1 && chessboard[i + 4][j] == -1
                            || chessboard[i][j] == -1 && chessboard[i + 1][j] == -1 && chessboard[i + 2][j] != -1 && chessboard[i + 3][j] == -1 && chessboard[i + 4][j] == -1
                            || chessboard[i][j] == -1 && chessboard[i + 1][j] != -1 && chessboard[i + 2][j] == -1 && chessboard[i + 3][j] == -1 && chessboard[i + 4][j] == -1
                            || chessboard[i][j] != -1 && chessboard[i + 1][j] == -1 && chessboard[i + 2][j] == -1 && chessboard[i + 3][j] == -1 && chessboard[i + 4][j] == -1) {
                            evaluation -= 2500;
                        }
                    }
                    if (i > 0 && chessboard[i - 1][j] == 0 && chessboard[i][j] == -1 && chessboard[i + 1][j] == -1 && chessboard[i + 2][j] == 0 && chessboard[i + 3][j] == -1 && chessboard[i + 4][j] == 0
                        || i < 10 && chessboard[i][j] == 0 && chessboard[i + 1][j] == -1 && chessboard[i + 2][j] == 0 && chessboard[i + 3][j] == -1 && chessboard[i + 4][j] == -1 && chessboard[i + 5][j] == 0) {
                        evaluation -= 1800;
                    }
                    if (i > 0 && chessboard[i - 1][j] == 0 && chessboard[i][j] == -1 && chessboard[i + 1][j] == -1 && chessboard[i + 2][j] == -1 && chessboard[i + 3][j] == -1 && chessboard[i + 4][j] == 0
                        || i < 10 && chessboard[i][j] == 0 && chessboard[i + 1][j] == -1 && chessboard[i + 2][j] == -1 && chessboard[i + 3][j] == -1 && chessboard[i + 4][j] == -1 && chessboard[i + 5][j] == 0) {
                        evaluation -= 1500;
                    }
                    if (i < 10 && chessboard[i + 5][j] == 1) {
                        if (i < 5) {
                            i = i + 5;
                        }
                        else {
                            i = 11;
                        }
                    }
                }
            }
            //左斜
            for (int i = 0; i <= 10; i++)
            {
                for (int j = 0; j <= 10; j++)
                {
                    if (chessboard[i][j] != -1 && chessboard[i + 1][j + 1] != -1 && chessboard[i + 2][j + 2] != -1 && chessboard[i + 3][j + 3] != -1 && chessboard[i + 4][j + 4] != -1) {
                        if (chessboard[i][j] != 1 && chessboard[i + 1][j + 1] == 1 && chessboard[i + 2][j + 2] == 1 && chessboard[i + 3][j + 3] != 1 && chessboard[i + 4][j + 4] != 1
                            || chessboard[i][j] != 1 && chessboard[i + 1][j + 1] != 1 && chessboard[i + 2][j + 2] == 1 && chessboard[i + 3][j + 3] == 1 && chessboard[i + 4][j + 4] != 1
                            || chessboard[i][j] != 1 && chessboard[i + 1][j + 1] == 1 && chessboard[i + 2][j + 2] != 1 && chessboard[i + 3][j + 3] == 1 && chessboard[i + 4][j + 4] != 1) {
                            evaluation += 10;
                        }
                        else if (chessboard[i][j] == 1 && chessboard[i + 1][j + 1] == 1 && chessboard[i + 2][j + 2] != 1 && chessboard[i + 3][j + 3] == 1 && chessboard[i + 4][j + 4] != 1
                            || chessboard[i][j] != 1 && chessboard[i + 1][j + 1] == 1 && chessboard[i + 2][j + 2] != 1 && chessboard[i + 3][j + 3] == 1 && chessboard[i + 4][j + 4] == 1) {
                            evaluation += 80;
                        }
                        else if (chessboard[i][j] != 1 && chessboard[i + 1][j + 1] != 1 && chessboard[i + 2][j + 2] == 1 && chessboard[i + 3][j + 3] == 1 && chessboard[i + 4][j + 4] == 1
                            || chessboard[i][j] == 1 && chessboard[i + 1][j + 1] == 1 && chessboard[i + 2][j + 2] == 1 && chessboard[i + 3][j + 3] != 1 && chessboard[i + 4][j + 4] != 1) {
                            evaluation += 100;
                        }
                        else if (chessboard[i][j] != 1 && chessboard[i + 1][j + 1] == 1 && chessboard[i + 2][j + 2] == 1 && chessboard[i + 3][j + 3] == 1 && chessboard[i + 4][j + 4] != 1) {
                            evaluation += 2000;
                        }
                        else if (chessboard[i][j] == 1 && chessboard[i + 1][j + 1] == 1 && chessboard[i + 2][j + 2] == 1 && chessboard[i + 3][j + 3] == 1 && chessboard[i + 4][j + 4] != 1
                            || chessboard[i][j] == 1 && chessboard[i + 1][j + 1] == 1 && chessboard[i + 2][j + 2] == 1 && chessboard[i + 3][j + 3] != 1 && chessboard[i + 4][j + 4] == 1
                            || chessboard[i][j] == 1 && chessboard[i + 1][j + 1] == 1 && chessboard[i + 2][j + 2] != 1 && chessboard[i + 3][j + 3] == 1 && chessboard[i + 4][j + 4] == 1
                            || chessboard[i][j] == 1 && chessboard[i + 1][j + 1] != 1 && chessboard[i + 2][j + 2] == 1 && chessboard[i + 3][j + 3] == 1 && chessboard[i + 4][j + 4] == 1
                            || chessboard[i][j] != 1 && chessboard[i + 1][j + 1] == 1 && chessboard[i + 2][j + 2] == 1 && chessboard[i + 3][j + 3] == 1 && chessboard[i + 4][j + 4] == 1) {
                            evaluation += 2500;
                        }
                    }
                    if (i > 0 && j > 0 && chessboard[i - 1][j - 1] == 0 && chessboard[i][j] == 1 && chessboard[i + 1][j + 1] == 1 && chessboard[i + 2][j + 2] == 0 && chessboard[i + 3][j + 3] == 1 && chessboard[i + 4][j + 4] == 0
                        || i < 10 && j < 10 && chessboard[i][j] == 0 && chessboard[i + 1][j + 1] == 1 && chessboard[i + 2][j + 2] == 0 && chessboard[i + 3][j + 3] == 1 && chessboard[i + 4][j + 4] == 1 && chessboard[i + 5][j + 5] == 0) {
                        evaluation += 1800;
                    }
                    if (i > 0 && j > 0 && chessboard[i - 1][j - 1] == 0 && chessboard[i][j] == 1 && chessboard[i + 1][j + 1] == 1 && chessboard[i + 2][j + 2] == 1 && chessboard[i + 3][j + 3] == 1 && chessboard[i + 4][j + 4] == 0
                        || i < 10 && j < 10 && chessboard[i][j] == 0 && chessboard[i + 1][j + 1] == 1 && chessboard[i + 2][j + 2] == 1 && chessboard[i + 3][j + 3] == 1 && chessboard[i + 4][j + 4] == 1 && chessboard[i + 5][j + 5] == 0) {
                        evaluation += 1500;
                    }
                    if (chessboard[i][j] != 1 && chessboard[i + 1][j + 1] != 1 && chessboard[i + 2][j + 2] != 1 && chessboard[i + 3][j + 3] != 1 && chessboard[i + 4][j + 4] != 1) {
                        if (chessboard[i][j] != -1 && chessboard[i + 1][j + 1] == -1 && chessboard[i + 2][j + 2] == -1 && chessboard[i + 3][j + 3] != -1 && chessboard[i + 4][j + 4] != -1
                            || chessboard[i][j] != -1 && chessboard[i + 1][j + 1] != -1 && chessboard[i + 2][j + 2] == -1 && chessboard[i + 3][j + 3] == -1 && chessboard[i + 4][j + 4] != -1
                            || chessboard[i][j] != -1 && chessboard[i + 1][j + 1] == -1 && chessboard[i + 2][j + 2] != -1 && chessboard[i + 3][j + 3] == -1 && chessboard[i + 4][j + 4] != -1) {
                            evaluation -= 10;
                        }
                        else if (chessboard[i][j] == -1 && chessboard[i + 1][j + 1] == -1 && chessboard[i + 2][j + 2] != -1 && chessboard[i + 3][j + 3] == -1 && chessboard[i + 4][j + 4] != -1
                            || chessboard[i][j] != -1 && chessboard[i + 1][j + 1] == -1 && chessboard[i + 2][j + 2] != -1 && chessboard[i + 3][j + 3] == -1 && chessboard[i + 4][j + 4] == -1) {
                            evaluation -= 80;
                        }
                        else if (chessboard[i][j] != -1 && chessboard[i + 1][j + 1] != -1 && chessboard[i + 2][j + 2] == -1 && chessboard[i + 3][j + 3] == -1 && chessboard[i + 4][j + 4] == -1
                            || chessboard[i][j] == -1 && chessboard[i + 1][j + 1] == -1 && chessboard[i + 2][j + 2] == -1 && chessboard[i + 3][j + 3] != -1 && chessboard[i + 4][j + 4] != -1) {
                            evaluation -= 100;
                        }
                        else if (chessboard[i][j] != -1 && chessboard[i + 1][j + 1] == -1 && chessboard[i + 2][j + 2] == -1 && chessboard[i + 3][j + 3] == -1 && chessboard[i + 4][j + 4] != -1) {
                            evaluation -= 2000;
                        }
                        else if (chessboard[i][j] == -1 && chessboard[i + 1][j + 1] == -1 && chessboard[i + 2][j + 2] == -1 && chessboard[i + 3][j + 3] == -1 && chessboard[i + 4][j + 4] != -1
                            || chessboard[i][j] == -1 && chessboard[i + 1][j + 1] == -1 && chessboard[i + 2][j + 2] == -1 && chessboard[i + 3][j + 3] != -1 && chessboard[i + 4][j + 4] == -1
                            || chessboard[i][j] == -1 && chessboard[i + 1][j + 1] == -1 && chessboard[i + 2][j + 2] != -1 && chessboard[i + 3][j + 3] == -1 && chessboard[i + 4][j + 4] == -1
                            || chessboard[i][j] == -1 && chessboard[i + 1][j + 1] != -1 && chessboard[i + 2][j + 2] == -1 && chessboard[i + 3][j + 3] == -1 && chessboard[i + 4][j + 4] == -1
                            || chessboard[i][j] != -1 && chessboard[i + 1][j + 1] == -1 && chessboard[i + 2][j + 2] == -1 && chessboard[i + 3][j + 3] == -1 && chessboard[i + 4][j + 4] == -1) {
                            evaluation -= 2500;
                        }
                    }
                    if (i > 0 && j > 0 && chessboard[i - 1][j - 1] == 0 && chessboard[i][j] == -1 && chessboard[i + 1][j + 1] == -1 && chessboard[i + 2][j + 2] == 0 && chessboard[i + 3][j + 3] == -1 && chessboard[i + 4][j + 4] == 0
                        || i < 10 && j < 10 && chessboard[i][j] == 0 && chessboard[i + 1][j + 1] == -1 && chessboard[i + 2][j + 2] == 0 && chessboard[i + 3][j + 3] == -1 && chessboard[i + 4][j + 4] == -1 && chessboard[i + 5][j + 5] == 0) {
                        evaluation -= 1800;
                    }
                    if (i > 0 && j > 0 && chessboard[i - 1][j - 1] == 0 && chessboard[i][j] == -1 && chessboard[i + 1][j + 1] == -1 && chessboard[i + 2][j + 2] == -1 && chessboard[i + 3][j + 3] == -1 && chessboard[i + 4][j + 4] == 0
                        || i < 10 && j < 10 && chessboard[i][j] == 0 && chessboard[i + 1][j + 1] == -1 && chessboard[i + 2][j + 2] == -1 && chessboard[i + 3][j + 3] == -1 && chessboard[i + 4][j + 4] == -1 && chessboard[i + 5][j + 5] == 0) {
                        evaluation -= 1500;
                    }
                }
            }
            //右斜
            for (int i = 4; i <= 14; i++)
            {
                for (int j = 0; j <= 10; j++)
                {
                    if (chessboard[i][j] != -1 && chessboard[i - 1][j + 1] != -1 && chessboard[i - 2][j + 2] != -1 && chessboard[i - 3][j + 3] != -1 && chessboard[i - 4][j + 4] != -1) {
                        if (chessboard[i][j] != 1 && chessboard[i - 1][j + 1] == 1 && chessboard[i - 2][j + 2] == 1 && chessboard[i - 3][j + 3] != 1 && chessboard[i - 4][j + 4] != 1
                            || chessboard[i][j] != 1 && chessboard[i - 1][j + 1] != 1 && chessboard[i - 2][j + 2] == 1 && chessboard[i - 3][j + 3] == 1 && chessboard[i - 4][j + 4] != 1
                            || chessboard[i][j] != 1 && chessboard[i - 1][j + 1] == 1 && chessboard[i - 2][j + 2] != 1 && chessboard[i - 3][j + 3] == 1 && chessboard[i - 4][j + 4] != 1) {
                            evaluation += 10;
                        }
                        else if (chessboard[i][j] == 1 && chessboard[i - 1][j + 1] == 1 && chessboard[i - 2][j + 2] != 1 && chessboard[i - 3][j + 3] == 1 && chessboard[i - 4][j + 4] != 1
                            || chessboard[i][j] != 1 && chessboard[i - 1][j + 1] == 1 && chessboard[i - 2][j + 2] != 1 && chessboard[i - 3][j + 3] == 1 && chessboard[i - 4][j + 4] == 1) {
                            evaluation += 80;
                        }
                        else if (chessboard[i][j] != 1 && chessboard[i - 1][j + 1] != 1 && chessboard[i - 2][j + 2] == 1 && chessboard[i - 3][j + 3] == 1 && chessboard[i - 4][j + 4] == 1
                            || chessboard[i][j] == 1 && chessboard[i - 1][j + 1] == 1 && chessboard[i - 2][j + 2] == 1 && chessboard[i - 3][j + 3] != 1 && chessboard[i - 4][j + 4] != 1) {
                            evaluation += 100;
                        }
                        else if (chessboard[i][j] != 1 && chessboard[i - 1][j + 1] == 1 && chessboard[i - 2][j + 2] == 1 && chessboard[i - 3][j + 3] == 1 && chessboard[i - 4][j + 4] != 1) {
                            evaluation += 2000;
                        }
                        else if (chessboard[i][j] == 1 && chessboard[i - 1][j + 1] == 1 && chessboard[i - 2][j + 2] == 1 && chessboard[i - 3][j + 3] == 1 && chessboard[i - 4][j + 4] != 1
                            || chessboard[i][j] == 1 && chessboard[i - 1][j + 1] == 1 && chessboard[i - 2][j + 2] == 1 && chessboard[i - 3][j + 3] != 1 && chessboard[i - 4][j + 4] == 1
                            || chessboard[i][j] == 1 && chessboard[i - 1][j + 1] == 1 && chessboard[i - 2][j + 2] != 1 && chessboard[i - 3][j + 3] == 1 && chessboard[i - 4][j + 4] == 1
                            || chessboard[i][j] == 1 && chessboard[i - 1][j + 1] != 1 && chessboard[i - 2][j + 2] == 1 && chessboard[i - 3][j + 3] == 1 && chessboard[i - 4][j + 4] == 1
                            || chessboard[i][j] != 1 && chessboard[i - 1][j + 1] == 1 && chessboard[i - 2][j + 2] == 1 && chessboard[i - 3][j + 3] == 1 && chessboard[i - 4][j + 4] == 1) {
                            evaluation += 2500;
                        }
                    }
                    if (i < 14 && j>0 && chessboard[i + 1][j - 1] == 0 && chessboard[i][j] == 1 && chessboard[i - 1][j + 1] == 1 && chessboard[i - 2][j + 2] == 0 && chessboard[i - 3][j + 3] == 1 && chessboard[i - 4][j + 4] == 0
                        || i > 4 && j < 10 && chessboard[i][j] == 0 && chessboard[i - 1][j + 1] == 1 && chessboard[i - 2][j + 2] == 0 && chessboard[i - 3][j + 3] == 1 && chessboard[i - 4][j + 4] == 1 && chessboard[i - 5][j + 5] == 0) {
                        evaluation += 1800;
                    }
                    if (i < 14 && j>0 && chessboard[i + 1][j - 1] == 0 && chessboard[i][j] == 1 && chessboard[i - 1][j + 1] == 1 && chessboard[i - 2][j + 2] == 1 && chessboard[i - 3][j + 3] == 1 && chessboard[i - 4][j + 4] == 0
                        || i > 4 && j < 10 && chessboard[i][j] == 0 && chessboard[i - 1][j + 1] == 1 && chessboard[i - 2][j + 2] == 1 && chessboard[i - 3][j + 3] == 1 && chessboard[i - 4][j + 4] == 1 && chessboard[i - 5][j + 5] == 0) {
                        evaluation += 1500;
                    }
                    if (chessboard[i][j] != 1 && chessboard[i - 1][j + 1] != 1 && chessboard[i - 2][j + 2] != 1 && chessboard[i - 3][j + 3] != 1 && chessboard[i - 4][j + 4] != 1) {
                        if (chessboard[i][j] != -1 && chessboard[i - 1][j + 1] == -1 && chessboard[i - 2][j + 2] == -1 && chessboard[i - 3][j + 3] != -1 && chessboard[i - 4][j + 4] != -1
                            || chessboard[i][j] != -1 && chessboard[i - 1][j + 1] != -1 && chessboard[i - 2][j + 2] == -1 && chessboard[i - 3][j + 3] == -1 && chessboard[i - 4][j + 4] != -1
                            || chessboard[i][j] != -1 && chessboard[i - 1][j + 1] == -1 && chessboard[i - 2][j + 2] != -1 && chessboard[i - 3][j + 3] == -1 && chessboard[i - 4][j + 4] != -1) {
                            evaluation -= 10;
                        }
                        else if (chessboard[i][j] == -1 && chessboard[i - 1][j + 1] == -1 && chessboard[i - 2][j + 2] != -1 && chessboard[i - 3][j + 3] == -1 && chessboard[i - 4][j + 4] != -1
                            || chessboard[i][j] != -1 && chessboard[i - 1][j + 1] == -1 && chessboard[i - 2][j + 2] != -1 && chessboard[i - 3][j + 3] == -1 && chessboard[i - 4][j + 4] == -1) {
                            evaluation -= 80;
                        }
                        else if (chessboard[i][j] != -1 && chessboard[i - 1][j + 1] != -1 && chessboard[i - 2][j + 2] == -1 && chessboard[i - 3][j + 3] == -1 && chessboard[i - 4][j + 4] == -1
                            || chessboard[i][j] == -1 && chessboard[i - 1][j + 1] == -1 && chessboard[i - 2][j + 2] == -1 && chessboard[i - 3][j + 3] != -1 && chessboard[i - 4][j + 4] != -1) {
                            evaluation -= 100;
                        }
                        else if (chessboard[i][j] != -1 && chessboard[i - 1][j + 1] == -1 && chessboard[i + 2][j + 2] == -1 && chessboard[i - 3][j + 3] == -1 && chessboard[i - 4][j + 4] != -1) {
                            evaluation -= 2000;
                        }
                        else if (chessboard[i][j] == -1 && chessboard[i - 1][j + 1] == -1 && chessboard[i - 2][j + 2] == -1 && chessboard[i - 3][j + 3] == -1 && chessboard[i - 4][j + 4] != -1
                            || chessboard[i][j] == -1 && chessboard[i - 1][j + 1] == -1 && chessboard[i - 2][j + 2] == -1 && chessboard[i - 3][j + 3] != -1 && chessboard[i - 4][j + 4] == -1
                            || chessboard[i][j] == -1 && chessboard[i - 1][j + 1] == -1 && chessboard[i - 2][j + 2] != -1 && chessboard[i - 3][j + 3] == -1 && chessboard[i - 4][j + 4] == -1
                            || chessboard[i][j] == -1 && chessboard[i - 1][j + 1] != -1 && chessboard[i - 2][j + 2] == -1 && chessboard[i - 3][j + 3] == -1 && chessboard[i - 4][j + 4] == -1
                            || chessboard[i][j] != -1 && chessboard[i - 1][j + 1] == -1 && chessboard[i - 2][j + 2] == -1 && chessboard[i - 3][j + 3] == -1 && chessboard[i - 4][j + 4] == -1) {
                            evaluation -= 2500;
                        }
                    }
                    if (i < 14 && j>0 && chessboard[i + 1][j - 1] == 0 && chessboard[i][j] == -1 && chessboard[i - 1][j + 1] == -1 && chessboard[i - 2][j + 2] == 0 && chessboard[i - 3][j + 3] == -1 && chessboard[i - 4][j + 4] == 0
                        || i > 4 && j < 10 && chessboard[i][j] == 0 && chessboard[i - 1][j + 1] == -1 && chessboard[i - 2][j + 2] == 0 && chessboard[i - 3][j + 3] == -1 && chessboard[i - 4][j + 4] == -1 && chessboard[i - 5][j + 5] == 0) {
                        evaluation -= 1800;
                    }
                    if (i < 14 && j>0 && chessboard[i + 1][j - 1] == 0 && chessboard[i][j] == -1 && chessboard[i - 1][j + 1] == -1 && chessboard[i - 2][j + 2] == -1 && chessboard[i - 3][j + 3] == -1 && chessboard[i - 4][j + 4] == 0
                        || i > 4 && j < 10 && chessboard[i][j] == 0 && chessboard[i - 1][j + 1] == -1 && chessboard[i - 2][j + 2] == -1 && chessboard[i - 3][j + 3] == -1 && chessboard[i - 4][j + 4] == -1 && chessboard[i - 5][j + 5] == 0) {
                        evaluation -= 1500;
                    }
                }
            }
        }

    }
}
//检测是否到达终结状态，若机器胜，返回state::Machine，人胜返回state::Human
state chess::exam_end()const
{
    for (int i = 0; i < Size_y; i++) {
        for (int j = 0; j < Size_x; j++) {
            if (j <= Size_x - 5) {
                if (chessboard[i][j] + chessboard[i][j + 1] + chessboard[i][j + 2]
                    + chessboard[i][j + 3] + chessboard[i][j + 4] == -5) {
                    return state::Human;
                }
                else if (chessboard[i][j] + chessboard[i][j + 1] + chessboard[i][j + 2]
                    + chessboard[i][j + 3] + chessboard[i][j + 4] == 5) {
                    return state::Machine;
                }
            }
            if (i <= Size_y - 5) {
                if (chessboard[i][j] + chessboard[i + 1][j] + chessboard[i + 2][j]
                    + chessboard[i + 3][j] + chessboard[i + 4][j] == -5) {
                    return state::Human;
                }
                else if (chessboard[i][j] + chessboard[i + 1][j] + chessboard[i + 2][j]
                    + chessboard[i + 3][j] + chessboard[i + 4][j] == 5) {
                    return state::Machine;
                }
            }
            if (i <= Size_y - 5 && j <= Size_x - 5) {
                if (chessboard[i][j] + chessboard[i + 1][j + 1] + chessboard[i + 2][j + 2]
                    + chessboard[i + 3][j + 3] + chessboard[i + 4][j + 4] == -5) {
                    return state::Human;
                }
                else if (chessboard[i][j] + chessboard[i + 1][j + 1] + chessboard[i + 2][j + 2]
                    + chessboard[i + 3][j + 3] + chessboard[i + 4][j + 4] == 5) {
                    return state::Machine;
                }
            }
            if (i <= Size_y - 5 && j >= 4) {
                if (chessboard[i][j] + chessboard[i + 1][j - 1] + chessboard[i + 2][j - 2]
                    + chessboard[i + 3][j - 3] + chessboard[i + 4][j - 4] == -5) {
                    return state::Human;
                }
                else if (chessboard[i][j] + chessboard[i + 1][j - 1] + chessboard[i + 2][j - 2]
                    + chessboard[i + 3][j - 3] + chessboard[i + 4][j - 4] == 5) {
                    return state::Machine;
                }
            }
        }
    }
    return state::Empty;
}
//α-β剪枝算法
void chess::chess_Alpha_Beta_search()
{
    int Alpha = INT32_MIN;
    int Beta = INT32_MAX;
    int v = chess_Machine_value(*this, Alpha, Beta, 0);
    for (auto it = this->successors.begin(); it != this->successors.end(); it++) {
        bool select = true;
        if (v == (*it)->evaluation&&select)
        {
            select = false;
            chessboard = new int[Size_y][Size_x];
            memcpy(chessboard, now, Size_y * Size_x * sizeof(int));
            for (auto p = (*it)->action.begin(); p != (*it)->action.end(); p++) {
                chessboard[p->chessY][p->chessX] = p->who;
            }
        }
        chess* p = *it;
        delete p;
    }
    while (!successors.empty())
        successors.pop_back();
}
//α-β剪枝算法中机器选择走棋
int chess::chess_Machine_value(chess& c, int Alpha, int Beta, int depth)
{
    if (depth == limited_depth || c.exam_end() != state::Empty) {
        c.chess_evalue();
        delete c.chessboard;
        return c.evaluation;
    }
    int v = INT32_MIN;
    for (int i = 0; i < Size_x; i++) {
        for (int j = 0; j < Size_y; j++) {
            if (c.chessboard[j][i] == state::Empty) {
                if ((i > 0 && chessboard[j][i - 1] != state::Empty) || (i < Size_x - 1 && chessboard[j][i + 1] != state::Empty) ||
                    (i > 0 && j > 0 && chessboard[j - 1][i - 1] != state::Empty) || (j > 0 && chessboard[j - 1][i] != state::Empty) ||
                    (j > 0 && i < Size_x - 1 && chessboard[j - 1][i + 1] != state::Empty) || (i > 0 && j < Size_y - 1 && chessboard[j + 1][i - 1] != state::Empty) ||
                    (j < Size_y - 1 && chessboard[j + 1][i] != state::Empty) || (i < Size_x - 1 && j < Size_y - 1 && chessboard[j + 1][i + 1] != state::Empty))
                {
                    Action p{ i, j, state::Machine };
                    chess* next = new chess(c, p);
                    c.successors.push_back(next);
                    int t = chess_Human_value(*next, Alpha, Beta, depth + 1);
                    v = t > v ? t : v;
                    if (v > Beta ) {
                        c.evaluation = v;
                        for (auto it = c.successors.begin(); it != c.successors.end(); it++) {
                            chess* p = *it;
                            delete p;
                        }
                        while (!c.successors.empty())
                            c.successors.pop_back();
                        delete c.chessboard;
                        return v;
                    }
                    Alpha = Alpha > v ? Alpha : v;
                }

            }
        }
    }
    c.evaluation = v;
    delete c.chessboard;
    return v;
}
//α-β剪枝算法中人选择走棋
int chess::chess_Human_value(chess& c, int Alpha, int Beta, int depth)
{
    if (depth == limited_depth || c.exam_end() != state::Empty) {
        c.chess_evalue();
        delete c.chessboard;
        return c.evaluation;
    }
    int v = INT32_MAX;
    for (int i = 0; i < Size_x; i++) {
        for (int j = 0; j < Size_y; j++) {
            if (c.chessboard[j][i] == state::Empty) {
                if ((i > 0 && chessboard[j][i - 1] != state::Empty) || (i < Size_x - 1 && chessboard[j][i + 1] != state::Empty) ||
                    (i > 0 && j > 0 && chessboard[j - 1][i - 1] != state::Empty) || (j > 0 && chessboard[j - 1][i] != state::Empty) ||
                    (j > 0 && i < Size_x - 1 && chessboard[j - 1][i + 1] != state::Empty) || (i > 0 && j < Size_y - 1 && chessboard[j + 1][i - 1] != state::Empty) ||
                    (j < Size_y - 1 && chessboard[j + 1][i] != state::Empty) || (i < Size_x - 1 && j < Size_y - 1 && chessboard[j + 1][i + 1] != state::Empty))
                {
                    Action p{ i, j, state::Human };
                    chess* next = new chess(c, p);
                    c.successors.push_back(next);
                    int t = chess_Machine_value(*next, Alpha, Beta, depth + 1);
                    v = t < v ? t : v;
                    if (v < Alpha) {
                        c.evaluation = v;
                        for (auto it = c.successors.begin(); it != c.successors.end(); it++) {
                            chess* p = *it;
                            delete p;
                        }
                        while (!c.successors.empty())
                            c.successors.pop_back();
                        delete c.chessboard;
                        return v;
                    }
                    Beta = Beta < v ? Beta : v;
                }
            }
        }
    }
    c.evaluation = v;
    delete c.chessboard;
    return v;
}
//游戏重开,对象回复初始状态
void chess::chess_restart()
{
    for (auto it = prev.begin(); it != prev.end(); it++) {
        vet p = *it;
        delete []p;
    }
    while (!prev.empty())
        prev.pop_back();
    memset(chessboard, Empty, Size_y * Size_x * sizeof(int));
}
//悔棋操作，从prev中取出先前状态
void chess::chess_withdraw()
{
    if (!prev.empty()) {
        delete[]chessboard;
        chessboard = *prev.rbegin();
        prev.pop_back();
    }
}
