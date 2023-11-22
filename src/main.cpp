/*
 vinyl player
 */


#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

// rgba(13,32,36,255)
float backplateColor[3] = { 13.0f / 255.0f, 32.0f / 255.0f, 36.0f / 255.0f };

// rgba(186,248,225,255)
// rgba(74, 255, 188, 255)
float frontplateColor[3] = { 74.0f / 255.0f, 255.0f / 255.0f, 188.0f / 255.0f };

// rgba(233, 247, 236, 255)

float backVolumeColor[3] = { 233.0f / 255.0f, 247.0f / 255.0f, 236.0f / 255.0f };

// rgba(11, 217, 55)
float volumeColor[3] = { 11.0f / 255.0f, 217.0f / 255.0f, 55.0f / 255.0f };

// black disc
float discColor[3] = { 0.0f, 0.0f, 0.0f };

// orange label
float labelColor[3] = { 1.0f, 0.5f, 0.0f };

// gray color
float grayColor[3] = { 0.5f, 0.5f, 0.5f };

// rgba(59, 53, 53)
float knobColor[3] = { 59.0f / 255.0f, 53.0f / 255.0f, 53.0f / 255.0f };

// Define the pie slice angle
const float pieSliceAngle = M_PI / 6; // 90 degrees in radians
float pieSliceRotation = 0.0f; // Rotation angle in degrees
float twistBarRotation = 0.0f; // Rotation angle in degrees

float volumeBarScale = 1.0f;


GLuint backplateVBO, frontplateVBO, discVBO, labelVBO, pieVBO, volumeBarVBO, backVolumeBarVBO, twistBarVBO, knobVBO,
    rodCircleVBO, rodPlateVBO, rodPlateTopVBO,  rodStick1VBO, rodStick2VBO, rodHeadVBO;
const int segments = 100;

bool forUpdate = false;

