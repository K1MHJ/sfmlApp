#include <fcntl.h>
#include <iostream>
#include <ncurses.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include "game.h"

using std::cout;
using std::endl;

std::chrono::high_resolution_clock::time_point lastUpdateTime;

bool EventTriggered(int interval) {
  std::chrono::high_resolution_clock::time_point currentTime =
      std::chrono::high_resolution_clock::now();
  auto diff = currentTime - lastUpdateTime;
  if (std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() >=
      interval) {
    lastUpdateTime = currentTime;
    return true;
  }
  return false;
};

void rectangle(int y1, int x1, int y2, int x2) {
  mvhline(y1, x1, 0, x2 - x1);
  mvhline(y2, x1, 0, x2 - x1);
  mvvline(y1, x1, 0, y2 - y1);
  mvvline(y1, x2, 0, y2 - y1);
  mvaddch(y1, x1, ACS_ULCORNER);
  mvaddch(y2, x1, ACS_LLCORNER);
  mvaddch(y1, x2, ACS_URCORNER);
  mvaddch(y2, x2, ACS_LRCORNER);
};
constexpr const int _TEXT = 0;
constexpr const int _WIN_BORDER = 1;
constexpr const int _WIN_TEXT = 2;
#define COLOR(x) COLOR_PAIR(x)

WINDOW *win;
int main() {
  /* initialize curses */
  initscr();
  win = newwin(30, 50, 1, 1);
  start_color();

  init_pair(_TEXT, COLOR_WHITE, COLOR_BLACK);
  init_pair(_WIN_BORDER, COLOR_YELLOW, COLOR_BLACK);
  init_pair(_WIN_TEXT, COLOR_WHITE, COLOR_BLACK);

  init_pair(10 + 1, COLOR_WHITE, COLOR_RED);
  init_pair(10 + 2, COLOR_WHITE, COLOR_GREEN);
  init_pair(10 + 3, COLOR_RED, COLOR_YELLOW);
  init_pair(10 + 4, COLOR_WHITE, COLOR_BLUE);
  init_pair(10 + 5, COLOR_WHITE, COLOR_MAGENTA);
  init_pair(10 + 6, COLOR_WHITE, COLOR_CYAN);
  init_pair(10 + 7, COLOR_WHITE, COLOR_WHITE);

  wattron(win, COLOR(_WIN_BORDER));
  box(win, 0, 0);
  // wmove(win, 2, 1); // set cursor
  //  whline(win, 'x', 10); // draw line from current cursor
  wattroff(win, COLOR(_WIN_BORDER));
  noecho();    // 입력한 문자 화면에 출력하지 않음
  curs_set(0); // 커서 숨김
  mvwprintw(win, 1, 1, "Press Q key to stop.");

  wattron(win, COLOR(_WIN_BORDER));
  mvwprintw(win, 5, 30, "Score");
  mvwprintw(win, 6, 30, "Next");

  lastUpdateTime = std::chrono::high_resolution_clock::now();
  Game game = Game();
  bool running = true;
  while (running) {
    game.HandleInput();
    if (game.gameTerminate) {
      running = false;
    }
    if (game.gameOver) {
      mvwprintw(win, 3, 30, "GAME OVER");
    }
    if (EventTriggered(20)) {
      game.MoveBlockDown();
    }
    char scoreText[10];
    snprintf(scoreText, 10, "%d", game.score);
    mvwprintw(win, 5, 40, "%s", scoreText);
    game.Draw();
    wrefresh(win);
  }
  endwin();
}
