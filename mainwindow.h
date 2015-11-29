#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Scene.h"
#include <QLineEdit>
#include <QMessageBox>
#include <QPixmap>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include "tabwidgettools.h"
#include "RWObjects.h"
#include "Checkers.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_GeneratePicButton_clicked();

    void on_EditProject_triggered();

    void on_SaveProject_triggered();

    void on_LoadProject_triggered();

    void on_Exit_triggered();

    void on_About_triggered();

private:
    bool InitCamera();
    void InitSceneProperties();
    bool InitScene();
    void LoadScene(const QString &filename);
    void SaveScene(const QString &filename);
private:
    TabWidgetTools *tabtools;
    Ui::MainWindow *ui;
    Scene scene;
    QPixmap _pic, _picBvh;
};

#endif // MAINWINDOW_H
