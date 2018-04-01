#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<GL/glut.h>

GLfloat random[3] = { 1.0 };	//���� RGB
GLfloat spin = 0;	//ȸ�� Ȯ��

					//������ǥ
int matrix_x[100] = { 0 };
int matrix_y[100] = { 0 };

//������ǥ �ε���
int index_x = 0;
int index_y = 0;

int rotate = 0;	//ȸ�� ����

float reshape_x, reshape_y;	//��ũ�������� ����
float angle = 0;	//ȸ�� �ӵ�


					//��ũ�� ������ ����ȭ
void reshape(int w, int h)
{
	reshape_x = w;
	reshape_y = h;
}

void drawLines()
{
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(4);

	glBegin(GL_LINE_STRIP);
	{
		for (int i = 0; i < index_x; i++)
			glVertex2f(matrix_x[i], matrix_y[i]);
	}
	glEnd();
}

void draw_stars(int tri_l)
{

	//�� �� �������� ������ ����
	glColor3f(random[0], random[1], random[2]);
	glPointSize(4);

	//ù��° �ﰢ��
	glBegin(GL_TRIANGLES);
	{
		glVertex2f(0, tri_l / sqrt(3));
		glVertex2f(-tri_l / 2, -tri_l / (2 * sqrt(3)));
		glVertex2f(tri_l / 2, -tri_l / (2 * sqrt(3)));
	}
	glEnd();

	//�ι�° �ﰢ��
	glBegin(GL_TRIANGLES);
	{
		glVertex2f(-tri_l / 2, tri_l / (2 * sqrt(3)));
		glVertex2f(0, -tri_l / sqrt(3));
		glVertex2f(tri_l / 2, tri_l / (2 * sqrt(3)));
	}
	glEnd();
}

//���콺 �̺�Ʈ
void mouseProcess(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//matrix�� Ŭ���� ������ ��ǥ �Է�
		matrix_x[index_x++] = x;
		matrix_y[index_y++] = reshape_y - y;
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
		for (int i = 0; i<3; i++)
			random[i] = (float)rand() / RAND_MAX;
	}

}

void ideCallBack()
{
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

	for (int i = 0; i < index_x; i++)
	{
		glPushMatrix();
		{
			glTranslated(matrix_x[i], matrix_y[i], 0);	//��ǥ �̵�
			glRotatef(angle * 3, 0, 0, 1);				//�� ȸ��
			glScalef(2, 2, 1);							//�� ũ�� ����
			draw_stars(25);								//�� �׸���
		}
		glPopMatrix();
	}
	glutSwapBuffers();
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
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
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}
