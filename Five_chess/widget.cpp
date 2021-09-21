#include "widget.h"
#include "ui_widget.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    ,chess()
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //绑定重开与悔棋两个槽函数与对应的点击信号
    QObject::connect(ui->restart, SIGNAL(clicked()),
                         this, SLOT(game_restart()));
    QObject::connect(ui->withdraw, SIGNAL(clicked()),
                         this, SLOT(game_withdraw()));
}
//绘画棋盘的初始状态
void Widget::paintEvent(QPaintEvent* event)
{
    startX=25;
    startY=25;
    gridX=40;
    gridY=40;
    QPainter p(this);
    QPen pen;
    pen.setWidth(3);
    p.setPen(pen);
    for (int i = 0; i < Size_x; i++)
        p.drawLine(startX, startY + gridY * i, startX + (Size_x-1) * gridX, startY + gridY * i);
    for (int i = 0; i < Size_y; i++)
        p.drawLine(startX+ gridX * i, startY , startX+ gridX * i, startY + (Size_y-1) * gridY);
    pen.setWidth(1);
    p.setPen(pen);
    for (int i = 0; i < Size_x; i++) {
        for (int j = 0; j < Size_y; j++) {
            if(chess_check(i,j)==state::Machine){
                pen.setColor(Qt::white);
                p.setPen(pen);
                p.setBrush(QBrush(Qt::white));
                p.drawEllipse(QPointF(startX + i* gridX,startY + gridY * j),gridX*2/5,gridY*2/5);
            }
            else if(chess_check(i,j)==state::Human){
                pen.setColor(Qt::black);
                p.setPen(pen);
                p.setBrush(QBrush(Qt::black));
                p.drawEllipse(QPointF(startX + i* gridX,startY + gridY * j),gridX*2/5,gridY*2/5);
            }

        }
    }
}
//检测鼠标事件，实现用户与机器的对战
void Widget::mousePressEvent(QMouseEvent* event)
{
    if(exam_end()==state::Empty){
        float x = event->position().rx();
        float y = event->position().ry();
        // 要保证点击点在棋盘范围里面
        if (x >= startX&& x <= startX + (Size_x-1) * gridX
            && y >= startY && y <= startY + (Size_y-1) * gridY) {
            // 棋盘的位置转换转换为坐标下标值
            // 类似于a[i][j]的i和j
            int chessX = (x - startX) / gridX>int((x - startX) / gridX)+0.5?int((x - startX) / gridX)+1:int((x - startX) / gridX);
            int chessY = (y - startY) / gridY>int((y - startY) / gridY)+0.5?int((y - startY) / gridY)+1:int((y - startY) / gridY);
            if (chess_check(chessX, chessY) == state::Empty){
                chess_setxy_H(chessX, chessY);
                if(exam_end() == state::Human)
                    ui->Human_win->setEnabled(true);
                else
                {
                    chess_Alpha_Beta_search();
                    if (exam_end() == state::Machine)
                        ui->Machine_win->setEnabled(true);
                }
                repaint();
            }
        }
    }
}
//实现点击重开功能
void Widget::game_restart()
{
    chess_restart();
    ui->Human_win->setEnabled(false);
    ui->Machine_win->setEnabled(false);
    repaint();
}
//实现点击悔棋功能
void Widget::game_withdraw()
{
    chess_withdraw();
    ui->Human_win->setEnabled(false);
    ui->Machine_win->setEnabled(false);
    repaint();
}
//释放UI界面
Widget::~Widget()
{
    delete ui;
    chess_restart();
}
