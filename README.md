# gc_snapback_reductionとは
GCコンをArduino経由で読み取り、跳ね戻りを軽減するプロジェクトです。
## 必要な物
Arduino
GCコン延長ケーブル
ジャンパワイヤ
ロジックレベルコンバーター
### 使いかた
1. Arduino IDEをインストールする
2. ライブラリマネージャーよりnicohood/Nintendoライブラリをインストールする
3. NintendoSwitchControlllibraryをインストールする
4. snapbackfix.inoを開きコンパイル・書き込みする
5. GCコン延長ケーブルを半分に切り、メス側の被覆をはがして内部線をArduinoに配線する(3.3V,5V,GND,DATA線)
6. GCコンをArduinoに繋いでからswitchにUSBを挿す
#### 課題
十分動かせるレベルではあるがスマブラのようなシビアなゲームではダッシュが出なかったり調整が必要
配線も難しくいまいち実用性に欠ける
