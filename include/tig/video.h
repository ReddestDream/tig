#ifndef TIG_VIDEO_H_
#define TIG_VIDEO_H_

#define DIRECTDRAW_VERSION 0x0700
#include <ddraw.h>

#include "tig/color.h"
#include "tig/rect.h"
#include "tig/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum TigVideoBufferCreateFlags {
    TIG_VIDEO_BUFFER_CREATE_COLOR_KEY = 0x0001,
    TIG_VIDEO_BUFFER_CREATE_VIDEO_MEMORY = 0x0002,
    TIG_VIDEO_BUFFER_CREATE_SYSTEM_MEMORY = 0x0004,
    TIG_VIDEO_BUFFER_CREATE_3D = 0x0008,
    TIG_VIDEO_BUFFER_CREATE_TEXTURE = 0x0010,
} TigVideoBufferCreateFlags;

typedef enum TigVideoBufferFlags {
    TIG_VIDEO_BUFFER_LOCKED = 0x0001,
    TIG_VIDEO_BUFFER_COLOR_KEY = 0x0002,
    TIG_VIDEO_BUFFER_VIDEO_MEMORY = 0x0004,
    TIG_VIDEO_BUFFER_SYSTEM_MEMORY = 0x0008,
    TIG_VIDEO_BUFFER_3D = 0x0010,
    TIG_VIDEO_BUFFER_TEXTURE = 0x0020,
} TigVideoBufferFlags;

typedef enum TigVideoBufferBlitFlags {
    TIG_VIDEO_BUFFER_BLIT_FLIP_X = 0x0001,
    TIG_VIDEO_BUFFER_BLIT_FLIP_Y = 0x0002,
    TIG_VIDEO_BUFFER_BLIT_BLEND_ADD = 0x0004,
    TIG_VIDEO_BUFFER_BLIT_BLEND_MUL = 0x0010,
    TIG_VIDEO_BUFFER_BLIT_BLEND_ALPHA_AVG = 0x0020,
    TIG_VIDEO_BUFFER_BLIT_BLEND_ALPHA_CONST = 0x0040,
    TIG_VIDEO_BUFFER_BLIT_BLEND_ALPHA_SRC = 0x0080,
    TIG_VIDEO_BUFFER_BLIT_BLEND_ALPHA_LERP = 0x0100,
    TIG_VIDEO_BUFFER_BLIT_BLEND_COLOR_CONST = 0x0200,
    TIG_VIDEO_BUFFER_BLIT_BLEND_COLOR_LERP = 0x0400,
    TIG_VIDEO_BUFFER_BLIT_FLIP_ANY = TIG_VIDEO_BUFFER_BLIT_FLIP_X | TIG_VIDEO_BUFFER_BLIT_FLIP_Y,
} TigVideoBufferBlitFlags;

// Opaque handle.
typedef struct TigVideoBuffer TigVideoBuffer;

typedef struct TigVideoBufferCreateInfo {
    /* 0000 */ unsigned int flags;
    /* 0004 */ int width;
    /* 0008 */ int height;
    /* 000C */ unsigned int background_color;
    /* 0010 */ unsigned int color_key;
} TigVideoBufferCreateInfo;

static_assert(sizeof(TigVideoBufferCreateInfo) == 0x14, "wrong size");

typedef struct TigVideoBufferData {
    /* 0000 */ unsigned int flags;
    /* 0004 */ int width;
    /* 0008 */ int height;
    /* 000C */ int pitch;
    /* 0010 */ int background_color;
    /* 0014 */ int color_key;
    /* 0018 */ int bpp;
    /* 001C */ union {
        void* pixels;
        uint8_t* p8;
        uint16_t* p16;
        uint32_t* p32;
    } surface_data;
} TigVideoBufferData;

static_assert(sizeof(TigVideoBufferData) == 0x20, "wrong size");

typedef struct TigVideoBufferBlitInfo {
    /* 0000 */ unsigned int flags;
    /* 0004 */ TigVideoBuffer* src_video_buffer;
    /* 0008 */ TigRect* src_rect;
    /* 000C */ uint8_t alpha[4];
    /* 0010 */ int field_10;
    /* 0014 */ int field_14;
    /* 0018 */ int field_18;
    /* 001C */ int field_1C;
    /* 0020 */ TigRect* field_20;
    /* 0024 */ TigVideoBuffer* dst_video_buffer;
    /* 0028 */ TigRect* dst_rect;
} TigVideoBufferBlitInfo;

