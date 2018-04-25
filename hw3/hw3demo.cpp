#include <cstdio>
#include <vector>
#include <cstring>

const char kFormat[] =
"      1 | 2 | 3 | 4 | 5\n"
"O %c\\ O %c|O %c|O %c|O %c|O %c /O %c\n"
" X %c\\X %c|X %c|X %c|X %c|X %c/X %c\n"
"----+---+---+---+---+---+\n"
"O %c | %c | %c | %c | %c | %c | 1\n"
"X %c/+---+---+---+---+---+\n"
"O %c | %c | %c | %c | %c | %c | 2\n"
"X %c/+---+---+---+---+---+\n"
"O %c | %c | %c | %c | %c | %c | 3\n"
"X %c/+---+---+---+---+---+\n"
"O %c | %c | %c | %c | %c | %c | 4\n"
"X %c/+---+---+---+---+---+    O:%d\n"
"O %c | %c | %c | %c | %c | %c | 5  X:%d\n"
"X %c/+---+---+---+---+---+\n";

class Board {
  char c[5][5];
  int round_;
public:
  Board() : round_(0) { memset(c, ' ', sizeof(c)); };

  int OutputBoard() const {
    char a[12], b[12];
    int sO = 0, sX = 0;
    memset(a, 0, sizeof(a)); memset(b, 0, sizeof(b));
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        if (c[i][j] == ' ') continue;
        char* z = c[i][j] == 'O' ? a : b;
        z[j + 1]++; z[i + 7]++;
        if (i == j) z[0]++;
        if (i == 4 - j) z[6]++;
      }
    }
    for (int i = 0; i < 12; i++) {
      if (a[i] >= 4) sO++;
      else if (b[i] >= 4) sX++;
      bool flaga = false, flagb = false;
      if (a[i] >= 2) flagb = true;
      if (b[i] >= 2) flaga = true;
      a[i] = flaga ? '-' : a[i] ^ '0';
      b[i] = flagb ? '-' : b[i] ^ '0';
    }
    printf(kFormat,
           a[0],a[1],a[2],a[3],a[4],a[5],a[6],
           b[0],b[1],b[2],b[3],b[4],b[5],b[6],
           a[7],c[0][0],c[0][1],c[0][2],c[0][3],c[0][4],b[7],
           a[8],c[1][0],c[1][1],c[1][2],c[1][3],c[1][4],b[8],
           a[9],c[2][0],c[2][1],c[2][2],c[2][3],c[2][4],b[9],
           a[10],c[3][0],c[3][1],c[3][2],c[3][3],c[3][4],b[10],sO,
           a[11],c[4][0],c[4][1],c[4][2],c[4][3],c[4][4],sX,b[11]);
    return sO >= sX ? sO > sX : -1;
  };

  int Round() const { return round_; }
  bool Finished() const { return round_ == 11; }
  void Finish() {
    for (int i = 0; i < 5; i++)
      for (int j = 0; j < 5; j++)
        if (c[i][j] == ' ') c[i][j] = 'X';
  }
  bool Play(int x1, int y1, int x2, int y2) {
    auto Valid = [](int z){return z > 0 && z <= 5;};
    if (!(Valid(x1) && Valid(y1) && Valid(x2) && Valid(y2)) ||
        (x1 == x2 && y1 == y2) ||
        c[--x1][--y1] != ' ' || c[--x2][--y2] != ' ') return false;
    c[x1][y1] = c[x2][y2] = (round_++ & 1) ? 'X' : 'O';
    return true;
  }
};


int main()
{
  const int buf_size = 2003;
  char input[buf_size];
  setvbuf(stdout, nullptr, _IONBF, 0);
  for (bool nextgame = true; nextgame;) {
    std::vector<Board> history(1);
    bool output = true;
    for (; !history.back().Finished();) {
      if (output) history.back().OutputBoard();
      history.push_back(history.back());
      printf("Enter your 2 pairs of (row, col) [space delim] or u to undo>");

      output = true;
      fgets(input, buf_size, stdin);
      if (input[0] == 'u' || input[0] == 'U') {
        history.pop_back();
        if (history.size() >= 2) history.pop_back();
        else puts("Can't undo"), output = false;
      } else {
        int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
        sscanf(input, "%d%d%d%d", &x1, &y1, &x2, &y2);
        if (!history.back().Play(x1, y1, x2, y2)) {
          puts("Invalid move");
          output = false;
          history.pop_back();
        }
      }
    }
    history.back().Finish();
    int res = history.back().OutputBoard();
    puts(res ? res > 0 ? "O win!" : "X win!" : "Draw!");

    for (;;) {
      printf("One more game? (y/n)>");
      fgets(input, buf_size, stdin);
      if (input[0] == 'Y' || input[0] == 'y') {
        break;
      } else if (input[0] == 'N' || input[0] == 'n') {
        nextgame = false;
        break;
      } else {
        puts("Invalid input");
      }
    }
  }
}
