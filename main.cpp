#include "src/window.h"
#include "resources/ss.cpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Window win;
    win.show();

    return app.exec();
}