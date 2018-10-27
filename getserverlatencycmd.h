#ifndef GETSERVERLATENCYCMD_H
#define GETSERVERLATENCYCMD_H

#include <QVariantMap>

//class QStringList;
//class QVariantMap;

/**
 * @brief コマンド版GetServerLatency
 * @class GetServerLatencyCmd
 */
class GetServerLatencyCmd
{
public:
  QStringList operator ()(QVariantMap &params);
};

#endif // GETSERVERLATENCYCMD_H
