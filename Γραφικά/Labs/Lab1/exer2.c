#include <GL/freeglut.h>

void display() {
    glClearColor(1.0f,1.0f,1.0f,0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a black vertical line
    glColor3f(0.0f,0.0f,0.0f); 
    glLineWidth(2); // size of the line
    glLineStipple(0,0x00FF); 
    glBegin(GL_LINES); 
        glVertex2i(50,0);
        glVertex2i(50,100);
    glEnd();

    // Draw a black horizontal line
    glColor3f(0.0f,0.0f,0.0f);
    glLineWidth(2); // size of the line
    glLineStipple(0,0x00FF);
    glBegin(GL_LINES); 
        glVertex2i(0,50);
        glVertex2i(100,50);
    glEnd(); 

    // Draw a string with black Roman fonts
    glColor3f(0.0f,0.0f,0.0f);
    glRasterPos2f(75, 75);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (void *)"Hello world");

    // Draw two red points in the screen
    glColor3f(1,0,0);
    glPointSize(8); // point size
    glBegin(GL_POINTS);
    glVertex2i(75,75);
    glVertex2i(50,50);
    glEnd();

    // Draw a dashed line
    glEnable(GL_LINE_STIPPLE);
    glColor3f(1,0,1); 
    glLineWidth(2); 
    glLineStipple(2,0x00FF); 
    glBegin(GL_LINE_STRIP); 
        glVertex2i(10,0); 
        glVertex2i(100,90); 
    glEnd();
    glDisable(GL_LINE_STIPPLE);

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
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}