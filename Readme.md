Notes Commandline Tool
======================

コマンドラインからNotes C APIを通してNotes環境にアクセスするコマンドツールです。

# Requirement

  * Visual Studio(C++) (>= 2015)

  * Qt (>= 5.2)

  * IBM Notesクライアント

  * IBM C API Toolkit(Notesクライアントのバージョンと合わせる)

# History

* v0.0.1 - 2018-10-23

  * NSFGetServerLatency関数を利用して、pServer定数に指定したサーバのバージョン(ビルド番号)を取得します。
  * GET_LATENCY_TIMEシグネチャを有効にすると、そのサーバとの通信にかかる待ち時間も取得できます。
  * プロジェクトファイル(.pro)の「NotesCAPIDir」変数に、Notes C APIを展開したディレクトリを指定して、ヘッダファイル、リンクファイルを解決します。なお、プロジェクトファイルで指定するパスの区切り記号は、Windowsであっても/(スラッシュ)です(バックスラッシュは複数行にまたがる文に使用します)。
  * 実行時に、Notesクライアントのプログラムフォルダにパスを通すようにします。VCやQtのランタイムも同様です。
