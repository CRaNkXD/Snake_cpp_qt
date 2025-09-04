#include "dialog_highscore.h"
#include "ui_dialog_highscore.h"

#include <vector>
#include <utility>
#include <string>

#include <helper.h>

// #include <gamewindow.h>

dialog_highscore::dialog_highscore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_highscore)
{
    ui->setupUi(this);
    m_ok_button = ui->btn_OK;
    m_table_highscore = ui->table_highscore;

    std::vector<std::pair<std::string, std::string>> highscore_list;
    // get the current highscore list and init the table view
    highscore_list = get_highscore_list();

    m_model = new QStandardItemModel(Tools::sizet_to_int(highscore_list.size()),2,this);
    m_table_highscore->setModel(m_model);

    m_model->setHorizontalHeaderLabels({"Name", "Points"});
    m_table_highscore->verticalHeader()->hide();

    for (int i = 0; i < Tools::sizet_to_int(highscore_list.size()); ++i)
    {
        QModelIndex idx_name = m_model->index(i,0,QModelIndex());
        QModelIndex idx_points = m_model->index(i,1,QModelIndex());
        QString name = QString::fromStdString(highscore_list[i].first);
        m_model->setData(idx_name, name);
        QString points = QString::fromStdString(highscore_list[i].second);
        m_model->setData(idx_points, points);
    }

    //connect slots
    connect(m_ok_button, SIGNAL (clicked()), this, SLOT (close()));
}

dialog_highscore::~dialog_highscore()
{
    delete ui;
}
