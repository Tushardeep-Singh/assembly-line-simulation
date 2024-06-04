// Author: Tushardeep Singh
// Seneca College Alumni

#include "Station.h"

namespace seneca
{
  // Defining class(static) variables
  size_t Station::m_widthField = 0;
  size_t Station::id_generator = 0;

  // Default constructor
  Station::Station()
  {
    // I'd generator generates a new I'd for each instance of Station
    m_stationId = ++id_generator;
    m_stationItem = "";
    m_stationDescription = "";
    m_stationItemSerialNumber = 0;
    m_stationNumInStockItems = 0;
  }

  // 1-arg constructor
  Station::Station(const std::string &dataLine)
  {
    m_stationId = ++id_generator;
    Utilities utilities;
    size_t next_pos = 0;
    bool more = true;
    m_stationItem = utilities.extractToken(dataLine, next_pos, more);
    m_stationItemSerialNumber = static_cast<size_t>(std::stoi(utilities.extractToken(dataLine, next_pos, more)));
    m_stationNumInStockItems = static_cast<size_t>(std::stoi(utilities.extractToken(dataLine, next_pos, more)));

    m_widthField = std::max(m_widthField, utilities.getFieldWidth());

    m_stationDescription = utilities.extractToken(dataLine, next_pos, more);
  }

  // Getter
  const std::string &Station::getItemName() const
  {
    return m_stationItem;
  }

  // Getter
  size_t Station::getNextSerialNumber()
  {
    return m_stationItemSerialNumber++;
  }

  // Getter
  size_t Station::getQuantity() const
  {
    return m_stationNumInStockItems;
  }

  void Station::updateQuantity()
  {
    if (m_stationNumInStockItems > 0)
      --m_stationNumInStockItems;
  }

  // Getter
  int Station::getStationId() const
  {
    return m_stationId;
  }

  // Getter
  std::string Station::getStationDescription() const
  {
    return m_stationDescription;
  }

  // Getter
  size_t Station::getSerialNumWithoutUpdate() const
  {
    return m_stationItemSerialNumber;
  }

  // Getter
  size_t Station::getWidthField() const
  {
    return m_widthField;
  }

  // Displays the contents of Station
  void Station::display(std::ostream &os, bool full) const
  {
    os << std::setw(3) << std::right << std::setfill('0') << getStationId();
    os << std::setfill(' ') << " | ";
    os << std::setw(getWidthField()) << std::left << getItemName();
    os << " | ";
    os << std::setw(6) << std::right << std::setfill('0') << getSerialNumWithoutUpdate();
    os << std::setfill(' ') << " | ";

    if (full)
    {
      os << std::setw(4) << std::right << getQuantity();
      os << " | ";
      os << getStationDescription();
    }
    os << '\n';
  }

  // Setter
  void Station::setStationItem(const std::string itemName)
  {
    m_stationItem = itemName;
  }
}