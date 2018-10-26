#include <QCoreApplication>
#include <QTranslator>
#include <QLocale>

#include "getserverlatency.h"

/**
 * @brief 結果を出力する。
 * @param out 出力先ストリーム
 * @param result 関数オブジェクトの戻り値(Result)
 * @param header 出力ヘッダテキスト
 * @param key 出力値のキーワード
 * @param tempText 出力テキストのテンプレート
 */
void outputResult(QTextStream &out,
                  const Result &result,
                  const QString &header,
                  const QString &key,
                  const QString &tempText
                  )
{
  if (result.contains(key))
    out << header
        << ": "
        << tempText.arg(result.value(key).toUInt())
        << endl;
}

// 自身で到達させたいサーバ名を設定する。
const char *pServer = "Your/server/name";

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

  // レイテンシ(待ち時間)とサーバのバージョンを取得する。
  Result result = GetServerLatency()(pServer);
  out << QObject::tr("NSFGetServerLatency status")
      << ": "
      << result.error()
      << endl;

  // エラーがなければ・・・
  if (result.noError()) {
    // 戻り値を標準出力に表示する。
    outputResult( out, result,
          QObject::tr("Build version of '%1'").arg(pServer),
          GetServerLatency::KEY_VERSION,
          QString("%1")
          );
    outputResult( out, result,
          QObject::tr("Latency time for client to server"),
          GetServerLatency::KEY_LATENCY_C2S,
          QString("%1 ms")
          );
    outputResult( out, result,
          QObject::tr("Latency time for server to client"),
          GetServerLatency::KEY_LATENCY_S2C,
          QString("%1 ms")
          );
  }

  // Notes C APIを終了する。
  if (initStatus.noError())
    NotesTerm();

  return 0;
}
