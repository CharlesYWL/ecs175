#include<gl/glut.h>
#include<cmath>
#include<iostream>
using namespace std;

void LineBres(int x1, int y1, int x2, int y2,int windowsize)
{
	glViewport(0, 0, windowsize, windowsize);
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);

	int flag = 0;
	if (dx < dy)//for reverse X&Y under slope>1
	{
		flag = 1;
		swap(x1, x2);
		swap(y1, y2);
		swap(dx, dy);
	}
	int tx = (x2 - x1) > 0 ? 1 : -1;
	int ty = (y2 - y1) > 0 ? 1 : -1;
	int curx = x1;
	int cury = y1;
	int dS = 2 * dy / windowsize;
	int dT = 2 * (dy - dx) / windowsize;
	int d = dS - dx/windowsize;
	while (curx != x2)
	{
		if (d < 0)
			d += dS;
		else
		{
			cury += ty;
			d += dT;
		}

		if (flag)
		{
			glBegin(GL_POINTS);
			glVertex2f((cury-0.5*windowsize)/(0.5*windowsize), (curx-0.5*windowsize)/(0.5*windowsize));
		}
		else
		{
			glBegin(GL_POINTS);
			glVertex2f((curx-0.5*windowsize)/(0.5*windowsize), (cury-0.5*windowsize)/(0.5*windowsize));
		}
		curx += tx;
	}
}

void showCase()
{
	glViewport(720, 0, 1440, 720);
	cout << "hello world" << endl;
	return;
}

void renderWindow(void)
{
	glClear(GL_COLOR_BUFFER_BIT);                           //black back
	glColor3f(1, 0, 0);                                       //RGB, red line
	glPointSize(1.0);
//	glBegin(GL_POINTS);
//	glVertex2d(0.5, 0.5);
//	glBegin(GL_POINTS);
//	glVertex2d(0.0, 0.0);

	LineBres(0,0, 720,720,720);
	LineBres(0, 720, 720,0,720);
//	showCase();
	glEnd();                                                
	glFlush();                                             
}

void renderWindow1(void)
{
	glClear(GL_COLOR_BUFFER_BIT);                           //black back
	glColor3f(0, 0, 1);                                       //RGB, red line
	glPointSize(1.0);
	//	glBegin(GL_POINTS);
	//	glVertex2d(0.5, 0.5);
	//	glBegin(GL_POINTS);
	//	glVertex2d(0.0, 0.0);

	LineBres(0, 0, 720, 720, 720);
	//LineBres(0, 720, 720, 0, 720);
	//	showCase();
	glEnd();
	glFlush();
}

int main(int argc, char *argv[])                           
{
	glutInit(&argc, argv);                                  
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);           
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1440, 720);
	glutCreateWindow("DrawSystem");
	system("pause");
	glutDisplayFunc(&renderWindow);
	system("pause");
	glutDisplayFunc(&renderWindow1);
	glutMainLoop();
	return 0;
}