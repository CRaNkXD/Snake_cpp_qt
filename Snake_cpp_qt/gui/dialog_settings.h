#pragma once

#include <QDialog>

namespace Ui {
class DialogSettings;
}

class DialogSettings : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSettings(int current_speed, QWidget *parent = nullptr);
    ~DialogSettings();

    int get_game_time_speed_from_difficulty() const;
    
private:
    Ui::DialogSettings *ui;
};