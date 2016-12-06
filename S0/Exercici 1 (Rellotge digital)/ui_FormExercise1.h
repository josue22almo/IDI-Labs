/********************************************************************************
** Form generated from reading UI file 'FormExercise1.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMEXERCISE1_H
#define UI_FORMEXERCISE1_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDial>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FormExercise1
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLCDNumber *lcdHours;
    QDial *dialHours;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLCDNumber *lcdMinutes;
    QDial *dialMinutes;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonExit;

    void setupUi(QDialog *FormExercise1)
    {
        if (FormExercise1->objectName().isEmpty())
            FormExercise1->setObjectName(QString::fromUtf8("FormExercise1"));
        FormExercise1->resize(432, 313);
        gridLayout = new QGridLayout(FormExercise1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(FormExercise1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        lcdHours = new QLCDNumber(FormExercise1);
        lcdHours->setObjectName(QString::fromUtf8("lcdHours"));

        verticalLayout->addWidget(lcdHours);

        dialHours = new QDial(FormExercise1);
        dialHours->setObjectName(QString::fromUtf8("dialHours"));
        dialHours->setMaximum(23);

        verticalLayout->addWidget(dialHours);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(FormExercise1);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        lcdMinutes = new QLCDNumber(FormExercise1);
        lcdMinutes->setObjectName(QString::fromUtf8("lcdMinutes"));

        verticalLayout_2->addWidget(lcdMinutes);

        dialMinutes = new QDial(FormExercise1);
        dialMinutes->setObjectName(QString::fromUtf8("dialMinutes"));
        dialMinutes->setMaximum(59);

        verticalLayout_2->addWidget(dialMinutes);


        horizontalLayout->addLayout(verticalLayout_2);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 122, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        buttonExit = new QPushButton(FormExercise1);
        buttonExit->setObjectName(QString::fromUtf8("buttonExit"));

        horizontalLayout_3->addWidget(buttonExit);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);


        retranslateUi(FormExercise1);
        QObject::connect(buttonExit, SIGNAL(clicked()), FormExercise1, SLOT(close()));
        QObject::connect(dialHours, SIGNAL(sliderMoved(int)), lcdHours, SLOT(display(int)));
        QObject::connect(dialMinutes, SIGNAL(sliderMoved(int)), lcdMinutes, SLOT(display(int)));

        QMetaObject::connectSlotsByName(FormExercise1);
    } // setupUi

    void retranslateUi(QDialog *FormExercise1)
    {
        FormExercise1->setWindowTitle(QApplication::translate("FormExercise1", "Dialog", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FormExercise1", "Hours", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FormExercise1", "Minutes", 0, QApplication::UnicodeUTF8));
        buttonExit->setText(QApplication::translate("FormExercise1", "Exit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FormExercise1: public Ui_FormExercise1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMEXERCISE1_H