void createVBO(GLuint* vboId, GLfloat* vertices, int size)
{
    glGenBuffers(1, vboId);
    glBindBuffer(GL_ARRAY_BUFFER, *vboId);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void createCircle(float x, float y, float radius, GLfloat* circleVertices)
{
    for (int i = 0; i < segments; ++i) {
        float angle = 2.0f * M_PI * i / segments;
        circleVertices[3 * i] = x + radius * cos(angle);
        circleVertices[3 * i + 1] = y + radius * sin(angle);
        circleVertices[3 * i + 2] = 0.0f;
    }
}

void createPieSlice(float x, float y, float radius, float angle, GLfloat* circleVertices) {
    int count = 0;
    circleVertices[count++] = x;
    circleVertices[count++] = y;
    circleVertices[count++] = 0.0f;

    for (int i = 0; i <= segments; ++i) {
        float theta = angle * i / segments;
        circleVertices[count++] = x + radius * cos(theta);
        circleVertices[count++] = y + radius * sin(theta);
        circleVertices[count++] = 0.0f;
    }
}

void drawVBO(GLuint vboId, int size, float* color, GLenum mode = GL_POLYGON)
{
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glColor3fv(color);
    glDrawArrays(mode, 0, size);
}

void drawLineVBO(GLuint vboId, int size, float* color, int width)
{
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glColor3fv(color);
    glLineWidth(width);
    glDrawArrays(GL_LINES, 0, size);
}

void update(int value)
{
    pieSliceRotation += 2.0f; // Adjust rotation speed here
    if (pieSliceRotation >= 360.0f) {
        pieSliceRotation -= 360.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // Set up the next timer callback
}

void face()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);

    // draw backplate
    drawVBO(backplateVBO, 4, backplateColor);

    // draw frontplate
    drawVBO(frontplateVBO, 4, frontplateColor);

    // draw disc
    drawVBO(discVBO, segments, discColor, GL_TRIANGLE_FAN);

     // Draw pie slice
    glPushMatrix(); // Save current transformation
    glTranslatef(-0.15f, 0.0f, 0.0f); // Translate to origin
    glRotatef(pieSliceRotation, 0.0f, 0.0f, 1.0f); // Apply rotation
    glTranslatef(0.15f, 0.0f, 0.0f); // Translate back to original position

    drawVBO(pieVBO, segments + 2, grayColor, GL_TRIANGLE_FAN);
    glPopMatrix(); // Restore previous transformation

    // draw label
    drawVBO(labelVBO, segments, labelColor, GL_TRIANGLE_FAN);

    // draw knob
    drawVBO(knobVBO, segments, knobColor, GL_TRIANGLE_FAN);

    // draw volumeBarBack
    drawLineVBO(backVolumeBarVBO, 2, backVolumeColor, 10);

     // draw rod circle
    drawVBO(rodCircleVBO, segments, knobColor, GL_TRIANGLE_FAN);

    // draw rod plate
    drawVBO(rodPlateVBO, 4, backVolumeColor);

    // draw rod stick 1
    drawLineVBO(rodStick1VBO, 2, knobColor, 8);

    // draw rod stick 2
    drawLineVBO(rodStick2VBO, 2, knobColor, 8);

    // draw rod head
    drawVBO(rodHeadVBO, 4, backVolumeColor);

    // draw rod plate top
    drawVBO(rodPlateTopVBO, segments, knobColor, GL_TRIANGLE_FAN);
    
    // draw volumeBar
    glPushMatrix(); // Save current transformation
    glTranslatef(0.5f, -0.35f, 0.0f); // Translate to the bottom of the volume bar
    glScalef(1.0f, volumeBarScale, 1.0f); // Apply scaling
    glTranslatef(-0.5f, 0.35f, 0.0f); // Translate back

    drawLineVBO(volumeBarVBO, 2, volumeColor, 10);
    glPopMatrix(); // Restore previous transformation

    // Draw twistBar with rotation
    glPushMatrix(); // Save current transformation
    float twistBarCenterX = 0.35f;
    float twistBarCenterY = -0.24f;
    glTranslatef(twistBarCenterX, twistBarCenterY, 0.0f); // Translate to the center of the twistBar
    glRotatef(twistBarRotation, 0.0f, 0.0f, 1.0f); // Apply rotation
    // Translate back to original position
    glTranslatef(-twistBarCenterX, -twistBarCenterY, 0.0f);


    drawLineVBO(twistBarVBO, 2, grayColor, 7);
    glPopMatrix(); // Restore previous transformation
    

    glDisableClientState(GL_VERTEX_ARRAY);
    glutSwapBuffers();  // Swap the front and back buffers
}

