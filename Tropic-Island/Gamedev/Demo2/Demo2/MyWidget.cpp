#include "MyWidget.h"
/*
// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";
*/
#pragma comment(lib,"Qt6Cored.lib")
#pragma comment(lib,"Qt6Guid.lib")
#pragma comment(lib,"Qt6Widgetsd.lib")
#pragma comment(lib,"Qt6OpenGLd.lib")
#pragma comment(lib,"Qt6OpenGLWidgetsd.lib")
//#pragma comment(lib,"Qt6OpenGLExtensionsd.lib")

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
	m_button.push_back(new QPushButton("Help", this));
	m_button.push_back(new QPushButton("Take", this));
	m_button.push_back(new QPushButton("Spin", this));
	m_button.push_back(new QPushButton("Risk", this));
	m_button.push_back(new QPushButton("Exit", this));
	
	m_button.push_back(new QPushButton("Take", this));
	m_button.push_back(new QPushButton("Risk", this));
	m_button.push_back(new QPushButton("Risk", this));
	m_button.push_back(new QPushButton("Risk", this));
	m_button.push_back(new QPushButton("Risk", this));

	// устанавливаем размер и положение кнопки
	m_button[0]->setGeometry(QRect(QPoint(50, 450), QSize(100, 50)));
	m_button[1]->setGeometry(QRect(QPoint(170, 450), QSize(100, 50)));
	m_button[2]->setGeometry(QRect(QPoint(290, 450), QSize(100, 50)));
	m_button[3]->setGeometry(QRect(QPoint(410, 450), QSize(100, 50)));
	m_button[4]->setGeometry(QRect(QPoint(530, 450), QSize(100, 50)));
	// устанавливаем размер и положение кнопки
	
	m_button[5]->setGeometry(QRect(QPoint(50, 450), QSize(100, 50)));
	m_button[6]->setGeometry(QRect(QPoint(170, 450), QSize(100, 50)));
	m_button[7]->setGeometry(QRect(QPoint(290, 450), QSize(100, 50)));
	m_button[8]->setGeometry(QRect(QPoint(410, 450), QSize(100, 50)));
	m_button[9]->setGeometry(QRect(QPoint(530, 450), QSize(100, 50)));
    
	m_button[5]->hide();
	m_button[6]->hide();
	m_button[7]->hide();
	m_button[8]->hide();
	m_button[9]->hide();

	//connect(m_button, SIGNAL(released()), this, SLOT(handleButton()));
    QObject::connect(m_button[0], &QPushButton::clicked, [=]() {
		F[0] = !F[0];
        });
	
    QObject::connect(m_button[1], &QPushButton::clicked, [=]() {
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
		F[3] = !F[3];
		if (Logic_->GetWin() > 0 && !bonus)
		{
			bonus = true;
			Logic_->SetRandom();
			SetShowHideButtons(true);
			F[3] = false;
		}
        });

    QObject::connect(m_button[4], &QPushButton::clicked, [=]() {
		F[4] = !F[4];
		exit(0);
        });

	QObject::connect(m_button[5], &QPushButton::clicked, [=]() {
		F[5] = !F[5];
		});
	QObject::connect(m_button[6], &QPushButton::clicked, [=]() {
		F[6] = !F[6];
		});
	QObject::connect(m_button[7], &QPushButton::clicked, [=]() {
		F[7] = !F[7];
		});
	QObject::connect(m_button[8], &QPushButton::clicked, [=]() {
		F[8] = !F[8];
		});
	QObject::connect(m_button[9], &QPushButton::clicked, [=]() {
		F[9] = !F[9];
		});


}
void MyWidget::SetShowHideButtons(bool set)
{
	if (set)
	{
		m_button[0]->hide();
		m_button[1]->hide();
		m_button[2]->hide();
		m_button[3]->hide();
		m_button[4]->hide();

		m_button[5]->show();
		m_button[6]->show();
		m_button[7]->show();
		m_button[8]->show();
		m_button[9]->show();
	}
	else
	{
		m_button[0]->show();
		m_button[1]->show();
		m_button[2]->show();
		m_button[3]->show();
		m_button[4]->show();

		m_button[5]->hide();
		m_button[6]->hide();
		m_button[7]->hide();
		m_button[8]->hide();
		m_button[9]->hide();
	}
}
void MyWidget::change()
{
	//rotate+=1;
	update();
}
void MyWidget::initializeGL()
{
	ctx = new QOpenGLContext();
	f = QOpenGLContext::currentContext()->extraFunctions();
	//f = QOpenGLContext::currentContext()->functions();
    glClearColor(0,0,0,0); // заполняем экран белым цветом
    //glEnable(GL_DEPTH_TEST); // задаем глубину проверки пикселей
    //glShadeModel(GL_FLAT); // убираем режим сглаживания цветов
    //glEnable(GL_CULL_FACE); // говорим, что будем строить только внешние поверхности
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // фигуры будут закрашены с обеих сторон
	gluLookAt(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	image1.load("content//drum//auto1.png"); // загружаем изображение в переменную image1
	// конвертируем изображение в формат для работы с OpenGL:
	texture = new QOpenGLTexture(image1.mirrored());
	texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
	texture->setMagnificationFilter(QOpenGLTexture::Linear);

	image1.load("content//drum//auto2.png"); // загружаем изображение в переменную image1
	// конвертируем изображение в формат для работы с OpenGL:
	texture2 = new QOpenGLTexture(image1.mirrored());
	texture2->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
	texture2->setMagnificationFilter(QOpenGLTexture::Linear);
	Scene1_ = new Scene1();
	Scene1_->LoadWelcome();
	Scene2_ = new Scene2();
#if QTAPI_==1
	Scene2_->LoadQT();
#endif
	/*
	GLuint vertexShader = f->glCreateShader(GL_VERTEX_SHADER);
	
	f->glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	f->glCompileShader(vertexShader);
	// Check for compile time errors
	GLint success;
	GLchar infoLog[512];
	f->glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		f->glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Fragment shader
	GLuint fragmentShader = f->glCreateShader(GL_FRAGMENT_SHADER);
	f->glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	f->glCompileShader(fragmentShader);
	// Check for compile time errors
	f->glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		f->glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Link shaders
	shaderProgram = f->glCreateProgram();
	f->glAttachShader(shaderProgram, vertexShader);
	f->glAttachShader(shaderProgram, fragmentShader);
	f->glLinkProgram(shaderProgram);
	// Check for linking errors
	f->glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		f->glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	f->glDeleteShader(vertexShader);
	f->glDeleteShader(fragmentShader);


	// Set up vertex data (and buffer(s)) and attribute pointers
	//GLfloat vertices[] = {
	//  // First triangle
	//   0.5f,  0.5f,  // Top Right
	//   0.5f, -0.5f,  // Bottom Right
	//  -0.5f,  0.5f,  // Top Left 
	//  // Second triangle
	//   0.5f, -0.5f,  // Bottom Right
	//  -0.5f, -0.5f,  // Bottom Left
	//  -0.5f,  0.5f   // Top Left
	//}; 
	GLfloat vertices[] = {
		 0.5f,  0.5f, 0.0f,  // Top Right
		 0.5f, -0.5f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  // Bottom Left
		-0.5f,  0.5f, 0.0f   // Top Left 
	};
	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3,  // First Triangle
		1, 2, 3   // Second Triangle
	};
	GLuint VBO, EBO;
	f->glGenVertexArrays(1, &VAO);
	f->glGenBuffers(1, &VBO);
	f->glGenBuffers(1, &EBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	f->glBindVertexArray(VAO);

	f->glBindBuffer(GL_ARRAY_BUFFER, VBO);
	f->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	f->glEnableVertexAttribArray(0);

	f->glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	f->glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO


	// Uncommenting this call will result in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	*/
	QPair<int, int> version = QOpenGLContext(ctx).format().version();
	std::cout << version.first << " " << version.second << std::endl;
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
	m_button[0]->setGeometry(QRect(QPoint(0, nHeight - 50), QSize(nWidth / 5, 50)));
	m_button[1]->setGeometry(QRect(QPoint(0 + nWidth / 5, nHeight - 50), QSize(nWidth / 5, 50)));
	m_button[2]->setGeometry(QRect(QPoint(0 + nWidth / 5*2, nHeight - 50), QSize(nWidth / 5, 50)));
	m_button[3]->setGeometry(QRect(QPoint(0 + nWidth / 5*3, nHeight - 50), QSize(nWidth / 5, 50)));
	m_button[4]->setGeometry(QRect(QPoint(0 + nWidth / 5*4, nHeight - 50), QSize(nWidth / 5, 50)));

	m_button[5]->setGeometry(QRect(QPoint(0, nHeight - 50), QSize(nWidth / 5, 50)));
	m_button[6]->setGeometry(QRect(QPoint(0 + nWidth / 5, nHeight - 50), QSize(nWidth / 5, 50)));
	m_button[7]->setGeometry(QRect(QPoint(0 + nWidth / 5 * 2, nHeight - 50), QSize(nWidth / 5, 50)));
	m_button[8]->setGeometry(QRect(QPoint(0 + nWidth / 5 * 3, nHeight - 50), QSize(nWidth / 5, 50)));
	m_button[9]->setGeometry(QRect(QPoint(0 + nWidth / 5 * 4, nHeight - 50), QSize(nWidth / 5, 50)));
}
bool MyWidget::eventFilter(QObject* watched, QEvent* event)
{
	if (watched == m_button[2])
	{
		if (event->type() == QEvent::MouseButtonRelease)
		{
			F[2] = false;
			/*Mouse release button event */
			qDebug() << tr("Monitor button event, mouse release button event");
			pressbutton = 1;
			upbutton = 0;
			return true;
		}
		else if (event->type() == QEvent::MouseButtonPress)
		{
			/*Mouse down button event */
			qDebug() << tr("Monitor button event, button press event");
			F[2] = true;
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
			return true;
		}
	}
	return false;
}
void MyWidget::SetElements(Scene1* Scene1__, Scene2* Scene2__, Logic* Logic__, Sound* Sound__)
{
	//QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
	this->Scene1_ = Scene1__;
	this->Scene2_ = Scene2__;
	this->Logic_ = Logic__;
	this->Sound_ = Sound__;
}

void MyWidget::Lister()
{
	glColor3f(0.0, 0.5, 0.0);
	glBegin(GL_QUADS);
	for (float i = -0.8; i < 0.8; i += 0.1)
	{
		glVertex3f(0, i, 0);
		glVertex3f(0.1, i + 0.1, 0);
		glVertex3f(0.1, i + 0.2, 0);
		glVertex3f(0, i + 0.1, 0);
	}
	glEnd();
	
	glBegin(GL_TRIANGLES);
	glVertex3f(0, 0.8, 0);
	glVertex3f(0.1, 0.9, 0);
	glVertex3f(0, 1.0, 0);
	glEnd();
	glColor3f(0, 1.0, 0);
	glLineWidth((GLfloat)1);
	glBegin(GL_LINES);
	glVertex3f(0, -0.8, -0.01);
	glVertex3f(0, 1, -0.01);
	glVertex3f(0, -0.8, 0.01);
	glVertex3f(0, 1, 0.01);
	glEnd();
	glBegin(GL_LINES);
	for (float i = -0.8; i < 0.9; i += 0.1)
	{
		glVertex3f(0, i, -0.01);
		glVertex3f(0.11, i + 0.1, -0.01);
		glVertex3f(0, i, 0.01);
		glVertex3f(0.11, i + 0.1, 0.01);
	}
	glEnd();
}

void MyWidget::FullLister()
{
	Lister();
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	Lister();
	glPopMatrix();
}
void MyWidget::Show()
{
	/*
	// Draw our first triangle
	f->glUseProgram(shaderProgram);
	f->glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	f->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	f->glBindVertexArray(0);
	*/
	glRotatef(1, 0, 1, 0);
	glPushMatrix();
	glScalef(0.7, 0.7, 1);
	glColor3f(0.0, 0.5, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0,-0.8,0);
	glVertex3f(-0.01,-1,0);
	glVertex3f(0.01, -1, 0);
	glEnd();
	FullLister();
	
	glPushMatrix();
	glTranslatef(-0.2, -0.45, 0);
	glRotatef(30, 0, 0, 1);
	glScalef(0.6, 0.6, 1);
	FullLister();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.2,-0.45, 0);
	glRotatef(-30, 0, 0, 1);
	glScalef(0.6, 0.6, 1);
	FullLister();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, -0.7, 0);
	glRotatef(60, 0, 0, 1);
	glScalef(0.4, 0.4, 1);
	FullLister();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.3, -0.7, 0);
	glRotatef(-60, 0, 0, 1);
	glScalef(0.4, 0.4, 1);
	FullLister();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.15, -0.9, 0);
	glRotatef(100, 0, 0, 1);
	glScalef(0.2, 0.2, 1);
	FullLister();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.15, -0.9, 0);
	glRotatef(-100, 0, 0, 1);
	glScalef(0.2, 0.2, 1);
	FullLister();
	glPopMatrix();
	
	glPopMatrix();

