// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2020

#include <stdint.h>
#include <stdbool.h>

#include "common.h"
#include "entries.h"
#include "gbtoolchainid.h"


// ==== Various
// Records can be at any location

    DEF_PATTERN_STR(sig_str_ghx_audio, "GHX Audio Engine");
    DEF_PATTERN_STR(sig_str_ghx_sound, "GHX Sound Engine");

    DEF_PATTERN_STR(sig_str_devsound_standard, "DevSound GB music player");
    DEF_PATTERN_STR(sig_str_devsound_lite, "DevSound Lite");
    DEF_PATTERN_STR(sig_str_devsound_x, "DevSound X sound driver");

    DEF_PATTERN_STR(sig_str_gbmusicplayer_audio, "GB Music Player Copyright VISUAL IMPACT BVBA");

    DEF_PATTERN_STR(sig_str_MusyX_1, "MusyX Audio Tools");
    DEF_PATTERN_STR(sig_str_MusyX_2, "MUSYX AUDIO TOOLS");
    DEF_PATTERN_STR(sig_str_MusyX_3, "MusyX Soundtool");

    DEF_PATTERN_STR(sig_str_freaq_1, "Stilianos Doussis");
    DEF_PATTERN_STR(sig_str_freaq_2, "Gameboy Audio-System coded and Music composed by Stilianos Doussis");

    DEF_PATTERN_STR(sig_str_lsdj_1, "LITTLESOUNDDJ.COM");
    DEF_PATTERN_STR(sig_str_lsdj_2, "LITTLE SOUND DJ");

    // GBSoundSystem only (not 100% sure) : soundsys.asm : SSFP_multi_sfx
    DEF_PATTERN_BUF(sig_gbsoundsystem_modern_SSFP_multi_sfx, AR_ARGS(0x57, 0x78, 0x06, 0x00, 0x87, 0xCB, 0x10, 0x87, 0xCB, 0x10, 0x87, 0xCB, 0x10, 0x83, 0x6F, 0x3E, 0x00, 0x8A, 0x80, 0x67));
    // Paragon5 only : sndsys_c.asm : MultiSFXLoop
    DEF_PATTERN_BUF(sig_gbsoundsystem_MultiSFXLoop, AR_ARGS(0x2A, 0x4E, 0x06, 0x00, 0x87, 0xCB, 0x10, 0x87, 0xCB, 0x10, 0x87, 0xCB, 0x10));
    DEF_PATTERN_STR(sig_str_gbsoundsystem_1, "SoundSystem");
    DEF_PATTERN_STR(sig_str_gbsoundsystem_2, "Hockenhull");

    // hUGEDriver
        // // _load_note_data -> lookup_note : https://github.com/untoxa/hUGEBuild/blame/master/hUGEDriver.asm#L332
        // DEF_PATTERN_BUF(sig_hugetracker_load_note_data, AR_ARGS(0x67, 0x84, 0x84, 0xC6, 0x02, 0x26, 0x00, 0x6F, 0x09, 0x3A, 0x4F, 0x3A, 0x47, 0x7E, 0xC9 ));
        // https://github.com/SuperDisk/hUGEDriver/blob/e996cfab0b16bea6e394f269e89a5729d8421bb2/hUGEDriver.asm#L295 -> 308
        // DEF_PATTERN_BUF(sig_hugetracker_load_note_data_v2, AR_ARGS(0x67, 0x84, 0x84, 0x26, 0x00, 0x6F, 0x09, 0x2A, 0x46, 0x23, 0x4E, 0xC9))
    // https://github.com/SuperDisk/hUGEDriver/blame/3e67d4ea8a27f5317fd5be73a534c543614130ef/hUGEDriver.asm#L760 -> 772
    DEF_PATTERN_BUF(sig_hugetracker_fx_vol_slide_base_v1, AR_ARGS(0x79, 0xE6, 0x0F, 0x57, 0x79, 0xE6, 0xF0, 0x5F, 0xCB, 0x33 ,0x7E, 0xE6, 0xF0, 0xCB, 0x37, 0x92));
    // https://github.com/SuperDisk/hUGEDriver/blob/e996cfab0b16bea6e394f269e89a5729d8421bb2/hUGEDriver.asm#L736 -> 743
    DEF_PATTERN_BUF(sig_hugetracker_fx_vol_slide_base_v2, AR_ARGS(0x79, 0xE6, 0x0F, 0x57, 0x79, 0xE6, 0xF0, 0x5F, 0xCB, 0x33 ,0x78, 0x87, 0x87, 0x80, 0xC6, 0x12, 0x4F, 0xF2, 0xE6, 0xF0, 0xCB, 0x37, 0x92));
    // ADDED: Initial Release (2022-10)
    // asm: https://github.com/ISSOtm/fortISSimO/blob/master/fortISSimO.asm#L937
    DEF_PATTERN_BUF(sig_hugetracker_fortissimo_fx_vol_slide, AR_ARGS(0xA1, 0xC8, 0xEE, 0x02, 0x3C, 0xEE, 0x04, 0xC6, 0x12, 0x4F, 0x78, 0x06, 0xF0, 0xA0, 0x67, 0x78, 0xCB, 0x37, 0xA0, 0x6F, 0xF2, 0xA0, 0x95));
    // get_note_poly is highly conserved, appears distinct, can use it as a fallback
    // v1: https://github.com/SuperDisk/hUGEDriver/blame/3e67d4ea8a27f5317fd5be73a534c543614130ef/hUGEDriver.asm#L388
    // v2: https://github.com/SuperDisk/hUGEDriver/blob/e996cfab0b16bea6e394f269e89a5729d8421bb2/hUGEDriver.asm#L361 - 392
    // Valen: https://github.com/datguywitha3ds/Valens-Game-Boy-Graveyard/blob/main/hUGEDriver-5.5/hUGEDriver.asm#L427
    DEF_PATTERN_BUF(sig_hugetracker_fx_get_note_poly, AR_ARGS(0xC6, 0xC0, 0x2F, 0xFE, 0x07, 0xD8, 0x67, 0xD6, 0x04, 0xCB, 0x3F, 0xCB, 0x3F, 0x6F, 0x7C, 0xE6, 0x03, 0xC6, 0x04, 0xCB, 0x35, 0xB5, 0xC9));
    // https://github.com/datguywitha3ds/Valens-Game-Boy-Graveyard/blob/main/hUGEDriver-5.5/hUGEDriver.asm#L1409 - 1416
    // Shorter pattern, so combine with get_note_poly
    DEF_PATTERN_BUF(sig_hugetracker_fx_coffeebat_get_shift_ch3, AR_ARGS(0xCB, 0x37, 0xCB, 0x3F, 0x4F, 0xAF, 0x91, 0xE6, 0x03, 0x4F));

    // engine.asm, tbe_thumbprint::
    DEF_PATTERN_STR(sig_tbengine_noisetable, "tbengine - sound driver by stoneface");


    // Black Box Music Player
    // May not be entirely accurate. Also, many trainers added to ROMs used it
    // From a 3 way diff between Infinite Bobs, Player.bin and Pocket Voice
    DEF_PATTERN_BUF(sig_blackboxplayer_1, AR_ARGS(0x09, 0x11, 0x30, 0xFF, 0x06, 0x10, 0x2A, 0x12, 0x13, 0x05, 0x20, 0xFA, 0x3E, 0x80, 0xE0, 0x1A, 0xC9, 0xAF, 0xE0, 0x1A, 0xC9));
    DEF_PATTERN_BUF(sig_blackboxplayer_2, AR_ARGS(0xCB, 0x27, 0x4F, 0x06, 0x00, 0x09, 0x2A, 0xFE, 0x00, 0x28, 0x08, 0x47, 0x7E, 0x3D, 0x05, 0xCD));


    // From "Sliced" 32KB SRAM File (*.sav) into two files (or ROM banks for assembler)
    // Slices a 32KB SRAM File (*.sav) into two files (or ROM banks for assembler):
        // 1) 16KB music player code and music data (*.bin)
        // "CARILLON PLAYER Version 1.0 (c)2000 Aleksi Eeben (email:aleksi@cncd.fi)";
        DEF_PATTERN_STR(sig_carillon_player_1, "CARILLON PLAYER");
        // "CARILLON EDITOR Version 1.2 Free for all non-commercial use (c)2000-2001 Aleksi Eeben";
        DEF_PATTERN_STR(sig_carillon_player_2, "CARILLON EDITOR");

    // PLAYER.asm / LP1.297.c, l_wave / wave[]
    // It's possible this doesn't pick up uses where the default wave instrument has changed
    DEF_PATTERN_BUF(sig_lemon_wave_default, AR_ARGS(
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0xCB, 0xA8, 0x75, 0x43, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00,
            0xFF, 0xFF, 0xFF, 0xFF, 0xB7, 0x42, 0x23, 0x46, 0x9B, 0xCD, 0xDB, 0x84, 0x00, 0x00, 0x00, 0x00,
            0xFF, 0x89, 0xCB, 0x88, 0xBA, 0x78, 0x99, 0x77, 0x88, 0x66, 0x78, 0x54, 0x77, 0x43, 0x67, 0x00));
            // Continues below, but above is probably sufficient
            // 0xF8, 0xB8, 0xA9, 0x99, 0x89, 0x89, 0x88, 0x78, 0x78, 0x78, 0x77, 0x67, 0x66, 0x65, 0x74, 0x70,
            // 0x9B, 0xDE, 0xEF, 0xFF, 0xFF, 0xFE, 0xED, 0xB9, 0x64, 0x22, 0x10, 0x00, 0x00, 0x01, 0x22, 0x46,
            // 0xAD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDA, 0x52, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25,
            // 0xFF, 0xFE, 0xDD, 0xCC, 0xBB, 0xAA, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x10, 0x00,
            // 0xBE, 0xEC, 0xBA, 0x98, 0x76, 0x54, 0x31, 0x14, 0xBE, 0xEC, 0xBA, 0x98, 0x76, 0x54, 0x31, 0x14};

    // ==== gbt_player
    // gbt_wave: ; 8 sounds
    DEF_PATTERN_BUF(sig_gbtplayer_gbt_wave, AR_ARGS(
        0xA5, 0xD7, 0xC9, 0xE1, 0xBC, 0x9A, 0x76, 0x31, 0x0C, 0xBA, 0xDE, 0x60, 0x1B, 0xCA, 0x03, 0x93,
        0xF0, 0xE1, 0xD2, 0xC3, 0xB4, 0xA5, 0x96, 0x87, 0x78, 0x69, 0x5A, 0x4B, 0x3C, 0x2D, 0x1E, 0x0F,
        0xFD, 0xEC, 0xDB, 0xCA, 0xB9, 0xA8, 0x97, 0x86, 0x79, 0x68, 0x57, 0x46, 0x35, 0x24, 0x13, 0x02));

    // ==== MPlay (doesn't find all instances)
        // A possible LUT with "MPlay2" appended to the end
        // { 0x01, 0x6B, 0x01, 0xC9, 0x01, 0x23, 0x02, 0x77, 0x02, 0xC6, 0x02, 0x12, 0x03, 0x56, 0x03, 0x9B,
        // 0x03, 0xDA, 0x03, 0x16, 0x04, 0x4E, 0x04, 0x83, 0x04, 0xB5, 0x04, 0xE5, 0x04, 0x11, 0x05, 0x3B,
        // 0x05, 0x63, 0x05, 0x89, 0x05, 0xAC, 0x05, 0xCE, 0x05, 0xED, 0x05, 0x0A, 0x06, 0x27, 0x06, 0x42,
        // 0x06, 0x5B, 0x06, 0x72, 0x06, 0x89, 0x06, 0x9E, 0x06, 0xB2, 0x06, 0xC4, 0x06, 0xD6, 0x06, 0xE7,
        // 0x06, 0xF7, 0x06, 0x06, 0x07, 0x14, 0x07, 0x21, 0x07, 0x2D, 0x07, 0x39, 0x07, 0x44, 0x07, 0x4F,
        // 0x07, 0x59, 0x07, 0x62, 0x07, 0x6B, 0x07, 0x73, 0x07, 0x7B, 0x07, 0x83, 0x07, 0x8A, 0x07, 0x90,
        // 0x07, 0x97, 0x07, 0x9D, 0x07, 0xA2, 0x07, 0xA7, 0x07, 0xAC, 0x07, 0xB1, 0x07, 0xB6, 0x07, 0xBA,
        // 0x07, 0xBE, 0x07, 0xC1, 0x07, 0xC4, 0x07, 0xC8, 0x07, 0xCB, 0x07, 0xCE, 0x07, 0xD1, 0x07, 0xD4, 0x07, 0xD6,
        // Continues above, but above is probably sufficient
    DEF_PATTERN_BUF(sig_mplay2, AR_ARGS(0x07, 0xD9, 0x07, 0xDB, 0x07, 0xDD, 0x07, 0xDF, 0x07, 0x4D, 0x50, 0x6C, 0x61, 0x79, 0x32));
    DEF_PATTERN_BUF(sig_mplay1, AR_ARGS(0x07, 0xD9, 0x07, 0xDB, 0x07, 0xDD, 0x07, 0xDF, 0x07, 0xCC, 0xCC, 0xCC, 0xCC, 0x00, 0x00, 0x00, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0x00, 0x00, 0x00, 0x00));

    // ==== mmlgb
    // https://github.com/SimonLarsen/tobutobugirl-dx/blob/master/mmlgb/driver/vib.c#L18
                                        // Start if array below, but probably sufficient without it
                                        // 0x04, 0x04, 0x05, 0x05, 0x06, 0x06, 0x06, 0x07, 0x07, 0x07, 0x07, 0x08, 0x08, 0x08, 0x08, 0x08,
    DEF_PATTERN_BUF(sig_mmlgb1, AR_ARGS(0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x07, 0x07, 0x07, 0x07, 0x06, 0x06, 0x06, 0x05, 0x05, 0x04,
                                        0x04, 0x04, 0x03, 0x03, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x03, 0x03, 0x04));
    // https://github.com/SimonLarsen/tobutobugirl-dx/blob/master/mmlgb/driver/vib.c#L25
                                        // Start if array below, but probably sufficient without it
                                        // 0x08, 0x09, 0x0A, 0x0A, 0x0B, 0x0C, 0x0C, 0x0D, 0x0E, 0x0E, 0x0F, 0x0F, 0x0F, 0x10, 0x10, 0x10,
    DEF_PATTERN_BUF(sig_mmlgb2, AR_ARGS(0x10, 0x10, 0x10, 0x10, 0x0F, 0x0F, 0x0F, 0x0E, 0x0E, 0x0D, 0x0C, 0x0C, 0x0B, 0x0A, 0x0A, 0x09,
                                        0x08, 0x07, 0x06, 0x06, 0x05, 0x04, 0x04, 0x03, 0x02, 0x02, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x02, 0x02, 0x03, 0x04, 0x04, 0x05, 0x06, 0x06, 0x07));
    // Retro-Hax extension of mmlgb, unofficial "mmlgb2"
    // https://github.com/Retro-Hax/mmlgb2/commit/b79306a89e886f2d37d89f2416b16eb61ef79935#diff-81ba965f2e900e504b3ac868a4856fc7a37d4a89b758a4fa9b7a9df7a5f5833cR117
    DEF_PATTERN_BUF(sig_mmlgb_v2, AR_ARGS(55, 54, 53, 52, 39, 38, 37, 36, 23, 22, 21, 20, 0, 0, 0, 0, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0));


    // GBMC (GameBoy Music Compiler)
    // http://mydocuments.g2.xrea.com/html/gb/sounddriver.html
    // sdrv_0.z80 Snd_EXEC_MODV (midway through)
    DEF_PATTERN_BUF(sig_gbmc_snd_exec_modv, AR_ARGS(0x7E, 0xCB, 0x37, 0x0F, 0x4F, 0x3E, 0x04, 0x91, 0xE6, 0x03, 0x80, 0xFE, 0x04, 0x38, 0x06, 0x07, 0x3E, 0x03, 0x30, 0x01, 0xAF, 0x47, 0x3E, 0x04, 0x90, 0xE6, 0x03, 0x87, 0xCB, 0x37));


    // Tip via Coffee Bat
    // Audio Arts (Allister Brimble, Will Davis)
    // After music / driver data: "0x.1..2v.3S.4!.5..6..7$.8h.9" .. then .. "== THE END =="
    DEF_PATTERN_STR(sig_audio_arts_term_1, "-- THE END --");
    DEF_PATTERN_BUF(sig_audio_arts_term_2, AR_ARGS(0x30, 0x78, 0x01, 0x31, 0x88, 0x01, 0x32, 0x76, 0x01, 0x33, 0x53, 0x01, 0x34, 0x21, 0x01, 0x35, 0x00, 0x01, 0x36, 0x01, 0x01, 0x37, 0x24, 0x01, 0x38, 0x68, 0x01, 0x39));


