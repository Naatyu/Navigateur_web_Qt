#include "mainwindow.h"



#include <QWebEngineView>
#include <QtWidgets>
#include <QTabWidget>
#include <QGridLayout>
#include <QMenuBar>
#include <QLabel>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *fenetre = new QWidget;
    QGridLayout *mainlayout = new QGridLayout;
    fenetre->setLayout(mainlayout);
    setCentralWidget(fenetre);
    centralWidget()->layout()->setContentsMargins(0,0,0,0);
    setWindowTitle("NavigateurV1.0");
    /*----implementer la page web----*/
    Pageweb = new QWebEngineView;
    Pageweb->load(QUrl("http://www.google.fr"));

    /*----tab----*/
    onglets = new QTabWidget;
    onglets->setTabsClosable(1);

    QString tab = "Tab";
    onglets->addTab(Pageweb,tab );
    mainlayout->addWidget(onglets,1,0,1,2);
    QObject::connect(onglets,SIGNAL(tabCloseRequested ( int )), this, SLOT(fermeronglet(int)));
    QObject::connect(onglets,SIGNAL(currentChanged(int)),this,SLOT(detectchangetab(int)));


    /*----toolbar supérieure----*/

    /*URL*/
    Ligne_URL = new QLineEdit;
    Ligne_URL->setText(Pageweb->url().toString());
    mainlayout->addWidget(Ligne_URL,0,0);

     /*recherche*/
    QPushButton *rechercher = new QPushButton(this);
    rechercher->setText("Rechercher");
    mainlayout->addWidget(rechercher,0,1);
    QObject::connect(rechercher,SIGNAL(clicked()),this,SLOT(chargerPage()));

    /*création des menus*/
    QMenu *menuFavoris = menuBar()->addMenu("&Favoris");
    QMenu *menuActions = menuBar()->addMenu("&Actions");


    /*création des actions*/
    QAction *actionQuitter = new QAction("&Quitter", this);
    menuActions->addAction(actionQuitter);
     QObject::connect(actionQuitter, SIGNAL(triggered()), this, SLOT(close()));

    QAction *actionHome = new QAction("&Home",this);
    menuActions->addAction(actionHome);
    QObject::connect(actionHome,SIGNAL(triggered()),this,SLOT(chargerHome()));

    QAction *ajouter_favoris = new QAction("&Ajouter un favoris");
    menuFavoris->addAction(ajouter_favoris);
    QObject::connect(ajouter_favoris, SIGNAL(triggered()),this,SLOT(Ajouter_Favoris()));

    QAction *ajouterOnglets = new QAction("&Nouveau onglet",this);
    menuActions->addAction(ajouterOnglets);
    QObject::connect(ajouterOnglets,SIGNAL(triggered()),this,SLOT(Addonglets()));

    /*----Actualisation----*/

    QObject::connect(Pageweb,SIGNAL(urlChanged(QUrl)),this,SLOT(refreshurl(QUrl)));
    QObject::connect(Pageweb,SIGNAL(titleChanged(QString)),this,SLOT(refreshtitle(QString)));



    /*----couleurs----*/
    QPalette pal = palette();
    pal.setColor(QPalette::Background,qRgb(169,169,169));

    centralWidget()->setAutoFillBackground(true);
    centralWidget()->setPalette(pal);

}

MainWindow::~MainWindow()
{

}

void MainWindow::chargerHome()
{
    Pageweb->page()->load(QUrl("http://www.google.fr"));
}

void MainWindow::fermeronglet(int index)
{
    onglets->removeTab(index);
}

void MainWindow::Addonglets()
{
    Pageweb2 = new QWebEngineView;
    Pageweb2->load(QUrl("http://www.google.fr"));
    int idx = onglets->currentIndex();
    idx = idx+1;
    QString Tab="Tab "+ QString::number(idx);

    onglets->insertTab(idx,Pageweb2,"Nouvel onglet");
    QObject::connect(Pageweb2,SIGNAL(titleChanged(QString)),this,SLOT(refreshtitlenewonglet(QString)));
}

void MainWindow::chargerPage()
{
    QString idxpage;
    idxpage = Ligne_URL->text();
    int idxonglet = onglets->currentIndex();
    QWidget* pWidget = onglets->widget(idxonglet);
    Pageweb = (QWebEngineView*)pWidget;
    Pageweb->load(QUrl(idxpage));
}

void MainWindow::refreshurl(QUrl idx)
{
    Ligne_URL->setText(idx.toString());
}

void MainWindow::refreshtitle(QString titre)
{
    int idx = onglets->currentIndex();
    onglets->setTabText(idx,titre);
}

void MainWindow::Ajouter_Favoris(){
    fenetrefavoris = new Affichage_Favoris(this);
    fenetrefavoris->show();
}

void MainWindow::detectchangetab(int idx)
{
    QWidget* pWidget = onglets->widget(idx);
    Pageweb = (QWebEngineView*)pWidget;
    QUrl url = Pageweb->url();
    Ligne_URL->setText(url.toString());
    QObject::connect(Pageweb,SIGNAL(urlChanged(QUrl)),this,SLOT(refreshurl(QUrl)));
}

void MainWindow::refreshtitlenewonglet(QString titre)
{
    int idx = onglets->count();
    idx=idx-1;
    onglets->setTabText(idx,titre);
}

