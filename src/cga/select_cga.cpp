#include <fstream>
#include <iterator>
#include "./select_cga.h"

int mx_color (int p_v, int n_v, bool s) {
	/*switch (n_v) {
		case 0:
			switch (p_v) {
				case 1:
					return (s ? 0 : 1);
					break;
				case 2:
					return (s ? 0 : 2);
					break;
				case 3:
					return (s ? 0 : 3);
					break;
				case 4:
					return (s ? 4 : 0);
					break;
				case 5:
					return (s ? 4 : 1);
					break;
				case 6:
					return (s ? 4 : 2);
					break;
				case 7:
					return (s ? 4 : 3);
					break;
				case 8:
					return (s ? 8 : 0);
					break;
				case 9:
					return (s ? 8 : 1);
					break;
				case 10:
					return (s ? 8 : 2);
					break;
				case 11:
					return (s ? 8 : 3);
					break;
				case 12:
					return (s ? 12 : 0);
					break;
				case 13:
					return (s ? 12 : 1);
					break;
				case 14:
					return (s ? 12 : 2);
					break;
				case 15:
					return (s ? 12 : 3);
					break;
			}
			break;
		case 1:
			switch (p_v) {
				case 0:
					return (s ? 3 : 12);
					break;
				case 1:
					return (s ? 3 : 13);
					break;
				case 2:
					return (s ? 3 : 14);
					break;
				case 3:
					return (s ? 3 : 15);
					break;
				case 4:
					return (s ? 7 : 12);
					break;
				case 5:
					return (s ? 7 : 13);
					break;
				case 6:
					return (s ? 7 : 14);
					break;
				case 7:
					return (s ? 7 : 15);
					break;
				case 8:
					return (s ? 11 : 12);
					break;
				case 9:
					return (s ? 11 : 13);
					break;
				case 10:
					return (s ? 11 : 14);
					break;
				case 11:
					return (s ? 11 : 15);
					break;
				case 12:
					return (s ? 15 : 12);
					break;
				case 13:
					return (s ? 15 : 13);
					break;
				case 14:
					return (s ? 15 : 14);
					break;
				case 15:
					return (s ? 15 : 15);
					break;
			}
			break;
		case 2:
			switch (p_v) {
				case 0:
					return (s ? 1 : 4);
					break;
				case 1:
					return (s ? 1 : 5);
					break;
				case 2:
					return (s ? 1 : 6);
					break;
				case 3:
					return (s ? 1 : 7);
					break;
				case 4:
					return (s ? 5 : 4);
					break;
				case 5:
					return (s ? 5 : 5);
					break;
				case 6:
					return (s ? 5 : 6);
					break;
				case 7:
					return (s ? 5 : 7);
					break;
				case 8:
					return (s ? 9 : 4);
					break;
				case 9:
					return (s ? 9 : 5);
					break;
				case 10:
					return (s ? 9 : 4);
					break;
				case 11:
					return (s ? 9 : 7);
					break;
				case 12:
					return (s ? 13 : 4);
					break;
				case 13:
					return (s ? 13 : 5);
					break;
				case 14:
					return (s ? 13 : 6);
					break;
				case 15:
					return (s ? 13 : 7);
					break;
			}
			break;
		case 3:
			switch (p_v) {
				case 0:
					return (s ? 2 : 8);
					break;
				case 1:
					return (s ? 2 : 9);
					break;
				case 2:
					return (s ? 2 : 10);
					break;
				case 3:
					return (s ? 2 : 11);
					break;
				case 4:
					return (s ? 6 : 8);
					break;
				case 5:
					return (s ? 6 : 9);
					break;
				case 6:
					return (s ? 6 : 10);
					break;
				case 7:
					return (s ? 6 : 11);
					break;
				case 8:
					return (s ? 10 : 8);
					break;
				case 9:
					return (s ? 10 : 9);
					break;
				case 10:
					return (s ? 10 : 10);
					break;
				case 11:
					return (s ? 10 : 11);
					break;
				case 12:
					return (s ? 14 : 8);
					break;
				case 13:
					return (s ? 14 : 9);
					break;
				case 14:
					return (s ? 14 : 10);
					break;
				case 15:
					return (s ? 14 : 11);
					break;
			}
			break;
	}*/
	return colors_table_cga[n_v][p_v][s];
}

