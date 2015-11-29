#ifndef TABWIDGETTOOLS_H
#define TABWIDGETTOOLS_H

#include <QTabWidget>
#include <QMessageBox>
#include "Scene.h"
#include "Primitives.h"
#include <vector>
#include "Checkers.h"

namespace Ui {
class TabWidgetTools;
}

class TabWidgetTools : public QTabWidget
{
    Q_OBJECT
    
public:
    explicit TabWidgetTools(QWidget *parent = 0);
    ~TabWidgetTools();
public:
    void SetMyParent(QWidget *par);
    void SetScene(Scene* scene);
private:
    void ParseSceneObjects();
    void AddItemsToCombo();
    int GetCurrentMaterialNum(const Material &m);
    Material GetMaterial(int num);
    bool CheckTriangleParameters();
    bool CheckSphereParameters();
    bool CheckLightParameters();
    void LoadItemsToScene();
private slots:
    void on_SCloseButton_clicked();
    void closeEvent(QCloseEvent *);
    void on_TCloseButton_clicked();
    void on_LCloseButton_clicked();
    void on_LightComboBox_currentIndexChanged(int index);
    void on_SphereComboBox_currentIndexChanged(int index);
    void on_TrianglesComboBox_currentIndexChanged(int index);
    void on_TApplyButton_clicked();
    void on_SApplyButton_clicked();
    void on_LApplyButton_clicked();

private:
    Scene *_scene;
    std::vector<Triangle> triangles;
    std::vector<Sphere> spheres;
    std::vector<Light> lights;
    QWidget *myparent;
    Ui::TabWidgetTools *ui;
};

#endif // TABWIDGETTOOLS_H
