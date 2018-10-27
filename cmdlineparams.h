#ifndef CMDLINEPARAMS_H
#define CMDLINEPARAMS_H

#include <QVariant>

enum class Cmd {
  Unknown,
  GetServerLatency
};

/**
 * @brief コマンドラインパラメータクラス
 * @class CmdlineParamss
 */
class CmdlineParams
{
public:
  CmdlineParams();

  Cmd command() const;

  QVariantMap &params();

  void setCommand(const Cmd &cmd);

  void setParam(const QString &key, const QVariant &value);

private:
  Cmd command_;
  QVariantMap params_;
};

#endif // CMDLINEPARAMS_H
