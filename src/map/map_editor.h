#pragma once
#ifndef MENU_WINDOW_H
#define MENU_WINDOW_H

#include <wx/spinctrl.h>
#include <wx/wxprec.h>
#include <wx/dcclient.h>
#include <wx/event.h>
#include <string>
#include <vector>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#define select_map_type 20
#define load_button_map 21
#define save_button_map 22

void set_map_tile_id (int, wxBitmap*);
void get_map_tile_id (int, int, wxBitmap*, wxBitmap*);

class map_editor_display : public wxPanel {
	public:
		wxPaintDC *dc;
		int xp = 0, yp = 0;
		bool move_on_map = false;
		map_editor_display(wxFrame* parent);
	private:
		void draw_editor(wxPaintEvent & evt);
		void select_tile(wxMouseEvent & evt);
		void mouse_wheel(wxMouseEvent & evt);
		void mouse_move_on (wxMouseEvent & evt);
		void mouse_move_off (wxMouseEvent & evt);
		void mouse_move(wxMouseEvent & evt);
		void change_tile(wxMouseEvent & evt);
		void change_selecyted_tile(wxMouseEvent & evt);
		DECLARE_EVENT_TABLE()
};

class map_editors : public wxFrame {
	public:
		map_editor_display *drawPanel;
		map_editors(std::string);
	private:
		void exit (wxCommandEvent& event);
		void change_map (wxCommandEvent& event);
};

#endif
