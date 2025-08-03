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

// 薙刀式コンボキーの設定
enum combo_events {
    // 濁音（20音）
    GA_COMBO,  // が
    GI_COMBO,  // ぎ
    GU_COMBO,  // ぐ
    GE_COMBO,  // げ
    GO_COMBO,  // ご
    ZA_COMBO,  // ざ
    ZI_COMBO,  // じ
    ZU_COMBO,  // ず
    ZE_COMBO,  // ぜ
    ZO_COMBO,  // ぞ
    DA_COMBO,  // だ
    DI_COMBO,  // ぢ
    DU_COMBO,  // づ
    DE_COMBO,  // で
    DO_COMBO,  // ど
    BA_COMBO,  // ば
    BI_COMBO,  // び
    BU_COMBO,  // ぶ
    BE_COMBO,  // べ
    BO_COMBO,  // ぼ
    
    // 半濁音（5音）
    PA_COMBO,  // ぱ
    PI_COMBO,  // ぴ
    PU_COMBO,  // ぷ
    PE_COMBO,  // ぺ
    PO_COMBO,  // ぽ
    
    // 拗音（36音）
    KYA_COMBO, // きゃ
    KYU_COMBO, // きゅ
    KYO_COMBO, // きょ
    SYA_COMBO, // しゃ
    SYU_COMBO, // しゅ
    SYO_COMBO, // しょ
    CHA_COMBO, // ちゃ
    CHU_COMBO, // ちゅ
    CHO_COMBO, // ちょ
    NYA_COMBO, // にゃ
    NYU_COMBO, // にゅ
    NYO_COMBO, // にょ
    HYA_COMBO, // ひゃ
    HYU_COMBO, // ひゅ
    HYO_COMBO, // ひょ
    MYA_COMBO, // みゃ
    MYU_COMBO, // みゅ
    MYO_COMBO, // みょ
    RYA_COMBO, // りゃ
    RYU_COMBO, // りゅ
    RYO_COMBO, // りょ
    GYA_COMBO, // ぎゃ
    GYU_COMBO, // ぎゅ
    GYO_COMBO, // ぎょ
    ZYA_COMBO, // じゃ
    ZYU_COMBO, // じゅ
    ZYO_COMBO, // じょ
    DYA_COMBO, // ぢゃ
    DYU_COMBO, // ぢゅ
    DYO_COMBO, // ぢょ
    BYA_COMBO, // びゃ
    BYU_COMBO, // びゅ
    BYO_COMBO, // びょ
    PYA_COMBO, // ぴゃ
    PYU_COMBO, // ぴゅ
    PYO_COMBO, // ぴょ
    COMBO_LENGTH
};

// 濁音のコンボ定義（文字キー + あ(3キー)）
const uint16_t PROGMEM ga_combo[] = {KC_T, KC_3, COMBO_END};  // か+あ→が
const uint16_t PROGMEM gi_combo[] = {KC_G, KC_3, COMBO_END};  // き+あ→ぎ
const uint16_t PROGMEM gu_combo[] = {KC_H, KC_3, COMBO_END};  // く+あ→ぐ
const uint16_t PROGMEM ge_combo[] = {KC_QUOT, KC_3, COMBO_END};  // け+あ→げ
const uint16_t PROGMEM go_combo[] = {KC_B, KC_3, COMBO_END};  // こ+あ→ご

const uint16_t PROGMEM za_combo[] = {KC_X, KC_3, COMBO_END};  // さ+あ→ざ
const uint16_t PROGMEM zi_combo[] = {KC_D, KC_3, COMBO_END};  // し+あ→じ
const uint16_t PROGMEM zu_combo[] = {KC_R, KC_3, COMBO_END};  // す+あ→ず
const uint16_t PROGMEM ze_combo[] = {KC_P, KC_3, COMBO_END};  // せ+あ→ぜ
const uint16_t PROGMEM zo_combo[] = {KC_C, KC_3, COMBO_END};  // そ+あ→ぞ

