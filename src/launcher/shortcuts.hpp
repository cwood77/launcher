#pragma once

#include <map>
#include <string>

class shortcut {
public:
   std::string command;
};

class shortcuts {
public:
   shortcut& addNew(const std::string& alias);
   shortcut *fetch(const std::string& alias);

private:
   std::map<std::string,shortcut> m_dict;
};
