#include "analyseur.h"

#include <QStringList>
#include <QMessageBox>

Analyseur::Analyseur() {}

void Analyseur::analyse(const QString &phrase, QList <Verbe> verbes)
{
    QStringList mots = phrase.split(' '); //On sépare la phrase en mots
    //On va chercher le mot dans ce qu'on connait déjà
    for (auto & m : mots) {
        for (auto & v : verbes) {
            int personne = -1;
            for (int i = 0; i < 6; ++i) {
                if (m.toLower() == v.conjuguer(i)) {
                    personne = i;
                }
            }
            if (personne >= 0) {
                trouveSujet(phrase.left(phrase.indexOf(m)), personne);
            }
        }
    }
}

void Analyseur::trouveSujet(const QString &phrase, int personne)
{
    if (phrase.isEmpty()) return;
    QString sujet = phrase.split(",", Qt::SkipEmptyParts).last().toLower(); // Rien pour l'instant entre le sujet et le verbe
    while (!sujet[0].isLetter()) sujet.removeFirst();
    while (!sujet.last(1)[0].isLetter()) sujet.removeLast();
    Sujet s(personne, sujet);
    if (_sujetCour.personne()>=0) {
        _sujets[_sujetCour].append(s);//On ajoute aux états suivants l'état courant ce qu'on vient de trouver.
    }
    if (!_sujets.contains(s)) {
        _sujets.insert(s, QList<Sujet>());//Le cas échéant, on l'ajoute à la liste des sujets.
    }
    _sujetCour = s;
    QMessageBox::information(nullptr, "Sujet :", sujet);
}
