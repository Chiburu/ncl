#include "parsecmdline.h"

#include <QCommandLineParser>

ParseCmdline::ParseCmdline()
  : cmdMap_(),
    pOptions_()
{}

void ParseCmdline::addCommand(const QString &name, const Cmd &cmd)
{
  cmdMap_.insert(name, cmd);
}

void ParseCmdline::addOption(QCommandLineOption *pOption)
{
  pOptions_.append(pOption);
}

Rx::observable<CmdlineParams> ParseCmdline::operator ()(
    QCoreApplication &app
    )
{
  // コマンドラインパーサを初期化
  QCommandLineParser parser;
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addPositionalArgument("command", QObject::tr("Specify command."));
  QList<QCommandLineOption*>::iterator it = pOptions_.begin();
  for (; it != pOptions_.end(); ++it)
  {
    QCommandLineOption *pOption = *it;
    parser.addOption(*pOption);
  }

  // パースプロセスを実行
  parser.process(app);

  // コマンドラインの指定値を解析

  // コマンドを取得
  QStringList args = parser.positionalArguments();
  QString cmdText = args.first().toLower();

  // コマンド文字列を値に変換
  CmdlineParams params;
  if (cmdMap_.keys().contains(cmdText)) {
    params.setCommand(cmdMap_.value(cmdText));
  }

  // オプション引数を解析
  it = pOptions_.begin();
  for (; it != pOptions_.end(); ++it)
  {
    QCommandLineOption *pOption = *it;
    if (parser.isSet(*pOption))
      params.setParam(pOption->names().first(), parser.value(*pOption));
  }

  return Rx::observable<>::just(params);
}
