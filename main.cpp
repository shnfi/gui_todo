#include <iostream>

#include <QApplication>
#include <QWidget>
#include <QString>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>

#include "ss.cpp"

struct WIN_INF_ST
{
    const QString TITLE = "Todo";
    const unsigned int WIDTH = 1000;
    const unsigned int HEIGHT = 600;
} WIN_INF;

class Window : public QWidget
{
private:
    QVBoxLayout *middle_bar_layout;
    QLineEdit *todo_field;

public:
    Window(QWidget *parent = nullptr) : QWidget(parent)
    {
        // window settings 
        
        setWindowTitle(WIN_INF.TITLE);
        setFixedSize(WIN_INF.WIDTH, WIN_INF.HEIGHT);

        setStyleSheet(main_SS);

        // main container

        QVBoxLayout *container = new QVBoxLayout(this);

        // top bar 

        QWidget *top_bar = new QWidget();
        top_bar->setObjectName("bar");
        top_bar->setStyleSheet(bar_SS);

        QHBoxLayout *top_bar_layout = new QHBoxLayout(top_bar);

        todo_field = new QLineEdit();
        
        todo_field->setStyleSheet(todo_field_SS);

        QPushButton *todo_button = new QPushButton("Add");

        todo_button->setStyleSheet(todo_button_SS);

        connect(todo_button, &QPushButton::clicked, this, &Window::add_todo);
        
        top_bar_layout->addSpacerItem(new QSpacerItem(5, 5));
        top_bar_layout->addWidget(todo_field, 8);
        top_bar_layout->addWidget(todo_button, 1);
        top_bar_layout->addSpacerItem(new QSpacerItem(5, 5));
        container->addWidget(top_bar);

        // middle bar
        
        QWidget *middle_bar = new QWidget();
        middle_bar->setObjectName("bar");
        middle_bar->setStyleSheet(bar_SS);

        middle_bar_layout = new QVBoxLayout(middle_bar);

        middle_bar_layout->addStretch();

        container->addWidget(middle_bar);

        // bottom bar
        
        QWidget *bottom_bar = new QWidget();
        bottom_bar->setObjectName("bar");
        bottom_bar->setStyleSheet(bar_SS);

        QHBoxLayout *bottom_bar_layout = new QHBoxLayout(bottom_bar);

        QLabel *music_name_label = new QLabel("Music name");
        music_name_label->setStyleSheet(music_name_label_SS);

        bottom_bar_layout->addSpacerItem(new QSpacerItem(20, 20));
        bottom_bar_layout->addWidget(music_name_label);

        bottom_bar_layout->addStretch();

        QWidget *music_control_widget = new QWidget();
        QHBoxLayout *music_control_layout = new QHBoxLayout(music_control_widget);

        QPushButton *play_music = new QPushButton("P");
        QPushButton *stop_music = new QPushButton("S");

        play_music->setStyleSheet(control_music_button_SS);
        stop_music->setStyleSheet(control_music_button_SS);

        music_control_layout->addWidget(play_music);
        music_control_layout->addSpacerItem(new QSpacerItem(5, 5));
        music_control_layout->addWidget(stop_music);
        music_control_layout->addSpacerItem(new QSpacerItem(10, 10));

        bottom_bar_layout->addWidget(music_control_widget);

        container->addWidget(bottom_bar);

        // container settings

        container->setStretch(0, 1);
        container->setStretch(1, 8);
        container->setStretch(2, 1);

        setLayout(container);
    }

    void add_todo()
    {
        QWidget *todo_container = new QWidget();
        todo_container->setFixedHeight(50);
        todo_container->setObjectName("todo_container");
        todo_container->setStyleSheet(todo_container_SS);

        QHBoxLayout *todo_container_label_box = new QHBoxLayout(todo_container);

        QLabel *todo_label = new QLabel(todo_field->text());
        todo_label->setStyleSheet(todo_label_SS);
        todo_field->clear();

        QPushButton *remove_todo_button = new QPushButton("");
        remove_todo_button->setFixedWidth(30);
        remove_todo_button->setStyleSheet(remove_todo_button_SS);

        connect(remove_todo_button, &QPushButton::clicked, this, [=]() { remove_todo(todo_container); });

        todo_container_label_box->addSpacerItem(new QSpacerItem(5, 5));
        todo_container_label_box->addWidget(todo_label);
        todo_container_label_box->addWidget(remove_todo_button);
        todo_container_label_box->addSpacerItem(new QSpacerItem(5, 5));

        middle_bar_layout->insertWidget(0, todo_container);
    }

    void remove_todo(QWidget *tc)
    {
        middle_bar_layout->removeWidget(tc);
        tc->deleteLater();
        tc = nullptr;
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Window win;
    win.show();

    return app.exec();
}