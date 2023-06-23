#include "MyWidget.h"
#if QTAPI_==1

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

const GLchar* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 position;\n"
"layout(location = 1) in vec4 color;\n"
"layout(location = 2) in vec2 texCoord;\n"
"out vec4 ourColor;\n"
"out vec2 TexCoord;\n"
"uniform mat4 transform;\n"
"void main()\n"
"{\n"
"gl_Position = transform*vec4(position, 1.0f);\n"
"ourColor = color;\n"

"TexCoord = texCoord;\n"
"}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
"in vec4 ourColor;\n"
"in vec2 TexCoord;\n"
"out vec4 color;\n"
"uniform sampler2D ourTexture;\n"
"void main()\n"
"{\n"
"color = texture(ourTexture, TexCoord);\n"
"}\0";
// Shaders
/*
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";
*/
/*
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
   // resize(1920, 1000); // задаем размеры окна
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
    



	//connect(m_button, SIGNAL(released()), this, SLOT(handleButton()));
    QObject::connect(m_button[0], &QPushButton::clicked, [=]() {
		F[0] = !F[0];
        });
	
    QObject::connect(m_button[1], &QPushButton::clicked, [=]() {
		F[1] = !F[1];
		if (!bonus)
		{
			Logic_->SetCredits(Logic_->GetCredits() + Logic_->GetWin(), online);
			Logic_->SetWin(0.0f);
			Sound_->Play(4);
		}
        });

    QObject::connect(m_button[2], &QPushButton::clicked, [=]() {
		if (Logic_->GetCredits() - Logic_->GetTotalBet() >= Logic_->GetTotalBet())
		{
			F[2] = !F[2];
			pressbutton += 1;
			upbutton += 1;
			if (!bonus)
			{
				Sound_->Play(5);
				if (Logic_->checkwin)
				{
					Logic_->SetCredits(Logic_->GetCredits() + Logic_->GetWin(), online);
					Logic_->SetWin(0.0f);
					Sound_->Play(4);
				}
				Logic_->SetCredits(Logic_->GetCredits() - Logic_->GetTotalBet(), online);
				Logic_->checkwin = false;
				showline = false;
			}
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

	enablesound = false;
	m_button[0]->hide();
	m_button[1]->hide();
	m_button[2]->hide();
	m_button[3]->hide();
	m_button[4]->hide();

	m_button[5]->hide();
	m_button[6]->hide();
	m_button[7]->hide();
	m_button[8]->hide();
	m_button[9]->hide();
}
bool MyWidget::eventFilter(QObject* watched, QEvent* event)
{
	if (watched == m_button[2])
	{

		if (event->type() == QEvent::MouseButtonRelease)
		{
			if (Logic_->GetCredits() - Logic_->GetTotalBet() >= 0)
			{
				if (!bonus)
					Logic_->SetCredits(Logic_->GetCredits() - Logic_->GetTotalBet(), online);
				F[2] = false;
				/*Mouse release button event */
				qDebug() << tr("Monitor button event, mouse release button event");
				pressbutton = 1;
				upbutton = 0;
				return true;
			}
		}
		else if (event->type() == QEvent::MouseButtonPress)
		{
			if (Logic_->GetCredits() - Logic_->GetTotalBet() >= 0)
			{
				/*Mouse down button event */
				qDebug() << tr("Monitor button event, button press event");
				F[2] = true;
				pressbutton += 1;
				upbutton += 1;
				if (!bonus)
				{
					Sound_->Play(5);
					if (Logic_->checkwin)
					{
						Logic_->SetCredits(Logic_->GetCredits() + Logic_->GetWin(), online);
						Logic_->SetWin(0.0f);
						Sound_->Play(4);
					}
					Logic_->checkwin = false;
					showline = false;
				}
			}
			return true;
		}
	}
	return false;
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
	//Build and compile our shader program
	//Vertex shader
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
	/*GLuint */ shaderProgram = f->glCreateProgram();
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
	
	Scene1_ = new Scene1();
	Scene1_->LoadWelcome();
	Scene1_->LoadDrum(f);
	Scene1_->LoadBorder(f);
	Scene2_ = new Scene2();
#if QTAPI_==1
	Scene2_->LoadQT();
