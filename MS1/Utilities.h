// Author: Tushardeep Singh
// Seneca College Alumni

#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H

#include <iostream>
#include <string>

namespace seneca
{
  class Utilities
  {
  private:
    // Used for display purpose
    size_t m_widthField;
    // Delimiter to extract tokens
    static char m_delimiter;

  public:
    // Default constructor
    Utilities();
    // Setter: sets the m_widthField to param "newWidth"
    void setFieldWidth(size_t newWidth);
    // Getter: returns the field width (m_widthField)
    size_t getFieldWidth() const;
    // Extracts one token at a time from string param "str"
    std::string extractToken(const std::string &str, size_t &next_pos, bool &more);
    // Removes leading and trailing whitespaces from referenced string param "str"
    void removeLeadTrailWhiteSpaces(std::string &str);
    // Setter: sets the delimiter (m_delimiter) to param "newDelimiter"
    static void setDelimiter(char newDelimiter);
    // Getter: returns the delimiter (m_delimiter)
    static char getDelimiter();
  };
}

#endif