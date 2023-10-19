#pragma once
#include"Music.h"

class Application
{
public:
	//Startup point of application
	Application();

private:
	//font and text class
	Font font;
	Text PL;
	//sprite for background
	Sprite Back;
	//vector for melody`s avalible in folder
	vector<Melody> Playlist;
	// function to search every melody in folder
	void LoadMusic();
	//Menu's
	void Menu();
	void GetName(RenderWindow& window);
	void PlayMusic(int index, RenderWindow& window);
};

