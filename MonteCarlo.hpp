#pragma once
class MonteCarlo
{
public:
	virtual void Solve() = 0;
	double get_price() const;
protected:
	double price;
};

