#include <iostream>
#include <algorithm>

#include <QDebug>

#include <snake.h>
#include <food.h>
#include <helper.h>
#include <constants.h>

#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent, const UShort &size_x, const UShort &size_y)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
    , m_settings{"CRaNkXD","Snake_cpp_qt"}
    , m_size_x{size_x}
    , m_size_y{size_y}
    , m_playing_field(m_size_x, std::vector<QLabel *>(m_size_y))
    , m_start_position(m_size_x / 2, m_size_y / 2)
    , m_snake(m_start_position, constants::Direction::RIGHT,
              4, m_size_x * m_size_y + 1)
    , m_food(rand_position(m_size_x - 1, m_size_y - 1), 100)
    , m_in_game{false}
    , m_won{false}
    , m_points{0}
    , m_key_buffer{}
{
    ui->setupUi(this);
    m_game_timer = new QTimer(this);
    m_game_timer_speed = m_settings.value("difficulty", constants::DIFFICULTY_SPEEDS[constants::DEFAULT_DIFFICULTY]).toInt();
    m_exit_menu = ui->actionExit_2;
    m_highscore_menu = ui->actionShow_Highscore;
    m_settings_menu = ui->actionShow_Settings;
    m_start_button = ui->btn_start;
    m_points_label = ui->label_points;
    display_points();

    for (UShort i = 0; i < m_size_x; ++i)
    {
        for (UShort j = 0; j < m_size_y; ++j)
        {
            QString field_name = "field_" + QString::number(i) + "_" +  QString::number(j);
            m_playing_field[i][j] = GameWindow::findChild<QLabel *>(field_name);
            m_playing_field[i][j]->setScaledContents(true);
            m_playing_field[i][j]->setPixmap(QPixmap(m_empty_field_icon_path));
        }
    }

    // Connect slots
    connect(m_game_timer, SIGNAL(timeout()), this, SLOT(update_game_state()));
    connect(m_start_button, SIGNAL(clicked()), this, SLOT(start_game()));
    connect(m_exit_menu, SIGNAL (triggered()), this, SLOT (close()));
    connect(m_highscore_menu, SIGNAL (triggered()), this, SLOT (show_highscore_list()));
    connect(m_settings_menu, SIGNAL(triggered()), this, SLOT(show_settings()));
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::add_points(const int &points)
{
    m_points += points;
}

void GameWindow::display_points() const
{
    QString points = QString::number(m_points);
    m_points_label->setText(points);
}

void GameWindow::start_game()
{
    m_in_game = true;
    m_game_timer->start(m_game_timer_speed);
}

void GameWindow::reset_game()
{
    m_in_game = false;
    m_key_buffer.clear();
    m_food.set_eaten(true);
    m_game_timer->stop();
    for (UShort i = 0; i < m_size_x; ++i)
    {
        for (UShort j = 0; j < m_size_y; ++j)
        {
            m_playing_field[i][j]->setPixmap(QPixmap(m_empty_field_icon_path));
        }
    }
    m_snake = Snake(m_start_position, constants::Direction::RIGHT, 4, m_size_x * m_size_y + 1);
    m_points = 0;
    display_points();
}

void GameWindow::display_game_state() const
{
    SnakeVec snake_vec = m_snake.get_snake();
    for (auto it_snake = snake_vec.begin();
         it_snake != snake_vec.begin() + m_snake.get_length();
         ++it_snake)
    {
        if (it_snake == snake_vec.begin())
        {
            switch (it_snake->get_direction())
            {
                case constants::Direction::UP:
                {
                    m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(m_snake_head_UP_icon_path));
                    break;
                }
                case constants::Direction::DOWN:
                {
                    m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(m_snake_head_DOWN_icon_path));
                    break;
                }
                case constants::Direction::LEFT:
                {
                    m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(m_snake_head_LEFT_icon_path));
                    break;
                }
                case constants::Direction::RIGHT:
                {
                    m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(m_snake_head_RIGHT_icon_path));
                    break;
                }
            }
        }
        else if (it_snake == snake_vec.begin() + m_snake.get_length() - 2)
        {
            switch (it_snake->get_direction())
            {
                case constants::Direction::UP:
                {
                    m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(m_snake_tail_UP_icon_path));
                    break;
                }
                case constants::Direction::DOWN:
                {
                    m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(m_snake_tail_DOWN_icon_path));
                    break;
                }
                case constants::Direction::LEFT:
                {
                    m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(m_snake_tail_LEFT_icon_path));
                    break;
                }
                case constants::Direction::RIGHT:
                {
                    m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(m_snake_tail_RIGHT_icon_path));
                    break;
                }
            }
        }
        // the last part is used to clean up the path behind the snake
        else if (it_snake == snake_vec.begin() + m_snake.get_length() - 1)
        {
            switch (it_snake->get_direction())
            {
                case constants::Direction::UP:
                {
                    m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(m_empty_field_icon_path));
                    break;
                }
                case constants::Direction::DOWN:
                {
                    m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(m_empty_field_icon_path));
                    break;
                }
                case constants::Direction::LEFT:
                {
                    m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(m_empty_field_icon_path));
                    break;
                }
                case constants::Direction::RIGHT:
                {
                    m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(m_empty_field_icon_path));
                    break;
                }
            }
        }
        else if (it_snake->get_direction() != std::next(it_snake)->get_direction())
        {
            // TODO: consider renaming the curve pics
            if (it_snake->get_direction() == constants::Direction::UP)
            {
                if (std::next(it_snake)->get_direction() == constants::Direction::RIGHT)
                {
                    m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(m_snake_body_curve_UP_LEFT_icon_path));
                }
                else
                {
                    m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(m_snake_body_curve_UP_RIGHT_icon_path));
                }
            }
            else if (it_snake->get_direction() == constants::Direction::DOWN)
            {
                if (std::next(it_snake)->get_direction() == constants::Direction::RIGHT)
                {
                    m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(m_snake_body_curve_DOWN_LEFT_icon_path));
                }
                else
                {
                    m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(m_snake_body_curve_DOWN_RIGHT_icon_path));
                }
            }
            else if (it_snake->get_direction() == constants::Direction::LEFT)
            {
                if (std::next(it_snake)->get_direction() == constants::Direction::UP)
                {
                    m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(m_snake_body_curve_DOWN_LEFT_icon_path));
                }
                else
                {
                    m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(m_snake_body_curve_UP_LEFT_icon_path));
                }
            }
            else if (it_snake->get_direction() == constants::Direction::RIGHT)
            {
                if (std::next(it_snake)->get_direction() == constants::Direction::UP)
                {
                    m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(m_snake_body_curve_DOWN_RIGHT_icon_path));
                }
                else
                {
                    m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(m_snake_body_curve_UP_RIGHT_icon_path));
                }
            }
        }
        else if (it_snake->get_direction() == std::next(it_snake)->get_direction())
        {
            switch (it_snake->get_direction())
            {
                case constants::Direction::UP:
                {
                    m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(m_snake_body_vertical_icon_path));
                    break;
                }
                case constants::Direction::DOWN:
                {
                    m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(m_snake_body_vertical_icon_path));
                    break;
                }
                case constants::Direction::LEFT:
                {
                    m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(m_snake_body_horizontal_icon_path));
                    break;
                }
                case constants::Direction::RIGHT:
                {
                    m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(m_snake_body_horizontal_icon_path));
                    break;
                }
            }
        }
    }
}

