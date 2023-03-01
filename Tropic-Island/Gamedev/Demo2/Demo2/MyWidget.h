#pragma once
#include "Logic.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Sound.h"
#if QTAPI_==1
#include <QtCore/qglobal.h>
#include <QtGui/QtGui>
#include <QtWidgets/QtWidgets>
#include <QtWidgets/QPushButton>
#include <QtCore/QTimer>
#ifdef Q_OS_LINUX
    #include<QtWidgets/qopenglwidget.h>//QtOpenGLWidgets
#endif
#ifdef Q_OS_WIN
    #include<QtOpenGLWidgets/qopenglwidget.h>
#endif

#include <QtOpenGL/QOpenGLVersionProfile>
#include <QtWidgets/QWidget>
class MyWidget
    :  public QOpenGLWidget
{
  // Q_OBJECT
public:
    MyWidget(QWidget* parent);
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
    void SetElements(Scene1*Scene1_,Scene2*Scene2_,Logic*Logic_,Sound*Sound_);
    void Show();
    bool eventFilter(QObject* watched, QEvent* event);
    void Lister();
    void FullLister();
    void SetShowHideButtons(bool set);
private slots:
    void change();
private:
    std::vector<QPushButton*> m_button;
    bool* F;
    int upbutton, pressbutton;
    Scene1* Scene1_;
    Scene2* Scene2_;
    Sound* Sound_;
    Logic* Logic_;
    bool loading, bonus, firsttime, online;
    int iter;
    bool showline;
    int tmpcounter;
    int number;
    bool wait;
    QOpenGLTexture* texture,*texture2;
    QImage image1;
    float rotate;
    QTimer* timer;

    QOpenGLContext* ctx;
    GLuint shaderProgram;
    GLuint VAO;
    QOpenGLExtraFunctions* f;
    bool enablesound;

    QWidget windowsettings;

    QLabel* labelmin, * labelmax;
    QLabel* labelwin1, *labelwin2,* labelwin3,* labelwin4, *labelwin5;
    QLabel* labelcredits, * labeltotalbet;
    QTextEdit textEditmin, textEditmax;
    QTextEdit textEditwin1, textEditwin2, textEditwin3, textEditwin4, textEditwin5;
    QTextEdit textEditcredits, textEdittotalbet;
    QPushButton setbutton;
    QCheckBox* checkbox;
};
#endif