void change_pixel (int x, int y, std::vector<unsigned char> *buffer, const char* path, int color, int tile, int y_m, int size, int size2) {
	/*int res_value = 0, init_value = ((x % 4 == 0) ? 12 : 3), prev_value = buffer.at(((int)(x / 4) + (y * 4)) + (tile * 64));
	std::cout << (int)(x / 4) << "\t" << (y * 4) << "\t" << (x % 4 == 0) << "\t" << (x % 2 == 0) << "\n";
	init_value = ((x % 4 == 0) ?
		mx_color(
			((x % 2 == 0) ? 
				((prev_value & 0xF0) >> 4)
				:
				(prev_value & 0x0F)
			), color, false)
			:
		mx_color(
			((x % 2 == 0) ? 
				((prev_value & 0xF0) >> 4)
				:
				(prev_value & 0x0F)
			), color, true)
	);
	if (x % 2	== 0) {
		res_value = (prev_value & 0x0F) + (init_value << 4);
	} else {
		res_value = (init_value << 4) + ((prev_value & 0xF0) >> 4);
	}
	buffer.at(((int)(x / 4) + (y * 4)) + (tile * 64)) = res_value;
	std::ofstream file(path, std::ios::out|std::ios::binary);
	copy(buffer.cbegin(), buffer.cend(), std::ostream_iterator<char>(file));
	*/
	int pixels[size];
	int pixel = 0;
	std::vector<unsigned char> tmp_buf = *buffer;
	for (int i = 0; i < size2; i++) {
		pixels[pixel] = byte_to_color((tmp_buf[i + (tile * size2)] & 0xF0) >> 4, false);
		pixels[pixel + 1] = byte_to_color((tmp_buf[i + (tile * size2)] & 0xF0) >> 4, true);
		pixels[pixel + 2] = byte_to_color(tmp_buf[i + (tile * size2)] & 0x0F, false);
		pixels[pixel + 3] = byte_to_color(tmp_buf[i + (tile * size2)] & 0x0F, true);
		pixel += 4;
	}
	pixels[x + (y * y_m)] = color;
	int first_byte = 0, second_byte = 0, e = 0;
	for (int i = 0; i < size; i += 4) {
		first_byte = color_to_byte(pixels[i], pixels[i + 1]);
		second_byte = color_to_byte(pixels[i + 2], pixels[i + 3]);
		buffer->at(e + (tile * size2)) = ((first_byte << 4) + second_byte);
		e += 1;
	}
	std::ofstream file(path, std::ios::out|std::ios::binary);
	copy(buffer->cbegin(), buffer->cend(), std::ostream_iterator<char>(file));
}

int color_to_byte (int byte1, int byte2) { //PATTERN
	switch (byte1) {
		case 0:
			switch (byte2) {
				case 0:
					return 0;
					break;
				case 1:
					return 3;
					break;
				case 2:
					return 1;
					break;
				case 3:
					return 2;
					break;
			}
			break;
		case 1:
			switch (byte2) {
				case 0:
					return 12;
					break;
				case 1:
					return 15;
					break;
				case 2:
					return 13;
					break;
				case 3:
					return 14;
					break;
			}
			break;
		case 2:
			switch (byte2) {
				case 0:
					return 4;
					break;
				case 1:
					return 7;
					break;
				case 2:
					return 5;
					break;
				case 3:
					return 6;
					break;
			}
			break;
		case 3:
			switch (byte2) {
				case 0:
					return 8;
					break;
				case 1:
					return 11;
					break;
				case 2:
					return 9;
					break;
				case 3:
					return 10;
					break;
			}
			break;
		default:
			return 0;
	};
}

int byte_to_color (int color, bool c) {
	switch (color) {
		case 0:
			return (!c ? 0 : 0);
			break;
		case 1:
			return (!c ? 0 : 2);
			break;
		case 2:
			return (!c ? 0 : 3);
			break;
		case 3:
			return (!c ? 0 : 1);
			break;
		case 4:
			return (!c ? 2 : 0);
			break;
		case 5:
			return (!c ? 2 : 2);
			break;
		case 6:
			return (!c ? 2 : 3);
			break;
		case 7:
			return (!c ? 2 : 1);
			break;
		case 8:
			return (!c ? 3 : 0);
			break;
		case 9:
			return (!c ? 3 : 2);
			break;
		case 10:
			return (!c ? 3 : 3);
			break;
		case 11:
			return (!c ? 3 : 1);
			break;
		case 12:
			return (!c ? 1 : 0);
			break;
		case 13:
			return (!c ? 1 : 2);
			break;
		case 14:
			return (!c ? 1 : 3);
			break;
		case 15:
			return (!c ? 1 : 1);
			break;
		default:
			return (!c ? 0 : 0);
			break;
	};
}
