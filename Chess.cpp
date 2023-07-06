#include <iostream>
#include <windows.h>

using namespace std;

class Piece
{
public:
	Piece(char Name, int Team)
	{
		this->name = Name;
		this->team = Team;
	}

	char getname()
	{
		return name;
	}

	int GetTeam()
	{
		return team;
	}

private:
	char name;
	int team;
};

class Chess
{
public:
	Chess()
	{
		ChessBoard = new Piece * *[8];

		for (int i = 0; i < 8; i++)
		{
			ChessBoard[i] = new Piece * [8];
		}
	}

	void InitializeBoard()
	{
		for (int i = 0; i < 8; i += 7)
		{
			if (i == 0)
			{
				ChessBoard[i][0] = new Piece('R', 1);
				ChessBoard[i][1] = new Piece('N', 1);
				ChessBoard[i][2] = new Piece('B', 1);
				ChessBoard[i][3] = new Piece('K', 1);
				ChessBoard[i][4] = new Piece('Q', 1);
				ChessBoard[i][5] = new Piece('B', 1);
				ChessBoard[i][6] = new Piece('N', 1);
				ChessBoard[i][7] = new Piece('R', 1);
			}
			else
			{
				ChessBoard[i][0] = new Piece('R', 2);
				ChessBoard[i][1] = new Piece('N', 2);
				ChessBoard[i][2] = new Piece('B', 2);
				ChessBoard[i][3] = new Piece('K', 2);
				ChessBoard[i][4] = new Piece('Q', 2);
				ChessBoard[i][5] = new Piece('B', 2);
				ChessBoard[i][6] = new Piece('N', 2);
				ChessBoard[i][7] = new Piece('R', 2);
			}
		}

		for (int j = 0; j < 8; j++)
		{
			ChessBoard[1][j] = new Piece('P', 1);
			ChessBoard[6][j] = new Piece('P', 2);
		}

		for (int x = 0; x < 8; x++)
		{
			for (int y = 2; y < 6; y++)
			{
				ChessBoard[y][x] = nullptr;
			}
		}
	}

	void Run()
	{
		while (IsRunning)
		{
			Display();
			HandleInput();
		}
	}

	void HandleInput()
	{
		cout << endl;
		cout << "말을 선택하세요" << endl;
		int x0, y0;
		cin >> x0 >> y0;



		cout << "말을 이동시킬 장소를 선택하세요" << endl;
		int x1, y1;
		cin >> x1 >> y1;


		MovePiece(x0, y0, x1, y1);
	}

	void MovePiece(int x0, int y0, int x1, int y1)
	{
		Piece* piece = ChessBoard[x0][y0];

		if (x1 < 0 || x1 > 7 || y1 < 0 || y1 > 7) {
			cout << "유효하지 않은 위치입니다." << endl;
			return;
		}

		if (piece == nullptr)
		{
			cout << "선택한 위치에 말이 없습니다." << endl;
			return;
		}

		if (!IsValidMove(x0, y0, x1, y1))
		{
			cout << "유효하지 않은 이동입니다." << endl;
			return;
		}

		// 이동 실행
		ChessBoard[x1][y1] = piece;
		ChessBoard[x0][y0] = nullptr;

		cout << "말을 이동했습니다." << endl;
	}

