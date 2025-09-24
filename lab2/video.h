#ifndef VIDEO_H
#define VIDEO_H

#include <string>

struct Video {
  std::string title;
  std::string theme;
  int actors_count;
  std::string *actors;
  std::string filename;
  std::string release_date;
  int rating;
  int duration;

  Video();
  Video(std::string title_arg, std::string theme_arg, int actors_count_arg,
        std::string actors_arg[], std::string filename_arg,
        std::string release_date_arg, int rating_arg, int duration_arg);
  Video(const Video &other);
  ~Video();

  Video &operator=(const Video &other);
};

class VideoLibrary {
private:
  Video *videos;
  int videos_count;

public:
  VideoLibrary();
  VideoLibrary(int video_count_arg, Video videos_arg[]);
  VideoLibrary(const VideoLibrary &other);
  ~VideoLibrary();

  VideoLibrary &operator=(const VideoLibrary &other);
  Video &operator[](int index) const;

  int getVideosCount() const;

  void add(const Video &video);
  Video pop();

  void show_by_actor(const std::string &actor);
  void show_by_title(const std::string &title);
  void show_by_theme(const std::string &theme);
  void show_all();
};

class VideoPlayer {
public:
  VideoLibrary library;

  VideoPlayer(VideoLibrary &library_arg);
  ~VideoPlayer();

  void play(int index);
  void stop();
};

#endif
