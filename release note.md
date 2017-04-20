# このノートはNefry(ESP32版)のリリースノートになります。

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

