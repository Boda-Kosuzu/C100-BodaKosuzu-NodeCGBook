= Dashboard

この章から実際にNodeCGで使う画面を作成していきます。
DashboardとGraphicsのどちらの画面から作ってもよいのですが、変化した値をGraphicsで確認するために入力が必要なため、先にDashboardを作成するのをお勧めします。
コードを記述する前に、dashboardフォルダの中に@<code>{dashboard.js}と@<code>{dashboard.css}ファイルをそれぞれ作っておいてください。

== 作成のゴール

最初に今回作成するものの明確なゴールを確認しておきましょう。
アップロードされた画像を利用し、それに紐づいた名前、役職、生死の状態を入力・制御する入力画面を作成するのがゴールです。
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

NodeCGを起動し、確認すると図4.1のようになっていると思います。
これでHTMLは完成です。
//image[01][HTMLの完成][scale=0.7]

== JavaScript

次にJavaScript（以下JS）を記述していきましょう。
前章で作成したdashboardフォルダ内のdashboard.jsに記述していきます。
JSではAssetsにアップロードされた画像を取得したり、入力された名前などのデータをGraphicsに送信するなどNodeCGに依存した処理があります。

まずは実際の処理を書く前に、下準備として以下の処理を書きましょう。
//listnum[js1][dashboard.js その1][javascript]{
window.onload = () => {

}
//}
この@<code>{window.onload}はJS特有の機能で、画面が表示されたら{}の中の処理を行うというものです。
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
()の中にコンマで区切って二つの引数があります。
一つ目はどのような操作があった場合に起動するかを指定しています。
今回は@<code>{change}となっていますが、これは画像のリストに変更があった場合、つまり画像がアップロードされたり削除された場合に起動します。
二つ目はどのような処理を行うかを指定しています。
@<code>{characters => }の個所のcharactersはAsettsにアップロードされている画像のデータのリストになっています。
その後の{}の中でforEachループを使ってcharactersの項目からそれぞれ必要な情報を引き抜き、ほかの情報とまとめてplayerDataリストの項目に追加しています。
今回利用している情報は@<code>{base}と@<code>{url}の二つです。
これらはそれぞれ、ファイル名とファイルの場所を記録している変数です。

Asettsにアップロードされた画像の取得はできたので、これを利用して管理画面にリストをが表示されるようにしましょう。
//listnum[js3][dashboard.js その3][javascript]{
const playerData = []
const thumbnails = nodecg.Replicant('assets:nodecg-werewolf-games')
const playerList = document.getElementById('playerList')

thumbnails.on('change', characters => {
  characters.forEach((item, index) => {
    const li = document.createElement('li')
    listItem.classList.add('playerList-classList')

    playerData.push({/* 省略 */})

    li.innerText = item.base

    playerList.appendChild(li)
  })
})
//}
ここで追記したものは3、7、8、12、14行目です。
3行目では先ほど作成したHTMLのDOMを取得しています。
今回使っている@<code>{document.getElementById}は、HTMLのID属性を利用してDOMを取得します。
つまり前節で作成したHTMLのplayerListというIDのulタグをDOMとして取得しています。
7行目ではDOMを作成しています。
@<code>{document.createElement('')}の''内に作成したいタグの名前を記入することでDOMを作成できます。
8行目では7行目で作成したDOMにclass属性を付与しています。
DOMではclass属性で指定されたものは@<code>{classList}というリストで保持されています。
これにaddで追加したり、削除したりすることで指定することができます
12行目では7行目で作成したDOMのHTMLタグの中にテキストを挿入しています。
@<code>{innerText}にテキストを代入します。
この段階では変数liの中のDOMを表示すると、@<code>{<li>アップロードした画像ファイル名</li>}となります。
最後の14行目では3行目に取得したulのDOMに、11行目で作成したliのDOMを挿入しています。
@<code>{挿入されるDOM.appendChild(挿入するDOM)}と記述することでDOMを組み立てることができます。
今回の場合は挿入されるDOMはもともとHTMLに記述してあるもののため、このappendChildが実行された時点で挿入したDOMは表示されることになります。
ファイル保存後にNodeCGでAsettsに画像をアップロードしてみると、ファイル名が一覧として表示されるはずです。

