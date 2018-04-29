#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<bits/stdc++.h>
#include <windows.h>
#include <glut.h>
using namespace std;
#define pi (2*acos(0.0))

double cameraHeight;
double cameraAngle;
int drawgrid,flag;
int drawaxes;
double angle;

struct point
{
	double x,y,z;
};
point pos,v,nx,ny,m;
double mv;

void drawAxes()
{
	if(drawaxes==1)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);{
			glVertex3f( 100,0,0);
			glVertex3f(-100,0,0);

			glVertex3f(0,-100,0);
			glVertex3f(0, 100,0);

			glVertex3f(0,0, 100);
			glVertex3f(0,0,-100);
		}glEnd();
	}
}



void drawSquare(double a)
{
    glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINES);{
		glVertex3f( a, a,0);
		glVertex3f( a,-a,0);
	}glEnd();
	glBegin(GL_LINES);{
        glVertex3f(-a,a,0);
        glVertex3f(a,a,0);
	}glEnd();
	glBegin(GL_LINES);{
        glVertex3f(-a,-a,0);
        glVertex3f(a,-a,0);
	}glEnd();
	glBegin(GL_LINES);{
		glVertex3f(-a,-a,0);
		glVertex3f(-a, a,0);
	}glEnd();
}

void drawArrow()
{
    point d;
    d.x = 10*v.x;
    d.y = 10*v.y;
    d.z = 0;

    double alpha = atan2(d.y,d.x);

    glColor3f(1,0,0);
    glBegin(GL_TRIANGLES);
    {
        glVertex3f(pos.x+d.x,pos.y+d.y,0);
        glVertex3f((pos.x+d.x)+(6*cos(alpha+15)),(pos.y+d.y)+(6*sin(alpha+15)),0);
        glVertex3f((pos.x+d.x)+(6*cos(alpha-15)),(pos.y+d.y)+(6*sin(alpha-15)),0);
    }
    glEnd();

    glColor3f(0,0,1);
    glBegin(GL_LINES);
    {
        glVertex3f(pos.x,pos.y,0);
        glVertex3f(pos.x+d.x,pos.y+d.y,0);
    }

}


void drawSS()
{
    glPushMatrix();{
        //glTranslatef(pos.x,pos.y,0);
        drawArrow();
        //glutPostRedisplay();
    }
    glPopMatrix();
    drawSquare(100);

}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':
			drawgrid=1-drawgrid;
			break;

		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			cameraHeight -= 3.0;
			break;
		case GLUT_KEY_UP:		// up arrow key
			cameraHeight += 3.0;
			break;

		case GLUT_KEY_RIGHT:
			{
			    point px = v,py;
			    py.x = v.y;
			    py.y = -v.x;

                v.x = px.x*cos(-1) + py.x*sin(-1);
                v.y = px.y*cos(-1) + py.y*sin(-1);

                double r = sqrt(pow(v.x,2)+pow(v.y,2)+pow(v.z,2));
                v.x/=r;
                v.y/=r;

                break;
			}
		case GLUT_KEY_LEFT:
			{
                point px = v;
                point py;

                py.x = v.y;
                py.y = -v.x;

                v.x = px.x*cos(1) + py.x*sin(1);
                v.y = px.y*cos(1) + py.y*sin(1);

                double r = sqrt(pow(v.x,2)+pow(v.y,2)+pow(v.z,2));
                v.x/=r;
                v.y/=r;

                break;
			}

		case GLUT_KEY_PAGE_UP:
			break;
		case GLUT_KEY_PAGE_DOWN:
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				drawaxes=1-drawaxes;
			}
			break;

		case GLUT_RIGHT_BUTTON:
			//........
			break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}



void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(100,100,100,	0,0,0,	0,0,1);
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	gluLookAt(0,0,200,	0,0,0,	0,1,0);
	glMatrixMode(GL_MODELVIEW);

	//drawAxes();
	drawGrid();
    drawSS();
    //drawSquare(100);
	glutSwapBuffers();
}


void animate(){
	angle+=0.05;

	pos.x += v.x*0.035;
	pos.y += v.y*0.035;

	if(pos.x<=-100||pos.x>=100){
        mv = 2*(v.x*nx.x+v.y*nx.y+v.z*nx.z);

        m.x = nx.x*mv;
        m.y = nx.y*mv;

        v.x -= m.x;
        v.y -= m.y;

        double r = sqrt(pow(v.x,2)+pow(v.y,2));
        v.x/=r;
        v.y/=r;

        //if(pos.y<=-100||pos.y>=100) flag = 1;

	}

    if(pos.y<=-100||pos.y>=100){
        cout << pos.x << " " << pos.y << endl;
        //cout << "here";
        mv = 2*(v.x*ny.x+v.y*ny.y+v.z*ny.z);

        m.x = ny.x*mv;
        m.y = ny.y*mv;

        v.x -= m.x;
        v.y -= m.y;

        double r = sqrt(pow(v.x,2)+pow(v.y,2));
        v.x/=r;
        v.y/=r;


	}
	glutPostRedisplay();
}

void init(){
	//codes for initialization
	drawgrid=0;
	drawaxes=1;
	cameraHeight=150.0;
	cameraAngle=1.0;
	angle=0;
	flag = 0;

	pos.x = 1;
	pos.y = 1;
	pos.z = 0;

	v.x = 1;
	v.y = 1;
	v.z = 0;

	nx.x = 1;
	nx.y = 0;
	nx.z = 0;

	ny.x = 0;
	ny.y = 1;
	ny.z = 0;

	//clear the screen
	glClearColor(0,0,0,0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80,	1,	1,	1000.0);

}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
