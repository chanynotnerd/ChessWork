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
		cout << "���� �����ϼ���" << endl;
		int x0, y0;
		cin >> x0 >> y0;



		cout << "���� �̵���ų ��Ҹ� �����ϼ���" << endl;
		int x1, y1;
		cin >> x1 >> y1;


		MovePiece(x0, y0, x1, y1);
	}

	void MovePiece(int x0, int y0, int x1, int y1)
	{
		Piece* piece = ChessBoard[x0][y0];

		if (x1 < 0 || x1 > 7 || y1 < 0 || y1 > 7) {
			cout << "��ȿ���� ���� ��ġ�Դϴ�." << endl;
			return;
		}

		if (piece == nullptr)
		{
			cout << "������ ��ġ�� ���� �����ϴ�." << endl;
			return;
		}

		if (!IsValidMove(x0, y0, x1, y1))
		{
			cout << "��ȿ���� ���� �̵��Դϴ�." << endl;
			return;
		}

		// �̵� ����
		ChessBoard[x1][y1] = piece;
		ChessBoard[x0][y0] = nullptr;

		cout << "���� �̵��߽��ϴ�." << endl;
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
		case 'P': // ���� ó���� �� ĭ, �� �������� �� ĭ�� �̵� ����
			if (piece->GetTeam() == 1)	// ���� Ȯ��, ���� �ִ� �������� ���
			{
				if (x0 == 1 && x1 == 3 && y0 == y1 && ChessBoard[2][y1] == nullptr)	
				// �� ĭ ������� ��
				// �������� ��� x0(���� �ִ� ��)�� 1(�������� ���� �ڸ����)�̰� ������ ���� ��ĭ ���̸鼭 �������� �������� �ʾ����� ������ �ڸ��� ����ִٸ�
				{
					return true;	// �����δ�.
				}
				else if (x1 == x0 + 1 && abs(y1 - y0) == 1 && ChessBoard[x1][y1] != nullptr && ChessBoard[x1][y1]->GetTeam() != piece->GetTeam())
				// �����̴� ��ҿ� �ٸ� ���� ���� ���
				// �������� ��� x1(������� ��)�� x0(���� ���� �ִ� �ڸ�)�� 1 ���̰� ���鼭, x1.y1(���� �� ��)�� ������� �����鼭 
				// ���� ��(������ ����)�̶� ���� �ٸ���(������ ��ҿ� �ʷϸ��� �ִٸ�)
				{
					delete ChessBoard[x1][y1];
					return true;
				}
				else if (x1 == x0 + 1 && y0 == y1 && ChessBoard[x1][y1] == nullptr)
				// �� ĭ ���������
				// �������� ��� x1(������� ��)�� x0(���� ���� �ִ� �ڸ�)�� 1���̰� ���鼭 �������� �������� �ʾ����鼭, x1.y1(���� �� ��)�� ����ִٸ�
				{
					return true;	// �����δ�.
				}
			}
			else if (piece->GetTeam() == 2) // ���� Ȯ��, �ؿ� �ִ� �ʷ����� ���
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

		case 'R': // ���� ���� �������� ���� �ٴ�. 
			if (x0 == x1 || y0 == y1) {		// ���� �ٿ��� �����̴��� �˻�.
				if (x0 == x1) {	// �̵���ΰ� �����࿡���� �����δٸ�
					int minY = min(y0, y1);	// ���� �̵���ο����� �ּҰ��� ���ϱ� ����
					int maxY = max(y0, y1); // ���� �̵���ο����� �ִ밪�� ���ϱ� ����
					for (int y = minY + 1; y < maxY; ++y) {	// for���� ���� �������� �ּҰ��� �ִ밪 ������ ������ �˻� 
						if (ChessBoard[x0][y] != nullptr) {	// �̵� ��ο� �ٸ� ���� �ִٸ�
							cout << "�ٸ� ���� ����� �� �����ϴ�." << endl;	// �ٸ� ���� ����� �� ���ٰ� ��� ����ġ.
							return false;
						}
					}
				}
				else {	// �ƴ� ���, ���� �ٿ����� �ٴѴٴ� ��.
					int minX = min(x0, x1);	// ���� �̵���ο��� �ּҰ��� ����
					int maxX = max(x0, x1);	// ���� �̵���ο��� �ִ밪�� ����
					for (int x = minX + 1; x < maxX; ++x) {	// for���� ���� �������� �ּҰ��� �ִ밪 ���� ������ �˻�
						if (ChessBoard[x][y0] != nullptr) {	// �̵���ο� �ٸ� ���� �ִٸ�
							cout << "�ٸ� ���� ����� �� �����ϴ�." << endl;	// �ٸ� ���� ����� �� ���� ��� ����ġ
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

		case 'N': // ����Ʈ�� L�� ���·� �����δ�.
		// �̵� ���⿡ ���� �������� 2ĭ �̵�, �������� 1ĭ �̵� or �������� 2ĭ �̵�, �������� 1ĭ �̵�
		{
			int dx = abs(x1 - x0);	// �̵��Ÿ� ����� ���� ������ġ x0���� ������ ��ġ x1���� ���밪�� ����.
			int dy = abs(y1 - y0);	// �̵��Ÿ� ����� ���� ������ġ y0���� ������ ��ġ y1���� ���밪�� ����.
			if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) {	
			// ����Ʈ�� �̵���Ģ�� �����ϴ��� Ȯ��
				if (ChessBoard[x1][y1] == nullptr || ChessBoard[x1][y1]->GetTeam() != piece->GetTeam()) {
				// ������ ���� �ٸ� ���� ���ų�, ���� ���� ��ǥ ��ġ�� �ִ� ���� ���� �ٸ� ���� ���ϴ��� Ȯ��.
					return true;	// ������ ��ġ �ű��.
				}
				else if (ChessBoard[x1][y1]->GetTeam() != piece->GetTeam()) {
				// ��ǥ ��ġ�� ��� ���� ���� �ִ� ���
					delete ChessBoard[x1][y1];  // ��� �� ����
					ChessBoard[x1][y1] = nullptr;  // �ش� ��ġ�� ���
					return true;
				}
				else {
					cout << "���� ���� ���� �ִ� ��ġ�δ� �̵��� �� �����ϴ�." << endl;
				}
			}
			else {
				cout << "��ȿ���� ���� �̵��Դϴ�." << endl;
			}
			break;
		}

		case 'B': // ����� �밢�����θ� ������.
		{
			int bx, by;	// �̵��Ÿ� ���� ������ ���� ������(x0,x1)�� ������(y,y1)�� ���̸� �����ϱ� ���� ���� ���� 
			bx = (x1 > x0) ? 1 : -1;	// bx�� ���� �־���. ������ ��ǥ��ǥ x1�� ���� ��ġ x0���� ũ�� 1, �ƴϸ� -1
			by = (y1 > y0) ? 1 : -1;	// by�� ���� �־���. ������ ��ǥ��ǥ y1�� ���� ��ġ y0���� ũ�� 1, �ƴϸ� -1
			if (abs(x1 - x0) == abs(y1 - y0)) {	// x�� �̵����� y�� �̵����� ���ƾ� �밢������ �̵��ϹǷ� ���ǹ��� ����,���� �̵��Ÿ��� ������ �˻�
				int x = x0 + bx;	// ���̰� ���ٸ� �밢�� �������� �������� �Ǵϱ� ������ ���� x�� �ʱⰪx0�� �̵�����bx�� ������
				int y = y0 + by;	// ���̰� ���ٸ� �밢�� �������� �������� �Ǵϱ� ������ ���� y�� �ʱⰪy0�� �̵�����by�� ������
				while (x != x1 && y != y1) {	// ����� ��ġ�� x+bx, y+by���� ������Ʈ �ϸ鼭 �밢�� �������� ��� �̵�
					if (ChessBoard[x][y] != nullptr) {	// �ٸ� ���� �ִ����� Ȯ����. ������ �� �����ϱ�.
						cout << "�ٸ� ���� ����� �� �����ϴ�." << endl;
						return false;
					}
					x += bx;	// x�� ����. �� ĭ �̵��ؼ� �ٽ� �˻�
					y += by;	// y�� ����. �� ĭ �̵��ؼ� �ٽ� �˻�
				}
				// �̵��� ��ġ�� �ٸ� ���� ���ų�, �ٸ� ���� ���� �ִ� ��� �ش� ���� ��� �� ��ǥ ����.
				if (ChessBoard[x1][y1] == nullptr || ChessBoard[x1][y1]->GetTeam() != piece->GetTeam()) {
					if (ChessBoard[x1][y1] != nullptr) {
						delete ChessBoard[x1][y1];
						ChessBoard[x1][y1] = nullptr;
					}
					return true;
				}
				else {
					cout << "���� ���� ���� �ִ� ��ġ�δ� �̵��� �� �����ϴ�." << endl;
				}
			}
			else {
				cout << "��ȿ���� ���� �̵��Դϴ�." << endl;
			}
			break;
		}

		case 'Q':
		{
			
		}
		case 'K': // ŷ
		{
			// ŷ�� ������ ó��, ŷ�� �����¿�� �밢�� �� �� ĭ���� ������ �� �ִ�.
			if (abs(x1 - x0) <= 1 && abs(y1 - y0) <= 1)	// ���� ��ǥ ���� ��ǥ���� ���� 1�� ��쿡�� ������ �� �ִ�. 
			{
				if (ChessBoard[x1][y1] != nullptr && ChessBoard[x1][y1]->GetTeam() != piece->GetTeam())
				// ŷ�� �����̴� �ڸ��� nullptr�� �ƴϰ�(�ٸ� ���� �ִ� ���̴ϱ�) ��ǥ��ǥ�� ���� �����̴� ���� ���� �ٸ��ٸ� 
				{
					delete ChessBoard[x1][y1];	// �ش� ���� �����.
					ChessBoard[x1][y1] = nullptr;	// �ش� �迭�ڸ��� �ִ� ���� nullptr�� �ٲ��ش�
				}
				return true;
			}
			else
			{
				cout << "��ȿ���� ���� �̵��Դϴ�." << endl;
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
