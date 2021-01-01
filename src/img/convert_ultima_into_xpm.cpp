#include "./convert_ultima_into_xpm.h"
#include "../graphic/start_window.h"
#include "../files.h"
#include "../cga/cga_select.h"
#include "../ega/ega_select.h"
#include "../t1k/Tandy_Select.h"
#include "../map/map_pixel.h"

std::string get_cas (int index) {
	std::string cas = (std::string(cas_path_prefix) + (index < 10 ? "0" : "") + std::to_string((int)index) + ".bmp");
	return cas;
}

void convert_xpm (int tt, int pal, std::string ultima_path, int index_tiles, int index_mond, int index_town, int index_space, int index_fight, bool fsc, bool map) {
	std::vector<unsigned char> bmp_buffer, bin_buffer;
	int size, bin_size;
	if (!fsc) {
		if (pal == 0) { //When i do a BIG switch it just doesn't work
			bmp_buffer = readfile(water_cga_path, &size);
			int index = 0, width = 0, height = 0;
			char *file_path;
			switch (tt) {
				case 0:
					bin_buffer = readfile((ultima_path + "/CGATILES.BIN").c_str(), &bin_size);
					index = index_tiles;
					width = TILES_W * 4;
					height = TILES_H * 4;
					file_path = water_cga_path;
					break;
				case 1:
					bin_buffer = readfile((ultima_path + "/CGAMOND.BIN").c_str(), &bin_size);
					index = index_mond;
					width = MOND_W * 4;
					height = TILES_H * 4;
					file_path = water_cga_path;
					break;
				case 2:
					bin_buffer = readfile((ultima_path + "/CGASPACE.BIN").c_str(), &bin_size);
					bmp_buffer = readfile(space_cga_path, &size);
					index = index_space;
					width = 152;
					height = 152;
					file_path = space_cga_path;
					break;
				case 3:
					bin_buffer = readfile((ultima_path + "/CGAFIGHT.BIN").c_str(), &bin_size);
					bmp_buffer = readfile(fight_cga_path, &size);
					index = index_fight;
					width = 114;
					height = 114;
					file_path = fight_cga_path;
					break;
				case 4:
					bin_buffer = readfile((ultima_path + "/CGATOWN.BIN").c_str(), &bin_size);
					width = TOWN_W;
					index = index_town * 2;
					height = TILES_H;
					bmp_buffer = readfile(town_cga_path, &size);
					file_path = town_cga_path;
					break;
			}
			for (int i = 0; i < height; i++) {
				cga_to_hex((unsigned char)((bin_buffer.at(i + (width * index)) & 0xF0) >> 4), &bmp_buffer, (6 * i) * 2);
				cga_to_hex((unsigned char)(bin_buffer.at(i  + (width * index)) & 0x0F), &bmp_buffer, (6 * (i + 1)) + (i * 6));
			}
			
			std::ofstream water((map ? get_cas(index) : file_path), std::ios::out|std::ios::binary);
			copy(bmp_buffer.cbegin(), bmp_buffer.cend(), std::ostreambuf_iterator<char>(water));
		}
		if (pal == 1) {
			bmp_buffer = readfile(water_cga_path, &size);
			int index = 0, width = 0, height = 0;
			char *file_path;
			int ind = 0, ex = 0;
			switch (tt) {
				case 0:
					bin_buffer = readfile((ultima_path + "/EGATILES.BIN").c_str(), &bin_size);
					ind = (index_tiles * 128);
					file_path = water_ega_path;
					height = 16;
					width = 12;
					break;
				case 1:
					bin_buffer = readfile((ultima_path + "/EGAMOND.BIN").c_str(), &bin_size);
					ind = (index_mond * 128);
					file_path = water_ega_path;
					height = 16;
					width = 12;
					break;
				case 2:
					bin_buffer = readfile((ultima_path + "/EGASPACE.BIN").c_str(), &bin_size);
					bmp_buffer = readfile(space_ega_path, &size);
					ind = index_space * 76;
					height = 8;
					width = 12;
					file_path = space_ega_path;
					break;
				case 3:
					bin_buffer = readfile((ultima_path + "/EGAFIGHT.BIN").c_str(), &bin_size);
					bmp_buffer = readfile(fight_ega_path, &size);
					ind = index_fight * 57;
					height = 7;
					width = 8;
					file_path = fight_ega_path;
					break;
				case 4:
					bin_buffer = readfile((ultima_path + "/EGATOWN.BIN").c_str(), &bin_size);
					ind = index_town * 32;
					bmp_buffer = readfile(town_ega_path, &size);
					height = 8;
					width = 4;
					file_path = town_ega_path;
					break;
			}
			for (int i = 0; i < height; i++) {
				if (tt == 0 || tt == 1)
					ega_to_hex(&bmp_buffer, bin_buffer, i, &ind, &ex);
				if (tt == 4)
					ega_to_town(&bmp_buffer, bin_buffer, i, &ind, &ex);
				if (tt == 2)
					ega_to_space(&bmp_buffer, bin_buffer, i, &ind, &ex);
				if (tt == 3)
					ega_to_space(&bmp_buffer, bin_buffer, i, &ind, &ex);
			}
			std::ofstream water(file_path, std::ios::out|std::ios::binary);
			copy(bmp_buffer.cbegin(), bmp_buffer.cend(), std::ostreambuf_iterator<char>(water));
		}
		
		if (pal == 2) {
			bmp_buffer = readfile(water_tik_path, &size);
			int index = 0, width = 0, height = 0;
			char *file_path;
			int ind = 0, ex = 0;
			switch (tt) {
				case 0:
					bin_buffer = readfile((ultima_path + "/T1KTILES.BIN").c_str(), &bin_size);
					ind = (index_tiles * 128);
					width = 128;
					file_path = water_tik_path;
					break;
				case 1:
					bin_buffer = readfile((ultima_path + "/T1KMOND.BIN").c_str(), &bin_size);
					ind = (index_mond * 128);
					width = 128;
					file_path = water_tik_path;
					break;
				case 2:
					bin_buffer = readfile((ultima_path + "/T1KSPACE.BIN").c_str(), &bin_size);
					bmp_buffer = readfile(space_tik_path, &size);
					ind = index_space * 304;
					width = 304;
					file_path = space_tik_path;
					break;
				case 3:
					bin_buffer = readfile((ultima_path + "/T1KFIGHT.BIN").c_str(), &bin_size);
					bmp_buffer = readfile(fight_tik_path, &size);
					ind = index_fight * 228;
					width = 228;
					file_path = fight_tik_path;
					break;
				case 4:
					bin_buffer = readfile((ultima_path + "/T1KTOWN.BIN").c_str(), &bin_size);
					ind = (index_town * 32);
					width = 32;
					bmp_buffer = readfile(town_tik_path, &size);
					file_path = town_tik_path;
					break;
			}
			tandy_to_hex(&bmp_buffer, bin_buffer, ind, width);
			std::ofstream water(file_path, std::ios::out|std::ios::binary);
			copy(bmp_buffer.cbegin(), bmp_buffer.cend(), std::ostreambuf_iterator<char>(water));
		}
	} else {
		int l;
		castle_xpm(pal, ultima_path);
		map_xpm((ultima_path + "/MAP.BIN").c_str());
	}
}

