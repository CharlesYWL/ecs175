#include<gl/glut.h>
#include<cmath>
#include<iostream>
#include<Windows.h>
#include<string>
#include<vector>
using namespace std;
float *PixelBuffer;

void LineBres(int x1, int y1, int x2, int y2,int windowsize)
{
//	glViewport(0, 0, windowsize, windowsize);
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
//			glBegin(GL_POINTS);
//			glVertex2f((cury-0.5*windowsize)/(0.5*windowsize), (curx-0.5*windowsize)/(0.5*windowsize));
			glDrawPixels(cury, curx, GL_RGB, GL_FLOAT, PixelBuffer);
		}
		else
		{
//			glBegin(GL_POINTS);
//			glVertex2f((curx-0.5*windowsize)/(0.5*windowsize), (cury-0.5*windowsize)/(0.5*windowsize));
			glDrawPixels(curx, cury, GL_RGB, GL_FLOAT, PixelBuffer);
		}
		curx += tx;
	}
	glutSwapBuffers();
}

void drawString(const char* str) 
{

	if (str && strlen(str)) {
		while (*str) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *str);
			str++;
		}
	}
	
}

void showCase()
{
//	glViewport(720, 0, 720, 720);
//	drawString("Hello world!I'm Weili");
//	glEnd();
//	glDrawPixels(200, 200, GL_RGB, GL_FLOAT, PixelBuffer);
	return;
} //show the words


void DrawPolygon(int NumV, vector<int> vertexs)
{
	if (2 * NumV != vertexs.size())
	{
		cerr << "Wrong Num of Vertexs Entered" << endl;
		return;
	}
//	glViewport(0, 0, 720, 720);
	int i, j;
	for ( i = 0, j = 1; j < 2*NumV-1; i +=2,j+=2)
	{
		LineBres(vertexs[i], vertexs[j], vertexs[i + 2], vertexs[j + 2], 720); //720 as defult resolution
	}
	LineBres(vertexs[0], vertexs[1], vertexs[i], vertexs[j], 720);
	return;

}

void renderWindow(void)
{
	glClear(GL_COLOR_BUFFER_BIT);                           //black back
	glLoadIdentity();
	glColor3f(1, 0, 0);                                       //RGB, red line
	glViewport(0, 0, 720, 720);
	showCase();
	LineBres(0,0, 720,720,720);
//	glViewport(720, 0, 720, 720);//last two are height and wid not coordiniation
	vector<int> array = { 0, 0, 360, 720, 720, 0 };
//	DrawPolygon(3, array);        
	glEnd();
	glFlush();                                             
}


int main(int argc, char *argv[])                           
{
	PixelBuffer = new float[720 * 720 * 3];
	glutInit(&argc, argv);                                  
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);  
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(720, 720);
	glutCreateWindow("DrawSystem");
	glutDisplayFunc(&renderWindow);
	glutMainLoop();
	return 0;
}