void init()
{
    GLfloat backplateVertices[] = 
    {
        -0.62f, 0.46f, 0.0f,
        -0.62f, -0.46f, 0.0f,
        0.62f, -0.46f, 0.0f,
        0.62f, 0.46f, 0.0f
    };

    GLfloat frontplateVertices[] =
    {
        -0.58f, 0.42f, 0.0f,
        -0.58f, -0.42f, 0.0f,
        0.58f, -0.42f, 0.0f,
        0.58f, 0.42f, 0.0f
    };

    GLfloat backVolumeBarVertices[] =
    {
        0.5f, -0.35f, 0.0f,
        0.5f, -0.07f, 0.0f
    };

    GLfloat volumeBarVertices[] =
    {
        0.5f, -0.35f, 0.0f,
        0.5f, -0.23f, 0.0f
    };

    GLfloat twistBarVertices[] = 
    {
        0.35f, -0.2f, 0.0f,
        0.35f, -0.28f, 0.0f
    };

    GLfloat rodPlateVertices[] =
    {
        0.36f, 0.33f, 0.0f,
        0.44f, 0.33f, 0.0f,
        0.44f, 0.2f, 0.0f,
        0.36f, 0.2f, 0.0f
    };

    GLfloat rodStick1Vertices[] = 
    {
        0.4f, 0.2f, 0.0f,
        0.4f, 0.05f, 0.0f
    };

    GLfloat rodStick2Vertices[] =
    {
        0.4f, 0.05f, 0.0f,
        0.31f, -0.07f, 0.0f
    };

    GLfloat rodHeadVertices[] = 
    {
        0.2775f, -0.0656f, 0.0f,
        0.2986f, -0.0395f, 0.0f,
        0.3258f, -0.0962f, 0.0f,
        0.3441f, -0.0728f, 0.0f
    };

    GLfloat discVertices[3 * segments];
    GLfloat labelVertices[3 * segments];
    GLfloat knobVertices[3 * segments];
    GLfloat rodCircleVertices[3 * segments];
    GLfloat rodPlateTopVertices[3 * segments];

    GLfloat pieVertices[3 * (segments + 2)];
    createPieSlice(-0.15f, 0.0f, 0.35f, pieSliceAngle, pieVertices);
    
    
    createCircle(-0.15f, 0.0f, 0.35f, discVertices);
    createCircle(-0.15f, 0.0f, 0.1f, labelVertices);
    createCircle(0.35f, -0.24f, 0.05f, knobVertices);
    createCircle(0.4f, 0.3f, 0.08f, rodCircleVertices);
    createCircle(0.4f, 0.3f, 0.02f, rodPlateTopVertices);

    createVBO(&backplateVBO, backplateVertices, sizeof(backplateVertices));
    createVBO(&frontplateVBO, frontplateVertices, sizeof(frontplateVertices));
    createVBO(&discVBO, discVertices, sizeof(discVertices));
    createVBO(&labelVBO, labelVertices, sizeof(labelVertices));
    createVBO(&pieVBO, pieVertices, sizeof(pieVertices));
    createVBO(&backVolumeBarVBO, backVolumeBarVertices, sizeof(backVolumeBarVertices));
    createVBO(&volumeBarVBO, volumeBarVertices, sizeof(volumeBarVertices));
    createVBO(&twistBarVBO, twistBarVertices, sizeof(twistBarVertices));
    createVBO(&knobVBO, knobVertices, sizeof(knobVertices));
    createVBO(&rodCircleVBO, rodCircleVertices, sizeof(rodCircleVertices));
    createVBO(&rodPlateVBO, rodPlateVertices, sizeof(rodPlateVertices));
    createVBO(&rodStick1VBO, rodStick1Vertices, sizeof(rodStick1Vertices));
    createVBO(&rodStick2VBO, rodStick2Vertices, sizeof(rodStick2Vertices));
    createVBO(&rodHeadVBO, rodHeadVertices, sizeof(rodHeadVertices));
    createVBO(&rodPlateTopVBO, rodPlateTopVertices, sizeof(rodPlateTopVertices));
}

void onClick(int button, int state, int x, int y)
{
    if (state != GLUT_DOWN) return;

    if (button == GLUT_LEFT_BUTTON) 
    {
        twistBarRotation += 10.0f; // Rotate by 10 degrees on each click
        if (twistBarRotation >= 360.0f) 
        {
            twistBarRotation -= 360.0f; // Keep the angle in the range [0, 360]
        }
    }

    else if (button == 3) // Scroll up
    {
        volumeBarScale += 0.1f;
        volumeBarScale = max(0.1f, min(volumeBarScale, 2.0f)); // Clamp the scale value
    }
    else if (button == 4) // Scroll down
    {
        volumeBarScale -= 0.1f;
        volumeBarScale = max(0.1f, min(volumeBarScale, 2.0f)); // Clamp the scale value
    }

    glutPostRedisplay(); // Request to redraw the window
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    float aspect = (float)width / (float)height;
    glOrtho(-aspect, aspect, -1, 1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void onKeyPress(unsigned char key, int x, int y)
{
    bool positionChanged = false;
    
    switch (key) 
    {
    case 27: exit(0); break;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("lab4 Babasa");
    glutDisplayFunc(face);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(onKeyPress);
    glutMouseFunc(onClick);
    glutTimerFunc(0, update, 0); // Start the timer

    // rgba(253,242,238,255) beige
    // rgba(242,90,41,255) orange
    glClearColor(242.0f / 255.0f, 90 / 255.0f, 41.0f / 255.0f, 1.0);

    GLenum err = glewInit();
    glutFullScreen();

    if (err == GLEW_OK)
    {
        init();
        glutMainLoop();
    }
}