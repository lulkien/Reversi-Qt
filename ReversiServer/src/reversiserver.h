#ifndef REVERSISERVER_H
#define REVERSISERVER_H

#include <QObject>
#include <QTcpServer>
#include "playerinfo.h"

class ReversiServer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int          connections     READ connections    NOTIFY connectionsChanged)
    Q_PROPERTY(QString      roomKey         READ roomKey        NOTIFY roomKeyChanged)
    Q_PROPERTY(int          matchState      READ matchState     NOTIFY matchStateChanged)
    Q_PROPERTY(PlayerInfo*  lPlayer         READ lPlayer        NOTIFY lPlayerChanged)
    Q_PROPERTY(PlayerInfo*  rPlayer         READ rPlayer        NOTIFY rPlayerChanged)

public:
    explicit ReversiServer(QObject *parent = nullptr);
    ~ReversiServer();

    void initialized();
    bool startServer();

    int connections() const;
    const QString &roomKey() const;
    int matchState() const;
    PlayerInfo *lPlayer() const;
    PlayerInfo *rPlayer() const;

public slots:
    void generateNewKey();
    void sendKeyToClipBoard();

signals:
    void roomKeyChanged();
    void connectionsChanged();
    void matchStateChanged();
    void lPlayerChanged();
    void rPlayerChanged();

private:
    QTcpServer  *m_server;
    int         m_connections;
    QString     m_roomKey;
    int         m_matchState;
    PlayerInfo* m_lPlayer;
    PlayerInfo* m_rPlayer;
};

#endif // REVERSISERVER_H
