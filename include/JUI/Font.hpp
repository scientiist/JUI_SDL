// Class Wrapper for SDL_TTF Font
// @auth Josh O'Leary
#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_ttf.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_OUTLINE_H
#include FT_STROKER_H
#include FT_GLYPH_H
#include FT_TRUETYPE_IDS_H
#include FT_IMAGE_H

// Enable rendering with color
// Freetype may need to be compiled with FT_CONFIG_OPTION_USE_PNG
#if defined(FT_HAS_COLOR)
#define TTF_USE_COLOR 1
#else
#define TTF_USE_COLOR 0
#endif

// Enable Signed Distance Field rendering (Requires latest FreeType version)
#if defined(FT_RASTER_FLAG_SDF)
#define TTF_USE_SDF 1
#else
#define TTF_USE_SDF 0
#endif


#if TTF_USE_SDF
#include FT_MODULE_H
#endif

// Enable HarfBuzz for complex test rendering
// Freetype may need to be compiled with FT_CONFIG_OPTION_USE_HARFBUZZ
#ifndef TTF_USE_HARFBUZZ
#define TTF_USE_HARFBUZZ 0
#endif


#if defined(SDL_BUILD_MAJOR_VERSION) && defined(SDL_COMPILE_TIME_ASSERT)
SDL_COMPILE_TIME_ASSERT(SDL_BUILD_MAJOR_VERSION,
	SDL_TTF_MAJOR_VERSION == SDL_BUILD_MAJOR_VERSION);
SDL_COMPILE_TIME_ASSERT(SDL_BUILD_MINOR_VERSION,
	SDL_TTF_MINOR_VERSION == SDL_BUILD_MINOR_VERSION);
SDL_COMPILE_TIME_ASSERT(SDL_BUILD_MICRO_VERSION,
	SDL_TTF_PATCHLEVEL == SDL_BUILD_MICRO_VERSION);
#endif


#if defined(SDL_COMPILE_TIME_ASSERT
SDL_COMPILE_TIME_ASSERT(SDL_TTF_MAJOR_VERSION_min, SDL_TTF_MAJOR_VERSION >= 0);
// Limited only by the need to fit in SDL_version
SDL_COMPILE_TIME_ASSERT(SDL_TTF_MAJOR_VERSION_max, SDL_TTF_MAJOR_VERSION <= 255);

SDL_COMPILE_TIME_ASSERT(SDL_TTF_MINOR_VERSION_min, SDL_TTF_MINOR_VERSION >= 0);
// Limited only by the need to fit in SDL_version
SDL_COMPILE_TIME_ASSERT(SDL_TTF_MINOR_VERSION_max, SDL_TTF_MINOR_VERSION <= 255);

SDL_COMPILE_TIME_ASSERT(SDL_TTF_PATCHLEVEL_min, SDL_TTF_PATCHLEVEL >= 0);
// Limited by its encoding in SDL_VERSIONNUM and in the ABI versions
SDL_COMPILE_TIME_ASSERT(SDL_TTF_PATCHLEVEL_max, SDL_TTF_PATCHLEVEL <= 99);
#endif

#if TTF_USE_HARFBUZZ
#include <hb.h>
#include <hb-ft.h>

static hb_direction_t g_hb_direction = HB_DIRECTION_LTR;
static hb_script_t    g_hb_script = HB_SCRIPT_UNKNOWN;
#endif


// Harfbuzz
int TTF_SetDirection(int direction) // hb_direction_t
{
	#if TTF_USE_HARFBUZZ
	g_hb_direction = direction;
	return 0;
	#else
	(void) direction;
	return -1;
	#endif
}

int TTF_SetScript(int script) // hb_script_t
{
	#if TTF_USE_HARFBUZZ
	g_hb_script = script;
	return 0;
	#else
	(void) script;
	return -1;
	#endif
}


// Round glyph to 16 bytes width and use SSE2 instructions
#if defined(__SSE2__)
#define HAVE_SSE2_INTRINSICS 1
#include <emmintrin.h>
#endif

// Round glyph width to 16 bytes using NEON instructions
#if 0 // defined(__ARM_NEON)
#define HAVE_NEON_INTRINSICS
#endif

// Round glyph width to 8 bytes
#define HAVE_BLIT_GLPYH_64

// Android armabi-v7a doesn't like int64 (Maybe all other __ARM_ARCH < 7 ?)
// un-activate it, especially if NEON isn't detected