/*
	texture->bind();
	//glColor4f(1,0,0,0); // задаем цвет
	glBegin(GL_QUADS); // говорим, что рисовать будем прямоугольник
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
	*/
}
void MyWidget::paintGL() // рисование
{
		glClear(GL_COLOR_BUFFER_BIT /**/ | GL_DEPTH_BUFFER_BIT); // очистка экрана
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
			
			if (bonus || wait)
			{
				if ((Logic_->GetWin() > 0 && F[5]))
				{
					bonus = false;
					Logic_->firstline = false;
					Logic_->secondline = false;
					Logic_->thirdline = false;
					Logic_->SetCredits(Logic_->GetCredits() + Logic_->GetWin(), online);
					Logic_->SetWin(0.0f);
					Sound_->Play(4);
					F[5] = false;
					SetShowHideButtons(false);
				}
				for (int i = 6; i < 10; i++)
				{
					if (F[i] && !wait)
					{
						wait = true;
						tmpcounter = 0;
						number = i;
						F[i] = false;
					}
				}
				glDisable(GL_DEPTH_TEST);
				Scene2_->ShowBackGround(F, Logic_->GetRandom(), Logic_->GetCredits(), Logic_->GetWin(), Logic_->GetTotalBet());
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
									SetShowHideButtons(false);
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

			{
				if (Scene1_->ShowDrum(countdrums, counttextureondrums,Logic_->GetDrum(),F,pressbutton,&upbutton))
				{
					Sound_->Play(6);
					showline = true;
				}
				else
				{
					for (int i = 0; i < Scene1_->CountDrum; i++)
						if (Scene1_->changedrum[i])
							Logic_->SetDrum(i);
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
		if(!F[0])
			Sound_->Play(0);
		
		//glFlush();
}