#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>

#include <QApplication>
#include <QMainWindow>
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

class Window : public QWidget
{
public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();

private:
    void add_todo();
    void remove_todo(QWidget *tc);
    void removnig_todo_animation(QWidget *mw);
    void play_music();
    void pause_music();
    void play_again(QMediaPlayer::MediaStatus status);

private:
    QVBoxLayout *container;
    QWidget *top_bar;
    QHBoxLayout *top_bar_layout;
    QLineEdit *todo_field;
    QPushButton *todo_button;
    QWidget *middle_bar;
    QVBoxLayout *middle_bar_layout;
    QMediaPlayer *player;
    QAudioOutput *output;
    QWidget *bottom_bar;
    QHBoxLayout *bottom_bar_layout;
    QLabel *music_name_label;
    QWidget *music_control_widget;
    QHBoxLayout *music_control_layout;
    QPushButton *play_music_button;
    QPushButton *pause_music_button;
    QMessageBox *error_msgbox;
    QWidget *todo_container;
    QHBoxLayout *todo_container_label_box;
    QLabel *todo_label;
    QPushButton *remove_todo_button;
    QMediaPlayer *d_player;
    QAudioOutput *d_output;
    QPropertyAnimation *animation;
};

#endif // WINDOW_H