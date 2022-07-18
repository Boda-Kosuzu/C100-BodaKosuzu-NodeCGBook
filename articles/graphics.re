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

続けて役職名を表示するDOMを作りましょう。
//listnum[js3][createPosition][javascript]{
const position = {
  werewolf: '人狼',
  kyoujin: '狂人',
  kyousinsya: '狂信者',
  murabito: '村人',
  uranaishi: '占い師',
  reinousya: '霊能者',
  kishi: '騎士',
  kyouyuusya: '共有者',
  kitune: '狐',
  haitokusya: '背徳者'
}

const createPosition = positionId => {
  const positionName = document.createElement('div')
  positionName.innerText = position[positionId]
  positionName.classList.add('position-name')

  return positionName
}
//}
ここでは最初に役職のオブジェクトを作成しています。
役職のIDをキー、名前を値としているので表示するための役職名をIDで直接指定できます。
createPosition関数は役職IDを受け取り、組み立てたDOMを返しています。
特に変わったことはしていませんが、やはりここでもclassは忘れずにつけておいてください。

最後にプレイヤー名を表示するDOMを作りましょう。
//listnum[js4][createPlayerName][javascript]{
const createPlayerName = name => {
  const playerName = document.createElement('div')
  playerName.innerText = name.replace(/\.(png|jpg|jpeg|gif)/g, '')
  playerName.classList.add('player-name')

  return playerName
}
//}
この関数ではプレイヤー名を受け取って、それを使って組み立てたDOMを返しています。
ただし、今回受け取っているプレイヤー名はファイル名であるため、そのままだと拡張子(.pngとか.jpgとか)が付いたままになっています。
そこで今回は@<code>{string.replace('A', 'B')}という関数を使っています。
この関数はstringという文字列の中のAをすべてBに書き換えるという処理を行っています。
また、今回は書き換える対象が拡張子という、いくつかのパターンが存在するもののため、正規表現というものを使っています。
この正規表現は一言でいうならば、文字列がどういった構造になっているかを表すものです。
@<code>{/\.(png|jpg|jpeg|gif)/g}は.の後に()の中のどれかが並んだ文字列を表しています。
つまるところ、今回のreplaceはプレイヤー名の.pngか.jpgか.jpegか.gifを文字がない状態に書き換えて消しているということです。

では、最後に画面に反映されるように変更検知の関数の中に入れましょう。
//listnum[js5][変更検知 完成系][javascript]{
const playerList = document.getElementById('playerList')

replicant.on('change', players => {
  playerList.innerHTML = ''

  players.forEach(player => {
    const li = document.createElement('li')
    li.classList.add('player', player.position)

    if (player.isDead) li.classList.add('dead')

    li.appendChild(createBackIcon(player.position))
    li.appendChild(createPosition(player.position))
    li.appendChild(createPlayerImage(player.url))
    li.appendChild(createPlayerName(player.name))

    playerList.appendChild(li)
  });
})
//}
こちらでも特に変わったことはしていません。
HTMLから取得したulを一度リセットし、各プレイヤーの情報のリストをループさせてDOMを組み立て、順番にulに追加しています。
ulをリセットするのは、追加するという処理の都合上消さずにいるとどんどん表示が増えていってしまうためです。
また、この時に生死状態の管理もします。
@<code>{player.isDead}はtrue/falseのどちらかの値を持っているので、条件分岐にそのまま使うことができます。
isDeadがtrue、つまり死亡状態だった場合にdeadというクラスを付与しています。

すべての処理を書き終えたら一度NodeCGを起動して確認してみましょう。
Assetsで画像をアップロードして、Dashbordで役職を変えたり、生死の状態を変えたりして確定ボタンを押してみましょう。
Graphics画面を開くと、図5.1のように役職と画像、画像のファイル名が表示されると思います。
うまく動いていなかったら、一度書いたコードを確認してみてください。
//image[01][graphicsの動作確認][scale=0.7]

== CSS

最後にcssを書いていきましょう。
レイアウト画面は配信にのせるもののため、デザインをしっかりと考えて作りこんでいきましょう。

まずはフォントの設定をします。
CSSはフォントを変更することもできますが、デフォルトで用意されたもの以外は読み込まないといけません。
//listnum[css1][フォントの設定][css]{
@font-face {
  font-family: '源柔ゴシック';
  src: url('./font/GenJyuuGothicL-P-Bold.ttf');
}
//}
@<code>{font-family}はcssで指定する際の名前を設定します。
@<code>{src}はフォントのファイルの場所を示しています。
今回はcssファイルと同じ階層にfontというフォルダを作り、その中にフォントファイルを入れています。

次に全体にあたっている余計なCSSを削除します。
//listnum[css2][bodyのスタイルの削除][css]{
body {
  margin: 0;
  padding: 0;
}
//}
全体の表示に関わるbodyタグには大抵の場合@<code>{margin}と@<code>{padding}というスタイルがついています。
これらは隙間を制御するスタイルなのですが、全体にあたっていると余計な隙間の影響で表示したいものがはみ出ることがあります。

