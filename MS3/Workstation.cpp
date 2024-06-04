// Author: Tushardeep Singh
// Seneca College Alumni

#include "Workstation.h"

namespace seneca
{
  // Defining the global variables
  std::deque<seneca::CustomerOrder> g_pending{};
  std::deque<seneca::CustomerOrder> g_completed{};
  std::deque<seneca::CustomerOrder> g_incomplete{};

  // Default constructor
  Workstation::Workstation()
  {
    m_pNextStation = nullptr;
  }

  // Fills the order at the front of deque "m_orders"
  void Workstation::fill(std::ostream &os)
  {
    if (m_orders.size() == 0)
      return;
    m_orders.front().fillItem(*this, os);
  }

  // Moves the orders to their right place
  bool Workstation::attemptToMoveOrder()
  {
    if (m_orders.size() > 0 && (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0))
    {
      if (m_pNextStation == nullptr)
      {
        if (!m_orders.front().isOrderFilled())
          g_incomplete.push_back(std::move(m_orders.front()));
        else
          g_completed.push_back(std::move(m_orders.front()));
      }
      else
        *m_pNextStation += std::move(m_orders.front());
      m_orders.pop_front();
      return true;
    }
    return false;
  }

  // Setter
  void Workstation::setNextStation(Workstation *station)
  {
    m_pNextStation = station;
  }

  // Getter
  Workstation *Workstation::getNextStation() const
  {
    return m_pNextStation;
  }

  void Workstation::display(std::ostream &os) const
  {
    os << getItemName() << " --> ";
    if (m_pNextStation == nullptr)
    {
      os << "End of Line\n";
      return;
    }
    os << m_pNextStation->getItemName() << '\n';
  }

  Workstation &Workstation::operator+=(CustomerOrder &&newOrder)
  {
    m_orders.push_back(std::move(newOrder));
    return *this;
  }
}