const uint16_t PROGMEM da_combo[] = {KC_Q, KC_3, COMBO_END};  // た+あ→だ
const uint16_t PROGMEM di_combo[] = {KC_A, KC_3, COMBO_END};  // ち+あ→ぢ
const uint16_t PROGMEM du_combo[] = {KC_Z, KC_3, COMBO_END};  // つ+あ→づ
const uint16_t PROGMEM de_combo[] = {KC_W, KC_3, COMBO_END};  // て+あ→で
const uint16_t PROGMEM do_combo[] = {KC_S, KC_3, COMBO_END};  // と+あ→ど

const uint16_t PROGMEM ba_combo[] = {KC_F, KC_3, COMBO_END};  // は+あ→ば
const uint16_t PROGMEM bi_combo[] = {KC_V, KC_3, COMBO_END};  // ひ+あ→び
const uint16_t PROGMEM bu_combo[] = {KC_2, KC_3, COMBO_END};  // ふ+あ→ぶ
const uint16_t PROGMEM be_combo[] = {KC_MINUS, KC_3, COMBO_END};  // へ+あ→べ
const uint16_t PROGMEM bo_combo[] = {KC_6, KC_3, COMBO_END};  // ほ+あ→ぼ

// 半濁音のコンボ定義（文字キー + な(Uキー)）
const uint16_t PROGMEM pa_combo[] = {KC_F, KC_U, COMBO_END};  // は+な→ぱ
const uint16_t PROGMEM pi_combo[] = {KC_V, KC_U, COMBO_END};  // ひ+な→ぴ
const uint16_t PROGMEM pu_combo[] = {KC_2, KC_U, COMBO_END};  // ふ+な→ぷ
const uint16_t PROGMEM pe_combo[] = {KC_MINUS, KC_U, COMBO_END};  // へ+な→ぺ
const uint16_t PROGMEM po_combo[] = {KC_6, KC_U, COMBO_END};  // ほ+な→ぽ

// 拗音のコンボ定義（文字キー + や(7)/ゆ(8)/よ(9)）
const uint16_t PROGMEM kya_combo[] = {KC_G, KC_7, COMBO_END};  // き+や→きゃ
const uint16_t PROGMEM kyu_combo[] = {KC_G, KC_8, COMBO_END};  // き+ゆ→きゅ
const uint16_t PROGMEM kyo_combo[] = {KC_G, KC_9, COMBO_END};  // き+よ→きょ

const uint16_t PROGMEM sya_combo[] = {KC_D, KC_7, COMBO_END};  // し+や→しゃ
const uint16_t PROGMEM syu_combo[] = {KC_D, KC_8, COMBO_END};  // し+ゆ→しゅ
const uint16_t PROGMEM syo_combo[] = {KC_D, KC_9, COMBO_END};  // し+よ→しょ

const uint16_t PROGMEM cha_combo[] = {KC_A, KC_7, COMBO_END};  // ち+や→ちゃ
const uint16_t PROGMEM chu_combo[] = {KC_A, KC_8, COMBO_END};  // ち+ゆ→ちゅ
const uint16_t PROGMEM cho_combo[] = {KC_A, KC_9, COMBO_END};  // ち+よ→ちょ

const uint16_t PROGMEM nya_combo[] = {KC_I, KC_7, COMBO_END};  // に+や→にゃ
const uint16_t PROGMEM nyu_combo[] = {KC_I, KC_8, COMBO_END};  // に+ゆ→にゅ
const uint16_t PROGMEM nyo_combo[] = {KC_I, KC_9, COMBO_END};  // に+よ→にょ

const uint16_t PROGMEM hya_combo[] = {KC_V, KC_7, COMBO_END};  // ひ+や→ひゃ
const uint16_t PROGMEM hyu_combo[] = {KC_V, KC_8, COMBO_END};  // ひ+ゆ→ひゅ
const uint16_t PROGMEM hyo_combo[] = {KC_V, KC_9, COMBO_END};  // ひ+よ→ひょ

