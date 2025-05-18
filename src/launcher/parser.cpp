#define WIN32_LEAN_AND_MEAN
#include "error.hpp"
#include "parser.hpp"
#include "shortcuts.hpp"
#include "windows.h"
#include <fstream>

void parser::parse(const std::string& filePath, shortcuts& s)
{
   parser(s).parseFile(filePath);
}

parser::parser(shortcuts& s)
: m_s(s)
{
}

void parser::parseFile(const std::string& filePath)
{
   std::ifstream f(filePath);
   if(!f.good())
      error(errLoc,"file can't be loaded")
         .with("path",filePath)
         .raise();

   do
   {
      std::string line;
      std::getline(f,line);
      parseLine(line);
   }
   while(f.good());
}

void parser::parseLine(const std::string& line)
{
   if(line.empty())
      return; // blank line

   if(line.c_str()[0] == ';')
      return; // comments

   // example:
   // alias command
   char alias[MAX_PATH];
   int n;
   int rval = ::sscanf(
      line.c_str(),
      "%[^ ] %n",
      alias,&n
   );
   if(rval != 1)
      error(errLoc,"can't parse line")
         .with("line",line)
         .raise();

   const char *cmd = line.c_str() + n;

   m_s.addNew(alias).command = cmd;
}