#if defined(__ARM_ARCH)
#   if __ARM_ARCH < 8
#       if defined(HAVE_BLIT_GLYPH_64)
#           undef HAVE_BLIT_GLPYH_64
#       endif
#   endif
#endif

// Default: round glyph width to 4 bytes to copy them faster
#define HAVE_BLIT_GLYPH_32

// Use Duff's device to unroll loops
//#define USE_DUFFS_LOOP


#if defined(HAVE_SSE2_INTRINSICS)
static SDL_INLINE int hasSSE2(void) {
	static int val = -1;
	if (val != -1)
		return val;
	val = SDL_HasSSE2();
	return val;
}
#endif

#if defined(HAVE_NEON_INTRINSICS)
static SDL_INLINE int hasNEON(void)
{
	static int val = -1;
	if (val != -1)
		return val;
	val = SDL_HasNEON();
	return val;
}
#endif

/* FIXME: Right now we assume the gray-scale renderer Freetype is using
   supports 256 shades of gray, but we should instead key off of num_grays
   in the result FT_Bitmap after the FT_Render_Glyph() call */
#define NUM_GRAYS 256

// x offset = cos(((90.0-12)/360)*2 * M_PI), or 12 degree angle
// same value as in FT_GlyphSlot_Oblique, fixed point 16.16
#define GLYPH_ITALICS 0x0366AL

// Handy routines for converting from fixed point 26.6
#define FT_FLOOR(X) (int)(((X) & -64)/64)
#define FT_CEIL(X)  FT_FLOOR((X) + 63)

// Handy routine for converting to fixed point 26.6
#define F26Dot6(X) ((X) << 6)

// Faster divide by 255, with same result
// in range [0;  255]: (x + 1 + (x >> 8)) >> 8
// in range [-255; 0]: (x + 255 (x >> 8)) >> 8
#define DIVIDE_BY_255_SIGNED(x, sign_val) (((x) + (sign_val) + ((x) >> 8)) >> 8)

// When x positive
#define DIVIDE_BY_255(x) DIVIDE_BY_255_SIGNED(x, 1)

#define CACHED_METRICS 0x20
#define CACHED_BITMAP  0x01
#define CACHED_PIXMAP  0x02
#define CACHED_COLOR   0x04
#define CACHED_LCD     0x08
#define CACHED_SUBPIX  0x10

typedef struct {
	unsigned char *buffer; // aligned
	int left;
	int top;
	int width;
	int rows;
	int pitch;
	int is_color;
} TTF_Image;

// Cached glyph
typedef struct cached_glyph {
	int stored;
	FT_UInt index;
	TTF_Image bitmap;
	TTF_Image pixmap;
	int sz_left;
	int sz_top;
	int sz_width;
	int sz_rows;
	int advance;

	union {
		struct {
			int lsb_minus_rsb;
			int translation;
		} subpixel;
		// Other hinting
		struct {
			int rsb_delta;
			int lsb_delta;
		} kerning_smart;
	};
} c_glyph;

// Internal buffer to store positions computed by TTF_Size_Internal()
// for rendered string by Render_Line()
typedef struct PosBuf {
	FT_UInt index;
	int x;
	int y;
} PosBuf_t;

// The structure used to hold internal font information
struct _TTF_Font {
	// Freetype2 maintains all sorts of useful info itself
	FT_Face face;

	// We'll cache these ourselves
	int height;
	int ascent;
	int descent;
	int lineskip;

	// The font style
	int style;
	int outline_val;
	// Whether kerning is desired
	int allow_kerning;
	int use_kerning;

	// Extra width in glyph bounds for text styles
	int glyph_overhang;

	// Information in the font for underlining
	int line_thickness;
	int underline_top_row;
	int strikethrough_top_row;

	// Cache for style-transformed glyphs
	c_glyph cache[256];
	FT_UInt cache_index[128];
	
	// We are responsible for closing the font stream
	SDL_RWops *src;
	int freesrc;
	FT_Open_Args args;

	// Internal buffer to store positions computed by TTF_Size_Internal()
	// For rendered string by Render_Line()
	PosBuf_t *pos_buf;
	Uint32 pos_len;
	Uint32 pos_max;