const uint16_t PROGMEM mya_combo[] = {KC_N, KC_7, COMBO_END};  // み+や→みゃ
const uint16_t PROGMEM myu_combo[] = {KC_N, KC_8, COMBO_END};  // み+ゆ→みゅ
const uint16_t PROGMEM myo_combo[] = {KC_N, KC_9, COMBO_END};  // み+よ→みょ

const uint16_t PROGMEM rya_combo[] = {KC_L, KC_7, COMBO_END};  // り+や→りゃ
const uint16_t PROGMEM ryu_combo[] = {KC_L, KC_8, COMBO_END};  // り+ゆ→りゅ
const uint16_t PROGMEM ryo_combo[] = {KC_L, KC_9, COMBO_END};  // り+よ→りょ

// 濁音の拗音（き+3+や等の代わりに、4+や等を使用）
const uint16_t PROGMEM gya_combo[] = {KC_4, KC_7, COMBO_END};  // ぎゃ
const uint16_t PROGMEM gyu_combo[] = {KC_4, KC_8, COMBO_END};  // ぎゅ
const uint16_t PROGMEM gyo_combo[] = {KC_4, KC_9, COMBO_END};  // ぎょ

const uint16_t PROGMEM zya_combo[] = {KC_E, KC_7, COMBO_END};  // じゃ
const uint16_t PROGMEM zyu_combo[] = {KC_E, KC_8, COMBO_END};  // じゅ
const uint16_t PROGMEM zyo_combo[] = {KC_E, KC_9, COMBO_END};  // じょ

const uint16_t PROGMEM dya_combo[] = {KC_5, KC_7, COMBO_END};  // ぢゃ
const uint16_t PROGMEM dyu_combo[] = {KC_5, KC_8, COMBO_END};  // ぢゅ
const uint16_t PROGMEM dyo_combo[] = {KC_5, KC_9, COMBO_END};  // ぢょ

const uint16_t PROGMEM bya_combo[] = {KC_4, KC_6, COMBO_END};  // びゃ
const uint16_t PROGMEM byu_combo[] = {KC_4, KC_EQL, COMBO_END};  // びゅ
const uint16_t PROGMEM byo_combo[] = {KC_4, KC_BSLS, COMBO_END};  // びょ

const uint16_t PROGMEM pya_combo[] = {KC_5, KC_6, COMBO_END};  // ぴゃ
const uint16_t PROGMEM pyu_combo[] = {KC_5, KC_EQL, COMBO_END};  // ぴゅ
const uint16_t PROGMEM pyo_combo[] = {KC_5, KC_BSLS, COMBO_END};  // ぴょ

