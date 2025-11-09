#ifndef SUJET_H
#define SUJET_H

#include <QString>

class Sujet
{
public:
    Sujet(int personne = -1, QString nom = "");
    int personne() const;
    QString nom() const;
    bool operator < (const Sujet & b) const;

private:
    int _personne;
    QString _nom;
};

#endif // SUJET_H
