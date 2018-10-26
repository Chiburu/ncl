#include "result.h"

Result::Result(STATUS status)
  : status_(status)
  , values_()
{}

STATUS Result::status() const
{
  return status_;
}

STATUS Result::error() const
{
  return ERR(status_);
}

bool Result::hasError() const
{
  return error() != NOERROR;
}

bool Result::noError() const
{
  return !hasError();
}

bool Result::contains(const QString &key) const
{
  return values_.contains(key);
}

QVariant Result::value(const QString &key) const
{
  return values_.value(key);
}

void Result::insert(const QString &key, const QVariant &value)
{
  values_.insert(key, value);
}
