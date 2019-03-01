#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addNewCube(){

    Cube* cube = new Cube();
    cube->setPosition(static_cast<float> (ui->posx->value()), static_cast<float> (ui->posy->value()), static_cast<float> (ui->posz->value()));
    cube->setOrientation(static_cast<float> (ui->roulis->value()), static_cast<float> (ui->tangage->value()), static_cast<float> (ui->lacet->value()));
    ui->openGLWidget->addDrawable(cube);
}

void MainWindow::addNewPinkCube(){

    CubeTex* cubetex = new CubeTex();
    cubetex->setPosition(static_cast<float> (ui->posx->value()), static_cast<float> (ui->posy->value()), static_cast<float> (ui->posz->value()));
    cubetex->setOrientation(static_cast<float> (ui->roulis->value()), static_cast<float> (ui->tangage->value()), static_cast<float> (ui->lacet->value()));
    cubetex->setTexture(":images/cubeRose128");
    ui->openGLWidget->addDrawable(cubetex);
}

void MainWindow::addNewDeAJouer(){

    DeAJouer* dee = new DeAJouer();
    dee->setPosition(static_cast<float> (ui->posx->value()), static_cast<float> (ui->posy->value()), static_cast<float> (ui->posz->value()));
    dee->setOrientation(static_cast<float> (ui->roulis->value()), static_cast<float> (ui->tangage->value()), static_cast<float> (ui->lacet->value()));
    dee->setTexture(":images/texture_de");
    ui->openGLWidget->addDrawable(dee);
}

