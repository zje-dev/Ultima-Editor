#pragma once
#ifndef COLOR_WINDOW_H
#define COLOR_WINDOW_H

#include <wx/wxprec.h>
#include <wx/event.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#define map_tile_select 27

class tile_map_picker_window : public wxFrame {
	public:
		int *current_tile;
		wxChoice *map_type;
		tile_map_picker_window(int*);
	private:
		void exit (wxCommandEvent& event);
		//cga
		void select_tile (wxCommandEvent& event);
};
#endif
