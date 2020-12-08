#pragma once
#include <TGUI/TGUI.hpp>
class GUI
{
private:
	tgui::Gui& gui;
	void createResourceBar();
	void createSelectionWindow();
public:
	GUI(tgui::Gui& gui) : gui(gui) {};
	void createGUI();
	void updateResourceLabels();
	void updateSelection();
	void update();

};

