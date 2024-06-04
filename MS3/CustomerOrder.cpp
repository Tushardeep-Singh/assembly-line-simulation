// Author: Tushardeep Singh
// Seneca College Alumni

#include "CustomerOrder.h"

namespace seneca
{
  // Defining the class variable(static)
  size_t CustomerOrder::m_widthField = 0;

  // Default constructor
  CustomerOrder::CustomerOrder()
  {
    m_name = "";
    m_product = "";
    m_cntItem = 0;
    m_lstItem = nullptr;
  }

  // Getter
  size_t CustomerOrder::getCntItem() const
  {
    return m_cntItem;
  }

  // Setter
  void CustomerOrder::setCntItem(size_t count)
  {
    m_cntItem = count;
  }

  // Copy constructor
  Item::Item(const Item &copyFromItem)
  {
    m_itemName = copyFromItem.m_itemName;
    m_serialNumber = copyFromItem.m_serialNumber;
    m_isFilled = copyFromItem.m_isFilled;
  }

  // Copy assignment operator
  Item &Item::operator=(const Item &copyFromItem)
  {
    m_itemName = copyFromItem.m_itemName;
    m_serialNumber = copyFromItem.m_serialNumber;
    m_isFilled = copyFromItem.m_isFilled;

    return *this;
  }

  // 1-arg constructor
  CustomerOrder::CustomerOrder(const std::string &dataLine)
  {
    Utilities utilities;
    size_t next_pos = 0;
    bool more = true;
    m_name = utilities.extractToken(dataLine, next_pos, more);
    m_product = utilities.extractToken(dataLine, next_pos, more);

    // Store the order items in a vector and then allocate memory to m_lstItem for size of the order vector
    std::vector<std::string> orders;
    while (more)
      orders.push_back(utilities.extractToken(dataLine, next_pos, more));

    setCntItem(static_cast<size_t>(orders.size()));
    m_lstItem = new Item *[getCntItem()];
    for (int i = 0; i < getCntItem(); ++i)
      m_lstItem[i] = new Item(orders[i]);
    m_widthField = std::max(utilities.getFieldWidth(), m_widthField);
  }

  // Copy operations are not allowed
  CustomerOrder::CustomerOrder(const CustomerOrder &other)
  {
    throw std::runtime_error("Customer Order Copy Operations are not allowed");
  }

  // Getter
  std::string CustomerOrder::getName() const
  {
    return m_name;
  }

  // Getter
  std::string CustomerOrder::getProduct() const
  {
    return m_product;
  }

  // Setter
  void CustomerOrder::setName(const std::string &name)
  {
    m_name = name;
  }

  // Setter
  void CustomerOrder::setProduct(const std::string &product)
  {
    m_product = product;
  }

  // Subscript operator
  Item *CustomerOrder::operator[](int index)
  {
    return m_lstItem[index];
  }

  // Move constructor
  CustomerOrder::CustomerOrder(CustomerOrder &&moveFromCustomerOrder) noexcept
  {
    m_name = moveFromCustomerOrder.getName();
    m_product = moveFromCustomerOrder.getProduct();
    m_cntItem = moveFromCustomerOrder.getCntItem();
    moveFromCustomerOrder.setName("");
    moveFromCustomerOrder.setProduct("");
    moveFromCustomerOrder.setCntItem(0);

    // Make m_lstItem double pointer point towards the memory of moveFromCustomerOrder.m_lstItem
    m_lstItem = moveFromCustomerOrder.m_lstItem;
    moveFromCustomerOrder.m_lstItem = nullptr;
  }

  // Move assignment operator
  CustomerOrder &CustomerOrder::operator=(CustomerOrder &&moveFromCustomerOrder) noexcept
  {
    m_name = moveFromCustomerOrder.getName();
    m_product = moveFromCustomerOrder.getProduct();
    moveFromCustomerOrder.setName("");
    moveFromCustomerOrder.setProduct("");

    // De-allocate the memory of the current double pointer
    for (int i = 0; i < getCntItem(); ++i)
    {
      delete m_lstItem[i];
      m_lstItem[i] = nullptr;
    }
    delete[] m_lstItem;
    m_lstItem = nullptr;

    m_cntItem = moveFromCustomerOrder.getCntItem();
    moveFromCustomerOrder.setCntItem(0);

    // Make this double pointer point towards the memory of moveFromCustomerOrder.m_lstItem
    m_lstItem = moveFromCustomerOrder.m_lstItem;
    moveFromCustomerOrder.m_lstItem = nullptr;

    return *this;
  }

  // Destructor
  CustomerOrder::~CustomerOrder()
  {
    m_name = "";
    m_product = "";

    if (m_lstItem != nullptr)
    {
      // Destroy each pointer
      for (int i = 0; i < getCntItem(); ++i)
      {
        delete m_lstItem[i];
        m_lstItem[i] = nullptr;
      }
      // Destroy double pointer itself
      delete[] m_lstItem;
      m_lstItem = nullptr;
    }

    m_cntItem = 0;
  }

  bool CustomerOrder::isOrderFilled() const
  {
    for (int i = 0; i < m_cntItem; ++i)
      if (m_lstItem[i]->m_isFilled == false)
        return false;

    return true;
  }

  bool CustomerOrder::isItemFilled(const std::string &itemName) const
  {
    bool returnVal = true;
    for (int i = 0; i < getCntItem(); ++i)
    {
      if (m_lstItem[i]->m_itemName == itemName && m_lstItem[i]->m_isFilled == false)
        returnVal = false;
    }
    return returnVal;
  }

  void CustomerOrder::fillItem(Station &station, std::ostream &os)
  {
    bool available = false;
    for (int i = 0; i < getCntItem(); ++i)
      if (m_lstItem[i]->m_itemName == station.getItemName())
        available = true;
    if (!available)
      return;

    for (int i = 0; i < m_cntItem; ++i)
      if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled && station.getQuantity() >= 1)
      {
        station.updateQuantity();
        m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
        m_lstItem[i]->m_isFilled = true;
        os << "    Filled " << getName() << ", " << getProduct() << " [" << station.getItemName() << "]\n";
        return;
      }

    for (int i = 0; i < m_cntItem; ++i)
      if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled && station.getQuantity() == 0)
      {
        os << "    Unable to fill " << getName() << ", " << getProduct() << " [" << station.getItemName() << "]\n";
      }
  }

  size_t CustomerOrder::getFieldWidth() const
  {
    return m_widthField;
  }

  void CustomerOrder::display(std::ostream &os) const
  {
    os << getName() << " - " << getProduct() << '\n';
    for (int i = 0; i < getCntItem(); ++i)
    {
      os << '[';
      os << std::setw(6) << std::setfill('0') << std::right << m_lstItem[i]->m_serialNumber;
      os << std::setfill(' ') << "] ";
      os << std::setw(getFieldWidth()) << std::left << m_lstItem[i]->m_itemName;
      os << " - ";
      if (m_lstItem[i]->m_isFilled)
        os << "FILLED\n";
      else
        os << "TO BE FILLED\n";
    }
  }
}