#include <GL/glu.h>
#include "GL/glut.h"
#include <QGLWidget>
#include <cmath>
#include "SolidCubeWidget.h"
#include <QSlider>
#include <iostream>
#include <QKeyEvent>
#include <math.h>       /* sin cos tan */

// Body Scales
double HEAD_HEIGHT    = 1.5;
double ARM_LENGTH     = 3.0;
double SHOULDER_WIDTH = 3.0;
double HIP_WIDTH      = 2;
double HIP_HEIGHT     = -3.25;
double LEG_LENGTH     = 3.0;

double radian = 57.2958;
float  sliderValue = 0;

// Button Triggers
int    playerHead=0;
int    playerHeadRotation=0;
int    toggleAnimatePlayer=0;
int    toggleStressTest=0;
int    togglePositionLight=0;
double stressAngle=10;


// Setting up material properties
typedef struct materialStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;


static materialStruct brassMaterials = {
  { 0.33, 0.22, 0.03, 1.0},
  { 0.78, 0.57, 0.11, 1.0},
  { 0.99, 0.91, 0.81, 1.0},
  27.8
};

static materialStruct whiteShinyMaterials = {
  { 1.0, 1.0, 1.0, 1.0},
  { 1.0, 1.0, 1.0, 1.0},
  { 1.0, 1.0, 1.0, 1.0},
  100.0
};


SolidCubeWidget::SolidCubeWidget(QWidget *parent) // constructor
        : QGLWidget(parent),
        angle(0),
        imgGrass        ("./textures/GrassGreen.ppm"),
        imgLeaves       ("./textures/GrassGreen.ppm"),
        imgLogStump     ("./textures/DarkBrown.ppm"),
        imgLogStumpInner("./textures/LightBrown.ppm"),
        imgLogBark      ("./textures/logBark.ppm"),
        imgLogBark2     ("./textures/logBark2.ppm"),
        imgTentWall     ("./textures/CreamWhite.ppm"),
        imgSkinTone     ("./textures/SkinTone.ppm"),
        imgNoseTone     ("./textures/NoseTone.ppm"),
        imgPlaid        ("./textures/Plaid.ppm"),
        imgJeans        ("./textures/Jeans.ppm"),
        imgHead         ("./textures/face.ppm"),
        imgEarth        ("./textures/earth.ppm"),
        imgMoi          ("./textures/Moi.ppm"){
    phead         = gluNewQuadric();
    pshoulders    = gluNewQuadric();
    ptorso        = gluNewQuadric();
    pupperleft    = gluNewQuadric();
    plowerleft    = gluNewQuadric();
    pupperleftLeg = gluNewQuadric();
    plowerleftLeg = gluNewQuadric();
    pground       = gluNewQuadric();

    pTentWall      = gluNewQuadric();
    pLog           = gluNewQuadric();
    pLogStump      = gluNewQuadric();
    pLogStumpInner = gluNewQuadric();
    pLeaves        = gluNewQuadric();

    // Set the focus policy to allow for keyPressEvent to function
    setFocusPolicy(Qt::StrongFocus);
    buttonResetPlayer();    // Player start position
}


// called when OpenGL context is set up
void SolidCubeWidget::initializeGL(){
	// set the widget background colour
    glClear(GL_COLOR_BUFFER_BIT);
    float brightness = 0.0f;
	glClearColor((195.0f/255.0f)*brightness, (243.0f/255.0f)*brightness, (243.0f/255.0f)*brightness, 1.0f);
    glEnable(GL_TEXTURE_2D);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}


