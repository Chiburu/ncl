#include <QCoreApplication>
#include <QTranslator>
#include <QLocale>
#include <QTextStream>

#include "parsecmdline.h"
#include "getserverlatency.h"
#include "getserverlatencycmd.h"

int main(int argc, char *argv[])
{
  // Qtアプリケーションの初期化
  QCoreApplication app(argc, argv);

  // 翻訳処理
  QTranslator translator;
  translator.load(QLocale(), "ncl", ".", ":/translations", ".qm");
  app.installTranslator(&translator);

  // 標準出力
  QTextStream out(stdout, QIODevice::WriteOnly);

  // Notes C APIを初期化する。
  Result initStatus = NotesInitExtended(argc, argv);
  out << QObject::tr("NotesInitExtended status")
      << ": "
      << initStatus.error()
      << endl;

  // コマンドライン解析
  ParseCmdline parseCmdline;

  // コマンドを追加
  parseCmdline.addCommand("get-server-latency", Cmd::GetServerLatency);

  // コマンドで使用するオプション引数を追加
  QCommandLineOption server(
        "server",
        QObject::tr("Server name."),
        "server-name"
        );
  QCommandLineOption timeout(
        "timeout",
        QObject::tr("Timeout(ms). To set 0 is for default."),
        "milliseconds"
        );
  QCommandLineOption retvalues(
        "return",
        QObject::tr("Return values devided comma (ex. ver,c2s,s2c)."),
        "retuen-values"
        );
  parseCmdline.addOption(&server);
  parseCmdline.addOption(&timeout);
  parseCmdline.addOption(&retvalues);

  // コマンドラインを解析
  parseCmdline(app).flat_map([](CmdlineParams clparams)
  {
    // コマンドごとに処理
    QStringList list;
    switch (clparams.command())
    {
    case Cmd::GetServerLatency:
      list = GetServerLatencyCmd()(clparams.params());
    }
    return Rx::observable<>::just(list);
  })
  .subscribe([&out](QStringList lines)
  {
    // 戻ってきたテキストリストを標準出力に表示。
    foreach (QString line, lines) {
      out << line << endl;
    }
  });

  // Notes C APIを終了する。
  if (initStatus.noError())
    NotesTerm();

  return 0;
}
