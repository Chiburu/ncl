#include "getserverlatency.h"

// Notes C APIのインクルードは、Windowsではアラインメントを1バイトにして読み込む。
#ifdef NT
#pragma pack(push, 1)
#endif

#include <nsfdb.h>

#ifdef NT
#pragma pack(pop)
#endif

const char* const GetServerLatency::KEY_VERSION = "version";
const char* const GetServerLatency::KEY_LATENCY_C2S = "latency-c2s";
const char* const GetServerLatency::KEY_LATENCY_S2C = "latency-s2c";

GetServerLatency::GetServerLatency(
    bool bVersion,
    bool bLatencyC2S,
    bool bLatencyS2C
    )
  : retVersion_(bVersion, KEY_VERSION)
  , retLatencyC2S_(bLatencyC2S, KEY_LATENCY_C2S)
  , retLatencyS2C_(bLatencyS2C, KEY_LATENCY_S2C)
{}

Result GetServerLatency::operator ()(
    const QByteArray &serverName,
    DWORD timeout
    )
{
  // API関数を実行する。
  Result result = NSFGetServerLatency(
        const_cast<char*>(serverName.constData()),
        timeout,
        retLatencyC2S_.pValue(),
        retLatencyS2C_.pValue(),
        retVersion_.pValue()
        );
  addValue<WORD>(result, retVersion_);
  addValue<DWORD>(result, retLatencyC2S_);
  addValue<DWORD>(result, retLatencyS2C_);
  return result;
}