// Check for misc sound drivers
void check_music(void) {
    tool_entry entry;

    entry = FORMAT_ENTRY(TYPE_MUSIC,"GHX", "");
    if (FIND_PATTERN_STR_NOTERM(sig_str_ghx_audio) ||
        FIND_PATTERN_STR_NOTERM(sig_str_ghx_sound))
        entry_add(entry);

    entry = FORMAT_ENTRY(TYPE_MUSIC,"DevSound","Standard");
    if (FIND_PATTERN_STR_NOTERM(sig_str_devsound_standard)) {
        entry_add(entry);
    }
    else if (FIND_PATTERN_STR_NOTERM(sig_str_devsound_lite)) {
        entry = FORMAT_ENTRY(TYPE_MUSIC,"DevSound","Lite");
        entry_add(entry);
    }
    else if (FIND_PATTERN_STR_NOTERM(sig_str_devsound_x)) {
        entry = FORMAT_ENTRY(TYPE_MUSIC,"DevSound","X");
        entry_add(entry);
    }

    entry = FORMAT_ENTRY(TYPE_MUSIC,"Visual Impact", "");
    if (FIND_PATTERN_STR_NOTERM(sig_str_gbmusicplayer_audio))
        entry_add(entry);

    entry = FORMAT_ENTRY(TYPE_MUSIC,"MusyX", "");
    if (FIND_PATTERN_STR_NOTERM(sig_str_MusyX_1) ||
        FIND_PATTERN_STR_NOTERM(sig_str_MusyX_2) ||
        FIND_PATTERN_STR_NOTERM(sig_str_MusyX_3))
        entry_add(entry);

    entry = FORMAT_ENTRY(TYPE_MUSIC,"Freaq", "");
    if (FIND_PATTERN_STR_NOTERM(sig_str_freaq_1) ||
        FIND_PATTERN_STR_NOTERM(sig_str_freaq_2))
        entry_add(entry);

    entry = FORMAT_ENTRY(TYPE_MUSIC,"LSDJ", "");
    if (FIND_PATTERN_STR_NOTERM(sig_str_lsdj_1) ||
        FIND_PATTERN_STR_NOTERM(sig_str_lsdj_2))
        entry_add(entry);

    // hUGETracker and variants
    entry = FORMAT_ENTRY(TYPE_MUSIC,"hUGETracker","SuperDisk");
    if (FIND_PATTERN_BUF(sig_hugetracker_fx_vol_slide_base_v1))
        entry_add(entry);
    else if (FIND_PATTERN_BUF(sig_hugetracker_fx_vol_slide_base_v2))
        entry_add(entry);
    else if (FIND_PATTERN_BUF(sig_hugetracker_fortissimo_fx_vol_slide)) {
        entry = FORMAT_ENTRY(TYPE_MUSIC,"hUGETracker","fortISSimO");
        entry_add(entry);
    } else if (FIND_PATTERN_BUF(sig_hugetracker_fx_get_note_poly)) {

        if (FIND_PATTERN_BUF(sig_hugetracker_fx_coffeebat_get_shift_ch3)) {
            entry = FORMAT_ENTRY(TYPE_MUSIC,"hUGETracker","Coffee Bat");
            entry_add(entry);
        } else
            entry_add(entry); // Fallback, default HT entry
    }

    entry = FORMAT_ENTRY(TYPE_MUSIC,"Trackerboy engine", "");
    if (FIND_PATTERN_STR_NOTERM(sig_tbengine_noisetable))
        entry_add(entry);

    entry = FORMAT_ENTRY(TYPE_MUSIC,"Black Box Music Box", "");
    if (FIND_PATTERN_BUF(sig_blackboxplayer_1) &&
        FIND_PATTERN_BUF(sig_blackboxplayer_2))
        entry_add(entry);

    entry = FORMAT_ENTRY(TYPE_MUSIC,"Lemon", "");
    if (FIND_PATTERN_BUF(sig_lemon_wave_default))
        entry_add(entry);

    entry = FORMAT_ENTRY(TYPE_MUSIC,"GBT Player", "");
    if (FIND_PATTERN_BUF(sig_gbtplayer_gbt_wave))
        entry_add(entry);

    entry = FORMAT_ENTRY(TYPE_MUSIC,"Carillon Player", "");
    if (FIND_PATTERN_STR_NOTERM(sig_carillon_player_1) ||
        FIND_PATTERN_STR_NOTERM(sig_carillon_player_2))
        entry_add(entry);

    entry = FORMAT_ENTRY(TYPE_MUSIC,"MPlay", "");
    if (FIND_PATTERN_BUF(sig_mplay2))
        entry_add_with_version(entry, "2");
    else if (FIND_PATTERN_BUF(sig_mplay1))
        entry_add_with_version(entry, "1");

    // GBSoundSystem (Paragon5) and variants
    entry = FORMAT_ENTRY(TYPE_MUSIC,"GBSoundSystem","Modern");
    if (FIND_PATTERN_BUF(sig_gbsoundsystem_modern_SSFP_multi_sfx)) {
        entry_add(entry);
    }
    else {
        entry = FORMAT_ENTRY(TYPE_MUSIC,"GBSoundSystem","Classic");
        if (FIND_PATTERN_STR_NOTERM(sig_str_gbsoundsystem_1) &&
            FIND_PATTERN_STR_NOTERM(sig_str_gbsoundsystem_2))
            entry_add(entry);
        else if (FIND_PATTERN_BUF(sig_gbsoundsystem_MultiSFXLoop))
            entry_add(entry);
    }

    // MMLGB and variants
    entry = FORMAT_ENTRY(TYPE_MUSIC,"MMLGB", "");
    if ((FIND_PATTERN_BUF(sig_mmlgb1)) || (FIND_PATTERN_BUF(sig_mmlgb2))) {
        if (FIND_PATTERN_BUF(sig_mmlgb_v2))
            entry_add_with_version(entry, "Retro-Hax");
        else
            entry_add(entry);
    }

    // GBMC (Game Boy Music Compiler)
    entry = FORMAT_ENTRY(TYPE_MUSIC,"GBMC", "");
    if (FIND_PATTERN_BUF(sig_gbmc_snd_exec_modv))
            entry_add(entry);

    // Audio Arts
    entry = FORMAT_ENTRY(TYPE_MUSIC,"Audio Arts", "");
    if (FIND_PATTERN_STR_NOTERM(sig_audio_arts_term_1))
        if (FIND_PATTERN_STR_NOTERM(sig_audio_arts_term_2))
            entry_add(entry);
}
