#include <GL/freeglut.h>
#include <math.h>

void drawCube3d(float size) {
    float halfSize = size / 2.0f;

    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f( halfSize, halfSize, -halfSize);
      glVertex3f(-halfSize, halfSize, -halfSize);
      glVertex3f(-halfSize, halfSize,  halfSize);
      glVertex3f( halfSize, halfSize,  halfSize);
 
      // Bottom face (y = -1.0f)
      glColor3f(1.0f, 0.5f, 0.0f);     // Orange
      glVertex3f( halfSize, -halfSize,  halfSize);
      glVertex3f(-halfSize, -halfSize,  halfSize);
      glVertex3f(-halfSize, -halfSize, -halfSize);
      glVertex3f( halfSize, -halfSize, -halfSize);
 
      // Front face  (z = 1.0f)
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( halfSize,  halfSize, halfSize);
      glVertex3f(-halfSize,  halfSize, halfSize);
      glVertex3f(-halfSize, -halfSize, halfSize);
      glVertex3f( halfSize, -halfSize, halfSize);
 
      // Back face (z = -1.0f)
      glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
      glVertex3f( halfSize, -halfSize, -halfSize);
      glVertex3f(-halfSize, -halfSize, -halfSize);
      glVertex3f(-halfSize,  halfSize, -halfSize);
      glVertex3f( halfSize,  halfSize, -halfSize);
 
      // Left face (x = -1.0f)
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(-halfSize,  halfSize,  halfSize);
      glVertex3f(-halfSize,  halfSize, -halfSize);
      glVertex3f(-halfSize, -halfSize, -halfSize);
      glVertex3f(-halfSize, -halfSize,  halfSize);
 
      // Right face (x = 1.0f)
      glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
      glVertex3f(halfSize,  halfSize, -halfSize);
      glVertex3f(halfSize,  halfSize,  halfSize);
      glVertex3f(halfSize, -halfSize,  halfSize);
      glVertex3f(halfSize, -halfSize, -halfSize);
    glEnd();  // End of drawing color-cube
}



void display() {
    glClearColor(1.0f,1.0f,1.0f,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (void *)"Exercise 7");

    glMatrixMode(GL_MODELVIEW);
    
    glTranslatef(25,25,0);
    glScalef(1.2,1.2,1.2);
    glRotatef(45,1.0,1.0,0.0);

    drawCube3d(20);

    glRotatef(-45,1.0,1.0,0.0);
    glScalef(1/1.2,1/1.2,1/1.2);
    glTranslatef(-25,-25,0);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc,argv);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("A sample 3D OpenGL application");
    glMatrixMode(GL_PROJECTION);
    glOrtho(-5,105,-5,105, -100, 100);
    glTranslatef(50,50,0);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}