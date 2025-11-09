#include "verbe.h"

Verbe::Verbe(QStringList conjugaisons, QString lemme)
    :_conjugaisons(conjugaisons), _lemme(lemme)
{

}

QString Verbe::conjuguer(int personne) const
{
    return _conjugaisons[personne];
}

QString Verbe::lemme() const
{
    return _lemme;
}

bool Verbe::operator <(const Verbe &b) const
{
    return lemme() < b.lemme();
}