// model character body part
void SolidCubeWidget::modelHead(){
    glRotatef(90,0,1,0);
    glRotatef(-90,1,0,0);

    glBindTexture(GL_TEXTURE_2D, 0);
    if (playerHead==0){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgHead.Width(), imgHead.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, imgHead.imageField());
    }else if(playerHead==1){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgMoi.Width(), imgMoi.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, imgMoi.imageField());
    }else{
        glRotatef(25,0,1,0);
        glRotatef(playerHeadRotation,0,0,1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgEarth.Width(), imgEarth.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, imgEarth.imageField());
    }
    glColor3f(0.0,1.0,0.0);
    gluQuadricDrawStyle(phead, GLU_FILL);
    gluQuadricTexture(phead, true);
    gluQuadricNormals(phead, GLU_SMOOTH);

    gluSphere(phead,1.0,20,20);

    if (playerHead==0){// Nose

        glRotatef(-90,1,0,0);
        glTranslatef(0,0.2,-1.2);

        glBindTexture(GL_TEXTURE_2D, 0);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgNoseTone.Width(), imgNoseTone.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, imgNoseTone.imageField());
        glColor3f(0.0,1.0,0.0);
        gluQuadricDrawStyle(phead, GLU_FILL);
        gluQuadricTexture(phead, true);
        gluQuadricNormals(phead, GLU_SMOOTH);
        gluCylinder(phead,   0,0.2,   0.25,3,4);

    }
}

// model character body part
void SolidCubeWidget::modelShoulders(){
    glBindTexture(GL_TEXTURE_2D, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgPlaid.Width(), imgPlaid.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, imgPlaid.imageField());
    glColor3f(0.0,1.0,0.0);
    gluQuadricDrawStyle(pshoulders, GLU_FILL);
    gluQuadricTexture(pshoulders, true);
    gluQuadricNormals(pshoulders, GLU_SMOOTH);

    gluCylinder(pshoulders,0.5,0.5,3,   20,4);
    gluSphere(pshoulders,0.5,   20,20);
    glTranslatef(0,0,3);
    gluSphere(pshoulders,0.5,   20,20);

    glTranslatef(-0.5,-1.0,-1.5);
    glRotatef(90,0,1,0);
    GLfloat normals[][3] =  {{0., 0., 1.}, {0., 0., -1.}, {1., 0., 0.}, {-1., 0., 0.}};


    glNormal3fv(normals[0]); // Front
    glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0);         // Bottom Right
        glVertex3f(-1.5, -2.0, 1.0);

        glTexCoord2f(1.0, 0.0);         // Bottom Left
        glVertex3f( 1.5, -2.0, 1.0);

        glTexCoord2f(1.0, 1.0);         // Top Left
        glVertex3f( 1.5,  1.0, 1.0);

        glTexCoord2f(0.0, 1.0);         // Top Right
        glVertex3f(-1.5,  1.0, 1.0);
    glEnd();

    // glRotatef(0,0,1,0);
    glTranslatef(0,0,-1);

    glNormal3fv(normals[1]); // Back
    glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0);         // Bottom Right
        glVertex3f(-1.5, -2.0, 1.0);

        glTexCoord2f(1.0, 0.0);         // Bottom Left
        glVertex3f( 1.5, -2.0, 1.0);

        glTexCoord2f(1.0, 1.0);         // Top Left
        glVertex3f( 1.5,  1.0, 1.0);

        glTexCoord2f(0.0, 1.0);         // Top Right
        glVertex3f(-1.5,  1.0, 1.0);
    glEnd();

    glRotatef(90,0,1,0);
    glTranslatef(-1.5,0,-2.5);


    glNormal3fv(normals[2]); // Left Side
    glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0);         // Bottom Right
        glVertex3f(-0.5, -2.0, 1.0);

        glTexCoord2f(1.0, 0.0);         // Bottom Left
        glVertex3f( 0.5, -2.0, 1.0);

        glTexCoord2f(1.0, 1.0);         // Top Left
        glVertex3f( 0.5,  1.0, 1.0);

        glTexCoord2f(0.0, 1.0);         // Top Right
        glVertex3f(-0.5,  1.0, 1.0);
    glEnd();

    glTranslatef(0,0,3);

    glNormal3fv(normals[3]); // Left Side
    glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0);         // Bottom Right
        glVertex3f(-0.5, -2.0, 1.0);

        glTexCoord2f(1.0, 0.0);         // Bottom Left
        glVertex3f( 0.5, -2.0, 1.0);

        glTexCoord2f(1.0, 1.0);         // Top Left
        glVertex3f( 0.5,  1.0, 1.0);

        glTexCoord2f(0.0, 1.0);         // Top Right
        glVertex3f(-0.5,  1.0, 1.0);
    glEnd();

}

