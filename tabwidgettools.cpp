#include "tabwidgettools.h"
#include "ui_tabwidgettools.h"

TabWidgetTools::TabWidgetTools(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::TabWidgetTools)
{
    ui->setupUi(this);
    myparent = NULL;
}

TabWidgetTools::~TabWidgetTools()
{
    delete ui;
}

void TabWidgetTools::SetScene(Scene *scene)
{
    _scene = scene;
    ParseSceneObjects();
    AddItemsToCombo();
}

void TabWidgetTools::SetMyParent(QWidget *par)
{
    myparent = par;
}

void TabWidgetTools::closeEvent(QCloseEvent *)
{
    if (myparent == NULL)
    {
        QMessageBox msg;
        msg.exec();
    } else {
        LoadItemsToScene();
        myparent->setEnabled(true);    
    }
}

void TabWidgetTools::on_SCloseButton_clicked()
{
    this->close();
}

void TabWidgetTools::ParseSceneObjects()
{
    Triangle *tr;
    Sphere  *sp;

    for (int i = 0; i < _scene->objects.size(); i++)
    {
        tr = dynamic_cast<Triangle *>(_scene->objects[i]);
        sp = dynamic_cast<Sphere *>(_scene->objects[i]);
        if (tr != NULL)
            triangles.push_back(*tr);
        else
            spheres.push_back(*sp);
    }
    lights = _scene->lights;
}

int TabWidgetTools::GetCurrentMaterialNum(const Material &m)
{
    return m.id;
}

Material TabWidgetTools::GetMaterial(int num)
{
    switch(num) {
    case 0:
        return constMaterial.metal;
        break;
    case 1:
        return constMaterial.plastic;
        break;
    case 2:
        return constMaterial.wood;
        break;
    case 3:
        return constMaterial.mirror;
        break;
    }

    QMessageBox msg;
    msg.setText("Wrong material");
    msg.exec();

    return constMaterial.metal;
}
void TabWidgetTools::AddItemsToCombo()
{
    QString str =  QString::fromLocal8Bit("Треугольник ");
    for (int i = 0; i < triangles.size(); i++)
    {
        ui->TrianglesComboBox->addItem(str + QString::number(i));
    }

    str =  QString::fromLocal8Bit("Сфера ");
    for (int i = 0; i < spheres.size(); i++)
    {
        ui->SphereComboBox->addItem(str + QString::number(i));
    }

    str =  QString::fromLocal8Bit("Источник света ");
    for (int i = 0; i < lights.size(); i++)
    {
        ui->LightComboBox->addItem(str + QString::number(i));
    }
}

void TabWidgetTools::on_TCloseButton_clicked()
{
    this->close();
}

void TabWidgetTools::on_LCloseButton_clicked()
{
    this->close();
}

void TabWidgetTools::on_LightComboBox_currentIndexChanged(int index)
{
    Light _light = lights[index];
    ui->LightPosXEdit->setText(QString::number((int)_light.pos[0]));
    ui->LightPosYEdit->setText(QString::number((int)_light.pos[1]));
    ui->LightPosZEdit->setText(QString::number((int)_light.pos[2]));
}

void TabWidgetTools::on_SphereComboBox_currentIndexChanged(int index)
{
    Sphere sp = spheres[index];
    ui->SpherePosXEdit->setText(QString::number((int)sp.pos[0]));
    ui->SpherePosYEdit->setText(QString::number((int)sp.pos[1]));
    ui->SpherePosZEdit->setText(QString::number((int)sp.pos[2]));
    ui->SphereRadiusEdit->setText(QString::number((int)sp.radius));
    ui->SColor->SetColor(sp.material.color);

    ui->SStyleComboBox->setCurrentIndex(sp.material.id);
}

void TabWidgetTools::on_TrianglesComboBox_currentIndexChanged(int index)
{
    Triangle tr = triangles[index];
    ui->APosXEdit->setText(QString::number((int)tr.vertex[0][0]));
    ui->APosYEdit->setText(QString::number((int)tr.vertex[0][1]));
    ui->APosZEdit->setText(QString::number((int)tr.vertex[0][2]));

    ui->BPosXEdit->setText(QString::number((int)tr.vertex[1][0]));
    ui->BPosYEdit->setText(QString::number((int)tr.vertex[1][1]));
    ui->BPosZEdit->setText(QString::number((int)tr.vertex[1][2]));

    ui->CPosXEdit->setText(QString::number((int)tr.vertex[2][0]));
    ui->CPosYEdit->setText(QString::number((int)tr.vertex[2][1]));
    ui->CPosZEdit->setText(QString::number((int)tr.vertex[2][2]));

    ui->TColor->SetColor(tr.material.color);
    ui->TStyleComboBox->setCurrentIndex(tr.material.id);
}

