#pragma once

#include <fstream>
#include <string>

namespace filesystem {
  std::string getBaseDirectory();
  std::string getGameDirectory();
  std::string getPathSeparator();

  // main
  void createFileSystem();
  void destroyFileSystem();

  // file
  class FileBase {
  public:
    enum class Position { Begin, end, current };

    FileBase();
    ~FileBase();

    int getPositionOffset(Position pos);
    void setPosition(Position pos, int offset);

  protected:
    std::fstream mFile;
  };

  class FileTextWriter : public FileBase {
  public:
    void open(std::string filename);

    void write(std::string text);
  };

  class FileBinaryWriter : public FileBase {
  public:
    void open(std::string filename);

    template <class T> void write(T *data, int count);
  };

  class FileTextReader : public FileBase {
  public:
    void open(std::string filename);

    bool checkNext(std::string texte);
    bool readLine(std::string &line);
    bool read(int size, std::string &text);
  };

  class FileBinaryReader : public FileBase {
  public:
    void open(std::string filename);

    template <class T> bool read(T *data, int count);
  };
}
