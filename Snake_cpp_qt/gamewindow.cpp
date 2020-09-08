#include <iostream>
#include <algorithm>

#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "model/snake.h"
#include "model/food.h"
#include "helper/helper.h"
#include "constants/constants.h"

GameWindow::GameWindow(QWidget *parent, const UShort &size_x, const UShort &size_y)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
    , m_size_x(size_x)
    , m_size_y(size_y)
    , m_playing_field(m_size_x, std::vector<QLabel *>(this->m_size_y))
    , m_start_position(this->m_size_x / 2, this->m_size_y / 2)
    , m_snake(this->m_start_position, constants::Direction::RIGHT,
              4, this->m_size_x * this->m_size_y + 1)
    , m_in_game(false)
    , m_game_updated(true)
    , m_won(false)
    , m_points(0)
{
    ui->setupUi(this);
    this->m_game_timer = new QTimer(this);
    this->m_exit_menu = ui->actionExit_3;
    this->m_start_button = ui->btn_start;
    this->m_points_label = ui->label_points;
    this->display_points();

    // init food with eaten so that the first food will be generated
    this->m_food.eaten = true;

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
    connect(m_game_timer, SIGNAL(timeout()), this, SLOT(update_game_state()));
    connect(m_start_button, SIGNAL(clicked()), this, SLOT(start_game()));
    connect(m_exit_menu, SIGNAL (triggered()), this, SLOT (close()));
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
    this->m_game_updated = false;
    this->m_food.eaten = true;
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
            switch (it_snake->direction)
            {
                case constants::Direction::UP:
                {
                    this->m_playing_field[it_snake->position.first][it_snake->position.second]->setPixmap(QPixmap(this->m_snake_head_UP_icon_path));
                    break;
                }
                case constants::Direction::DOWN:
                {
                    this->m_playing_field[it_snake->position.first][it_snake->position.second]->setPixmap(QPixmap(this->m_snake_head_DOWN_icon_path));
                    break;
                }
                case constants::Direction::LEFT:
                {
                    this->m_playing_field[it_snake->position.first][it_snake->position.second]->setPixmap(QPixmap(this->m_snake_head_LEFT_icon_path));
                    break;
                }
                case constants::Direction::RIGHT:
                {
                    this->m_playing_field[it_snake->position.first][it_snake->position.second]->setPixmap(QPixmap(this->m_snake_head_RIGHT_icon_path));
                    break;
                }
            }
        }
        else if (it_snake == snake_vec.begin() + this->m_snake.get_length() - 2)
        {
            switch (it_snake->direction)
            {
                case constants::Direction::UP:
                {
                    this->m_playing_field[it_snake->position.first][it_snake->position.second]->setPixmap(QPixmap(this->m_snake_tail_UP_icon_path));
                    break;
                }
                case constants::Direction::DOWN:
                {
                    this->m_playing_field[it_snake->position.first][it_snake->position.second]->setPixmap(QPixmap(this->m_snake_tail_DOWN_icon_path));
                    break;
                }
                case constants::Direction::LEFT:
                {
                    this->m_playing_field[it_snake->position.first][it_snake->position.second]->setPixmap(QPixmap(this->m_snake_tail_LEFT_icon_path));
                    break;
                }
                case constants::Direction::RIGHT:
                {
                    this->m_playing_field[it_snake->position.first][it_snake->position.second]->setPixmap(QPixmap(this->m_snake_tail_RIGHT_icon_path));
                    break;
                }
            }
        }
        // the last part is used to clean up the path behind the snake
        else if (it_snake == snake_vec.begin() + this->m_snake.get_length() - 1)
        {
            switch (it_snake->direction)
            {
                case constants::Direction::UP:
                {
                    this->m_playing_field[it_snake->position.first][it_snake->position.second]->setPixmap(QPixmap(this->m_empty_field_icon_path));
                    break;
                }
                case constants::Direction::DOWN:
                {
                    this->m_playing_field[it_snake->position.first][it_snake->position.second]->setPixmap(QPixmap(this->m_empty_field_icon_path));
                    break;
                }
                case constants::Direction::LEFT:
                {
                    this->m_playing_field[it_snake->position.first][it_snake->position.second]->setPixmap(QPixmap(this->m_empty_field_icon_path));
                    break;
                }
                case constants::Direction::RIGHT:
                {
                    this->m_playing_field[it_snake->position.first][it_snake->position.second]->setPixmap(QPixmap(this->m_empty_field_icon_path));
                    break;
                }
            }
        }
        else if (it_snake->direction != std::next(it_snake)->direction)
        {
            // TODO: consider renaming the curve pics
            if (it_snake->direction == constants::Direction::UP)
            {
                if (std::next(it_snake)->direction == constants::Direction::RIGHT)
                {
                    this->m_playing_field[it_snake->position.first][it_snake->position.second]->setPixmap(QPixmap(this->m_snake_body_curve_UP_LEFT_icon_path));
                }
                else
                {
                    this->m_playing_field[it_snake->position.first][it_snake->position.second]->setPixmap(QPixmap(this->m_snake_body_curve_UP_RIGHT_icon_path));
                }
            }
            else if (it_snake->direction == constants::Direction::DOWN)
            {
                if (std::next(it_snake)->direction == constants::Direction::RIGHT)
                {
                    this->m_playing_field[it_snake->position.first][it_snake->position.second]->setPixmap(QPixmap(this->m_snake_body_curve_DOWN_LEFT_icon_path));
                }
                else
                {
                    this->m_playing_field[it_snake->position.first][it_snake->position.second]->setPixmap(QPixmap(this->m_snake_body_curve_DOWN_RIGHT_icon_path));
                }
            }
            else if (it_snake->direction == constants::Direction::LEFT)
            {
                if (std::next(it_snake)->direction == constants::Direction::UP)
                {
                    this->m_playing_field[it_snake->position.first][it_snake->position.second]->setPixmap(QPixmap(this->m_snake_body_curve_DOWN_LEFT_icon_path));
                }
                else
                {
                    this->m_playing_field[it_snake->position.first][it_snake->position.second]->setPixmap(QPixmap(this->m_snake_body_curve_UP_LEFT_icon_path));
                }
            }
            else if (it_snake->direction == constants::Direction::RIGHT)
            {
                if (std::next(it_snake)->direction == constants::Direction::UP)
                {
                    this->m_playing_field[it_snake->position.first][it_snake->position.second]->setPixmap(QPixmap(this->m_snake_body_curve_DOWN_RIGHT_icon_path));
                }
                else
                {
                    this->m_playing_field[it_snake->position.first][it_snake->position.second]->setPixmap(QPixmap(this->m_snake_body_curve_UP_RIGHT_icon_path));
                }
            }
        }
        else if (it_snake->direction == std::next(it_snake)->direction)
        {
            switch (it_snake->direction)
            {
                case constants::Direction::UP:
                {
                    this->m_playing_field[it_snake->position.first][it_snake->position.second]->setPixmap(QPixmap(this->m_snake_body_vertical_icon_path));
                    break;
                }
                case constants::Direction::DOWN:
                {
                    this->m_playing_field[it_snake->position.first][it_snake->position.second]->setPixmap(QPixmap(this->m_snake_body_vertical_icon_path));
                    break;
                }
                case constants::Direction::LEFT:
                {
                    this->m_playing_field[it_snake->position.first][it_snake->position.second]->setPixmap(QPixmap(this->m_snake_body_horizontal_icon_path));
                    break;
                }
                case constants::Direction::RIGHT:
                {
                    this->m_playing_field[it_snake->position.first][it_snake->position.second]->setPixmap(QPixmap(this->m_snake_body_horizontal_icon_path));
                    break;
                }
            }
        }
    }
}

