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
    void analyse(const QString &phrase, const QList<Verbe> verbes);
    void trouveSujet(const QString &phrase, int personne); //On trouve un sujet associé à un verbe conjugué, on a donc la personne
private:
    Sujet _sujetCour;
    QMap<Sujet, QList<Sujet>> _sujets;
};

#endif // ANALYSEUR_H
