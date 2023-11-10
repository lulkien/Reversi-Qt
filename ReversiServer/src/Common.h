#ifndef COMMON_H
#define COMMON_H

#include <QObject>

enum GameRoles {
    SERVER,
    PLAYER_1,
    PLAYER_2,
};

enum ReversiTcpCommands {
    // Server -> Client
    CMD_VALIDATE_ROOM_KEY,
    CMD_INIT_BOARD,
    CMD_PLAYER_TURN,
    CMD_UPDATE_BOARD,

    // Client -> Server
    CMD_PLAYER_READY,
    CMD_PLAYER_MOVE,
};

class AppEnums
{
    Q_GADGET
public:
    enum class MatchState {
        WAITING_FOR_PLAYER,
        PLAYER_PREPARING,
        IN_GAME,
        END_GAME,
    };
    Q_ENUM(MatchState)

};

#endif // COMMON_H
