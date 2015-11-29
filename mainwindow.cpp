#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QElapsedTimer>
#include "hiform.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMessageBox msg;
    //msg.setWindowTitle(QString::fromLocal8Bit("Курсовая работа"));
    //msg.setText(QString::fromLocal8Bit("Обратная трассировка лучей\nИспользование bvh-дерева для ускорения трассировки лучей\n\Выполнил: Могильников Алексей\nГруппа: ИУ7-52\nНаучный руководитель: Романова Татьяна Николаевна"));
    //msg.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::InitCamera()
{
    QMessageBox msg;
    msg.setWindowTitle(QString::fromLocal8Bit("Ошибка"));
    if (!CheckPosEdit(ui->CameraPosXEdit, scene.camera.pos.values[0]))
    {
        msg.setText(QString::fromLocal8Bit("Значение координаты Х положения камеры должно \nбыть целым и лежать в диапазоне от -99999 до 99999"));
        msg.exec();
        return false;
    }

    if (!CheckPosEdit(ui->CameraPosYEdit, scene.camera.pos.values[1]))
    {
        msg.setText(QString::fromLocal8Bit("Значение координаты Y положения камеры должно \nбыть целым и лежать в диапазоне от -99999 до 99999"));
        msg.exec();
        return false;
    }

    if (!CheckPosEdit(ui->CameraPosZEdit, scene.camera.pos.values[2]))
    {
        msg.setText(QString::fromLocal8Bit("Значение координаты Z положения камеры должно \nбыть целым и лежать в диапазоне от -99999 до 99999"));
        msg.exec();
        return false;
    }
    //////////////
    if (!CheckPosEdit(ui->CameraDirXEdit, scene.camera.screenVector.values[0]))
    {
        msg.setText(QString::fromLocal8Bit("Значение координаты Х вектора направления камеры должно \nбыть целым и лежать в диапазоне от -99999 до 99999"));
        msg.exec();
        return false;
    }
    if (!CheckPosEdit(ui->CameraDirYEdit, scene.camera.screenVector.values[1]))
    {
        msg.setText(QString::fromLocal8Bit("Значение координаты Y вектора направления камеры должно \nбыть целым и лежать в диапазоне от -99999 до 99999"));
        msg.exec();
        return false;
    }
    /*if (!CheckPosEdit(ui->CameraDirZEdit, scene.camera.screenVector.values[2]))
    {
        msg.setText(QString::fromLocal8Bit("Значение координаты Z вектора направления камеры должно \nбыть целым и лежать в диапазоне от -99999 до 99999"));
        msg.exec();
        return false;
    }*/
    scene.camera.screenVector.values[2] = 0;

    return true;
}

bool MainWindow::InitScene()
{
    InitSceneProperties();
    return InitCamera();
}

void MainWindow::InitSceneProperties()
{
    scene.isUseBvh = ui->BVHCheckBox->isChecked();
    scene.isDrawLight = ui->DrawLightCheckBox->isChecked();
    scene.isUseSmooth = ui->SmoothCheckBox->isChecked();
}

void MainWindow::on_GeneratePicButton_clicked()
{
    QElapsedTimer timer;
    qint64 bvhTime;
    qint64 traceTime;
    if (InitScene())
        if (scene.isUseBvh)
        {
            ui->bvhTime->setText(QString::fromLocal8Bit("Генерация изображения"));
            this->repaint();
            this->repaint();
            timer.start();
            scene.InitBVH();
            bvhTime = timer.elapsed();
            timer.restart();
            scene.DrawScene();
            traceTime = timer.elapsed();
            QString res = QString::fromLocal8Bit("Время генерации BVH дерева: ") + QString::number(bvhTime,10)+ QString::fromLocal8Bit("мс\n");
            res += QString::fromLocal8Bit("Время генерации изображения: ") +QString::number(traceTime,10) + QString::fromLocal8Bit("мс");
            ui->bvhTime->setText(res);
            ui->picBVH->SetImage(scene.matrixColor);
        } else{
            ui->standartTime->setText(QString::fromLocal8Bit("Генерация изображения"));
            this->repaint();
            this->repaint();
            timer.start();
            scene.DrawScene();
            traceTime = timer.elapsed();
            ui->picStandart->SetImage(scene.matrixColor);
            ui->standartTime->setText(QString::fromLocal8Bit("Время генерации изображения: ") +QString::number(traceTime,10) + QString::fromLocal8Bit("мс"));
        }
    this->update();
}

void MainWindow::on_EditProject_triggered()
{
    this->setEnabled(false);
    tabtools = new TabWidgetTools();
    tabtools->SetMyParent(this);
    tabtools->SetScene(&scene);
    tabtools->show();
}

void MainWindow::on_SaveProject_triggered()
{
    QString filename = "";
    filename = QFileDialog::getSaveFileName(this, "Save scene", "untitled.rtsc","Scenes (*.rtsc)");
    if (filename != "")
        SaveScene(filename);

}

void MainWindow::on_LoadProject_triggered()
{
    QString filename = "";
    filename = QFileDialog::getOpenFileName(this,"Open scene","","Scenes (*.rtsc)");
    if (filename != "")
        LoadScene(filename);
}

void MainWindow::SaveScene(const QString &filename)
{
    QFile fout(filename);
    fout.open(QIODevice::WriteOnly | QIODevice::Text);
    QDataStream out(&fout);
    std::vector<Triangle> triangles;
    std::vector<Sphere> spheres;
    Triangle* tr;
    Sphere* sp;
    for (int i = 0; i < scene.objects.size(); i++)
    {
        sp = dynamic_cast<Sphere *>(scene.objects[i]);
        tr = dynamic_cast<Triangle *>(scene.objects[i]);
        if (sp == NULL)
            triangles.push_back(*tr);
        else
            spheres.push_back(*sp);
    }
    out << spheres.size();
    for (int i = 0; i < spheres.size(); i++)
        out << spheres[i];
    out << triangles.size();
    for (int i = 0; i < triangles.size(); i++)
        out << triangles[i];
    out << scene.lights.size();
    for (int i = 0; i < scene.lights.size(); i++)
        out << scene.lights[i];
    fout.close();
  //  scene.
}

void MainWindow::LoadScene(const QString &filename)
{
    QFile fin(filename);
    fin.open(QIODevice::ReadOnly | QIODevice::Text);
    QDataStream in(&fin);
    scene.lights.clear();
    scene.ClearObjects();
    Sphere sp;
    Triangle tr;
    Light lt;
    int counter;

    in >> counter;
    for (int i = 0; i < counter; i++)
    {
        in >> sp;
        scene.objects.push_back(new Sphere(sp));
    }

    in >> counter;
    for (int i = 0; i < counter; i++)
    {
        in >> tr;
        scene.objects.push_back(new Triangle(tr));
    }

    in >> counter;
    for (int i = 0; i < counter; i++)
    {
        in >> lt;
        scene.lights.push_back(lt);
    }
    fin.close();
    scene.InitObjectsWithLight();
}

void MainWindow::on_Exit_triggered()
{
    close();
}

void MainWindow::on_About_triggered()
{
    HiForm* newform = new HiForm;
    newform->show();
}
