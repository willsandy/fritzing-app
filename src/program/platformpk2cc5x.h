#include "platform.h"

#include <QString>

#ifndef PLATFORMPK2CC5X_H
#define PLATFORMPK2CC5X_H

class PlatformPk2Cc5x : public Platform
{
public:
    PlatformPk2Cc5x();

    void upload(QWidget *source, const QString &port, const QString &board, const QString &fileLocation);
};

#endif // PLATFORMPK2CC5X_H
