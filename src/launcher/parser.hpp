#pragma once

#include <string>

class shortcuts;

class parser {
public:
   static void parse(const std::string& filePath, shortcuts& s);

private:
   explicit parser(shortcuts& s);
   void parseFile(const std::string& filePath);
   void parseLine(const std::string& line);

   shortcuts& m_s;
};
