#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>

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

void MainWindow::addNewLightCube(){

    CubeEclaire* lightCube = new CubeEclaire();
    lightCube->setPosition(static_cast<float> (ui->posx->value()), static_cast<float> (ui->posy->value()), static_cast<float> (ui->posz->value()));
    lightCube->setOrientation(static_cast<float> (ui->roulis->value()), static_cast<float> (ui->tangage->value()), static_cast<float> (ui->lacet->value()));
    lightCube->setTexture(":images/ice");
    lightCube->setLight(ui->openGLWidget->light());
    ui->openGLWidget->addDrawable(lightCube);
}

void MainWindow::changeAmbientLight()
{
    Light* light = ui->openGLWidget->light();
    QColor col = QColorDialog::getColor(light->getAmbient_color(), this);
    if (col.isValid()) {
        QString qss = QString("background-color: %1;\n border: 1px solid black;\n border-radius: 5px;").arg(col.name());
        ui->ambientButton->setStyleSheet(qss);
        light->setAmbient_color(col);
    }
}

void MainWindow::changeDiffuseLight()
{
    Light* light = ui->openGLWidget->light();
    QColor col = QColorDialog::getColor(light->getDiffuse_color(), this);
    if (col.isValid()) {
        QString qss = QString("background-color: %1;\n border: 1px solid black;\n border-radius: 5px;").arg(col.name());
        ui->diffuseButton->setStyleSheet(qss);
        light->setDiffuse_color(col);
    }
}

void MainWindow::changeSpecularLight()
{
    Light* light = ui->openGLWidget->light();
    QColor col = QColorDialog::getColor(light->getSpecular_color(), this);
    if (col.isValid()) {
        QString qss = QString("background-color: %1;\n border: 1px solid black;\n border-radius: 5px;").arg(col.name());
        ui->specularButton->setStyleSheet(qss);
        light->setSpecular_color(col);
    }
}

void MainWindow::changeSpecularCoefficent()
{
    Light* light = ui->openGLWidget->light();
    light->setSpecular_strength(ui->SpecularCoeff->maximum()- ui->SpecularCoeff->value());
}

void MainWindow::changeLightPosition()
{
    Light* light = ui->openGLWidget->light();
    double x = ui->LightX->value();
    double y = ui->LightY->value();
    double z = ui->LightZ->value();

    light->setLight_position(QVector3D(x,y,z));

}
