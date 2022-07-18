= 画面を作る前に

NodeCGで画面を作るためには、予備知識としてWebページに関しての知識が必要になります。
そのため、この章ではその解説を行います。
ただし、ここで解説するのはあくまでもさわりの部分、基礎の部分であるため詳しく知りたい場合は各自検索してください。

== 画面作成に必要な知識

NodeCG、ひいてはWebページを作成する際に必要な知識は大きく分けて三つあります。
それらはHTML、CSS、JavaScriptです。
それぞれ、HTMLは画面の構成を決めるもので、CSSは画面の装飾をするためのもので、JavaScriptは画面の動きや操作させるものです。

少しわかりづらいので自動車で例えてみましょう。
HTMLは自動車で例えるとフレームやタイヤなどの最低限動くために必要なものになります。
とはいえ、それだけでは見栄えも悪いですし、走って止まる程度しかできないでしょう。
CSSは外装・内装に例えることができるでしょう。
つまり好みの色や形に自由に変えることができるということです。
JavaScriptは電気系統に例えることができます。
ライトやウィンカーを出したり、カーナビを使うようにさまざまな動きをさせることができます。

では、次章からはそれぞれ書き方などの詳細を見ていきましょう。

== HTML

前章でも説明したように、HTMLはWebページの構成を決めるためのものです。
よくプログラミング言語と言われていたりもしますが、まったく別のものです。

HTMLはタグというものを用いて記述します。
基本的には@<list>{html1}のように実際に表示したいものを開始タグと終了タグの中に記述します。
//list[html1][HTMLの基本的な書き方][html]{
<div>
  <div>
    HTMLはこのように書きます
  </div>
  <div>
    終了タグは開始タグの先頭に「/」を付けたものです
    <div>
      また、このようにタグを入れ子にすることもできます
    </div>
  </div>
</div>
//}
このタグには数多くの種類があるうえ、検索すればわかるもののため覚えなくて大丈夫です。
ただし、検索する場合は情報がほぼないサイトもあるため気を付けてください。
//table[html][HTMLタグの例]{
タグ	説明
--------------------------------
div	コンテンツを分けるためのタグ この中にあるものは一つのまとまりとして扱われる
label	入力の説明をするタグ inputタグと組み合わせて使う
ul	順序なしのリストを作るタグ
li	リストのアイテムのタグ ulの中で使う
input	入力欄のタグ テキストや色、ラジオボタンなどが指定可能
img	画像を表示するためのタグ
button	ボタンを作るタグ
//}

また、すべてのタグには属性と呼ばれる詳細な情報をつけることができます。
例えばタグに単一のIDを付けたり、CSSを利用するために必要だったり、それぞれに必要なデータを付けることができます。
基本的に無くても問題ありませんが、一部画像のURLを指定したり、入力形式を指定するために必須な場合もあります
//table[html2][属性の例]{
タグ	説明
--------------------------------
id	HTMLの中の識別子
class	cssを適応するための属性
type	inputタグでどの入力を利用するのかを指定
src	 imgタグで画像を指定
for	 labelタグでinputと紐づけるための属性
//}

== CSS

CSSはHTMLにスタイルを指定する、つまり装飾するためのものです。
MicrosoftのWordやExelにあるスタイルシートと同じものだと捉えて問題ありません。

このCSSというものはHTMLの好きな箇所に装飾ができます。
その装飾する箇所を指定するためには、基本的にはclass属性を利用しますが、id属性やタグに対応させることも可能です。
ただし、同じ属性やタグの場合、すべての個所に装飾されるので気を付けないといけません。
書き方としては@<list>{css1}のようになります。
//list[css1][CSSの書き方][css]{
.class {
  // {}の前に書かれているものがHTMLに対応
  // 先頭に.がついている場合はclass要素に対応
  // この{}の中に幅や高さ、背景色、文字の装飾などを記述
  width: 10px;
}
#id {
  // 先頭に#がついている場合はid要素に対応
  height: 10px;
}
div {
  // 先頭に何もついていない場合はタグに対応
  display: none;
}
//}

CSSの装飾に関してはHTMLタグ以上に存在しています。
ここで解説するときりがなくなるので割愛させていただきます。

== JavaScript

