#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<bits/stdc++.h>

#include <windows.h>
#include <glut.h>
using namespace std;
#define pi (2*acos(0.0))

struct point
{
	double x,y,z;
};

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;
point pos,vec_u,vec_l,vec_r;
double a,r;


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


void drawGrid()
{
	int i;
	if(drawgrid==1)
	{
		glColor3f(0.6, 0.6, 0.6);	//grey
		glBegin(GL_LINES);{
			for(i=-8;i<=8;i++){

				if(i==0)
					continue;	//SKIP the MAIN axes

				//lines parallel to Y-axis
				glVertex3f(i*10, -90, 0);
				glVertex3f(i*10,  90, 0);

				//lines parallel to X-axis
				glVertex3f(-90, i*10, 0);
				glVertex3f( 90, i*10, 0);
			}
		}glEnd();
	}
}

void drawSquare(double a)
{
    //glColor3f(0.0,1.0,0.0);
	glBegin(GL_QUADS);{
		glVertex3f( a, a,a);
		glVertex3f( a,-a,a);
		glVertex3f(-a,-a,a);
		glVertex3f(-a, a,a);
	}glEnd();
}


void drawCircle(double radius,int segments)
{
    int i;
    struct point points[100];
    glColor3f(0.7,0.7,0.7);
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points
    for(i=0;i<segments;i++)
    {
        glBegin(GL_LINES);
        {
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}


void drawCylinder(double radius, double height, int segments)
{
    int i;
    double shade;
    struct point points[100];
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*(pi/2));
        points[i].y=radius*sin(((double)i/(double)segments)*(pi/2));
    }

    //draw segments using generated points
    for(i=0;i<segments;i++)
    {

        glBegin(GL_QUADS);
        {
			glVertex3f(points[i].x,points[i].y,-height/2);
			glVertex3f(points[i+1].x,points[i+1].y,-height/2);
			glVertex3f(points[i+1].x,points[i+1].y,height/2);
			glVertex3f(points[i].x,points[i].y,height/2);
        }
        glEnd();
    }
}




void drawSphere(double radius,int slices,int stacks)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*pi/2);
			points[i][j].y=r*sin(((double)j/(double)slices)*pi/2);
			points[i][j].z=h>0?h:-h;
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        //glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
        glColor3f(1,0,0);
		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			    //upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                //lower hemisphere
                /*glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);*/
			}glEnd();
		}
	}
}


