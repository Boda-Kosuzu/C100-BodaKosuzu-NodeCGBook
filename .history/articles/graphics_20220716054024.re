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

次にJavaScript（以下JS）を記述していきましょう。
こちらも、先ほど作成した@<code>{graphics.js}に記述していきます。

まずは管理画面の入力の変更を検知する処理を書いていきましょう。
//listnum[js1][変更検知][javascript]{
window.onload = () => {
  const replicant = nodecg.Replicant('nodecg-werewolf-games')
  replicant.on('change', players => {
    // ここに変更を検知した際の処理を書く
  })
}
//}
管理画面の時と同じように、すべての処理はonloadに記述します。
変更を検知するためにはNodeCGの管理オブジェクトを取得する必要があります。
これは管理画面でAssetsの画像の時とほとんど同じです。
ただし、今回の()の中の指定はpackage.jsonで指定したdashboardPanelsのnameと同じ必要があります。
また、Assetsの際は@<code>{assets:}を付けていましたが、Dashboardの値を指定する場合は@<code>{dashboard:}のような指定は不要です。

変更の検知はAssetsの画像と同じになります。
ただし、playersは画像のデータのリストではなく、管理画面で入力したデータのリストとなっています。

次にプレイヤーの立ち絵などが表示できるようにしていきます。
まずは立ち絵の後ろに表示する、役職のアイコンのDOMを作る関数作っていきましょう。
//listnum[js2][createBackIcon][javascript]{
const createBackIcon = positionId => {
  const backIcon = document.createElement('div')
  backIcon.classList.add('icon', `backIcon-${positionId}`)

  return backIcon
}
//}
この関数は役職のIDを引数として受け取り、組み立てたDOMを戻り値として返します。
divを作成してclassにiconと@<code>{backIcon-役職ID}を指定しています。
今回、アイコンはCSSで指定しているので、このような形となっています。

== CSS