// model character body part
void SolidCubeWidget::modelHips(){
    glBindTexture(GL_TEXTURE_2D, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgJeans.Width(), imgJeans.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, imgJeans.imageField());
    glColor3f(0.0,1.0,0.0);
    gluQuadricDrawStyle(pshoulders, GLU_FILL);
    gluQuadricTexture(pshoulders, true);
    gluCylinder(pshoulders,0.5,0.5,HIP_WIDTH,10,4);
}

// model character body part
void SolidCubeWidget::modelUpperArm(){
    glBindTexture(GL_TEXTURE_2D, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgPlaid.Width(), imgPlaid.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, imgPlaid.imageField());
    glColor3f(0.0,1.0,0.0);
    gluQuadricDrawStyle(pupperleft, GLU_FILL);
    gluQuadricTexture(pupperleft, true);
    gluCylinder(pupperleft,      0.5,0.5,   2,10,4);

    glBindTexture(GL_TEXTURE_2D, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgSkinTone.Width(), imgSkinTone.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, imgSkinTone.imageField());
    glColor3f(0.0,1.0,0.0);
    gluQuadricDrawStyle(pupperleft, GLU_FILL);
    gluQuadricTexture(pupperleft, true);
    gluCylinder(pupperleft,      0.35,0.35,    3,10,4);

}

// model character body part
void SolidCubeWidget::modelLowerArm(){
    glBindTexture(GL_TEXTURE_2D, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgSkinTone.Width(), imgSkinTone.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, imgSkinTone.imageField());
    glColor3f(0.0,1.0,0.0);
    gluQuadricDrawStyle(plowerleft, GLU_FILL);
    gluQuadricTexture(plowerleft, true);
    gluCylinder(plowerleft,      0.35,0.25,    2,10,8);
}

// model character body part
void SolidCubeWidget::modelUpperLeg(){
    glBindTexture(GL_TEXTURE_2D, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgJeans.Width(), imgJeans.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, imgJeans.imageField());
    glColor3f(0.0,1.0,0.0);
    gluQuadricDrawStyle(pupperleftLeg, GLU_FILL);
    gluQuadricTexture(pupperleftLeg, true);
    gluCylinder(pupperleftLeg,   0.5,0.5,    2,10,4);

    glBindTexture(GL_TEXTURE_2D, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgSkinTone.Width(), imgSkinTone.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, imgSkinTone.imageField());
    glColor3f(0.0,1.0,0.0);
    gluQuadricDrawStyle(pupperleftLeg, GLU_FILL);
    gluQuadricTexture(pupperleftLeg, true);
    gluCylinder(pupperleftLeg,  0.35,0.35,    3.25,10,4);
}

// model character body part
void SolidCubeWidget::modelLowerLeg(){
    glBindTexture(GL_TEXTURE_2D, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgSkinTone.Width(), imgSkinTone.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, imgSkinTone.imageField());
    glColor3f(0.0,1.0,0.0);
    gluQuadricDrawStyle(pupperleftLeg, GLU_FILL);
    gluQuadricTexture(pupperleftLeg, true);
    gluCylinder(plowerleftLeg,   0.35,0.25,    3,10,8);
}


// model floor
void SolidCubeWidget::modelGround(){
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgGrass.Width(), imgGrass.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, imgGrass.imageField());

    gluDisk(pground,0,100 ,8,8);
}

// event for keyboard input
void SolidCubeWidget::keyPressEvent(QKeyEvent * e){
    // std::cout << "Pressed: " << char(e->key()) << "\n";

    switch (e->key()) {
        case Qt::Key_A:
        case Qt::Key_S:
        case Qt::Key_W:
        case Qt::Key_D:
            pcKeyDown = char(e->key());  break; // key up
        case Qt::Key_Down:  arrowKeyDown = 'D';  break; // key up
        case Qt::Key_Left:  arrowKeyDown = 'L';  break; // key up
        case Qt::Key_Right: arrowKeyDown = 'R';  break; // key up
        case Qt::Key_Up:    arrowKeyDown = 'U';  break; // key up

    }
}

