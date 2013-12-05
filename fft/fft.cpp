

#include "fft.h"

#define PI 3.1415926
#define NR_END 1
#define m 4

float *vector(long nl, long nh);

/*void bitreverse(void)
{
	int f = 0;
	int ag = 0;
	div_t res;

	for(int k = 0; k < N; k++)
	{
		n = 0;
		f = ag;

		for(int p = (m-1); p >= 0; p -= 1)
		{
			res = div(f, 2);
			n = n + res.rem * pow(2, p);
			f = res.quot;
		}

		xr[k] = x[n];
		xi[k] = x[n];

		ag += 1;

	}
}*/


void fft(float signal[], int N)
{
	int space, s, width, r, w, itop, ibot;
	float *xr, *xi, wtfaci, wtfacr, tmpr, tmpi;

	int f = 0, n;
	int ag = 0;
	div_t res;

	xr = vector(1, N);
	xi = vector(1, N);

	// Bit reverse

	for(int k = 0; k < N; k++)
	{
		n = 0;
		f = ag;

		for(int p = (m-1); p >= 0; p -= 1)
		{
			res = div(f, 2);
			n = n + res.rem * pow(2, p);
			f = res.quot;
		}

		xr[k] = signal[n];
		xi[k] = signal[n];

		ag += 1;

	}

	// The Transform

	for(int l = 1; l <= m; l++)
	{
		space = pow(2, l);
		s = N/space;
		width = space/2;

		for(int j = 0; j < width; j++)
		{
			r = s * j;
			ag = w * r;
			wtfacr = cos(ag);
			wtfaci = sin(ag);

			for(itop = j; itop <= (N-2); itop += space)
			{
				ibot = itop + width;
				tmpr = xr[ibot] * wtfacr - xi[ibot] * wtfaci;
				tmpi = xr[ibot] * wtfaci + xi[ibot] * wtfacr;
				xr[ibot] = xr[itop] - tmpr;
				xr[itop] = xr[itop] + tmpr;
				xi[ibot] = xi[itop] - tmpi;
				xi[itop] = xi[itop] + tmpi;
			}
		}
	}

	// This is a good place to return something
	for(k = 0; k < N; k++)
	{
		signal[k] = (xi[k] * xi[k]) + (xr[k] * xr[k]);
	}

}

float *vector(long nl, long nh)
{
	float *v;

	v = (float *)malloc((size_t) ((nh - nl + 1 + NR_END) *sizeof(float)));

	return v - nl + NR_END;
}