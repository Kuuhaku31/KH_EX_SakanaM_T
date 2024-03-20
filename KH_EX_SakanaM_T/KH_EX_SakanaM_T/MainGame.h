
#pragma once

#include <iostream>

#include "GameScene.h"

class MainGame
{	public:

	void 
	RUN()
	{
		init();

		DWORD start_time = 0;
		DWORD end___time = 0;
		DWORD delta_time = 0;

		BeginBatchDraw();
		do
		{	FlushBatchDraw();
			end___time = clock();
			delta_time = end___time - start_time; std::cout << delta_time << std::endl;
			if (delta_time < 1000 / FRAME_RATE) { Sleep(1000 / FRAME_RATE - delta_time); }
			start_time = clock();
		} while (update());
		EndBatchDraw();

		over();
	}

private:

	HWND graph_HWND = nullptr;
	HDC graph_HDC = nullptr;

	Library* library = nullptr;
	Input* input = nullptr;
	Camera* camera = nullptr;
	UI* ui = nullptr;

	GameScene* main_game_scene = nullptr;

	const int FRAME_RATE = 60;

	const int GRAPHWIDE = 1600;
	const int GRAPHHIGH = 900;
	const int GRAPHLONG = 1600 * 900;

	inline void 
	init()
	{
		graph_HWND = initgraph(GRAPHWIDE, GRAPHHIGH, 1);
		graph_HDC = GetImageHDC();

		SetWindowText(graph_HWND, "Sakana");
		setbkcolor(DARKGRAY);
		cleardevice();

		library = new Library();
		library->Init();

		input = new Input();

		double k = 1.0 / 4.0;
		camera = new Camera();
		camera->New_graph(GRAPHWIDE, GRAPHHIGH, GRAPHLONG);
		camera->Reset_sight(GRAPHWIDE * k, GRAPHHIGH * k);

		ui = new UI();
		ui->New_graph(GRAPHWIDE, GRAPHHIGH, GRAPHLONG);

		main_game_scene = new GameScene(library, input, camera, ui);
	}

	inline bool
	update()
	{
		camera->Photographed();
		//ui->Photographed();
		return main_game_scene->Update();
	}

	inline void
	over()
	{
		library->Delete();

		delete library;
		delete input;
		delete camera;
		delete ui;

		delete main_game_scene;

		closegraph();
	}
};
