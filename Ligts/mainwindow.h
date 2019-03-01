#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cubetex.h"
#include "deAJouer.h"
#include "cubeeclaire.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addNewCube();
    void addNewPinkCube();
    void addNewDeAJouer();
    void addNewLightCube();
    void changeAmbientLight();
    void changeDiffuseLight();
    void changeSpecularLight();
    void changeSpecularCoefficent();
    void changeLightPosition();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
