// Random.h: interface for the CRandom class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

struct rand_array
{
	unsigned long* ptr1;
	unsigned long* ptr2;
	unsigned long table[55];
	unsigned long shuff[45];
	unsigned long last;
};

class CRandom
{
public:
	void rand_long_buf(int n, long* buf);
	double rand_exponential(double mean);
	double rand_normal(double mean, double std_dev);
	double rand_double(double a, double b);
	int rand_int_range(int a, int b);
	double rand_frac(void);
	unsigned short rand_short(void);
	unsigned long rand_long(void);
	void rand_shuffle(const char* key);
	CRandom();
	virtual ~CRandom();

	//	CString rand_string(int nLen=12);
	void Initialize();
	void Initialize(char* key);
	rand_array r;
};

//typedef CTypedPtrArray<CPtrArray, CRandom*> CRandomArray;

#define TWOPI	6.283185307179586
#define __MAXLONG 4294967295.0