続けて画像一覧に入力欄を作っていきましょう。
これは画像に紐づけていきたいので、先ほどのforEachの中に追記していきます。
ただし、forEachの中にべた書きすると非常に長くなってしまい、管理が大変になってしまいます。
そのため、それぞれの入力欄を作る処理を分割して関数にしましょう。
今回は三つの関数に分割して作成します。

@<list>{js4}は画像ファイル名を表示するDOMを作る関数です。
画像ファイル名を引数として受け取り、それを使って組み立てたDOMを戻り値として返しています。
createElementでファイル名を表示するDOMを作成し、そこにinnerTextで受け取った名前を挿入しています。
//listnum[js4][画像ファイル名][javascript]{
const createImgName = name => {
  const imgName = document.createElement('div')
  imgName.innerText = name

  return imgName
}
//}

@<list>{js5}は役職を選択する機能を作る関数です。。
画像リストの何番目かとその画像リストの番号に対応したplayerDataリストのアイテムを引数として受け取っています。
そして、その引数を使って組み立てたDOMを戻り値として返しています。
また、ここでは関数の外に役職の名前と表示名のオブジェクトのリストを作成しています。

この関数ではselectタグを作成しています。
このタグは文字通りいくつかの選択肢から項目を選ぶ入力欄になっています。
その中に選択肢を作るoptionタグを入れることで選択欄が作られます。
今回、selectタグにはvalue属性を付けています。
value属性は現在どの選択肢が選ばれているかを示しています。
初期値では村人が選ばれている状態にしたいので、'murabito'を代入しています。

optionタグは選択肢すべてを書いていたら役職分createElementを書くことになるため、関数外で作成したリストを利用してループで作ります。
optionタグのvalue属性は選択したときに、JSで使う値です。
また、村人のoptionタグのselected属性をtrueにしています。
selected属性は選択肢として最初から選ばれていてほしいものにつける属性です。

最後にselectタグの選択が変わった時の処理を書いています。
@<code>{selectタグのDOM.onchange}に選択が変わったときに実行される関数を代入することで、任意の処理を実行することができます。
今回は選択によって変わったvalueを引数のplayerDataのposition、つまり役職のデータの変数に上書きしています。
//listnum[js5][役職選択][javascript]{
const positions = [
  { name: 'werewolf', display: '人狼'},
  { name: 'kyoujin', display: '狂人'},
  { name: 'kyousinsya', display: '狂信者'},
  { name: 'murabito', display: '村人'},
  { name: 'uranaishi', display: '占い師'},
  { name: 'reinousya', display: '霊能者'},
  { name: 'kishi', display: '騎士'},
  { name: 'kyouyuusya', display: '共有者'},
  { name: 'kitune', display: '狐'},
  { name: 'haitokusya', display: '背徳者'},
]

const createPositionSelect = (index, item) => {
  const select = document.createElement('select')
  select.value = 'murabito'

  positions.forEach(position => {
    const option = document.createElement('option')
    option.innerText = position.display
    option.value = position.name
    if (position.name === 'murabito') option.selected = true

    select.appendChild(option)
  })

  select.onchange = (e) => {
    item.position = select.value
  }

  return select
}
//}

@<list>{js6}はプレイヤーの生死状態を制御する機能を作る関数です。
@<list>{js5}と同様に、画像リストの何番目かとその画像リストの番号に対応したplayerDataリストのアイテムを引数として受け取っています。
そして、その引数を使って組み立てたDOMを戻り値として返しています。
返却するDOMのつくりは、divタグの中にinput:checkboxとlabelが入っている形です。

