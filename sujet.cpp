#include "sujet.h"

Sujet::Sujet(int personne, QString nom)
    :_nom(nom), _personne(personne)
{
}

int Sujet::personne() const
{
    return _personne;
}

QString Sujet::nom() const
{
    return _nom;
}

bool Sujet::operator <(const Sujet &b) const
{
    return nom() < b.nom();
}
