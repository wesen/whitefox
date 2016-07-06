#include "keymap_common.h"

const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qwerty */
//    /*    K00,   K02,  K03, K04, K05, K06, K07, K08, K09, K0A,  K0B,  K0C,  K0D,  K0E,  K0F,  K0G,  K0H, */
//    KEYMAP(ESC,  F1,   F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,   F10,  F11,  F12,  PSCR, SLCK, PAUS, PWR,
//    /*    K10, K11, K12,  K13, K14, K15, K16, K17, K18, K19, K1A,      K1B, K1C,  K1D,  K1E,  K1F,  K1G,  K1H, K1I,  K1J,   K1K, */
//           GRV,  1,    2,   3,   4,   5,   6,   7,   8,   9,    0,    MINS, EQL,  BSLS, BSPC, INS,  HOME, PGUP, NLCK, PSLS, PAST, PMNS,
//     /*    K20, K21, K22, K23, K24, K25, K26, K27, K28,  K29, K2A,     K2B,  K2C, K2D, K2E,   K2F,   K2G,   K2H, K2I, K2J, */
//           TAB,  Q,    W,   E,   R,   T,   Y,   U,   I,   O,    P,    LBRC, RBRC, ENT, DEL,   END,  PGDN,   P7,   P8,   P9,
//     /*     K30, K31, K32, K33, K34, K35, K36, K37, K38, K39,     K3A,  K3B, K3C,  K3H, K3I,    K3J, K3K, */
//           CAPS, A,    S,   D,   F,   G,   H,   J,   K,   L,    SCLN, QUOT, P4,   P5,  P6,    PPLS,
//      /*    K40,  K41, K42, K43, K44, K45, K46, K47, K48, K49,  K4A,  K4B,  K4C,  K4F, K4H,  K4I,  K4J, */
//           LSFT, BSLS, Z,   X,   C,   V,   B,   N,   M,   COMM, DOT,  SLSH, RSFT, UP,  P1,    P2,   P3,
//      /*    K50,  K51, K52,           K56,                       K5A,  K5B, K5C, K5D,   K5E,   K5F, K5G,  K5I, K5J, K5K */
//           LCTL, LGUI,LALT,           SPC,                      RALT, RGUI, APP, RCTL, LEFT,  DOWN, RGHT, P0, PCMM, PENT ),

    KEYMAP(ESC,  F1,   F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,   F10,  F11,  F12,  PSCR, SLCK, PAUS, PWR,
           GRV,  1,    2,   3,   4,   5,   6,   7,   8,   9,    0,    MINS, EQL,  BSPC, INS,  HOME, PGUP, NLCK, PSLS, PAST, PMNS,
           TAB,  Q,    W,   E,   R,   T,   Y,   U,   I,   O,    P,    LBRC, RBRC, ENT, DEL,   END,  PGDN,   P7,   P8,   P9,
           CAPS, A,    S,   D,   F,   G,   H,   J,   K,   L,    BSLS, SCLN, QUOT, P4,   P5,  P6,    PPLS,
           LSFT, BSLS, Z,   X,   C,   V,   B,   N,   M,   COMM, DOT,  SLSH, RSFT, UP,  P1,    P2,   P3,
           LCTL, LGUI,LALT,           SPC,                      RALT, RGUI, APP, RCTL, LEFT,  DOWN, RGHT, P0, PCMM, PENT ),
};
const uint16_t fn_actions[] = {};
