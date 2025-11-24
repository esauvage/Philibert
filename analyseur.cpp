#include "analyseur.h"

#include <QStringList>

Analyseur::Analyseur() {}

void Analyseur::analyse(const QString &phrase, const QMap<Verbe, QList<Verbe>> &verbes, const QMap<Sujet, QList<Sujet> > &sujets)
{
    _sujets = sujets;
    _verbes = verbes;
    QStringList mots = phrase.toLower().split(' '); //On sépare la phrase en mots
    //On va chercher le mot dans ce qu'on connait déjà
    for (auto & m : mots) {
        for (auto & v : _verbes.keys()) {
            int personne = -1;
            for (int i = 0; i < 6; ++i) {
                if (m.toLower() == v.conjuguer(i)) {
                    personne = i;
                }
            }
            if (personne >= 0) {
                trouveSujet(phrase.toLower().left(phrase.toLower().indexOf(m)), personne);
            }
        }
    }
    for (auto & s : _sujets.keys()) {
        if (phrase.toLower().contains(s.nom().toLower(), Qt::CaseInsensitive)) {
            auto pos = phrase.toLower().indexOf(s.nom().toLower());
            trouveVerbe(phrase.toLower().right(phrase.length() - phrase.toLower().indexOf(s.nom().toLower()) - s.nom().length()), s.personne());
        }
    }
}

void Analyseur::trouveSujet(const QString &phrase, int personne)
{
    if (phrase.isEmpty()) return;
    QString sujet = phrase.split(",", Qt::SkipEmptyParts).last().toLower(); // Rien pour l'instant entre le sujet et le verbe
    while (!sujet[0].isLetter()) sujet.remove(0, 1);
    while (!sujet.last(1)[0].isLetter()) sujet.remove(sujet.length() - 1, 1);
    Sujet s(personne, sujet);
    if (_sujetCour.personne()>=0) {
        _sujets[_sujetCour].append(s);//On ajoute aux états suivants l'état courant ce qu'on vient de trouver.
    }
    if (!_sujets.contains(s)) {
        _sujets.insert(s, QList<Sujet>());//Le cas échéant, on l'ajoute à la liste des sujets.
    }
    _sujetCour = s;
}

void Analyseur::trouveVerbe(const QString &phrase, int personne)
{
    if (phrase.isEmpty()) return;
    auto verbe = phrase.split(",", Qt::SkipEmptyParts).last().toLower(); // Rien pour l'instant entre le sujet et le verbe
    while (!verbe[0].isLetter()) verbe.remove(0, 1);
    while (!verbe.last(1)[0].isLetter()) verbe.remove(verbe.length() - 1, 1);
    QStringList conjugaison;
    for (; conjugaison.length() < personne;) {
        conjugaison  << "";
    }
    conjugaison << verbe;
    for (; conjugaison.length() < 6;) {
        conjugaison << "";
    }
    Verbe v(conjugaison, verbe);
    for (const auto & v2 : _verbes.keys()) {
        if (v2.conjuguer(personne) == verbe) {
            v = v2;
            break;
        }
    }
    if (!_verbeCour.lemme().isEmpty()) {
        _verbes[_verbeCour].append(v);//On ajoute aux états suivants l'état courant ce qu'on vient de trouver.
    }
    if (!_verbes.contains(v)) {
        _verbes.insert(v, QList<Verbe>());//Le cas échéant, on l'ajoute à la liste des sujets.
    }
    _verbeCour = v;
}

QMap<Sujet, QList<Sujet> > Analyseur::sujets() const
{
    return _sujets;
}
