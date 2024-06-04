// Author: Tushardeep Singh
// Seneca College Alumni

#ifndef SENECA_STATION_H
#define SENECA_STATION_H

#include "Utilities.h"
#include <algorithm>
#include <iomanip>

namespace seneca
{
  class Station
  {
  private:
    // Station I'd
    int m_stationId;
    // Name of the item this station stores
    std::string m_stationItem;
    // Description of the station
    std::string m_stationDescription;
    // Serial number of the item stored at this station
    size_t m_stationItemSerialNumber;
    // Number of items in stock at this station
    size_t m_stationNumInStockItems;

    // Class(static) variables
    // Width of the field, used for display purposes
    static size_t m_widthField;
    // Sets a new I'd for each new Station instance variable m_stationId
    static size_t id_generator;

  public:
    // Default constructor
    Station();
    // 1-arg constructor
    Station(const std::string &dataLine);
    // Getter: returns the name of the item stored at current station (m_stationItem)
    const std::string &getItemName() const;
    // Getter: returns the serial number of the current item and increments it (m_stationItemSerialNumber)
    size_t getNextSerialNumber();
    // Getter: returns the items in stock at this station (m_stationNumInStockItems)
    size_t getQuantity() const;
    // Reduces the number of items in stock by 1
    void updateQuantity();
    // Displays the details of this station
    void display(std::ostream &os, bool full) const;
    // Getter: returns the station id (m_stationId)
    int getStationId() const;
    // Getter: returns the description of this station (m_stationDescription)
    std::string getStationDescription() const;
    // Getter: returns serial number of item without incrementing it, as in getNextSerialNumber()
    size_t getSerialNumWithoutUpdate() const;
    // Getter: returns the width of the field (m_widthField)
    size_t getWidthField() const;
    // Setter: sets the name of the item stored by the station(m_stationItem) to param "itemName"
    void setStationItem(const std::string itemName);
  };
}

#endif