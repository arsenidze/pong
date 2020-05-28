#include <iostream>
#include <filesystem>
#include <map>

#include "Graphics/Graphics.h"
#include "Game/Game.h"
#include "InputHandler/InputHandler.h"
#include "Paddle/Paddle.h"
#include "Wall/Wall.h"
#include "Ball/Ball.h"
#include "PaddleBot/PaddleBot.h"

int winWidth = 800;
int winHeight = 600;

// Use it to run from ide
//std::map<std::string, std::filesystem::path> textureFileMap =
//{
//	{"paddle", std::filesystem::current_path() / "assets" / "brown32.png"},
//	{"wall", std::filesystem::current_path() / "assets" / "wall.png"},
//	{"ball", std::filesystem::current_path() / "assets" / "ball32.png"},
//};

std::map<std::string, std::filesystem::path> textureFileMap =
{
	{"paddle", std::filesystem::current_path() / ".." / "assets" / "brown32.png"},
	{"wall", std::filesystem::current_path() / ".." / "assets" / "wall.png"},
	{"ball", std::filesystem::current_path() / ".." / "assets" / "ball32.png"},
};


int main(int argc, char* argv[])
{
	std::cout << textureFileMap["paddle"].string() << std::endl;
	GraphicsConfig	graphicsConfig;

	graphicsConfig.winName = "Pong";
	graphicsConfig.winWidth = winWidth;
	graphicsConfig.winHeight = winHeight;

	bool playWithBot = true;

	std::cout << "Play with bot? Press 'y' to play with bot or any other character to 1x1 game" << std::endl;

	std::string userInput;
	std::cin >> userInput;
	if (userInput == "y")
	{
		playWithBot = true;
	}
	else
	{
		playWithBot = false;
	}

	auto gameObjects = std::vector<std::shared_ptr<IGameObject>>{
			std::make_shared<Ball>(
			std::move(Vector2D(winWidth / 2, winHeight / 2)),
			10,
			"ball"),

			std::make_shared<Wall>(
			std::move(Vector2D(winWidth / 2, 10)),
			std::move(Vector2D(winWidth, 20)),
			"wall",
			std::move(Vector2D(0, 1))),

			std::make_shared<Wall>(
			std::move(Vector2D(winWidth / 2, winHeight - 10)),
			std::move(Vector2D(winWidth, 20)),
			"wall",
			std::move(Vector2D(0, -1))),

			std::make_shared<Paddle>(
			std::move(Vector2D(50, winHeight / 2)),
			std::move(Vector2D(10, 50)),
			"paddle",
			std::move(Vector2D(1, 0)),
			std::vector<std::string>{"W", "S"})
	};


	if (playWithBot)
	{
		gameObjects.push_back(
			std::make_shared<PaddleBot>(
				std::move(Vector2D(winWidth - 50, winHeight / 2)),
				std::move(Vector2D(10, 50)),
				"paddle",
				std::move(Vector2D(1, 0)),
				std::static_pointer_cast<Ball>(gameObjects[0]))
		);
	}
	else
	{
		gameObjects.push_back(
			std::make_shared<Paddle>(
				std::move(Vector2D(winWidth - 50, winHeight / 2)),
				std::move(Vector2D(10, 50)),
				"paddle",
				std::move(Vector2D(-1, 0)),
				std::vector<std::string>{"P", "L"})
		);
	}
	
	std::cout << "Press W/S or P/L" << std::endl;

	auto&	graphics = Graphics::getInstance();
	graphics.init(graphicsConfig);
	graphics.loadTextures(textureFileMap);
	
	InputHandler inputHandler;

	Game game(winWidth, winHeight, gameObjects);

	while (game.isRunning())
	{
		inputHandler.ask();
		if (inputHandler.isWindowClosed())
		{
			break;
		}
		game.handleInput(inputHandler);
		game.update(inputHandler);
		game.render(graphics);
	}

	graphics.deinit();

	return 0;
}