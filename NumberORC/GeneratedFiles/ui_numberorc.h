/********************************************************************************
** Form generated from reading UI file 'numberorc.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NUMBERORC_H
#define UI_NUMBERORC_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NumberORCClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBox_view;
    QVBoxLayout *verticalLayout_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_main;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_1;
    QLabel *label_2;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_pre;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_next;
    QGroupBox *groupBox_operation;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_openfiles;
    QPushButton *pushButton_recognization;
    QTextEdit *textEdit;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *NumberORCClass)
    {
        if (NumberORCClass->objectName().isEmpty())
            NumberORCClass->setObjectName(QString::fromUtf8("NumberORCClass"));
        NumberORCClass->resize(913, 647);
        centralWidget = new QWidget(NumberORCClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_4 = new QHBoxLayout(centralWidget);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        groupBox_view = new QGroupBox(centralWidget);
        groupBox_view->setObjectName(QString::fromUtf8("groupBox_view"));
        verticalLayout_3 = new QVBoxLayout(groupBox_view);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        scrollArea = new QScrollArea(groupBox_view);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 617, 522));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_main = new QLabel(scrollAreaWidgetContents);
        label_main->setObjectName(QString::fromUtf8("label_main"));

        verticalLayout_2->addWidget(label_main);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_3->addWidget(scrollArea);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_1 = new QLabel(groupBox_view);
        label_1->setObjectName(QString::fromUtf8("label_1"));
        label_1->setMaximumSize(QSize(120, 120));

        horizontalLayout_2->addWidget(label_1);

        label_2 = new QLabel(groupBox_view);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMaximumSize(QSize(120, 120));

        horizontalLayout_2->addWidget(label_2);

        label_3 = new QLabel(groupBox_view);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMaximumSize(QSize(120, 120));

        horizontalLayout_2->addWidget(label_3);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButton_pre = new QPushButton(groupBox_view);
        pushButton_pre->setObjectName(QString::fromUtf8("pushButton_pre"));

        horizontalLayout_3->addWidget(pushButton_pre);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButton_next = new QPushButton(groupBox_view);
        pushButton_next->setObjectName(QString::fromUtf8("pushButton_next"));

        horizontalLayout_3->addWidget(pushButton_next);


        verticalLayout_3->addLayout(horizontalLayout_3);


        horizontalLayout_4->addWidget(groupBox_view);

        groupBox_operation = new QGroupBox(centralWidget);
        groupBox_operation->setObjectName(QString::fromUtf8("groupBox_operation"));
        groupBox_operation->setMinimumSize(QSize(150, 0));
        groupBox_operation->setMaximumSize(QSize(250, 16777215));
        verticalLayout = new QVBoxLayout(groupBox_operation);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_openfiles = new QPushButton(groupBox_operation);
        pushButton_openfiles->setObjectName(QString::fromUtf8("pushButton_openfiles"));

        horizontalLayout->addWidget(pushButton_openfiles);

        pushButton_recognization = new QPushButton(groupBox_operation);
        pushButton_recognization->setObjectName(QString::fromUtf8("pushButton_recognization"));

        horizontalLayout->addWidget(pushButton_recognization);


        verticalLayout->addLayout(horizontalLayout);

        textEdit = new QTextEdit(groupBox_operation);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        verticalLayout->addWidget(textEdit);


        horizontalLayout_4->addWidget(groupBox_operation);

        NumberORCClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(NumberORCClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        NumberORCClass->setStatusBar(statusBar);

        retranslateUi(NumberORCClass);

        QMetaObject::connectSlotsByName(NumberORCClass);
    } // setupUi

    void retranslateUi(QMainWindow *NumberORCClass)
    {
        NumberORCClass->setWindowTitle(QApplication::translate("NumberORCClass", "NumberORC", 0, QApplication::UnicodeUTF8));
        groupBox_view->setTitle(QApplication::translate("NumberORCClass", "View", 0, QApplication::UnicodeUTF8));
        label_main->setText(QString());
        label_1->setText(QString());
        label_2->setText(QString());
        label_3->setText(QString());
        pushButton_pre->setText(QApplication::translate("NumberORCClass", "pre", 0, QApplication::UnicodeUTF8));
        pushButton_next->setText(QApplication::translate("NumberORCClass", "next", 0, QApplication::UnicodeUTF8));
        groupBox_operation->setTitle(QApplication::translate("NumberORCClass", "Operation", 0, QApplication::UnicodeUTF8));
        pushButton_openfiles->setText(QApplication::translate("NumberORCClass", "OpenFiles", 0, QApplication::UnicodeUTF8));
        pushButton_recognization->setText(QApplication::translate("NumberORCClass", "Recognization", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NumberORCClass: public Ui_NumberORCClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NUMBERORC_H
