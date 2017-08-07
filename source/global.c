#include "global.h"

char * fontChars =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ      0123456789.,!?'\"-+=/\\%()<>:;     ";

void drawText(char * msg, u32 x, u32 y) {
	int i = 0;
	for (i = 0; i < strlen(msg); ++i) {
		int ix = strchr(fontChars, toupper((unsigned char) msg[i])) - fontChars;
		int iy = ix >> 5;
		if (ix >= 0) {
			sf2d_draw_texture_part(font, x + i * 12, y, (ix & 31) * 12,
					16 + (iy * 12), 12, 12);
		}
	}
}

void drawSizedText(char * msg, u32 x, u32 y, float size) {
	int i = 0;
	for (i = 0; i < strlen(msg); ++i) {
		int ix = strchr(fontChars, toupper((unsigned char) msg[i])) - fontChars;
		int iy = ix >> 5;
		if (ix >= 0) {
			sf2d_draw_texture_part_scale(font, (x + i * 8) * size, y,
					(ix & 31) << 3, iy << 3, 8, 8, size, size);
		}
	}
}

void drawTextColor(char * msg, u32 x, u32 y, u32 color) {
	int i = 0;
	for (i = 0; i < strlen(msg); ++i) {
		int ix = strchr(fontChars, toupper((unsigned char) msg[i])) - fontChars;
		int iy = ix >> 5;
		if (ix >= 0) {
			sf2d_draw_texture_part_blend(font, x + i * 12, y, (ix & 31) * 12,
					16 + (iy * 12), 12, 12, color);
		}
	}
}

void drawSizedTextColor(char * msg, int x, int y, float size, u32 color) {
	int i;
	for (i = 0; i < strlen(msg); ++i) {
		int ix = strchr(fontChars, toupper((unsigned char) msg[i])) - fontChars;
		int iy = ix >> 5;
		if (ix >= 0)
			sf2d_draw_texture_part_scale_blend(font, (x + i * 8) * size,
					y * size, (ix & 31) << 3, iy << 3, 8, 8, size, size, color);
	}
}

