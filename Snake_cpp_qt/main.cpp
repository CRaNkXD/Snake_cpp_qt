#include "gamewindow.h"
#include <helper.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    // init highscore list
    std::vector<std::pair<std::string, std::string>> highscore_list;
    save_highscore_list(highscore_list);

    QApplication a(argc, argv);
    GameWindow w;
    w.show();
    return a.exec();
}
