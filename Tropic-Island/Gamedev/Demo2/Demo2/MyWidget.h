#pragma once
#include <QtGui/QtGui>
#include <QtWidgets/QtWidgets>
#include <QtWidgets/QPushButton>
#include "Logic.h"
#include "Scene1.h"
//#include "Scene2.h"
#include "Sound.h"
#include <QtCore/QTimer>
class MyWidget
    :  public QOpenGLWidget
{
  // Q_OBJECT
public:
    MyWidget(QWidget* parent);
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
    void SetElements(Scene1*Scene1_,Scene1*Scene2_,Logic*Logic_,Sound*Sound_);
    void Show();
    bool eventFilter(QObject* watched, QEvent* event);
private slots:
    void change();
private:
    std::vector<QPushButton*> m_button;
    bool* F;
    int upbutton, pressbutton;
    Scene1* Scene1_;
    Scene1* Scene2_;
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
};


