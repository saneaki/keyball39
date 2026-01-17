# conductor キーマップ仕様書

## 概要

conductorは、Keyball39向けのAML（Auto Mouse Layer）機能を搭載したキーマップです。
via2キーマップをベースに、トラックボール操作時の自動レイヤー切り替え機能を追加しています。

## AML（Auto Mouse Layer）仕様

### 基本動作

| 項目 | 仕様 |
|------|------|
| AMLレイヤー | Layer 4 |
| タイムアウト | 1秒（1000ms） |
| クリック後タイムアウト | 500ms |

### 動作フロー

```
1. トラックボールを動かす
   → Layer4（AML）有効化、タイムアウト1秒開始

2-a. K押下 → 左クリック送信
     → タイムアウトを500msに短縮
     → トラックボール移動で1秒にリセット

2-b. L押下 → 右クリック送信
     → タイムアウトを500msに短縮
     → トラックボール移動で1秒にリセット

2-c. KL同時押し → スクロールモード

2-d. 他キー押下 → Layer0のキー送信 + AML即時解除

3. タイムアウト経過 → Layer0に戻る
```

### AMLレイヤー（Layer 4）キー配置

| 位置 | キー | 機能 |
|------|------|------|
| K | KC_BTN1 | 左クリック |
| L | KC_BTN2 | 右クリック |
| その他 | _______ | 透過（Layer0のキー） |

### コンボキー

| コンボ | 出力 | 説明 |
|--------|------|------|
| BTN1 + BTN2 | SCRL_MO | 左クリック+右クリック同時押しでスクロールモード |

## レイヤー構成

| Layer | 用途 |
|-------|------|
| 0 | メイン（QWERTY） |
| 1 | ファンクションキー・記号 |
| 2 | テンキー・矢印 |
| 3 | 設定（RGB、CPI、スクロール） |
| 4 | AML（Auto Mouse Layer） |
| 5 | 予備 |

## 設定値（config.h）

```c
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_DEFAULT_LAYER 4
#define AUTO_MOUSE_TIME 1000
#define COMBO_COUNT 1
#define COMBO_TERM 50
#define DYNAMIC_KEYMAP_LAYER_COUNT 6
```

## ビルド方法

### GitHub Actions（推奨）

1. GitHubリポジトリの **Actions** タブを開く
2. **Build a firmware on demand** を選択
3. **Run workflow** をクリック
4. Keyboard: `keyball39`、Keymap: `conductor` を入力
5. **Run workflow** を実行

### ローカルビルド

```bash
cd qmk_firmware
qmk compile -kb keyball/keyball39 -km conductor
```

## 技術詳細

### 使用するQMK機能

- `POINTING_DEVICE_AUTO_MOUSE_ENABLE`: 自動マウスレイヤー機能
- `COMBO_ENABLE`: コンボキー機能
- `process_record_user()`: キー入力処理のカスタマイズ
- `pointing_device_task_user()`: ポインティングデバイス処理
- `is_mouse_record_user()`: マウスキー判定
- `layer_state_set_user()`: レイヤー状態変更時の処理

### グローバル変数

```c
static bool clicked_in_aml = false;           // AML中にクリックしたか
static uint16_t aml_default_timeout = 1000;   // デフォルトタイムアウト
static uint16_t aml_after_click_timeout = 500; // クリック後タイムアウト
```

### RGB LED設定

| レイヤー | 色 |
|----------|------|
| 0-3（通常） | 青色 |
| 4（AML） | 赤色 |
| 5（予備） | 緑色 |

## 注意事項

- クリック後タイムアウト値（500ms）は調整可能。短すぎるとダブルクリックが難しくなる
- `is_mouse_record_user()`でマウスキー以外を`false`にすることで、通常キー入力時にAMLタイマーが停止する
- AML有効時はRGB LEDが赤色に変化し、マウス操作モードであることを視覚的に確認できる

## 更新履歴

| 日付 | 変更内容 |
|------|----------|
| 2025-01 | 初版作成、AML機能実装 |
| 2026-01 | RGB設定変更（通常時青、AML時赤）、コンボキーをBTN1+BTN2スクロールのみに変更 |
