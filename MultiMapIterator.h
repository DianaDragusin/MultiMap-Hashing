#pragma once
#include "MultiMap.h"

class MultiMap;

class MultiMapIterator
{
	friend class MultiMap;

private:
	const MultiMap& col;
	int current;

	MultiMapIterator(const MultiMap& c);

public:
    bool modify( TElem change);
	TElem getCurrent()const;
	bool valid() const;
	void next();
	void first();
};

