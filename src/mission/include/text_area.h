/***************************************************************************
 *                           text_area.h  -  description
 *                           --------------------------
 *                           begin                : January 10, 2002
 *                           copyright            : (C) 2002 by David Ranger
 *                           email                : ussreliant@users.sourceforge.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   any later version.                                                    *
 *                                                                         *
 ***************************************************************************/

#ifndef TEXT_AREA_H
#define TEXT_AREA_H

// Version: 1.1  - February 27, 2002
// Changes:
//    1.0 - Fixed misaligned down scroll button (FINALLY). Fixed text going past the text area (horizontal). Added multiline text areas.

/* This class is designed to be self sufficient.
 * The only external functions it requires that aren't provided by system libs are in glut_support.h
 */


// There are places where a float is converted to an int. This define takes extra steps to convert without a warning (float -> char -> int)
#define NO_WARNINGS

#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream.h>

#include "glut_support.h"

#define DIR_TEXT "data/images/gui/text_area/"

// These defines are used by the image loader
#define TEXT_AREA_00 DIR_TEXT ## "button_down.png"
#define TEXT_AREA_01 DIR_TEXT ## "button_up.png"
#define TEXT_AREA_02 DIR_TEXT ## "corner_top_left.png"
#define TEXT_AREA_03 DIR_TEXT ## "corner_top_right.png"
#define TEXT_AREA_04 DIR_TEXT ## "corner_bottom_left.png"
#define TEXT_AREA_05 DIR_TEXT ## "corner_bottom_right.png"
#define TEXT_AREA_06 DIR_TEXT ## "highlight_button_up.png"
#define TEXT_AREA_07 DIR_TEXT ## "highlight_button_down.png"
#define TEXT_AREA_08 DIR_TEXT ## "horizontal.png"
#define TEXT_AREA_09 DIR_TEXT ## "left_side.png"
#define TEXT_AREA_10 DIR_TEXT ## "right_side.png"
#define TEXT_AREA_11 DIR_TEXT ## "scrollbar.png"
#define TEXT_AREA_12 DIR_TEXT ## "highlight_scrollbar.png"
#define TEXT_AREA_13 DIR_TEXT ## "horizontal_end.png"

// These defines are used by the class functions to locate the texture in the array (above)
#define IMG_BUTTON_DOWN 0
#define IMG_BUTTON_UP 1
#define IMG_CORNER_TOP_LEFT 2
#define IMG_CORNER_TOP_RIGHT 3
#define IMG_CORNER_BOTTOM_LEFT 4
#define IMG_CORNER_BOTTOM_RIGHT 5
#define IMG_HIGHLIGHT_BUTTON_UP 6
#define IMG_HIGHLIGHT_BUTTON_DOWN 7
#define IMG_HIGHLIGHT_SCROLLBAR 12
#define IMG_TOP 8
#define IMG_BOTTOM 8
#define IMG_LEFT_SIDE 9
#define IMG_RIGHT_SIDE 10
#define IMG_SCROLLBAR 11
#define IMG_END 13

class TextArea {
public:
	TextArea(void);
	TextArea(float x, float y, float wid, float hei, int scrollbar);
	~TextArea(void);

	void DoHighlight(int yes);	// DoHighlight(0) to disable mouse highlighting. Also disable clicking on entries
	void DoMultiline(int yes);	// DoMultiline(1) to enable multi-line entries
	void Refresh(void);
	void RenderText(void);
	void AddTextItem(char *name, char *description);
	void AddTextItem(char *name, char *description, char *parent_name);
	void ChangeTextItem(char *name, char *description);
	void SetText(char *text);	// Sets the text. Enables Multiline and disables highlighting
	// Returns the char of the currently selected item. NULL if nothing is selected
	char *GetSelectedItemName(void);
	char *GetSelectedItemDesc(void);

	// Returns 1 if the click is inside the text area. 0 if it's outside. Same thing for movement
	// The class requires you convert the x,y co-ordinate to a -1 to 1 float. The class doesn't know the screen dimensions
	int MouseClick(int button, int state, float x, float y);
	int MouseMove(float x, float y);
	// Mouse movement while the button is clicked
	int MouseMoveClick(float x, float y);

private:
	// Flag that enables/disables the scrollbar (It is not shown if it is disabled). This includes the scroll buttons
	int has_scrollbar;

	// Flags that enable/disable Highlighting and Mutli-line text
	int do_highlight;
	int do_multiline;

	// Array is as follows:
	// Entire box (the border), top scroll button, buttom scroll button, entire scrollbar, active scrollbar, text area
	float xcoord[6];
	float ycoord[6];
	float width[6];
	float height[6];

	// Percentage of space to allocate for the border. [0] is the thin part, [1] is the scrollbar area (right side)
	float ratio[2];

	// Ratios for the top and button buttons (proportional x,y, height, and width values)
	float button_ratio[4];

	// Ratios for the scroll bar area (proportional x,y, height, and width values)
	float scrollbar_ratio[4];

	// Amount of space to display between lines
	float text_spacing;

	// Amout of space to allocate to the horizontal bar for each level of text (expanding trees)
	float horizontal_per_level;

	// Amount of space between the text and the top/bottom border
	float horizontal_spacer;

	// Amount of space to the left of text to have the vertical bar
	float vertical_left_of_text;

	// Size of the font. The float version is to prevent rounding errors in calculations
	int font_size;
	float font_size_float;

	// The number of lines of text we can display at once
	float max_lines;

	// 0 for no button clicked, 1 for top button, 2 for bottom button, 3 for scrollbar, 4 for above scrollbar, 5 for below scrollbar
	int button_pressed;

	// The currently highlighted item
	int cur_highlighted;

	// The number of items in our list
	int item_count;

	// The currently selected number
	int cur_selected;

	// The number of the first item in the visible area
	int top_item_number;

	// The number of items to jump when clicking in the passive area of the scrollbar
	int page_size;

	// This stores the y coord of where the mouse was when it started dragging the scrollbar
	float scroll_start;

	// This stores the current y axes of the mouse while scrolling
	float scroll_cur;

	// Linked list of items that will appear if the text area is a select box (doubles as an expanding tree)
	class TextAreaItem *ItemList;

	// Check if that x,y co-ordinate is inside us
	int Inside(float x, float y, int group);
	void LoadTextures(void);
	void RenderTextItem(TextAreaItem *current, int level);

	int LocateCount(float y);

	// Highlighted text (mouse over, selected item) will only occur at a Refresh()
	void HighlightCount(int count, int type);

	void DisplayScrollbar(void);
	char *GetSelectedItem(int type);

	// Takes a line and puts them in as seperate items (line wrapping)
	void ChompIntoItems(char *text, char *parent);
};

// Keep everything public so the TextArea class can get faster access to the elements in this class
class TextAreaItem {
public:
	TextAreaItem(void);
	// parent_class is NULL for the master TextAreaItem
	TextAreaItem(char *new_name, char *desc, TextAreaItem *parent_class);
	~TextAreaItem(void);

	// A recursive function. This function will be called to all the children until one of them matches the search_name
	// If no match is found, it will use the main tree.
	TextAreaItem *FindChild(char *search_name);
	TextAreaItem *FindCount(int count, int cur);

	void AddChild(char *new_name, char *desc);
	void ExpandTree(void);

	char *name;
	char *description;

	// The size of the array is 10 * child_count_multiplier. Allows for an expanding array
	int child_count_multiplier;
	int child_count;
	TextAreaItem **child;

	TextAreaItem *parent;

	int expanded;
};

void LoadTextures(void);

#endif    // TEXT_AREA_H
