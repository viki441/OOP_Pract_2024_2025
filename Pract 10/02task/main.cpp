#include <iostream>
#include "Foodpanda.h"
#include "Restaurant.h"
#include "Order.h"
#include "String.h"

int main() {
    std::cout << "Starting test program..." << std::endl;

    // Create product lists
    String products1[] = { "Burger", "Fries", "Coke" };
    String products2[] = { "Pizza", "Pasta", "Water" };

    std::cout << "Milestone1 - Creating Restaurants..." << std::endl;
    Restaurant rest1("BurgerHouse", products1, 3, nullptr, 0);
    Restaurant rest2("Italiano", products2, 3, nullptr, 0);

    std::cout << "Milestone2 - Preparing Foodpanda..." << std::endl;
    Restaurant restArray[] = { rest1, rest2 };

    Foodpanda app(restArray, 2);
    std::cout << "Milestone3 - Foodpanda Ready" << std::endl;

    // Add new product
    std::cout << "Adding product 'Salad' to BurgerHouse..." << std::endl;
    app.addNewProductInRestaurant("BurgerHouse", "Salad");

    // Create and add an order
    std::cout << "Creating order for John Doe..." << std::endl;
    String orderItems1[] = { "Burger", "Fries" };
    Order order1("John Doe", orderItems1, 2);

    std::cout << "Adding order for 'John Doe' to BurgerHouse..." << std::endl;
    app.addOrderToRestaurant("BurgerHouse", order1);

    // Add a new restaurant
    std::cout << "Creating TokyoEats restaurant..." << std::endl;
    String products3[] = { "Sushi", "Ramen" };
    Restaurant rest3("TokyoEats", products3, 2, nullptr, 0);
    std::cout << "Adding new restaurant TokyoEats..." << std::endl;
    app.addNewRestaurant(rest3);

    // Add order to new restaurant
    std::cout << "Creating order for Alice..." << std::endl;
    String orderItems2[] = { "Sushi" };
    Order order2("Alice", orderItems2, 1);

    std::cout << "Adding order for 'Alice' to TokyoEats..." << std::endl;
    app.addOrderToRestaurant("TokyoEats", order2);

    // Print restaurant state
    std::cout << "\n--- Final Restaurant Info ---\n" << std::endl;
    const Restaurant* allRests = app.getRestaurants();

    // Add this method to your Foodpanda class if needed
    unsigned int totalRestaurants = 3; // hardcoded fallback if you don’t expose a getter

    for (unsigned int i = 0; i < totalRestaurants; ++i) {
        std::cout << "Restaurant: " << allRests[i].getName() << std::endl;
        std::cout << "Products: ";
        for (unsigned int j = 0; j < allRests[i].getCount(); ++j) {
            std::cout << allRests[i].getList()[j] << " ";
        }
        std::cout << std::endl;
        std::cout << "Receipts: " << allRests[i].getReceipts() << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }

    std::cout << "Test complete." << std::endl;
    return 0;
}