続けてリストのスタイルを作っていきましょう。
//listnum[css3][playerList][css]{
.playerList {
  width: 100vw;
  height: 100vh;
  margin: 0;
  padding: 25px;
  display: flex;
  flex-wrap: wrap;
  align-content: space-between;
  list-style: none;
  box-sizing: border-box;
}
//}
こちらはリストの大枠のスタイルです。
高さと幅を画面サイズと同じになるように指定しています。
marginと@<code>{list-style: none;}の指定ではulにデフォルトとなっている「・」の表示や文字の開始が右にずれている見た目を打ち消しています。
@<code>{display}、@<code>{flex-wrap}、@<code>{align-content}の三つはリストの中身の見た目を変更しています。
本来ならば縦一列に並ぶようになっていますが、横一列で幅に合わせて自動で折り返すようになります。
@<code>{box-sizing: border-box;}はpaddingのあたり方を指定するものです。
paddingもmarginもどちらも隙間を指定するものですが、コンテンツの内側か外側の違いがあります。
paddingはコンテンツの内側の隙間となっているため、背景色を付けた際にはこの隙間にも色が付きます。
ただし、幅を指定していた場合はその幅に加えて内側の隙間となって今します。
それが嫌な場合、つまり幅の中にその隙間を収めたい場合は@<code>{box-sizing: border-box;}の指定を利用します。

次はリスト内のアイテムの表示のスタイルを作ります。
今回はカードのような見た目にしていきます。
//listnum[css4][player][css]{
.player {
  width: 265px;
  height: 424px;
  border: 15px solid #F4F5F7;
  position: relative;
  box-sizing: border-box;
  border-radius: 10px;
  overflow: hidden;
}
//}
カードのような見た目にするために、幅と高さは固定しています。
今回はカードの白枠を作るために@<code>{border}というスタイルを利用しています。
これは枠線を作るためのスタイルで、枠の太さ、線の見た目、色を指定できます。
また、borderはpaddingと同様にコンテンツの幅に加えて枠線の太さを追加してしまうため、@<code>{box-sizing: border-box;}を指定しています。
カードのようにアイテムの角を丸めるために@<code>{border-radius}というスタイルを利用しています。
カードのような見た目にする都合上、立ち絵などの中の表示がはみ出ていたら明らかにおかしいので、@<code>{overflow: hidden;}ではみ出た箇所は表示されないようにしています。
@<code>{position: relative;}ですが、役職のアイコンの位置を調整するために必要なため、おまじないとして書いておいてください。

