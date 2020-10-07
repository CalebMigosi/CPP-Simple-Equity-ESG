#include "Portfolio.h"

class Portfolio: public AbstPortfolio{
	// Prices the model with the relevant model
	double price(std::shared_ptr<Model> model) const = 0;
	
	// Get the quantity of an asset given the index
	double getQuantity(int index) const = 0;
	
	// General Function allowing to add securities to the portfolio
	void addAsset(double quantity, std::shared_ptr<Security> security) = 0;	
};
