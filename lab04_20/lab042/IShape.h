#pragma once

class IShape // интерфейс "плоская фигура"
{
public:
	virtual ~IShape(){};
	virtual double GetArea() const = 0; // площадь образа
	virtual double GetPerimeter() const = 0; // периметр образа
	virtual std::string ToString() const = 0; // описание фигуры
	virtual std::uint32_t GetOutlineColor() const = 0; // цвет контура
};
