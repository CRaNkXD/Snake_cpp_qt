#include "dialog_new_highscore.h"
#include "ui_dialog_new_highscore.h"

#include <QValidator>

#include <algorithm>

#include <helper.h>

DialogNewHighscore::DialogNewHighscore(unsigned int &new_highscore, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewHighscore)
{
    ui->setupUi(this);
    this->m_ok_button = ui->btn_OK;
    this->m_line_edit_name = ui->lineEdit_name;
    this->m_table_highscore = ui->table_highscore;

    // restrict line edit to alphanumeric and 10 chars
    this->m_line_edit_name->setValidator(new QRegExpValidator( QRegExp("\\w+"), this ));
    this->m_line_edit_name->setMaxLength(10);

    // get the current highscore list and init the table view
    this->m_highscore_list = get_highscore_list();

    this->m_model = new QStandardItemModel(Tools::sizet_to_int(this->m_highscore_list.size()),2,this);
    this->m_table_highscore->setModel(this->m_model);

    this->m_model->setHorizontalHeaderLabels({"Name", "Points"});
    this->m_table_highscore->verticalHeader()->hide();

    std::pair<std::string, std::string> new_entry{"NewHighscore", std::to_string(new_highscore)};
    this->m_highscore_list.insert(std::find_if(this->m_highscore_list.begin(), this->m_highscore_list.end(),
                                       [&](const auto& entry)
                                        {
                                            return Tools::int_to_uint(std::stoi(entry.second)) <= new_highscore;
                                        }), new_entry);
    this->m_highscore_list.pop_back();

    for (int i = 0; i != Tools::sizet_to_int(this->m_highscore_list.size()); ++i)
    {
        QModelIndex idx_name = this->m_model->index(i,0,QModelIndex());
        QModelIndex idx_points = this->m_model->index(i,1,QModelIndex());
        QString name = QString::fromStdString(this->m_highscore_list[i].first);
        QString points = QString::fromStdString(this->m_highscore_list[i].second);
        this->m_model->setData(idx_name, name);
        this->m_model->setData(idx_points, points);
    }

    //connect slots
    connect(this->m_ok_button, SIGNAL (clicked()), this, SLOT (enter_name()));
}

DialogNewHighscore::~DialogNewHighscore()
{
    delete ui;
}

void DialogNewHighscore::enter_name()
{
    QString name = this->m_line_edit_name->text();
    if (name != "")
    {
        auto it = std::find_if(this->m_highscore_list.begin(), this->m_highscore_list.end(),
                     [](const auto& entry)
                    {
                        return entry.first == "NewHighscore";
                    });

        it->first = name.toStdString();
        save_highscore_list(this->m_highscore_list);
        this->close();
    }
}
