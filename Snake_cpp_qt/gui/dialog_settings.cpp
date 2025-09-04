#include "dialog_settings.h"
#include "ui_dialog_settings.h"

#include <constants.h>



DialogSettings::DialogSettings(int current_speed, QWidget *parent)
    : QDialog(parent), ui(new Ui::DialogSettings)
{
    ui->setupUi(this);

    // Populate combo box with difficulty labels
    for (const auto& label : constants::DIFFICULTY_LABELS) {
        ui->m_cb_difficulty->addItem(QString::fromStdString(label));
    }

    // Find closest difficulty for current_speed
    int idx = 0;
    for (int i = 0; i < constants::NUMBER_OF_DIFFICULTIES; ++i) {
        if (current_speed >= constants::DIFFICULTY_SPEEDS[i]) {
            idx = i;
            break;
        }
    }
    ui->m_cb_difficulty->setCurrentIndex(idx);
}

DialogSettings::~DialogSettings()
{
    delete ui;
}

int DialogSettings::get_game_time_speed_from_difficulty() const
{
    return constants::DIFFICULTY_SPEEDS[ui->m_cb_difficulty->currentIndex()];
}