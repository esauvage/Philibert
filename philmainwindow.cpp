#include "philmainwindow.h"
#include "ui_philmainwindow.h"
#include <QJsonObject>
#include <QJsonArray>

#include "analyseur.h"

PhilMainWindow::PhilMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PhilMainWindow), _courVerbe(QStringList(), "")
{
    ui->setupUi(this);

    // QStringList conjugaisons;
    // conjugaisons << "mange" << "manges" << "mange" << "mangeons" << "mangez" << "mangent";

    // _courVerbe = Verbe(conjugaisons, "manger");

    // _verbes << _courVerbe;
    // _verbes.insert(_courVerbe, QList<Verbe>());
    // conjugaisons.clear();
    // conjugaisons << "bois" << "bois" << "boit" << "buvons" << "buvez" << "boivent";
    // _verbes << Verbe(conjugaisons, "boire");
    // _verbes.insert(Verbe(conjugaisons, "boire"), QList<Verbe>());
    // _sujets << Sujet(2, "Toto");
    // _sujets << Sujet(3, "Nous");
}

PhilMainWindow::~PhilMainWindow()
{
    delete ui;
}

QString PhilMainWindow::dire()
{
    QString ret;

    auto l = _sujets[_courant];
    if ((_courant.personne() < 0) || l.isEmpty())
    {
        // Si il n'y a pas de sujet courant, on en tire un.
        l = _sujets.keys();
    }
    auto index = QRandomGenerator::global()->bounded(0, l.length());
    _courant = l[index];

    auto u = _verbes[_courVerbe];
    if (_courVerbe.lemme().isEmpty() || u.isEmpty())
    {
        // Si il n'y a pas de sujet courant, on en tire un.
        u = _verbes.keys();
    }
    auto indexVerbe = QRandomGenerator::global()->bounded(0, u.length());
    _courVerbe = u[indexVerbe];

    ret = _courant.nom() + " " + _courVerbe.conjuguer(_courant.personne());

    return ret;
}

void PhilMainWindow::on_actionOuvrir_triggered()
{
    QString fileName = QFileDialog::getOpenFileName();
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
        return;
    }

    QByteArray saveData = file.readAll();
    QJsonDocument jsonDoc(QJsonDocument::fromJson(saveData));

    // On lit les sujets
    if (jsonDoc.object().contains("sujets") && jsonDoc.object()["sujets"].isArray())
    {
        QJsonArray jsonSujets = jsonDoc.object()["sujets"].toArray();
        _sujets.clear();
        // On parcourt sujet par sujet
        for (auto i = 0; i < jsonSujets.size(); ++i) {
            //Un objet sujet contient le sujet et la liste des sujets suivants
            auto jsonSujet = jsonSujets[i].toObject();
            //On récupère la liste des objets suivants
            QJsonArray jsonSuivants = jsonSujet["suivants"].toArray();
            QList <Sujet> lSuiv;
            //On parcourt la liste des objets suivants
            for (auto j = 0; j < jsonSuivants.size(); ++j) {
                //Il s'agit d'un sujet
                auto jsonS = jsonSuivants[j].toObject();
                lSuiv << Sujet(jsonS["personne"].toInt(), jsonS["nom"].toString());
            }
            // On crée le sujet et on l'insère dans la QMap
            _sujets.insert(Sujet(jsonSujet["personne"].toInt(), jsonSujet["nom"].toString()), lSuiv);
        }
    }
    // On lit les verbes
    if (jsonDoc.object().contains("verbes") && jsonDoc.object()["verbes"].isArray())
    {
        QJsonArray jsonVerbes = jsonDoc.object()["verbes"].toArray();
        _verbes.clear();
        // On parcourt verbe par verbe
        for (auto i = 0; i < jsonVerbes.size(); ++i) {
            //Un objet verbe contient le verbe et la liste des verbes suivants
            auto jsonVerbe = jsonVerbes[i].toObject();

            QJsonArray jsonC = jsonVerbe["conjugaisons"].toArray();
            QStringList conjugaisons;

            for (auto j = 0; j < jsonC.size(); ++j)
            {
                auto jsonV = jsonC[j];
                conjugaisons << jsonV.toString();
            }

            //On récupère la liste des verbes suivants
            QJsonArray jsonSuivants = jsonVerbe["suivants"].toArray();
            QList <Verbe> lSuiv;
            //On parcourt la liste des objets suivants
            for (auto j = 0; j < jsonSuivants.size(); ++j)
            {
                auto jsonVerbe = jsonSuivants[j].toObject();

                QJsonArray jsonC = jsonVerbe["conjugaisons"].toArray();
                QStringList conjugaisons;

                for (auto o = 0; o < jsonC.size(); ++o)
                {
                    auto jsonV = jsonC[o];
                    conjugaisons << jsonV.toString();
                }
                //Il s'agit d'un verbe
                auto jsonV = jsonSuivants[j].toObject();
                lSuiv << Verbe(conjugaisons, jsonV["lemme"].toString());
            }
            QString lemme = jsonVerbe["lemme"].toString();
            // On insère le verbe dans la QMap
            Verbe toto(conjugaisons, lemme);
            _verbes.insert(toto, lSuiv);
        }
    }

    file.close();
}

void PhilMainWindow::on_btnDire_clicked()
{
    ui->lblPhrase->setText(dire());
}

void PhilMainWindow::on_actionAnalyser_triggered()
{
    //On demande un fichier. "Analyse.txt" est bien
    QString fileName = QFileDialog::getOpenFileName();
    if (fileName.isEmpty()) return; //On n'a pas de nom de fichier, tant pis

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        //On n'a pas pu ouvrir le fichier
        QMessageBox::information(0, "error", file.errorString());
        return;
    }

    Analyseur analyseur;//On a besoin d'un analyseur
    QTextStream in(&file);
    //On dit : le fichier contient une phrase sur une seule ligne.
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList phrases = line.split(".", Qt::SkipEmptyParts); //Une phrase se termine par un point.
        for (auto & p : phrases) {
            if (p.isEmpty()) break;//Vide = fini
            while (p[0] == ' ') p.removeFirst(); //On supprime les espaces devant.
            if (p[0] != p[0].toUpper()) break; // Une phrase doit commencer par une majuscule.
            analyseur.analyse(p, _verbes.keys(), _sujets);
            _sujets = analyseur.sujets();
        }
    }
}

