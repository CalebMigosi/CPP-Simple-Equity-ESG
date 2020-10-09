#pragma once
#include "Model.h"
#include "stdafx.h"

//INTERFACE

// Interface for an equity security priced by a specific model
class Security{
public:
	virtual double price(std::shared_ptr<Model> model) const = 0;
	virtual ~Security(){};
};
