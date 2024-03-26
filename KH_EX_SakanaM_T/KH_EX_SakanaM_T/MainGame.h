
#pragma once

#include <iostream>

#include "GameScene.h"

class MainGame
{	public:

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

	Library library;
	Input input;

	Camera camera;

	GameScene* main_game_scene = nullptr;

	const int FRAME_RATE = 60;
	const int SLEEP = 1000 / FRAME_RATE;

	const int GRAPHWIDE = 1600;
	const int GRAPHHIGH = 900;
	const int GRAPHLONG = 1600 * 900;

	inline void 
	init()
	{
		graph_HWND = initgraph(GRAPHWIDE, GRAPHHIGH, 1);
		SetWindowPos(graph_HWND, nullptr, 1000, 1500, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		SetWindowText(graph_HWND, "Sakana");

		library.Init();

		float k = 1.0 / 4.0;
		camera.New_graph(GRAPHWIDE, GRAPHHIGH, GRAPHLONG);
		camera.Reset_sight(GRAPHWIDE * k, GRAPHHIGH * k);

		main_game_scene = new GameScene(&library, &input, &camera);
	}

	inline bool
	update()
	{
		return main_game_scene->Update();
	}

	inline void
	over()
	{
		delete main_game_scene;

		closegraph();
	}
};
