#pragma once

#include "wx/wx.h"
#include <time.h> 
#include <vector>

#define EMPTY_SPOT 0

class cMain : public wxFrame
{

public:
	cMain();
	~cMain();

private:

	enum Players
	{
		PLAYER = -10,
		AI = 10
	};
	enum Status
	{
		PLAYER_WIN = PLAYER,
		NO_WIN = -1,
		AI_WIN = AI,
		TIE = 0 //also empty spot
	};
	struct move
	{
		int x;
		int y;
	};

	//Variables
	int fieldWidth = 3;
	int fieldHeight = 3;
	wxButton** btn;

	int* field = nullptr;
	bool firstClick = true;
	int winStatus = NO_WIN;
	int currentPlayer = PLAYER;
	//int turnCount = 0;

	move bestMove;



	void OnButtonClicked(wxCommandEvent& evt);
	int CheckWinner();
	void ResetGame();

	//modifies winStatus variable
	void CheckWinCondition();
	move BestMove();
	int MiniMax(int* arr, int depth, int NextPlayer);


	wxDECLARE_EVENT_TABLE();

};

