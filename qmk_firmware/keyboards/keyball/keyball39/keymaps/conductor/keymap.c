/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"

// AML（Auto Mouse Layer）クリック後タイムアウト管理用
static bool clicked_in_aml = false;
static uint16_t aml_default_timeout = 1000;      // デフォルト1秒
static uint16_t aml_after_click_timeout = 500;   // クリック後500ms

// コンボキーの設定
enum combo_events {
    BTN_SCRL,   // 左クリック+右クリック同時押しでスクロール
    COMBO_LENGTH
};

const uint16_t PROGMEM btn_combo[] = {KC_BTN1, KC_BTN2, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [BTN_SCRL] = COMBO(btn_combo, SCRL_MO),  // BTN1+BTN2同時押しでスクロールモード
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
    KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , KC_K     , KC_L     , KC_MINS  ,
    KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  ,
    KC_LCTL  , KC_LGUI  , KC_LALT  ,LSFT_T(KC_LNG2),LT(1,KC_SPC),LT(3,KC_LNG1),KC_BSPC,LT(2,KC_ENT),LSFT_T(KC_LNG2),KC_RALT,KC_RGUI, KC_RSFT
  ),

  [1] = LAYOUT_universal(
    KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_RBRC  ,                            KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   ,
    KC_F5    , KC_EXLM  , S(KC_6)  ,S(KC_INT3), S(KC_8)  ,                           S(KC_INT1), KC_BTN1  , KC_PGUP  , KC_BTN2  , KC_SCLN  ,
    S(KC_EQL),S(KC_LBRC),S(KC_7)   , S(KC_2)  ,S(KC_RBRC),                            KC_LBRC  , KC_DLR   , KC_PGDN  , KC_BTN3  , KC_F11   ,
    KC_INT1  , KC_EQL   , S(KC_3)  , _______  , _______  , _______  ,      TO(2)    , TO(0)    , _______  , KC_RALT  , KC_RGUI  , KC_F12
  ),

  [2] = LAYOUT_universal(
    KC_TAB   , KC_7     , KC_8     , KC_9     , KC_MINS  ,                            KC_NUHS  , _______  , KC_BTN3  , _______  , KC_BSPC  ,
   S(KC_QUOT), KC_4     , KC_5     , KC_6     ,S(KC_SCLN),                            S(KC_9)  , KC_BTN1  , KC_UP    , KC_BTN2  , KC_QUOT  ,
    KC_SLSH  , KC_1     , KC_2     , KC_3     ,S(KC_MINS),                           S(KC_NUHS), KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  ,
    KC_ESC   , KC_0     , KC_DOT   , KC_DEL   , KC_ENT   , KC_BSPC  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  ,                            _______  , _______  , SSNP_HOR , SSNP_VRT , SSNP_FRE ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , SCRL_DVI ,                            _______  , _______  , _______  , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , SCRL_DVD ,                            CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE ,
    QK_BOOT  , KBC_RST  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , KBC_RST  , QK_BOOT
  ),

  // Layer 4: AML（Auto Mouse Layer）
  // トラックボール移動で自動的にこのレイヤーに切り替わる
  // K = 左クリック, L = 右クリック, 他は透過（Layer0のキー）
  [4] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , KC_BTN1  , KC_BTN2  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  // Layer 5: 予備
  [5] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),
};
// clang-format on

// AMLレイヤー（Layer4）有効時のキー処理
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // AMLレイヤー（Layer4）有効時の処理
    if (layer_state_is(4) && record->event.pressed) {
        switch (keycode) {
            case KC_BTN1:
            case KC_BTN2:
            case KC_BTN3:
                // マウスクリック → タイムアウトを短縮（ダブルクリック対応）
                clicked_in_aml = true;
                set_auto_mouse_timeout(aml_after_click_timeout);
                break;
            case SCRL_MO:
                // スクロールはAML維持
                break;
            default:
                // 他のキーでAML即時解除
                layer_off(4);
                clicked_in_aml = false;
                set_auto_mouse_timeout(aml_default_timeout);
                break;
        }
    }
    return true;
}

// トラックボール移動でタイムアウトリセット
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // トラックボールが動いた場合
    if (mouse_report.x != 0 || mouse_report.y != 0) {
        if (clicked_in_aml) {
            // クリック後にトラックボールを動かしたらタイムアウトをリセット
            clicked_in_aml = false;
            set_auto_mouse_timeout(aml_default_timeout);
        }
    }
    return mouse_report;
}

// マウスレコード判定（AMLタイマー制御用）
bool is_mouse_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case KC_BTN1:
        case KC_BTN2:
        case KC_BTN3:
        case SCRL_MO:
            return true;   // マウスキーはAMLタイマー延長
        default:
            return false;  // 他のキーはAMLタイマー停止
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);

    // AMLレイヤー（Layer4）を離れた時にフラグリセット
    if (!layer_state_cmp(state, 4)) {
        clicked_in_aml = false;
        set_auto_mouse_timeout(aml_default_timeout);
    }

    #ifdef RGBLIGHT_ENABLE
    // レイヤーに応じてRGBカラーを変更
    switch (get_highest_layer(state)) {
        case 0:
        case 1:
        case 2:
        case 3:
            // レイヤー0-3: 青色に設定
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            rgblight_sethsv_noeeprom(170, 255, 255);  // 青色 (Hue=170)
            break;
        case 4:
            // レイヤー4（AML）: 赤色に設定
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            rgblight_sethsv_noeeprom(0, 255, 255);    // 赤色 (Hue=0)
            break;
        case 5:
            // レイヤー5: 緑色に設定
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            rgblight_sethsv_noeeprom(85, 255, 255);   // 緑色 (Hue=85)
            break;
        default:
            break;
    }
    #endif

    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif

// AML（Auto Mouse Layer）を起動時に有効化
void pointing_device_init_user(void) {
    set_auto_mouse_layer(4);        // Layer 4をAMLレイヤーに設定
    set_auto_mouse_enable(true);    // AMLを有効化
}
