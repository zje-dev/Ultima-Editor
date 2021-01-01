#include "../img/icon.xpm"

#include "../graphic/tiles.h"

#include <string>
#include <vector>
#include "./start_window.h"
#include "./palette.h"
#include "../files.h"
#include "../cga/cga.h"
#include "../cga/select_cga.h"
#include "../ega/select_ega.h"
#include "../t1k/Select_Tandy.h"
#include "../img/convert_ultima_into_xpm.cpp"
#include "../legal.h"
#include "../map/map_editor.h"
#include "../color/color.h"

#include <iostream>

#define version "1"

std::string ultima_path;
std::vector<unsigned char> buffer;
wxSpinCtrl *Tile_tile_wid, *mond_tile_wid, *town_tile_wid, *space_tile_wid, *fight_tile_wid;
wxChoice *Read_Tile_As, *Select_Palette;
int bin_size = 0;

//control
bool fullscreen_castle = false;

void frame::legal_stuff_display (wxCommandEvent& event) {
	wxMessageBox(legal_stuff);
}

void frame::run_ultima (wxCommandEvent& event) {
	std::string command = read_ini(config_ini, "UltimaCommand");
	if (command.length() > 2) {
		system(command.c_str());
	} else {
		wxMessageDialog *dial = new wxMessageDialog(NULL, 
     	wxT("Execute command not configured"), wxT("Error"), wxOK | wxICON_ERROR);
		dial->ShowModal();
	}
}

