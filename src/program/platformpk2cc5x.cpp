#include "platformpk2cc5x.h"

#include <QProcess>
#include <QFileInfo>
#include <QSettings>

#include <iostream>

#include "programtab.h"

PlatformPk2Cc5x::PlatformPk2Cc5x() : Platform(QString("PK2CC5X"))
{
    setReferenceUrl(QUrl("http://www.bknd.com/doc/cc5x-35.pdf"));
    setCanProgram(true);
    setIdeName("CC5X and PK2CMD");
    setDownloadUrl(QUrl("https://github.com/willsandy/Fritzing-PK2-Cc5x/"));
    setMinVersion("3.5+1.20");
    setExtensions(QStringList() << ".c");

    QMap<QString, QString> boards;
    boards.insert("PIC16F690", "PIC16f690");
    boards.insert("PIC16F1829", "PIC16f1829");
    setBoards(boards);

    setDefaultBoardName("PIC16F690");
}

void PlatformPk2Cc5x::upload(QWidget *source, const QString &port, const QString &board, const QString &fileLocation)
{
    QProcess * process = new QProcess(this);
    process->setProcessChannelMode(QProcess::MergedChannels);
    process->setReadChannel(QProcess::StandardOutput);

    connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), source, SLOT(programProcessFinished(int, QProcess::ExitStatus)));
    connect(process, SIGNAL(readyReadStandardOutput()), source, SLOT(programProcessReadyRead()));

    QFileInfo cmdFileInfo(getCommandLocation());
    QString cmdDir(cmdFileInfo.absoluteDir().absolutePath().append("/"));

    QFileInfo fileInfo(fileLocation);
    QString workDir(fileInfo.absoluteDir().absolutePath().append("/"));
    QString fileName(fileInfo.fileName());
    QString fileBaseName(fileInfo.completeBaseName());

    QStringList args;
    args.append(cmdDir);
    args.append(getBoards().value(board));
    args.append(workDir);
    args.append(fileName);
    args.append(fileBaseName);

    ProgramTab *tab = qobject_cast<ProgramTab *>(source);
    if (tab)
        tab->appendToConsole(tr("Running %1 %2").arg(getCommandLocation()).arg(args.join(" ")));
    process->start(getCommandLocation(), args);
}
