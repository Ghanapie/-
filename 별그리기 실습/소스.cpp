#include"ListTemplate.h"
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<GL/glut.h>

//데이터 구조체
struct coord {
	int x;
	int y;
	coord(int x, int y) { this->x = x, this->y = y; }
};

//좌표를 담을 리스트
List<coord> list;

GLfloat random[3] = { 1,1,0};	//랜덤 RGB
GLfloat spin = 0;	//회전 확인

int rotate = 0;	//회전 방향

float reshapeX, reshapeY;	//스크린사이즈 조정
float angle = 0;	//회전 속도


					//스크린 사이즈 동기화
void reShape(int w, int h)
{
	reshapeX = w;
	reshapeY = h;
}

void drawLines()
{
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(4);

	glBegin(GL_LINE_STRIP);
	{
		Node<coord> *current = list.Head;

		while (current != NULL)
		{
			glVertex2f(current->data.x, current->data.y);
			current = current->NextNode;
		}
	}
	glEnd();
}

void drawStars(int triangleLength)
{

	//별 색 랜덤으로 나오게 설정
	glColor3f(random[0], random[1], random[2]);
	glPointSize(4);

	//첫번째 삼각형
	glBegin(GL_TRIANGLES);
	{
		glVertex2f(0, triangleLength / sqrt(3));
		glVertex2f(-triangleLength / 2, -triangleLength / (2 * sqrt(3)));
		glVertex2f(triangleLength / 2, -triangleLength / (2 * sqrt(3)));
	}
	glEnd();

	//두번째 삼각형
	glBegin(GL_TRIANGLES);
	{
		glVertex2f(-triangleLength / 2, triangleLength / (2 * sqrt(3)));
		glVertex2f(0, -triangleLength / sqrt(3));
		glVertex2f(triangleLength / 2, triangleLength / (2 * sqrt(3)));
	}
	glEnd();
}

//마우스 이벤트
void mouseProcess(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//matrix에 클릭시 나오는 좌표 입력
		addNode(&list, createNode(coord(x, reshapeY - y)));
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//rotate가 1이면 반시계방향, -1이면 시계방향으로 돌게 설정
		printf("Right mouse button\n");
		rotate = (rotate == 1) ? -1 : 1;
	}

	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		printf("Middle mouse button\n");
		//랜덤 수 지정
		for (int i = 0; i<3; i++)
			random[i] = (float)rand() / RAND_MAX;
	}

}

void ideCallBack()
{
	//회전 속도 고정
	angle += rotate * 0.75;
	glutPostRedisplay();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glViewport(0, 0, 500, 500);

	drawLines();	//별 중점들을 연결하는 선 그리기

	//좌표 노드 헤더
	Node<coord> *current = list.Head;

	while (current != NULL)
	{
		glPushMatrix();
		{
			glTranslated(current->data.x, current->data.y, 0);	//좌표 이동
			glRotatef(angle * 3, 0, 0, 1);				//별 회전
			glScalef(2, 2, 1);							//별 크기 조정
			drawStars(25);								//별 그리기
		}
		glPopMatrix();

		current = current->NextNode;	//다음 노드로 지정
	}
	glutSwapBuffers();
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	list.Head = NULL;
	srand(time(NULL));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(150, 150);
	glutCreateWindow("Stars Rotated");

	glutDisplayFunc(display);
	glutMouseFunc(mouseProcess);
	glutIdleFunc(ideCallBack);
	glutReshapeFunc(reShape);
	glutMainLoop();

	return 0;
}