#include "mainwindow.h"
#include <QApplication>

#include "zlog.h"

// Qt 写日志
#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <QTextStream>
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
{
    QString txt;
    switch (type) {
    case QtDebugMsg:
        txt = QString("Debug:");
        break;
    case QtWarningMsg:
        txt = QString("Warning:");
        break;
    case QtCriticalMsg:
        txt = QString("Critical:");
        break;
    case QtFatalMsg:
        txt = QString("Fatal:");
    }

    QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString current_date = QString("(%1)").arg(current_date_time);
    QString message = QString("%1 %2 %3 %4").arg(txt).arg(context_info).arg(msg).arg(current_date);

    QFile file("log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&file);
    ts << message << "\r\n";
    file.flush();
    file.close();
}
#else
void myMessageOutput(QtMsgType type, const char *msg)
{
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s\n", msg);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s\n", msg);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s\n", msg);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s\n", msg);
        abort();
    }
}
#endif
// END

// c++ windows 写日志
void AppendLine(const char *FileName, const char *text)
{
    FILE *fp = NULL;
    if((fp = fopen(FileName, "a+")) == NULL) {
        return;
    }
    fprintf(fp, "%s\n", text);
    fflush(fp);
    fclose(fp);
}

void log(const char *device, const char *format, ...)
{
    va_list v;
    char buffer[1000];
    char filename[100];
    va_start(v, format);
    _vsnprintf(buffer, 900, format, v);
    va_end(v);

    CreateDirectoryA("LOG",0);
    sprintf(filename,"LOG/%s.txt",device);
    AppendLine(filename,buffer);
}
// END

// use log4qt
#include "log4qt/consoleappender.h"
#include "log4qt/logger.h"
#include "log4qt/ttcclayout.h"

#include <QtCore/QBuffer>
#include <QtCore/QBitArray>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QMetaEnum>
#include <QtCore/QSettings>
#include <QtCore/QTextStream>
#include <QtCore/QThread>
#include <QtTest/QtTest>
#include "log4qt/basicconfigurator.h"
#include "log4qt/consoleappender.h"
#include "log4qt/dailyrollingfileappender.h"
#include "log4qt/fileappender.h"
#include "log4qt/helpers/configuratorhelper.h"
#include "log4qt/helpers/datetime.h"
#include "log4qt/helpers/factory.h"
#include "log4qt/helpers/initialisationhelper.h"
#include "log4qt/helpers/optionconverter.h"
#include "log4qt/helpers/patternformatter.h"
#include "log4qt/helpers/properties.h"
#include "log4qt/logmanager.h"
#include "log4qt/loggerrepository.h"
#include "log4qt/patternlayout.h"
#include "log4qt/propertyconfigurator.h"
#include "log4qt/rollingfileappender.h"
#include "log4qt/simplelayout.h"
#include "log4qt/ttcclayout.h"
#include "log4qt/varia/denyallfilter.h"
#include "log4qt/varia/levelmatchfilter.h"
#include "log4qt/varia/levelrangefilter.h"
#include "log4qt/varia/stringmatchfilter.h"
// log4qt end


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    qInstallMessageHandler(myMessageOutput);
#else
    qInstallMsgHandler(myMessageOutput);
#endif

    // show log
    DBG("DBG: Program start...\n");
    qDebug() << "qDebug(): Program start...";
    myMessageOutput(QtDebugMsg, "myMessageOutput: Program start...");
    log("mylog", "Log: %s", "c++: Program start...");
    // show end


    // use log4qt
    Log4Qt::BasicConfigurator::configure();
    Log4Qt::PropertyConfigurator::configure(qApp->applicationDirPath() + "/log4qt.properties");

    Log4Qt::Logger *al = Log4Qt::Logger::logger("A1");
    al->info("the message of log");//the log save at logs/a1.log

    Log4Qt::Logger *a2 = Log4Qt::Logger::logger("A2");
    a2->info("the message of log");//the log save at logs/a2.log

    Log4Qt::Logger *a3 = Log4Qt::Logger::logger("A3");
    a3->info("the message of log");//the log save at logs/a3.log
    // use log4qt end


    MainWindow w;
    w.show();

    return a.exec();
}