input:checkboxはinputタグのtype属性をcheckboxにしたものです。
このタグはチェックを入れたり消したりできる入力欄になります。
属性はtype以外にidとcheckedを指定しています。
idはこの後に説明するlabelと紐づけるために必要です。
id属性の値はcheckbox-に画像リストの何番目かの値を組み合わせたものを代入しています。
checked属性はチェックされているかどうかを設定できます。
表示時はチェックされていない状態であってほしいため、今回はfalseを代入しています。
また、selectの時と同じように、値の変更があった時の関数をonchangeに代入しています。
チェックボックスのチェック状態を役職のデータの変数である、引数のplayerDataのisDeadに上書きしています。

labelタグはinputに紐づけられたテキストを表示するためのタグです。
今回はinput:checkboxと紐づけて、チェックボックスだけなくテキストをクリックしたときにもチェックの制御ができるようにします。
labelにsetAttributeでfor属性を付与します。
基本的にDOMは子に属性を持っているので@<code>{DOM.attribute}という形で指定しますが、for属性などの一部の属性はsetAttributeを利用して付与します。
@<code>{DOM.setAttribute('attribute', `data`)}という形で指定します。
つまり今回は、for属性にcheckbox-に画像リストの何番目かの値を組み合わせたものを代入しているということです。
ここで気づくかもしれませんが、このlabelタグのfor属性は先ほどのinput:checkboxのid属性と同じ値を代入しています。
この二つを同じにすることで、テキストをクリックしてもチェックの制御ができるようになります。

最後に、チェックボックスとラベルのDOMをdivタグのDOMにappendChildで挿入しています。
ここでは挿入する順番に気を付けてください。
appendChildはタグの子の一番最後に追加する仕様になっています。
つまり今回はラベルを一番目、チェックボックスを二番目に表示されるようにしていることになります。
逆でも問題ないのですが、人間の認知の関係で左から右、上から下のほうがわかりやすいです。
//listnum[js6][生死状態][javascript]{
const createCheckbox = (index, item) => {
  const check = document.createElement('div')
  const text = document.createElement('label')
  const checkbox = document.createElement('input')

  checkbox.id = `checkbox-${index}`
  checkbox.type = 'checkbox'
  checkbox.checked = false
  checkbox.onchange = () => {
    item.isDead = checkbox.checked
  }

  text.setAttribute('for', `checkbox-${index}`)
  text.innerText = '死亡'

  check.appendChild(text)
  check.appendChild(checkbox)

  return check
}
//}

次に作った関数を@<list>{js4}の中から呼び出してみましょう。
@<list>{js7}の17～19行目が関数を呼び出している部分です。
戻り値を変数で受け取ってからappendChildでliに挿入してもいいのですが、その分行数が多くなってしまうので今回は直接関数をappendChildの引数にしています。
//listnum[js7][thumbnails.on 完成][javascript]{
thumbnails.on('change', characters => {
  playerList.innerHTML = ''
  playerData = []

  characters.forEach((item, index) => {
    const li = document.createElement('li')
    const listItem = document.createElement('div')
    listItem.classList.add('playerList-classList')

    playerData.push({
      name: item.base,
      url: item.url,
      isDead: false,
      position: 'murabito'
    })

    listItem.appendChild(createImgName(item.base))
    listItem.appendChild(createPositionSelect(index, playerData[index]))
    listItem.appendChild(createCheckbox(index, playerData[index]))

    li.appendChild(listItem)

    playerList.appendChild(li)
  })
})
//}
これで一度NodeCGを起動してみてみましょう。
Assetsで画像をアップロードしたら、Workdspaceが図のようになっているならば大丈夫です。

最後に確定ボタンの制御を作ります。
//listnum[js8][確定ボタンの制御][javascript]{
const submit = document.getElementById('submit')

