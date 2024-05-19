#include "RestaurantItem.h"

RestaurantItem::RestaurantItem(ProductType type, size_t count, double price)
{
    setType(type);
    setCount(count);
    setPrice(price);
}

const ProductType RestaurantItem::getType() const
{
    return this->type;
}

const size_t RestaurantItem::getCount() const
{
    return this->count;
}

const double RestaurantItem::getPrice() const
{
    return this->price;
}

void RestaurantItem::setCount(size_t count)
{
    if (count < 0) return;

    this->count = count;
}

void RestaurantItem::setPrice(double price)
{
    if (price < 0) return;

    this->price = price;
}

void RestaurantItem::setType(ProductType type)
{
    this->type = type;
}
