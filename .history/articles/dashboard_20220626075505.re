= Dashboard

この章から実際にNodeCGで使う画面を作成していきます。
DashboardとGraphicsのどちらの画面から作ってもよいのですが、変化した値をGraphicsで確認するために入力が必要なため、先にDashboardを作成するのをお勧めします。
コードを記述する前に、dashboardフォルダの中に@<code>{dashboard.js}と@<code>{dashboard.css}ファイルをそれぞれ作っておいてください。

== 作成のゴール

最初に今回作成するものの明確なゴールを確認しておきましょう。
Assetsで入力された画像を利用し、それに紐づいた名前、役職、生死の状態を入力・制御し、Graphicsへ反映する入力画面を作成します。
この画面を作成するには、以下の機能が必要となります。
//list[goal][作成のゴール]{
 * Assetsで入力された画像をリストにする
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

入力欄やボタンは作成した基盤のbodyタグの中に記述していきます。
まずはファイルの読み込みを書き込みます。
基本的にHTMLは上から順番に読み込み、表示されるという特性があります。
そのため、複数のファイルを読み込む際にはその順番に気を付けてください。
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
読み込むファイルは同じ階層に作った場合は、ファイル名に合わせて@<code>{./}より後を書き換えてください。
また、rel要素は言語の形式を指定するものですが、基本的にJavaScript以外を利用しないため固定です。
linkタグは外部のファイルを読み込むために利用するためのタグです。
rel属性でファイルが何かを示していますが、基本的にCSSの@<code>{stylesheet}とアイコンの@<code>{icon}である場合が多いです。
href属性はscriptタグのsrc属性と同じで、ファイルを指定します。

== CSS

== JavaScript
