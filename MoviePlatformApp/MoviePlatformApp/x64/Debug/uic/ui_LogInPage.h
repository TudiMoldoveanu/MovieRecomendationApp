/********************************************************************************
** Form generated from reading UI file 'LogInPage.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINPAGE_H
#define UI_LOGINPAGE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QtWidgets>

QT_BEGIN_NAMESPACE

class Ui_LogInPage
{
public:
    QWidget *centralWidget;
    QLabel *welcomeLabel;
    QPushButton *logInButton;
    QPushButton *registerButton;
    QLabel *userLabel;
    QLabel *passLable;
    QLineEdit *userLineEdit;
    QLineEdit *passLineEdit;
    QLabel *errorLabel;
    QLabel *avatarLabel;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QLabel* loaderLabel;
    QMovie* loaderMovie;
  
    void setupUi(QMainWindow *LogInPage)
    {
        if (LogInPage->objectName().isEmpty())
            LogInPage->setObjectName("LogInPage");
        LogInPage->setWindowModality(Qt::WindowModal);
        LogInPage->resize(600, 700);
        LogInPage->setStyleSheet(QString::fromUtf8("/*-----QWidget-----*/\n"
"QWidget\n"
"{\n"
"	background-color: #175282;\n"
"	color: #fff;\n"
"	border-color: #000000;\n"
"\n"
"}\n"
"\n"
"\n"
"/*-----QLabel-----*/\n"
"QLabel\n"
"{\n"
"	background-color: transparent;\n"
"	color: #fff;\n"
"	font-weight: bold;\n"
"	border-color: #000000;\n"
"\n"
"}\n"
"\n"
"\n"
"/*-----QPushButton-----*/\n"
"QPushButton\n"
"{\n"
"	background-color: #e8a813;\n"
"	color: #fff;\n"
"	font-weight: bold;\n"
"	border-radius: 2px;\n"
"	padding: 5px;\n"
"\n"
"}\n"
"\n"
"\n"
"QPushButton::hover\n"
"{\n"
"	background-color: #fcba21;\n"
"	color: #fff;\n"
"\n"
"}\n"
"\n"
"\n"
"QPushButton::pressed\n"
"{\n"
"	background-color: #fcba21;\n"
"	color: #fff;\n"
"\n"
"}\n"
"\n"
"\n"
"/*-----QToolButton-----*/\n"
"QToolButton\n"
"{\n"
"	background-color: transparent;\n"
"	color: #000000;\n"
"	border-style: solid;\n"
"	border-color: #000000;\n"
"\n"
"}\n"
"\n"
"\n"
"QToolButton::hover\n"
"{\n"
"	background-color: #d10000;\n"
"	color: #000000;\n"
"	border-radius: 15px;\n"
"	border-color: #d10000;\n"
""
                        "\n"
"}\n"
"\n"
"\n"
"QToolButton::pressed\n"
"{\n"
"	background-color: #d10000;\n"
"	color: #000000;\n"
"	border-style: solid;\n"
"	border-width: 0px;\n"
"\n"
"}\n"
"\n"
"\n"
"/*-----QLineEdit-----*/\n"
"QLineEdit{\n"
"	background-color: #4d4d4d;\n"
"	color: #fff;\n"
"	font-weight: bold;\n"
"	border-style: solid;\n"
"	border-radius: 10px;\n"
"	padding: 5px;\n"
"\n"
"}\n"
"\n"
"\n"
"/*-----QCheckBox-----*/\n"
"QCheckBox\n"
"{\n"
"	background-color: transparent;\n"
"	color: #b9b9bb;\n"
"	font-weight: bold;\n"
"\n"
"}\n"
"\n"
"\n"
"QCheckBox::indicator\n"
"{\n"
"    color: #b1b1b1;\n"
"    background-color: #00111d;\n"
"    border: 1px solid #d10000;\n"
"    width: 12px;\n"
"    height: 12px;\n"
"\n"
"}\n"
"\n"
"\n"
"QCheckBox::indicator:checked\n"
"{\n"
"    image:url(\"./ressources/check.png\"); /*To replace*/\n"
"	background-color: #d10000;\n"
"    border: 1px solid #d10000;\n"
"\n"
"}\n"
"\n"
"\n"
"QCheckBox::indicator:unchecked:hover\n"
"{\n"
"    border: 1px solid #ff0000;\n"
"\n"
"}\n"
"\n"
"\n"
"QCheckBox"
                        "::disabled\n"
