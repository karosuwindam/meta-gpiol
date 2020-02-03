# C言語でのGPIO制御プログラム

## はじめに
作成については、YoctoのPoky機能のテンプレート作成機能をベースに作成しています。
## 使用方法
以下の内容を上から実行してください。
* conf/bblayer.confにレシピパスの追加を行います。
* bitbake gpiolコマンドでビルドができることを確認します。
* conf/local.confにIMAGE_INSTALL_append = " gpiol"を追加します。
## プログラム内容
実行すると10秒間1秒間隔で、点滅が繰り返されます。
