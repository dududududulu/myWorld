#include <iostream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <fstream>
using namespace std;

/*

	///////////////////////////////////////////////////////////////

	File Name:				Segment.h
	Date of Creation:		20200104
	Latest Revise:			20200104

	Description:
		This file claims and defines template class Segment and Index for any type of statistic data and any dimension.

	Classes:
		


	///////////////////////////////////////////////////////////////

*/
template<typename U = double>
class _Empty
{
public:
	_Empty() {};
	~_Empty() {};
};
using iEmpty = _Empty<int>;
const iEmpty prior;
const _Empty<double> dprior;

template<typename U>
class _Data
{
	U value;
public:
	_Data(U val = 0) { value = val; };
	~_Data() {};
	U getVal()const { return value; };
};

template<typename U, typename V>
_Data<U> operator|(const _Empty<V>& emp, const U& val) {
	_Data<U> result(val);
	return result;
}

/////////////////////////////////////////////////////////
template<typename U>		// U is addable.
class _Segment;
template<typename U> class _uIndex;

template<typename U>
class _Segment
{
protected:
	U beg, end;
public:
	_Segment(U sbeg, U send) {
		beg = sbeg;
		end = send;
		if (beg > end)
		{
			U temp = beg;
			beg = end;
			end = temp;
		}
	};
	~_Segment() {};
	U getBeg()const { return beg; };
	U getEnd()const { return end; };
	operator _uIndex<U>() {
		_uIndex<U> result(beg, end, 1);
		return result;
	};
	friend ostream& operator<<<U>(ostream&, _Segment<U>&);		// << overload.
};

template<typename U>
ostream& operator<<(ostream& s, _Segment<U>& seg)
{
	cout << endl;
	cout << "- Display: ";
	cout << "Segment = [" << seg.beg << ", " << seg.end << "]" << endl;
	return s;
}

template<typename U>
_Segment<U> operator|(const _Data<U>& data, const U& val) {
	_Segment<U> result(data.getVal(), val);
	return result;
}

using _iSegment = _Segment<int>;


////////////////////////////////////////////////////////////////
	// _uIndex class.
template<typename U>
class _uIndex :public _Segment<U>
{
	U step;
public:
	_uIndex(U = 0, U = 1);
	_uIndex(U, U, U);
	~_uIndex() {};
	U getStep()const { return step; };

	void operator=(const _Segment<U>&);
	void operator=(const _uIndex<U>&);
	friend ostream& operator<<<U>(ostream&, const _uIndex<U>&);		// << overload.
};

template<typename U>
_uIndex<U>::_uIndex(U ibeg, U iend) :_Segment<U>(ibeg, iend) {
	step = 1;
}

template<typename U>
_uIndex<U>::_uIndex(U ibeg, U iend, U istep) : _Segment<U>(ibeg, iend) {
	step = istep;
}

template<typename U>
void _uIndex<U>::operator=(const _Segment<U>& seg)
{
	this->beg = seg.getBeg();
	this->end = seg.getEnd();
	step = 1;
}

template<typename U>
void _uIndex<U>::operator=(const _uIndex<U>& index)
{
	this->beg = index.beg;
	this->end = index.end;
	step = index.step;
}

template<typename U>
ostream& operator<<(ostream& s, const _uIndex<U>& index)
{
	U cur_index = index.beg;
	cout << endl << "- Display: ";
	cout << "Index(beg = " << index.beg << ", step = " << index.step << ", end = " << index.end << ")" << endl;
	cout << "         = [" << cur_index;
	cur_index = cur_index + index.step;;
	while (cur_index <= index.end)
	{
		cout << ", "<<cur_index ;
		cur_index = cur_index + index.step;
	}
	cout << "]" << endl;
	return s;
}

template<typename U>
_uIndex<U> operator|(const _Segment<U>& seg, const U& val) {
	_uIndex<U> result(seg.getBeg(), val, seg.getEnd());
	return result;
}

using _Index = _uIndex<int>;