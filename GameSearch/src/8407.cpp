#include <ncurses.h>
#include <unistd.h>

int main(int argc, char **argv) {
  initscr();
  noecho();    // 입력한 문자 화면에 출력하지 않음
  curs_set(0); // 커서 숨김

  int x = 10, y = 10; // 사각형의 초기 위치
  int width = 5, height = 3;

  while (1) {
    // 이전 사각형 지우기
    mvprintw(y, x, " ");
    mvprintw(y + height - 1, x, " ");
    for (int i = 1; i < height - 1; i++) {
      mvprintw(y + i, x, " ");
      mvprintw(y + i, x + width - 1, " ");
    }

    // 사각형 이동
    x++;

    // 화면 가장자리에 도달하면 방향 변경
    if (x + width >= COLS) {
      x = 0;
    }

    // 새로운 위치에 사각형 그리기
    mvprintw(y, x, "+");
    mvprintw(y + height - 1, x, "+");
    for (int i = 1; i < height - 1; i++) {
      mvprintw(y + i, x, "|");
      mvprintw(y + i, x + width - 1, "|");
    }

    refresh();
    usleep(100000); // 0.1초 지연
  }

  endwin();
  return 0;
}
