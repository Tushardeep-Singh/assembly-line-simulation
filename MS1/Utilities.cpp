// Author: Tushardeep Singh
// Seneca College Alumni

#include "Utilities.h"

namespace seneca
{
  // Defining the static variable m_delimiter
  char Utilities::m_delimiter{};

  // Default constructor
  Utilities::Utilities()
  {
    m_widthField = 1;
  }

  void Utilities::setFieldWidth(size_t newWidth)
  {
    m_widthField = newWidth;
  }

  size_t Utilities::getFieldWidth() const
  {
    return m_widthField;
  }

  void Utilities::removeLeadTrailWhiteSpaces(std::string &str)
  {
    int idx1, idx2;
    for (int i = 0; i < str.length(); ++i)
      if (str[i] != ' ')
      {
        idx1 = i;
        break;
      }

    for (int i = str.length() - 1; i >= 0; --i)
      if (str[i] != ' ')
      {
        idx2 = i;
        break;
      }

    str = str.substr(idx1, idx2 - idx1 + 1);
  }

  std::string Utilities::extractToken(const std::string &str, size_t &next_pos, bool &more)
  {
    if (str[next_pos] == getDelimiter())
    {
      more = false;
      throw std::runtime_error("EXCEPTION: Delimiter found at next_pos.");
    }

    int index = str.find_first_of(m_delimiter, next_pos);
    if (next_pos == 0 && index != std::string::npos)
    {
      std::string strUtils = str.substr(next_pos, index);
      removeLeadTrailWhiteSpaces(strUtils);
      if (m_widthField < strUtils.length())
        setFieldWidth(strUtils.length());
      next_pos = index + 1;
      more = true;
      return strUtils;
    }

    if (index != std::string::npos)
    {
      std::string strUtils = str.substr(next_pos, index - next_pos);
      removeLeadTrailWhiteSpaces(strUtils);
      if (m_widthField < strUtils.length())
        setFieldWidth(strUtils.length());
      next_pos = index + 1;
      more = true;
      return strUtils;
    }

    std::string strUtils = str.substr(next_pos);
    removeLeadTrailWhiteSpaces(strUtils);
    if (m_widthField < strUtils.length())
      setFieldWidth(strUtils.length());
    more = false;
    return strUtils;
  }

  void Utilities::setDelimiter(char newDelimiter)
  {
    m_delimiter = newDelimiter;
  }

  char Utilities::getDelimiter()
  {
    return m_delimiter;
  }
}