#ifndef VERBE_H
#define VERBE_H

#include <QString>
#include <QStringList>

class Verbe
{
public:
    Verbe(QStringList conjugaisons, QString lemme);
    QString conjuguer(int personne) const;
    QString lemme() const;
    bool operator < (const Verbe & b) const;

private:
    QString _lemme;
    QStringList _conjugaisons;
};

#endif // VERBE_H
