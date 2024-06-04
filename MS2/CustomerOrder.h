// Author: Tushardeep Singh
// Seneca College Alumni

#ifndef SENECA_CUSTOMER_ORDER_H
#define SENECA_CUSTOMER_ORDER_H

#include "Station.h"
#include <stdexcept>
#include <vector>

namespace seneca
{
  struct Item
  {
    // Name of the item present in customer order
    std::string m_itemName;
    // Serial number of the item
    size_t m_serialNumber{0};
    // Flag contains whether item is filled by station or not
    bool m_isFilled{false};

    // 1-arg constructor
    Item(const std::string &src) : m_itemName(src){};
    // Copy constructor
    Item(const Item &copyFromItem);
    // Copy assignment operator
    Item &operator=(const Item &copyFromItem);
  };

  class CustomerOrder
  {
  private:
    // Name of the customer
    std::string m_name{""};
    // Name of the product ordered by customer
    std::string m_product{""};
    // Number of items in customer's product order
    int m_cntItem{0};
    // Array of pointers storing customer order items
    Item **m_lstItem{nullptr};

    // Class variable(static) that stores the width of the field, used for display purposes
    static size_t m_widthField;

  public:
    // Default constructor
    CustomerOrder();
    // 1-arg constructor
    CustomerOrder(const std::string &dataLine);
    // Getter: returns number of items ordered by customer (m_cntItem)
    size_t getCntItem() const;
    // Setter: sets the m_cntItem to param "count"
    void setCntItem(size_t count);
    // Copy constructor
    CustomerOrder(const CustomerOrder &);
    // Copy assignment operator, deleted
    CustomerOrder &operator=(const CustomerOrder &) = delete;
    // Move constructor
    CustomerOrder(CustomerOrder &&moveFromCustomerOrder) noexcept;
    // Move assignment operator
    CustomerOrder &operator=(CustomerOrder &&moveFromCustomerOrder) noexcept;
    // Getter: returns the name of the customer (m_name)
    std::string getName() const;
    // Getter: returns the name of the product ordered by customer (m_product)
    std::string getProduct() const;
    // Setter: sets the name of the customer(m_name) to param "name"
    void setName(const std::string &name);
    // Setter: sets the product name(m_product) to param "product"
    void setProduct(const std::string &product);
    // Subscript operator overload
    Item *operator[](int index);
    // Destructor
    ~CustomerOrder();
    // Returns true if all the items in the order have been filled, false otherwise
    bool isOrderFilled() const;
    // Returns true if the item specified by param "itemName" is filled
    bool isItemFilled(const std::string &itemName) const;
    // If the item stored at station specified by param "station" is available and current order contains that item and it is to be filled, this function fills that item
    void fillItem(Station &station, std::ostream &os);
    // Displays the contents of this CustomerOrder
    void display(std::ostream &os) const;
    // Getter: returns the width of the field(m_widthField)
    size_t getFieldWidth() const;
  };
}

#endif