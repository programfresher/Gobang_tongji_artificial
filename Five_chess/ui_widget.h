/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.1.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *withdraw;
    QPushButton *restart;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *Human_win;
    QLabel *Machine_win;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->setEnabled(true);
        Widget->resize(700, 610);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Widget->sizePolicy().hasHeightForWidth());
        Widget->setSizePolicy(sizePolicy);
        Widget->setMinimumSize(QSize(700, 610));
        Widget->setMaximumSize(QSize(700, 610));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(240, 240, 240, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(255, 255, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(227, 227, 227, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(160, 160, 160, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush4);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        QBrush brush5(QColor(0, 0, 0, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush5);
        palette.setBrush(QPalette::Active, QPalette::Base, brush2);
        QBrush brush6(QColor(255, 170, 0, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush6);
        QBrush brush7(QColor(105, 105, 105, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush7);
        QBrush brush8(QColor(0, 120, 215, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Highlight, brush8);
        palette.setBrush(QPalette::Active, QPalette::HighlightedText, brush2);
        QBrush brush9(QColor(0, 0, 255, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Link, brush9);
        QBrush brush10(QColor(255, 0, 255, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::LinkVisited, brush10);
        QBrush brush11(QColor(245, 245, 245, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush11);
        QBrush brush12(QColor(0, 0, 0, 255));
        brush12.setStyle(Qt::NoBrush);
        palette.setBrush(QPalette::Active, QPalette::NoRole, brush12);
        QBrush brush13(QColor(255, 255, 220, 255));
        brush13.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush13);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush5);
        QBrush brush14(QColor(255, 0, 0, 128));
        brush14.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush14);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::Highlight, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Link, brush9);
        palette.setBrush(QPalette::Inactive, QPalette::LinkVisited, brush10);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush11);
        QBrush brush15(QColor(0, 0, 0, 255));
        brush15.setStyle(Qt::NoBrush);
        palette.setBrush(QPalette::Inactive, QPalette::NoRole, brush15);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush13);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush5);
        QBrush brush16(QColor(255, 0, 0, 128));
        brush16.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush16);
#endif
        QBrush brush17(QColor(120, 120, 120, 255));
        brush17.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush17);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        QBrush brush18(QColor(247, 247, 247, 255));
        brush18.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush18);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush17);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush17);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Highlight, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Link, brush9);
        palette.setBrush(QPalette::Disabled, QPalette::LinkVisited, brush10);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush11);
        QBrush brush19(QColor(0, 0, 0, 255));
        brush19.setStyle(Qt::NoBrush);
        palette.setBrush(QPalette::Disabled, QPalette::NoRole, brush19);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush13);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush5);
        QBrush brush20(QColor(255, 0, 0, 128));
        brush20.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush20);
#endif
        Widget->setPalette(palette);
        verticalLayoutWidget = new QWidget(Widget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(610, 360, 82, 241));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        withdraw = new QPushButton(verticalLayoutWidget);
        withdraw->setObjectName(QString::fromUtf8("withdraw"));
        withdraw->setEnabled(true);
        sizePolicy.setHeightForWidth(withdraw->sizePolicy().hasHeightForWidth());
        withdraw->setSizePolicy(sizePolicy);
        QFont font;
        font.setBold(true);
        withdraw->setFont(font);
        withdraw->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout->addWidget(withdraw);

        restart = new QPushButton(verticalLayoutWidget);
        restart->setObjectName(QString::fromUtf8("restart"));
        restart->setEnabled(true);
        sizePolicy.setHeightForWidth(restart->sizePolicy().hasHeightForWidth());
        restart->setSizePolicy(sizePolicy);
        restart->setFont(font);
        restart->setCursor(QCursor(Qt::PointingHandCursor));
        restart->setFocusPolicy(Qt::StrongFocus);
        restart->setAcceptDrops(false);
        restart->setFlat(true);

        verticalLayout->addWidget(restart);

        verticalLayoutWidget_2 = new QWidget(Widget);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(609, 59, 81, 171));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        Human_win = new QLabel(verticalLayoutWidget_2);
        Human_win->setObjectName(QString::fromUtf8("Human_win"));
        Human_win->setEnabled(false);
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush21(QColor(255, 0, 0, 128));
        brush21.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush21);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        QBrush brush22(QColor(255, 0, 0, 128));
        brush22.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush22);
#endif
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush17);
        QBrush brush23(QColor(255, 0, 0, 128));
        brush23.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush23);
#endif
        Human_win->setPalette(palette1);
        Human_win->setTextFormat(Qt::RichText);

        verticalLayout_2->addWidget(Human_win);

        Machine_win = new QLabel(verticalLayoutWidget_2);
        Machine_win->setObjectName(QString::fromUtf8("Machine_win"));
        Machine_win->setEnabled(false);
        Machine_win->setTextFormat(Qt::RichText);

        verticalLayout_2->addWidget(Machine_win);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "\344\272\224\345\255\220\346\243\213\344\272\272\346\234\272\345\257\271\345\206\263", nullptr));
        withdraw->setText(QCoreApplication::translate("Widget", "\346\202\224\346\243\213", nullptr));
#if QT_CONFIG(statustip)
        restart->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        restart->setText(QCoreApplication::translate("Widget", "\351\207\215\345\274\200", nullptr));
        Human_win->setText(QCoreApplication::translate("Widget", "\347\216\251\345\256\266\350\216\267\350\203\234", nullptr));
        Machine_win->setText(QCoreApplication::translate("Widget", "\347\224\265\350\204\221\350\216\267\350\203\234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
