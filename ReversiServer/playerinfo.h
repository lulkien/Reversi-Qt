#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include <QObject>

class PlayerInfo : public QObject
{
    Q_OBJECT
public:
    explicit PlayerInfo(QObject *parent = nullptr);

signals:

};

#endif // PLAYERINFO_H
