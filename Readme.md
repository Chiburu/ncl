Notes Commandline Tool
======================

コマンドラインからNotes C APIを通してNotes環境にアクセスするコマンドツールです。

# Requirement

  * Visual Studio(C++) (>= 2015)

  * Qt (>= 5.2)

  * IBM Notesクライアント

  * IBM C API Toolkit(Notesクライアントのバージョンと合わせる)

# History

* v0.0.3 - 2018-10-27

  * GetServerLatency関数オブジェクトをコマンド化します。

  ```
  > ncl get-server-latency --server=yourserver --return=ver,c2s,s2c
  >
  > ver=405,c2s=0,s2c=10
  ```

* v0.0.2 - 2018-10-26

  * NSFGetServerLatency関数をラップして、関数オブジェクトにします。
  * STATUSとその他の値を1オブジェクトで返すことが可能なクラスResultを定義します。

* v0.0.1 - 2018-10-23

  * NSFGetServerLatency関数を利用して、pServer定数に指定したサーバのバージョン(ビルド番号)を取得します。
  * GET_LATENCY_TIMEシグネチャを有効にすると、そのサーバとの通信にかかる待ち時間も取得できます。
  * プロジェクトファイル(.pro)の「NotesCAPIDir」変数に、Notes C APIを展開したディレクトリを指定して、ヘッダファイル、リンクファイルを解決します。なお、プロジェクトファイルで指定するパスの区切り記号は、Windowsであっても/(スラッシュ)です(バックスラッシュは複数行にまたがる文に使用します)。
  * 実行時に、Notesクライアントのプログラムフォルダにパスを通すようにします。VCやQtのランタイムも同様です。