frame::frame () : wxFrame(NULL, wxID_ANY, "Ultima 1 Editor") {
	SetClientSize(1200, 580);
	wxString *Tiles_Formats = new wxString[5];
	Tiles_Formats[0] = "TILES";
	Tiles_Formats[1] = "MOND";
	Tiles_Formats[2] = "SPACE";
	Tiles_Formats[3] = "FIGHT";
	Tiles_Formats[4] = "TOWN";
	wxString *Palettes = new wxString[3];
	Palettes[0] = "CGA";
	Palettes[1] = "EGA";
	Palettes[2] = "T1K";

	wxMenu *menu(new wxMenu), *editors_selection(new wxMenu), *help_and_info(new wxMenu), *run_menu(new wxMenu);
	menu->Append(menu_load_button, "Open","Select Ultima 1 (DOS) folder");
	menu->AppendSeparator();
	menu->Append(wxID_EXIT);
	editors_selection->Append(select_tile_editor, "Tile editor", "Open the tile editor");
	editors_selection->Append(select_map_editor, "Map editor", "Open the map editor");
	editors_selection->Append(select_castle_editor, "Castle editor", "Open the castle editor");
	help_and_info->Append(legal, "Legal warning", "Legal warning");
	help_and_info->AppendSeparator();
	help_and_info->Append(help, "Help", "...");
	run_menu->Append(run_ultima_button, "Run" "");
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menu, "&File");
	menuBar->Append(editors_selection, "Editor");
	menuBar->Append(run_menu, "Run");
	menuBar->Append(help_and_info, "Help");
	SetMenuBar(menuBar);
	CreateStatusBar();
	//UI
	wxButton *Open_Folder = new wxButton(this, load_button, _T("Open"), wxPoint(1010, 0), wxSize(180, 20), 0),
	*Edit_Castle = new wxButton(this, edit_castle, _T("Edit castle"), wxPoint(1010, 30), wxSize(180, 20), 0),
	*Edit_Tiles_b = new wxButton(this, edit_tiles, _T("Edit tiles"), wxPoint(1010, 60), wxSize(180, 20), 0),
	*map_editor = new wxButton(this, button_map_editor, _T("Map editor"), wxPoint(1010, 492), wxSize(180, 40), 0);
	SetStatusText(((std::string)"Ultima Editor v" + version));
	new wxStaticText(this, wxID_ANY, "Tiles type", wxPoint(1010, 120));
	Read_Tile_As = new wxChoice(this, tile_format, wxPoint(1010, 140), wxSize(180, 25), 5, Tiles_Formats);
	new wxStaticText(this, wxID_ANY, "Palette", wxPoint(1010, 170));
	Select_Palette = new wxChoice(this, palette_selector, wxPoint(1010, 190), wxSize(180, 25), 3, Palettes);
	Read_Tile_As->SetSelection(0);
	Select_Palette->SetSelection(0);
	new wxStaticText(this, wxID_ANY, "Select tile tiles", wxPoint(1010, 230));
	Tile_tile_wid = new wxSpinCtrl(this, tile_tile, "Tile tile", wxPoint(1010, 250), wxSize(180, 20), wxSP_ARROW_KEYS, 0, 51, 0);
	new wxStaticText(this, wxID_ANY, "Select mond tiles", wxPoint(1010, 280));
	mond_tile_wid = new wxSpinCtrl(this, mond_tile, "Mond tile", wxPoint(1010, 300), wxSize(180, 20), wxSP_ARROW_KEYS, 0, 18, 0);
	new wxStaticText(this, wxID_ANY, "Select town tile", wxPoint(1010, 330));
	town_tile_wid = new wxSpinCtrl(this, tile_town, "town tile", wxPoint(1010, 350), wxSize(180, 20), wxSP_ARROW_KEYS, 0, 50, 0);
	new wxStaticText(this, wxID_ANY, "Select space tile", wxPoint(1010, 380));
	space_tile_wid = new wxSpinCtrl(this, space_tile, "space tile", wxPoint(1010, 400), wxSize(180, 20), wxSP_ARROW_KEYS, 0, 47, 0);
	new wxStaticText(this, wxID_ANY, "Select fight tile", wxPoint(1010, 430));
	fight_tile_wid = new wxSpinCtrl(this, fight_tile, "fight tile", wxPoint(1010, 450), wxSize(180, 20), wxSP_ARROW_KEYS, 0, 27, 0);
	//canvas
	drawPanel = new draw_area(this);
	//Bind
	Bind(wxEVT_MENU, &frame::exit, this, wxID_EXIT);
	Bind(wxEVT_MENU, &frame::select_ultima_folder, this, menu_load_button);
	Bind(wxEVT_MENU, &frame::legal_stuff_display, this, legal);
	Bind(wxEVT_MENU, &frame::tile_editor, this, select_tile_editor);
	Bind(wxEVT_MENU, &frame::tile_castle, this, select_castle_editor);
	Bind(wxEVT_MENU, &frame::tile_map, this, select_map_editor);
	Bind(wxEVT_MENU, &frame::run_ultima, this, run_ultima_button);
	Bind(wxEVT_BUTTON, &frame::select_ultima_folder, this, load_button);
	Bind(wxEVT_BUTTON, &frame::tile_editor, this, edit_tiles);
	Bind(wxEVT_BUTTON, &frame::tile_castle, this, edit_castle);
	Bind(wxEVT_BUTTON, &frame::tile_map, this, button_map_editor);
	Bind(wxEVT_SPINCTRL, &frame::change_tile, this, tile_tile);
	Bind(wxEVT_SPINCTRL, &frame::change_tile, this, mond_tile);
	Bind(wxEVT_SPINCTRL, &frame::change_tile, this, space_tile);
	Bind(wxEVT_SPINCTRL, &frame::change_tile, this, fight_tile);
	Bind(wxEVT_SPINCTRL, &frame::change_tile, this, tile_town);
	Bind(wxEVT_CHOICE, &frame::change_tile, this, palette_selector);
	Bind(wxEVT_CHOICE, &frame::change_tile, this, tile_format);
	wxAcceleratorEntry entries[1];
	entries[0].Set(wxACCEL_NORMAL, WXK_F5, run_ultima_button);
	wxAcceleratorTable accel(1, entries);
	this->SetAcceleratorTable(accel);
	Show();
}