submit.onclick = () => {
  replicant.value = playerData
}
//}
リストと同様にgetElementByIdでボタンのDOMを取得し、onclickに関数を代入します。
このonclickは名前の通りにクリックしたときの処理を代入するためのものです。
今回はreplicant.valueに全プレイヤーのデータのリストを代入しています。
replicantは最初に宣言したNodeCGで用意された変数です。
その中にあるvalueを変更するだけで、あとはNodeCG側で自動で処理をしてくれます。

== CSS

最後にcssを書いていきましょう。
ただし、ここで作成しているWorkdspaceのパネルは管理画面です。
つまり、配信に移すことのない、自分だけが見るものです。
そのため、あまり凝った作りにせずに最低限わかりやすくするためだけにとどめています。
//listnum[css][CSS][css]{
.playerList-classList {
  display: flex;
}

.playerList-classList > * + * {
  margin-left: 15px;
}
//}
一つ目の指定はclass属性で@<code>{.playerList-classList}が指定されているタグにスタイルをあてています。
displayプロパティはHTMLの表示ルールやレイアウトを変更するプロパティです。
今回はflexというレイアウトを変更する指定をしています。
指定をしない場合では縦一列になりますが、flexを指定することで横に一列に表示されます。

二つ目の@<code>{.playerList-classList > * + *}はスタイルをあてる場所の指定が少し複雑になっています。
今回の場合.playerList-classListというclassが当てられたタグの子のタグの二番目以降すべてにスタイルがあたります。

>と+の記号が場所を表し、*がどのタグに充てるかを指定しています。
なお、場所を表す記号はどこに充てるかまでは指定しないので、それで終わることはできません。

*で指定されるタグはすべてのタグです。
どんなタグの形式、class属性、id属性など関係なく、ありとあらゆるタグにクラスが当てられます。

>は左の指定の子の中にある右にスタイルを当てるという意味です。
今回はplayerList-classListというclassが指定されたタグの子を意味します。
@<code>{.playerList-classList > *}と指定された場合、@<list>{css2}の箇所にスタイルが当てられます。
//listnum[css2][.playerList-classList > *のスタイルのあたる箇所][html]{
<div class='playerList-classList'>
  <div>hoge</div> <!-- ここ -->
  <div>fuga</div> <!-- ここ -->
</div>
//}

+は前後で指定したタグが連続した場合、後（右）にスタイルをあてるという意味です。
指定されたタグが同じ階層に複数あった場合、二番目以降すべてにスタイルがあたります。
@<code>{* + *}と指定された場合、@<list>{css3}の箇所にスタイルが当てられます。
//listnum[css3][* + *のスタイルのあたる箇所][html]{
<div>hoge</div>
<div>fuga</div> <!-- ここ -->
<div>piyo</div> <!-- ここ -->
//}

これら二つの指定が組み合わさると、.playerList-classListというclassが当てられたタグの子のタグの二番目以降すべてというしていになるわけです。
言葉にすると少しわかりづらいのですが、実際にスタイルがあたる場所が@<list>{css4}になります。
//listnum[css4][今回の指定でスタイルのあたる箇所][html]{
<div class='playerList-classList'>
  <div>hoge</div>
  <div>fuga</div> <!-- ここ -->
  <div>piyo</div> <!-- ここ -->
</div>
//}

あたる場所はわかりましたので、適用されているスタイルを見てみましょう。
marginは隙間を開けるためのプロパティです。
本来は上下左右すべてに隙間をあけるのですが、今回はmargin-leftという指定になっているので、左側のみに隙間をあけます。


CSSの記述も終わったので、再びNodeCGを見てみましょう。
画像をアップロードし、Workdspaceのパネルを確認すると図のようになっているかと思います。

== 完成

これで管理画面は完成です。
ただ、これだけではちゃんとできているのがわかりづらくはあります。
レイアウト画面に反映されるのを確認してようやく管理画面が完成と言えなくもありません。
実際に動作の確認は次の章にまとめて行うことになります。
