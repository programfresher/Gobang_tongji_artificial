#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QtTest/QTest>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include "chess.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget,public chess
{
    Q_OBJECT

public:
    //生成UI界面，绑定信号与槽
    Widget(QWidget *parent = nullptr);
    //绘画棋盘的初始状态
    void paintEvent(QPaintEvent* event);
    //检测人点击下棋并反应
    void mousePressEvent(QMouseEvent* event);
    //释放UI界面
    ~Widget();
public slots:
    //实现点击重开功能
    void game_restart();
    //实现点击悔棋功能
    void game_withdraw();
private:
    //指向UI图形界面
    Ui::Widget *ui;
    //绘画棋盘的左上角X坐标
    int startX;
    //绘画棋盘的左上角Y坐标
    int startY;
    //棋盘X坐标轴间隔
    int gridX;
    //棋盘Y坐标轴间隔
    int gridY;
};
#endif // WIDGET_H