void frame::change_tile (wxCommandEvent& event) {
	castle_xpm(Select_Palette->GetSelection(), ultima_path);
	switch (Select_Palette->GetSelection()) {
		case 0:
			if (space_tile_wid->GetValue() > 47)
				space_tile_wid->SetValue(47);
			if (fight_tile_wid->GetValue() > 27)
				fight_tile_wid->SetValue(27);
			break;
		case 1:
			if (space_tile_wid->GetValue() > 95)
				space_tile_wid->SetValue(95);
			if (fight_tile_wid->GetValue() > 55)
				fight_tile_wid->SetValue(55);
		case 2:
			if (space_tile_wid->GetValue() > 96)
				space_tile_wid->SetValue(96);
			if (fight_tile_wid->GetValue() > 55)
				fight_tile_wid->SetValue(55);
			break;
	}
	this->Refresh();
}

void frame::tile_map (wxCommandEvent& event) {
	map_editors *f = new map_editors(ultima_path);
	f->Show(true);
	f->Maximize(false);
}

BEGIN_EVENT_TABLE(draw_area, wxPanel)
	EVT_PAINT(draw_area::draw_editor)
	EVT_LEFT_DOWN(draw_area::select_tile)
	EVT_RIGHT_DOWN(draw_area::select_color)
END_EVENT_TABLE()

void frame::exit (wxCommandEvent& event) {
	Close(true);
}

