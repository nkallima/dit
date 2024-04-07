#include <GL/freeglut.h>

void display() {
    glClearColor(1.0f,1.0f,1.0f,0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a black line
    glColor3f(0.0f,1.0f,0.0f); 
    glLineWidth(2); 
    glLineStipple(2,0x00FF); 
    glBegin(GL_LINE_STRIP); 
        glVertex2i(10,0); 
        glVertex2i(100,90); 
    glEnd();

    // Draw a red point in the screen
    glColor3f(1,0,0);
    glPointSize(8); // point size
    glBegin(GL_POINTS);
    glVertex2i(50,50);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc,argv);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("A sample 2D OpenGL application");
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,100,0,100);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}