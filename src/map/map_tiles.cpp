#include "./map_tiles.h"

tile_map_picker_window::tile_map_picker_window (int *tile) : wxFrame(NULL, wxID_ANY, "Map tile picker") {
	current_tile = tile;
	wxString *map = new wxString[8];
	map[0] = "Water    0";
	map[1] = "Grass    1";
	map[2] = "Forest   2";
	map[3] = "Mountain 3";
	map[4] = "Castle   4";
	map[5] = "Signpost 5";
	map[6] = "Town     6";
	map[7] = "Dungeon  7";
	SetClientSize(265, 125);
	map_type = new wxChoice(this, map_tile_select, wxPoint(0, 0), wxSize(180, 30), 8, map);
	map_type->SetSelection(0);
	Bind(wxEVT_CHOICE, &tile_map_picker_window::select_tile, this, map_tile_select);
	Show();
}

void tile_map_picker_window::select_tile (wxCommandEvent& event) {
	*current_tile = map_type->GetCurrentSelection();
}
