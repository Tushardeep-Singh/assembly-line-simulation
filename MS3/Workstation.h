// Author: Tushardeep Singh
// Seneca College Alumni

#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H

#include "CustomerOrder.h"
#include "Station.h"
#include <deque>

namespace seneca
{
  // Global variables(deque)
  // Stores the pending customer orders
  extern std::deque<seneca::CustomerOrder> g_pending;
  // Stores the completed customer orders
  extern std::deque<seneca::CustomerOrder> g_completed;
  // Stores the incomplete i.e. can not be completed orders
  extern std::deque<seneca::CustomerOrder> g_incomplete;

  // Inherits from Station class
  class Workstation : public Station
  {
  private:
    // Deque that stores customer orders
    std::deque<seneca::CustomerOrder> m_orders{};
    // Pointer to next station
    Workstation *m_pNextStation{nullptr};

  public:
    // Default constructor
    Workstation();
    // 1-arg constructor
    Workstation(const std::string &dataLine) : Station(dataLine){};
    // Deleting copy constructor
    Workstation(const Workstation &) = delete;
    // Deleting copy assignment operator
    Workstation &operator=(const Workstation &) = delete;
    // Deleting move constructor
    Workstation(Workstation &&) = delete;
    // Deleting move assignment operator
    Workstation &operator=(Workstation &&) = delete;
    // Member function that fills the customer order at the front of the m_orders
    void fill(std::ostream &os);
    // Member function that moves the customer order to it's right place
    bool attemptToMoveOrder();
    // Setter: sets the member variable "m_pNextStation" to param "station"
    void setNextStation(Workstation *station);
    // Getter: returns the member variable "m_pNextStation"
    Workstation *getNextStation() const;
    // Displays the content of Stations
    void display(std::ostream &os) const;
    // Overloading "+=" operator
    Workstation &operator+=(CustomerOrder &&newOrder);
  };
}

#endif