void drawSS()
{
    glColor3f(1,1,1);
    drawSquare(a-r);

    glPushMatrix();{
        glTranslatef(0,0,-2*(a-r));
        drawSquare(a-r);
    }glPopMatrix();

    glPushMatrix();{
        //glRotatef(90,0,0,1);
        //glColor3f(0,0,1);
        glRotatef(90,1,0,0);
        drawSquare(a-r);
    }glPopMatrix();

    glPushMatrix();{
        //glColor3f(1,0,0);
        glRotatef(90,0,0,1);
        glRotatef(90,1,0,0);
        drawSquare(a-r);
    }glPopMatrix();

    glPushMatrix();{
        //glColor3f(1,1,1);
        glRotatef(180,0,0,1);
        glRotatef(90,1,0,0);
        drawSquare(a-r);
    }glPopMatrix();

    glPushMatrix();{
        glRotatef(270,0,0,1);
        glRotatef(90,1,0,0);
        drawSquare(a-r);
    }glPopMatrix();

    //8 1/8 spheres
    glPushMatrix(); {
			glRotatef(180, 0, 1, 0);
			glTranslatef(a-r, a-r, a-r);
			drawSphere(r, 20, 20);
    } glPopMatrix();

    glPushMatrix(); {
            glTranslatef(a-r, a-r, a-r);
            drawSphere(r, 20, 20);
    } glPopMatrix();

    glPushMatrix(); {
            glRotatef(90,0,0,1);
			glRotatef(180, 0, 1, 0);
			glTranslatef(a-r, a-r, a-r);
			drawSphere(r, 20, 20);
    } glPopMatrix();

    glPushMatrix(); {
            glRotatef(90,0,0,1);
            glTranslatef(a-r, a-r, a-r);
            drawSphere(r, 20, 20);
    } glPopMatrix();

    glPushMatrix(); {
            glRotatef(180,0,0,1);
			glRotatef(180, 0, 1, 0);
			glTranslatef(a-r, a-r, a-r);
			drawSphere(r, 20, 20);
    } glPopMatrix();

    glPushMatrix(); {
            glRotatef(180,0,0,1);
            glTranslatef(a-r, a-r, a-r);
            drawSphere(r, 20, 20);
    } glPopMatrix();

    glPushMatrix(); {
            glRotatef(270,0,0,1);
			glRotatef(180, 0, 1, 0);
			glTranslatef(a-r, a-r, a-r);
			drawSphere(r, 20, 20);
    } glPopMatrix();

    glPushMatrix(); {
            glRotatef(270,0,0,1);
            glTranslatef(a-r, a-r, a-r);
            drawSphere(r, 20, 20);
    } glPopMatrix();

    //cylinder
    glPushMatrix();{
        glColor3f(0,1,0);
        glTranslatef(a-r,a-r,0);
        drawCylinder(r,2*(a-r),20);
    }glPopMatrix();

    glPushMatrix();{
        glColor3f(0,1,0);
        glTranslatef(a-r,0,(a-r));
        glRotatef(90,1,0,0);
        drawCylinder(r,2*(a-r),20);
    }glPopMatrix();

    glPushMatrix();{
        glColor3f(0,1,0);
        glRotatef(180,0,1,0);
        glTranslatef(a-r,0,(a-r));
        glRotatef(90,1,0,0);
        drawCylinder(r,2*(a-r),20);
    }glPopMatrix();

    glPushMatrix();{
        glRotatef(90,0,0,1);
        glColor3f(0,1,0);
        glTranslatef(a-r,a-r,0);
        drawCylinder(r,2*(a-r),20);
    }glPopMatrix();

    glPushMatrix();{
        glColor3f(0,1,0);
        glRotatef(90,0,0,1);
        glTranslatef(a-r,0,(a-r));
        glRotatef(90,1,0,0);
        drawCylinder(r,2*(a-r),20);
    }glPopMatrix();

    glPushMatrix();{
        glColor3f(0,1,0);
        glRotatef(90,0,0,1);
        glRotatef(180,0,1,0);
        glTranslatef(a-r,0,(a-r));
        glRotatef(90,1,0,0);
        drawCylinder(r,2*(a-r),20);
    }glPopMatrix();

    glPushMatrix();{
        glRotatef(180,0,0,1);
        glColor3f(0,1,0);
        glTranslatef(a-r,a-r,0);
        drawCylinder(r,2*(a-r),20);
    }glPopMatrix();

    glPushMatrix();{
        glColor3f(0,1,0);
        glRotatef(180,0,0,1);
        glTranslatef(a-r,0,(a-r));
        glRotatef(90,1,0,0);
        drawCylinder(r,2*(a-r),20);
    }glPopMatrix();

    glPushMatrix();{
        glColor3f(0,1,0);
        glRotatef(180,0,0,1);
        glRotatef(180,0,1,0);
        glTranslatef(a-r,0,(a-r));
        glRotatef(90,1,0,0);
        drawCylinder(r,2*(a-r),20);
    }glPopMatrix();

    glPushMatrix();{
        glRotatef(270,0,0,1);
        glColor3f(0,1,0);
        glTranslatef(a-r,a-r,0);
        drawCylinder(r,2*(a-r),20);
    }glPopMatrix();

    glPushMatrix();{
        glColor3f(0,1,0);
        glRotatef(270,0,0,1);
        glTranslatef(a-r,0,(a-r));
        glRotatef(90,1,0,0);
        drawCylinder(r,2*(a-r),20);
    }glPopMatrix();

    glPushMatrix();{
        glColor3f(0,1,0);
        glRotatef(270,0,0,1);
        glRotatef(180,0,1,0);
        glTranslatef(a-r,0,(a-r));
        glRotatef(90,1,0,0);
        drawCylinder(r,2*(a-r),20);
    }glPopMatrix();

}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':
			{
			    point px = vec_l,py = vec_r;

                vec_l.x = px.x*cos(3) + py.x*sin(3);
                vec_l.y = px.y*cos(3) + py.y*sin(3);
                double r = sqrt(pow(vec_l.x,2)+pow(vec_l.y,2)+pow(vec_l.z,2));
                vec_l.x/=r;
                vec_l.y/=r;
                vec_l.z/=r;

                vec_r.x = py.x*cos(3) - px.x*sin(3);
                vec_r.y = py.y*cos(3) - px.y*sin(3);
                double r2 = sqrt(pow(vec_r.x,2)+pow(vec_r.y,2)+pow(vec_r.z,2));
                vec_r.x/=r2;
                vec_r.y/=r2;
                vec_r.z/=r2;

                break;
			}


        case '2':
            {
                point px = vec_l,py = vec_r;

                vec_l.x = px.x*cos(-3) + py.x*sin(-3);
                vec_l.y = px.y*cos(-3) + py.y*sin(-3);
                double r = sqrt(pow(vec_l.x,2)+pow(vec_l.y,2)+pow(vec_l.z,2));
                vec_l.x/=r;
                vec_l.y/=r;
                vec_l.z/=r;

                vec_r.x = py.x*cos(-3) - px.x*sin(-3);
                vec_r.y = py.y*cos(-3) - px.y*sin(-3);
                double r2 = sqrt(pow(vec_r.x,2)+pow(vec_r.y,2)+pow(vec_r.z,2));
                vec_r.x/=r2;
                vec_r.y/=r2;
                vec_r.z/=r2;

                break;
            }


        case '3':
            {
                point px = vec_l,py = vec_u;

                vec_l.x = px.x*cos(3) + py.x*sin(3);
                vec_l.y = px.y*cos(3) + py.y*sin(3);
                vec_l.z = px.z*cos(3) + py.z*sin(3);
                double r = sqrt(pow(vec_l.x,2)+pow(vec_l.y,2)+pow(vec_l.z,2));
                vec_l.x/=r;
                vec_l.y/=r;
                vec_l.z/=r;

                vec_u.x = py.x*cos(3) - px.x*sin(3);
                vec_u.y = py.y*cos(3) - px.y*sin(3);
                vec_u.z = py.z*cos(3) - px.z*sin(3);
                double r2 = sqrt(pow(vec_u.x,2)+pow(vec_u.y,2)+pow(vec_u.z,2));
                vec_u.x/=r2;
                vec_u.y/=r2;
                vec_u.z/=r2;

                break;
            }

        case '4':
            {
                point px = vec_l,py = vec_u;

                vec_l.x = px.x*cos(-3) + py.x*sin(-3);
                vec_l.y = px.y*cos(-3) + py.y*sin(-3);
                vec_l.z = px.z*cos(-3) + py.z*sin(-3);
                double r = sqrt(pow(vec_l.x,2)+pow(vec_l.y,2)+pow(vec_l.z,2));
                vec_l.x/=r;
                vec_l.y/=r;
                vec_l.z/=r;

                vec_u.x = py.x*cos(-3) - px.x*sin(-3);
                vec_u.y = py.y*cos(-3) - px.y*sin(-3);
                vec_u.z = py.z*cos(-3) - px.z*sin(-3);
                double r2 = sqrt(pow(vec_u.x,2)+pow(vec_u.y,2)+pow(vec_u.z,2));
                vec_u.x/=r2;
                vec_u.y/=r2;
                vec_u.z/=r2;
                break;
            }

        case '5':
            {
                point px = vec_u,py = vec_r;

                vec_u.x = px.x*cos(3) + py.x*sin(3);
                vec_u.y = px.y*cos(3) + py.y*sin(3);
                vec_u.z = px.z*cos(3) + py.z*sin(3);
                double r = sqrt(pow(vec_u.x,2)+pow(vec_u.y,2)+pow(vec_u.z,2));
                vec_u.x/=r;
                vec_u.y/=r;
                vec_u.z/=r;

                vec_r.x = py.x*cos(3) - px.x*sin(3);
                vec_r.y = py.y*cos(3) - px.y*sin(3);
                vec_r.z = py.z*cos(3) - px.z*sin(3);
                double r2 = sqrt(pow(vec_r.x,2)+pow(vec_r.y,2)+pow(vec_r.z,2));
                vec_r.x/=r2;
                vec_r.y/=r2;
                vec_r.z/=r2;

                break;
            }

        case '6':
            {
                point px = vec_u,py = vec_r;

                vec_u.x = px.x*cos(-3) + py.x*sin(-3);
                vec_u.y = px.y*cos(-3) + py.y*sin(-3);
                vec_u.z = px.z*cos(-3) + py.z*sin(-3);
                double r = sqrt(pow(vec_u.x,2)+pow(vec_u.y,2)+pow(vec_u.z,2));
                vec_u.x/=r;
                vec_u.y/=r;
                vec_u.z/=r;

                vec_r.x = py.x*cos(-3) - px.x*sin(-3);
                vec_r.y = py.y*cos(-3) - px.y*sin(-3);
                vec_r.z = py.z*cos(-3) - px.z*sin(-3);
                double r2 = sqrt(pow(vec_r.x,2)+pow(vec_r.y,2)+pow(vec_r.z,2));
                vec_r.x/=r2;
                vec_r.y/=r2;
                vec_r.z/=r2;

                break;
            }

	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			//cameraHeight -= 3.0;
			pos.x -= vec_l.x*2;
			pos.y -= vec_l.y*2;
			pos.z -= vec_l.z*2;
			break;
		case GLUT_KEY_UP:		// up arrow key
			//cameraHeight += 3.0;
			pos.x += vec_l.x*2;
			pos.y += vec_l.y*2;
			pos.z += vec_l.z*2;
			break;

		case GLUT_KEY_RIGHT:
			//cameraAngle += 0.03;
			pos.x += vec_r.x*2;
			pos.y += vec_r.y*2;
			pos.z += vec_r.z*2;
			break;
		case GLUT_KEY_LEFT:
			//cameraAngle -= 0.03;
			pos.x -= vec_r.x*2;
			pos.y -= vec_r.y*2;
			pos.z -= vec_r.z*2;
			break;

		case GLUT_KEY_PAGE_UP:
		    pos.x += vec_u.x*2;
			pos.y += vec_u.y*2;
			pos.z += vec_u.z*2;
			break;
		case GLUT_KEY_PAGE_DOWN:
		    pos.x -= vec_u.x*2;
			pos.y -= vec_u.y*2;
			pos.z -= vec_u.z*2;
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
		    r++;
			break;
		case GLUT_KEY_END:
		    r--;
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
	//gluLookAt(0,0,200,	0,0,0,	0,1,0);
	gluLookAt(pos.x,pos.y,pos.z, pos.x + vec_l.x, pos.y + vec_l.y, pos.z + vec_l.z, vec_u.x,vec_u.y,vec_u.z);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);

	drawAxes();
	drawGrid();

    //glColor3f(1,0,0);
    //drawSquare(10);

    drawSS();

    //drawCircle(30,24);

    //drawCone(20,50,24);

	//drawSphere(30,24,20);




	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){
	angle+=0.05;
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init(){
	//codes for initialization
	drawgrid=0;
	drawaxes=1;
	cameraHeight=150.0;
	cameraAngle=1.0;
	angle=0;

	pos.x = 100;
	pos.y = 100;
	pos.z = 0;

	vec_u.x = 0;
	vec_u.y = 0;
	vec_u.z = 1;

	vec_l.x = -1/sqrt(2);
	vec_l.y = -1/sqrt(2);
	vec_l.z = 0;

	vec_r.x = -1/sqrt(2);
	vec_r.y = 1/sqrt(2);
	vec_r.z = 0;

	a = 50;
	r = 10;

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
