#ifndef RESULT_H
#define RESULT_H

#include <QVariantMap>

// Notes C APIのインクルードは、Windowsではアラインメントを1バイトにして読み込む。
#ifdef NT
#pragma pack(push, 1)
#endif

#include <global.h>

#ifdef NT
#pragma pack(pop)
#endif

/**
 * @brief API関数戻り値クラス
 * @class Result
 */
class Result
{
public:
  /**
   * @brief コンストラクタ
   * @param status ステータス
   */
  Result(STATUS status = NOERROR);

  /**
   * @brief ステータスを返す。
   * @return ステータス
   */
  STATUS status() const;

  /**
   * @brief エラー部のみを返す。
   * @return ステータス(エラー部)
   */
  STATUS error() const;

  /**
   * @brief エラーがあればTrueを返す。
   * @return エラーがあればTrue
   */
  bool hasError() const;

  /**
   * @brief エラーがなければTrueを返す。
   * @return エラーがなければTrue
   */
  bool noError() const;

  /**
   * @brief キーが含まれていればTrueを返す。
   * @param key 検査するキー
   * @return キーが含まれていればTrue
   */
  bool contains(const QString &key) const;

  /**
   * @brief キーにあたる値を返す。
   * @param key キー
   * @return 値
   */
  QVariant value(const QString &key) const;

  /**
   * @brief 値を挿入する。
   * @param key キー
   * @param value 挿入する値
   */
  void insert(const QString &key, const QVariant &value);

private:
  STATUS status_;
  QVariantMap values_;
};

#endif // RESULT_H