void frame::select_ultima_folder (wxCommandEvent& event) {
	wxDirDialog sarch_folder (this, "Select Ultima 1 (DOS) folder", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
	if (sarch_folder.ShowModal() == wxID_CANCEL)
		return;
	ultima_path = sarch_folder.GetPath() + "/";
	castle_xpm(Read_Tile_As->GetSelection(), ultima_path);
	map_xpm((ultima_path + "/MAP.BIN").c_str());
	std::string command = read_ini(config_ini, "UltimaCommand");
	if (command.length() < 2) {
		ini_write(config_ini, "UltimaCommand", ("cd \"" + ultima_path + "\"; wine ultima.exe").c_str()); //i don't know to do this on windows
	}
	this->Refresh();
}

void frame::tile_editor (wxCommandEvent& event) {
	fullscreen_castle = false;
	this->Refresh();
}

void frame::tile_castle (wxCommandEvent& event) {
	fullscreen_castle = true;
	this->Refresh();
}

void draw_area::select_tile (wxMouseEvent & evt) {
	if (!fullscreen_castle) {
		if (ultima_path.length() > 1) {
			if (Read_Tile_As->GetSelection() == 0) {
				if (
					(evt.GetLogicalPosition(*this->dc).x) >= -50
					&&
					(evt.GetLogicalPosition(*this->dc).y) <= 31
					&&
					(evt.GetLogicalPosition(*this->dc).x) <= -35
					&&
					(evt.GetLogicalPosition(*this->dc).y) >= 16
				) {
					switch (Select_Palette->GetSelection()) {
						case 0: {
							int x = (evt.GetLogicalPosition(*this->dc).x + 35) * -1,
							y = (evt.GetLogicalPosition(*this->dc).y - 16);
							std::vector<unsigned char> bin_buffer = readfile((ultima_path + "CGATILES.BIN").c_str(), &bin_size);
							change_pixel(x, y, &bin_buffer, (ultima_path + "CGATILES.BIN").c_str(), cga_current_color, Tile_tile_wid->GetValue(), 16, 256, 64);
							}
							break;
						case 1: {
							int x = (evt.GetLogicalPosition(*this->dc).x + 35) * -1,
							y = (evt.GetLogicalPosition(*this->dc).y - 16);
							std::vector<unsigned char> bin_buffer = readfile((ultima_path + "EGATILES.BIN").c_str(), &bin_size);
							change_ega_pixel(x, y, &bin_buffer, (ultima_path + "EGATILES.BIN").c_str(), cga_current_color, Tile_tile_wid->GetValue(), 256, 128, 16);
							}
							break;
						case 2: {
							int xt = (evt.GetLogicalPosition(*this->dc).x + 35) * -1,
							yt = (evt.GetLogicalPosition(*this->dc).y - 16);
							std::vector<unsigned char> bin_buffer = readfile((ultima_path + "T1KTILES.BIN").c_str(), &bin_size);
							change_tandy_pixel(xt, yt, &bin_buffer, (ultima_path + "T1KTILES.BIN").c_str(), cga_current_color, Tile_tile_wid->GetValue(), 256, 128, 16);
							}
							break;
					}
				}
			} else if (Read_Tile_As->GetSelection() == 1) {
				if (
					(evt.GetLogicalPosition(*this->dc).x) >= -50
					&&
					(evt.GetLogicalPosition(*this->dc).y) <= 31
					&&
					(evt.GetLogicalPosition(*this->dc).x) <= -35
					&&
					(evt.GetLogicalPosition(*this->dc).y) >= 16
				) {
					switch (Select_Palette->GetSelection()) {
						case 0: {
							int x = (evt.GetLogicalPosition(*this->dc).x + 35) * -1,
							y = (evt.GetLogicalPosition(*this->dc).y - 16);
							std::vector<unsigned char> bin_buffer = readfile((ultima_path + "CGAMOND.BIN").c_str(), &bin_size);
							change_pixel(x, y, &bin_buffer, (ultima_path + "CGAMOND.BIN").c_str(), cga_current_color, mond_tile_wid->GetValue(), 16, 256, 64);
							}
							break;
						case 1: {
							int x = (evt.GetLogicalPosition(*this->dc).x + 35) * -1,
							y = (evt.GetLogicalPosition(*this->dc).y - 16);
							std::vector<unsigned char> bin_buffer = readfile((ultima_path + "EGAMOND.BIN").c_str(), &bin_size);
							change_ega_pixel(x, y, &bin_buffer, (ultima_path + "EGAMOND.BIN").c_str(), cga_current_color, mond_tile_wid->GetValue(), 256, 128, 16);
							}
							break;
						case 2: {
							int xt = (evt.GetLogicalPosition(*this->dc).x + 35) * -1,
							yt = (evt.GetLogicalPosition(*this->dc).y - 16);
							std::vector<unsigned char> bin_buffer = readfile((ultima_path + "T1KMOND.BIN").c_str(), &bin_size);
							change_tandy_pixel(xt, yt, &bin_buffer, (ultima_path + "T1KMOND.BIN").c_str(), cga_current_color, mond_tile_wid->GetValue(), 256, 128, 16);
							}
							break;
					}
				}
			} else if (Read_Tile_As->GetSelection() == 2) {
				if (
					(evt.GetLogicalPosition(*this->dc).x) >= -70
					&&
					(evt.GetLogicalPosition(*this->dc).y) <= 34
					&&
					(evt.GetLogicalPosition(*this->dc).x) <= -38
					&&
					(evt.GetLogicalPosition(*this->dc).y) >= 16
				) {
					switch (Select_Palette->GetSelection()) {
						case 0: {
							int x = (evt.GetLogicalPosition(*this->dc).x + 38) * -1,
							y = (evt.GetLogicalPosition(*this->dc).y - 16);
							std::vector<unsigned char> bin_buffer = readfile((ultima_path + "CGASPACE.BIN").c_str(), &bin_size);
							change_pixel(x, y, &bin_buffer, (ultima_path + "CGASPACE.BIN").c_str(), cga_current_color, space_tile_wid->GetValue(), 32, 612, 153);
							}
							break;
						case 1: {
							int x = (evt.GetLogicalPosition(*this->dc).x + 38) * -1,
							y = (evt.GetLogicalPosition(*this->dc).y - 16);
							std::vector<unsigned char> bin_buffer = readfile((ultima_path + "EGASPACE.BIN").c_str(), &bin_size);
							change_ega_mono(x, y, &bin_buffer, (ultima_path + "EGASPACE.BIN").c_str(), cga_current_color, space_tile_wid->GetValue(), 608, 76, 32);
							}
							break;
						case 2: {
							int x = (evt.GetLogicalPosition(*this->dc).x + 38) * -1,
							y = (evt.GetLogicalPosition(*this->dc).y - 16);
							std::vector<unsigned char> bin_buffer = readfile((ultima_path + "T1KSPACE.BIN").c_str(), &bin_size);
							change_tandy_pixel(x, y, &bin_buffer, (ultima_path + "T1KSPACE.BIN").c_str(), cga_current_color, space_tile_wid->GetValue(), 608, 304, 32);
							}
							break;

					}
				}
			} else if (Read_Tile_As->GetSelection() == 3) {
				if (
					(evt.GetLogicalPosition(*this->dc).x) >= -50
					&&
					(evt.GetLogicalPosition(*this->dc).y) <= 34
					&&
					(evt.GetLogicalPosition(*this->dc).x) <= -26
					&&
					(evt.GetLogicalPosition(*this->dc).y) >= 16
				) {
					switch (Select_Palette->GetSelection()) {
						case 0:{
							int x = (evt.GetLogicalPosition(*this->dc).x + 26) * -1,
							y = (evt.GetLogicalPosition(*this->dc).y - 16);
							std::vector<unsigned char> bin_buffer = readfile((ultima_path + "CGAFIGHT.BIN").c_str(), &bin_size);
							change_pixel(x, y, &bin_buffer, (ultima_path + "CGAFIGHT.BIN").c_str(), cga_current_color, fight_tile_wid->GetValue(), 24, 456, 114);
							}
							break;
						case 1:{
							int x = (evt.GetLogicalPosition(*this->dc).x + 26) * -1,
							y = (evt.GetLogicalPosition(*this->dc).y - 16);
							std::vector<unsigned char> bin_buffer = readfile((ultima_path + "EGAFIGHT.BIN").c_str(), &bin_size);
							change_ega_mono(x, y, &bin_buffer, (ultima_path + "EGAFIGHT.BIN").c_str(), cga_current_color, fight_tile_wid->GetValue(), 24, 57, 24);
							}
							break;
						case 2:{
							int x = (evt.GetLogicalPosition(*this->dc).x + 26) * -1,
							y = (evt.GetLogicalPosition(*this->dc).y - 16);
							std::vector<unsigned char> bin_buffer = readfile((ultima_path + "T1KFIGHT.BIN").c_str(), &bin_size);
							change_tandy_pixel(x, y, &bin_buffer, (ultima_path + "T1KFIGHT.BIN").c_str(), cga_current_color, fight_tile_wid->GetValue(), 456, 228, 24);
							}
							break;
					}
				}
			} else if (Read_Tile_As->GetSelection() == 4) {
				if (
					(evt.GetLogicalPosition(*this->dc).x) >= -30
					&&
					(evt.GetLogicalPosition(*this->dc).y) <= 96
					&&
					(evt.GetLogicalPosition(*this->dc).x) <= -22
					&&
					(evt.GetLogicalPosition(*this->dc).y) >= 15
				) {
					switch (Select_Palette->GetSelection()) {
						case 0: {
							int x = ((evt.GetLogicalPosition(*this->dc).x + 22) * -1),
							y = (evt.GetLogicalPosition(*this->dc).y - 15);
							std::vector<unsigned char> bin_buffer = readfile((ultima_path + "CGATOWN.BIN").c_str(), &bin_size);
							change_pixel(x, y, &bin_buffer, (ultima_path + "CGATOWN.BIN").c_str(), cga_current_color, town_tile_wid->GetValue(), 8, 64, 16);
							}
							break;
						case 1: {
							int x = (evt.GetLogicalPosition(*this->dc).x + 22) * -1,
							y = (evt.GetLogicalPosition(*this->dc).y - 15);
							std::vector<unsigned char> bin_buffer = readfile((ultima_path + "EGATOWN.BIN").c_str(), &bin_size);
							change_ega_town(x, y, &bin_buffer, (ultima_path + "EGATOWN.BIN").c_str(), cga_current_color, mond_tile_wid->GetValue(), 256, 128, 16);
							}
							break;
						case 2: {
							int x = ((evt.GetLogicalPosition(*this->dc).x + 22) * -1),
							y = (evt.GetLogicalPosition(*this->dc).y - 15);
							std::vector<unsigned char> bin_buffer = readfile((ultima_path + "T1KTOWN.BIN").c_str(), &bin_size);
							change_tandy_pixel(x, y, &bin_buffer, (ultima_path + "T1KTOWN.BIN").c_str(), cga_current_color, town_tile_wid->GetValue(), 64, 32, 8);
							}
							break;
					}
				}
			}
		}
	} else {
		if (
			(evt.GetLogicalPosition(*this->dc).x) >= -330
			&&
			(evt.GetLogicalPosition(*this->dc).y) <= 202
			&&
			(evt.GetLogicalPosition(*this->dc).x) <= -11
			&&
			(evt.GetLogicalPosition(*this->dc).y) >= 3
		) {
			int x = ((evt.GetLogicalPosition(*this->dc).x + 11) * -1),
			y = evt.GetLogicalPosition(*this->dc).y - 3;
			if (Select_Palette->GetSelection() == 0) {
				int e = 0, cri = 80;
				int color[32000], roloc[32000];
				bool cr = true;
				std::vector<unsigned char> tmp_buf = readfile((ultima_path + "CASTLE.4").c_str(), &bin_size);
				//CGA
				for (int i = 0; i < 8000; i++) {
					color[e] = byte_to_color((tmp_buf[i] & 0xF0) >> 4, false);
					color[e + 1] = byte_to_color((tmp_buf[i] & 0xF0) >> 4, true);
					color[e + 2] = byte_to_color((tmp_buf[i] & 0x0F), false);
					color[e + 3] = byte_to_color((tmp_buf[i] & 0x0F), true);
					roloc[e] = byte_to_color((tmp_buf[i + 8192] & 0xF0) >> 4, false);
					roloc[e + 1] = byte_to_color((tmp_buf[i + 8192] & 0xF0) >> 4, true);
					roloc[e + 2] = byte_to_color((tmp_buf[i + 8192] & 0x0F), false);
					roloc[e + 3] = byte_to_color((tmp_buf[i + 8192] & 0x0F), true);
					e += 4;
				}
				if (y % 2 == 0) {
					color[x + (y * 160)] = cga_current_color;
				} else {
					roloc[x + ((y + 1) * 160)] = cga_current_color;
				}
				e = 0;
				cri = 320;
				cr = true;
				int byte_one = 0, byte_two = 0;
				for (int i = 0; i < 32000; i += 4) {
					byte_one = color_to_byte(color[i], color[i + 1]);
					byte_two = color_to_byte(color[i + 2], color[i + 3]);
					tmp_buf[e] = ((byte_one << 4) + byte_two);
					e ++;
				}
				e = 0;
				for (int i = 0; i < 32000; i += 4) {
					byte_one = color_to_byte(roloc[i], roloc[i + 1]);
					byte_two = color_to_byte(roloc[i + 2], roloc[i + 3]);
					tmp_buf[e + 8192] = ((byte_one << 4) + byte_two);
					e ++;
				}
				std::ofstream file((ultima_path + "CASTLE.4").c_str(), std::ios::out|std::ios::binary);
				copy(tmp_buf.cbegin(), tmp_buf.cend(), std::ostream_iterator<char>(file));
				castle_xpm(0, ultima_path);
			} else if (Select_Palette->GetSelection() == 1) {
				int color[64000], e = 0;
				std::vector<unsigned char> tmp_buf = readfile((ultima_path + "CASTLE.16").c_str(), &bin_size);
				for (int i = 0; i < 32000; i++) {
					color[e] = (tmp_buf[i] & 0xF0) >> 4;
					color[e + 1] = tmp_buf[i] & 0x0F;
					e += 2;
				}
				color[x + (y * 320)] = cga_current_color;
				e = 0;
				for (int i = 0; i < 64000; i += 2) {
					tmp_buf[e] = (color[i] << 4) + color[i + 1];
					e++;
				}
				std::ofstream file((ultima_path + "CASTLE.16").c_str(), std::ios::out|std::ios::binary);
				copy(tmp_buf.cbegin(), tmp_buf.cend(), std::ostream_iterator<char>(file));
				castle_xpm(1, ultima_path);
			} else if (Select_Palette->GetSelection() == 2) {
				int color[64000], e = 0;
				std::vector<unsigned char> tmp_buf = readfile((ultima_path + "CASTLE.16").c_str(), &bin_size);
				for (int i = 0; i < 32000; i++) {
					color[e] = (tmp_buf[i] & 0xF0) >> 4;
					color[e + 1] = tmp_buf[i] & 0x0F;
					e += 2;
				}
				color[x + (y * 320)] = cga_current_color;
				e = 0;
				for (int i = 0; i < 64000; i += 2) {
					tmp_buf[e] = (color[i] << 4) + color[i + 1];
					e++;
				}
				std::ofstream file((ultima_path + "CASTLE.16").c_str(), std::ios::out|std::ios::binary);
				copy(tmp_buf.cbegin(), tmp_buf.cend(), std::ostream_iterator<char>(file));
				castle_xpm(2, ultima_path);
			}
		}
	}
	this->Refresh();
	return;
}

void draw_area::select_color (wxMouseEvent & evt) {
	if (ultima_path.length() > 1) {
		new color_picker_window(Select_Palette->GetSelection(), &cga_current_color, fullscreen_castle);
	}
}

draw_area::draw_area(wxFrame* parent) : wxPanel(parent, wxID_ANY){}

void draw_area::draw_editor (wxPaintEvent & evt) {
	wxBrush *bgc = new wxBrush(wxColour(30, 30, 30), wxCROSS_HATCH);
	dc = new wxPaintDC(this);
	SetClientSize(1000, 540);
	if (!fullscreen_castle) {
		//tiles
		dc->SetUserScale(-10, 10);
		dc->SetBrush(*bgc);
		dc->DrawRectangle(0, -10, -100, 100);
		if (ultima_path.length() > 1) {
			convert_xpm(Read_Tile_As->GetSelection(), Select_Palette->GetSelection(), ultima_path, 
				Tile_tile_wid->GetValue(),
				mond_tile_wid->GetValue(),
				town_tile_wid->GetValue(),
				space_tile_wid->GetValue(),
				fight_tile_wid->GetValue(),
				fullscreen_castle,
				false
			);
			wxBitmap bitmap;
			int imagex = -40;
			switch (Read_Tile_As->GetSelection()) {
				case 0:
					switch (Select_Palette->GetSelection()) {
						case 0:
							bitmap.LoadFile(water_cga_path, wxBITMAP_TYPE_BMP);
							dc->SetUserScale(-10, 10);
							imagex = -50;
							break;
						case 1:
							bitmap.LoadFile(water_ega_path, wxBITMAP_TYPE_BMP);
							dc->SetUserScale(-10, 10);
							imagex = -50;
							break;
						case 2:
							bitmap.LoadFile(water_tik_path, wxBITMAP_TYPE_BMP);
							dc->SetUserScale(-10, 10);
							imagex = -50;
							break;
					}
					break;
				case 1:
					switch (Select_Palette->GetSelection()) {
						case 0:
							bitmap.LoadFile(water_cga_path, wxBITMAP_TYPE_BMP);
							dc->SetUserScale(-10, 10);
							imagex = -50;
							break;
						case 1:
							bitmap.LoadFile(water_ega_path, wxBITMAP_TYPE_BMP);
							dc->SetUserScale(-10, 10);
							imagex = -50;
							break;
						case 2:
							bitmap.LoadFile(water_tik_path, wxBITMAP_TYPE_BMP);
							dc->SetUserScale(-10, 10);
							imagex = -50;
							break;
					}
					break;
				case 2:
					switch (Select_Palette->GetSelection()) {
						case 0:
							bitmap.LoadFile(space_cga_path, wxBITMAP_TYPE_BMP);
							dc->SetUserScale(-10, 10);
							imagex = -70;
							space_tile_wid->SetRange(0, 47);
							break;
						case 1:
							bitmap.LoadFile(space_ega_path, wxBITMAP_TYPE_BMP);
							dc->SetUserScale(-10, 10);
							imagex = -70;
							space_tile_wid->SetRange(0, 96);
							break;
						case 2:
							bitmap.LoadFile(space_tik_path, wxBITMAP_TYPE_BMP);
							dc->SetUserScale(-10, 10);
							imagex = -70;
							space_tile_wid->SetRange(0, 24);
							break;
					}
					break;
				case 3:
					bitmap.LoadFile(fight_cga_path, wxBITMAP_TYPE_BMP);
					switch (Select_Palette->GetSelection()) {
						case 0:
							bitmap.LoadFile(fight_cga_path, wxBITMAP_TYPE_BMP);
							dc->SetUserScale(-10, 10);
							imagex = -50;
							fight_tile_wid->SetRange(0, 27);
							break;
						case 1:
							bitmap.LoadFile(fight_ega_path, wxBITMAP_TYPE_BMP);
							dc->SetUserScale(-10, 10);
							imagex = -50;
							fight_tile_wid->SetRange(0, 55);
							break;
						case 2:
							bitmap.LoadFile(fight_tik_path, wxBITMAP_TYPE_BMP);
							dc->SetUserScale(-10, 10);
							imagex = -50;
							fight_tile_wid->SetRange(0, 55);
							break;
					}
					break;
				case 4:
					bitmap.LoadFile(town_cga_path, wxBITMAP_TYPE_BMP);
					switch (Select_Palette->GetSelection()) {
						case 0:
							bitmap.LoadFile(town_cga_path, wxBITMAP_TYPE_BMP);
							dc->SetUserScale(-15, 15);
							imagex = -30;
							break;
						case 1:
							bitmap.LoadFile(town_ega_path, wxBITMAP_TYPE_BMP);
							dc->SetUserScale(-15, 15);
							imagex = -30;
							break;
						case 2:
							bitmap.LoadFile(town_tik_path, wxBITMAP_TYPE_BMP);
							dc->SetUserScale(-15, 15);
							imagex = -30;
							break;
					}
					break;
			}
			if (bitmap.IsOk()) {
				dc->DrawBitmap(bitmap, imagex, 15, false);
			} else {
				wxMessageBox(wxT("Could not load tile."));
			}
		}
	} else {
		//castle
		wxBitmap bitmap, top, mid, dow;
		switch (Select_Palette->GetSelection()) {
			case 0:
				dc->SetUserScale(-2.65, 2.6);
				dc->SetBrush(*bgc);
				dc->DrawRectangle(0, 0, -1000, 500);
				bitmap.LoadFile(castle_cga_path, wxBITMAP_TYPE_BMP);
				if (bitmap.IsOk()) {
					dc->DrawBitmap(bitmap, -330, 2, false);
				} else {
					wxMessageBox(wxT("Could not load castle."));
				}
				break;
			case 1:
				dc->SetUserScale(-2.65, 2.6);
				dc->SetBrush(*bgc);
				dc->DrawRectangle(0, 0, -1000, 500);
				bitmap.LoadFile(castle_ega_path, wxBITMAP_TYPE_BMP);
				if (bitmap.IsOk()) {
					dc->DrawBitmap(bitmap, -330, 2, false);
				} else {
					wxMessageBox(wxT("Could not load castle."));
				}
				break;
			case 2:
				dc->SetUserScale(-2.65, 2.6);
				dc->SetBrush(*bgc);
				dc->DrawRectangle(0, 0, -1000, 500);
				bitmap.LoadFile(castle_tik_path, wxBITMAP_TYPE_BMP);
				if (bitmap.IsOk()) {
					dc->DrawBitmap(bitmap, -330, 2, false);
				} else {
					wxMessageBox(wxT("Could not load castle."));
				}
				break;
		}
	}
}

bool UltimaEditor::OnInit() {
	frame *f = new frame();
	f->SetIcon(wxICON(icon));
	f->Show(true);
	f->Maximize(false);
	return true;
}
