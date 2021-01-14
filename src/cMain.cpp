#include <cMain.h>


wxBEGIN_EVENT_TABLE(cMain, wxFrame)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Kolko i Krzyzyk", wxPoint(), wxSize(600, 600))
{
	srand(time(NULL));
	btn = new wxButton*[fieldWidth * fieldHeight];
	wxGridSizer* grid = new wxGridSizer(fieldHeight,fieldHeight,0,0);

	field = new int[fieldWidth * fieldHeight];

	wxFont font(56, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	for (int x = 0; x < fieldWidth; x++)
	{
		for (int y = 0; y < fieldHeight; y++)
		{
			btn[y * fieldWidth + x] = new wxButton(this, 10000 + (y * fieldWidth + x));
			btn[y * fieldWidth + x] ->SetFont(font);
			grid->Add(btn[y * fieldWidth + x], 1, wxEXPAND | wxALL);

			btn[y * fieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);

			field[y * fieldWidth + x] = 0;
		}
	}

	this->SetSizer(grid);
	grid->Layout();

}

cMain::~cMain()
{
	delete[] btn;
}

void cMain::OnButtonClicked(wxCommandEvent& evt)
{
	int x = (evt.GetId() - 10000) % fieldWidth;
	int y = (evt.GetId() - 10000) / fieldHeight;


	//disable pressed button
	btn[y * fieldWidth + x]->Enable(false);

	//if field is empty
	if (field[y * fieldWidth + x] == 0)
	{
		if (currentPlayer == PLAYER)
		{
			field[y * fieldWidth + x] = PLAYER;
			btn[y * fieldWidth + x]->SetLabel("X");
			currentPlayer = AI;
		}
	}


	CheckWinCondition();
	
	//AI move
	
	if (currentPlayer == AI)
	{

		//picking move
		move aiMove = BestMove();
		
		field[aiMove.y * fieldWidth + aiMove.x] = AI;
		btn[aiMove.y * fieldWidth + aiMove.x]->SetLabel("O");
		btn[aiMove.y * fieldWidth + aiMove.x]->Enable(false);

		currentPlayer = PLAYER;
	}

	//modifies winStatus variable
	CheckWinCondition();

	evt.Skip();
}

void cMain::ResetGame()
{
	for (int x = 0; x < fieldWidth; x++)
		for (int y = 0; y < fieldHeight; y++)
		{
			field[y * fieldWidth + x] = EMPTY_SPOT;
			btn[y * fieldWidth + x]->SetLabel("");
			btn[y * fieldWidth + x]->Enable(true);
		}
	currentPlayer = PLAYER;
	winStatus = NO_WIN;
}

int cMain::CheckWinner()
{
	//check rows
	for (int ry = 0; ry < 3; ry++)
	{
		if (field[ry * 3] != EMPTY_SPOT && field[ry * fieldWidth] == field[ry * fieldWidth + 1] && field[ry * fieldWidth + 1] == field[ry * fieldWidth + 2])
		{
			return field[ry * 3];
		}
	}

	//check colums
	for (int rx = 0; rx < 3; rx++)
	{
		if (field[rx] != EMPTY_SPOT &&
			field[0 * fieldWidth + rx] == field[1 * fieldWidth + rx] &&
			field[1 * fieldWidth + rx] == field[2 * fieldWidth + rx])
		{
			return field[rx];
		}
	}

	//check diagonal from top left to bottom right
	if (field[0 * fieldWidth + 0] != EMPTY_SPOT &&
		field[0 * fieldWidth + 0] == field[1 * fieldWidth + 1] &&
		field[1 * fieldWidth + 1] == field[2 * fieldWidth + 2])
	{
		return field[0 * fieldWidth + 0];
	}

	//check diagonal from top right to bottom left
	if (field[0 * fieldWidth + 2] != EMPTY_SPOT &&
		field[0 * fieldWidth + 2] == field[1 * fieldWidth + 1] &&
		field[1 * fieldWidth + 1] == field[2 * fieldWidth + 0])
	{
		return field[0 * fieldWidth + 2];
	}

	//check for Tie
	int turnCount = 0;
	for (int x = 0; x < fieldWidth; x++)
		for (int y = 0; y < fieldHeight; y++)
		{
			if (field[y * fieldWidth + x] != EMPTY_SPOT) turnCount++;
		}
	
	if (turnCount >= 9) return TIE;

	return NO_WIN;
}

void cMain::CheckWinCondition()
{
	//check win condition:
	winStatus = CheckWinner();

	switch (winStatus)
	{
		case NO_WIN:
		{
			break;
		}
		case PLAYER_WIN:
		{
			wxMessageBox("Player has won");
			ResetGame();
			break;
		}
		case AI_WIN:
		{
			wxMessageBox("AI has won");
			ResetGame();
			break;
		}
		case TIE:
		{
			wxMessageBox("Tie!");
			ResetGame();
			break;
		}
		default:
		{
			break;
		}
	}
}

cMain::move cMain::BestMove()
{
	int bestScore = INT_MIN;
	int score = 0;
	move bestMove;

	for (int x = 0; x < fieldWidth; x++)
		for (int y = 0; y < fieldHeight; y++)
		{
			if (field[y * fieldWidth + x] == EMPTY_SPOT)
			{
				field[y * fieldWidth + x] = AI;
				score = MiniMax(field, 10, PLAYER);
				field[y * fieldWidth + x] = EMPTY_SPOT;

				if (score > bestScore)
				{
					bestScore = score;
					bestMove.x = x;
					bestMove.y = y;
				}
			}
		}

	return bestMove;
}


int cMain::MiniMax(int* arr, int depth, int NextPlayer)
{
	int bestScore = INT_MIN;
	int score = INT_MIN;
	
	winStatus = CheckWinner();
	if (winStatus != NO_WIN)
	{
		return winStatus * depth;
	}

	if (NextPlayer == AI)
	{
		bestScore = INT_MIN;
		score = INT_MIN;

		for (int x = 0; x < fieldWidth; x++)
			for (int y = 0; y < fieldHeight; y++)
			{
				if (field[y * fieldWidth + x] == EMPTY_SPOT)
				{
					arr[y * fieldWidth + x] = AI;
					score = MiniMax(arr, depth - 1, PLAYER);
					arr[y * fieldWidth + x] = EMPTY_SPOT;
					bestScore = score > bestScore ? score : bestScore;
				}
			}

		return bestScore;

	}
	else //PLAYER
	{
		bestScore = INT_MAX;
		score = INT_MAX;

		for (int x = 0; x < fieldWidth; x++)
			for (int y = 0; y < fieldHeight; y++)
			{
				if (field[y * fieldWidth + x] == EMPTY_SPOT)
				{
					arr[y * fieldWidth + x] = PLAYER;
					score = MiniMax(arr, depth - 1, AI);
					arr[y * fieldWidth + x] = EMPTY_SPOT;
					bestScore = score < bestScore ? score : bestScore;
				}
			}

		return bestScore;
	}

	
}