combo_t key_combos[] = {
    // 濁音
    [GA_COMBO] = COMBO_ACTION(ga_combo),
    [GI_COMBO] = COMBO_ACTION(gi_combo),
    [GU_COMBO] = COMBO_ACTION(gu_combo),
    [GE_COMBO] = COMBO_ACTION(ge_combo),
    [GO_COMBO] = COMBO_ACTION(go_combo),
    [ZA_COMBO] = COMBO_ACTION(za_combo),
    [ZI_COMBO] = COMBO_ACTION(zi_combo),
    [ZU_COMBO] = COMBO_ACTION(zu_combo),
    [ZE_COMBO] = COMBO_ACTION(ze_combo),
    [ZO_COMBO] = COMBO_ACTION(zo_combo),
    [DA_COMBO] = COMBO_ACTION(da_combo),
    [DI_COMBO] = COMBO_ACTION(di_combo),
    [DU_COMBO] = COMBO_ACTION(du_combo),
    [DE_COMBO] = COMBO_ACTION(de_combo),
    [DO_COMBO] = COMBO_ACTION(do_combo),
    [BA_COMBO] = COMBO_ACTION(ba_combo),
    [BI_COMBO] = COMBO_ACTION(bi_combo),
    [BU_COMBO] = COMBO_ACTION(bu_combo),
    [BE_COMBO] = COMBO_ACTION(be_combo),
    [BO_COMBO] = COMBO_ACTION(bo_combo),
    
    // 半濁音
    [PA_COMBO] = COMBO_ACTION(pa_combo),
    [PI_COMBO] = COMBO_ACTION(pi_combo),
    [PU_COMBO] = COMBO_ACTION(pu_combo),
    [PE_COMBO] = COMBO_ACTION(pe_combo),
    [PO_COMBO] = COMBO_ACTION(po_combo),
    
    // 拗音
    [KYA_COMBO] = COMBO_ACTION(kya_combo),
    [KYU_COMBO] = COMBO_ACTION(kyu_combo),
    [KYO_COMBO] = COMBO_ACTION(kyo_combo),
    [SYA_COMBO] = COMBO_ACTION(sya_combo),
    [SYU_COMBO] = COMBO_ACTION(syu_combo),
    [SYO_COMBO] = COMBO_ACTION(syo_combo),
    [CHA_COMBO] = COMBO_ACTION(cha_combo),
    [CHU_COMBO] = COMBO_ACTION(chu_combo),
    [CHO_COMBO] = COMBO_ACTION(cho_combo),
    [NYA_COMBO] = COMBO_ACTION(nya_combo),
    [NYU_COMBO] = COMBO_ACTION(nyu_combo),
    [NYO_COMBO] = COMBO_ACTION(nyo_combo),
    [HYA_COMBO] = COMBO_ACTION(hya_combo),
    [HYU_COMBO] = COMBO_ACTION(hyu_combo),
    [HYO_COMBO] = COMBO_ACTION(hyo_combo),
    [MYA_COMBO] = COMBO_ACTION(mya_combo),
    [MYU_COMBO] = COMBO_ACTION(myu_combo),
    [MYO_COMBO] = COMBO_ACTION(myo_combo),
    [RYA_COMBO] = COMBO_ACTION(rya_combo),
    [RYU_COMBO] = COMBO_ACTION(ryu_combo),
    [RYO_COMBO] = COMBO_ACTION(ryo_combo),
    [GYA_COMBO] = COMBO_ACTION(gya_combo),
    [GYU_COMBO] = COMBO_ACTION(gyu_combo),
    [GYO_COMBO] = COMBO_ACTION(gyo_combo),
    [ZYA_COMBO] = COMBO_ACTION(zya_combo),
    [ZYU_COMBO] = COMBO_ACTION(zyu_combo),
    [ZYO_COMBO] = COMBO_ACTION(zyo_combo),
    [DYA_COMBO] = COMBO_ACTION(dya_combo),
    [DYU_COMBO] = COMBO_ACTION(dyu_combo),
    [DYO_COMBO] = COMBO_ACTION(dyo_combo),
    [BYA_COMBO] = COMBO_ACTION(bya_combo),
    [BYU_COMBO] = COMBO_ACTION(byu_combo),
    [BYO_COMBO] = COMBO_ACTION(byo_combo),
    [PYA_COMBO] = COMBO_ACTION(pya_combo),
    [PYU_COMBO] = COMBO_ACTION(pyu_combo),
    [PYO_COMBO] = COMBO_ACTION(pyo_combo),
};

