= NodeCG画面作成時に必要なもの

NodeCGで画面を作成するために、最低限必要なものは3つあります。
package.jsonファイル、dashboard配下のindex.htmlファイル、graphics配下のindex.htmlファイルの3つです。
dashboard配下に置いたものは管理画面に表示され、graphics配下に置いたものは配信レイアウトとして表示されます。
それぞれのindex.htmlの詳細はのちの章でお話しします。
これ以降の章では、nodecg-werewolf-gamesというバンドルを作成するというかたちで進めていきます。

== フォルダー構成

バンドルを作成する際に最低限必要なファイルは、先ほども説明した通りに3つだけです。
最初は@<list>{folder}にあるファイルのみで問題ありません。
ファイルを作る場合はテキストファイルを一度作成し、ファイル名を拡張子ごと変えることで作成できます。
また、これらのフォルダやファイルはnodeCGのフォルダ内にあるbundlesフォルダの中に作ってください。
//list[folder][フォルダー構成][html]{
nodecg
  ┗ bundles
    ┗ nodecg-werewolf-games
      ┣ dashboard
      ┃ ┗ index.html
      ┣ graphics
      ┃ ┗ index.html
      ┗ package.json
//}

== package.json

package.jsonはバンドルの設定を記述しておくファイルになります。
@<list>{package}は最低限package.jsonに書いておく必要がある設定です。
//list[package][package.json][html]{
{
  "name": "nodecg-werewolf-games",
  "version": "1.0.0",
  "description": "",
  "nodecg": {
    "compatibleRange": "^1.0.0",
    "dashboardPanels": [
      {
        "width": "3",
        "name": "nodecg-werewolf-games",
        "title": "人狼ゲーム",
        "file": "index.html"
      }
    ],
    "graphics": [
      {
        "file": "index.html",
        "width": "800",
        "height": "600"
      }
    ],
    "assetCategories": [
      {
        "name": "nodecg-werewolf-games",
        "title": "nodecg-werewolf-games",
        "allowedTypes": ["jpg", "jpeg", "gif", "png"]
      }
    ]
  }
}
//}

「name」は文字通り、バンドルの名前を記しています。
「version」はこのバンドルのバージョンを記しています。特に理由が無ければ、1.0.0から始めて更新するたびに上げていきます。
「description」はこのバンドルの大まかな説明です。

「nodecg」はこのファイルのメインです。
NodeCGのバージョンやHTMLはどれを使うかなどを記述しています。
//table[nodecg][nodecgの項目の説明]{
項目	説明
--------------------------------
compatibleRange	NodeCGのバージョン指定 ^は以上の意味（1.0.0以上となる）
dashboardPanels	dashboard（管理画面）の設定
width	管理画面で表示する際の幅
name	管理画面のパネルの名前
title	管理画面のパネルに表示されるタイトル
file	管理画面にパネルとして表示するHTMLのファイル名
graphics	graphics（配信レイアウト）の設定
width	配信レイアウトの幅
height	配信レイアウトの高さ
file	配信レイアウトとして表示するHTMLのファイル名
assetCategories	画像ファイルをアップロードに関する設定
name	ファイルを管理するための名前
title	アップロード画面に表示されるタイトル
allowedTypes	アップロード可能なファイル形式
//}

これらの設定は、widthやheightといったもの以外は基本的に固有のものにしてください。
NodeCGでは管理画面、配信レイアウトをそれぞれ複数を用意することができるため、nameやtitleの設定が重複すると想定外の挙動をしたり、バグの温床となってしまいます。
