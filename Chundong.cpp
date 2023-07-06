#include <iostream>
#include <windows.h>

using namespace std;



class Piece
{
private:
   char Name;
   int Team;
public:

   Piece(char Name, int Team)
   {
      this->Name = Name;
      this->Team = Team;
   }

   int GetTeam()
   {
      return Team;
   }

   char GetName()
   {
      return Name;
   }
};

class Chess
{
private:
   Piece* ChessBoard[8][8];
   Piece*** HeapBoard;

public:
   Chess()
   {
      HeapBoard = new Piece * *[8];
      for (int i = 0; i < 8; i++)
      {
         HeapBoard[i] = new Piece * [8];
      }
   }

   HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

   void InitializeBoard()
   {
      for (int i = 0; i < 8; i += 7)
      {
         if (i == 0)
         {
            HeapBoard[i][0] = new Piece('R', 1);
            HeapBoard[i][1] = new Piece('N', 1);
            HeapBoard[i][2] = new Piece('B', 1);
            HeapBoard[i][3] = new Piece('K', 1);
            HeapBoard[i][4] = new Piece('Q', 1);
            HeapBoard[i][5] = new Piece('B', 1);
            HeapBoard[i][6] = new Piece('N', 1);
            HeapBoard[i][7] = new Piece('R', 1);
         }
         else
         {
            HeapBoard[i][0] = new Piece('R', 2);
            HeapBoard[i][1] = new Piece('N', 2);
            HeapBoard[i][2] = new Piece('B', 2);
            HeapBoard[i][3] = new Piece('K', 2);
            HeapBoard[i][4] = new Piece('Q', 2);
            HeapBoard[i][5] = new Piece('B', 2);
            HeapBoard[i][6] = new Piece('N', 2);
            HeapBoard[i][7] = new Piece('R', 2);
         }
      }

      for (int j = 0; j < 8; j++)
      {
         HeapBoard[1][j] = new Piece('P', 1);
         HeapBoard[6][j] = new Piece('P', 2);
      }

      for (int x = 0; x < 8; x++)
      {
         for (int y = 2; y < 6; y++)
         {
            HeapBoard[y][x] = nullptr;
         }
      }
   }

   void DisPlay()
   {
      for (int i = 0; i < 8; i++)
      {
         for (int j = 0; j < 8; j++)
         {
            if (HeapBoard[i][j] != nullptr && HeapBoard[i][j]->GetTeam() == 1)
            {
               SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
               cout << HeapBoard[i][j]->GetName() << ' ';
            }
            else if (HeapBoard[i][j] != nullptr && HeapBoard[i][j]->GetTeam() == 2)
            {
               SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
               cout << HeapBoard[i][j]->GetName() << ' ';
            }
            else
            {
               SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
               cout << "  ";
            }
         }
         cout << endl;
      }
   }

   void SetPiece(int i, int j, int x, int y)
   {
      if (HeapBoard[i][j]->GetName() == 'P')
      {
         if (x < i)
         {
            cout << "해당 말은 뒤로 움직일 수 없습니다." << endl;
         }
         else
         {
            if (HeapBoard[x][y] != nullptr)
            {
               if (HeapBoard[i][j]->GetTeam() == HeapBoard[x][y]->GetTeam())
               {
                  cout << "같은 팀의 말을 넘을 수 없습니다." << endl;
               }
               else
               {
                  cout << "상대방의 말을 잡았습니다. " << HeapBoard[x][y]->GetName() << endl;
                  HeapBoard[x][y] = HeapBoard[i][j];
                  HeapBoard[i][j] = nullptr;
                  DisPlay();
               }
            }
            else
            {
               cout << "말이 이동하였습니다." << endl;
               HeapBoard[x][y] = HeapBoard[i][j];
               HeapBoard[i][j] = nullptr;
               DisPlay();
            }
         }
      }
      else
      {
         if (HeapBoard[x][y] != nullptr)
         {
            cout << "상대방의 말을 잡았습니다. " << HeapBoard[x][y] << endl;
            HeapBoard[x][y] = HeapBoard[i][j];
            HeapBoard[i][j] = nullptr;
            DisPlay();
         }
         else
         {
            cout << "말이 이동하였습니다." << endl;
            HeapBoard[x][y] = HeapBoard[i][j];
            HeapBoard[i][j] = nullptr;
            DisPlay();

         }
      }
   }
};

class ChessGame
{
private:
   int Count;
   char Piece;
   int numi;
   int numj;
   int numx;
   int numy;

public:

   Chess* ChessBoard = new Chess;
   char Choice;

   void Game()
   {
      ChessBoard->InitializeBoard();
      ChessBoard->DisPlay();
      Count = 0;

      while (true)
      {
         cout << Count << "번째 행동을 정해주세요. 종료-e, 세트-p" << endl;
         cin >> Choice;
         if (Choice == 'e')
         {
            break;
         }
         else if (Choice == 'p')
         {
            cout << "이동시킬 말을 정해주세요." << endl;
            cout << "이동시킬 말의 위치:" << endl;
            cin >> numi;
            cin >> numj;
            cout << "이동할 위치:" << endl;
            cin >> numx;
            cin >> numy;
            ChessBoard->SetPiece(numi, numj, numx, numy);
         }
      }
   }

};


int main()
{
   ChessGame* Chessgame = new ChessGame;
   Chessgame->Game();

   return 0;
}