"{\n"
"	color: #656565;\n"
"\n"
"}\n"
"\n"
"\n"
"QCheckBox::indicator:disabled\n"
"{\n"
"	background-color: #656565;\n"
"	color: #656565;\n"
"    border: 1px solid #656565;\n"
"\n"
"}"));

        centralWidget = new QWidget(LogInPage);
        centralWidget->setObjectName("centralWidget");
        welcomeLabel = new QLabel(centralWidget);
        welcomeLabel->setObjectName("welcomeLabel");
        welcomeLabel->setGeometry(QRect(230, 200, 171, 51));

        loaderMovie = new QMovie("loader2.gif"); 
        loaderLabel = new QLabel(centralWidget);
        loaderLabel->setObjectName("loaderLabel");
        loaderLabel->setMovie(loaderMovie);
        loaderLabel->setGeometry(QRect(275, 470, 240, 50)); // for first loader: (290, 480, 50, 50)

        QFont font;
        font.setFamilies({QString::fromUtf8("Verdana")});
        font.setPointSize(22);
        font.setBold(true);
        welcomeLabel->setFont(font);
        welcomeLabel->setStyleSheet(QString::fromUtf8("/*-----QWidget-----*/\n"
"QWidget\n"
"{\n"
"	background-color: #175282;\n"
"	color: #fff;\n"
"	border-color: #000000;\n"
"\n"
"}\n"
"\n"
"\n"
"/*-----QLabel-----*/\n"
"QLabel\n"
"{\n"
"	background-color: transparent;\n"
"	color: #fff;\n"
"	font-weight: bold;\n"
"	border-color: #000000;\n"
"\n"
"}\n"
"\n"
"\n"
"/*-----QPushButton-----*/\n"
"QPushButton\n"
"{\n"
"	background-color: #d10000;\n"
"	color: #fff;\n"
"	font-weight: bold;\n"
"	border: 1px solid #d10000;  \n"
"	border-radius: 2px;\n"
"	padding: 5px;\n"
"\n"
"}\n"
"\n"
"\n"
"QPushButton::hover\n"
"{\n"
"	background-color: #ad0000;\n"
"	color: #fff;\n"
"\n"
"}\n"
"\n"
"\n"
"QPushButton::pressed\n"
"{\n"
"	background-color: #e00000;\n"
"	color: #fff;\n"
"\n"
"}\n"
"\n"
"\n"
"/*-----QToolButton-----*/\n"
"QToolButton\n"
"{\n"
"	background-color: transparent;\n"
"	color: #000000;\n"
"	border-style: solid;\n"
"	border-color: #000000;\n"
"\n"
"}\n"
"\n"
"\n"
"QToolButton::hover\n"
"{\n"
"	background-color: #d10000;\n"
"	color: #000000;\n"
"	border-radius: 15px"
                        ";\n"
"	border-color: #d10000;\n"
"\n"
"}\n"
"\n"
"\n"
"QToolButton::pressed\n"
"{\n"
"	background-color: #d10000;\n"
"	color: #000000;\n"
"	border-style: solid;\n"
"	border-width: 0px;\n"
"\n"
"}\n"
"\n"
"\n"
"/*-----QLineEdit-----*/\n"
"QLineEdit{\n"
"	background-color: #4d4d4d;\n"
"	color: #fff;\n"
"	font-weight: bold;\n"
"	border-style: solid;\n"
"	border-radius: 5px;\n"
"	padding: 5px;\n"
"\n"
"}\n"
"\n"
"\n"
"/*-----QCheckBox-----*/\n"
"QCheckBox\n"
"{\n"
"	background-color: transparent;\n"
"	color: #b9b9bb;\n"
"	font-weight: bold;\n"
"\n"
"}\n"
"\n"
"\n"
"QCheckBox::indicator\n"
"{\n"
"    color: #b1b1b1;\n"
"    background-color: #00111d;\n"
"    border: 1px solid #d10000;\n"
"    width: 12px;\n"
"    height: 12px;\n"
"\n"
"}\n"
"\n"
"\n"
"QCheckBox::indicator:checked\n"
"{\n"
"    image:url(\"./ressources/check.png\"); /*To replace*/\n"
"	background-color: #d10000;\n"
"    border: 1px solid #d10000;\n"
"\n"
"}\n"
"\n"
"\n"
"QCheckBox::indicator:unchecked:hover\n"
"{\n"
"    border: 1px solid #ff0000;\n"
""
                        "\n"
"}\n"
"\n"
"\n"
"QCheckBox::disabled\n"
"{\n"
"	color: #656565;\n"
"\n"
"}\n"
"\n"
"\n"
"QCheckBox::indicator:disabled\n"
"{\n"
"	background-color: #656565;\n"
"	color: #656565;\n"
"    border: 1px solid #656565;\n"
"\n"
"}"));
        logInButton = new QPushButton(centralWidget);
        logInButton->setObjectName("logInButton");
        logInButton->setGeometry(QRect(110, 550, 131, 41));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Verdana")});
        font1.setPointSize(16);
        font1.setBold(true);
        logInButton->setFont(font1);
        logInButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"border-radius:10px;\n"
