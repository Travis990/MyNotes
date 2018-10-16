/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPlainTextEdit *plainTextEdit_regex;
    QLabel *label_2;
    QPlainTextEdit *plainTextEdit_content;
    QLabel *label_result;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(671, 332);
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        plainTextEdit_regex = new QPlainTextEdit(Widget);
        plainTextEdit_regex->setObjectName(QStringLiteral("plainTextEdit_regex"));

        verticalLayout->addWidget(plainTextEdit_regex);

        label_2 = new QLabel(Widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        plainTextEdit_content = new QPlainTextEdit(Widget);
        plainTextEdit_content->setObjectName(QStringLiteral("plainTextEdit_content"));

        verticalLayout->addWidget(plainTextEdit_content);

        label_result = new QLabel(Widget);
        label_result->setObjectName(QStringLiteral("label_result"));

        verticalLayout->addWidget(label_result);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        label->setText(QApplication::translate("Widget", "\346\255\243\345\210\231\350\241\250\350\276\276\345\274\217\357\274\232", nullptr));
        label_2->setText(QApplication::translate("Widget", "\346\255\243\346\226\207\357\274\232", nullptr));
        label_result->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
