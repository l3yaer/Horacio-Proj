#ifndef _VALUE_H_
#define _VALUE_H_

#include <string>
#include <vector>

typedef std::string Symbol;

class PrimitiveValue
{
public:
	enum Type
	{
		UNKNOWN,
		FLOAT,
		INTEGER,
		SYMBOL,
		STRING,
		MULTIFIELD,
		VOID
	};

protected:
	PrimitiveValue();

public:
	virtual ~PrimitiveValue();

	virtual Type type() const;
	virtual bool is_float();
	virtual bool is_integer();
	virtual bool is_number();
	virtual bool is_symbol();
	virtual bool is_string();
	virtual bool is_multifield();
	virtual bool is_void();

	virtual bool operator==(const PrimitiveValue &o) const;
};


class FloatValue : public PrimitiveValue
{
public:
	FloatValue(float value);

	Type type() const override;
	bool is_float() override;
	bool is_number() override;

	bool operator==(const PrimitiveValue &o) const override;

	float value;
};

class IntegerValue : public PrimitiveValue
{
public:
	IntegerValue(int value);

	Type type() const override;
	bool is_integer() override;
	bool is_number() override;

	bool operator==(const PrimitiveValue &o) const override;

	int value;
};

class SymbolValue : public PrimitiveValue
{
public:
	SymbolValue(Symbol value);

	Type type() const override;
	bool is_symbol() override;

	bool operator==(const PrimitiveValue &o) const override;

	Symbol value;
};

class StringValue : public PrimitiveValue
{
public:
	StringValue(std::string value);

	Type type() const override;
	bool is_string() override;

	bool operator==(const PrimitiveValue &o) const override;

	std::string value;
};

class MultifieldValue : public PrimitiveValue
{
public:
	MultifieldValue(std::vector<PrimitiveValue *> value);
	~MultifieldValue();

	Type type() const override;
	bool is_multifield() override;

	bool operator==(const PrimitiveValue &o) const override;

	std::vector<PrimitiveValue *> value;
};

class VoidValue : public PrimitiveValue
{
public:
	Type type() const override;
	bool is_void() override;
};

#endif //_VALUE_H_