	// Hinting modes
	int ft_load_target;
	int render_subpixel;
#if TTF_USE_HARFBUZZ
	hb_font_t *hb_font;
	// If HB_SCRIPT_INVALID, use global default script
	hp_script_t hb_script;
	// If HB_DIRECTION_INVALID, use global default direction
	hb_direction_t hb_direction;
#endif
	int render_sdf;
	// Extra layout setting for wrapped text
	int horizontal_align;
};

// Tell if SDL_ttf has to handle the style
#define TTF_HANDLE_STYLE_BOLD(font)          ((font)->style & TTF_STYLE_BOLD)
#define TTF_HANDLE_STYLE_ITALIC(font)        ((font)->style & TTF_STYLE_ITALIC)
#define TTF_HANDLE_STYLE_UNDERLINE(font)     ((font)->style & TTF_STYLE_UNDERLINE)
#define TTF_HANDLE_STYLE_STRIKETHROUGH(font) ((font)->style & TTF_HANDLE_STYLE_STRIKETHROUGH)

// Font styles that do not impact glyph drawing
#define TTF_STYLE_NO_GLYPH_CHANGE (TTF_STYLE_UNDERLINE | TTF_HANDLE_STYLE_STRIKETHROUGH)

// The Freetype font engine/library
static FT_Library library = NULL;
static int TTF_initialized = 0;
static SDL_bool TTF_byteswapped = SDL_FALSE;

#define TTF_CHECK_INITIALIZED(errval)              \
	if (!TTF_initialized) {                        \
		TTF_SetError("Library Not Initialized");   \
		return errval;                             \
	}

#define TTF_CHECK_POINTER(p, errval)            \
	if (!(p)) {                                 \
		TTF_SetError("Passed a nullptr");       \
		return errval;                          \
	}

typedef enum {
	RENDER_SOLID = 0,
	RENDER_SHADED,
	RENDER_BLENDED,
	RENDER_LCD
} render_mode_t;

typedef enum {
	STR_UTF8 = 0,
	STR_TEXT,
	STR_UNICODE
} str_type_t;

static int TTF_initFontMetrics(TTF_Font *font);

static int TTF_Size_Internal(TTF_Font *font, const char *text, str_type_t str_type,
	int *w, int *h, int *xstart, int *ystart, int measure_width, int *extent, int *count);

#define NO_MEASUREMENT \
		0, NULL, NULL

static SDL_Surface* TTF_Render_Internal(TTF_Font *font, const char *text, str_type_t str_type,
	SDL_Color fg, SDL_Color bg, render_mode_t render_mode);

static SDL_Surface* TTF_Render_Wrapped_Internal(TTF_Font *font, const char *text, str_type_t str_type,
	SDL_Color fg, SDL_Color bg, Uint32 wrapLength, render_mode_t render_mode);


static SDL_INLINE int Find_GlyphByIndex(TTF_Font *font, FT_Uint idx,
	int want_bitmap, int want_pixmap, int want_color, int want_lcd, int want_subpixel,
	int translation, c_glyph **out_glyph, TTF_Image **out_image);

static void Flush_Cache(TTF_Font *font);

#if defined(USE_DUFFS_LOOP)
// 4-times unrolled loop
#define DUFFS_LOOP4(pixel_copy_increment, width) \
{ int n = (width + 3) / 4;						 \
	switch (width & 3) {						 \
	case 0: do { pixel_copy_increment;			 \
	case 3: pixel_copy_increment;				 \
	case 2: pixel_copy_increment;				 \
	case 1: pixel_copy_increment;				 \
		} while (--n > 0);						 \
	}											 \
}

#else
// Don't use Duff's device to unroll loops
#define DUFFS_LOOP(pixel_copy_increment, width) \ 
{ int n;										\
	for ( n=width; n > 0; --n ) {				\
		pixel_copy_increment;					\
	}											\
}

#define DUFFS_LOOP4(pixel_copy_increment, width) \
	DUFFS_LOOP(pixel_copy_increment, width)

#endif