void GameWindow::update_game_state()
{
    this->m_snake.move();
    if (snake_hit_snake(this->m_snake) ||
        snake_hit_wall(this->m_snake, this->m_size_x, this->m_size_y))
    {
        this->reset_game();
        // TODO: show highscore list if and prompt input if a new highscore was set
    }
    else
    {
        if (snake_ate_food(this->m_snake, this->m_food))
        {
            this->m_snake.add_part();
            this->add_points(this->m_food.points);
            this->display_points();
            this->m_food.eaten = true;
            if (this->m_snake.get_length() == this->m_size_x * this->m_size_y)
            {
                this->m_won = true;
            }
        }

        if (!this->m_won)
        {
            if (this->m_food.eaten)
            {
                do{
                    this->m_food.position = rand_position(this->m_size_x - 1, this->m_size_y - 1);
                } while(this->m_snake.is_occupied(this->m_food.position));
                this->m_food.eaten = false;
            }
            this->m_playing_field[this->m_food.position.first][this->m_food.position.second]->setPixmap(QPixmap(this->m_food_icon_path));

            this->display_game_state();
            this->m_game_updated = true;
        }
        else
        {
            this->reset_game();
            // TODO: show you have won message
        }

    }
}

void GameWindow::show_highscore()
{

}

void GameWindow::new_game()
{

}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    if (this->m_in_game && this->m_game_updated)
    {
        constants::Direction current_direction = this->m_snake.get_front_direction();
        switch(event->key())
        {
            case Qt::Key_W:
            {
                if (current_direction != constants::Direction::DOWN)
                    this->m_snake.set_front_direction(constants::Direction::UP);
                break;
            }
            case Qt::Key_A:
            {
                if (current_direction != constants::Direction::RIGHT)
                    this->m_snake.set_front_direction(constants::Direction::LEFT);
                break;
            }
            case Qt::Key_S:
            {
                if (current_direction != constants::Direction::UP)
                    this->m_snake.set_front_direction(constants::Direction::DOWN);
                break;
            }
            case Qt::Key_D:
            {
                if (current_direction != constants::Direction::LEFT)
                    this->m_snake.set_front_direction(constants::Direction::RIGHT);
                break;
            }
            default:
            {
                return;
            }
        }
        this->m_game_updated = false;
    }
}

void GameWindow::show_settings()
{

}
