#include "stdafx.h"
#include "Security.h"

class AbstPortfolio: public Security{
public:
	// Destructor
	virtual ~AbstPortfolio();
	
	// Prices the model with the relevant model
	virtual double price(std::shared_ptr<Model> model) const = 0;
	
	// Get the quantity of an asset given the index
	virtual double getQuantity(int index) const = 0;
	
	// General Function allowing to add securities to the portfolio
	virtual void addAsset(double quantity, std::shared_ptr<Security> security) = 0;
	
	// Static method to instantiate a portfolio object
	// Use of the factory method
	static std::shared_ptr<AbstPortfolio> newInstance();
};

