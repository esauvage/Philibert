#ifndef ANALYSEUR_H
#define ANALYSEUR_H

#include <QString>
#include <QMap>

#include "verbe.h"
#include "sujet.h"

class Analyseur
{
public:
    Analyseur();
    void analyse(const QString &phrase, const QMap<Verbe, QList<Verbe>> &verbes, const QMap<Sujet, QList<Sujet> > &sujets);
    void trouveSujet(const QString &phrase, int personne); //On trouve un sujet associé à un verbe conjugué, on a donc la personne
    void trouveVerbe(const QString &phrase, int personne); //On trouve un verbe associé à un sujet, on a donc la personne

    QMap<Sujet, QList<Sujet> > sujets() const;

private:
    Sujet _sujetCour;
    Verbe _verbeCour;
    QMap<Sujet, QList<Sujet>> _sujets;
    QMap<Verbe, QList<Verbe>> _verbes;
};

#endif // ANALYSEUR_H
