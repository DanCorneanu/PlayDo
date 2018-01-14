#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(player);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    player->setPlaylist(playlist);
    playlistNumbering = 0;

    connect(player, &QMediaPlayer::currentMediaChanged, this, &MainWindow::updateSongName);
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::on_songProgressSlider_positionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::on_songProgressSlider_durationChanged);
    connect(player, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error), this, &MainWindow::reportError);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addSongPlaylistButton_clicked()
{
    QStringList fileNames;
    fileNames = QFileDialog::getOpenFileNames(this,"Add an mp3 file","","MP3 (*.mp3)");
    if (fileNames.empty()) return;
    foreach (const QString fileName, fileNames)
    {
        QFileInfo fileInfo(fileName);
        ui->playlistWidget->addItem(QString::number(++playlistNumbering) + ". " + fileInfo.completeBaseName());
        QUrl fileUrl = QUrl::fromLocalFile(fileInfo.absoluteFilePath());
        playlist->addMedia(fileUrl);
    }
}

void MainWindow::on_removeSongPlaylistButton_clicked()
{
    QListWidgetItem *selectedSong = ui->playlistWidget->currentItem();
    if (selectedSong!=NULL)
    {
        playlist->removeMedia(ui->playlistWidget->row(selectedSong));
        delete ui->playlistWidget->takeItem(ui->playlistWidget->row(selectedSong));
        updateSongName();
    }
    /* Add ->selectionMode() if multiple item selection is needed
    using "ui->playlistWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

    QList<QListWidgetItem*> selectedSongs = ui->playlistWidget->selectedItems();
    foreach (QListWidgetItem * song, selectedSongs)
    {
        playlist->removeMedia(ui->playlistWidget->row(song));
        delete ui->playlistWidget->takeItem(ui->playlistWidget->row(song));
        updateSongName();
    } */
}

void MainWindow::on_moveUpSongPlaylistButton_clicked()
{
    QListWidgetItem *selectedSong = ui->playlistWidget->currentItem();
    if (selectedSong!=NULL)
    {
        int selectedSongRow = ui->playlistWidget->row(selectedSong);
        if (selectedSongRow == 0) return;
        playlist->moveMedia(selectedSongRow, selectedSongRow-1);
        ui->playlistWidget->takeItem(selectedSongRow);
        ui->playlistWidget->insertItem(selectedSongRow-1,selectedSong);
        ui->playlistWidget->setCurrentRow(playlist->currentIndex());
        updateSongName();
    }
}

void MainWindow::on_moveDownSongPlaylistButton_clicked()
{
    QListWidgetItem *selectedSong = ui->playlistWidget->currentItem();
    if (selectedSong!=NULL)
    {
        int selectedSongRow = ui->playlistWidget->row(selectedSong);
        if (selectedSongRow+1 == ui->playlistWidget->count()) return;
        playlist->moveMedia(selectedSongRow, selectedSongRow+1);
        ui->playlistWidget->takeItem(selectedSongRow);
        ui->playlistWidget->insertItem(selectedSongRow+1,selectedSong);
        ui->playlistWidget->setCurrentRow(playlist->currentIndex());
        updateSongName();
    }
}

void MainWindow::on_playlistWidget_itemDoubleClicked(QListWidgetItem *item)
{
    player->play();
    playlist->setCurrentIndex(ui->playlistWidget->row(item));
}

