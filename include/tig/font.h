#ifndef TIG_FONT_H_
#define TIG_FONT_H_

#include "tig/types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TIG_FONT_HANDLE_INVALID ((tig_font_handle_t)0)

typedef enum TigFontFlags {
    TIG_FONT_SCALE = 0x01,
    TIG_FONT_UNDERLINE = 0x02,
    TIG_FONT_SHADOW = 0x08,
    TIG_FONT_CENTERED = 0x10,
    TIG_FONT_STRIKE_THROUGH = 0x20,
    TIG_FONT_NO_ALPHA_BLEND = 0x80,
    TIG_FONT_BLEND_ADD = 0x100,
} TigFontFlags;

typedef struct TigFont {
    /* 0000 */ TigFontFlags flags;
    /* 0004 */ tig_art_id_t art_id;
    /* 0008 */ tig_color_t color;
    /* 000C */ tig_color_t underline_color;
    /* 0010 */ int field_10;
    /* 0014 */ tig_color_t strike_through_color;
    /* 0018 */ float scale;
    /* 001C */ const char* str;
    /* 0020 */ int width;
    /* 0024 */ int height;
    /* 0028 */ int field_28;
} TigFont;

// See 0x5352E0.
static_assert(sizeof(TigFont) == 0x2C, "wrong size");

int tig_font_init(TigInitInfo* init_info);
void tig_font_exit();
void tig_font_create(TigFont* font, tig_font_handle_t* font_handle_ptr);
void tig_font_destroy(tig_font_handle_t font_handle);
int tig_font_push(tig_font_handle_t font_handle);
void tig_font_pop();
void sub_535390(TigFont* font);
int tig_font_write(TigVideoBuffer* video_buffer, const char* str, const TigRect* rect, TigRect* dirty_rect);

#ifdef __cplusplus
}
#endif

#endif /* TIG_FONT_H_ */
