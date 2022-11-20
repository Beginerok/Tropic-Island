#include "MyWidget.h"
#pragma comment(lib,"Qt5Cored.lib")
#pragma comment(lib,"Qt5Guid.lib")
#pragma comment(lib,"Qt5Widgetsd.lib")
#pragma comment(lib,"Qt5OpenGLd.lib")
#pragma comment(lib,"Qt5OpenGLExtensionsd.lib")
#pragma comment(lib,"OpenGL32.lib")
MyWidget::MyWidget(QWidget* parent) // конструктор
{
	timer = new QTimer;
	connect(timer, &QTimer::timeout,this, &MyWidget::change);
	timer->start(10);
	rotate = 0;
	loading = true;
	iter = -1;
	bonus = false;
	firsttime = false;
	online = false;
	wait = false;
	tmpcounter = 0;
	number = -1;
	F = new bool[10];
	for (int i = 0; i < 10; i++)
		F[i] = false;
	pressbutton = 0;
	upbutton = 1;
    this->setWindowTitle(QString("sosok"));
    resize(700, 500); // задаем размеры окна
     // создаем кнопку
    //qw.setParent(&qw);
	m_button.push_back(new QPushButton("My Button1", this));
	m_button.push_back(new QPushButton("My Button2", this));
	m_button.push_back(new QPushButton("My Button3", this));
	m_button.push_back(new QPushButton("My Button4", this));
	m_button.push_back(new QPushButton("My Button5", this));
	m_button.push_back(new QPushButton("My Button6", this));
	m_button.push_back(new QPushButton("My Button7", this));
	m_button.push_back(new QPushButton("My Button8", this));
	m_button.push_back(new QPushButton("My Button9", this));
	m_button.push_back(new QPushButton("My Button10", this));
    // устанавливаем размер и положение кнопки
    m_button[0]->setGeometry(QRect(QPoint(50, 400), QSize(100, 50)));
    m_button[1]->setGeometry(QRect(QPoint(170, 400), QSize(100, 50)));
    m_button[2]->setGeometry(QRect(QPoint(290, 400), QSize(100, 50)));
    m_button[3]->setGeometry(QRect(QPoint(410, 400), QSize(100, 50)));
    m_button[4]->setGeometry(QRect(QPoint(530, 400), QSize(100, 50)));
    //connect(m_button, SIGNAL(released()), this, SLOT(handleButton()));
    QObject::connect(m_button[0], &QPushButton::clicked, [=]() {
        // мен€ем текст
        m_button[0]->setText("Example1");
        // измен€ем размер кнопки
       // m_button->resize(100, 100);
		F[0] = !F[0];
        });
	
    QObject::connect(m_button[1], &QPushButton::clicked, [=]() {
        // мен€ем текст
        m_button[1]->setText("Example2");
        // измен€ем размер кнопки
       // m_button->resize(100, 100);
		F[1] = !F[1];
		if (!bonus)
		{
			Logic_->firstline = false;
			Logic_->secondline = false;
			Logic_->thirdline = false;
			Logic_->SetCredits(Logic_->GetCredits() + Logic_->GetWin(), online);
			Logic_->SetWin(0.0f);
			Sound_->Play(4);
		}
        });

	
    QObject::connect(m_button[2], &QPushButton::clicked, [=]() {
        // мен€ем текст
        m_button[2]->setText("Example3");
        // измен€ем размер кнопки
       // m_button->resize(100, 100);
	
		F[2] = !F[2];
		pressbutton += 1;
		upbutton += 1;
		if (!bonus)
		{
			Sound_->Play(5);
			if (Logic_->firstline || Logic_->secondline || Logic_->thirdline)
			{
				Logic_->firstline = false;
				Logic_->secondline = false;
				Logic_->thirdline = false;
				Logic_->SetCredits(Logic_->GetCredits() + Logic_->GetWin(), online);
				Logic_->SetWin(0.0f);
				Sound_->Play(4);
			}
			Logic_->SetCredits(Logic_->GetCredits() - Logic_->GetTotalBet(), online);
			Logic_->checkwin = false;
			showline = false;
		}
        });

	m_button[2]->installEventFilter(this);
    QObject::connect(m_button[3], &QPushButton::clicked, [=]() {
        // мен€ем текст
        m_button[3]->setText("Example4");
        // измен€ем размер кнопки
       // m_button->resize(100, 100);
		F[3] = !F[3];
		if (Logic_->GetWin() > 0 && !bonus)
		{
			bonus = true;
			Logic_->SetRandom();
		}
        });

    QObject::connect(m_button[4], &QPushButton::clicked, [=]() {
        // мен€ем текст
        m_button[4]->setText("Example5");
        // измен€ем размер кнопки
       // m_button->resize(100, 100);
		F[4] = !F[4];
        });
}
void MyWidget::change()
{
	//rotate+=1;
	update();
}
void MyWidget::initializeGL()
{
	//QOpenGLContext* ctx = new QOpenGLContext();
    //QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    glClearColor(0,0,0,0); // заполн€ем экран белым цветом
    //glEnable(GL_DEPTH_TEST); // задаем глубину проверки пикселей
    //glShadeModel(GL_FLAT); // убираем режим сглаживани€ цветов
    //glEnable(GL_CULL_FACE); // говорим, что будем строить только внешние поверхности
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // фигуры будут закрашены с обеих сторон
	gluLookAt(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	image1.load("content//drum//auto1.png"); // загружаем изображение в переменную image1
	// конвертируем изображение в формат дл€ работы с OpenGL:
	texture = new QOpenGLTexture(image1.mirrored());
	texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
	texture->setMagnificationFilter(QOpenGLTexture::Linear);

	image1.load("content//drum//auto2.png"); // загружаем изображение в переменную image1
	// конвертируем изображение в формат дл€ работы с OpenGL:
	texture2 = new QOpenGLTexture(image1.mirrored());
	texture2->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
	texture2->setMagnificationFilter(QOpenGLTexture::Linear);
	Scene1_ = new Scene1();
	Scene1_->LoadWelcome();
}

void MyWidget::resizeGL(int nWidth, int nHeight)
{
    glViewport(0, 0, nHeight, nHeight); // установка точки обзора
    glMatrixMode(GL_PROJECTION); // установка режима матрицы
    glLoadIdentity(); // загрузка матрицы
	glMatrixMode(GL_MODELVIEW); // задаем модельно-видовую матрицу
	glLoadIdentity();           // загрузка единичную матрицу
	//glOrtho(-2, 2, -2, 2, -2, 2);
	gluLookAt(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}
bool MyWidget::eventFilter(QObject* watched, QEvent* event)
{
	if (event->type() == QEvent::MouseButtonRelease)
	{
		/*Mouse release button event */
		qDebug() << tr("Monitor button event, mouse release button event");
		pressbutton = 1;
		upbutton = 0;	
		Logic_->SetDrum();
		return true;
	}
}
void MyWidget::SetElements(Scene1* Scene1__, Scene1* Scene2__, Logic* Logic__, Sound* Sound__)
{
	//QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
	this->Scene1_ = Scene1__;
	this->Scene2_ = Scene2__;
	this->Logic_ = Logic__;
	this->Sound_ = Sound__;
}
void MyWidget::Show()
{
	texture->bind();
	//glColor4f(1,0,0,0); // задаем цвет
	glBegin(GL_QUADS); // говорим, что рисовать будем пр€моугольник
	// задаем вершины многоугольника
	glTexCoord2f(1, 1);
	glVertex3f(1, 1,-1);
	glTexCoord2f(0, 1);
	glVertex3f(0, 1, -1);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, -1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 0, -1);

	texture2->bind();
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 0.5, 1);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 0.5, 1);
	glTexCoord2f(0, 0);
	glVertex3f(-1, -1, 1);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, -1, 1);
	glEnd();
}
void MyWidget::paintGL() // рисование
{
	//std::cout<<rotate<<std::endl;
	
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка экрана
		//glEnable(GL_DEPTH_TEST);
		//glEnable(GL_TEXTURE_2D);

		//Show();

		//Scene1_->ShowWelcome(loading);


	
#if WINAPI_==1
		if (!WindowsWinApi_->keyboard__->offline && !online)
			Sound_->Play(2);
		online = !WindowsWinApi_->keyboard__->offline;
#endif
		if (!firsttime
#if DBAPI_ == 1
			&& Logic_->dbconn->userid != -1
#endif
			)
		{
			firsttime = true;
			Logic_->SetCredits();//
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_TEXTURE_2D);

		int countdrums = 5;
		int counttextureondrums = 6;
		if (!loading)
		{
			/*
			if (bonus || wait)
			{
				if ((Logic_->GetWin() > 0 && WindowsWinApi_->GetF()[5]))
				{
					bonus = false;
					Logic_->firstline = false;
					Logic_->secondline = false;
					Logic_->thirdline = false;
					Logic_->SetCredits(Logic_->GetCredits() + Logic_->GetWin(), online);
					Logic_->SetWin(0.0f);
					Sound_->Play(4);
				}
				for (int i = 6; i < 10; i++)
				{
					if (WindowsWinApi_->GetF()[i] && !wait)
					{
						wait = true;
						tmpcounter = 0;
						number = i;
					}
				}
				glDisable(GL_DEPTH_TEST);
				Scene2_->ShowBackGround(WindowsWinApi_->GetF(), Logic_->GetRandom(), Logic_->GetCredits(), Logic_->GetWin(), Logic_->GetTotalBet());
				glEnable(GL_DEPTH_TEST);
				Sound_->Pause(0);
				Sound_->Play(7);
				if (wait)
				{
					if (tmpcounter > 30)
					{
						wait = false;
						for (int i = number; i < number + 1; i++)
						{
							{
								if (((Logic_->GetRandom()[0] - 3) % 13) < ((Logic_->GetRandom()[i - 5] - 3) % 13))
								{
									Logic_->SetWin(Logic_->GetWin() * 2);
									Sound_->Play(3);
									Logic_->SetRandom();
								}
								else if (((Logic_->GetRandom()[0] - 3) % 13) > ((Logic_->GetRandom()[i - 5] - 3) % 13))
								{
									Logic_->SetWin(0);
									Sound_->Play(8);
									bonus = false;
									Logic_->firstline = false;
									Logic_->secondline = false;
									Logic_->thirdline = false;
								}
								else
								{
									Logic_->SetRandom();
								}
							}
						}
					}
				}
				tmpcounter++;
			}
			else
			*/
			{
				if (Scene1_->ShowDrum(countdrums, counttextureondrums,Logic_->GetDrum(),F,pressbutton,&upbutton))
				{
					Sound_->Play(6);
					showline = true;
				}
				Scene1_->ShowButtons();
				Scene1_->ShowNumbersAndWords(Logic_->GetCredits(), Logic_->GetWin(), Logic_->GetTotalBet());
				Scene1_->ShowBorder();
				if (showline)
				{
					if (Logic_->CheckWin())
						Sound_->Play(3);
					glDisable(GL_DEPTH_TEST);
					Scene1_->ShowLine(Logic_->firstline, Logic_->secondline, Logic_->thirdline);
					glEnable(GL_DEPTH_TEST);
				}
			}
			if (F[0] && !bonus)
			{
				glDisable(GL_DEPTH_TEST);
				Scene1_->ShowHelp();
				glEnable(GL_DEPTH_TEST);
				Sound_->Pause(0);
				Sound_->Play(1);
			}
			else
				Sound_->Pause(1);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
			Scene1_->ShowWelcome(loading);
			glEnable(GL_DEPTH_TEST);
		}
		glDisable(GL_TEXTURE_2D);
		loading = Scene1_->LoadDrum(++iter);
		if (iter > 15)
			loading = Scene1_->LoadButtons(++iter);
		if (iter > 16)
			loading = Scene1_->LoadWords(++iter);
		if (iter > 17)
			loading = Scene1_->LoadNumbers(++iter);
		if (iter > 18)
			loading = Scene1_->LoadBorder(++iter);
		if (iter > 19)
			iter = 20;
		Sound_->Play(0);
		
		glFlush();
}