// コンボキーが押されたときの処理
void process_combo_event(uint16_t combo_index, bool pressed) {
    if (pressed) {
        switch(combo_index) {
            // 濁音
            case GA_COMBO:
                tap_code16(S(KC_R)); tap_code16(S(KC_T));
                break;
            case GI_COMBO:
                tap_code16(S(KC_R)); tap_code16(S(KC_Y));
                break;
            case GU_COMBO:
                tap_code16(S(KC_R)); tap_code16(S(KC_U));
                break;
            case GE_COMBO:
                tap_code16(S(KC_R)); tap_code16(S(KC_I));
                break;
            case GO_COMBO:
                tap_code16(S(KC_R)); tap_code16(S(KC_O));
                break;
            case ZA_COMBO:
                tap_code16(S(KC_F)); tap_code16(S(KC_T));
                break;
            case ZI_COMBO:
                tap_code16(S(KC_F)); tap_code16(S(KC_Y));
                break;
            case ZU_COMBO:
                tap_code16(S(KC_F)); tap_code16(S(KC_U));
                break;
            case ZE_COMBO:
                tap_code16(S(KC_F)); tap_code16(S(KC_I));
                break;
            case ZO_COMBO:
                tap_code16(S(KC_F)); tap_code16(S(KC_O));
                break;
            case DA_COMBO:
                tap_code16(S(KC_G)); tap_code16(S(KC_T));
                break;
            case DI_COMBO:
                tap_code16(S(KC_G)); tap_code16(S(KC_Y));
                break;
            case DU_COMBO:
                tap_code16(S(KC_G)); tap_code16(S(KC_U));
                break;
            case DE_COMBO:
                tap_code16(S(KC_G)); tap_code16(S(KC_I));
                break;
            case DO_COMBO:
                tap_code16(S(KC_G)); tap_code16(S(KC_O));
                break;
            case BA_COMBO:
                tap_code16(S(KC_V)); tap_code16(S(KC_T));
                break;
            case BI_COMBO:
                tap_code16(S(KC_V)); tap_code16(S(KC_Y));
                break;
            case BU_COMBO:
                tap_code16(S(KC_V)); tap_code16(S(KC_U));
                break;
            case BE_COMBO:
                tap_code16(S(KC_V)); tap_code16(S(KC_I));
                break;
            case BO_COMBO:
                tap_code16(S(KC_V)); tap_code16(S(KC_O));
                break;
            
            // 半濁音
            case PA_COMBO:
                tap_code16(S(KC_B)); tap_code16(S(KC_T));
                break;
            case PI_COMBO:
                tap_code16(S(KC_B)); tap_code16(S(KC_Y));
                break;
            case PU_COMBO:
                tap_code16(S(KC_B)); tap_code16(S(KC_U));
                break;
            case PE_COMBO:
                tap_code16(S(KC_B)); tap_code16(S(KC_I));
                break;
            case PO_COMBO:
                tap_code16(S(KC_B)); tap_code16(S(KC_O));
                break;
            
            // 拗音
            case KYA_COMBO:
                tap_code(KC_K); tap_code16(S(KC_Q));
                break;
            case KYU_COMBO:
                tap_code(KC_K); tap_code16(S(KC_W));
                break;
            case KYO_COMBO:
                tap_code(KC_K); tap_code16(S(KC_E));
                break;
            case SYA_COMBO:
                tap_code(KC_S); tap_code16(S(KC_Q));
                break;
            case SYU_COMBO:
                tap_code(KC_S); tap_code16(S(KC_W));
                break;
            case SYO_COMBO:
                tap_code(KC_S); tap_code16(S(KC_E));
                break;
            case CHA_COMBO:
                tap_code(KC_T); tap_code16(S(KC_Q));
                break;
            case CHU_COMBO:
                tap_code(KC_T); tap_code16(S(KC_W));
                break;
            case CHO_COMBO:
                tap_code(KC_T); tap_code16(S(KC_E));
                break;
            case NYA_COMBO:
                tap_code(KC_N); tap_code16(S(KC_Q));
                break;
            case NYU_COMBO:
                tap_code(KC_N); tap_code16(S(KC_W));
                break;
            case NYO_COMBO:
                tap_code(KC_N); tap_code16(S(KC_E));
                break;
            case HYA_COMBO:
                tap_code(KC_H); tap_code16(S(KC_Q));
                break;
            case HYU_COMBO:
                tap_code(KC_H); tap_code16(S(KC_W));
                break;
            case HYO_COMBO:
                tap_code(KC_H); tap_code16(S(KC_E));
                break;
            case MYA_COMBO:
                tap_code(KC_M); tap_code16(S(KC_Q));
                break;
            case MYU_COMBO:
                tap_code(KC_M); tap_code16(S(KC_W));
                break;
            case MYO_COMBO:
                tap_code(KC_M); tap_code16(S(KC_E));
                break;
            case RYA_COMBO:
                tap_code(KC_R); tap_code16(S(KC_Q));
                break;
            case RYU_COMBO:
                tap_code(KC_R); tap_code16(S(KC_W));
                break;
            case RYO_COMBO:
                tap_code(KC_R); tap_code16(S(KC_E));
                break;
            case GYA_COMBO:
                tap_code16(S(KC_R)); tap_code16(S(KC_Y)); tap_code16(S(KC_Q));
                break;
            case GYU_COMBO:
                tap_code16(S(KC_R)); tap_code16(S(KC_Y)); tap_code16(S(KC_W));
                break;
            case GYO_COMBO:
                tap_code16(S(KC_R)); tap_code16(S(KC_Y)); tap_code16(S(KC_E));
                break;
            case ZYA_COMBO:
                tap_code16(S(KC_F)); tap_code16(S(KC_Y)); tap_code16(S(KC_Q));
                break;
            case ZYU_COMBO:
                tap_code16(S(KC_F)); tap_code16(S(KC_Y)); tap_code16(S(KC_W));
                break;
            case ZYO_COMBO:
                tap_code16(S(KC_F)); tap_code16(S(KC_Y)); tap_code16(S(KC_E));
                break;
            case DYA_COMBO:
                tap_code16(S(KC_G)); tap_code16(S(KC_Y)); tap_code16(S(KC_Q));
                break;
            case DYU_COMBO:
                tap_code16(S(KC_G)); tap_code16(S(KC_Y)); tap_code16(S(KC_W));
                break;
            case DYO_COMBO:
                tap_code16(S(KC_G)); tap_code16(S(KC_Y)); tap_code16(S(KC_E));
                break;
            case BYA_COMBO:
                tap_code16(S(KC_V)); tap_code16(S(KC_Y)); tap_code16(S(KC_Q));
                break;
            case BYU_COMBO:
                tap_code16(S(KC_V)); tap_code16(S(KC_Y)); tap_code16(S(KC_W));
                break;
            case BYO_COMBO:
                tap_code16(S(KC_V)); tap_code16(S(KC_Y)); tap_code16(S(KC_E));
                break;
            case PYA_COMBO:
                tap_code16(S(KC_B)); tap_code16(S(KC_Y)); tap_code16(S(KC_Q));
                break;
            case PYU_COMBO:
                tap_code16(S(KC_B)); tap_code16(S(KC_Y)); tap_code16(S(KC_W));
                break;
            case PYO_COMBO:
                tap_code16(S(KC_B)); tap_code16(S(KC_Y)); tap_code16(S(KC_E));
                break;
        }
    }
}

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

  [4] = LAYOUT_universal(
    // ひらがな入力用レイヤー（左手側）
    // た行     ら行     だ行     が行     ざ行                                      な行     は行     ば行     ま行     わ行
    KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    // あ行     か行     さ行                                                          や行                      ぱ行
    KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  ,
    // っ      ー                                                                      ん      、       。       ？
    KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  [5] = LAYOUT_universal(
    // ひらがな入力用レイヤー（濁音・半濁音・拗音）
    // ゃ      ゅ       ょ       ゎ       っ                                          小文字記号
    S(KC_Q)  , S(KC_W)  , S(KC_E)  , S(KC_R)  , S(KC_T)  ,                            S(KC_Y)  , S(KC_U)  , S(KC_I)  , S(KC_O)  , S(KC_P)  ,
    // ぁ      ぃ       ぅ       ぇ       ぉ                                          
    S(KC_A)  , S(KC_S)  , S(KC_D)  , S(KC_F)  , S(KC_G)  ,                            _______  , _______  , _______  , _______  , _______  ,
    // 「      」       ・       ！       〜
    KC_LBRC  , KC_RBRC  , KC_BSLS  , S(KC_1)  , S(KC_MINS),                           _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    
    #ifdef RGBLIGHT_ENABLE
    // レイヤーに応じてRGBカラーを変更
    switch (get_highest_layer(state)) {
        case 0:
        case 1:
        case 2:
        case 3:
            // レイヤー0-3: デフォルト設定に戻す
            rgblight_sethsv_noeeprom(0, 0, 0);  // 一旦オフにして
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT);  // デフォルトモードに戻す
            break;
        case 4:
        case 5:
            // レイヤー4-5: 赤色に設定
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            rgblight_sethsv_noeeprom(0, 255, 255);  // 赤色 (Hue=0)
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
