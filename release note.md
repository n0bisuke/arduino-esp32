# このノートはNefry(ESP32版)のリリースノートになります。

## 0.7.2

0.7.1で修正した内容を破棄

バグフィックス

- コンパイラ環境の復元

## 0.7.1

コンパイル環境のesptoolがうまく動作しなかったため修正

バグフィックス

- コンパイラ環境の修正

## 0.7.0

NefryのModule設定機能の追加

新規機能

- モジュール情報設定機能
- esp32/arduino[3b86e0c]コミットまでマージ
- サンプルプログラムを追加


## 0.6.2

NefryのWeb関連機能の修正とDNSの追加、それに伴う起動シークエンスの変更

新規機能

- DNS対応
- CaptivePortal対応
- webserver更新

バグフィックス

- 起動シークエンスの変更

## 0.6.1

IFTTTライブラリー追加とバグフィックス対応

新規機能

- IFTTTライブラリー追加

バグフィックス

- ボード名変更　Nefry BT
- 関数名変更　storageとstoreがあったためStoreに統一
- SWの処理を変更

## 0.6.0
Data Store機能の追加

新規機能

- Data Store機能の追加
- setStoreTitle関数の追加

バグフィックス

- メイン処理の変更
- 初回起動時の処理の修正
- スイッチ関連関数の修正
- Data Store機能のデータのキャッシュ機能の追加
- WiFi機能の修正


## 0.5.4
WiFi関連のバグフィックス

機能
- WiFi関連機能のバグフィックス
- 関数追加
	- saveWiFi
	- addWiFi
	- deleteWiFi

## 0.5.3
書き込み時にパスが通らなくなってしまったためその修正

機能
- コンパイルオプションの変更

## 0.5.2
コンパイルが通らなくなってしまったためその修正

機能
- コンパイルオプションの変更

## 0.5.1
Nefry Icingボードを追加。

機能
- ボードの追加


## 0.5.0
NefryのベースとなるWebserver機能、WiFi設定機能を搭載した初回リリース。

機能
- ESP32 Arduino公式までをマージ(https://github.com/espressif/arduino-esp32/commit/2b075f320477278be0eec55a34de9eca19426019)
- 公式が出すまでの仮バージョンのWebServerを追加
- WiFiの設定機能を追加
- 最低限のデータ管理システムとRGBLED制御などNefryとしての機能を追加
- RTOSの機能によりwebserverとボタン確認機能を追加

## 0.5.1
Nefry Icingボードを追加。

機能
- ボードの追加

