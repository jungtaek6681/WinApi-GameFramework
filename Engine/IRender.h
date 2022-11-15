#pragma once
struct IRender abstract
{
	virtual void	Render() = 0;

	float			GetZOrder() { return zOrder; }
	void			SetZOrder(float zOrder) { this->zOrder = zOrder; }

	float			zOrder = 0;
};