"}"));
        registerButton = new QPushButton(centralWidget);
        registerButton->setObjectName("registerButton");
        registerButton->setGeometry(QRect(370, 550, 131, 41));
        registerButton->setFont(font1);
        registerButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"border-radius:10px;\n"
"}"));
        userLabel = new QLabel(centralWidget);
        userLabel->setObjectName("userLabel");
        userLabel->setGeometry(QRect(60, 330, 151, 31));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Verdana")});
        font2.setPointSize(18);
        font2.setBold(true);
        userLabel->setFont(font2);
        passLable = new QLabel(centralWidget);
        passLable->setObjectName("passLable");
        passLable->setGeometry(QRect(60, 380, 141, 31));
        passLable->setFont(font2);
        userLineEdit = new QLineEdit(centralWidget);
        userLineEdit->setObjectName("userLineEdit");
        userLineEdit->setGeometry(QRect(220, 330, 321, 31));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Verdana")});
        font3.setPointSize(10);
        font3.setBold(true);
        userLineEdit->setFont(font3);
        userLineEdit->setStyleSheet(QString::fromUtf8(""));
        passLineEdit = new QLineEdit(centralWidget);
        passLineEdit->setObjectName("passLineEdit");
        passLineEdit->setGeometry(QRect(220, 380, 271, 31));
        passLineEdit->setFont(font3);
        passLineEdit->setEchoMode(QLineEdit::Password);
        passLineEdit->setClearButtonEnabled(true);
        errorLabel = new QLabel(centralWidget);
        errorLabel->setObjectName("errorLabel");
        errorLabel->setGeometry(QRect(60, 420, 471, 51));
        errorLabel->setFont(font);
        avatarLabel = new QLabel(centralWidget);
        avatarLabel->setObjectName("avatarLabel");
        avatarLabel->setGeometry(QRect(260, 70, 101, 101));
        avatarLabel->setStyleSheet(QString::fromUtf8("background-image: url(:/newPrefix/8-account-outline.png)"));
        avatarLabel->setPixmap(QPixmap(QString::fromUtf8(":/LogInPage/8-account-outline.png")));
        avatarLabel->setScaledContents(true);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(500, 380, 41, 31));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"border-radius:10px;\n"
"background-image:url(:/LogInPage/12417494831642659861-128.png)\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/LogInPage/12417494831642659861-128.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(40, 40));
        LogInPage->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LogInPage);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 600, 26));
        LogInPage->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LogInPage);
        mainToolBar->setObjectName("mainToolBar");
        LogInPage->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(LogInPage);
        statusBar->setObjectName("statusBar");
        LogInPage->setStatusBar(statusBar);

        retranslateUi(LogInPage);

        QMetaObject::connectSlotsByName(LogInPage);
    } // setupUi

    void retranslateUi(QMainWindow *LogInPage)
    {
        LogInPage->setWindowTitle(QCoreApplication::translate("LogInPage", "Log In Page", nullptr));
        welcomeLabel->setText(QCoreApplication::translate("LogInPage", "Welcome!", nullptr));
        logInButton->setText(QCoreApplication::translate("LogInPage", "Log in!", nullptr));
        registerButton->setText(QCoreApplication::translate("LogInPage", "Register!", nullptr));
        userLabel->setText(QCoreApplication::translate("LogInPage", "Username:", nullptr));
        passLable->setText(QCoreApplication::translate("LogInPage", "Password:", nullptr));
        userLineEdit->setText(QString());
        passLineEdit->setText(QString());
        errorLabel->setText(QString());
        avatarLabel->setText(QString());
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LogInPageClass: public Ui_LogInPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINPAGE_H