void SolidCubeWidget::keyReleaseEvent(QKeyEvent * e){
    // std::cout << "Released: " << char(e->key()) << "\n";
    pcKeyDown = ' ';
    arrowKeyDown = ' ';
    arrowKeyUp = e->key();
}



SolidCubeWidget::~SolidCubeWidget(){}

void SolidCubeWidget::updateSlider(int i){
    sliderValue = float(i)/100.0;
    std::cout << sliderValue << "  " << sliderValue << "\n";

}

void SolidCubeWidget::updateCameraSliderX(int i){
    cameraAngleX = float(i)/32.0f;
}
void SolidCubeWidget::updateCameraSliderY(int i){
    cameraAngleY = float(i)/10.0f;
}

void SolidCubeWidget::buttonResetCamera(){
    cameraAngleX=0.0f;
    cameraAngleY=0.0f;
}

void SolidCubeWidget::buttonResetPlayer(){ // Reset Player Position
    pcX=0;
    pcY=0;
    pcZ=10;
    buttonResetCamera();
    toggleStressTest=0;
    stressAngle=0;
    cameraAngleX=0;
    cameraAngle=0;
}

void SolidCubeWidget::buttonStressTest(){
    if (toggleStressTest==0){
        toggleStressTest = 1;
    }else if (toggleStressTest==1){
        buttonResetPlayer();
    }
}

void SolidCubeWidget::buttonPositionLight(){
    if (togglePositionLight==0){
        togglePositionLight = 1;
    }else if (togglePositionLight==1){
        togglePositionLight = 0;
    }
}

void SolidCubeWidget::buttonAnimatePlayer(){
    if (toggleAnimatePlayer==0){
        toggleAnimatePlayer = 1;
    }else if (toggleAnimatePlayer==1){
        toggleAnimatePlayer = 0;
    }
}

void SolidCubeWidget::buttonSwitchHead(){
    if (playerHead==0){
        playerHead = 1;
    }else if (playerHead==1){
        playerHead = 2;
    }else if (playerHead==2){
        playerHead = 0;
    }
}


void SolidCubeWidget::updateAngle(){
    angle += .1;
    double moveSpeed = 0.5;

    if (toggleStressTest==1){
        // If stress test
        stressAngle+=0.02;
        cameraAngleX-=0.1;
        cameraAngle= remainder(cameraAngle+.1, 360/radian);
        pcAngle = 0;
        animWalkCycle();
    }else if (toggleAnimatePlayer==1) {
        animWalkCycle();
    }else{
        switch (arrowKeyDown) {
            case  'U':
                // std::cout << "Angle: " << pcAngle*radian << "\n";
                pcX -= moveSpeed*sin(pcAngle);
                pcZ -= moveSpeed*cos(pcAngle);
                animWalkCycle();
                break; // key up
            case  'D':
                pcX += moveSpeed*sin(pcAngle);
                pcZ += moveSpeed*cos(pcAngle);
                animWalkCycle();
                break; // key down
            case  'L':
                pcAngle+=.1;
                cameraAngle = remainder(cameraAngle+.1, 360/radian);
                break; // key right
            case  'R':
                pcAngle-=.1;
                cameraAngle = remainder(cameraAngle-.1, 360/radian);
                break; // key left
            default:
                armangle = 0; break;


        }
    }
    this->repaint();

    if (playerHead==2){
        playerHeadRotation+=1;
    }
}

void SolidCubeWidget::animWalkCycle(){
    int animSpeed = 5;
    armangle = (animDirection) ? armangle+animSpeed : armangle-animSpeed;

    if (armangle>35 && animDirection){
        animDirection=false;
    } else if (armangle<-35 && !animDirection){
        animDirection=true;
    }
}

