#include "getserverlatencycmd.h"
#include "getserverlatency.h"

QStringList GetServerLatencyCmd::operator ()(
    QVariantMap &params
    )
{
  QStringList lines;

  // サーバ名を取得
  QByteArray server = params.value("server").toByteArray();
  if (server.isEmpty()) {
    lines << QObject::tr("No server.");
    return lines;
  }

  // あればタイムアウト時間を取得
  DWORD timeout = params.value("timeout", "0").toUInt();

  // あれば戻り値リストを取得
  QStringList retValues = params.value("return")
      .toString()
      .toLower()
      .split(",")
      ;
  bool isVer = (retValues.indexOf("ver") >= 0);
  bool isC2S = (retValues.indexOf("c2s") >= 0);
  bool isS2C = (retValues.indexOf("s2c") >= 0);

  // レイテンシ(待ち時間)とサーバのバージョンを取得する。
  Result result = GetServerLatency(isVer, isC2S, isS2C)(server, timeout);
  if (result.hasError()) {
    lines << QObject::tr("GetServerLatency error: code=%1")
             .arg(result.error())
             ;
    return lines;
  }

  // 戻り値をテキストリストにまとめる。
  QStringList outValues;
  if (isVer) {
    outValues
        << QString("ver=%1")
           .arg(result.value(GetServerLatency::KEY_VERSION).toUInt());
  }
  if (isC2S) {
    outValues
        << QString("c2s=%1")
           .arg(result.value(GetServerLatency::KEY_LATENCY_C2S).toUInt());
  }
  if (isS2C) {
    outValues
        << QString("s2c=%1")
           .arg(result.value(GetServerLatency::KEY_LATENCY_S2C).toUInt());
  }
  lines << outValues.join(",");

  return lines;
}