void castle_xpm (int pal, std::string ultima_path) {
	std::vector<unsigned char> bmp_buffer, bin_buffer;
	int size = 0, bin_size = 0, pixel = 0;
	if (pal == 0) { //Switch doesn't work
		bin_buffer = readfile((ultima_path + "/CASTLE.4").c_str(), &bin_size);
		bmp_buffer = readfile(castle_cga_path, &size);
		int nex = 0, t = 80;
		for (int i = 0; i < 8000; i++) {
			int width = TILES_W * 4;
			if (i == t) {
				nex += 2;
				if (nex <= 200)
					t += 80;
			}
			cga_to_hex((unsigned char)((bin_buffer.at(i) & 0xF0) >> 4), &bmp_buffer, ((6 * i) + (i * 6)) + (nex * 480));
			cga_to_hex((unsigned char)(bin_buffer.at(i) & 0x0F), &bmp_buffer, (6 * ((i + 1)) + (i * 6)) +  (nex * 480));
			cga_to_hex((unsigned char)((bin_buffer.at(i + 8192) & 0xF0) >> 4), &bmp_buffer, ((6 * i) + (i * 6)) + ((nex + 2) * 480));
			cga_to_hex((unsigned char)(bin_buffer.at(i + 8192) & 0x0F), &bmp_buffer, (6 * ((i + 1)) + (i * 6)) +  ((nex + 2) * 480));
		}
		std::ofstream castle(castle_cga_path, std::ios::out|std::ios::binary);
		copy(bmp_buffer.cbegin(), bmp_buffer.cend(), std::ostreambuf_iterator<char>(castle));
	}
	if (pal == 1) {
		bin_buffer = readfile((ultima_path + "/CASTLE.16").c_str(), &bin_size);
		bmp_buffer = readfile(castle_ega_path, &size);
		for (int i = 0; i < 32000; i++) {
			map_ega_xpm(&bmp_buffer, (bin_buffer[i] & 0xF0) >> 4, &pixel);
			map_ega_xpm(&bmp_buffer, bin_buffer[i] & 0x0F, &pixel);
		}
		std::ofstream castle(castle_ega_path, std::ios::out|std::ios::binary);
		copy(bmp_buffer.cbegin(), bmp_buffer.cend(), std::ostreambuf_iterator<char>(castle));
	}
	if (pal == 2) {
		bin_buffer = readfile((ultima_path + "/CASTLE.16").c_str(), &bin_size);
		bmp_buffer = readfile(castle_tik_path, &size);
		for (int i = 0; i < 32000; i++) {
			map_tik_xpm(&bmp_buffer, (bin_buffer[i] & 0xF0) >> 4, &pixel);
			map_tik_xpm(&bmp_buffer, bin_buffer[i] & 0x0F, &pixel);
		}
		std::ofstream castle(castle_tik_path, std::ios::out|std::ios::binary);
		copy(bmp_buffer.cbegin(), bmp_buffer.cend(), std::ostreambuf_iterator<char>(castle));
	}
}