// called every time the widget is resized
void SolidCubeWidget::resizeGL(int w, int h){ // resizeGL()

    // set the viewport to the entire widget
    glViewport(0, 0, w, h);
    GLfloat light_pos[] = {1., 0.5, 1., 0.};

    glEnable(GL_LIGHTING); // enable lighting in general
    glEnable(GL_LIGHT0);   // each light source must also be enabled

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    materialStruct* p_front = &brassMaterials;

    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightf (GL_LIGHT0, GL_SPOT_CUTOFF, 150.);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float ratioX=16, ratioY=9, fov=10;
    ratioX/=fov;
    ratioY/=fov;
    glFrustum(-1*ratioX, ratioX, -1*ratioY, ratioY, 1.5, 100.0);  // FOV, Draw distance)
    glMatrixMode(GL_MODELVIEW);
}



void SolidCubeWidget::modelLog(){
    glPushMatrix();
    // pLog
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgLogBark.Width(), imgLogBark.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, imgLogBark.imageField());
    glColor3f(0.0,1.0,0.0);
	gluQuadricDrawStyle(pLog, GLU_FILL);
	glBindTexture(GL_TEXTURE_2D, 0);
	gluQuadricTexture(pLog, true);
	gluQuadricNormals(pLog, GLU_SMOOTH);
    gluCylinder(pLog,0.5,0.5, 3,20,8);
    glPopMatrix();


    glPushMatrix();
    // pLogStump
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgLogStump.Width(), imgLogStump.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, imgLogStump.imageField());
    glBindTexture(GL_TEXTURE_2D, 0);
    glColor3f(0.0,1.0,0.0);
    gluDisk(pLogStump,0,.5,20,10);
    glTranslatef(0, 0, 3);
    gluDisk(pLogStump,0,.5,20,10);
    glPopMatrix();

    glPushMatrix();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgLogStumpInner.Width(), imgLogStumpInner.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, imgLogStumpInner.imageField());
    glBindTexture(GL_TEXTURE_2D, 0);
    gluQuadricTexture(pLogStumpInner, true);
	gluQuadricNormals(pLogStumpInner, GLU_SMOOTH);

    glTranslatef(0, 0, -.01);
    glRotatef(-180,1,0,0);
    gluDisk(pLogStumpInner,0,.4,20,10);
    glRotatef(-180,1,0,0);
    glTranslatef(0, 0, 3.02);
    gluDisk(pLogStumpInner,0,.4,20,10);
    glPopMatrix();

}

void SolidCubeWidget::modelLogLong(){
    glPushMatrix();
    // pLog
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgLogBark.Width(), imgLogBark.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, imgLogBark.imageField());
    glColor3f(0.0,1.0,0.0);
	gluQuadricDrawStyle(pLog, GLU_FILL);
	glBindTexture(GL_TEXTURE_2D, 0);
	gluQuadricTexture(pLog, true);
	gluQuadricNormals(pLog, GLU_SMOOTH);
    gluCylinder(pLog,0.5,0.5, 28,20,8);
    glPopMatrix();
}

void SolidCubeWidget::modelLogWide(){
    glPushMatrix();
    // pLog
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgLogBark.Width(), imgLogBark.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, imgLogBark.imageField());
    glColor3f(0.0,1.0,0.0);
	gluQuadricDrawStyle(pLog, GLU_FILL);
	glBindTexture(GL_TEXTURE_2D, 0);
	gluQuadricTexture(pLog, true);
	gluQuadricNormals(pLog, GLU_SMOOTH);
    gluCylinder(pLog,2,2, 5,20,8);
    glPopMatrix();
}


void SolidCubeWidget::modelTree(){
    modelLogWide();

    glTranslatef(0, 0, 5);
    glRotatef(5,0,1,1);
    // pLeaves
    glBindTexture(GL_TEXTURE_2D, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgLeaves.Width(), imgLeaves.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, imgLeaves.imageField());
    glColor3f(0.0,1.0,0.0);
    gluQuadricDrawStyle(pLeaves, GLU_FILL);
    gluQuadricTexture(pLeaves, true);
    gluQuadricNormals(pLeaves, GLU_SMOOTH);
    gluCylinder(pLeaves,12,4, 8,5,10);

    glRotatef(-5,0,1,1);
    glTranslatef(0, 0, 5);
    glRotatef(5,1,0,1);
    gluCylinder(pLeaves,10,2, 8,5,10);
    glRotatef(-5,1,0,1);
    glTranslatef(0, 0, 5);
    glRotatef(5,1,1,0);
    gluCylinder(pLeaves,8,0, 8,5,10);

}

