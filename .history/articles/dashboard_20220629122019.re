= Dashboard

この章から実際にNodeCGで使う画面を作成していきます。
DashboardとGraphicsのどちらの画面から作ってもよいのですが、変化した値をGraphicsで確認するために入力が必要なため、先にDashboardを作成するのをお勧めします。
コードを記述する前に、dashboardフォルダの中に@<code>{dashboard.js}と@<code>{dashboard.css}ファイルをそれぞれ作っておいてください。

== 作成のゴール

最初に今回作成するものの明確なゴールを確認しておきましょう。
Assetsでアップロードされた画像を利用し、それに紐づいた名前、役職、生死の状態を入力・制御し、Graphicsへ反映する入力画面を作成します。
この画面を作成するには、以下の機能が必要となります。
//list[goal][作成のゴール]{
 * Assetsでアップロードされた画像をリストにする
 * リストの画像に紐づいた名前を入力できる
 * リストの画像に紐づいた役職を制御できる
 * リストの画像に紐づいた生死状態を制御できる
 * 入力・制御した状態をGraphicsに反映する
//}

== HTML

まず最初にHTMLを作っていきましょう。
前章で作成したdashboardフォルダ内のindex.htmlに記述していきます。
HTMLは画面の構成を決めるほかにJavaScriptとCSSを読み込む機能があります。
今回はそれぞれ別のファイルにするため、それを利用する必要があります。

まずはHTMLの基盤を作成します。
//listnum[html1][index.html その1][html]{
<!DOCTYPE html>
<html>
  <body>
  </body>
</html>
//}
この記述はHTMLであることを示したり、表示する部分であることを示すものであるため、必ず書かなければならないおまじないと覚えてください。

まずはbodyタグの中にファイルの読み込みを書き込みます。
//listnum[html2][index.html その2][html]{
<!DOCTYPE html>
<html>
  <body>
    <script type="text/javascript" src="./dashboard.js"></script>
    <link rel="stylesheet" href="./dashboard.css">
  </body>
</html>
//}
scriptタグはJavaScriptを記述したり、読み込むために利用するタグです。
src属性でファイルを指定するか、タグの間に記述することでJavaScriptが利用できます。
今回は外部のファイルを読み込むために利用するので、src属性にファイルを指定しています。
読み込むファイルの名前に合わせて@<code>{./}より後を書き換えてください。
rel要素は言語の形式を指定するものですが、基本的にJavaScript以外を利用しないため固定です。
linkタグは外部のファイルを読み込むために利用するためのタグです。
rel属性でファイルが何かを示しています。
href属性はscriptタグのsrc属性と同じで、ファイルを指定します。
こちらも読み込むファイルの名前に合わせて@<code>{./}より後を書き換えてください。

次に実際に表示するリストとボタンを記述していきましょう。
リストを記述するとは言いましたが、アップロードされた画像を使う都合上、そのリストを作るのはJavaScriptで行うことになります。
そのため、実際にはリストの枠だけ作ります。
//listnum[html3][index.html その3][html]{
<!DOCTYPE html>
<html>
  <body>
    <script type="text/javascript" src="./dashboard.js"></script>
    <link rel="stylesheet" href="./dashboard.css">

    <ul id="playerList" class="playerList"></ul>
    <button id="submit">確定</button>
  </body>
</html>
//}
ここで追加したulタグとbuttonタグには必ずid属性を書いてください。
後々JavaScriptでリストを追加したり、ボタンの挙動で必要になります。
ulタグにはclass属性を指定しています。
CSSではid属性を使ってスタイルを指定することも可能ですが、基本的にはclass属性を使った方がCSSを書く際に楽になります。

NodeCGを起動するとDashbord画面のパネルが一つ追加され、そこに確定と書いてあるボタンが表示されるはずです。
これでHTMLは完成です。

== JavaScript

次にJavaScript（以下JS）を記述していきましょう。
前章で作成したdashboardフォルダ内のdashboard.jsに記述していきます。
JSではAssetsにアップロードされた画像を取得したり、入力された名前などのデータをGraphicsに送信するなどNodeCGに依存した処理があります。

まずは実際の処理を書く前に、下準備として以下の処理を書きましょう。
//listnum[js1][dashboard.js その1][javascript]{
window.onload = () => {

}
//}
これはJS特有の機能で、画面が表示されたら{}の中の処理を行うというものです。
このような処理が必要なのはJSの機能と関係しています。
JSは表示された画面の要素を取得する処理が存在します。
この処理が画面が表示される前に実行されると、存在しない画面の要素を取得しようとしてエラーになってしまいます。
つまり、処理のタイミングを合わせるためにこのようにしないといけないということです。

では、実際の処理を{}の中に書いていきましょう。
まずはAssetsでアップロードされた画像のデータを取得する処理を書いていきましょう。
//listnum[js2][dashboard.js その2][javascript]{
const playerData = []
const thumbnails = nodecg.Replicant('assets:nodecg-werewolf-games')

thumbnails.on('change', characters => {
  characters.forEach((item, index) => {
    playerData.push({
      name: item.base,
      url: item.url,
      isDead: false,
      position: 'murabito'
    })
  })
})
//}
ここではAssetsにアップロードされた画像の情報から、必要な情報をまとめてplayerDataとして組み立てなおしています。
@<code>{nodecg.Replicant('assets:nodecg-werewolf-games')}という処理はNodeCGで用意されたものです。
DashboardとGraphics、Asetts間でデータのやり取りをするための処理や情報の塊を取得する処理です。
Replicantの後の()の中にはどの画面とやり取りをするかを指定します。
今回の場合は@<code>{assets:nodecg-werewolf-games}となっていますが、これはAssets内のnodecg-werewolf-gamesを指定しています。
これ前章で作成したpackage.jsonで指定したassetCategoriesのnameと同じ必要があります。

4行目の@<code>{thumbnails.on}はAsettsの何かしらの操作があった場合に行う処理を設定するものです。
()の中にコンマで区切って二つの指定がしてあります。
一つ目はどのような操作があった場合に起動するかを指定しています。
今回は@<code>{change}となっていますが、これは画像のリストに変更があった場合、つまり画像がアップロードされたり削除された場合に起動します。
二つ目はどのような処理を行うかを指定しています。
@<code>{characters => }の個所のcharactersはAsettsにアップロードされている画像のデータのリストになっています。
その後の{}の中でforEachループを使ってcharactersの項目からそれぞれ必要な情報を引き抜き、ほかの情報とまとめてplayerDataリストの項目に追加しています。


Asettsにアップロードされた画像の取得はできたので、これを利用して管理画面にリストをが表示されるようにしましょう。
//listnum[js3][dashboard.js その3][javascript]{
const playerData = []
const thumbnails = nodecg.Replicant('assets:nodecg-werewolf-games')
const playerList = document.getElementById('playerList')

thumbnails.on('change', characters => {
  characters.forEach((item, index) => {
    const li = document.createElement('li')

    playerData.push({/* 省略 */})

    li.innerText(item.base)

    playerList.appendChild(li)
  })
})
//}
ここで追記したものは3、7、9行目です。
3行目ではHTMLタグデータの塊であるDOMを作成しています。
DOMは説明すると長くなってしまうので、今回はHTMLタグをJSで扱える形にしたものと覚えてください。


== CSS
