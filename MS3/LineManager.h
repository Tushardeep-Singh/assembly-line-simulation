// Author: Tushardeep Singh
// Seneca College Alumni

#ifndef SENECA_LINE_MANAGER_H
#define SENECA_LINE_MANAGER_H

#include <vector>
#include "Workstation.h"
#include <fstream>
#include <map>
#include <list>

namespace seneca
{
  class LineManager
  {
  private:
    // Vector storing workstations
    std::vector<Workstation *> m_activeLine{};
    // Count of customer orders
    size_t m_cntCustomerOrder{0};
    // First station in the assembly line
    Workstation *m_firstStation{nullptr};

  public:
    // 2-arg constructor
    LineManager(const std::string &file, const std::vector<Workstation *> &stations);
    // Sorts the workstations beginning from first station to last station in m_activeLine
    void reorderStations();
    // Starts the assembly line
    bool run(std::ostream &os);
    // Displays the contents of assembly line
    void display(std::ostream &os) const;
  };
}

#endif