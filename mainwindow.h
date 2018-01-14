#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QListWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_playButton_clicked();

    void on_pauseButton_clicked();

    void on_stopButton_clicked();

    void on_previousButton_clicked();

    void on_nextButton_clicked();

    void on_volumeButton_clicked();

    void on_volumeSlider_sliderMoved(int position);

    void on_songProgressSlider_sliderMoved(int position);

    void on_songProgressSlider_positionChanged(qint64 position);

    void on_songProgressSlider_durationChanged(qint64 duration);

    void on_addSongPlaylistButton_clicked();

    void on_removeSongPlaylistButton_clicked();

    void on_moveUpSongPlaylistButton_clicked();

    void on_moveDownSongPlaylistButton_clicked();

    void on_playlistWidget_itemDoubleClicked(QListWidgetItem *item);

    void updateSongName();

    void updateSongDuration();

    void reportError();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    qint64 playlistNumbering;
    QListWidget *playlistWidget;
};

#endif // MAINWINDOW_H
