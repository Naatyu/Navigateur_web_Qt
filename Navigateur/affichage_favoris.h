#ifndef AFFICHAGE_FAVORIS_H
#define AFFICHAGE_FAVORIS_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QLayout>
#include <QListWidget>
#include <QWebEngineView>

#include "mainwindow.h"

class MainWindow;

class Affichage_Favoris : public QWidget
{
    Q_OBJECT
public:
    Affichage_Favoris(MainWindow *);
    ~Affichage_Favoris();

public slots :
    void Ajouter();
    void charger();
    void suprimer_Fav();
    void refreshtitlenewonglet(QString);

private :
    MainWindow *Parent;
    QLineEdit *barre_url;
    QComboBox *Favoris;



};

#endif // AFFICHAGE_FAVORIS_H