bool TabWidgetTools::CheckTriangleParameters()
{
    float temp;
    QMessageBox msg;
    msg.setWindowTitle(QString::fromLocal8Bit("Ошибка"));
    if (!CheckPosEdit(ui->APosXEdit,temp))
    {
        msg.setText(QString::fromLocal8Bit("Значение координаты Х первой точки должно быть\nцелым и лежать в диапазоне от -99999 до 99999"));
        msg.exec();
        return false;
    }
    if (!CheckPosEdit(ui->APosYEdit,temp))
    {
        msg.setText(QString::fromLocal8Bit("Значение координаты Y первой точки должно быть\nцелым и лежать в диапазоне от -99999 до 99999"));
        msg.exec();
        return false;
    }
    if (!CheckPosEdit(ui->APosZEdit,temp))
    {
        msg.setText(QString::fromLocal8Bit("Значение координаты Z первой точки должно быть\nцелым и лежать в диапазоне от -99999 до 99999"));
        msg.exec();
        return false;
    }


    if (!CheckPosEdit(ui->BPosXEdit,temp))
    {
        msg.setText(QString::fromLocal8Bit("Значение координаты Х второй точки должно быть\nцелым и лежать в диапазоне от -99999 до 99999"));
        msg.exec();
        return false;
    }
    if (!CheckPosEdit(ui->BPosYEdit,temp))
    {
        msg.setText(QString::fromLocal8Bit("Значение координаты Y второй точки должно быть\nцелым и лежать в диапазоне от -99999 до 99999"));
        msg.exec();
        return false;
    }
    if (!CheckPosEdit(ui->BPosZEdit,temp))
    {
        msg.setText(QString::fromLocal8Bit("Значение координаты Z второй точки должно быть\nцелым и лежать в диапазоне от -99999 до 99999"));
        msg.exec();
        return false;
    }

    if (!CheckPosEdit(ui->CPosXEdit,temp))
    {
        msg.setText(QString::fromLocal8Bit("Значение координаты Х третьей точки должно быть\nцелым и лежать в диапазоне от -99999 до 99999"));
        msg.exec();
        return false;
    }
    if (!CheckPosEdit(ui->CPosYEdit,temp))
    {
        msg.setText(QString::fromLocal8Bit("Значение координаты Y третьей точки должно быть\nцелым и лежать в диапазоне от -99999 до 99999"));
        msg.exec();
        return false;
    }
    if (!CheckPosEdit(ui->CPosZEdit,temp))
    {
        msg.setText(QString::fromLocal8Bit("Значение координаты Z третьей точки должно быть\nцелым и лежать в диапазоне от -99999 до 99999"));
        msg.exec();
        return false;
    }
    return true;
}

bool TabWidgetTools::CheckSphereParameters()
{
    float temp;
    QMessageBox msg;
    msg.setWindowTitle(QString::fromLocal8Bit("Ошибка"));
    if (!CheckPosEdit(ui->SpherePosXEdit,temp))
    {
        msg.setText(QString::fromLocal8Bit("Значение координаты Х центра сферы должно быть целым\n и лежать в диапазоне от -99999 до 99999"));
        msg.exec();
        return false;
    }
    if (!CheckPosEdit(ui->SpherePosYEdit,temp))
    {
        msg.setText(QString::fromLocal8Bit("Значение координаты Y центра сферы должно быть целым\n и лежать в диапазоне от -99999 до 99999"));
        msg.exec();
        return false;
    }
    if (!CheckPosEdit(ui->SpherePosZEdit,temp))
    {
        msg.setText(QString::fromLocal8Bit("Значение координаты Z центра сферы должно быть целым\n и лежать в диапазоне от -99999 до 99999"));
        msg.exec();
        return false;
    }
    if (!CheckPosEdit(ui->SphereRadiusEdit,temp))
    {
        msg.setText(QString::fromLocal8Bit("Значение радиуса сферы должно быть целым\n и лежать в диапазоне от -99999 до 99999"));
        msg.exec();
        return false;
    }
    return true;
}

