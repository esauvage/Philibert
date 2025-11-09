#ifndef PHILMAINWINDOW_H
#define PHILMAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QMap>
#include <QFileDialog>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QJsonDocument>
#include "sujet.h"
#include "verbe.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class PhilMainWindow;
}
QT_END_NAMESPACE

class PhilMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    PhilMainWindow(QWidget *parent = nullptr);
    ~PhilMainWindow();

private slots:
    void on_actionOuvrir_triggered();
    void on_btnDire_clicked();

private:
    Ui::PhilMainWindow *ui;
    Sujet _courant;
    Verbe _courVerbe;
    QMap<Sujet, QList<Sujet>> _sujets;
    // QList<Verbe> _verbes;
    QMap<Verbe, QList<Verbe>> _verbes;
    QString dire();
};
#endif // PHILMAINWINDOW_H
