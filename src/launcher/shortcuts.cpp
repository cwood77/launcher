#include "shortcuts.hpp"

shortcut& shortcuts::addNew(const std::string& alias)
{
   return m_dict[alias];
}

shortcut *shortcuts::fetch(const std::string& alias)
{
   auto it = m_dict.find(alias);
   if(it == m_dict.end())
      return NULL;
   return &it->second;
}
