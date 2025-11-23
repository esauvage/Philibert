#include "etat.h"

Etat::Etat() {
    QStringList conjugaisons;
    conjugaisons << "mange" << "manges" << "mange" << "mangeons" << "mangez" << "mangent";

    _verbe = Verbe(conjugaisons, "manger");
}

Verbe Etat::verbe() const
{
    return _verbe;
}

void Etat::setVerbe(const Verbe &newVerbe)
{
    _verbe = newVerbe;
}

Sujet Etat::sujet() const
{
    return _sujet;
}

void Etat::setSujet(const Sujet &newSujet)
{
    _sujet = newSujet;
}
