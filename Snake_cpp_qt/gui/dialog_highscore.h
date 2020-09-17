#pragma once

#include <QDialog>
#include <QPushButton>
#include <QTableView>
#include <QStandardItemModel>

namespace Ui {
class dialog_highscore;
}

class dialog_highscore : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_highscore(QWidget *parent = nullptr);
    ~dialog_highscore();

private:
    Ui::dialog_highscore *ui;
    QPushButton* m_ok_button;
    QTableView* m_table_highscore;
    QStandardItemModel* m_model;
};
