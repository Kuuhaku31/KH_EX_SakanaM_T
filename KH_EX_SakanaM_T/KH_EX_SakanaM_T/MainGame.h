
#pragma once

#include <iostream>

#include "MenuScene.h"
#include "GameScene.h"

Library main_library;
Input   main_input;
Camera  main_camera;

class MainGame
{	public: 
	MainGame() {}

	void 
	RUN()
	{
		init();

		unsigned long start_time = 0;
		unsigned long end___time = 0;
		unsigned long delta_time = 0;

		BeginBatchDraw();
		do
		{	FlushBatchDraw();
			end___time = clock();
			delta_time = end___time - start_time; std::cout << delta_time << std::endl;
			if (delta_time < SLEEP) { Sleep(SLEEP - delta_time); }
			start_time = clock();
		} while (update());
		EndBatchDraw();

		over();
	}

private:

	HWND graph_HWND = nullptr;

	MenuScene main_menu_scene;
	GameScene main_game_scene;

	const int FRAME_RATE = 60;
	const int SLEEP = 1000 / FRAME_RATE;

	const int GRAPHWIDE = 1600;
	const int GRAPHHIGH = 900;
	const int GRAPHLONG = 1600 * 900;

	const int wx = 1176;
	const int wy = 1569;

	inline void 
	init()
	{

		graph_HWND = initgraph(GRAPHWIDE, GRAPHHIGH, 1);
		SetWindowPos(graph_HWND, nullptr, -1374, 793, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		SetWindowText(graph_HWND, "Sakana");

		main_library.Init();

		float k = 1.0 / 4.0;
		main_camera.New_graph(GRAPHWIDE, GRAPHHIGH, GRAPHLONG);
		main_camera.Reset_sight(GRAPHWIDE * k, GRAPHHIGH * k);

		main_game_scene.Init();
	}

	inline bool
	update()
	{
		return main_game_scene.Update();
	}

	inline void
	over()
	{
		closegraph();
	}
};
