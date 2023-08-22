#include <bits/stdc++.h>
#include <termios.h>

#include <cctype>
#include <condition_variable>
#include <thread>

void input_enter_off(termios& t) {
  tcgetattr(STDIN_FILENO, &t);
  t.c_lflag &= ~ICANON;
  tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

int main(int argc, char const* argv[]) {
  bool pause = false;
  int cnt = 0;
  std::mutex m;
  std::condition_variable cv;
  termios t;

  input_enter_off(t);
  std::thread thread([&pause, &cv]() {
    while (true) {
      char key = getchar();
      if (key == 0x20) {
        pause = !pause;
        cv.notify_all();
      }
    }
  });
  while (true) {
    std::unique_lock lk(m);
    cv.wait(lk, [&pause]() { return !pause; });
    printf("\rLoop %d iterations", cnt++);
    fflush(stdout);
  }
  thread.join();
  return 0;
}
