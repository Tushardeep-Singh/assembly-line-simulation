// Author: Tushardeep Singh
// Seneca College Alumni

#include "LineManager.h"

namespace seneca
{
  LineManager::LineManager(const std::string &file, const std::vector<Workstation *> &stations)
  {
    std::fstream dataFile(file);
    // Throw an exception if the file can not be opened
    if (!dataFile.is_open())
      throw std::runtime_error("Can not open file [" + file + "]");

    std::string line, thisStationItem, nextStationItem;
    Utilities utilities;
    // Set the delimiter for the utilities class
    utilities.setDelimiter('|');
    // Map to find the first station, station with pair.second == 1, will be the first station in the assembly line
    std::map<std::string, int> getFirstStation;

    // Store each line from fstream dataFile into string line
    while (std::getline(dataFile, line))
    {
      size_t next_pos = 0;
      bool more = true;
      thisStationItem = utilities.extractToken(line, next_pos, more);
      nextStationItem = utilities.extractToken(line, next_pos, more);
      // Increment the value in map
      getFirstStation[thisStationItem]++;
      getFirstStation[nextStationItem]++;

      // Find the station in vector "stations" to get a reference to workstation
      std::vector<Workstation *>::const_iterator thisStation = std::find_if(stations.begin(), stations.end(), [&thisStationItem](Workstation *wStation)
                                                                            { return (wStation->getItemName() == thisStationItem); });

      std::vector<Workstation *>::const_iterator nextStation = std::find_if(stations.begin(), stations.end(), [&nextStationItem](Workstation *wStation)
                                                                            { return (wStation->getItemName() == nextStationItem); });

      // Set the next station based on the value of next_pos from utilities object
      if (next_pos != 0)
        (*thisStation)->setNextStation(*nextStation);
      else
        (*thisStation)->setNextStation(nullptr);
      // Add the workstations to vector m_activeLine
      m_activeLine.push_back(*thisStation);
    }

    // Find the pair in map whose pair.second is 1, that will be the firstStation in the assembly line
    std::map<std::string, int>::const_iterator it = std::find_if(getFirstStation.begin(), getFirstStation.end(), [](std::pair<std::string, int> pair)
                                                                 { return (pair.second == 1); });

    // Get a reference to first Station from stations vector
    std::vector<Workstation *>::const_iterator firstStation = std::find_if(stations.begin(), stations.end(), [&it](Workstation *wStation)
                                                                           { return (wStation->getItemName() == (*it).first); });

    m_firstStation = *firstStation;
    m_cntCustomerOrder = g_pending.size();
  }

  // Sort the stations starting from first station, second station .... last station
  void LineManager::reorderStations()
  {
    std::list<Workstation *> wStations;
    wStations.push_back(m_firstStation);
    Workstation *curr = m_firstStation;
    while (curr != nullptr)
    {
      if (curr->getNextStation() != nullptr)
      {
        std::vector<Workstation *>::const_iterator nextStation = std::find_if(m_activeLine.begin(), m_activeLine.end(), [&curr](Workstation *wStation)
                                                                              { return (wStation->getItemName() == curr->getNextStation()->getItemName()); });

        wStations.push_back(*nextStation);
        curr = *nextStation;
      }
      else
        curr = nullptr;
    }

    m_activeLine.clear();
    for (Workstation *station : wStations)
      m_activeLine.push_back(std::move(station));
  }

  // Starts the assembly line
  bool LineManager::run(std::ostream &os)
  {
    static int index = 1;
    os << "Line Manager Iteration: " << index++ << '\n';

    if (g_pending.size() > 0)
    {
      *m_firstStation += std::move(g_pending.front());
      g_pending.pop_front();
    }

    for (int i = 0; i < m_activeLine.size(); ++i)
      m_activeLine[i]->fill(os);
    for (int i = 0; i < m_activeLine.size(); ++i)
      m_activeLine[i]->attemptToMoveOrder();

    return (g_completed.size() + g_incomplete.size() == m_cntCustomerOrder);
  }

  // Displays the contents of the workstation
  void LineManager::display(std::ostream &os) const
  {
    for (int i = 0; i < m_activeLine.size(); ++i)
      m_activeLine[i]->display(os);
  }
}