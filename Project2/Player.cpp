#include"Player.h"

Application::Application()
{
	//Load font from project folder
	font.loadFromFile("Caprasimo-Regular.ttf");
	//Also load background image
	Texture Background;
	Background.loadFromFile("Resources/Back.jpg");
	Back.setTexture(Background);
	//call void function to create Music class elements
	LoadMusic();
	//Menu call
	Menu();
}
void Application::LoadMusic()
{
	int i = 1;
	string list;
	//search in directory for .mp3 files
	for (const auto& entry : fs::directory_iterator("Resources/"))
	{
		if (entry.path().extension() == ".mp3")
		{
			//redirect path to Melody class
			Playlist.push_back(Melody(entry));
			list += to_string(i);
			list += " ";
			list += entry.path().filename().string();
			list += '\n';
			i++;
		}
	}
	PL.setString(list);
}
void Application::Menu()
{
	//
	Text text;
	text.setFont(font);
	text.setString("To open player press P\n\nEscape - Exit");
	text.setCharacterSize(24);
	text.setFillColor(Color::White);
	text.setPosition(20, 50);
	//

	//Menu window render
	RenderWindow window(VideoMode(800, 400), "D'oh");
	window.setVerticalSyncEnabled(true);

	// Set an icon
	auto image = Image{};
	image.loadFromFile("Resources/Icon.png");
	window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
	//


	//While menu is open 
	while (window.isOpen())
	{
		// cycle that take any of listed event end make programmed actions
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				switch (event.key.code)
				{
				case Keyboard::Escape:
					window.close();
					break;
				case Keyboard::P:
					GetName(window);
					break;
				}
			}
		}
		//clean - draw - display Cycle
		window.clear();
		window.draw(Back);
		window.draw(text);
		window.display();
	}
}
void Application::GetName(RenderWindow& window)
{
	//
	Text text;
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(Color::White);
	text.setPosition(20, 50);
	string Input_box;
	text.setString("Please enter number of the song - " + Input_box
		+ "\nList Up - arrow Up\nList down - arrow Down\nEscape - Back");
	int Index;
	//
	PL.setFont(font);
	PL.setCharacterSize(16);
	PL.setFillColor(Color::White);
	PL.setPosition(520, 0);
	//
	int it = 0;

	while (window.isOpen())
	{
		// cycle that take any of listed event end make programmed actions
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				if (event.key.code == Keyboard::Backspace)
				{
					if (!Input_box.empty())
					{
						Input_box.clear();
						Index = 0;
						text.setString("Please enter number of the song - " + Input_box
							+ "\nList Up - arrow Up\nList down - arrow Down\nEscape - Back");
					}
				}
				else if (event.key.code == Keyboard::Enter)
				{
					if (Index > 0 && Index <= Playlist.size())
						PlayMusic(Index - 1, window);
				}
				else if (event.key.code == Keyboard::Escape)
					return;
				else if (event.key.code == Keyboard::Down)
				{
					if (Playlist.size() > 22)
					{
						if (it < Playlist.size() - 22)
						{
							it++;
							PL.setPosition(520, PL.getPosition().y - 18);
						}
					}
				}
				else if (event.key.code == Keyboard::Up)
				{
					if (it != 0)
					{
						it--;
						PL.setPosition(520, PL.getPosition().y + 18);
					}
				}
				break;
			}
			if (event.type == Event::TextEntered)
				if (event.text.unicode > 47 && event.text.unicode < 58)
				{
					Input_box += static_cast<char>(event.text.unicode);
					Index = stoi(Input_box);
					text.setString("Please enter number of the song - " + Input_box
						+ "\nList Up - arrow Up\nList down - arrow Down\nEscape - Back");
				}
		}
		//clean - draw - display Cycle
		window.clear();
		window.draw(Back);
		window.draw(text);
		window.draw(PL);
		window.display();
	}
}
void Application::PlayMusic(int index, RenderWindow& window)
{
	Music melody;
	//If melody cant be opened from file return to previous menu
	if (!melody.openFromFile(Playlist[index].Ret_Path()))
	{
		return;
	}

	//
	Text text;
	text.setFont(font);
	text.setString("Current melody - " + Playlist[index].Ret_Name() + "\nPause/continue - space\n"
		"Volume up - arrow UP\nVolume down - arrow Down\nPrevious melody - arrow Left\nNext melody - arrow Right\nCurrent volume\t"
		+ to_string((int)melody.getVolume()) + "\nEscape - Back");
	text.setCharacterSize(24);
	text.setFillColor(Color::White);
	text.setPosition(20, 50);
	//

	int Volume = melody.getVolume();
	melody.play();

	//Cycle while melody is playing
	while (melody.getStatus() == Music::Playing)
	{
		while (window.isOpen())
		{
			// cycle that take any of listed event end make programmed actions
			Event event;
			while (window.pollEvent(event))
			{
				//If melody is ended
				if (melody.getStatus() == Music::Stopped)
				{
					if (index + 1 < Playlist.size())
					{
						index++;
						melody.openFromFile(Playlist[index].Ret_Path());
						melody.play();
						text.setString("Current melody - " + Playlist[index].Ret_Name() + "\nPause/continue - space\n"
							"Volume up - arrow UP\nVolume down - arrow Down\nPrevious melody - arrow Left\nNext melody - arrow Right\nCurrent volume\t"
							+ to_string((int)melody.getVolume()) + "\nEscape - Back");
					}
				}
				switch (event.type)
				{
				case Event::Closed:
					melody.stop();
					window.close();
					break;
				case Event::KeyPressed:
					switch (event.key.code)
					{
					case Keyboard::Space:
						if (melody.getStatus() == Music::Playing)
							melody.pause();
						else
							melody.play();
						text.setString("Current melody - " + Playlist[index].Ret_Name() + "\nPause/continue - space\n"
							"Volume up - arrow UP\nVolume down - arrow Down\nPrevious melody - arrow Left\nNext melody - arrow Right\nCurrent volume\t"
							+ to_string((int)melody.getVolume()) + "\nEscape - Back");
						break;
					case Keyboard::Escape:
						return;
						break;
					case Keyboard::Up:
						if (melody.getVolume() <= 90.f)
						{
							if (melody.getVolume() == 0)
								melody.setVolume(10);
							else
								melody.setVolume(Volume += 10);
							text.setString("Current melody - " + Playlist[index].Ret_Name() + "\nPause/continue - space\n"
								"Volume up - arrow UP\nVolume down - arrow Down\nPrevious melody - arrow Left\nNext melody - arrow Right\nCurrent volume\t"
								+ to_string((int)melody.getVolume()) + "\nEscape - Back");
						}
						break;
					case Keyboard::Down:
						if (melody.getVolume() > 0.f)
						{
							if (melody.getVolume() <= 10)
								melody.setVolume(0);
							else
								melody.setVolume(Volume -= 10);
							text.setString("Current melody - " + Playlist[index].Ret_Name() + "\nPause/continue - space\n"
								"Volume up - arrow UP\nVolume down - arrow Down\nPrevious melody - arrow Left\nNext melody - arrow Right\nCurrent volume\t"
								+ to_string((int)melody.getVolume()) + "\nEscape - Back");
						}
						break;
					case Keyboard::Left:
						if (index - 1 >= 0)
						{
							index--;
							melody.openFromFile(Playlist[index].Ret_Path());
							melody.play();
							text.setString("Current melody - " + Playlist[index].Ret_Name() + "\nPause/continue - space\n"
								"Volume up - arrow UP\nVolume down - arrow Down\nPrevious melody - arrow Left\nNext melody - arrow Right\nCurrent volume\t"
								+ to_string((int)melody.getVolume()) + "\nEscape - Back");
						}
						break;
					case Keyboard::Right:
						if (index + 1 < Playlist.size())
						{
							index++;
							melody.openFromFile(Playlist[index].Ret_Path());
							melody.play();
							text.setString("Current melody - " + Playlist[index].Ret_Name() + "\nPause/continue - space\n"
								"Volume up - arrow UP\nVolume down - arrow Down\nPrevious melody - arrow Left\nNext melody - arrow Right\nCurrent volume\t"
								+ to_string((int)melody.getVolume()) + "\nEscape - Back");
						}
						break;
					}
					break;
				}
			}
			//clean - draw - display Cycle
			window.clear();
			window.draw(Back);
			window.draw(text);
			window.display();
		}
	}
}