#endif
	QPair<int, int> version = QOpenGLContext(ctx).format().version();
	std::cout << version.first << " " << version.second << std::endl;
	//glClearColor(0, 0, 0, 0);
	//gluLookAt(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}
void MyWidget::resizeGL(int nWidth, int nHeight)
{
    glViewport(0, 0, nHeight, nHeight); // установка точки обзора
    glMatrixMode(GL_PROJECTION); // установка режима матрицы
    glLoadIdentity(); // загрузка матрицы
	glMatrixMode(GL_MODELVIEW); // задаем модельно-видовую матрицу
	glLoadIdentity();           // загрузка единичную матрицу
	//glOrtho(-2, 2, -2, 2, -2, 2);
	//gluLookAt(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
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

void MyWidget::SetElements(Scene1* Scene1__, Scene2* Scene2__, Logic* Logic__, Sound* Sound__)
{
	newAPI();
	//QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
	this->Scene1_ = Scene1__;
	this->Scene2_ = Scene2__;
	this->Logic_ = Logic__;
	this->Sound_ = Sound__;

	windowsettings.setWindowTitle("Settings");
	windowsettings.show();
	QPixmap pix1("content\\drum\\auto1.png");
	labelpic1.setParent(&windowsettings);
	pix1 = pix1.scaled(50, 50, Qt::KeepAspectRatio);
	labelpic1.setPixmap(pix1);
	labelpic1.setGeometry(QRect(QPoint(10, 10), QSize(50, 50)));
	labelpic1.show();
	checkbox1 = new QCheckBox("auto1", &windowsettings);
	checkbox1->setCheckState(Qt::Checked);
	checkbox1->setGeometry(QRect(QPoint(65, 10), QSize(50, 30)));
	checkbox1->show();

	QPixmap pix2("content\\drum\\auto2.png");
	labelpic2.setParent(&windowsettings);
	pix2 = pix2.scaled(50, 50, Qt::KeepAspectRatio);
	labelpic2.setPixmap(pix2);
	labelpic2.setGeometry(QRect(QPoint(10, 40), QSize(50, 50)));
	labelpic2.show();
	checkbox2 = new QCheckBox("auto2", &windowsettings);
	checkbox2->setCheckState(Qt::Checked);
	checkbox2->setGeometry(QRect(QPoint(65, 40), QSize(50, 30)));
	checkbox2->show();

	QPixmap pix3("content\\drum\\auto3.png");
	labelpic3.setParent(&windowsettings);
	pix3 = pix3.scaled(50, 50, Qt::KeepAspectRatio);
	labelpic3.setPixmap(pix3);
	labelpic3.setGeometry(QRect(QPoint(10, 70), QSize(50, 50)));
	labelpic3.show();
	checkbox3 = new QCheckBox("auto3", &windowsettings);
	checkbox3->setCheckState(Qt::Checked);
	checkbox3->setGeometry(QRect(QPoint(65, 70), QSize(50, 30)));
	checkbox3->show();

	QPixmap pix4("content\\drum\\auto4.png");
	labelpic4.setParent(&windowsettings);
	pix4 = pix4.scaled(50, 50, Qt::KeepAspectRatio);
	labelpic4.setPixmap(pix4);
	labelpic4.setGeometry(QRect(QPoint(10, 100), QSize(50, 50)));
	labelpic4.show();
	checkbox4 = new QCheckBox("auto4", &windowsettings);
	checkbox4->setCheckState(Qt::Checked);
	checkbox4->setGeometry(QRect(QPoint(65, 100), QSize(50, 30)));
	checkbox4->show();

	QPixmap pix5("content\\drum\\auto5.png");
	labelpic5.setParent(&windowsettings);
	pix5 = pix5.scaled(50, 50, Qt::KeepAspectRatio);
	labelpic5.setPixmap(pix5);
	labelpic5.setGeometry(QRect(QPoint(10, 130), QSize(50, 50)));
	labelpic5.show();
	checkbox5 = new QCheckBox("auto5", &windowsettings);
	checkbox5->setCheckState(Qt::Checked);
	checkbox5->setGeometry(QRect(QPoint(65, 130), QSize(50, 30)));
	checkbox5->show();

	QPixmap pixwild("content\\drum\\wild.png");
	labelpicwild.setParent(&windowsettings);
	pixwild = pixwild.scaled(50, 50, Qt::KeepAspectRatio);
	labelpicwild.setPixmap(pixwild);
	labelpicwild.setGeometry(QRect(QPoint(10, 160), QSize(50, 50)));
	labelpicwild.show();
	checkboxwild = new QCheckBox("wild", &windowsettings);
	checkboxwild->setCheckState(Qt::Checked);
	checkboxwild->setGeometry(QRect(QPoint(65, 160), QSize(50, 30)));
	checkboxwild->show();

	QPixmap pixbonus("content\\drum\\bonus.png");
	labelpicbonus.setParent(&windowsettings);
	pixbonus = pixbonus.scaled(50, 50, Qt::KeepAspectRatio);
	labelpicbonus.setPixmap(pixbonus);
	labelpicbonus.setGeometry(QRect(QPoint(10, 190), QSize(50, 50)));
	labelpicbonus.show();
	checkboxbonus = new QCheckBox("bonus", &windowsettings);
	checkboxbonus->setCheckState(Qt::Checked);
	checkboxbonus->setGeometry(QRect(QPoint(65, 190), QSize(50, 30)));
	checkboxbonus->show();

	labelmin = new QLabel();
	labelmin->setParent(&windowsettings);
	labelmin->setText("min(range 0-6)");
	labelmin->setGeometry(QRect(QPoint(120, 10), QSize(80, 50)));
	labelmin->show();

	labelmax = new QLabel();
	labelmax->setParent(&windowsettings);
	labelmax->setText("max(range 0-6)");
	labelmax->setGeometry(QRect(QPoint(120, 70), QSize(80, 50)));
	labelmax->show();

	textEditmin.setParent(&windowsettings);
	textEditmin.setText("0");
	textEditmin.setGeometry(QRect(QPoint(200, 10), QSize(30, 30)));
	textEditmin.show();

	textEditmax.setParent(&windowsettings);
	textEditmax.setText("6");
	textEditmax.setGeometry(QRect(QPoint(200, 70), QSize(30, 30)));
	textEditmax.show();
	Logic_->SetMinMax(textEditmin.toPlainText().toInt(), textEditmax.toPlainText().toInt());
	
	checkbox = new QCheckBox("Enable Sound", &windowsettings);
	checkbox->setCheckState(Qt::Unchecked);
	checkbox->setGeometry(QRect(QPoint(10, 250), QSize(100, 50)));
	checkbox->show();

	setbutton.setParent(&windowsettings);
	setbutton.setText("Change");
	setbutton.setGeometry(QRect(QPoint(10, 300), QSize(100, 50)));
	setbutton.show();

	

	labelwin1 = new QLabel();
	labelwin1->setParent(&windowsettings);
	labelwin1->setText("WIN1");
	labelwin1->setGeometry(QRect(QPoint(230, 10), QSize(100, 50)));
	labelwin1->show();
	textEditwin1.setParent(&windowsettings);
	textEditwin1.setText("5");
	textEditwin1.setGeometry(QRect(QPoint(350, 10), QSize(100, 20)));
	textEditwin1.show();

	

	labelwin2 = new QLabel();
	labelwin2->setParent(&windowsettings);
	labelwin2->setText("WIN2");
	labelwin2->setGeometry(QRect(QPoint(230, 70), QSize(100, 50)));
	labelwin2->show();
	textEditwin2.setParent(&windowsettings);
	textEditwin2.setText("10");
	textEditwin2.setGeometry(QRect(QPoint(350, 70), QSize(100, 50)));
	textEditwin2.show();


	labelwin3 = new QLabel();
	labelwin3->setParent(&windowsettings);
	labelwin3->setText("WIN3");
	labelwin3->setGeometry(QRect(QPoint(230, 130), QSize(100, 50)));
	labelwin3->show();
	textEditwin3.setParent(&windowsettings);
	textEditwin3.setText("15");
	textEditwin3.setGeometry(QRect(QPoint(350, 130), QSize(100, 50)));
	textEditwin3.show();


	labelwin4 = new QLabel();
	labelwin4->setParent(&windowsettings);
	labelwin4->setText("WIN4");
	labelwin4->setGeometry(QRect(QPoint(230, 200), QSize(100, 50)));
	labelwin4->show();
	textEditwin4.setParent(&windowsettings);
	textEditwin4.setText("20");
	textEditwin4.setGeometry(QRect(QPoint(350, 200), QSize(100, 50)));
	textEditwin4.show();


	labelwin5 = new QLabel();
	labelwin5->setParent(&windowsettings);
	labelwin5->setText("WIN5");
	labelwin5->setGeometry(QRect(QPoint(230, 270), QSize(100, 50)));
	labelwin5->show();
	textEditwin5.setParent(&windowsettings);
	textEditwin5.setText("25");
	textEditwin5.setGeometry(QRect(QPoint(350, 270), QSize(100, 50)));
	textEditwin5.show();

	labelwild = new QLabel();
	labelwild->setParent(&windowsettings);
	labelwild->setText("WILD");
	labelwild->setGeometry(QRect(QPoint(230, 340), QSize(100, 50)));
	labelwild->show();
	textEditwild.setParent(&windowsettings);
	textEditwild.setText("50");
	textEditwild.setGeometry(QRect(QPoint(350, 340), QSize(100, 50)));
	textEditwild.show();

	labelbonus = new QLabel();
	labelbonus->setParent(&windowsettings);
	labelbonus->setText("BONUS");
	labelbonus->setGeometry(QRect(QPoint(230, 410), QSize(100, 50)));
	labelbonus->show();
	textEditbonus.setParent(&windowsettings);
	textEditbonus.setText("10");
	textEditbonus.setGeometry(QRect(QPoint(350, 410), QSize(100, 50)));
	textEditbonus.show();

	labelcredits = new QLabel();
	labelcredits->setParent(&windowsettings);
	labelcredits->setText("credits");
	labelcredits->setGeometry(QRect(QPoint(470, 10), QSize(100, 50)));
	labelcredits->show();
	textEditcredits.setParent(&windowsettings);
	textEditcredits.setText("1000");
	textEditcredits.setGeometry(QRect(QPoint(580, 10), QSize(100, 50)));
	textEditcredits.show();

	labeltotalbet = new QLabel();
	labeltotalbet->setParent(&windowsettings);
	labeltotalbet->setText("totalbet");
	labeltotalbet->setGeometry(QRect(QPoint(470, 70), QSize(100, 50)));
	labeltotalbet->show();
	textEdittotalbet.setParent(&windowsettings);
	textEdittotalbet.setText("1");
	textEdittotalbet.setGeometry(QRect(QPoint(580, 70), QSize(100, 50)));
	textEdittotalbet.show();

	
	QObject::connect(&setbutton, &QPushButton::clicked, [=]() {
		Logic_->SetMinMax(textEditmin.toPlainText().toInt(), textEditmax.toPlainText().toInt());
		Logic_->SetWin(textEditwin1.toPlainText().toInt(), textEditwin2.toPlainText().toInt(), textEditwin3.toPlainText().toInt(), textEditwin4.toPlainText().toInt(), textEditwin5.toPlainText().toInt(), textEditwild.toPlainText().toInt(), textEditbonus.toPlainText().toInt());
		Logic_->SetCredits(textEditcredits.toPlainText().toInt(),false);
		Logic_->SetTotalBet(textEdittotalbet.toPlainText().toInt());
		if (checkbox->checkState()==Qt::Unchecked)
			enablesound = false;
		else
			enablesound = true;
		std::vector<std::string> vecdrum;
		vecdrum.clear();
		if (checkbox1->checkState() == Qt::Checked)
			vecdrum.push_back("auto1");
		if (checkbox2->checkState() == Qt::Checked)
			vecdrum.push_back("auto2");
		if (checkbox3->checkState() == Qt::Checked)
			vecdrum.push_back("auto3");
		if (checkbox4->checkState() == Qt::Checked)
			vecdrum.push_back("auto4");
		if (checkbox5->checkState() == Qt::Checked)
			vecdrum.push_back("auto5");
		if (checkboxwild->checkState() == Qt::Checked)
			vecdrum.push_back("wild");
		if (checkboxbonus->checkState() == Qt::Checked)
			vecdrum.push_back("bonus");
		Logic_->SetDrum(vecdrum);
		});
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
void MyWidget::newAPI()
{
	//f = QOpenGLContext::currentContext()->extraFunctions();
}
void MyWidget::newShow()
{
	Scene1_->ShowDrum(f, shaderProgram);
	Scene1_->ShowBorder(f, shaderProgram);
}
void MyWidget::SetDisableBonusButton()
{

	m_button[5]->setEnabled(false);
	m_button[6]->setEnabled(false);
	m_button[7]->setEnabled(false);
	m_button[8]->setEnabled(false);
	m_button[9]->setEnabled(false);
}

void MyWidget::SetEnableBonusButton() 
{

	m_button[5]->setEnabled(true);
	m_button[6]->setEnabled(true);
	m_button[7]->setEnabled(true);
	m_button[8]->setEnabled(true);
	m_button[9]->setEnabled(true);
}
void MyWidget::SetDisableButton()
{

	m_button[0]->setEnabled(false);
	m_button[1]->setEnabled(false);
	m_button[2]->setEnabled(false);
	m_button[3]->setEnabled(false);
	m_button[4]->setEnabled(false);
	m_button[2]->removeEventFilter(this);
}

void MyWidget::SetEnableButton()
{

	m_button[0]->setEnabled(true);
	m_button[1]->setEnabled(true);
	m_button[2]->setEnabled(true);
	m_button[3]->setEnabled(true);
	m_button[4]->setEnabled(true);
	m_button[2]->installEventFilter(this);
}
void MyWidget::paintGL() // рисование
{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка экрана
		//glEnable(GL_DEPTH_TEST);
		newShow();
			/*
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
		glEnable(GL_TEXTURE_2D);
		int countdrums = 5;
		int counttextureondrums = 6;
		if (!loading)
		{
			SetShowHideButtons(bonus);
			if (bonus || wait)
			{
				Sound_->Pause(0);
				Sound_->Play(7);
				if ((Logic_->GetWin() > 0 && F[5]))
				{
					F[5] = false;
					bonus = false;
					Logic_->SetCredits(Logic_->GetCredits() + Logic_->GetWin(), online);
					Logic_->SetWin(0.0f);
					Sound_->Play(4);
					Sound_->Pause(7);
				}
				for (int i = 6; i < 10; i++)
				{
					if (F[i] && !wait)
					{
						wait = true;
						tmpcounter = 0;
						number = i;
						SetDisableBonusButton();
						break;
					}
				}
				glDisable(GL_DEPTH_TEST);
				Scene2_->ShowBackGround(F, Logic_->GetRandom(), Logic_->GetCredits(), Logic_->GetWin(), Logic_->GetTotalBet());
				glEnable(GL_DEPTH_TEST);
				if (wait)
				{
					if (tmpcounter > 100)
					{
						F[number] = false;
						wait = false;
						for (int i = number; i < number + 1; i++)
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
								Sound_->Pause(7);
							}
							else
							{
								Logic_->SetRandom();
							}
						}
						SetEnableBonusButton();
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
					SetEnableButton();
				}
				else
				{
					for (int i = 0; i < Scene1_->CountDrum; i++)
						if (Scene1_->changedrum[i])
							Logic_->SetDrum(i);

					if ((Scene1_->rotate[0] < 1800.0f) && (Scene1_->rotate[0] >0.0f)&& (Scene1_->rotate[0] != 360.0f))
						SetDisableButton();
				}
				Scene1_->ShowButtons();
				Scene1_->ShowNumbersAndWords(Logic_->GetCredits(), Logic_->GetWin(), Logic_->GetTotalBet());
				Scene1_->ShowBorder();
				if (showline)
				{
					if (Logic_->CheckWin())
						Sound_->Play(3);
					glDisable(GL_DEPTH_TEST);
					//Scene1_->ShowLine(Logic_->firstline, Logic_->secondline, Logic_->thirdline);
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
		if(!F[0] && !bonus)
			Sound_->Play(0);
		if (!enablesound)
			Sound_->StopAll();
		//glFlush();
		*/
}
#endif