#ifndef ETAT_H
#define ETAT_H

#include "verbe.h"
#include "sujet.h"

class Etat
{
public:
    Etat();

    Verbe verbe() const;
    void setVerbe(const Verbe &newVerbe);

    Sujet sujet() const;
    void setSujet(const Sujet &newSujet);

private:
    Verbe _verbe;
    Sujet _sujet;
};

#endif // ETAT_H
