#include "dialog_highscore.h"
#include "ui_dialog_highscore.h"

#include <vector>
#include <utility>
#include <string>

#include "gamewindow.h"
#include "helper/helper.h"

dialog_highscore::dialog_highscore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_highscore)
{
    ui->setupUi(this);
    this->m_ok_button = ui->btn_OK;
    this->m_table_highscore = ui->table_highscore;

    std::vector<std::pair<std::string, std::string>> highscore_list;
    // get the current highscore list and init the table view
    highscore_list = get_highscore_list();

    this->m_model = new QStandardItemModel(highscore_list.size(),2,this);
    this->m_table_highscore->setModel(this->m_model);

    this->m_model->setHorizontalHeaderLabels({"Name", "Points"});
    this->m_table_highscore->verticalHeader()->hide();

    for (size_t i = 0; i != highscore_list.size(); ++i)
    {
        QModelIndex idx_name = this->m_model->index(i,0,QModelIndex());
        QModelIndex idx_points = this->m_model->index(i,1,QModelIndex());
        QString name = QString::fromStdString(highscore_list[i].first);
        this->m_model->setData(idx_name, name);
        QString points = QString::fromStdString(highscore_list[i].second);
        this->m_model->setData(idx_points, points);
    }

    //connect slots
    connect(this->m_ok_button, SIGNAL (clicked()), this, SLOT (close()));
}

dialog_highscore::~dialog_highscore()
{
    delete ui;
}
