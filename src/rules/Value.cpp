#include "Value.h"

bool compare_primitives(const PrimitiveValue *lhs, const PrimitiveValue *rhs)
{
	return (*lhs) == (*rhs);
}

PrimitiveValue::PrimitiveValue()
{}

PrimitiveValue::~PrimitiveValue()
{}

PrimitiveValue::Type PrimitiveValue::type() const
{
	return PrimitiveValue::Type::UNKNOWN;
}

bool PrimitiveValue::is_float()
{
	return false;
}

bool PrimitiveValue::is_integer()
{
	return false;
}

bool PrimitiveValue::is_number()
{
	return false;
}

bool PrimitiveValue::is_symbol()
{
	return false;
}

bool PrimitiveValue::is_string()
{
	return false;
}

bool PrimitiveValue::is_multifield()
{
	return false;
}

bool PrimitiveValue::is_void()
{
	return false;
}

bool PrimitiveValue::operator==(const PrimitiveValue &o) const
{
	return type() == o.type();
}

//FLOAT VALUE

FloatValue::FloatValue(float value) : value(value)
{}

PrimitiveValue::Type FloatValue::type() const
{
	return PrimitiveValue::Type::FLOAT;
}

bool FloatValue::is_float()
{
	return true;
}

bool FloatValue::is_number()
{
	return true;
}

bool FloatValue::operator==(const PrimitiveValue &o) const
{
	if(type() != o.type())
		return false;

	return value == dynamic_cast<const FloatValue &>(o).value;
}

//INTEGER VALUE

IntegerValue::IntegerValue(int value) : value(value)
{}

PrimitiveValue::Type IntegerValue::type() const
{
	return PrimitiveValue::Type::INTEGER;
}

bool IntegerValue::is_integer()
{
	return true;
}

bool IntegerValue::is_number()
{
	return true;
}

bool IntegerValue::operator==(const PrimitiveValue &o) const
{
	if(type() != o.type())
		return false;

	return value == dynamic_cast<const IntegerValue &>(o).value;
}

//SYMBOL VALUE

SymbolValue::SymbolValue(Symbol value) : value(value)
{}

PrimitiveValue::Type SymbolValue::type() const
{
	return PrimitiveValue::Type::SYMBOL;
}

bool SymbolValue::is_symbol()
{
	return true;
}

bool SymbolValue::operator==(const PrimitiveValue &o) const
{
	if(type() != o.type())
		return false;

	return value == dynamic_cast<const SymbolValue &>(o).value;
}

//STRING VALUE

StringValue::StringValue(std::string value) : value(value)
{}

PrimitiveValue::Type StringValue::type() const
{
	return PrimitiveValue::Type::STRING;
}

bool StringValue::is_string()
{
	return true;
}

bool StringValue::operator==(const PrimitiveValue &o) const
{
	if(type() != o.type())
		return false;

	return value == dynamic_cast<const StringValue &>(o).value;
}

//MULTIFIELD VALUE

MultifieldValue::MultifieldValue(std::vector<PrimitiveValue *> value) : value(value)
{}

MultifieldValue::~MultifieldValue()
{
	for(auto field : value)
		delete field;
}

PrimitiveValue::Type MultifieldValue::type() const
{
	return PrimitiveValue::Type::MULTIFIELD;
}

bool MultifieldValue::is_multifield()
{
	return true;
}

bool MultifieldValue::operator==(const PrimitiveValue &o) const
{
	if(type() != o.type())
		return false;

	return std::equal(value.begin(),
					  value.end(),
					  dynamic_cast<const MultifieldValue &>(o).value.begin(),
					  compare_primitives);
}

PrimitiveValue::Type VoidValue::type() const
{
	return PrimitiveValue::Type::VOID;
}

bool VoidValue::is_void()
{
	return true;
}
