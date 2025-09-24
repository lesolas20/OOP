#include "video.h"
#include <iostream>

bool isNumeric(const std::string &str) {
  for (char ch : str) {
    if (!isdigit(ch)) {
      return false;
    }
  }
  return true;
}

int main() {
  std::string cast1[] = {"Christian Bale", "Heath Ledger", "Aaron Eckhart"};
  std::string cast2[] = {"Leonardo DiCaprio", "Joseph Gordon-Levitt", "Ellen Page"};
  std::string cast3[] = {"Tim Robbins", "Morgan Freeman"};
  std::string cast4[] = {"Matthew McConaughey", "Anne Hathaway", "Jessica Chastain"};
  std::string cast5[] = {"Andrew Garfield", "Justin Timberlake", "Armie Hammer"};

  Video video1("The Dark Knight", "Chaos", 3, cast1, "tdk.mp4", "2008-07-18", 90, 152);
  Video video2("Inception", "Dreams", 3, cast2, "inception.mp4", "2010-07-16", 88, 148);
  Video video3("The Shawshank Redemption", "Redemption", 2, cast3, "tsr.mp4", "1994-09-24", 93, 142);
  Video video4("Interstellar", "Space exploration", 3, cast4, "interstellar.mp4", "2014-11-05", 86, 169);
  Video video5("The Social Network", "Ambition", 3, cast5, "tsc.mp4", "2010-10-15", 75, 127);
  Video video6 = video1;
  video6 = video5;

  Video videos[6] = {video1, video2, video3, video4, video5, video6};

  VideoLibrary library(6, videos);

  VideoPlayer player(library);

  player.library.add(video3);

  std::string choice;
  int choice_i;

  do {
    std::cout << "\n=== Video Player Menu ===\n";
    std::cout << "1. Show all videos\n";
    std::cout << "2. Show by actor\n";
    std::cout << "3. Show by title\n";
    std::cout << "4. Show by theme\n";
    std::cout << "5. Play video\n";
    std::cout << "6. Stop video\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
    std::getline(std::cin, choice);

    if (!isNumeric(choice) || choice.empty()) {
      std::cout << "Invalid choice. Please try again.\n";
      continue;
    } else {
      choice_i = std::stoi(choice);
    }

    switch (choice_i) {
    case 1:
      player.library.show_all();
      break;
    case 2: {
      std::string actor;
      std::cout << "Enter actor name: ";
      std::getline(std::cin, actor);
      player.library.show_by_actor(actor);
      break;
    }
    case 3: {
      std::string title;
      std::cout << "Enter title: ";
      std::getline(std::cin, title);
      player.library.show_by_title(title);
      break;
    }
    case 4: {
      std::string theme;
      std::cout << "Enter theme: ";
      std::getline(std::cin, theme);
      player.library.show_by_theme(theme);
      break;
    }
    case 5: {
      std::string index;
      std::cout << "Enter index: ";
      std::getline(std::cin, index);
      player.play(std::stoi(index));
      break;
    }
    case 6: {
      player.stop();
      break;
    }
    case 0:
      std::cout << "Exiting...\n";
      break;
    default:
      std::cout << "Invalid choice. Please try again.\n";
      break;
    }
  } while (choice_i != 0);

  return 0;
}
