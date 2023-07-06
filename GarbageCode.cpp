#include <iostream>
#include <windows.h>

using namespace std;
class Piece
{
public:
Piece(char Name, int Team) {
    this->name = Name;
    this->team = Team;
}


    char getname() {
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
        ChessBoard = new Piece** [9];

        for (int i = 0; i < 9; i++) {
            ChessBoard[i] = new Piece* [9];
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
        if (piece == nullptr) {
            cout << "������ ��ġ�� ���� �����ϴ�." << endl;
            return;
        }

        if (!IsValidMove(x0, y0, x1, y1)) {
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
        if (piece == nullptr) {
            return false;
        }

        switch (piece->getname()) { // ü������ �̵�
            case 'P':   // ���� ó���� �� ĭ, �� ��
                 if (piece->GetTeam() == 1) {  

              }
                 else if (piece->GetTeam() == 2) { 
 
             }
             break;
             case 'R': 
                 if (piece->GetTeam() == 1) {

                 }
                 else if (piece->GetTeam() == 2) {

                 }
            
            break;
            // �ٸ� ���� �̵� ��Ģ�� ���� ����
        }

        return true;
    }


    void Display()
    {
        system("cls");
        for (int i = 0; i < 8; i++) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            cout << 8 - i << " ";
            for (int j = 0; j < 8; j++) {
                if (ChessBoard[i][j] != nullptr && ChessBoard[i][j]->GetTeam() == 1) {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    cout << ChessBoard[i][j]->getname();
                }
                if (ChessBoard[i][j] != nullptr && ChessBoard[i][j]->GetTeam() == 2) {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    cout << ChessBoard[i][j]->getname();
                }
                if (ChessBoard[i][j] != nullptr && ChessBoard[i][j]->GetTeam() == 3) {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
                    cout << ChessBoard[i][j]->getname() << ' ';
                }
                else
                {
                    cout << ' ';
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


int main() {

    Chess MyChess;
    MyChess.InitializeBoard();
    MyChess.Run();
    MyChess.Display();

}