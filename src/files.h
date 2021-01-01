#pragma once
#include <fstream>
#include <vector>
#include <string>
#ifndef FILES_H
#define FILES_H

#define map_cga_path (char*)"./img/castle/map.bmp"

//CGA
#define water_cga_path (char*)"./img/tiles_normal.bmp"
#define town_cga_path (char*)"./img/town_normal.bmp"
#define space_cga_path (char*)"./img/space_normal.bmp"
#define fight_cga_path (char*)"./img/fight_normal.bmp"
#define castle_cga_path (char*)"./img/castle/castle_cga.bmp"

//EGA
#define water_ega_path (char*)"./img/tiles_ega.bmp"
#define town_ega_path (char*)"./img/town_ega.bmp"
#define space_ega_path (char*)"./img/space_ega.bmp"
#define fight_ega_path (char*)"./img/fight_ega.bmp"
#define castle_ega_path (char*)"./img/castle/castle_ega.bmp"

//T1K
#define water_tik_path (char*)"./img/tiles_t1k.bmp"
#define town_tik_path (char*)"./img/town_t1k.bmp"
#define space_tik_path (char*)"./img/space_t1k.bmp"
#define fight_tik_path (char*)"./img/fight_t1k.bmp"
#define castle_tik_path (char*)"./img/castle/castle_t1k.bmp"

//FILES PREFIX 
#define cas_path_prefix (char*)"./img/Town Castle/town_cas_cga_"
#define config_ini (char*)"./ud.ini"

std::vector<unsigned char> readfile(const char*, int*);

void ini_write (std::string fil, const char *key, const char *);
std::string read_ini (std::string, const char*);
#endif
