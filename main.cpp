#include <iostream>
#include <vector>
#include <string>

using namespace std;

// A class to handle the stock trading logic
class StockTrader {
private:
    vector<int> priceData;

public:
    // Constructor to initialize the price data
    StockTrader(const vector<int>& prices) {
        this->priceData = prices;
    }

    // Function to find all profitable buy and sell days
    void findProfitableTransactions() {
        int n = priceData.size();
        if (n <= 1) {
            cout << "Not enough data to perform a transaction.\n";
            return;
        }

        cout << "\n--- All Profitable Transactions ---\n";
        int currentDay = 0;
        int maxProfit = 0;
        int bestBuyDay = -1;
        int bestSellDay = -1;

        while (currentDay < n - 1) {
            // Find the next valley (buy day)
            // Skip days where the price is decreasing
            while ((currentDay < n - 1) && (priceData[currentDay + 1] <= priceData[currentDay])) {
                currentDay++;
            }

            // If we've reached the end, no more profitable transactions
            if (currentDay == n - 1) {
                break;
            }

            int buyDay = currentDay++;

            // Find the next peak (sell day)
            // Skip days where the price is increasing
            while ((currentDay < n - 1) && (priceData[currentDay + 1] >= priceData[currentDay])) {
                currentDay++;
            }

            int sellDay = currentDay;

            // Calculate and print the transaction details
            int currentProfit = priceData[sellDay] - priceData[buyDay];
            cout << "Buy on day " << buyDay << " at price $" << priceData[buyDay]
                 << ", Sell on day " << sellDay << " at price $" << priceData[sellDay]
                 << ". Profit: $" << currentProfit << ".\n";

            // Track the single most profitable transaction
            if (currentProfit > maxProfit) {
                maxProfit = currentProfit;
                bestBuyDay = buyDay;
                bestSellDay = sellDay;
            }
        }

        // Print the best overall transaction
        if (bestBuyDay != -1) {
            cout << "\n--- Overall Maximum Profit Transaction ---\n";
            cout << "Best buy on day " << bestBuyDay << " at price $" << priceData[bestBuyDay]
                 << ", best sell on day " << bestSellDay << " at price $" << priceData[bestSellDay]
                 << ".\nTotal maximum profit: $" << maxProfit << ".\n";
        } else {
            cout << "\nNo profitable transactions found.\n";
        }
    }
};

int main() {
    // Using a vector as a safer alternative to a C-style array
    vector<int> stockPrices = {100, 180, 260, 310, 40, 535, 695};

    // Create an instance of our StockTrader class
    StockTrader trader(stockPrices);

    // Call the function to analyze the transactions
    trader.findProfitableTransactions();

    return 0;
}