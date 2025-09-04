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
    , m_size_x{size_x}
    , m_size_y{size_y}
    , m_playing_field(m_size_x, std::vector<QLabel *>(this->m_size_y))
    , m_start_position(this->m_size_x / 2, this->m_size_y / 2)
    , m_snake(this->m_start_position, constants::Direction::RIGHT,
              4, this->m_size_x * this->m_size_y + 1)
    , m_food(rand_position(this->m_size_x - 1, this->m_size_y - 1), 100)
    , m_in_game{false}
    , m_won{false}
    , m_points{0}
    , m_key_buffer{}
{
    ui->setupUi(this);
    this->m_game_timer = new QTimer(this);
    this->m_exit_menu = ui->actionExit_2;
    this->m_highscore_menu = ui->actionShow_Highscore;
    this->m_start_button = ui->btn_start;
    this->m_points_label = ui->label_points;
    this->display_points();

    for (UShort i = 0; i < this->m_size_x; ++i)
    {
        for (UShort j = 0; j < this->m_size_y; ++j)
        {
            QString field_name = "field_" + QString::number(i) + "_" +  QString::number(j);
            this->m_playing_field[i][j] = GameWindow::findChild<QLabel *>(field_name);
            this->m_playing_field[i][j]->setScaledContents(true);
            this->m_playing_field[i][j]->setPixmap(QPixmap(this->m_empty_field_icon_path));
        }
    }

    // Connect slots
    connect(this->m_game_timer, SIGNAL(timeout()), this, SLOT(update_game_state()));
    connect(this->m_start_button, SIGNAL(clicked()), this, SLOT(start_game()));
    connect(this->m_exit_menu, SIGNAL (triggered()), this, SLOT (close()));
    connect(this->m_highscore_menu, SIGNAL (triggered()), this, SLOT (show_highscore_list()));
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::add_points(const int &points)
{
    this->m_points += points;
}

void GameWindow::display_points()
{
    QString points = QString::number(this->m_points);
    this->m_points_label->setText(points);
}

void GameWindow::start_game()
{
    this->m_in_game = true;
    this->m_game_timer->start(150);
}

void GameWindow::reset_game()
{
    this->m_in_game = false;
    this->m_key_buffer.clear();
    this->m_food.set_eaten(true);
    this->m_game_timer->stop();
    for (UShort i = 0; i < this->m_size_x; ++i)
    {
        for (UShort j = 0; j < this->m_size_y; ++j)
        {
            this->m_playing_field[i][j]->setPixmap(QPixmap(this->m_empty_field_icon_path));
        }
    }
    this->m_snake = Snake(this->m_start_position, constants::Direction::RIGHT, 4, this->m_size_x * this->m_size_y + 1);
    this->m_points = 0;
    this->display_points();
}

void GameWindow::display_game_state()
{
    SnakeVec snake_vec = this->m_snake.get_snake();
    for (auto it_snake = snake_vec.begin();
         it_snake != snake_vec.begin() + this->m_snake.get_length();
         ++it_snake)
    {
        if (it_snake == snake_vec.begin())
        {
            switch (it_snake->get_direction())
            {
                case constants::Direction::UP:
                {
                    this->m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(this->m_snake_head_UP_icon_path));
                    break;
                }
                case constants::Direction::DOWN:
                {
                    this->m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(this->m_snake_head_DOWN_icon_path));
                    break;
                }
                case constants::Direction::LEFT:
                {
                    this->m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(this->m_snake_head_LEFT_icon_path));
                    break;
                }
                case constants::Direction::RIGHT:
                {
                    this->m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(this->m_snake_head_RIGHT_icon_path));
                    break;
                }
            }
        }
        else if (it_snake == snake_vec.begin() + this->m_snake.get_length() - 2)
        {
            switch (it_snake->get_direction())
            {
                case constants::Direction::UP:
                {
                    this->m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(this->m_snake_tail_UP_icon_path));
                    break;
                }
                case constants::Direction::DOWN:
                {
                    this->m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(this->m_snake_tail_DOWN_icon_path));
                    break;
                }
                case constants::Direction::LEFT:
                {
                    this->m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(this->m_snake_tail_LEFT_icon_path));
                    break;
                }
                case constants::Direction::RIGHT:
                {
                    this->m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(this->m_snake_tail_RIGHT_icon_path));
                    break;
                }
            }
        }
        // the last part is used to clean up the path behind the snake
        else if (it_snake == snake_vec.begin() + this->m_snake.get_length() - 1)
        {
            switch (it_snake->get_direction())
            {
                case constants::Direction::UP:
                {
                    this->m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(this->m_empty_field_icon_path));
                    break;
                }
                case constants::Direction::DOWN:
                {
                    this->m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(this->m_empty_field_icon_path));
                    break;
                }
                case constants::Direction::LEFT:
                {
                    this->m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(this->m_empty_field_icon_path));
                    break;
                }
                case constants::Direction::RIGHT:
                {
                    this->m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(this->m_empty_field_icon_path));
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
                    this->m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(this->m_snake_body_curve_UP_LEFT_icon_path));
                }
                else
                {
                    this->m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(this->m_snake_body_curve_UP_RIGHT_icon_path));
                }
            }
            else if (it_snake->get_direction() == constants::Direction::DOWN)
            {
                if (std::next(it_snake)->get_direction() == constants::Direction::RIGHT)
                {
                    this->m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(this->m_snake_body_curve_DOWN_LEFT_icon_path));
                }
                else
                {
                    this->m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(this->m_snake_body_curve_DOWN_RIGHT_icon_path));
                }
            }
            else if (it_snake->get_direction() == constants::Direction::LEFT)
            {
                if (std::next(it_snake)->get_direction() == constants::Direction::UP)
                {
                    this->m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(this->m_snake_body_curve_DOWN_LEFT_icon_path));
                }
                else
                {
                    this->m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(this->m_snake_body_curve_UP_LEFT_icon_path));
                }
            }
            else if (it_snake->get_direction() == constants::Direction::RIGHT)
            {
                if (std::next(it_snake)->get_direction() == constants::Direction::UP)
                {
                    this->m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(this->m_snake_body_curve_DOWN_RIGHT_icon_path));
                }
                else
                {
                    this->m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(this->m_snake_body_curve_UP_RIGHT_icon_path));
                }
            }
        }
        else if (it_snake->get_direction() == std::next(it_snake)->get_direction())
        {
            switch (it_snake->get_direction())
            {
                case constants::Direction::UP:
                {
                    this->m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(this->m_snake_body_vertical_icon_path));
                    break;
                }
                case constants::Direction::DOWN:
                {
                    this->m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(this->m_snake_body_vertical_icon_path));
                    break;
                }
                case constants::Direction::LEFT:
                {
                    this->m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(this->m_snake_body_horizontal_icon_path));
                    break;
                }
                case constants::Direction::RIGHT:
                {
                    this->m_playing_field[it_snake->get_position().first][it_snake->get_position().second]->setPixmap(QPixmap(this->m_snake_body_horizontal_icon_path));
                    break;
                }
            }
        }
    }
}

