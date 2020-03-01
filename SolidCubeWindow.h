#ifndef __GL_POLYGON_WINDOW_H__
#define __GL_POLYGON_WINDOW_H__ 1

#include <QGLWidget>
#include <QMenuBar>
#include <QSlider>
#include <QBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include "SolidCubeWidget.h"
#include <QTimer>

class SolidCubeWindow: public QWidget {

	public:
    	// constructor / destructor
    	SolidCubeWindow(QWidget *parent);
    	~SolidCubeWindow();

    	// window layout
        QBoxLayout *windowLayout;
    	QBoxLayout *mainLayout;

    	SolidCubeWidget *cubeWidget;   // beneath that, the main widget

    	// Camera Rotation Sliders
        QSlider *nSlider;
    	QSlider *nSlider2;

    	QTimer* ptimer;            // timer for animation
    	void ResetInterface();     // resets all the interface elements

    private:
        enum { NumButtons = 8 };

        QGroupBox *horizontalGroupBox;
        QGroupBox *gridGroupBox;
        QPushButton *buttons[NumButtons];
    };

#endif
