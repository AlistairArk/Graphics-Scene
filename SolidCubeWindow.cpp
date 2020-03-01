#include "SolidCubeWindow.h"

// constructor / destructor
SolidCubeWindow::SolidCubeWindow(QWidget *parent): QWidget(parent){ // constructor

    // create main widget
    cubeWidget = new SolidCubeWidget(this);
    cubeWidget->setGeometry(40,40,1024,576);

    /*
    30 fps      = 32
    60 fps      = 16.7
    */
    ptimer = new QTimer(this);
    connect(ptimer, SIGNAL(timeout()),  cubeWidget, SLOT(updateAngle()));
    ptimer->start(32);


    horizontalGroupBox = new QGroupBox(tr("Interactive Systemes"));

        QHBoxLayout *layout = new QHBoxLayout; // Create button layout

        buttons[0] = new QPushButton(tr("Reset Camera"));
        layout->addWidget(buttons[0]);
        connect(buttons[0], SIGNAL(clicked()), cubeWidget, SLOT(buttonResetCamera()));

        buttons[1] = new QPushButton(tr("Reset Player"));
        layout->addWidget(buttons[1]);
        connect(buttons[1], SIGNAL(clicked()), cubeWidget, SLOT(buttonResetPlayer()));

        buttons[2] = new QPushButton(tr("Animate Player"));
        layout->addWidget(buttons[2]);
        connect(buttons[2], SIGNAL(clicked()), cubeWidget, SLOT(buttonAnimatePlayer()));

        buttons[3] = new QPushButton(tr("Stress Test"));
        layout->addWidget(buttons[3]);
        connect(buttons[3], SIGNAL(clicked()), cubeWidget, SLOT(buttonStressTest()));

        buttons[4] = new QPushButton(tr("Position Light"));
        layout->addWidget(buttons[4]);
        connect(buttons[4], SIGNAL(clicked()), cubeWidget, SLOT(buttonPositionLight()));

        buttons[5] = new QPushButton(tr("Switch Head"));
        layout->addWidget(buttons[5]);
        connect(buttons[5], SIGNAL(clicked()), cubeWidget, SLOT(buttonSwitchHead()));

    horizontalGroupBox->setLayout(layout);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    // create slider
    nSlider2 = new QSlider(Qt::Vertical);
    connect(nSlider2, SIGNAL(valueChanged(int)), cubeWidget, SLOT(updateCameraSliderY(int)));
    mainLayout->addWidget(nSlider2);

    nSlider = new QSlider(Qt::Horizontal);
    connect(nSlider, SIGNAL(valueChanged(int)), cubeWidget, SLOT(updateCameraSliderX(int)));
    mainLayout->addWidget(nSlider);

    nSlider->setMinimum(-100); // Camera X Axis Slider
    nSlider->setMaximum(100);
    nSlider->setValue(80);

    nSlider2->setMinimum(-100); // Camera Y Axis Slider
    nSlider2->setMaximum(100);
    nSlider2->setValue(0);

    mainLayout->addWidget(horizontalGroupBox);

    setLayout(mainLayout);

    setWindowTitle(tr("Forest Camp")); // Set Widget Title
}


SolidCubeWindow::~SolidCubeWindow(){ // destructor
    delete nSlider;
	delete nSlider2;
	delete cubeWidget;
    delete windowLayout;
}


// resets all the interface elements
void SolidCubeWindow::ResetInterface() {


	// now force refresh
	cubeWidget->update();
	update();
}
