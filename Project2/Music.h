#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/System.hpp>
#include<iostream>
#include<string>
#include<filesystem>

//this player use filesystem library 
//that only availible vith last c++ language version!!
namespace fs = std::filesystem;
using namespace std;
using namespace sf;

class Melody
{
private:
	//Melody name and path in folder
	string name;
	string path;

public:
	Melody(const auto& placement)
	{
		name = placement.path().filename().string();
		path = placement.path().string();
	}
	string& Ret_Path()	{	return path;	}
	string& Ret_Name()	{	return name;	}
};