void GameWindow::update_game_state()
{
    if (!m_key_buffer.empty())
    {
        constants::Direction current_direction{m_snake.get_front_direction()};
        constants::Direction next_direction{m_key_buffer.front()};
        switch(next_direction)
        {
            case constants::Direction::UP:
            {
                if (current_direction != constants::Direction::DOWN)
                    m_snake.set_front_direction(next_direction);
                break;
            }
            case constants::Direction::LEFT:
            {
                if (current_direction != constants::Direction::RIGHT)
                    m_snake.set_front_direction(next_direction);
                break;
            }
            case constants::Direction::RIGHT:
            {
                if (current_direction != constants::Direction::LEFT)
                    m_snake.set_front_direction(next_direction);
                break;
            }
            case constants::Direction::DOWN:
            {
                if (current_direction != constants::Direction::UP)
                    m_snake.set_front_direction(next_direction);
                break;
            }
        }
        m_key_buffer.pop_front();
    }
    m_snake.move();
    if (snake_hit_snake(m_snake) ||
        snake_hit_wall(m_snake, m_size_x, m_size_y))
    {
        if (is_new_highscore(m_points))
        {
            m_dialog_new_highscore = new DialogNewHighscore(m_points, this);
            m_dialog_new_highscore->setAttribute(Qt::WA_DeleteOnClose);
            m_dialog_new_highscore->show();
        }
        else
        {
            show_highscore_list();
        }
        reset_game();
    }
    else
    {
        if (snake_ate_food(m_snake, m_food))
        {
            m_snake.add_part();
            add_points(m_food.get_points());
            display_points();
            m_food.set_eaten(true);
            if (m_snake.get_length() == m_size_x * m_size_y)
            {
                m_won = true;
            }
        }

        if (!m_won)
        {
            if (m_food.is_eaten())
            {
                // Collect all free positions into a vector, then randomly select one
                std::vector<Position> free_positions;
                for (UShort x = 0; x < m_size_x; ++x) {
                    for (UShort y = 0; y < m_size_y; ++y) {
                        Position pos(x, y);
                        if (!m_snake.is_occupied(pos)) {
                            free_positions.push_back(pos);
                        }
                    }
                }
                if (!free_positions.empty()) {
                    m_food.set_position(get_rand_position_from_vector(free_positions));
                }
                else{
                    // This should not happen as we check for win condition above
                    m_food.set_position(rand_position(m_size_x - 1, m_size_y - 1));
                }
                m_food.set_eaten(false);
            }
            m_playing_field[m_food.get_position().first][m_food.get_position().second]->setPixmap(QPixmap(m_food_icon_path));

            display_game_state();
        }
        else
        {
            reset_game();
            // TODO: show you have won message
        }

    }
}

void GameWindow::new_game()
{

}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    if (m_in_game)
    {
        switch(event->key())
        {
            case Qt::Key_W:
            {
                m_key_buffer.push_back(constants::Direction::UP);
                break;
            }
            case Qt::Key_A:
            {
                m_key_buffer.push_back(constants::Direction::LEFT);
                break;
            }
            case Qt::Key_S:
            {
                m_key_buffer.push_back(constants::Direction::DOWN);
                break;
            }
            case Qt::Key_D:
            {
                m_key_buffer.push_back(constants::Direction::RIGHT);
                break;
            }
            default:
            {
                return;
            }
        }
    }
}

void GameWindow::show_settings()
{
    m_dialog_settings = new DialogSettings(m_game_timer_speed, this);
    if (m_dialog_settings->exec() == QDialog::Accepted) {
        m_game_timer_speed = m_dialog_settings->get_game_time_speed_from_difficulty();
        m_game_timer->setInterval(m_game_timer_speed);
        m_settings.setValue("difficulty", m_game_timer_speed);
    }
}

void GameWindow::show_highscore_list()
{
    m_dialog_highscore = new dialog_highscore(this);
    m_dialog_highscore->setAttribute(Qt::WA_DeleteOnClose);
    m_dialog_highscore->show();
}