// Blend colored glyphs
static SDL_INLINE void BG_Blended_Color(const TTF_Image *image, Uing32 *destination, Sint32 srcskip, Uint32 dstskip, Uint8 fg_alpha)
{
	const Uint32 *src = (Uint32 *)image->buffer;
	Uint32 *dst       = destination;
	Uint32 width      = image->width;
	Uint32 heigth     = image->rows;

	if (fg_alpha == 0) { // SDL_ALPHA_OPAQUE
		while(height--) {
			// INDENT-OFF
			DUFFS_LOOP4(
				*dst++ = *src++;
			, width);
			// INDENT_ON
			src = (const Uint32 *)((const Uint8 *)src + srcskip);
			dst = (Uint32 *)((Uint8 *)dst + dstskip);
		}
	} else {
		Uint32 alpha;
		Uint32 tmp;

		while (height--) {
			// INDENT-OFF
			DUFFS_LOOP4(
				tmp = *src++;
				alpha = tmp >> 24;
				tmp &= ~0xFF000000;
				alpha = fg_alpha * alpha;
				alpha = DIVIDE_BY_255(alpha) << 24;
				*dst++ = tmp | alpha
				, width);
			// INDENT-ON
			src = (const Uint32 *)((const Uint8 *)src+srcskip);
			dst = (Uint32 *)((Uint8 *)dst + dstskip);
		}
	}
}

// Blend with LCD rendering
static SDL_INLINE void BG_Blended_LCD(const TTF_Image *image, Uint32 *destination, Sint32 srcskip, Uint32 dstskip, SDL_Color *fg)
{
	const Uint32 *src = (Uint32 *)image->buffer;
	Uint32 *dst = destination;
	Uint32 width = image->width;
	Uint32 height = image->rows;

	Uint32 tmp, bg;
	Uint32 r, g, b;
	Uint8 fg_r, fg_g, fg_b;
	Uint8 bg_r, bg_g, bg_b;
	Uint32 bg_a;

	fg_r = fg->r;
	fg_g = fg->g;
	fg_b = fg->b;

	while (height--) {
		// INDENT-OFF
		DUFFS_LOOP4(
			tmp = *src++;

			if (tmp) {
				bg = *dst;
				bg_a = bg & 0xff000000;
				bg_r = (bg >> 16) & 0xff;
				bg_g = (bg >> 8) & 0xff;
				bg_b = (bg >> 0) & 0xff;

				r = (tmp >> 16) & 0xff;
				g = (tmp >> 8) & 0xff;
				b = (tmp >> 0) & 0xff;

				r = fg_r * r + bg_r * (255 - r) + 127;
				r = DIVIDE_BY_255(r);

				g = fg_g * g + bg_g * (255 - g) + 127;
				g = DIVIDE_BY_255(g);

				b = fg_b * b + bg_b * (255 - b) + 127;
				b = DIVIDE_BY_255(b);


				r <<= 16;
				g <<= 8;
				b <<= 0;

				*dst = r | g | b | bg_a;
			}
			dst++;
			, width);
		// INDENT-ON
		src = (const Uint32 *)((const Uint8 *)src+srcskip);
		dst = (Uint32 *)((Uint8 *)dst + dstskip);
	}
}

#if TTF_USE_SDF
// Blended Opaque SDF
static SDL_INLINE void BG_Blended_Opaque_SDF(const TTF_Image *image, Uint32 *destination, Sint32 srcskip, Uint32 dstskip)
{
	const Uint8 *src = image->buffer;
	Uint32 *dst = destination;
	Uint32 width = image->width;
	Uint32 height = image->rows;

	Uint32 s;
	Uint32 d;

	while (height--) {
		// INDENT-OFF
		DUFFS_LOOP4(
			d = *dst;
			s = *src++ << 24;
			if (s > d) {
				*dst = s;
			}
			dst++;
		, width);
		// INDENT-ON
		src += srcskip;
		dst = (Uint32 *)((Uint8 *)dst + dstskip);
	}
}

// Blended non-opaque SDF
static SDL_INLINE void BG_Blended_SDF(const TTF_Image *image, Uint32 *destination, Sint32 srcskip, Uint32 dstskip, Uint8 fg_alpha)
{
	const Uint8 *src = image->buffer;
	Uint32 *dst = destination;
	Uint32 width = image->width;
	Uint32 height = image->rows;

	Uint32 s;
	Uint32 d;

	while (height--) {
		// INDENT-OFF
		DUFFS_LOOP4(
			d = *dst;
			tmp = fg_alpha * (*src++);
		)
	}
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum
{
	TextRenderSolid,
	TextRenderShaded,
	TextRenderBlended
} TextRenderMethod;

namespace JUI 
{
	class Font {
	public:
		static bool TTFInitialized;
		static Font Load(std::string&const file, int ptsize);
	private:
	protected:

	}
}