	bool IsValidMove(int x0, int y0, int x1, int y1)
	{
		Piece* piece = ChessBoard[x0][y0];
		if (piece == nullptr)
		{
			return false;
		}

		switch (piece->getname())
		{
		case 'P': // 폰은 처음만 두 칸, 그 다음에는 한 칸만 이동 가능
			if (piece->GetTeam() == 1)	// 팀을 확인, 위에 있는 빨강팀일 경우
			{
				if (x0 == 1 && x1 == 3 && y0 == y1 && ChessBoard[2][y1] == nullptr)	
				// 두 칸 가고싶을 때
				// 빨강팀일 경우 x0(말이 있는 곳)가 1(움직이지 않은 자리라면)이고 움직일 곳이 두칸 앞이면서 가로축이 움직이지 않았으며 움직일 자리가 비어있다면
				{
					return true;	// 움직인다.
				}
				else if (x1 == x0 + 1 && abs(y1 - y0) == 1 && ChessBoard[x1][y1] != nullptr && ChessBoard[x1][y1]->GetTeam() != piece->GetTeam())
				// 움직이는 장소에 다른 말이 있을 경우
				// 빨강팀의 경우 x1(가고싶은 곳)이 x0(원래 말이 있던 자리)랑 1 차이가 나면서, x1.y1(말이 갈 곳)이 비어있지 않으면서 
				// 현재 팀(지금은 빨강)이랑 팀이 다르면(움직일 장소에 초록말이 있다면)
				{
					delete ChessBoard[x1][y1];
					return true;
				}
				else if (x1 == x0 + 1 && y0 == y1 && ChessBoard[x1][y1] == nullptr)
				// 한 칸 가고싶을때
				// 빨강팀일 경우 x1(가고싶은 곳)이 x0(원래 말이 있던 자리)랑 1차이가 나면서 가로축이 움직이지 않았으면서, x1.y1(말이 갈 곳)이 비어있다면
				{
					return true;	// 움직인다.
				}
			}
			else if (piece->GetTeam() == 2) // 팀을 확인, 밑에 있는 초록팀일 경우
			{
				if (x0 == 6 && x1 == 4 && y0 == y1 && ChessBoard[5][y1] == nullptr)
				{
					return true;
				}
				else if (x1 == x0 - 1 && abs(y1 - y0) == 1 && ChessBoard[x1][y1] != nullptr && ChessBoard[x1][y1]->GetTeam() != piece->GetTeam())
				{
					return true;
				}
				else if (x1 == x0 - 1 && y0 == y1 && ChessBoard[x1][y1] == nullptr)
				{
					return true;
				}
			}
			break;

		case 'R': // 룩은 십자 방향으로 쭉쭉 다님. 
			if (x0 == x1 || y0 == y1) {		// 같은 줄에서 움직이는지 검사.
				if (x0 == x1) {	// 이동경로가 가로축에서만 움직인다면
					int minY = min(y0, y1);	// 가로 이동경로에서의 최소값을 구하기 위함
					int maxY = max(y0, y1); // 가로 이동경로에서의 최대값을 구하기 위함
					for (int y = minY + 1; y < maxY; ++y) {	// for문을 통해 가로축의 최소값과 최대값 사이의 데이터 검사 
						if (ChessBoard[x0][y] != nullptr) {	// 이동 경로에 다른 말이 있다면
							cout << "다른 말을 통과할 수 없습니다." << endl;	// 다른 말을 통과할 수 없다고 찍고 원위치.
							return false;
						}
					}
				}
				else {	// 아닐 경우, 세로 줄에서만 다닌다는 말.
					int minX = min(x0, x1);	// 세로 이동경로에서 최소값을 구함
					int maxX = max(x0, x1);	// 세로 이동경로에서 최대값을 구함
					for (int x = minX + 1; x < maxX; ++x) {	// for문을 통해 세로축의 최소값과 최대값 사이 데이터 검사
						if (ChessBoard[x][y0] != nullptr) {	// 이동경로에 다른 말이 있다면
							cout << "다른 말을 통과할 수 없습니다." << endl;	// 다른 말을 통과할 수 없다 찍고 원위치
							return false;
						}
					}
				}
				if (ChessBoard[x1][y1] != nullptr) {
					delete ChessBoard[x1][y1];
					ChessBoard[x1][y1] = nullptr;
				}
				return true;
			}

		case 'N': // 나이트는 L자 형태로 움직인다.
		// 이동 방향에 따라 수평으로 2칸 이동, 수직으로 1칸 이동 or 수직으로 2칸 이동, 수평으로 1칸 이동
		{
			int dx = abs(x1 - x0);	// 이동거리 계산을 위해 현재위치 x0값과 움직일 위치 x1값의 절대값을 구함.
			int dy = abs(y1 - y0);	// 이동거리 계산을 위해 현재위치 y0값과 움직일 위치 y1값의 절대값을 구함.
			if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) {	
			// 나이트의 이동규칙에 부합하는지 확인
				if (ChessBoard[x1][y1] == nullptr || ChessBoard[x1][y1]->GetTeam() != piece->GetTeam()) {
				// 움직일 곳에 다른 말이 없거나, 현재 말과 목표 위치에 있는 말이 서로 다른 팀에 속하는지 확인.
					return true;	// 맞으면 위치 옮기기.
				}
				else if (ChessBoard[x1][y1]->GetTeam() != piece->GetTeam()) {
				// 목표 위치에 상대 팀의 말이 있는 경우
					delete ChessBoard[x1][y1];  // 상대 말 제거
					ChessBoard[x1][y1] = nullptr;  // 해당 위치를 비움
					return true;
				}
				else {
					cout << "같은 팀의 말이 있는 위치로는 이동할 수 없습니다." << endl;
				}
			}
			else {
				cout << "유효하지 않은 이동입니다." << endl;
			}
			break;
		}

		case 'B': // 비숍은 대각선으로만 움직임.
		{
			int bx, by;	// 이동거리 방향 결정을 위해 가로축(x0,x1)와 세로축(y,y1)의 차이를 저장하기 위한 변수 설정 
			bx = (x1 > x0) ? 1 : -1;	// bx에 값을 넣어줌. 움직일 목표좌표 x1이 현재 위치 x0보다 크면 1, 아니면 -1
			by = (y1 > y0) ? 1 : -1;	// by에 값을 넣어줌. 움직일 목표좌표 y1이 현재 위치 y0보다 크면 1, 아니면 -1
			if (abs(x1 - x0) == abs(y1 - y0)) {	// x축 이동값과 y축 이동값이 같아야 대각선으로 이동하므로 조건문에 가로,세로 이동거리가 같은지 검사
				int x = x0 + bx;	// 차이가 같다면 대각선 방향으로 움직여야 되니까 가로축 변수 x에 초기값x0와 이동방향bx를 더해줌
				int y = y0 + by;	// 차이가 같다면 대각선 방향으로 움직여야 되니까 세로축 변수 y에 초기값y0와 이동방향by를 더해줌
				while (x != x1 && y != y1) {	// 비숍의 위치를 x+bx, y+by까지 업데이트 하면서 대각선 방향으로 계속 이동
					if (ChessBoard[x][y] != nullptr) {	// 다른 말이 있는지를 확인함. 막히면 더 못가니까.
						cout << "다른 말을 통과할 수 없습니다." << endl;
						return false;
					}
					x += bx;	// x값 증가. 한 칸 이동해서 다시 검사
					y += by;	// y값 증가. 한 칸 이동해서 다시 검사
				}
				// 이동할 위치에 다른 말이 없거나, 다른 팀의 말이 있는 경우 해당 말을 잡고 그 좌표 먹음.
				if (ChessBoard[x1][y1] == nullptr || ChessBoard[x1][y1]->GetTeam() != piece->GetTeam()) {
					if (ChessBoard[x1][y1] != nullptr) {
						delete ChessBoard[x1][y1];
						ChessBoard[x1][y1] = nullptr;
					}
					return true;
				}
				else {
					cout << "같은 팀의 말이 있는 위치로는 이동할 수 없습니다." << endl;
				}
			}
			else {
				cout << "유효하지 않은 이동입니다." << endl;
			}
			break;
		}

		case 'Q':
		{
			
		}
		case 'K': // 킹
		{
			// 킹의 움직임 처리, 킹은 상하좌우와 대각선 단 한 칸씩만 움직일 수 있다.
			if (abs(x1 - x0) <= 1 && abs(y1 - y0) <= 1)	// 현재 좌표 값과 목표값의 차가 1일 경우에만 움직일 수 있다. 
			{
				if (ChessBoard[x1][y1] != nullptr && ChessBoard[x1][y1]->GetTeam() != piece->GetTeam())
				// 킹이 움직이는 자리가 nullptr이 아니고(다른 말이 있는 것이니까) 목표좌표의 팀이 움직이는 말의 팀과 다르다면 
				{
					delete ChessBoard[x1][y1];	// 해당 말을 지운다.
					ChessBoard[x1][y1] = nullptr;	// 해당 배열자리에 있는 값을 nullptr로 바꿔준다
				}
				return true;
			}
			else
			{
				cout << "유효하지 않은 이동입니다." << endl;
				return false;
			}
		}


		}

		return false;
	}

	void Display()
	{
		// system("cls");
		for (int i = 0; i < 8; i++)
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << 8 - i << " ";
			for (int j = 0; j < 8; j++)
			{
				if (ChessBoard[i][j] != nullptr && ChessBoard[i][j]->GetTeam() == 1)
				{
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
					cout << ChessBoard[i][j]->getname() << ' ';
				}
				else if (ChessBoard[i][j] != nullptr && ChessBoard[i][j]->GetTeam() == 2)
				{
					SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
					cout << ChessBoard[i][j]->getname() << ' ';
				}
				else
				{
					cout << ' ' << ' ';
				}
			}
			cout << endl;
		}
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "  ";
		for (int i = 0; i < 8; i++)
		{
			cout << (char)('a' + i) << " ";
		}
		cout << endl;
	}

private:
	Piece*** ChessBoard;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	bool IsRunning = true;
};

int main()
{
	Chess MyChess;
	MyChess.InitializeBoard();
	MyChess.Run();

	return 0;
}
