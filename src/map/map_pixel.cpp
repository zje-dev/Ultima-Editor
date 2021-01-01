#include "./map_pixel.h"

void draw_tile_on_bmp (std::vector<unsigned char> *buf, int color, int pos, bool ot, int *e) {
	const int index = buf->size() - pos;
	switch (color) {
		case 0:
			buf->at(index - 1) = ((unsigned char)000);
			buf->at(index - 2) = ((unsigned char)153);
			buf->at(index - 3) = ((unsigned char)204);
			break;
		case 1:
			buf->at(index - 1) = ((unsigned char)000);
			buf->at(index - 2) = ((unsigned char)255);
			buf->at(index - 3) = ((unsigned char)000);
			break;
		case 2:
			buf->at(index - 1) = ((unsigned char)000);
			buf->at(index - 2) = ((unsigned char) 50);
			buf->at(index - 3) = ((unsigned char)000);
			break;
		case 3:
			buf->at(index - 1) = ((unsigned char)150);
			buf->at(index - 2) = ((unsigned char)150);
			buf->at(index - 3) = ((unsigned char)150);
			break;
		case 4:
			buf->at(index - 1) = ((unsigned char) 20);
			buf->at(index - 2) = ((unsigned char) 20);
			buf->at(index - 3) = ((unsigned char) 20);
			break;
		case 5:
			buf->at(index - 1) = ((unsigned char)255);
			buf->at(index - 2) = ((unsigned char)255);
			buf->at(index - 3) = ((unsigned char)204);
			break;
		case 6:
			buf->at(index - 1) = ((unsigned char)255);
			buf->at(index - 2) = ((unsigned char)204);
			buf->at(index - 3) = ((unsigned char)153);
			break;
		case 7:
			buf->at(index - 1) = ((unsigned char)255);
			buf->at(index - 2) = ((unsigned char)000);
			buf->at(index - 3) = ((unsigned char)000);
			break;
	}
	*e++;
}