JavaScriptはプログラミング言語のひとつです。
web上で簡単に動かせたり、ページの表示を書き換えたり動かせるのが特徴です。
比較的簡単な言語であるため、プログラミングの基礎がわかれば一通りのことはできるかと思います。

プログラミングは基本的に4つの概念で成り立っているといえます。
それは変数、関数、条件分岐、ループ
の3つです。

=== 変数

変数とは値を入れる箱のようなものです。
例えば数値や文字を入れて計算したり比較したりすることができます。
また、この変数には関数と呼ばれる処理のかたまりを入れることもできます。
それ以外にも複数の変数を一つにして順序付けした配列や、項目という形で変数をまとめたオブジェクトというものがあります。
JavaScriptにはあとから中身を変えられる@<code>{let}と最初に入れたもので固定される@<code>{const}があります。
//list[js1][JavaScriptの変数][JavaScript]{
let num1 = 100
const num2 = 10
num1 = 50 // num1の中身が50に上書きされる
const num3 = num1 + num2 // num3にはnum1とnum2の中身を計算した結果の60が入る
//}

=== 関数

関数とは処理の塊です。
例えば変数を作り値を入れたり、その値で計算をしたりと様々なことを一つのまとまりにできます。
メインの処理の中ですべて処理をさせることもできはしますが、とても長くなってしまいとてもわかりづらくなってしまいます。
そういった場合に、関数を作り処理を分割してわかりやすくできます。

関数には引数と戻り値というものがあります。
引数は関数に渡される値、つまり関数の外部から指定する値です。
戻り値は引数とは逆に、関数の呼び出しもとに返す値です。
ただし、戻り値はない場合もあります。
皆さんは学生時代に数学で@<code>{y = f(x)}という関数を学んだかと思います。
プログラミングにおける関数と数学における関数は違う概念ですが、引数、戻り値の概念はほとんど同じです。
xが引数、yが戻り値、f()が関数そのものです。
JavaScriptでは@<list>{jsfunc}のように関数を作ります。
//list[jsfunc][JavaScriptの関数][JavaScript]{
const func = (hikisu1, hikisu2) => {
  // ここに処理を書く
  return modoriti // return の後に戻り値を書く
}

// 関数を実行する
// 変数に戻り値を代入することも可能
const result = func('hikisu1', 'hikisu2')
//}

=== 条件分岐

条件分岐とは、とある条件を満たした場合はこちらの処理を行い、満たしていないならばあちらの処理を行うといったものです。
例えば、財布を確認してある程度お金があれば外食し、なければカップ麺を食べるのようなものが条件分岐になります。
この場合、「お財布にお金があるかどうか」が条件になり、「外食」があった時の処理、「カップ麺を食べる」がなかった時の処理ということです。
また、条件を満たしていなかった場合、追加で条件分岐を設定することができます。
//list[js2][JavaScriptの条件分岐][JavaScript]{
if (wallet > 1000 /* ここに条件を書く */) {
  eatingOut() // 条件を満たしたときの処理
} else {
  eatCupNoodle() // 条件を満たさなかったときの処理
}
//}

=== ループ

ループとは、特定の処理を一定回数もしくは条件を満たすまで繰り返す処理のことです。
ネットスラングに無限ループという言葉がありますがそれも無限に繰り返すという意味であり、プログラミングで使われている言葉と同じ意味です。
JavaScriptでは指定回数ループさせるforループと、配列の項目数だけ繰り返すforEachループがよくつかわれます。
//list[js3][JavaScriptのループ][JavaScript]{
for(let i = 0; i < 10; i++) { // 10回繰り返すループ
  //繰り返し行う処理
}

const data = [1, 2, 3, 4, 5]

data.forEach((d) => { // 配列dataの項目数（今回は5回）繰り返す。 また、このdはループ時に各項目になっている。
  // 繰り返し行う処理
})
//}

=== JavaScript特有のもの

JavaScriptはWebページに根付いた言語であるため、ブラウザウィンドウの操作や、表示されているHTMLタグのオブジェクトであるDOMを操作する機能があります。
ウィンドウの操作は@<code>{window.hoge}、DOMの操作は主に@<code>{document.hoge}といった形で用意されています。
ただし、本書で主に使うものは@<code>{document}で用意されているものなため、@<code>{window}は忘れても構いません。
