#ifndef GETSERVERLATENCY_H
#define GETSERVERLATENCY_H

#include "result.h"

#include <QTextStream>

/**
 * @brief クライアントーサーバ間の待ち時間とサーバのバージョンを取得します。
 * @class GetServerLatency
 */
class GetServerLatency
{
private:
  /**
   * @brief 戻り値管理用内部クラステンプレート
   * @class ReturnValue
   * @tparam T 戻り値のデータ型(WORDまたはDWORD)
   */
  template <typename T>
  class ReturnValue
  {
  public:
    /**
     * @brief コンストラクタ
     * @param isEnabled 有効ならTrue
     * @param key 戻り値のキーワード
     */
    ReturnValue(bool isEnabled, const QString &key)
      : isEnabled_(isEnabled)
      , value_(0)
      , key_(key)
    {}

    /**
     * @brief 有効ならTrueを返す。
     * @return 有効ならTrue
     */
    bool isEnabled() const
    {
      return isEnabled_;
    }

    /**
     * @brief 有効なら戻り値へのポインタ、無効ならヌルを返す。
     * @return 戻り値へのポインタまたはヌル
     */
    T* pValue()
    {
      return isEnabled_ ? &value_ : nullptr;
    }

    /**
     * @brief 戻り値をQVariant<uint>で返す。
     * @return
     */
    QVariant toVariant() const
    {
      return static_cast<uint>(value_);
    }

    /**
     * @brief マップデータ登録用のキーを返す。
     * @return キー
     */
    const QString &key() const
    {
      return key_;
    }

  private:
    bool isEnabled_;
    T value_;
    QString key_;
  };

public:
  /**
   * @brief Result登録用キーワード(バージョン)
   */
  static const char* const KEY_VERSION;
  /**
   * @brief Result登録用キーワード(クライアントーサーバ待ち時間)
   */
  static const char* const KEY_LATENCY_C2S;
  /**
   * @brief Result登録用キーワード(サーバークライアント待ち時間)
   */
  static const char* const KEY_LATENCY_S2C;

  /**
   * @brief コンストラクタ
   * @param bVersion サーババージョンの取得を有効にするか
   * @param bLatencyC2S クライアントからサーバへの待ち時間取得を有効にするか
   * @param bLatencyS2C サーバからクライアントへの待ち時間取得を有効にするか
   */
  GetServerLatency(
      bool bVersion = true,
      bool bLatencyC2S = true,
      bool bLatencyS2C = true
      );

  /**
   * @brief 関数オブジェクトメソッド
   * @param serverName サーバ名
   * @param timeout タイムアウト時間(ms) 0ならデフォルト
   * @return Resultオブジェクト
   */
  Result operator ()(const QByteArray &serverName, DWORD timeout = 0);

private:
  /**
   * @brief Resultオブジェクトに結果を追加する。
   * @tparam T ReturnValueの型。
   * @param result 追加先Resultオブジェクト
   * @param retVal 結果オブジェクト
   */
  template <typename T>
  void addValue(Result &result, const ReturnValue<T> &retVal)
  {
    if (retVal.isEnabled())
      result.insert(retVal.key(), retVal.toVariant());
  }

  ReturnValue<WORD> retVersion_;
  ReturnValue<DWORD> retLatencyC2S_;
  ReturnValue<DWORD> retLatencyS2C_;
};

#endif // GETSERVERLATENCY_H
