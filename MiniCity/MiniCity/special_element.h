#pragma once

class Special_element
{
protected:
	int maintenance_cost;
public:
	virtual ~Special_element() = default;

	int get_maintenance_cost() const
	{
		return maintenance_cost;
	}

};