// Random.cpp: implementation of the CRandom class.
//
//////////////////////////////////////////////////////////////////////

#include "Random.h"
#include <time.h>
#include <math.h>
#include <string.h>
#include ".\random.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRandom::CRandom()
{
	rand_shuffle("");
}

CRandom::~CRandom()
{

}

void CRandom::rand_shuffle(const char* key)
{
	int i, j;
	unsigned long tmp = 817171717;

	union
	{
		char keystr[200];
		long keylng[50];
	} ky;

	/////////////////////////////////////////////////////////////////
	// Fill the key array with starting numbers
	/////////////////////////////////////////////////////////////////
	for (i = 0; i < 50; i++)
		ky.keylng[i] = 123456 + i * 997;

	/////////////////////////////////////////////////////////////////
	// Use system date and time if key string is zero length
	/////////////////////////////////////////////////////////////////
	if ((j = (int)strlen(key)) == 0)
	{
		_strdate_s(ky.keystr);
		_strtime_s(&ky.keystr[8], 10);
	}
	else
	{
		for (i = 0; i < j; i++)
			ky.keystr[i % 200] ^= key[i];
	}

	/////////////////////////////////////////////////////////////////
	// Use the key array to initialize the table
	/////////////////////////////////////////////////////////////////
	for (i = 0; i < 55; i++)
		tmp = r.table[i] = ((tmp << 3) ^ ky.keylng[i % 50]) | i;

	/////////////////////////////////////////////////////////////////
	// Use the key array to initialize the shuffle table
	/////////////////////////////////////////////////////////////////
	for (i = 0; i < 45; i++)
		tmp = r.shuff[i] = ((tmp << 3) ^ ky.keylng[i]) | i;

	/////////////////////////////////////////////////////////////////
	// Initialize pointers into the table
	/////////////////////////////////////////////////////////////////
	r.ptr1 = r.table + 54;
	r.ptr2 = r.table + 23;

	/////////////////////////////////////////////////////////////////
	// Initialize the last random number
	/////////////////////////////////////////////////////////////////
	r.last = 0;

	/////////////////////////////////////////////////////////////////
	// Warm it up
	/////////////////////////////////////////////////////////////////
	for (i = 0; i < 997; i++)
		rand_long();

}

unsigned long CRandom::rand_long()
{
	unsigned long tmp, * shuffptr;

	/////////////////////////////////////////////////////////////////
	// Add two table entries
	/////////////////////////////////////////////////////////////////
	tmp = (*r.ptr1 += *r.ptr2);

	/////////////////////////////////////////////////////////////////
	// Decrement first index, keeping in table range 0 through 54
	/////////////////////////////////////////////////////////////////
	if (r.ptr1 > r.table)
		r.ptr1--;
	else
		r.ptr1 = r.table + 54;

	/////////////////////////////////////////////////////////////////
	// Decrement second index, keeping in table range 0 through 54
	/////////////////////////////////////////////////////////////////
	if (r.ptr2 > r.table)
		r.ptr2--;
	else
		r.ptr2 = r.table + 54;

	/////////////////////////////////////////////////////////////////
	// Use random number to index into shuffle table
	/////////////////////////////////////////////////////////////////
	shuffptr = r.shuff + (r.last % 45);

	/////////////////////////////////////////////////////////////////
	// Grab from the shuffle table
	/////////////////////////////////////////////////////////////////
	r.last = *shuffptr;

	/////////////////////////////////////////////////////////////////
	// Put the new random number in the shuffle table
	/////////////////////////////////////////////////////////////////
	*shuffptr = tmp;

	/////////////////////////////////////////////////////////////////
	// Return the number grabbed from the shuffle table
	/////////////////////////////////////////////////////////////////
	return(r.last);
}

unsigned short CRandom::rand_short()
{
	return (rand_long() & 0xFFFF);
}

double CRandom::rand_frac()
{
	return (rand_long() / __MAXLONG);
}

int CRandom::rand_int_range(int a, int b)
{
	return((int)(rand_long() % (b - a + 1) + a));
}

double CRandom::rand_double(double a, double b)
{
	return((rand_long() / __MAXLONG) * (b - a) + a);
}

double CRandom::rand_normal(double mean, double std_dev)
{
	double u1, u2, x;

	u1 = rand_long() / __MAXLONG;
	u2 = rand_long() / __MAXLONG;

	x = sqrt(-2.0 * log(u1)) * cos(TWOPI * u2);

	return(mean + std_dev * x);
}

double CRandom::rand_exponential(double mean)
{
	return(-mean * log(rand_long() / __MAXLONG));
}

void CRandom::rand_long_buf(int n, long* buf)
{
	unsigned long tmp, * shuffptr;

	while (n)
	{
		tmp = (*r.ptr1 += *r.ptr2);

		if (r.ptr1 > r.table)
			r.ptr1--;
		else
			r.ptr1 = r.table + 54;

		if (r.ptr2 > r.table)
			r.ptr2--;
		else
			r.ptr2 = r.table + 54;

		shuffptr = r.shuff + (r.last % 45);

		r.last = *shuffptr;

		*shuffptr = tmp;

		buf[--n] = r.last;
	}
}

//CString CRandom::rand_string(int nLen)
//{
//	CString szString;
//	CString szKey("abcdefghijklmnopqrstuvwxyz0123456789");
//	int i, index, size;

//	szString.Empty();
//	size = szKey.GetLength() - 1;

//	for(i=0; i<nLen; i++)
//	{
//		index = rand_int_range(0, size);
//		szString += szKey.Mid(index, 1);
//	}

//	return szString;
//}


void CRandom::Initialize()
{
	rand_shuffle("");
}


void CRandom::Initialize(char* key)
{
	rand_shuffle(key);
}
