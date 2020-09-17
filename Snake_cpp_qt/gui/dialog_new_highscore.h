#pragma once

#include <QDialog>
#include <QPushButton>
#include <QTableView>
#include <QStandardItemModel>
#include <QLineEdit>

namespace Ui {
class DialogNewHighscore;
}

class DialogNewHighscore : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewHighscore(unsigned int& new_highscore, QWidget *parent = nullptr);
    ~DialogNewHighscore();

private:
    Ui::DialogNewHighscore *ui;
    QPushButton* m_ok_button;
    QLineEdit* m_line_edit_name;
    QTableView* m_table_highscore;
    QStandardItemModel* m_model;
    std::vector<std::pair<std::string, std::string>> m_highscore_list;

private slots:
    void enter_name();
};
