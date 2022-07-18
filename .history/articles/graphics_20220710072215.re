= Graphics

この章ではレイアウト画面を作成していきます。
こちらは配信に乗せる画面であるため、こだわって作りましょう。
Dashboardの時と同様に、graphicsフォルダの中に@<code>{graphics.js}と@<code>{graphics.css}ファイルをそれぞれ作っておいてください。

== 作成のゴール

最初に今回作成するものの明確なゴールを確認しておきましょう。
管理画面で選択した役職や生死状態が立ち絵とともに表示される画面を作成するのがゴールです。

この画面を作成するには、以下の機能が必要となります。
//list[goal][作成のゴール]{
 * Assetsでアップロードされた画像を表示されている
 * プレイヤー名（画像名）が表示されている
 * 役職が何かわかるようになっている
 * 死亡した状態がわかるようになっている
//}

== HTML

レイアウト画面もHTMLから作成していきましょう。
こちらも管理画面と同じく画像や状態はJSで制御することになるため、実際に作るのはファイルの読み込みと画像リストの大枠のみです。
//listnum[html3][index.html その3][html]{
<!DOCTYPE html>
<html>
  <body>
    <script type="text/javascript" src="./graphics.js"></script>
    <link rel="stylesheet" href="./graphics.css">

    <ul id="playerList" class="playerList"></ul>
  </body>
</html>
//}

基本的に前章で解説したタグを利用しているので、特に目新しいものはありません。
ただし、レイアウト画面ではスタイルが重要になってきますので、class属性は必ず付与してください。

== JavaScript

== CSS
