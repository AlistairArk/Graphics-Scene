#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

#include <QGLWidget>
#include <GL/glut.h>
#include "Image.h"

class SolidCubeWidget: public QGLWidget	{ //

	Q_OBJECT

	public:
    	SolidCubeWidget(QWidget *parent);
    	~SolidCubeWidget();

	public slots:
        void updateAngle();
        void updateSlider(int i);
        void updateCameraSliderX(int i);
        void updateCameraSliderY(int i);
        void buttonResetCamera();
        void buttonResetPlayer();
        void buttonStressTest();
        void buttonPositionLight();
        void buttonAnimatePlayer();
        void buttonSwitchHead();


	protected:
    	void initializeGL();           // called when OpenGL context is set up
    	void resizeGL(int w, int h);   // called every time the widget is resized
    	void paintGL();                // called every time the widget needs painting
        void keyPressEvent(QKeyEvent *e);    // Keyboard handler
        void keyReleaseEvent(QKeyEvent *e);


	private:
        // Animation
        void animWalkCycle();

        // Environment Objects
        void modelGround(); GLUquadricObj* pground;
        void modelTent();   GLUquadricObj* pTentWall;
        void modelLog();    GLUquadricObj* pLog; GLUquadricObj* pLogStump; GLUquadricObj* pLogStumpInner;
        void modelLogLong();
        void modelLogWide();
        void modelTree();   GLUquadricObj* pLeaves;

        // Player Object
    	void modelHead();
        void modelShoulders();
    	void modelHips();
        void modelUpperArm();
    	void modelLowerArm();
        void modelUpperLeg();
        void modelLowerLeg();

    	GLUquadricObj* phead;
    	GLUquadricObj* ptorso;
    	GLUquadricObj* pshoulders;
        GLUquadricObj* pupperleft;
    	GLUquadricObj* plowerleft;
        GLUquadricObj* pupperleftLeg;
        GLUquadricObj* plowerleftLeg;

        double pcX,pcY,pcZ;     // Position in world
        char pcKeyDown;         // Holds last key user pressed down
        char arrowKeyDown, arrowKeyUp;

        double angle;
    	double cameraAngle, cameraAngleX, cameraAngleY;
        double pcAngle;
    	int armangle;
        bool animDirection;

        // gluLookAt
        double eyeX,eyeY,eyeZ,centerX,centerY,centerZ,upX,upY,upZ;


        // Images
        Image imgGrass;
        Image imgLeaves;
        Image imgLogStump;
        Image imgLogStumpInner;
        Image imgLogBark;
        Image imgLogBark2;
        Image imgTentWall;
        Image imgSkinTone;
        Image imgNoseTone;
        Image imgPlaid;
        Image imgJeans;
        Image imgHead;
        Image imgEarth;
        Image imgMoi;
	};
#endif