static_assert(sizeof(TigVideoBufferBlitInfo) == 0x2C, "wrong size");

typedef struct TigVideoScreenshotSettings {
    /* 0000 */ int key;
    /* 0004 */ int field_4;
} TigVideoScreenshotSettings;

typedef enum TigVideoBufferTintMode {
    TIG_VIDEO_BUFFER_TINT_MODE_ADD,
    TIG_VIDEO_BUFFER_TINT_MODE_SUB,
    TIG_VIDEO_BUFFER_TINT_MODE_MUL,
    TIG_VIDEO_BUFFER_TINT_MODE_GRAYSCALE,
    TIG_VIDEO_BUFFER_TINT_MODE_COUNT,
} TigVideoBufferTintMode;

typedef struct TigVideoBufferSaveToBmpInfo {
    /* 0000 */ unsigned int flags;
    /* 0004 */ TigVideoBuffer* video_buffer;
    /* 0008 */ char path[TIG_MAX_PATH];
    /* 010C */ TigRect* rect;
} TigVideoBufferSaveToBmpInfo;

static_assert(sizeof(TigVideoBufferSaveToBmpInfo) == 0x110, "wrong size");

int tig_video_init(TigInitInfo* init_info);
void tig_video_exit();
int tig_video_platform_window_get(HWND* wnd_ptr);
int tig_video_instance_get(HINSTANCE* instance_ptr);
int tig_video_main_surface_get(LPDIRECTDRAWSURFACE7* surface_ptr);
void tig_video_set_client_rect(LPRECT rect);
void tig_video_display_fps();
int tig_video_main_surface_lock(void** surface_data_ptr);
int tig_video_main_surface_unlock();
int tig_video_blit(TigVideoBuffer* src_video_buffer, TigRect* src_rect, TigRect* dst_rect, bool to_primary_surface);
int tig_video_fill(const TigRect* rect, tig_color_t color);
int sub_51F860();
int sub_51F880();
int tig_video_flip();
int tig_video_screenshot_set_settings(TigVideoScreenshotSettings* settings);
int tig_video_screenshot_make();
int sub_51FA40(TigRect* rect);
int tig_video_get_bpp(int* bpp);
int tig_video_get_palette(unsigned int* colors);
int tig_video_get_pitch(int* pitch);
int tig_video_3d_check_initialized();
int tig_video_3d_check_hardware();
int tig_video_3d_begin_scene();
int tig_video_3d_end_scene();
int tig_video_get_video_memory_status(size_t* total, size_t* available);
int tig_video_check_gamma_control();
int tig_video_fade(int color, int steps, float duration, unsigned int flags);
int tig_video_set_gamma(float gamma);
int tig_video_buffer_create(TigVideoBufferCreateInfo* vb_create_info, TigVideoBuffer** video_buffer);
int tig_video_buffer_destroy(TigVideoBuffer* video_buffer);
int tig_video_buffer_data(TigVideoBuffer* video_buffer, TigVideoBufferData* video_buffer_data);
int tig_video_buffer_set_color_key(TigVideoBuffer* video_buffer, int color_key);
int tig_video_buffer_lock(TigVideoBuffer* video_buffer);
int tig_video_buffer_unlock(TigVideoBuffer* video_buffer);
int tig_video_buffer_outline(TigVideoBuffer* video_buffer, TigRect* rect, int color);
int tig_video_buffer_fill(TigVideoBuffer* video_buffer, TigRect* rect, int color);
int tig_video_buffer_line(TigVideoBuffer* video_buffer, TigLine* line, TigRect* a3, unsigned int color);
int sub_520FB0(TigVideoBuffer* video_buffer, unsigned int flags);
int tig_video_buffer_blit(TigVideoBufferBlitInfo* blit_info);
int tig_video_buffer_get_pixel_color(TigVideoBuffer* video_buffer, int x, int y, unsigned int* color);
int tig_video_buffer_tint(TigVideoBuffer* video_buffer, TigRect* rect, tig_color_t tint_color, TigVideoBufferTintMode mode);
int tig_video_buffer_save_to_bmp(TigVideoBufferSaveToBmpInfo* save_info);
int tig_video_buffer_load_from_bmp(const char* filename, TigVideoBuffer** video_buffer_ptr, unsigned int flags);

#ifdef __cplusplus
}
#endif

#endif /* TIG_VIDEO_H_ */
