 #ifndef SETTINGSCENE_H
#define SETTINGSCENE_H

#include <QMainWindow>
#include <QPainter>

class SettingScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit SettingScene(QWidget *parent = nullptr);

    //重写paintEvent
    void paintEvent(QPaintEvent *);

signals:
    void chooseSceneBack();
};

#endif // SETTINGSCENE_H
