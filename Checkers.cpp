#include "Checkers.h"


bool CheckPosEdit(QLineEdit* _edit, float &_num)
{
    bool result = false;
    bool ok;
    QString temp = _edit->text();

    _num = temp.toInt(&ok, 10);
    if (ok && _num > -100000 && _num < 100000)
        result = true;
    return result;
}

bool CheckPosEdit(QLineEdit* _edit, int &_num)
{
    bool result = false;
    bool ok;
    QString temp = _edit->text();

    _num = temp.toInt(&ok, 10);
    if (ok && _num > -100000 && _num < 100000)
        result = true;
    return result;
}
