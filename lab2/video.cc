#include "video.h"

#include <iostream>
#include <stdexcept>
#include <string>

void printVideo(const Video &video);

Video::Video() {
  title = "";
  theme = "";
  actors_count = 0;
  actors = new std::string[0];
  filename = "";
  release_date = "";
  rating = 0;
  duration = 0;
}

Video::Video(std::string title_arg, std::string theme_arg, int actors_count_arg,
             std::string actors_arg[], std::string filename_arg,
             std::string release_date_arg, int rating_arg, int duration_arg) {
  title = title_arg;
  theme = theme_arg;
  filename = filename_arg;
  release_date = release_date_arg;
  rating = rating_arg;
  duration = duration_arg;

  actors_count = actors_count_arg;

  actors = new std::string[actors_count];
  for (int i = 0; i < actors_count; i++) {
    actors[i] = actors_arg[i];
  }
}

Video::Video(const Video &other) {
  title = other.title;
  theme = other.theme;
  filename = other.filename;
  release_date = other.release_date;
  rating = other.rating;
  duration = other.duration;

  actors_count = other.actors_count;

  actors = new std::string[actors_count];
  for (int i = 0; i < actors_count; i++) {
    actors[i] = other.actors[i];
  }
}

Video::~Video() { delete[] actors; }

Video &Video::operator=(const Video &other) {
  if (this == &other) {
    return *this;
  }

  delete[] actors;

  title = other.title;
  theme = other.theme;
  filename = other.filename;
  release_date = other.release_date;
  rating = other.rating;
  duration = other.duration;

  actors_count = other.actors_count;

  actors = new std::string[actors_count];
  for (int i = 0; i < actors_count; i++) {
    actors[i] = other.actors[i];
  }

  return *this;
}

VideoLibrary::VideoLibrary() {
  videos = new Video[0];
  videos_count = 0;
}

VideoLibrary::VideoLibrary(int video_count_arg, Video videos_arg[]) {
  videos_count = video_count_arg;

  videos = new Video[videos_count];
  for (int i = 0; i < videos_count; i++) {
    videos[i] = videos_arg[i];
  }
}

VideoLibrary::VideoLibrary(const VideoLibrary &other) {
  videos_count = other.videos_count;

  videos = new Video[videos_count];
  for (int i = 0; i < videos_count; i++) {
    videos[i] = other.videos[i];
  }
}

VideoLibrary::~VideoLibrary() { delete[] videos; }

VideoLibrary &VideoLibrary::operator=(const VideoLibrary &other) {
  if (this == &other) {
    return *this;
  }

  delete[] videos;

  videos_count = other.videos_count;

  videos = new Video[videos_count];
  for (int i = 0; i < videos_count; i++) {
    videos[i] = other.videos[i];
  }

  return *this;
}

Video &VideoLibrary::operator[](int index) const {
  if (index >= 0 && index < videos_count) {
    return videos[index];
  } else {
    throw std::out_of_range("Index out of range");
  }
}

int VideoLibrary::getVideosCount() const { return videos_count; }

void VideoLibrary::add(const Video &video) {
  int new_videos_count = videos_count + 1;

  Video *new_videos = new Video[new_videos_count];
  for (int i = 0; i < videos_count; i++) {
    new_videos[i] = videos[i];
  }

  delete[] videos;

  new_videos[videos_count] = video;

  videos = new_videos;
  videos_count = new_videos_count;
}

Video VideoLibrary::pop() {
  if (videos_count == 0) {
    throw std::out_of_range("Cannot pop from empty `library` object");
  }

  int new_videos_count = videos_count - 1;

  Video *new_videos = new Video[new_videos_count];
  for (int i = 0; i < new_videos_count; i++) {
    new_videos[i] = videos[i];
  }

  Video tail = videos[videos_count - 1];

  delete[] videos;

  videos = new_videos;
  videos_count = new_videos_count;

  return tail;
}

void VideoLibrary::show_by_actor(const std::string &actor) {
  bool found = false;

  for (int i = 0; i < videos_count; i++) {
    const Video &video = videos[i];

    for (int j = 0; j < video.actors_count; j++) {
      if (video.actors[j] == actor) {
        found = true;
        printVideo(video);
        break;
      }
    }
  }

  if (!found) {
    std::cout << "No videos found with actor: " << actor << "\n";
  }
}

void VideoLibrary::show_by_title(const std::string &title) {
  bool found = false;

  for (int i = 0; i < videos_count; i++) {
    if (videos[i].title == title) {
      found = true;
      printVideo(videos[i]);
    }
  }

  if (!found) {
    std::cout << "No videos found with title: " << title << "\n";
  }
}

void VideoLibrary::show_by_theme(const std::string &theme) {
  bool found = false;

  for (int i = 0; i < videos_count; i++) {
    if (videos[i].theme == theme) {
      found = true;
      printVideo(videos[i]);
    }
  }

  if (!found) {
    std::cout << "No videos found with theme: " << theme << "\n";
  }
}

void VideoLibrary::show_all() {
  for (int i = 0; i < videos_count; i++) {
    printVideo(videos[i]);
  }
}

VideoPlayer::VideoPlayer(VideoLibrary &library_arg) { library = library_arg; }

VideoPlayer::~VideoPlayer() {}

void VideoPlayer::play(int index) {
  if (index >= 0 && index < library.getVideosCount()) {
    std::cout << "Playing video '" << library[index].title << "' from file '"
              << library[index].filename << "'\n";
  } else {
    std::cout << "Invalid index!\n";
  }
}

void VideoPlayer::stop() { std::cout << "Stopping video...\n"; }

void printVideo(const Video &video) {
  std::cout << "-----------------------------\n";
  std::cout << "Title: " << video.title << "\n";
  std::cout << "Theme: " << video.theme << "\n";
  std::cout << "Actors: ";

  if (video.actors_count > 0) {
    for (size_t i = 0; i < (video.actors_count - 1); ++i) {
      std::cout << video.actors[i] << ", ";
    }
    std::cout << video.actors[video.actors_count - 1];
  }

  std::cout << "\n";
  std::cout << "Rating: " << video.rating << "/100\n";
  std::cout << "Duration: " << video.duration << " minutes\n";
  std::cout << "Filename: " << video.filename << "\n";
  std::cout << "Release Date: " << video.release_date << "\n";
  std::cout << "-----------------------------\n";
}