void map_xpm (const char* path) {
	std::vector<unsigned char> bmp_buffer;
	int size = 0, e = 0;
	std::vector<unsigned char> bin_buf;
	bmp_buffer = readfile(map_cga_path, &size);
	bin_buf = readfile(path, &size);
	
	for (int i = 0; i < 78624 ; i += 6) {
		int ind = bmp_buffer.size() - i - 673;
		switch ((bin_buf[e] & 0xF0) >> 4) {
			case 0:
				bmp_buffer.at(ind) = 0;
				bmp_buffer.at(ind - 1) = 0;
				bmp_buffer.at(ind - 2) = 255;
				break;
			case 1:
				bmp_buffer.at(ind) = 0;
				bmp_buffer.at(ind - 1) = 255;
				bmp_buffer.at(ind - 2) = 0;
				break;
			case 2:
				bmp_buffer.at(ind) = 0;
				bmp_buffer.at(ind - 1) = 125;
				bmp_buffer.at(ind - 2) = 0;
				break;
			case 3:
				bmp_buffer.at(ind) = 100;
				bmp_buffer.at(ind - 1) = 100;
				bmp_buffer.at(ind - 2) = 100;
				break;
			case 4:
				bmp_buffer.at(ind) = 255;
				bmp_buffer.at(ind - 1) = 255;
				bmp_buffer.at(ind - 2) = 255;
				break;
			case 5:
				bmp_buffer.at(ind) = 150;
				bmp_buffer.at(ind - 1) = 150;
				bmp_buffer.at(ind - 2) = 0;
				break;
			case 6:
				bmp_buffer.at(ind) = 0;
				bmp_buffer.at(ind - 1) = 0;
				bmp_buffer.at(ind - 2) = 0;
				break;
			case 7:
				bmp_buffer.at(ind) = 225;
				bmp_buffer.at(ind - 1) = 0;
				bmp_buffer.at(ind - 2) = 0;
				break;
		}
		switch (bin_buf[e] & 0x0F) {
			case 0:
				bmp_buffer.at(ind - 3) = 0;
				bmp_buffer.at(ind - 4) = 0;
				bmp_buffer.at(ind - 5) = 255;
				break;
			case 1:
				bmp_buffer.at(ind - 3) = 0;
				bmp_buffer.at(ind - 4) = 255;
				bmp_buffer.at(ind - 5) = 0;
				break;
			case 2:
				bmp_buffer.at(ind - 3) = 0;
				bmp_buffer.at(ind - 4) = 125;
				bmp_buffer.at(ind - 5) = 0;
				break;
			case 3:
				bmp_buffer.at(ind - 3) = 100;
				bmp_buffer.at(ind - 4) = 100;
				bmp_buffer.at(ind - 5) = 100;
				break;
			case 4:
				bmp_buffer.at(ind - 3) = 255;
				bmp_buffer.at(ind - 4) = 255;
				bmp_buffer.at(ind - 5) = 255;
				break;
			case 5:
				bmp_buffer.at(ind - 3) = 150;
				bmp_buffer.at(ind - 4) = 150;
				bmp_buffer.at(ind - 5) = 0;
				break;
			case 6:
				bmp_buffer.at(ind - 3) = 0;
				bmp_buffer.at(ind - 4) = 0;
				bmp_buffer.at(ind - 5) = 0;
				break;
			case 7:
				bmp_buffer.at(ind - 3) = 225;
				bmp_buffer.at(ind - 4) = 0;
				bmp_buffer.at(ind - 5) = 0;
				break;
		}
		e++;
	}
	
	std::ofstream castle(map_cga_path, std::ios::out|std::ios::binary);
	copy(bmp_buffer.cbegin(), bmp_buffer.cend(), std::ostreambuf_iterator<char>(castle));
}