void GameWindow::update_game_state()
{
    if (!this->m_key_buffer.empty())
    {
        constants::Direction current_direction{this->m_snake.get_front_direction()};
        constants::Direction next_direction{this->m_key_buffer.front()};
        switch(next_direction)
        {
            case constants::Direction::UP:
            {
                if (current_direction != constants::Direction::DOWN)
                    this->m_snake.set_front_direction(next_direction);
                break;
            }
            case constants::Direction::LEFT:
            {
                if (current_direction != constants::Direction::RIGHT)
                    this->m_snake.set_front_direction(next_direction);
                break;
            }
            case constants::Direction::RIGHT:
            {
                if (current_direction != constants::Direction::LEFT)
                    this->m_snake.set_front_direction(next_direction);
                break;
            }
            case constants::Direction::DOWN:
            {
                if (current_direction != constants::Direction::UP)
                    this->m_snake.set_front_direction(next_direction);
                break;
            }
        }
        this->m_key_buffer.pop_front();
    }
    this->m_snake.move();
    if (snake_hit_snake(this->m_snake) ||
        snake_hit_wall(this->m_snake, this->m_size_x, this->m_size_y))
    {
        if (is_new_highscore(this->m_points))
        {
            this->m_dialog_new_highscore = new DialogNewHighscore(this->m_points, this);
            this->m_dialog_new_highscore->setAttribute(Qt::WA_DeleteOnClose);
            this->m_dialog_new_highscore->show();
        }
        else
        {
            show_highscore_list();
        }
        this->reset_game();
    }
    else
    {
        if (snake_ate_food(this->m_snake, this->m_food))
        {
            this->m_snake.add_part();
            this->add_points(this->m_food.get_points());
            this->display_points();
            this->m_food.set_eaten(true);
            if (this->m_snake.get_length() == this->m_size_x * this->m_size_y)
            {
                this->m_won = true;
            }
        }

        if (!this->m_won)
        {
            if (this->m_food.is_eaten())
            {
                // Collect all free positions into a vector, then randomly select one
                std::vector<Position> free_positions;
                for (UShort x = 0; x < this->m_size_x; ++x) {
                    for (UShort y = 0; y < this->m_size_y; ++y) {
                        Position pos(x, y);
                        if (!this->m_snake.is_occupied(pos)) {
                            free_positions.push_back(pos);
                        }
                    }
                }
                if (!free_positions.empty()) {
                    this->m_food.set_position(get_rand_position_from_vector(free_positions));
                }
                else{
                    // This should not happen as we check for win condition above
                    this->m_food.set_position(rand_position(this->m_size_x - 1, this->m_size_y - 1));
                }
                this->m_food.set_eaten(false);
            }
            this->m_playing_field[this->m_food.get_position().first][this->m_food.get_position().second]->setPixmap(QPixmap(this->m_food_icon_path));

            this->display_game_state();
        }
        else
        {
            this->reset_game();
            // TODO: show you have won message
        }

    }
}

void GameWindow::new_game()
{

}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    if (this->m_in_game)
    {
        switch(event->key())
        {
            case Qt::Key_W:
            {
                this->m_key_buffer.push_back(constants::Direction::UP);
                break;
            }
            case Qt::Key_A:
            {
                this->m_key_buffer.push_back(constants::Direction::LEFT);
                break;
            }
            case Qt::Key_S:
            {
                this->m_key_buffer.push_back(constants::Direction::DOWN);
                break;
            }
            case Qt::Key_D:
            {
                this->m_key_buffer.push_back(constants::Direction::RIGHT);
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

}

void GameWindow::show_highscore_list()
{
    this->m_dialog_highscore = new dialog_highscore(this);
    this->m_dialog_highscore->setAttribute(Qt::WA_DeleteOnClose);
    this->m_dialog_highscore->show();
}
