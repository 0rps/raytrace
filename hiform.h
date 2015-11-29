#ifndef HIFORM_H
#define HIFORM_H

#include <QWidget>

namespace Ui {
class HiForm;
}

class HiForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit HiForm(QWidget *parent = 0);
    ~HiForm();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::HiForm *ui;
};

#endif // HIFORM_H
