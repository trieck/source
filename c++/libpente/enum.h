/////////////////////////////////////////////////////////////////////////////
//
// ENUM.H : Enumerator interface
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
//

#ifndef __ENUM_H__
#define __ENUM_H__

/////////////////////////////////////////////////////////////////////////////
template <typename T>
class Enumerator
{
public:
	Enumerator(typename T::const_iterator i1, typename T::const_iterator &i2) 
		: current(i1), begin(i1), end(i2) {
	}

	Enumerator(const Enumerator &rhs) {
		*this = rhs;
	}

	Enumerator<typename T>& operator = (const Enumerator &rhs) {
		if (this != &rhs) {
			current = rhs.current;
			begin = rhs.begin;
			end = rhs.end;
		}
		return *this;
	}

	typename T::const_reference next() {
		T::const_reference c = *current;

		if (current < end)
			current++;

		return c;
	}

	bool hasNext() const {
		return current != end;
	}

	void reset() {
		current = begin;
	}

private:
	typename T::const_iterator begin, current, end;
};

#endif // __ENUM_H__