void SolidCubeWidget::modelTent(){
    // tentWall
    glBindTexture(GL_TEXTURE_2D, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgTentWall.Width(), imgTentWall.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, imgTentWall.imageField());
    glColor3f(0.0,1.0,0.0);
    gluQuadricDrawStyle(pTentWall, GLU_FILL);
    gluQuadricTexture(pTentWall, true);
    gluQuadricNormals(pTentWall, GLU_SMOOTH);
    gluCylinder(pTentWall,12,1,  18,5,10);

}



// called every time the widget needs painting
void SolidCubeWidget::paintGL() { // paintGL()

    glFlush(); // flush to screen

    materialStruct* p_front = &whiteShinyMaterials;

    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
	glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

	p_front = &brassMaterials;
    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
	glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);


    // LIGHTING
    if (togglePositionLight==0){ // Fire Light
        glPushMatrix();
        //glLoadIdentity();
        glColor3f ( 1.0f, 1.0f, 0.0f ) ;
        GLfloat light_pos[] = {0., 0., 0., 5.};
        glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
        glLightf (GL_LIGHT0, GL_SPOT_CUTOFF,500.);

        glEnable ( GL_LIGHTING ) ;
        glPopMatrix();

        // glPushMatrix();
        // //glLoadIdentity();
        // glColor3f ( 1.0f, 1.0f, 0.0f ) ;
        // GLfloat light_pos2[] = {0., 1., 0., 5.};
        // glLightfv(GL_LIGHT1, GL_POSITION, light_pos2);
        // glLightf (GL_LIGHT1, GL_SPOT_CUTOFF,500.);
        //
        // glEnable ( GL_LIGHTING ) ;
        // glPopMatrix();
    }

    // clear the widget
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);

    // You must set the matrix mode to model view directly before enabling the depth test
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST); // comment out depth test to observe the result

    // Environment
	glPushMatrix();
    glTranslatef(0, -10, 0);
    glRotatef(-90,1,0,0);
	this->modelGround();
	glPopMatrix();


    // Fire Logs
    glPushMatrix();
    glTranslatef(0, -9.6, 0);
    for (int i = 0; i < 7; i++) {
        modelLog();
        glTranslatef(0, 0, -1);
        glRotatef(-50,0,1,0);
        glTranslatef(0, 0, 1);

    }
    glPopMatrix();



    // Tents
    int tentDist = -30;
    glPushMatrix();
    glTranslatef(0, -10, tentDist);
    glRotatef(-90,1,0,0);
    for (int i = 0; i < 5; i++) {
        glTranslatef(0, tentDist, 0);
        glRotatef(-60,0,0,1);
        glTranslatef(0, tentDist*-1, 0);

        modelTent();
        for (int i = 0; i < 5; i++) {
            glTranslatef(0, 13, 0);
            glRotatef(32,1,0,0);
            modelLogLong();
            glRotatef(-32,1,0,0);
            glTranslatef(0, -13, 0);
            glRotatef(72,0,0,1);
        }
    }
    glPopMatrix();

    // Trees
    int treeAngle = 0;
    int treeX[]     = { 35, 25, 10,-15,-45, 42,-42, 25, -20, 60, 45, -40, -40 };
    int treeY[]     = { 50,-40, 35, 45, 25,  0,  0,-65, -38, 45,-25, -40,  40 };
    glPushMatrix();
    glRotatef(-90,1,0,0);
        for (int i = 0; i < 13; i++) {
            treeAngle+=20;
            glPushMatrix();
            glTranslatef(treeX[i], treeY[i], -10);
            glRotatef(treeAngle,0,0,1);
            modelTree();
            glPopMatrix();
        }
    glPopMatrix();


    // PC
    if (toggleStressTest==1){
        // Stress Test
        double stressRadius=50;

        pcX = (stressRadius*sin(stressAngle));
        pcZ = (stressRadius*cos(stressAngle));
    }

    // Regular
    glTranslatef(pcX,0,pcZ);
    glRotatef(90+cameraAngle*radian,0,1.,0);

	// Shoulders
	glPushMatrix();
    glTranslatef(0.,0.,-SHOULDER_WIDTH/2);
	this->modelShoulders();
	glPopMatrix();

	// Head
	glPushMatrix(); // save the global rotation state
	glTranslatef(0., HEAD_HEIGHT, 0.);
	modelHead();
	glPopMatrix();  // restore the original matrix

    double armAngle2 = (armangle<0) ? -armangle:armangle;

    glPushMatrix(); // Right Arm
	glRotatef((double)armangle,0.,0.,1.);
	glTranslatef(0.,0., SHOULDER_WIDTH/2.);
    glRotatef(90,1.,0.,0.);
	this->modelUpperArm();
	glTranslatef(0.,0.,ARM_LENGTH); // move to the end of the arm;
	glRotatef((double)armAngle2,0.,1.,0.);
	this->modelLowerArm();
	glPopMatrix();

    glPushMatrix(); // Left Arm
    glRotatef(-(double)armangle,0.,0.,1.);
    glTranslatef(0.,0., -SHOULDER_WIDTH/2.);
    glRotatef(90,1.,0.,0.);
    this->modelUpperArm();
    glTranslatef(0.,0.,ARM_LENGTH); // move to the end of the arm;
    glRotatef((double)armAngle2,0.,1.,0.);
    this->modelLowerArm();
    glPopMatrix();

    // Hips
	glPushMatrix();
    glTranslatef(0, HIP_HEIGHT,-HIP_WIDTH/2);
	this->modelHips();
	glPopMatrix();

    glPushMatrix(); // Right Leg
    glTranslatef(0., HIP_HEIGHT+.25, -HIP_WIDTH/2.);
	glRotatef((double)armangle,0.,0.,1.);
    glRotatef(90,1.,0.,0.);
	this->modelUpperLeg();
	glTranslatef(0.,0.,LEG_LENGTH); // move to the end of the arm;
	glRotatef(-(double)armAngle2,0.,1.,0.);
	this->modelLowerLeg();
	glPopMatrix();

    glPushMatrix(); // Left Leg
    glTranslatef(0., HIP_HEIGHT+.25,  HIP_WIDTH/2.);
    glRotatef(-(double)armangle,0.,0.,1.);
    glRotatef(90,1.,0.,0.);
    this->modelUpperLeg();
    glTranslatef(0.,0.,LEG_LENGTH); // move to the end of the arm;
    glRotatef(-(double)armAngle2,0.,1.,0.);
    this->modelLowerLeg();
    glPopMatrix();

    // LIGHTING
    if (togglePositionLight==1){ // Player Light
        glPushMatrix();
        //glLoadIdentity();
        glColor3f ( 1.0f, 1.0f, 0.0f ) ;
        GLfloat light_pos[] = {0., 0., 0., 5.};
        glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
        glLightf (GL_LIGHT0, GL_SPOT_CUTOFF,500.);

        glEnable ( GL_LIGHTING ) ;
        glPopMatrix();
    }

    // CAMERA SYSTEM
    // Any point (x,y) on the path of the circle is x = rsin(θ), y = rcos(θ).
    // (x,y) = (cameraDistance*sin(cameraAngle), cameraDistance*cos(cameraAngle))
    // The point (0,r) ends up at x=rsinθ, y=rcosθ.
    double cameraDistance = 15;
    eyeX = pcX+(cameraDistance*sin(cameraAngle+cameraAngleX) );
    eyeY = 4+cameraAngleY;
    eyeZ = pcZ+(cameraDistance*cos(cameraAngle+cameraAngleX));
    centerX = pcX; centerY = -1; centerZ = pcZ;
    upX = 0.0; upY = 1.0; upZ = 0.0;    // Up direction used for rotation


	glLoadIdentity();
       	gluLookAt(eyeX,eyeY,eyeZ,centerX,centerY,centerZ,upX,upY,upZ);
	glFlush(); // flush to screen
}
