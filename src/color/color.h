#pragma once
#ifndef COLOR_WINDOW_H
#define COLOR_WINDOW_H

#include <vector>
#include <wx/wxprec.h>
#include <wx/event.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

//cga
#define cga_0 23
#define cga_1 24
#define cga_2 25
#define cga_3 26
//t1k
#define tik_0  29
#define tik_1  30
#define tik_2  31
#define tik_3  32
#define tik_4  33
#define tik_5  34
#define tik_6  35
#define tik_7  36
#define tik_8  37
#define tik_9  38
#define tik_10 39
#define tik_11 40
#define tik_12 41
#define tik_13 42
#define tik_14 43
#define tik_15 44

class color_picker_window : public wxFrame {
	public:
		int *current_color;
		color_picker_window(int palette, int*, bool);
	private:
		void exit (wxCommandEvent& event);
		std::vector<void (color_picker_window::*)(wxCommandEvent&)> selects;
		void select_color_0 (wxCommandEvent& event); //I hate my code
		void select_color_1 (wxCommandEvent& event);
		void select_color_2 (wxCommandEvent& event);
		void select_color_3 (wxCommandEvent& event);
		void select_color_4 (wxCommandEvent& event);
		void select_color_5 (wxCommandEvent& event);
		void select_color_6 (wxCommandEvent& event);
		void select_color_7 (wxCommandEvent& event);
		void select_color_8 (wxCommandEvent& event);
		void select_color_9 (wxCommandEvent& event);
		void select_color_10(wxCommandEvent& event);
		void select_color_11(wxCommandEvent& event);
		void select_color_12(wxCommandEvent& event);
		void select_color_13(wxCommandEvent& event);
		void select_color_14(wxCommandEvent& event);
		void select_color_15(wxCommandEvent& event);
};
#endif
