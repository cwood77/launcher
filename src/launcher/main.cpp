#define WIN32_LEAN_AND_MEAN
#include "commandLine.hpp"
#include "error.hpp"
#include "parser.hpp"
#include "shortcuts.hpp"
#include "windows.h"
#include <conio.h>
#include <iostream>

namespace {

std::string buildFilePath()
{
   char path[MAX_PATH];
   ::GetModuleFileNameA(NULL,path,MAX_PATH);
   return std::string("") + path + "\\..\\shortcuts.txt";
}

void printUsage()
{
   std::cout
      << "launcher - simple Windows app for launching other apps" << std::endl
      << "shortcuts are stored in file " << buildFilePath() << std::endl
      << "usage:" << std::endl
      << "   <cmd> - execute a command" << std::endl
   ;
}

void holdOpenWindow()
{
   std::cout << std::endl << "command returned an error; press any key to continue" << std::endl;
   ::getch();
}

void runShortcut(const std::string& alias)
{
   shortcuts s;
   parser::parse(buildFilePath(),s);

   shortcut *pCmd = s.fetch(alias);
   if(!pCmd)
      error(errLoc,"no command matches alias")
         .with("alias",alias)
         .raise();

   int rval = ::system(pCmd->command.c_str());
   if(rval)
      holdOpenWindow();
}

} // anonymous namespace

int main(int argc, const char *argv[])
{
   try
   {
      commandLine cl(argc,argv);

      if(cl.reset().literal("--help").end())
         printUsage();
      else if(cl.reset().arg().end())
         runShortcut(cl.getArg(0));
      else
         error(errLoc,"bad usage; use --help")
            .raise();

      return 0;
   }
   catch(std::exception& x)
   {
      std::cerr << "ERROR: " << x.what() << std::endl;
      return -1;
   }
}
