#include <GL/freeglut.h>


void display() {
    glClearColor(1.0f,1.0f,1.0f,0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a black vertical line
    glColor3f(0.0f,0.0f,0.0f); 
    glLineWidth(2); // size of the line
    glBegin(GL_LINES); 
        glVertex2i(-50,0);
        glVertex2i(50,0);
    glEnd();

    // Draw a black horizontal line
    glColor3f(0.0f,0.0f,0.0f);
    glLineWidth(2); // size of the line
    glBegin(GL_LINES); 
        glVertex2i(0,-50);
        glVertex2i(0,50);
    glEnd();

    // Draw a string with black Roman fonts
    glColor3f(0.0f,0.0f,0.0f);
    glRasterPos2f(-50, 50);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (void *)"Exercise 3");

    // Draw an empty blue cube
    glColor3f(0.0f,0.0f,1.0f); 
    glLineWidth(2); // size of the line
    glBegin(GL_LINES); 
        glVertex2i(-20,-20);
        glVertex2i(20,-20);
		glVertex2i(20,-20);
		glVertex2i(20,20);
		glVertex2i(20,20);
        glVertex2i(-20,20);
		glVertex2i(-20,20);
	    glVertex2i(-20,-20);
    glEnd();

	glMatrixMode(GL_MODELVIEW);
	glTranslatef(25,25,0);
    // Draw a green cube
    glColor3f(0,1,0); 
    glBegin(GL_POLYGON);
        glVertex2i(-15,-15);
        glVertex2i(15,-15);
		glVertex2i(15,15);
		glVertex2i(-15,15);
    glEnd();
	glTranslatef(-25,-25,0);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc,argv);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("A sample 2D OpenGL application");
	glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-5,105,-5,105);
	glTranslatef(50, 50, 0);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}