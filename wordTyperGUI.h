#ifndef WORDTYPERGUI_H
#define WORDTYPERGUI_H

/*A program to practice typing
By Frank Mock, December 2016
www.frankmock.com
*/
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Multiline_Output.H>
#include <Fl/Fl_Text_Editor.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Button.H>
#include <string>
#include <stdlib.h>
#include"wordMachine.h"

const double TIMER_TIMEOUT = 7.0; // 7 seconds between word phrases

class WordTyperGUI : Fl_Window{
public:

	// Constructs a window to place GUI widgets into
	WordTyperGUI(int w, int h, const char* title);
	~WordTyperGUI();

	// The GUI widgets
	Fl_Menu_Bar *menu;
	Fl_Scroll *scrollbox;
	Fl_Multiline_Output *msgBox; // To display messages to the user
	Fl_Output *output;		     // Words to type appear in this
	Fl_Text_Editor *input;       // User types into this input
	Fl_Text_Buffer *buff;		 // input uses a text buffer
	Fl_Button *startBtn;		 // Button to start the typing test
	Fl_Button *stopBtn;          // Button to stop the typing test

private:
	bool typerIsRunning;
	WordMachine *wm;	// WordMachine offers functionality to test user typing
	static void cut_CB(Fl_Widget*, void*);
	static void copy_CB(Fl_Widget*, void*);
	static void paste_CB(Fl_Widget*, void*);
	static void Quit_CB(Fl_Widget*, void*);
	static void startBtn_CB(Fl_Widget*, void*);
	static void stopBtn_CB(Fl_Widget*, void*);
	static void timerEvent(void*);  // Operation to perform at each timer timeout
	float getElapsedTime();    // Gets the time the test took form WordMachine
	std::string floatToString(float);  // Converts a float to a string
	static void textEditorChanged(int, int nInserted, int nDeleted, int, const char*, void* v);
};
#endif