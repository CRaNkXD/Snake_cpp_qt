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
    m_ok_button = ui->btn_OK;
    m_line_edit_name = ui->lineEdit_name;
    m_table_highscore = ui->table_highscore;

    // restrict line edit to alphanumeric and 10 chars
    m_line_edit_name->setValidator(new QRegularExpressionValidator( QRegularExpression("\\w+"), this ));
    m_line_edit_name->setMaxLength(10);

    // get the current highscore list and init the table view
    m_highscore_list = get_highscore_list();

    m_model = new QStandardItemModel(Tools::sizet_to_int(m_highscore_list.size()),2,this);
    m_table_highscore->setModel(m_model);

    m_model->setHorizontalHeaderLabels({"Name", "Points"});
    m_table_highscore->verticalHeader()->hide();

    std::pair<std::string, std::string> new_entry{"NewHighscore", std::to_string(new_highscore)};
    m_highscore_list.insert(std::find_if(m_highscore_list.begin(), m_highscore_list.end(),
                                       [&](const auto& entry)
                                        {
                                            return Tools::int_to_uint(std::stoi(entry.second)) <= new_highscore;
                                        }), new_entry);
    m_highscore_list.pop_back();

    for (int i = 0; i != Tools::sizet_to_int(m_highscore_list.size()); ++i)
    {
        QModelIndex idx_name = m_model->index(i,0,QModelIndex());
        QModelIndex idx_points = m_model->index(i,1,QModelIndex());
        QString name = QString::fromStdString(m_highscore_list[i].first);
        QString points = QString::fromStdString(m_highscore_list[i].second);
        m_model->setData(idx_name, name);
        m_model->setData(idx_points, points);

        // Highlight the "NewHighscore" row
        if (name == "NewHighscore") {
            QBrush highlightBrush(QColor("#FFD700")); // Gold color
            QFont boldFont;
            boldFont.setBold(true);
            m_model->setData(idx_name, highlightBrush, Qt::BackgroundRole);
            m_model->setData(idx_points, highlightBrush, Qt::BackgroundRole);
            m_model->setData(idx_name, boldFont, Qt::FontRole);
            m_model->setData(idx_points, boldFont, Qt::FontRole);
        }
    }

    //connect slots
    connect(m_ok_button, SIGNAL (clicked()), this, SLOT (enter_name()));
}

DialogNewHighscore::~DialogNewHighscore()
{
    delete ui;
}

void DialogNewHighscore::enter_name()
{
    QString name = m_line_edit_name->text();
    if (name != "")
    {
        auto it = std::find_if(m_highscore_list.begin(), m_highscore_list.end(),
                     [](const auto& entry)
                    {
                        return entry.first == "NewHighscore";
                    });

        it->first = name.toStdString();
        save_highscore_list(m_highscore_list);
        close();
    }
}
