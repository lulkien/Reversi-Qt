#include "reversiserver.h"
#include <QDebug>
#include <QNetworkInterface>
#include <QRandomGenerator>
#include <QQmlEngine>
#include <QClipboard>
#include <QGuiApplication>

ReversiServer::ReversiServer(QObject *parent)
    : QObject { parent }
    , m_server { nullptr }
    , m_connections { 0 }
    , m_roomKey { QString() }
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

ReversiServer::~ReversiServer()
{
    if (m_server)
    {
        qDebug() << "Stop listening...";
        m_server->close();
        delete m_server;
        m_server = nullptr;
    }
}

void ReversiServer::initialized()
{
    if (!m_server)
    {
        m_server = new QTcpServer();
    }
    generateNewKey();
}

bool ReversiServer::startServer()
{
    if (!m_server)
    {
        qCritical() << "Server is not initialized!";
        return false;
    }

    bool ret = m_server->listen(QHostAddress::Any, 14159);
    if (!ret)
    {
        qCritical() << "Fail to start Reversi Server! Error:" << m_server->errorString();
        return false;
    }

    qDebug() << "Server is up.";
    for (const QHostAddress &address : QNetworkInterface::allAddresses())
    {
        if (address.protocol() == QAbstractSocket::IPv4Protocol
                && address != QHostAddress(QHostAddress::LocalHost))
        {
            qInfo() << "Waiting player on " << address.toString();
        }
    }
    return true;
}

int ReversiServer::connections() const
{
    return m_connections;
}

const QString &ReversiServer::roomKey() const
{
    return m_roomKey;
}

void ReversiServer::generateNewKey()
{
    const QString allowedCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int length = 5;

    m_roomKey.clear();
    QRandomGenerator randomGenerator = QRandomGenerator::securelySeeded();

    for (int i = 0; i < length; i++)
    {
        int randomIndex = randomGenerator.bounded(allowedCharacters.length());
        m_roomKey.append(allowedCharacters.at(randomIndex));
    }

    qDebug() << "New key:" << m_roomKey;
    emit roomKeyChanged();
}

void ReversiServer::sendKeyToClipBoard()
{
    QGuiApplication::clipboard()->setText(m_roomKey);
}


int ReversiServer::matchState() const
{
    return m_matchState;
}

PlayerInfo *ReversiServer::lPlayer() const
{
    return m_lPlayer;
}

PlayerInfo *ReversiServer::rPlayer() const
{
    return m_rPlayer;
}
