#include "./town_tiles.h"
#include "../img/convert_ultima_into_xpm.h"

void tile_town_picker_window (int *tile) {
	switch (*tile) {
		case 0:
			*tile = 1;
			wxMessageBox("1 - Floor");
			break;
		case 1:
			*tile = 2;
			wxMessageBox("2 - Water");
			break;
		case 2:
			*tile = 3;
			wxMessageBox("3 - Water Corner: Top-Left");
			break;
		case 3:
			*tile = 4;
			wxMessageBox("4 - Water Corner: Bottom-Left");
			break;
		case 4:
			*tile = 5;
			wxMessageBox("5 - Water Corner: Top-Right");
			break;
		case 5:
			*tile = 6;
			wxMessageBox("6 - Water Corner: Bottom-Right");
			break;
		case 6:
			*tile = 7;
			wxMessageBox("7 - Water Diagonal: Bottom-Left");
			break;
		case 7:
			*tile = 8;
			wxMessageBox("8 - Tree: Small");
			break;
		case 8:
			*tile = 9;
			wxMessageBox("9 - Tree: Big");
			break;
		case 9:
			*tile = 10;
			wxMessageBox("10 - Counter: Left-Right");
			break;
		case 10:
			*tile = 11;
			wxMessageBox("11 - Counter: Top-Bottom");
			break;
		case 11:
			*tile = 12;
			wxMessageBox("12 - Counter: Top");
			break;
		case 12:
			*tile = 13;
			wxMessageBox("13 - Counter: Bottom");
			break;
		case 13:
			*tile = 14;
			wxMessageBox("14 - Counter: Left");
			break;
		case 14:
			*tile = 15;
			wxMessageBox("15 - Counter: Right");
			break;
		case 15:
			*tile = 16;
			wxMessageBox("16 - Person: Guard");
			break;
		case 16:
			*tile = 17;
			wxMessageBox("17 - Person: Player");
			break;
		case 17:
			*tile = 18;
			wxMessageBox("18 - Person: Jester 1");
			break;
		case 18:
			*tile = 19;
			wxMessageBox("19 - Person: King");
			break;
		case 19:
			*tile = 20;
			wxMessageBox("20 - Person: Merchant");
			break;
		case 20:
			*tile = 21;
			wxMessageBox("21 - Person: Prisoner");
			break;
		case 21:
			*tile = 22;
			wxMessageBox("22 - Brick Wall");
			break;
		case 22:
			*tile = 23;
			wxMessageBox("23 - A");
			break;
		case 23:
			*tile = 24;
			wxMessageBox("24 - B");
			break;
		case 24:
			*tile = 25;
			wxMessageBox("25 - C");
			break;
		case 25:
			*tile = 26;
			wxMessageBox("26 - D");
			break;
		case 26:
			*tile = 27;
			wxMessageBox("27 - E");
			break;
		case 27:
			*tile = 28;
			wxMessageBox("28 - F");
			break;
		case 28:
			*tile = 29;
			wxMessageBox("29 - G");
			break;
		case 29:
			*tile = 30;
			wxMessageBox("30 - H");
			break;
		case 30:
			*tile = 31;
			wxMessageBox("31 - I");
			break;
		case 31:
			*tile = 32;
			wxMessageBox("32 - J");
			break;
		case 32:
			*tile = 33;
			wxMessageBox("33 - K");
			break;
		case 33:
			*tile = 34;
			wxMessageBox("34 - L");
			break;
		case 34:
			*tile = 35;
			wxMessageBox("35 - M");
			break;
		case 35:
			*tile = 36;
			wxMessageBox("36 - N");
			break;
		case 36:
			*tile = 37;
			wxMessageBox("37 - O");
			break;
		case 37:
			*tile = 38;
			wxMessageBox("38 - H");
			break;
		case 38:
			*tile = 39;
			wxMessageBox("39 - P");
			break;
		case 39:
			*tile = 40;
			wxMessageBox("40 - Q");
			break;
		case 40:
			*tile = 41;
			wxMessageBox("41 - R");
			break;
		case 41:
			*tile = 42;
			wxMessageBox("42 - S");
			break;
		case 42:
			*tile = 43;
			wxMessageBox("43 - T");
			break;
		case 43:
			*tile = 44;
			wxMessageBox("44 - U");
			break;
		case 44:
			*tile = 45;
			wxMessageBox("45 - V");
			break;
		case 45:
			*tile = 46;
			wxMessageBox("46 - W");
			break;
		case 46:
			*tile = 47;
			wxMessageBox("47 - X");
			break;
		case 47:
			*tile = 48;
			wxMessageBox("48 - Y");
			break;
		case 48:
			*tile = 49;
			wxMessageBox("49 - Z");
			break;
		case 49:
			*tile = 50;
			wxMessageBox("50 - Person: Jester 2");
			break;
		case 50:
			*tile = 51;
			wxMessageBox("51 - Floor: Water Floor 1");
			break;
		case 51:
			*tile = 52;
			wxMessageBox("52 - Floor: Water Floor 2");
			break;
		case 52:
			*tile = 53;
			wxMessageBox("53 - Floor: Water Floor 3");
			break;
		case 53:
			*tile = 54;
			wxMessageBox("54 - Floor: Armoury 1");
			break;
		case 54:
			*tile = 55;
			wxMessageBox("55 - Floor: Armoury 2");
			break;
		case 55:
			*tile = 56;
			wxMessageBox("56 - Floor: Grocery 1");
			break;
		case 56:
			*tile = 57;
			wxMessageBox("57 - Floor: Grocery 2");
			break;
		case 57:
			*tile = 58;
			wxMessageBox("58 - Floor: Weaponry 1");
			break;
		case 58:
			*tile = 59;
			wxMessageBox("59 - Floor: Weaponry 2");
			break;
		case 59:
			*tile = 60;
			wxMessageBox("60 - Floor: Magic / Prison Cell 1");
			break;
		case 60:
			*tile = 61;
			wxMessageBox("61 - Floor: Pub or Inn / Prison Cell 2");
			break;
		case 61:
			*tile = 62;
			wxMessageBox("62 - Transportation / Throne Room");
			break;
		case 62:
			*tile = 63;
			wxMessageBox("63 - Between Grocery and Pub");
			break;
		case 63:
			*tile = 0;
			wxMessageBox("0 - Solid Wall");
			break;
	}
}