void TabWidgetTools::on_TApplyButton_clicked()
{
    Triangle tr;
    if (ui->TrianglesComboBox->count() > 0 && CheckTriangleParameters())
    {
        CheckPosEdit(ui->APosXEdit,tr.vertex[0].values[0]);
        CheckPosEdit(ui->APosYEdit,tr.vertex[0].values[1]);
        CheckPosEdit(ui->APosZEdit,tr.vertex[0].values[2]);

        CheckPosEdit(ui->BPosXEdit,tr.vertex[1].values[0]);
        CheckPosEdit(ui->BPosYEdit,tr.vertex[1].values[1]);
        CheckPosEdit(ui->BPosZEdit,tr.vertex[1].values[2]);

        CheckPosEdit(ui->CPosXEdit,tr.vertex[2].values[0]);
        CheckPosEdit(ui->CPosYEdit,tr.vertex[2].values[1]);
        CheckPosEdit(ui->CPosZEdit,tr.vertex[2].values[2]);

        tr.material = GetMaterial(ui->TStyleComboBox->currentIndex());
        tr.material.color = ui->TColor->_color;

        triangles[ui->TrianglesComboBox->currentIndex()] = tr;
    }
}

void TabWidgetTools::on_SApplyButton_clicked()
{
    Sphere sp;
    if ((ui->SphereComboBox->count() > 0) && CheckSphereParameters())
    {
        CheckPosEdit(ui->SpherePosXEdit,sp.pos.values[0]);
        CheckPosEdit(ui->SpherePosYEdit,sp.pos.values[1]);
        CheckPosEdit(ui->SpherePosZEdit,sp.pos.values[2]);
        CheckPosEdit(ui->SphereRadiusEdit,sp.radius);
        sp.material = GetMaterial(ui->SStyleComboBox->currentIndex());
        sp.material.color = ui->SColor->_color;
        spheres[ui->SphereComboBox->currentIndex()] = sp;
    }
}

bool TabWidgetTools::CheckLightParameters()
{
    int temp;
    QMessageBox msg;
    msg.setWindowTitle(QString::fromLocal8Bit("Ошибка"));
    if (!CheckPosEdit(ui->LightPosXEdit, temp))
    {
        msg.setText(QString::fromLocal8Bit("Значение координаты Х источника света должно\nбыть целым и лежать в интервале от -99999 до 99999"));
        msg.exec();
        return false;
    }

    if (!CheckPosEdit(ui->LightPosYEdit, temp))
    {
        msg.setText(QString::fromLocal8Bit("Значение координаты Y источника света должно\nбыть целым и лежать в интервале от -99999 до 99999"));
        msg.exec();
        return false;
    }

    if (!CheckPosEdit(ui->LightPosZEdit, temp))
    {
        msg.setText(QString::fromLocal8Bit("Значение координаты Z источника света должно\nбыть целым и лежать в интервале от -99999 до 99999"));
        msg.exec();
        return false;
    }
    return true;
}

void TabWidgetTools::on_LApplyButton_clicked()
{
    Light light;
    if (ui->LightComboBox->count() > 0 && CheckLightParameters())
    {
        CheckPosEdit(ui->LightPosXEdit, light.pos.values[0]);
        CheckPosEdit(ui->LightPosYEdit, light.pos.values[1]);
        CheckPosEdit(ui->LightPosZEdit, light.pos.values[2]);
        lights[ui->LightComboBox->currentIndex()] = light;
    }

}

void TabWidgetTools::LoadItemsToScene()
{
    _scene->lights = lights;
    for (int i = 0; i < lights.size(); i++)
        _scene->lights[i] = lights[i];
    std::vector<Triangle>::iterator tr = triangles.begin();
    std::vector<Sphere>::iterator sp = spheres.begin();
    Sphere *tempSp;
    Triangle *tempTr;
    for (int i = 0; i < _scene->objects.size(); i++)
    {
        tempSp = dynamic_cast<Sphere *>(_scene->objects[i]);
        tempTr = dynamic_cast<Triangle *>(_scene->objects[i]);
        if (tempSp != NULL)
        {
            *tempSp = *sp;
            sp++;
        } else {
            *tempTr = *tr;
            tr++;
        }
    }
    _scene->InitObjectsWithLight();
}

