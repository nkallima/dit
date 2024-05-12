#include <GL/freeglut.h>
#include <math.h>

#define PI 3.1415926

void drawSimplePolygon(int n, float width) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; ++i) {
        float theta = 2.0 * PI * i / n; // Calculate angle for each vertex
        float x = cos(theta) * width; // Calculate x-coordinate
        float y = sin(theta) * width; // Calculate y-coordinate
        glVertex2f(x, y); // Draw the vertex
    }
    glEnd();
}

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
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (void *)"Exercise 6");

    glColor3f(1.0f,0.5f,0.0f);
    glMatrixMode(GL_MODELVIEW);
    
    glTranslatef(25,25,0);
    drawSimplePolygon(5, 20);
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
    glTranslatef(50,50,0);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}