#ifndef PARSECMDLINE_H
#define PARSECMDLINE_H

#include "cmdlineparams.h"
#include <QCoreApplication>
#include <QCommandLineOption>

#include <rxcpp/rx.hpp>
namespace Rx {
using namespace rxcpp;
using namespace rxcpp::operators;
}

/**
 * @brief コマンドラインパーサのラップクラス
 * @class ParseCmdline
 */
class ParseCmdline
{
public:
  ParseCmdline();

  void addCommand(const QString &name, const Cmd &cmd);

  void addOption(QCommandLineOption *pOption);

  Rx::observable<CmdlineParams> operator ()(QCoreApplication &app);

private:
  QMap<QString, Cmd> cmdMap_;
  QList<QCommandLineOption*> pOptions_;
};


#endif // PARSECMDLINE_H
