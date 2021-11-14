#include "affichage_favoris.h"

#include <QLayout>
#include <QPushButton>
#include <QWebEngineView>
#include <QComboBox>
#include <QListWidget>


Affichage_Favoris::Affichage_Favoris(MainWindow*Pere)
{
    Parent=Pere;

    QGridLayout *layoutCentral = new QGridLayout;
    setLayout(layoutCentral);
    barre_url = new QLineEdit;
    barre_url->setText("http://");
    layoutCentral->addWidget(barre_url,0,0);

    QGridLayout *layoutbouton = new QGridLayout;
    QPushButton *Quitter = new QPushButton("Annuler");
    QPushButton *AjouterFavoris = new QPushButton("Ajouter");
    QPushButton *ChargerPage = new QPushButton("Charger page");
    QPushButton *suprimer = new QPushButton("Supprimer");
    layoutbouton->addWidget(AjouterFavoris,0,0);
    layoutbouton->addWidget(ChargerPage,0,1);
    layoutbouton->addWidget(Quitter,0,3);
    layoutbouton->addWidget(suprimer,0,2);
    layoutCentral->addLayout(layoutbouton,2,0);

    Favoris = new QComboBox;
    layoutCentral->addWidget(Favoris, 1,0);



    QObject::connect(Quitter, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(AjouterFavoris, SIGNAL(clicked()),this,SLOT(Ajouter()));
    QObject::connect(ChargerPage, SIGNAL(clicked()),this,SLOT(charger()));
    QObject::connect(suprimer, SIGNAL(clicked()),this,SLOT(suprimer_Fav()));




}


Affichage_Favoris::~Affichage_Favoris(){
}

void Affichage_Favoris::Ajouter(){
    if(!barre_url->text().isEmpty())
    {
      Favoris->addItem(barre_url->text());

}
}

void Affichage_Favoris::charger(){

    int indice = Favoris->currentIndex();

    QWebEngineView *Pageweb = new QWebEngineView();
    Pageweb->load(QUrl(Favoris->itemText(indice)));

    int idx =Parent->onglets->currentIndex();

    idx = idx+1;
    Parent->onglets->insertTab(idx,Pageweb,Favoris->itemText(indice));

    QObject::connect(Pageweb,SIGNAL(titleChanged(QString)),this,SLOT(refreshtitlenewonglet(QString)));



    }

void Affichage_Favoris::suprimer_Fav(){

   int idx = Favoris->currentIndex();
    Favoris->removeItem(idx);

}

void Affichage_Favoris::refreshtitlenewonglet(QString titre)
{
    int idx =Parent-> onglets->count();
    idx=idx-1;
    Parent->onglets->setTabText(idx,titre);
}
