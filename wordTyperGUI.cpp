#include"wordTyperGUI.h"
#include"wordMachine.h"
#include<string>
#include<sstream>
#include<stdio.h>


/*A program to practice typing
By Frank Mock, January 2017
www.frankmock.com
*/

// Construct and initialize program
WordTyperGUI::WordTyperGUI(int w, int h, const char* title) :Fl_Window(w, h, title){

	// typer not running until start button is pressed
	typerIsRunning = false;

	// Create a WordMachine object
	wm = new WordMachine();

	// Add GUI elements
	begin();
	menu = new Fl_Menu_Bar(0, 0, 600, 25);
	menu->add("File/Quit", FL_CTRL + 'q', Quit_CB);
	menu->add("Edit/Cut", FL_CTRL + 'c', cut_CB, (void*)this);
	menu->add("Edit/Copy", FL_CTRL + 'p', copy_CB, (void*)this);
	menu->add("Edit/Paste", FL_CTRL + 'v', paste_CB, (void*)this);


	int ypos = 150;

	// A Message box to display messages to the user
	msgBox = new Fl_Multiline_Output(0, 50, 600, 85, "");
	msgBox->color(0xc2c200);
	msgBox->textfont(FL_HELVETICA);
	msgBox->textsize(24);
	msgBox->value("Press CTRL-B to begin");


	// Outputs the words/phrases to the user
	output = new Fl_Output(0, ypos, 600, 42, "&output");
	output->color(0xc2c200);
	output->value("Word phrase will appear here");
	output->tooltip("Words or phrases will appear here");
	output->textfont(FL_HELVETICA);
	output->textsize(24);

	ypos += 100;

	input = new Fl_Text_Editor(0, ypos, 600, 210, "");
	input->textfont(FL_HELVETICA);
	input->textsize(24);
	input->tooltip("Word phrases appear here. Press enter after each phrase.");
	buff = new Fl_Text_Buffer();
	input->buffer(buff);

	// Assign callback to text editor buffer
	buff->add_modify_callback(textEditorChanged, this);

	//Add text to the buffer
	buff->text("You type here");



	// Add buttons to bottom of GUI
	// The buttons will be contained in the Fl_Text_editor container
	// This means, when created their starting x-position and y-position are
	// the same as the Fl_Text_Editor
	int xpos = 200;
	startBtn = new Fl_Button(xpos + 300, ypos + 225, 30, 30, "@>");
	startBtn->callback((Fl_Callback*)startBtn_CB, this);

	// Press CTRL-B to Begin
	startBtn->shortcut(FL_CTRL + 'b');

	stopBtn = new Fl_Button(xpos + 350, ypos + 225, 30, 30, "@square");
	stopBtn->callback((Fl_Callback*)stopBtn_CB, this);
	// Press CTRL-S to Stop
	stopBtn->shortcut(FL_CTRL + 's');

	end();
	resizable(this);
	show();
}

WordTyperGUI::~WordTyperGUI(){}

// Callback for menu items

void WordTyperGUI::cut_CB(Fl_Widget* w, void* v){
	WordTyperGUI* e = (WordTyperGUI*)v;  
	Fl_Text_Editor::kf_cut(0, e->input);
}

void WordTyperGUI::copy_CB(Fl_Widget*, void* v) { 
	WordTyperGUI* e = (WordTyperGUI*)v;  
	Fl_Text_Editor::kf_copy(0, e->input); 
}

void WordTyperGUI::paste_CB(Fl_Widget*, void* v) { 
	WordTyperGUI* e = (WordTyperGUI*)v;  
	Fl_Text_Editor::kf_paste(0, e->input); 
}

void WordTyperGUI::Quit_CB(Fl_Widget *, void *) {
	exit(0);
}

// Start button callback
void WordTyperGUI::startBtn_CB(Fl_Widget* w, void* v){
	WordTyperGUI* e = (WordTyperGUI*)v;

	// Position cursor at input textbox
	e->input->take_focus();

	// Capture the start time
	e->wm->setStartTime();

	int buffLen = e->buff->length();
	// clear msg in buffer
	e->buff->remove(0, buffLen);

	// Clear any messages to the user
	e->msgBox->value("");

	// Clear top output window
	e->output->value("");

	// Set timer control boolean to true
	e->typerIsRunning = true;

	// If WordMachine is ready, get a word and display it to user
	if (e->wm->runWordMachine()){
		// Get the string
		std::string a = e->wm->getWord();

		printf("word is %s\n", a.c_str());

		// Clear previous text
		e->output->value("");

		// Convert to C string and append to the output window
		e->output->insert(a.c_str());
	}

	// Add timer event that calls timerEvent in TIMER_TIMEOUT seconds
	Fl::add_timeout(TIMER_TIMEOUT, timerEvent, e);
}

// Stops the typing test and calls method to display results
void WordTyperGUI::stopBtn_CB(Fl_Widget* w, void* v){

	WordTyperGUI* e = (WordTyperGUI*)v;

	// Stop the timeout event from occuring again
	e->typerIsRunning = false;
	// Get the results and display to user
	e->getElapsedTime();

	// Analyze what user typed and get results
	std::string s = e->wm->getTestResults(e->buff);

	// output results to message textbox
	e->msgBox->value(s.c_str());
}


// Callback method the timer uses while typing test is running
void WordTyperGUI::timerEvent(void* v){
	// Don't have access to this so must cast v to this
	WordTyperGUI* e = (WordTyperGUI*)v;

	// If timer event is active get words and append them to buffer
	if (e->typerIsRunning){

		if (e->wm->runWordMachine()){
			// Get the string
			std::string a = e->wm->getWord();

			printf("word is %s\n", a.c_str());

			// Clear previous text
			e->output->value("");

			// Convert to C string and append to the output window
			e->output->insert(a.c_str());

			// Have timer call this method again at timeout
			Fl::add_timeout(TIMER_TIMEOUT, timerEvent, e);
		}
		else{

			e->typerIsRunning = false;
			e->getElapsedTime();

			// Analyze what user typed and get results
			std::string s = e->wm->getTestResults(e->buff);

			// output results to message textbox
			e->msgBox->value(s.c_str());
		}
	}
}


// Returns the elapsed time
// Also, displays results to user
//*****< TO DO > Break this into two methods ***
float WordTyperGUI::getElapsedTime(){
	// Capture the stop time
	wm->setStopTime();

	// Get the elapsed time
	float eTime = wm->getTime();

	// print elapsed time
	printf("Elapsed time %f\n", eTime);

	std::string message = "Elapsed time: ";

	std::string time = floatToString(eTime);

	// Print result to user
	msgBox->value((message + time).c_str());

	return eTime;
}

/*** < TO DO > Respond to events in editor (what user types) */
void WordTyperGUI::textEditorChanged(int, int nInserted, int nDeleted, int, const char*, void* v){
	//TO DO
}

/* Converts a float input to a string 
 * Returns the string */
std::string WordTyperGUI::floatToString(float f){
	std::ostringstream oss;
	oss << f;
	return oss.str();
}
