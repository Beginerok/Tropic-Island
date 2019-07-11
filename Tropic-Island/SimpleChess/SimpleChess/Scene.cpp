#include "Scene.h"



Scene::Scene()
{
	vec = new std::vector<Chest>();
}
void Scene::Chest_(float x1, float y1, float x2, float y2)
{
	glBegin(GL_LINES);
	glVertex2d(x1, y1);
	glVertex2d(x2, y2);

	glVertex2d(x1, y2);
	glVertex2d(x2, y1);
	glEnd();
}
void Scene::ShowFigure()
{
	Chest_((*vec)[0].x1, (*vec)[0].y1, (*vec)[0].x2, (*vec)[0].y2);
	Chest_((*vec)[1].x1, (*vec)[1].y1, (*vec)[1].x2, (*vec)[1].y2);
	Chest_((*vec)[2].x1, (*vec)[2].y1, (*vec)[2].x2, (*vec)[2].y2);

	Chest_((*vec)[8].x1, (*vec)[8].y1, (*vec)[8].x2, (*vec)[8].y2);
	Chest_((*vec)[9].x1, (*vec)[9].y1, (*vec)[9].x2, (*vec)[9].y2);
	Chest_((*vec)[10].x1, (*vec)[10].y1, (*vec)[10].x2, (*vec)[10].y2);

	Chest_((*vec)[16].x1, (*vec)[16].y1, (*vec)[16].x2, (*vec)[16].y2);
	Chest_((*vec)[17].x1, (*vec)[17].y1, (*vec)[17].x2, (*vec)[17].y2);
	Chest_((*vec)[18].x1, (*vec)[18].y1, (*vec)[18].x2, (*vec)[18].y2);
	glColor3d(0.0f, 1.0f, 0.0f);

	Chest_((*vec)[45].x1, (*vec)[45].y1, (*vec)[45].x2, (*vec)[45].y2);
	Chest_((*vec)[46].x1, (*vec)[46].y1, (*vec)[46].x2, (*vec)[46].y2);
	Chest_((*vec)[47].x1, (*vec)[47].y1, (*vec)[47].x2, (*vec)[47].y2);

	Chest_((*vec)[53].x1, (*vec)[53].y1, (*vec)[53].x2, (*vec)[53].y2);
	Chest_((*vec)[54].x1, (*vec)[54].y1, (*vec)[54].x2, (*vec)[54].y2);
	Chest_((*vec)[55].x1, (*vec)[55].y1, (*vec)[55].x2, (*vec)[55].y2);

	Chest_((*vec)[61].x1, (*vec)[61].y1, (*vec)[61].x2, (*vec)[61].y2);
	Chest_((*vec)[62].x1, (*vec)[62].y1, (*vec)[62].x2, (*vec)[62].y2);
	Chest_((*vec)[63].x1, (*vec)[63].y1, (*vec)[63].x2, (*vec)[63].y2);

	glColor3d(1.0f, 0.0f, 0.0f);
}
void Scene::Initialize()
{
	//line 1
	tmp.x1 = -.8f;
	tmp.y1 = .8f;
	tmp.x2 = -.6f;
	tmp.y2 = .6f;
	vec->push_back(tmp);

	tmp.x1 = -.6f;
	tmp.y1 = .8f;
	tmp.x2 = -.4f;
	tmp.y2 = .6f;
	vec->push_back(tmp);

	tmp.x1 = -.4f;
	tmp.y1 = .8f;
	tmp.x2 = -.2f;
	tmp.y2 = .6f;
	vec->push_back(tmp);

	tmp.x1 = -.2f;
	tmp.y1 = .8f;
	tmp.x2 = .0f;
	tmp.y2 = .6f;
	vec->push_back(tmp);

	tmp.x1 = .0f;
	tmp.y1 = .8f;
	tmp.x2 = .2f;
	tmp.y2 = .6f;
	vec->push_back(tmp);

	tmp.x1 = .2f;
	tmp.y1 = .8f;
	tmp.x2 = .4f;
	tmp.y2 = .6f;
	vec->push_back(tmp);

	tmp.x1 = .4f;
	tmp.y1 = .8f;
	tmp.x2 = .6f;
	tmp.y2 = .6f;
	vec->push_back(tmp);

	tmp.x1 = .6f;
	tmp.y1 = .8f;
	tmp.x2 = .8f;
	tmp.y2 = .6f;
	vec->push_back(tmp);
	//line 2
	tmp.x1 = -.8f;
	tmp.y1 = .6f;
	tmp.x2 = -.6f;
	tmp.y2 = .4f;
	vec->push_back(tmp);

	tmp.x1 = -.6f;
	tmp.y1 = .6f;
	tmp.x2 = -.4f;
	tmp.y2 = .4f;
	vec->push_back(tmp);

	tmp.x1 = -.4f;
	tmp.y1 = .6f;
	tmp.x2 = -.2f;
	tmp.y2 = .4f;
	vec->push_back(tmp);

	tmp.x1 = -.2f;
	tmp.y1 = .6f;
	tmp.x2 = .0f;
	tmp.y2 = .4f;
	vec->push_back(tmp);

	tmp.x1 = .0f;
	tmp.y1 = .6f;
	tmp.x2 = .2f;
	tmp.y2 = .4f;
	vec->push_back(tmp);

	tmp.x1 = .2f;
	tmp.y1 = .6f;
	tmp.x2 = .4f;
	tmp.y2 = .4f;
	vec->push_back(tmp);

	tmp.x1 = .4f;
	tmp.y1 = .6f;
	tmp.x2 = .6f;
	tmp.y2 = .4f;
	vec->push_back(tmp);

	tmp.x1 = .6f;
	tmp.y1 = .6f;
	tmp.x2 = .8f;
	tmp.y2 = .4f;
	vec->push_back(tmp);
	//line 3

	tmp.x1 = -.8f;
	tmp.y1 = .4f;
	tmp.x2 = -.6f;
	tmp.y2 = .2f;
	vec->push_back(tmp);

	tmp.x1 = -.6f;
	tmp.y1 = .4f;
	tmp.x2 = -.4f;
	tmp.y2 = .2f;
	vec->push_back(tmp);

	tmp.x1 = -.4f;
	tmp.y1 = .4f;
	tmp.x2 = -.2f;
	tmp.y2 = .2f;
	vec->push_back(tmp);

	tmp.x1 = -.2f;
	tmp.y1 = .4f;
	tmp.x2 = .0f;
	tmp.y2 = .2f;
	vec->push_back(tmp);

	tmp.x1 = .0f;
	tmp.y1 = .4f;
	tmp.x2 = .2f;
	tmp.y2 = .2f;
	vec->push_back(tmp);

	tmp.x1 = .2f;
	tmp.y1 = .4f;
	tmp.x2 = .4f;
	tmp.y2 = .2f;
	vec->push_back(tmp);

	tmp.x1 = .4f;
	tmp.y1 = .4f;
	tmp.x2 = .6f;
	tmp.y2 = .2f;
	vec->push_back(tmp);

	tmp.x1 = .6f;
	tmp.y1 = .4f;
	tmp.x2 = .8f;
	tmp.y2 = .2f;
	vec->push_back(tmp);
	//line 4
	tmp.x1 = -.8f;
	tmp.y1 = .2f;
	tmp.x2 = -.6f;
	tmp.y2 = .0f;
	vec->push_back(tmp);

	tmp.x1 = -.6f;
	tmp.y1 = .2f;
	tmp.x2 = -.4f;
	tmp.y2 = .0f;
	vec->push_back(tmp);

	tmp.x1 = -.4f;
	tmp.y1 = .2f;
	tmp.x2 = -.2f;
	tmp.y2 = .0f;
	vec->push_back(tmp);

	tmp.x1 = -.2f;
	tmp.y1 = .2f;
	tmp.x2 = .0f;
	tmp.y2 = .0f;
	vec->push_back(tmp);

	tmp.x1 = .0f;
	tmp.y1 = .2f;
	tmp.x2 = .2f;
	tmp.y2 = .0f;
	vec->push_back(tmp);

	tmp.x1 = .2f;
	tmp.y1 = .2f;
	tmp.x2 = .4f;
	tmp.y2 = .0f;
	vec->push_back(tmp);

	tmp.x1 = .4f;
	tmp.y1 = .2f;
	tmp.x2 = .6f;
	tmp.y2 = .0f;
	vec->push_back(tmp);

	tmp.x1 = .6f;
	tmp.y1 = .2f;
	tmp.x2 = .8f;
	tmp.y2 = .0f;
	vec->push_back(tmp);
	//line 5
	tmp.x1 = -.8f;
	tmp.y1 = .0f;
	tmp.x2 = -.6f;
	tmp.y2 = -.2f;
	vec->push_back(tmp);

	tmp.x1 = -.6f;
	tmp.y1 = .0f;
	tmp.x2 = -.4f;
	tmp.y2 = -.2f;
	vec->push_back(tmp);

	tmp.x1 = -.4f;
	tmp.y1 = .0f;
	tmp.x2 = -.2f;
	tmp.y2 = -.2f;
	vec->push_back(tmp);

	tmp.x1 = -.2f;
	tmp.y1 = .0f;
	tmp.x2 = .0f;
	tmp.y2 = -.2f;
	vec->push_back(tmp);

	tmp.x1 = .0f;
	tmp.y1 = .0f;
	tmp.x2 = .2f;
	tmp.y2 = -.2f;
	vec->push_back(tmp);

	tmp.x1 = .2f;
	tmp.y1 = .0f;
	tmp.x2 = .4f;
	tmp.y2 = -.2f;
	vec->push_back(tmp);

	tmp.x1 = .4f;
	tmp.y1 = .0f;
	tmp.x2 = .6f;
	tmp.y2 = -.2f;
	vec->push_back(tmp);

	tmp.x1 = .6f;
	tmp.y1 = .0f;
	tmp.x2 = .8f;
	tmp.y2 = -.2f;
	vec->push_back(tmp);
	//line 6
	tmp.x1 = -.8f;
	tmp.y1 = -.2f;
	tmp.x2 = -.6f;
	tmp.y2 = -.4f;
	vec->push_back(tmp);

	tmp.x1 = -.6f;
	tmp.y1 = -.2f;
	tmp.x2 = -.4f;
	tmp.y2 = -.4f;
	vec->push_back(tmp);

	tmp.x1 = -.4f;
	tmp.y1 = -.2f;
	tmp.x2 = -.2f;
	tmp.y2 = -.4f;
	vec->push_back(tmp);

	tmp.x1 = -.2f;
	tmp.y1 = -.2f;
	tmp.x2 = .0f;
	tmp.y2 = -.4f;
	vec->push_back(tmp);

	tmp.x1 = .0f;
	tmp.y1 = -.2f;
	tmp.x2 = .2f;
	tmp.y2 = -.4f;
	vec->push_back(tmp);

	tmp.x1 = .2f;
	tmp.y1 = -.2f;
	tmp.x2 = .4f;
	tmp.y2 = -.4f;
	vec->push_back(tmp);

	tmp.x1 = .4f;
	tmp.y1 = -.2f;
	tmp.x2 = .6f;
	tmp.y2 = -.4f;
	vec->push_back(tmp);

	tmp.x1 = .6f;
	tmp.y1 = -.2f;
	tmp.x2 = .8f;
	tmp.y2 = -.4f;
	vec->push_back(tmp);
	//line 7
	tmp.x1 = -.8f;
	tmp.y1 = -.4f;
	tmp.x2 = -.6f;
	tmp.y2 = -.6f;
	vec->push_back(tmp);

	tmp.x1 = -.6f;
	tmp.y1 = -.4f;
	tmp.x2 = -.4f;
	tmp.y2 = -.6f;
	vec->push_back(tmp);

	tmp.x1 = -.4f;
	tmp.y1 = -.4f;
	tmp.x2 = -.2f;
	tmp.y2 = -.6f;
	vec->push_back(tmp);

	tmp.x1 = -.2f;
	tmp.y1 = -.4f;
	tmp.x2 = .0f;
	tmp.y2 = -.6f;
	vec->push_back(tmp);

	tmp.x1 = .0f;
	tmp.y1 = -.4f;
	tmp.x2 = .2f;
	tmp.y2 = -.6f;
	vec->push_back(tmp);

	tmp.x1 = .2f;
	tmp.y1 = -.4f;
	tmp.x2 = .4f;
	tmp.y2 = -.6f;
	vec->push_back(tmp);

	tmp.x1 = .4f;
	tmp.y1 = -.4f;
	tmp.x2 = .6f;
	tmp.y2 = -.6f;
	vec->push_back(tmp);

	tmp.x1 = .6f;
	tmp.y1 = -.4f;
	tmp.x2 = .8f;
	tmp.y2 = -.6f;
	vec->push_back(tmp);
	//line 8
	tmp.x1 = -.8f;
	tmp.y1 = -.6f;
	tmp.x2 = -.6f;
	tmp.y2 = -.8f;
	vec->push_back(tmp);

	tmp.x1 = -.6f;
	tmp.y1 = -.6f;
	tmp.x2 = -.4f;
	tmp.y2 = -.8f;
	vec->push_back(tmp);

	tmp.x1 = -.4f;
	tmp.y1 = -.6f;
	tmp.x2 = -.2f;
	tmp.y2 = -.8f;
	vec->push_back(tmp);

	tmp.x1 = -.2f;
	tmp.y1 = -.6f;
	tmp.x2 = .0f;
	tmp.y2 = -.8f;
	vec->push_back(tmp);

	tmp.x1 = .0f;
	tmp.y1 = -.6f;
	tmp.x2 = .2f;
	tmp.y2 = -.8f;
	vec->push_back(tmp);

	tmp.x1 = .2f;
	tmp.y1 = -.6f;
	tmp.x2 = .4f;
	tmp.y2 = -.8f;
	vec->push_back(tmp);

	tmp.x1 = .4f;
	tmp.y1 = -.6f;
	tmp.x2 = .6f;
	tmp.y2 = -.8f;
	vec->push_back(tmp);

	tmp.x1 = .6f;
	tmp.y1 = -.6f;
	tmp.x2 = .8f;
	tmp.y2 = -.8f;
	vec->push_back(tmp);

}
void Scene::Show()
{
	/*
			glBegin(GL_LINES);

			glVertex3d(-.8f, .8f, 0.0f);
			glVertex3d(-.8f, -.8f, 0.0f);

			glVertex3d(-.6f, .8f, 0.0f);
			glVertex3d(-.6f, -.8f, 0.0f);

			glVertex3d(-.4f, .8f, 0.0f);
			glVertex3d(-.4f, -.8f, 0.0f);

			glVertex3d(-.2f, .8f, 0.0f);
			glVertex3d(-.2f, -.8f, 0.0f);

			glVertex3d(0.0f, .8f, 0.0f);
			glVertex3d(0.0f, -.8f, 0.0f);

			glVertex3d(.8f, .8f, 0.0f);
			glVertex3d(.8f, -.8f, 0.0f);

			glVertex3d(.6f, .8f, 0.0f);
			glVertex3d(.6f, -.8f, 0.0f);

			glVertex3d(.4f, .8f, 0.0f);
			glVertex3d(.4f, -.8f, 0.0f);

			glVertex3d(.2f, .8f, 0.0f);
			glVertex3d(.2f, -.8f, 0.0f);

			///////////////////////
			glVertex3d(-.8f, -.8f, 0.0f);
			glVertex3d(.8f, -.8f, 0.0f);

			glVertex3d(-.8f, -.6f, 0.0f);
			glVertex3d(.8f, -.6f, 0.0f);

			glVertex3d(-.8f, -.4f, 0.0f);
			glVertex3d(.8f, -.4f, 0.0f);

			glVertex3d(-.8f, -.2f, 0.0f);
			glVertex3d(.8f, -.2f, 0.0f);

			glVertex3d(-.8f, .0f, 0.0f);
			glVertex3d(.8f, .0f, 0.0f);

			glVertex3d(-.8f, .2f, 0.0f);
			glVertex3d(.8f, .2f, 0.0f);

			glVertex3d(-.8f, .4f, 0.0f);
			glVertex3d(.8f, .4f, 0.0f);

			glVertex3d(-.8f, .6f, 0.0f);
			glVertex3d(.8f, .6f, 0.0f);

			glVertex3d(-.8f, .8f, 0.0f);
			glVertex3d(.8f, .8f, 0.0f);
			
			glEnd();
			*/
		//1lines	
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.8f, 0.8f);
		glVertex2d(-.6f, 0.8f);
		glVertex2d(-.6f, 0.8f);
		glVertex2d(-.6f, 0.6f);
		glVertex2d(-.6f, 0.6f);
		glVertex2d(-.8f, 0.6f);
		glEnd();
		//1
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.6f, 0.8f);
		glVertex2d(-.4f, 0.8f);
		glVertex2d(-.4f, 0.8f);
		glVertex2d(-.4f, 0.6f);
		glVertex2d(-.4f, 0.6f);
		glVertex2d(-.6f, 0.6f);
		glEnd();
		//2
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.4f, 0.8f);
		glVertex2d(-.2f, 0.8f);
		glVertex2d(-.2f, 0.8f);
		glVertex2d(-.2f, 0.6f);
		glVertex2d(-.2f, 0.6f);
		glVertex2d(-.4f, 0.6f);
		glEnd();
		//3
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.2f, 0.8f);
		glVertex2d(.0f, 0.8f);
		glVertex2d(.0f, 0.8f);
		glVertex2d(.0f, 0.6f);
		glVertex2d(.0f, 0.6f);
		glVertex2d(-.2f, 0.6f);
		glEnd();
		//4
		glBegin(GL_LINE_LOOP);
		glVertex2d(.0f, 0.8f);
		glVertex2d(.2f, 0.8f);
		glVertex2d(.2f, 0.8f);
		glVertex2d(.2f, 0.6f);
		glVertex2d(.2f, 0.6f);
		glVertex2d(.0f, 0.6f);
		glEnd();
		//5
		glBegin(GL_LINE_LOOP);
		glVertex2d(.2f, 0.8f);
		glVertex2d(.4f, 0.8f);
		glVertex2d(.4f, 0.8f);
		glVertex2d(.4f, 0.6f);
		glVertex2d(.4f, 0.6f);
		glVertex2d(.2f, 0.6f);
		glEnd();
		//6
		glBegin(GL_LINE_LOOP);
		glVertex2d(.4f, 0.8f);
		glVertex2d(.6f, 0.8f);
		glVertex2d(.6f, 0.8f);
		glVertex2d(.6f, 0.6f);
		glVertex2d(.6f, 0.6f);
		glVertex2d(.4f, 0.6f);
		glEnd();
		//7
		glBegin(GL_LINE_LOOP);
		glVertex2d(.6f, 0.8f);
		glVertex2d(.8f, 0.8f);
		glVertex2d(.8f, 0.8f);
		glVertex2d(.8f, 0.6f);
		glVertex2d(.8f, 0.6f);
		glVertex2d(.6f, 0.6f);
		glEnd();
		//8
		//////////2 lines
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.8f, 0.6f);
		glVertex2d(-.6f, 0.6f);
		glVertex2d(-.6f, 0.6f);
		glVertex2d(-.6f, 0.4f);
		glVertex2d(-.6f, 0.4f);
		glVertex2d(-.8f, 0.4f);
		glEnd();
		//1
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.6f, 0.6f);
		glVertex2d(-.4f, 0.6f);
		glVertex2d(-.4f, 0.6f);
		glVertex2d(-.4f, 0.4f);
		glVertex2d(-.4f, 0.4f);
		glVertex2d(-.6f, 0.4f);
		glEnd();
		//2
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.4f, 0.6f);
		glVertex2d(-.2f, 0.6f);
		glVertex2d(-.2f, 0.6f);
		glVertex2d(-.2f, 0.4f);
		glVertex2d(-.2f, 0.4f);
		glVertex2d(-.4f, 0.4f);
		glEnd();
		//3
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.2f, 0.6f);
		glVertex2d(.0f, 0.6f);
		glVertex2d(.0f, 0.6f);
		glVertex2d(.0f, 0.4f);
		glVertex2d(.0f, 0.4f);
		glVertex2d(-.2f, 0.4f);
		glEnd();
		//4
		glBegin(GL_LINE_LOOP);
		glVertex2d(.0f, 0.6f);
		glVertex2d(.2f, 0.6f);
		glVertex2d(.2f, 0.6f);
		glVertex2d(.2f, 0.4f);
		glVertex2d(.2f, 0.4f);
		glVertex2d(.0f, 0.4f);
		glEnd();
		//5
		glBegin(GL_LINE_LOOP);
		glVertex2d(.2f, 0.6f);
		glVertex2d(.4f, 0.6f);
		glVertex2d(.4f, 0.6f);
		glVertex2d(.4f, 0.4f);
		glVertex2d(.4f, 0.4f);
		glVertex2d(.2f, 0.4f);
		glEnd();
		//6
		glBegin(GL_LINE_LOOP);
		glVertex2d(.4f, 0.6f);
		glVertex2d(.6f, 0.6f);
		glVertex2d(.6f, 0.6f);
		glVertex2d(.6f, 0.4f);
		glVertex2d(.6f, 0.4f);
		glVertex2d(.4f, 0.4f);
		glEnd();
		//7
		glBegin(GL_LINE_LOOP);
		glVertex2d(.6f, 0.6f);
		glVertex2d(.8f, 0.6f);
		glVertex2d(.8f, 0.6f);
		glVertex2d(.8f, 0.4f);
		glVertex2d(.8f, 0.4f);
		glVertex2d(.6f, 0.4f);
		glEnd();
		//8
		//3line
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.8f, 0.4f);
		glVertex2d(-.6f, 0.4f);
		glVertex2d(-.6f, 0.4f);
		glVertex2d(-.6f, 0.2f);
		glVertex2d(-.6f, 0.2f);
		glVertex2d(-.8f, 0.2f);
		glEnd();
		//1
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.6f, 0.4f);
		glVertex2d(-.4f, 0.4f);
		glVertex2d(-.4f, 0.4f);
		glVertex2d(-.4f, 0.2f);
		glVertex2d(-.4f, 0.2f);
		glVertex2d(-.6f, 0.2f);
		glEnd();
		//2
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.4f, 0.4f);
		glVertex2d(-.2f, 0.4f);
		glVertex2d(-.2f, 0.4f);
		glVertex2d(-.2f, 0.2f);
		glVertex2d(-.2f, 0.2f);
		glVertex2d(-.4f, 0.2f);
		glEnd();
		//3
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.2f, 0.4f);
		glVertex2d(.0f, 0.4f);
		glVertex2d(.0f, 0.4f);
		glVertex2d(.0f, 0.2f);
		glVertex2d(.0f, 0.2f);
		glVertex2d(-.2f, 0.2f);
		glEnd();
		//4
		glBegin(GL_LINE_LOOP);
		glVertex2d(.0f, 0.4f);
		glVertex2d(.2f, 0.4f);
		glVertex2d(.2f, 0.4f);
		glVertex2d(.2f, 0.2f);
		glVertex2d(.2f, 0.2f);
		glVertex2d(.0f, 0.2f);
		glEnd();
		//5
		glBegin(GL_LINE_LOOP);
		glVertex2d(.2f, 0.4f);
		glVertex2d(.4f, 0.4f);
		glVertex2d(.4f, 0.4f);
		glVertex2d(.4f, 0.2f);
		glVertex2d(.4f, 0.2f);
		glVertex2d(.2f, 0.2f);
		glEnd();
		//6
		glBegin(GL_LINE_LOOP);
		glVertex2d(.4f, 0.4f);
		glVertex2d(.6f, 0.4f);
		glVertex2d(.6f, 0.4f);
		glVertex2d(.6f, 0.2f);
		glVertex2d(.6f, 0.2f);
		glVertex2d(.4f, 0.2f);
		glEnd();
		//7
		glBegin(GL_LINE_LOOP);
		glVertex2d(.6f, 0.4f);
		glVertex2d(.8f, 0.4f);
		glVertex2d(.8f, 0.4f);
		glVertex2d(.8f, 0.2f);
		glVertex2d(.8f, 0.2f);
		glVertex2d(.6f, 0.2f);
		glEnd();
		//8
		//4 line
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.8f, 0.2f);
		glVertex2d(-.6f, 0.2f);
		glVertex2d(-.6f, 0.2f);
		glVertex2d(-.6f, 0.0f);
		glVertex2d(-.6f, 0.0f);
		glVertex2d(-.8f, 0.0f);
		glEnd();
		//1
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.6f, 0.2f);
		glVertex2d(-.4f, 0.2f);
		glVertex2d(-.4f, 0.2f);
		glVertex2d(-.4f, 0.0f);
		glVertex2d(-.4f, 0.0f);
		glVertex2d(-.6f, 0.0f);
		glEnd();
		//2
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.4f, 0.2f);
		glVertex2d(-.2f, 0.2f);
		glVertex2d(-.2f, 0.2f);
		glVertex2d(-.2f, 0.0f);
		glVertex2d(-.2f, 0.0f);
		glVertex2d(-.4f, 0.0f);
		glEnd();
		//3
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.2f, 0.2f);
		glVertex2d(.0f, 0.2f);
		glVertex2d(.0f, 0.2f);
		glVertex2d(.0f, 0.0f);
		glVertex2d(.0f, 0.0f);
		glVertex2d(-.2f, 0.0f);
		glEnd();
		//4
		glBegin(GL_LINE_LOOP);
		glVertex2d(.0f, 0.2f);
		glVertex2d(.2f, 0.2f);
		glVertex2d(.2f, 0.2f);
		glVertex2d(.2f, 0.0f);
		glVertex2d(.2f, 0.0f);
		glVertex2d(.0f, 0.0f);
		glEnd();
		//5
		glBegin(GL_LINE_LOOP);
		glVertex2d(.2f, 0.2f);
		glVertex2d(.4f, 0.2f);
		glVertex2d(.4f, 0.2f);
		glVertex2d(.4f, 0.0f);
		glVertex2d(.4f, 0.0f);
		glVertex2d(.2f, 0.0f);
		glEnd();
		//6
		glBegin(GL_LINE_LOOP);
		glVertex2d(.4f, 0.2f);
		glVertex2d(.6f, 0.2f);
		glVertex2d(.6f, 0.2f);
		glVertex2d(.6f, 0.0f);
		glVertex2d(.6f, 0.0f);
		glVertex2d(.4f, 0.0f);
		glEnd();
		//7
		glBegin(GL_LINE_LOOP);
		glVertex2d(.6f, 0.2f);
		glVertex2d(.8f, 0.2f);
		glVertex2d(.8f, 0.2f);
		glVertex2d(.8f, 0.0f);
		glVertex2d(.8f, 0.0f);
		glVertex2d(.6f, 0.0f);
		glEnd();
		//8
		//5 line
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.8f, 0.0f);
		glVertex2d(-.6f, 0.0f);
		glVertex2d(-.6f, 0.0f);
		glVertex2d(-.6f, -0.2f);
		glVertex2d(-.6f, -0.2f);
		glVertex2d(-.8f, -0.2f);
		glEnd();
		//1
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.6f, 0.0f);
		glVertex2d(-.4f, 0.0f);
		glVertex2d(-.4f, 0.0f);
		glVertex2d(-.4f, -0.2f);
		glVertex2d(-.4f, -0.2f);
		glVertex2d(-.6f, -0.2f);
		glEnd();
		//2
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.4f, 0.0f);
		glVertex2d(-.2f, 0.0f);
		glVertex2d(-.2f, 0.0f);
		glVertex2d(-.2f, -0.2f);
		glVertex2d(-.2f, -0.2f);
		glVertex2d(-.4f, -0.2f);
		glEnd();
		//3
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.2f, 0.0f);
		glVertex2d(.0f, 0.0f);
		glVertex2d(.0f, 0.0f);
		glVertex2d(.0f, -0.2f);
		glVertex2d(.0f, -0.2f);
		glVertex2d(-.2f, -0.2f);
		glEnd();
		//4
		glBegin(GL_LINE_LOOP);
		glVertex2d(.0f, 0.0f);
		glVertex2d(.2f, 0.0f);
		glVertex2d(.2f, 0.0f);
		glVertex2d(.2f, -0.2f);
		glVertex2d(.2f, -0.2f);
		glVertex2d(.0f, -0.2f);
		glEnd();
		//5
		glBegin(GL_LINE_LOOP);
		glVertex2d(.2f, 0.0f);
		glVertex2d(.4f, 0.0f);
		glVertex2d(.4f, 0.0f);
		glVertex2d(.4f, -0.2f);
		glVertex2d(.4f, -0.2f);
		glVertex2d(.2f, -0.2f);
		glEnd();
		//6
		glBegin(GL_LINE_LOOP);
		glVertex2d(.4f, 0.0f);
		glVertex2d(.6f, 0.0f);
		glVertex2d(.6f, 0.0f);
		glVertex2d(.6f, -0.2f);
		glVertex2d(.6f, -0.2f);
		glVertex2d(.4f, -0.2f);
		glEnd();
		//7
		glBegin(GL_LINE_LOOP);
		glVertex2d(.6f, 0.0f);
		glVertex2d(.8f, 0.0f);
		glVertex2d(.8f, 0.0f);
		glVertex2d(.8f, -0.2f);
		glVertex2d(.8f, -0.2f);
		glVertex2d(.6f, -0.2f);
		glEnd();
		//8
		//6 line

		glBegin(GL_LINE_LOOP);
		glVertex2d(-.8f, -0.2f);
		glVertex2d(-.6f, -0.2f);
		glVertex2d(-.6f, -0.2f);
		glVertex2d(-.6f, -0.4f);
		glVertex2d(-.6f, -0.4f);
		glVertex2d(-.8f, -0.4f);
		glEnd();
		//1
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.6f, -0.2f);
		glVertex2d(-.4f, -0.2f);
		glVertex2d(-.4f, -0.2f);
		glVertex2d(-.4f, -0.4f);
		glVertex2d(-.4f, -0.4f);
		glVertex2d(-.6f, -0.4f);
		glEnd();
		//2
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.4f, -0.2f);
		glVertex2d(-.2f, -0.2f);
		glVertex2d(-.2f, -0.2f);
		glVertex2d(-.2f, -0.4f);
		glVertex2d(-.2f, -0.4f);
		glVertex2d(-.4f, -0.4f);
		glEnd();
		//3
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.2f, -0.2f);
		glVertex2d(.0f, -0.2f);
		glVertex2d(.0f, -0.2f);
		glVertex2d(.0f, -0.4f);
		glVertex2d(.0f, -0.4f);
		glVertex2d(-.2f, -0.4f);
		glEnd();
		//4
		glBegin(GL_LINE_LOOP);
		glVertex2d(.0f, -0.2f);
		glVertex2d(.2f, -0.2f);
		glVertex2d(.2f, -0.2f);
		glVertex2d(.2f, -0.4f);
		glVertex2d(.2f, -0.4f);
		glVertex2d(.0f, -0.4f);
		glEnd();
		//5
		glBegin(GL_LINE_LOOP);
		glVertex2d(.2f, -0.2f);
		glVertex2d(.4f, -0.2f);
		glVertex2d(.4f, -0.2f);
		glVertex2d(.4f, -0.4f);
		glVertex2d(.4f, -0.4f);
		glVertex2d(.2f, -0.4f);
		glEnd();
		//6
		glBegin(GL_LINE_LOOP);
		glVertex2d(.4f, -0.2f);
		glVertex2d(.6f, -0.2f);
		glVertex2d(.6f, -0.2f);
		glVertex2d(.6f, -0.4f);
		glVertex2d(.6f, -0.4f);
		glVertex2d(.4f, -0.4f);
		glEnd();
		//7
		glBegin(GL_LINE_LOOP);
		glVertex2d(.6f, -0.2f);
		glVertex2d(.8f, -0.2f);
		glVertex2d(.8f, -0.2f);
		glVertex2d(.8f, -0.4f);
		glVertex2d(.8f, -0.4f);
		glVertex2d(.6f, -0.4f);
		glEnd();
		//8
		//7 line
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.8f, -0.4f);
		glVertex2d(-.6f, -0.4f);
		glVertex2d(-.6f, -0.4f);
		glVertex2d(-.6f, -0.6f);
		glVertex2d(-.6f, -0.6f);
		glVertex2d(-.8f, -0.6f);
		glEnd();
		//1
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.6f, -0.4f);
		glVertex2d(-.4f, -0.4f);
		glVertex2d(-.4f, -0.4f);
		glVertex2d(-.4f, -0.6f);
		glVertex2d(-.4f, -0.6f);
		glVertex2d(-.6f, -0.6f);
		glEnd();
		//2
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.4f, -0.4f);
		glVertex2d(-.2f, -0.4f);
		glVertex2d(-.2f, -0.4f);
		glVertex2d(-.2f, -0.6f);
		glVertex2d(-.2f, -0.6f);
		glVertex2d(-.4f, -0.6f);
		glEnd();
		//3
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.2f, -0.4f);
		glVertex2d(.0f, -0.4f);
		glVertex2d(.0f, -0.4f);
		glVertex2d(.0f, -0.6f);
		glVertex2d(.0f, -0.6f);
		glVertex2d(-.2f, -0.6f);
		glEnd();
		//4
		glBegin(GL_LINE_LOOP);
		glVertex2d(.0f, -0.4f);
		glVertex2d(.2f, -0.4f);
		glVertex2d(.2f, -0.4f);
		glVertex2d(.2f, -0.6f);
		glVertex2d(.2f, -0.6f);
		glVertex2d(.0f, -0.6f);
		glEnd();
		//5
		glBegin(GL_LINE_LOOP);
		glVertex2d(.2f, -0.4f);
		glVertex2d(.4f, -0.4f);
		glVertex2d(.4f, -0.4f);
		glVertex2d(.4f, -0.6f);
		glVertex2d(.4f, -0.6f);
		glVertex2d(.2f, -0.6f);
		glEnd();
		//6
		glBegin(GL_LINE_LOOP);
		glVertex2d(.4f, -0.4f);
		glVertex2d(.6f, -0.4f);
		glVertex2d(.6f, -0.4f);
		glVertex2d(.6f, -0.6f);
		glVertex2d(.6f, -0.6f);
		glVertex2d(.4f, -0.6f);
		glEnd();
		//7
		glBegin(GL_LINE_LOOP);
		glVertex2d(.6f, -0.4f);
		glVertex2d(.8f, -0.4f);
		glVertex2d(.8f, -0.4f);
		glVertex2d(.8f, -0.6f);
		glVertex2d(.8f, -0.6f);
		glVertex2d(.6f, -0.6f);
		glEnd();
		//8
		//8 line
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.8f, -0.6f);
		glVertex2d(-.6f, -0.6f);
		glVertex2d(-.6f, -0.6f);
		glVertex2d(-.6f, -0.8f);
		glVertex2d(-.6f, -0.8f);
		glVertex2d(-.8f, -0.8f);
		glEnd();
		//1
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.6f, -0.6f);
		glVertex2d(-.4f, -0.6f);
		glVertex2d(-.4f, -0.6f);
		glVertex2d(-.4f, -0.8f);
		glVertex2d(-.4f, -0.8f);
		glVertex2d(-.6f, -0.8f);
		glEnd();
		//2
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.4f, -0.6f);
		glVertex2d(-.2f, -0.6f);
		glVertex2d(-.2f, -0.6f);
		glVertex2d(-.2f, -0.8f);
		glVertex2d(-.2f, -0.8f);
		glVertex2d(-.4f, -0.8f);
		glEnd();
		//3
		glBegin(GL_LINE_LOOP);
		glVertex2d(-.2f, -0.6f);
		glVertex2d(.0f, -0.6f);
		glVertex2d(.0f, -0.6f);
		glVertex2d(.0f, -0.8f);
		glVertex2d(.0f, -0.8f);
		glVertex2d(-.2f, -0.8f);
		glEnd();
		//4
		glBegin(GL_LINE_LOOP);
		glVertex2d(.0f, -0.6f);
		glVertex2d(.2f, -0.6f);
		glVertex2d(.2f, -0.6f);
		glVertex2d(.2f, -0.8f);
		glVertex2d(.2f, -0.8f);
		glVertex2d(.0f, -0.8f);
		glEnd();
		//5
		glBegin(GL_LINE_LOOP);
		glVertex2d(.2f, -0.6f);
		glVertex2d(.4f, -0.6f);
		glVertex2d(.4f, -0.6f);
		glVertex2d(.4f, -0.8f);
		glVertex2d(.4f, -0.8f);
		glVertex2d(.2f, -0.8f);
		glEnd();
		//6
		glBegin(GL_LINE_LOOP);
		glVertex2d(.4f, -0.6f);
		glVertex2d(.6f, -0.6f);
		glVertex2d(.6f, -0.6f);
		glVertex2d(.6f, -0.8f);
		glVertex2d(.6f, -0.8f);
		glVertex2d(.4f, -0.8f);
		glEnd();
		//7
		glBegin(GL_LINE_LOOP);
		glVertex2d(.6f, -0.6f);
		glVertex2d(.8f, -0.6f);
		glVertex2d(.8f, -0.6f);
		glVertex2d(.8f, -0.8f);
		glVertex2d(.8f, -0.8f);
		glVertex2d(.6f, -0.8f);
		glEnd();
		//8
}
Scene::~Scene()
{
	vec->clear();
}