このままだとカードの背景が無色透明になっているので、役職に合わせて背景色を付けていきます。
//listnum[css5][カードの背景色][css]{
.werewolf,
.kyoujin,
.kyousinsya {
  background: radial-gradient(#c74754, #ad313b 40%, #621e2f);
}
.murabito,
.uranaishi,
.reinousya,
.kishi,
.kyouyuusya {
  background: radial-gradient(#5da2dc, #4286c9 40%, #264885);
}
.kitune,
.haitokusya {
  background: radial-gradient(#62c373, #3ba951 40%, #126627);
}
//}
この指定は役職ごとで同じ色になるようにしています。
クラスの指定は@<code>{,}を付けることで複数に同じスタイルを当てることができます。
今回は@<code>{background}という背景を指定するスタイルをあてています。
このスタイルは背景に色や画像を指定できるのですが、今回は色のグラデーションを指定しています。

カードの見た目はこれで綺麗になるのですが、カードとカードの間に隙間が無く詰まって見えてしまうので調整をしましょう。
//listnum[css6][カード間の隙間][css]{
.player + .player {
  margin-left: calc((100vw - 60px - 265px * 6) / 5);
}
.player:nth-child(6n + 1) {
  margin-left: 0;
}
.player:nth-child(n + 7) {
  margin-top: calc(100vh - 50px - 424px * 2);
}
//}
@<code>{.player + .player}の指定は前章でもお話した通り、前後で指定したクラスが連続した場合にスタイルを適用するという指定です。
今回はリストのアイテムの二つ目以降に適用されます。
@<code>{:nth-child()}は()内の数字番目のクラスにスタイルを適応するという指定です。
例えば、数字が2の場合は全体で2番目にplayerとクラスに指定された箇所に適応されます。
また、この数値はnを利用することで数列のように指定することが可能です。
今回の@<code>{6n + 1}は6の倍数に1を足した数である7、13……を、@<code>{n + 7}は7番目以降すべてを意味しています。
そうした指定で、それぞれにmarginを左や上につけています。
marginの指定に@<code>{calc()}というものを使っていますが、これはcss側が計算をして幅を決めてくれます。
今回はカード間の幅を決めているのですが、それぞれカードの幅や高さと全体に付けられている上下左右の隙間を考えて計算させています。

次に役職のアイコンのスタイルを作っていきましょう。
今回利用したアイコンはwebサイト「ICON MONO」様(https://icooon-mono.com/)にて配布されているものです。
そこからダウンロードしたアイコンを同じ階層に作ったiconフォルダの中に配置しています。
//listnum[css7][カード間の隙間][css]{
.icon {
  width: 100%;
  height: 100%;
  position: absolute;
  background: #F4F5F7;
  -webkit-mask-position: center;
  -webkit-mask-repeat: no-repeat;
  -webkit-mask-size: 90%;
}
.backIcon-werewolf {
  -webkit-mask-image: url('./icon/狼アイコン4.png');
}
//}
@<code>{icon}クラスではすべてのアイコンで共通のスタイルをあてています。
今回、もともとアイコンが黒色であり背景に混ざると見づらい可能性があったため、少し変わった手法で白色にています。
高さと幅は親と同じになるようにしています。
この場合の親はカードの背景色がかかっている箇所になります。
@<code>{position: absolute;}は基本的にコンテンツを自由に配置したい時に使うものです。
topやleftなどの位置をpx単位で指定することで、配置する場所を動かすことができます。
ただし、今回はカード内のコンテンツが重なるようになってほしいので指定しています。
@<code>{background}より下のスタイルがアイコンの色を変えるためのものです。
ざっくりした説明をすると、画像の透明でない箇所だけ背景をくりぬいて表示するイメージです。
@<code>{-webkit-mask-position}はマスクの位置をどこに置くのか、@<code>{-webkit-mask-repeat}はマスクの繰り返し（同じ画像を複数置く）かどうか、@<code>{-webkit-mask-size}は文字通りマスクのサイズをそれぞれ指定しています。
@<code>{.backIcon-werewolf}クラスではマスクの画像を指定しています。
@<code>{-webkit-mask-image: url('');}でアイコンの画像を指定しています。
また、ここでは例として一つだけを上げていますが、役職の分だけアイコンを用意しています。

次に役職名の表示のスタイルを作りましょう。
//listnum[css8][position-name][css]{
.position-name {
  top: 10px;
  position: absolute;
  writing-mode: vertical-rl;
  font-size: 48px;
  font-family: '源柔ゴシック';
  color: #F4F5F7;
  text-shadow: -2px 2px 0 #5e5e5e, -4px 4px 0 #f4f5f7, -6px 4px 10px #5e5e5e;
  z-index: 10;
}
//}
topとpositionで表示する位置を調整しています。
@<code>{writing-mode}は文字を縦書き横書きを指定するスタイルです。
今回は縦書きになるようにしています。
@<code>{font-size}、@<code>{font-family}、@<code>{color}はすべて文字に関するスタイルです。
それぞれ文字の大きさ、フォント、文字色を指定しています。
@<code>{text-shadow}は文字に影を付けるスタイルです。
ぼかした影を付けるのはもちろんですが、ぼかさずに同じ文字を表示する、といったことも可能です。
今回はそれを利用してずれた文字のようにしています。
@<code>{z-index}は各コンテンツの重なりの順番を指定しています。
数字が大きいほど重なりとしては上になります。
今回は一番上になってほしいため、大きめの数字にしています。

次はアップロードした画像のスタイルを作ります。
とはいえ、ここはあまり適用しているものはありません。
//listnum[css9][player-image][css]{
.player-image {
  width: 100%;
  position: relative;
}
//}
widthの%指定は、親コンテンツの幅を基準にどのぐらいの%幅にするかの指定です。
つまり、今回の100%は親コンテンツであるカードの幅と同じ幅にするという意味です。
@<code>{position: relative;}というスタイルをあてていますが、これは付けていないと役職のアイコンとの重なり順がおかしくなってしまうためです。

次にプレイヤー名のスタイルを作ります。
//listnum[css10][player-name][css]{
.player-name {
  width: 100%;
  height: 70px;
  bottom: 0px;
  position: absolute;
  display: flex;
  justify-content: center;
  align-items: center;
  background: #f4f5f7;
  font-family: '源柔ゴシック';
  font-size: 36px;
  color: #5e5e5e;
}
//}
幅は親に固定、高さはpxで固定にしています。
表示箇所はpositionとbottomで固定しています。
@<code>{display: flex;}、@<code>{justify-content: center;}、@<code>{align-items: center;}は表示位置を調整しています。
justify-contentは左右の位置、align-itemsは上下の位置を調整しています。
今回はどちらも中央にしています。
残りの指定は、背景色や文字の色、大きさなどをしています。

最後に、死亡した時のスタイルを作成します。
//listnum[css11][player-image][css]{
.dead {
  filter: grayscale(100%);
}
//}
@<code>{filter}は様々な効果を付けることができます。
今回はグレースケール、つまり灰色にするフィルターになっています。

これでCSSは完成です。
NodeCGで確認してみましょう。
すべてのCSSが問題なければ、図5.2のようになっているはずです。
//image[02][graphicsの完成][scale=0.7]
