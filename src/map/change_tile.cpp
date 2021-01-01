#include "./change_tile.h"

void change_tile_map (int x, int y, int o_or_t, std::vector<unsigned char> *buffer, int color) {
	unsigned char prev_color = (buffer->at(x + (y * 78))), res_color;
	if (!o_or_t) {
		res_color =
			((prev_color & 0xF0) >> 4)
			+ color;
	} else {
		res_color =
			(color * 10) +
			(prev_color & 0x0F);
	}
	buffer->at(x + (y * 78)) = res_color;
}
