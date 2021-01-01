#include "./map_editor.h"
#include "./map_tiles.h"
#include <vector>
#include "../files.h"
#include "../img/convert_ultima_into_xpm.h"
#include "./change_tile.h"
#include "./town_tiles.h"

std::string path;
int ypos = 0, current_tile = 0, town_inc = 0;
map_editor_display::map_editor_display(wxFrame* parent) : wxPanel(parent, wxID_ANY){}

wxChoice *map_type;

void set_map_tile_id (int t, wxBitmap *bitmap) {
	switch (t) {
		case 0:
			bitmap->LoadFile(get_cas(128).c_str(), wxBITMAP_TYPE_BMP);
			break;
		case 1:
			bitmap->LoadFile(get_cas(130).c_str(), wxBITMAP_TYPE_BMP);
			break;
		case 2:
			bitmap->LoadFile(get_cas(132).c_str(), wxBITMAP_TYPE_BMP);
			break;
		case 3:
			bitmap->LoadFile(get_cas(134).c_str(), wxBITMAP_TYPE_BMP);
			break;
		case 4:
			bitmap->LoadFile(get_cas(136).c_str(), wxBITMAP_TYPE_BMP);
			break;
		case 5:
			bitmap->LoadFile(get_cas(138).c_str(), wxBITMAP_TYPE_BMP);
			break;
		case 6:
			bitmap->LoadFile(get_cas(140).c_str(), wxBITMAP_TYPE_BMP);
			break;
		case 7:
			bitmap->LoadFile(get_cas(142).c_str(), wxBITMAP_TYPE_BMP);
			break;
	}
}

void get_map_tile_id (int t1, int t2, wxBitmap *one, wxBitmap *two) {
	set_map_tile_id(t1, one);
	set_map_tile_id(t2, two);
}

