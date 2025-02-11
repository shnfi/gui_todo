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
#include <QPropertyAnimation>
#include <QTimer>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <QMessageBox>

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
    QMediaPlayer *player;
    QAudioOutput *output;
    QPushButton *play_music_button;
    QPushButton *pause_music_button;

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

        // audio widget

        player = new QMediaPlayer(this);
        output = new QAudioOutput();

        output->setVolume(0.25);

        player->setAudioOutput(output);
        player->setSource(QUrl::fromLocalFile("audio/background_music.mp3"));

        connect(player, &QMediaPlayer::mediaStatusChanged, this, &Window::play_again);

        // bottom bar
        
        QWidget *bottom_bar = new QWidget();
        bottom_bar->setObjectName("bar");
        bottom_bar->setStyleSheet(bar_SS);

        QHBoxLayout *bottom_bar_layout = new QHBoxLayout(bottom_bar);

        QLabel *music_name_label = new QLabel("Automn Story");
        music_name_label->setStyleSheet(music_name_label_SS);

        bottom_bar_layout->addSpacerItem(new QSpacerItem(20, 20));
        bottom_bar_layout->addWidget(music_name_label);

        bottom_bar_layout->addStretch();

        QWidget *music_control_widget = new QWidget();
        QHBoxLayout *music_control_layout = new QHBoxLayout(music_control_widget);

        play_music_button = new QPushButton("P");
        pause_music_button = new QPushButton("S");

        connect(play_music_button, &QPushButton::clicked, this, &Window::play_music );
        connect(pause_music_button, &QPushButton::clicked, this, &Window::pause_music );

        play_music_button->setStyleSheet(control_music_button_SS);
        pause_music_button->setStyleSheet(control_music_button_SS);

        play_music();

        music_control_layout->addWidget(play_music_button);
        music_control_layout->addSpacerItem(new QSpacerItem(5, 5));
        music_control_layout->addWidget(pause_music_button);
        music_control_layout->addSpacerItem(new QSpacerItem(10, 10));

        bottom_bar_layout->addWidget(music_control_widget);

        container->addWidget(bottom_bar);

        // container settings

        container->setStretch(0, 1);
        container->setStretch(1, 8);
        container->setStretch(2, 1);

        setLayout(container);
    }

private:
    void add_todo()
    {
        if (todo_field->text() == "")
        {
            QMessageBox *error_msgbox = new QMessageBox(this);
            error_msgbox->setWindowTitle("FILL THE FIELD");
            error_msgbox->setIcon(QMessageBox::Information);
            error_msgbox->setText("Write something in the field!");
            error_msgbox->setInformativeText("The todo title's field must not be empty!");
            error_msgbox->setStandardButtons(QMessageBox::Ok);
            error_msgbox->exec();
        }
        else
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
    }

    void remove_todo(QWidget *tc)
    {
        tc->setStyleSheet(removing_todo_container_SS);

        startAnimation(tc);

        QMediaPlayer *d_player = new QMediaPlayer(this);
        QAudioOutput *d_output = new QAudioOutput();

        d_output->setVolume(0.35);

        d_player->setAudioOutput(d_output);
        d_player->setSource(QUrl::fromLocalFile("audio/todo_removing_sound.mp3"));

        d_player->play();

        QTimer::singleShot(300, this, [=]() {
            middle_bar_layout->removeWidget(tc);
            tc->deleteLater();
        });
    }

    void startAnimation(QWidget *mw)
    {
        QPropertyAnimation *animation = new QPropertyAnimation(mw, "pos", this);

        animation->setStartValue(mw->pos());
        animation->setEndValue(QPoint(1000, mw->pos().y()));

        animation->setEasingCurve(QEasingCurve::InOutQuad);

        animation->setDuration(200);

        animation->start();
    }

    void play_music()
    {
        player->play();

        play_music_button->setEnabled(false);
        pause_music_button->setEnabled(true);

        play_music_button->setStyleSheet(disabled_control_music_button_SS);
        pause_music_button->setStyleSheet(control_music_button_SS);
    }

    void pause_music()
    {
        player->pause();

        play_music_button->setEnabled(true);
        pause_music_button->setEnabled(false);

        play_music_button->setStyleSheet(control_music_button_SS);
        pause_music_button->setStyleSheet(disabled_control_music_button_SS);
    }

    void play_again(QMediaPlayer::MediaStatus status)
    {
        if (status == QMediaPlayer::EndOfMedia)
        {
            player->setPosition(0);
            player->play();
        }
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Window win;
    win.show();

    return app.exec();
}