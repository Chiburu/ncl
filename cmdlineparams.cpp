#include "cmdlineparams.h"

CmdlineParams::CmdlineParams()
  : command_(Cmd::Unknown)
  , params_()
{}

Cmd CmdlineParams::command() const
{
  return command_;
}

QVariantMap &CmdlineParams::params()
{
  return params_;
}

void CmdlineParams::setCommand(const Cmd &cmd)
{
  command_ = cmd;
}

void CmdlineParams::setParam(const QString &key, const QVariant &value)
{
  params_.insert(key, value);
}
