#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QWebEngineView>
#include "affichage_favoris.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class Affichage_Favoris;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTabWidget *onglets;

public slots:
    void chargerHome();
    void fermeronglet(int);
    void chargerPage();
    void Addonglets();
    void refreshurl(QUrl);
    void refreshtitle(QString);
    void Ajouter_Favoris();
    void detectchangetab(int);
    void refreshtitlenewonglet(QString);
private:
    QLineEdit *Ligne_URL;
    QWebEngineView *Pageweb;
    QWebEngineView *Pageweb2;
    Affichage_Favoris *fenetrefavoris;
};
#endif // MAINWINDOW_H
