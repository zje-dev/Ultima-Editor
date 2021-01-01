#pragma once
#ifndef START_WINDOW_H
#define START_WINDOW_H

#include <wx/accel.h>
#include <wx/spinctrl.h>
#include <wx/wxprec.h>
#include <wx/dcclient.h>
#include <wx/event.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#define menu_load_button 1 //The "open" button on the menu
#define load_button 2      //Load button on the window
#define tile_format 3      //Format of the tile ComboBox on the window
#define edit_castle 4      //The button who open the CASTLE.BIN file
#define save_button 5      //I have to explain?
#define edit_tiles 6       //I have to explain? x 2
#define palette_selector 7 //...
#define canvas_of_editor 8 //C A N V A S
#define tile_tile 9        //TILE TILE
#define mond_tile 10
#define tile_town 11
#define space_tile 12
#define fight_tile 13
#define select_tile_editor 14
#define select_map_editor 15
#define legal 16
#define help 17
#define select_castle_editor 18
#define button_map_editor 19
//20
//21
//22
//23
//24
//25
//26
//27
#define run_ultima_button 28
//29
//30
//31
//32
//33
//34
//35
//36
//37
//38
//39
//40
//41
//42
//43
//44
//45
//46
//47
//48
//49
//50
//51
//52
//53

class draw_area : public wxPanel {
	public:
		wxPaintDC *dc;
		int cga_current_color = 0;
		draw_area(wxFrame* parent);
		void draw_editor(wxPaintEvent & evt);
		void select_tile(wxMouseEvent & evt);
		void select_color(wxMouseEvent & evt);
		DECLARE_EVENT_TABLE()
};

class UltimaEditor : public wxApp {
	public:
		virtual bool OnInit();
};

class frame : public wxFrame {
	public:
		draw_area *drawPanel;
		void run_ultima (wxCommandEvent& event);
		frame();
	private:
		void exit (wxCommandEvent& event);
		void select_ultima_folder (wxCommandEvent& event);
		void tile_editor (wxCommandEvent& event);
		void tile_castle (wxCommandEvent& event);
		void tile_map (wxCommandEvent& event);
		void legal_stuff_display (wxCommandEvent& event);
		void change_tile (wxCommandEvent& event);
};

#endif