void map_editor_display::draw_editor (wxPaintEvent & evt) {
	std::vector<unsigned char> bin_buffer;
	int bin_size = 0, w = 0;
	dc = new wxPaintDC(this);
	SetClientSize(1000, 460);
	wxBitmap bitmap, tile_two;
	if (path.length() > 1) {
		if (map_type->GetSelection() == 0) {
			dc->SetUserScale(3.17, 3.17);
			bin_buffer = readfile((path + "/TCD.BIN").c_str(), &bin_size);
			w = 38;
			bitmap.LoadFile(get_cas(2).c_str(), wxBITMAP_TYPE_BMP);
			for (int i = 0; i < 38; i++) {
				for (int nx = 0; nx < 18; nx++) {
					switch ((int)bin_buffer.at(nx + ((i + ypos) * 18))) {
						case 0:
							bitmap.LoadFile(get_cas(0).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 1:
							bitmap.LoadFile(get_cas(2).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 2:
							bitmap.LoadFile(get_cas(4).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 3:
							bitmap.LoadFile(get_cas(10).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 4:
							bitmap.LoadFile(get_cas(12).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 5:
							bitmap.LoadFile(get_cas(6).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 6:
							bitmap.LoadFile(get_cas(8).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 7:
							bitmap.LoadFile(get_cas(16).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 8:
							bitmap.LoadFile(get_cas(14).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 9:
							bitmap.LoadFile(get_cas(18).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 10:
							bitmap.LoadFile(get_cas(20).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 11:
							bitmap.LoadFile(get_cas(22).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 12:
							bitmap.LoadFile(get_cas(24).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 13:
							bitmap.LoadFile(get_cas(26).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 14:
							bitmap.LoadFile(get_cas(28).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 15:
							bitmap.LoadFile(get_cas(32).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 16:
							bitmap.LoadFile(get_cas(30).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 17:
							bitmap.LoadFile(get_cas(34).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 18:
							bitmap.LoadFile(get_cas(36).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 19:
							bitmap.LoadFile(get_cas(38).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 20:
							bitmap.LoadFile(get_cas(40).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 21:
							bitmap.LoadFile(get_cas(42).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 22:
							bitmap.LoadFile(get_cas(44).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 23:
							bitmap.LoadFile(get_cas(46).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 24:
							bitmap.LoadFile(get_cas(48).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 25:
							bitmap.LoadFile(get_cas(50).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 26:
							bitmap.LoadFile(get_cas(52).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 27:
							bitmap.LoadFile(get_cas(54).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 28:
							bitmap.LoadFile(get_cas(56).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 29:
							bitmap.LoadFile(get_cas(58).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 30:
							bitmap.LoadFile(get_cas(60).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 31:
							bitmap.LoadFile(get_cas(62).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 32:
							bitmap.LoadFile(get_cas(64).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 33:
							bitmap.LoadFile(get_cas(66).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 34:
							bitmap.LoadFile(get_cas(68).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 35:
							bitmap.LoadFile(get_cas(70).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 36:
							bitmap.LoadFile(get_cas(72).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 37:
							bitmap.LoadFile(get_cas(74).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 38:
							bitmap.LoadFile(get_cas(76).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 39:
							bitmap.LoadFile(get_cas(78).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 40:
							bitmap.LoadFile(get_cas(80).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 41:
							bitmap.LoadFile(get_cas(82).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 42:
							bitmap.LoadFile(get_cas(84).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 43:
							bitmap.LoadFile(get_cas(86).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 44:
							bitmap.LoadFile(get_cas(88).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 45:
							bitmap.LoadFile(get_cas(90).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 46:
							bitmap.LoadFile(get_cas(92).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 47:
							bitmap.LoadFile(get_cas(94).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 48:
							bitmap.LoadFile(get_cas(96).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 49:
							bitmap.LoadFile(get_cas(98).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 50:
							bitmap.LoadFile(get_cas(100).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 51:
							bitmap.LoadFile(get_cas(102).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 52:
							bitmap.LoadFile(get_cas(104).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 53:
							bitmap.LoadFile(get_cas(106).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 54:
							bitmap.LoadFile(get_cas(108).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 55:
							bitmap.LoadFile(get_cas(110).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 56:
							bitmap.LoadFile(get_cas(112).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 57:
							bitmap.LoadFile(get_cas(114).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 58:
							bitmap.LoadFile(get_cas(116).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 59:
							bitmap.LoadFile(get_cas(118).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 60:
							bitmap.LoadFile(get_cas(122).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 61:
							bitmap.LoadFile(get_cas(120).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 62:
							bitmap.LoadFile(get_cas(124).c_str(), wxBITMAP_TYPE_BMP);
							break;
						case 63:
							bitmap.LoadFile(get_cas(126).c_str(), wxBITMAP_TYPE_BMP);
							break;
					}
					dc->DrawBitmap(bitmap, (i * 8), (nx * 8), false);
				}
			}
		} else {
			dc->SetUserScale(-10, 10);
			bitmap.LoadFile(map_cga_path, wxBITMAP_TYPE_BMP);
			dc->DrawBitmap(bitmap, -190 - xp, 0 + yp, false);
		}
	}
}

void map_editor_display::mouse_wheel (wxMouseEvent & evt) {
	if (evt.GetWheelRotation() < 0) {
		if (ypos < 342) {
			ypos += 38;
			town_inc += 1;
		}
	} else {
		if (ypos > 0) {
			ypos -= 38;
			town_inc -= 1;
		}
	}
	this->Refresh();
}

void map_editor_display::mouse_move_on (wxMouseEvent & evt) {
	if (map_type->GetCurrentSelection() == 1) {
		move_on_map = true;
		wxSetCursor(wxCursor(wxCURSOR_CROSS));
	} else {
		move_on_map = false;
		wxSetCursor(wxCursor(wxCURSOR_ARROW));
	}
}
void map_editor_display::mouse_move_off (wxMouseEvent & evt) {
	move_on_map = false;
	wxSetCursor(wxCursor(wxCURSOR_ARROW));
}

void map_editor_display::mouse_move (wxMouseEvent & evt) {
	if (map_type->GetCurrentSelection() == 1) {
		if (move_on_map) {
			if (evt.GetPosition().x > 700)
				xp -= 1;
			if (evt.GetPosition().x < 300)
				xp += 1;

			if (evt.GetPosition().y > 300)
				yp -= 1;
			if (evt.GetPosition().y < 100)
				yp += 1;

			this->Refresh();
		}
	}
}

BEGIN_EVENT_TABLE(map_editor_display, wxPanel)
	EVT_PAINT(map_editor_display::draw_editor)
	EVT_MOUSEWHEEL(map_editor_display::mouse_wheel)
	EVT_MIDDLE_DOWN(map_editor_display::mouse_move_on)
	EVT_MIDDLE_UP(map_editor_display::mouse_move_off)
	EVT_MOTION(map_editor_display::mouse_move)
	EVT_RIGHT_DOWN(map_editor_display::change_tile)
	EVT_LEFT_DOWN(map_editor_display::change_selecyted_tile)
END_EVENT_TABLE()

void map_editor_display::change_tile (wxMouseEvent& event) {
	if (map_type->GetCurrentSelection() == 1)
		new tile_map_picker_window(&current_tile);
	if (map_type->GetCurrentSelection() == 0)
		tile_town_picker_window(&current_tile);
}

void map_editor_display::change_selecyted_tile (wxMouseEvent& evt) {
	if (map_type->GetCurrentSelection() == 1) {
		if (
			(evt.GetLogicalPosition(*this->dc).x + 22 + xp) <= 0
				&&
			(evt.GetLogicalPosition(*this->dc).x + 22 + xp) >= -168
				&&
			(evt.GetLogicalPosition(*this->dc).y - yp) >= 0
				&&
			(evt.GetLogicalPosition(*this->dc).y - yp) <= 156
		) {
			int
			x = ((evt.GetLogicalPosition(*this->dc).x + 23 + xp) * -1),
			y = (evt.GetLogicalPosition(*this->dc).y - yp - 1), size, pixel(0);
			std::ifstream map((path + "/MAP.BIN").c_str());
			std::string data((std::istreambuf_iterator<char>(map)),std::istreambuf_iterator<char>());
			int map_data[26208];
			for (int i = 0; i < 13104; i ++) {
				map_data[pixel] = (data[i] & 0xF0) >> 4;
				map_data[pixel + 1] = (data[i] & 0x0F);
				pixel += 2;
			}
			map_data[x + (y * 168)] = current_tile;
			pixel = 0;
			for (int i = 0; i < 26208; i += 2) {
				data[pixel] = ((map_data[i] << 4) + map_data[i + 1]);
				pixel++;
			}
			map.close();
			std::ofstream maper((path + "/MAP.BIN").c_str());
			maper.write(data.c_str(), 13104);
			map_xpm((path + "/MAP.BIN").c_str());
			maper.close();
			this->Refresh();
		}
	} else if (map_type->GetCurrentSelection() == 0) {
		std::cout << "TCD\n";
		int x = evt.GetLogicalPosition(*this->dc).x / 8,
		y = evt.GetLogicalPosition(*this->dc).y / 8, size;
		std::vector<unsigned char> town_bin = readfile((path + "/TCD.BIN").c_str(), &size);
		town_bin[y + (x * 18) + (town_inc * 684)] = current_tile + 1;
		std::ofstream map((path + "/TCD.BIN").c_str(), std::ios::out|std::ios::binary);
		copy(town_bin.cbegin(), town_bin.cend(), std::ostreambuf_iterator<char>(map));
		this->Refresh();
		
	}
}

void map_editors::change_map (wxCommandEvent& event) {
	this->Refresh();
}

map_editors::map_editors (std::string ultimapath) : wxFrame(NULL, wxID_ANY, "Ultima 1 Map editor") {
	path = ultimapath;
	SetClientSize(1200, 480);
	drawPanel = new map_editor_display(this);
	wxString *map = new wxString[2];
	map[0] = "Towns & Castle";
	map[1] = "Overworld";
	map_type = new wxChoice(this, select_map_type, wxPoint(1010, 5), wxSize(180, 30), 2, map);
	map_type->SetSelection(0);
	Bind(wxEVT_CHOICE, &map_editors::change_map, this, select_map_type);
	Show();
}
