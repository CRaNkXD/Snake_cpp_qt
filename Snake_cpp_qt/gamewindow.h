#pragma once
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QKeyEvent>

#include <vector>

#include "model/snake.h"
#include "model/food.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

typedef std::vector<std::vector<QLabel *>> PlayingField;

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr, const UShort &size_x = 20, const UShort &size_y = 20);
    ~GameWindow();
    void add_points(const int &points);
    void display_points();
    void reset_game();
    void display_game_state();

private:
    Ui::GameWindow *ui;
    QAction *m_exit_menu;
    QPushButton *m_start_button;
    QLabel *m_points_label;
    UShort m_size_x;
    UShort m_size_y;
    PlayingField m_playing_field;
    Position m_start_position;
    Snake m_snake;
    Food m_food;
    bool m_in_game;
    bool m_game_updated;
    bool m_won;
    int m_points;
    QTimer *m_game_timer;
    QString m_snake_body_horizontal_icon_path = ":/pics/snake/snake_body_horizontal.png";
    QString m_snake_body_vertical_icon_path = ":/pics/snake/snake_body_vertical.png";
    QString m_snake_head_UP_icon_path = ":/pics/snake/snake_head_UP.png";
    QString m_snake_head_DOWN_icon_path = ":/pics/snake/snake_head_DOWN.png";
    QString m_snake_head_LEFT_icon_path = ":/pics/snake/snake_head_LEFT.png";
    QString m_snake_head_RIGHT_icon_path = ":/pics/snake/snake_head_RIGHT.png";
    QString m_snake_tail_UP_icon_path = ":/pics/snake/snake_tail_UP.png";
    QString m_snake_tail_DOWN_icon_path = ":/pics/snake/snake_tail_DOWN.png";
    QString m_snake_tail_LEFT_icon_path = ":/pics/snake/snake_tail_LEFT.png";
    QString m_snake_tail_RIGHT_icon_path = ":/pics/snake/snake_tail_RIGHT.png";
    QString m_snake_body_curve_DOWN_LEFT_icon_path = ":/pics/snake/snake_body_curve_DOWN_LEFT.png";
    QString m_snake_body_curve_DOWN_RIGHT_icon_path = ":/pics/snake/snake_body_curve_DOWN_RIGHT.png";
    QString m_snake_body_curve_UP_LEFT_icon_path = ":/pics/snake/snake_body_curve_UP_LEFT.png";
    QString m_snake_body_curve_UP_RIGHT_icon_path = ":/pics/snake/snake_body_curve_UP_RIGHT.png";
    QString m_empty_field_icon_path = ":/pics/snake/empty_field.png";
    QString m_food_icon_path = ":/pics/snake/food.png";

private slots:
    void start_game();
    void show_highscore();
    void new_game();
    void keyPressEvent(QKeyEvent *event) override;
    void show_settings();
    void update_game_state();

};
