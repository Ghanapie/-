#include"ListTemplate.h"
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<GL/glut.h>

//������ ����ü
struct coord {
	int x;
	int y;
	coord(int x, int y) { this->x = x, this->y = y; }
};

//��ǥ�� ���� ����Ʈ
List<coord> list;

GLfloat random[3] = { 1,1,0};	//���� RGB
GLfloat spin = 0;	//ȸ�� Ȯ��

int rotate = 0;	//ȸ�� ����

float reshapeX, reshapeY;	//��ũ�������� ����
float angle = 0;	//ȸ�� �ӵ�


					//��ũ�� ������ ����ȭ
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

	//�� �� �������� ������ ����
	glColor3f(random[0], random[1], random[2]);
	glPointSize(4);

	//ù��° �ﰢ��
	glBegin(GL_TRIANGLES);
	{
		glVertex2f(0, triangleLength / sqrt(3));
		glVertex2f(-triangleLength / 2, -triangleLength / (2 * sqrt(3)));
		glVertex2f(triangleLength / 2, -triangleLength / (2 * sqrt(3)));
	}
	glEnd();

	//�ι�° �ﰢ��
	glBegin(GL_TRIANGLES);
	{
		glVertex2f(-triangleLength / 2, triangleLength / (2 * sqrt(3)));
		glVertex2f(0, -triangleLength / sqrt(3));
		glVertex2f(triangleLength / 2, triangleLength / (2 * sqrt(3)));
	}
	glEnd();
}

//���콺 �̺�Ʈ
void mouseProcess(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//matrix�� Ŭ���� ������ ��ǥ �Է�
		addNode(&list, createNode(coord(x, reshapeY - y)));
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//rotate�� 1�̸� �ݽð����, -1�̸� �ð�������� ���� ����
		printf("Right mouse button\n");
		rotate = (rotate == 1) ? -1 : 1;
	}

	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		printf("Middle mouse button\n");
		//���� �� ����
		for (int i = 0; i<3; i++)
			random[i] = (float)rand() / RAND_MAX;
	}

}

void ideCallBack()
{
	//ȸ�� �ӵ� ����
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

	drawLines();	//�� �������� �����ϴ� �� �׸���

	//��ǥ ��� ���
	Node<coord> *current = list.Head;

	while (current != NULL)
	{
		glPushMatrix();
		{
			glTranslated(current->data.x, current->data.y, 0);	//��ǥ �̵�
			glRotatef(angle * 3, 0, 0, 1);				//�� ȸ��
			glScalef(2, 2, 1);							//�� ũ�� ����
			drawStars(25);								//�� �׸���
		}
		glPopMatrix();

		current = current->NextNode;	//���� ���� ����
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