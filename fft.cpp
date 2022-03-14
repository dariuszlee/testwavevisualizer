#include "fft.h"

Complex** fft(sample** sampleData, int nFrames, int nChans)
{
	Complex** x = new Complex*[nChans];
	for(int c = 0; c < nChans; c++){
		x[c] = new Complex[nFrames];
		for ( int j = 0; j < nFrames; j++){
			x[c][j] = sampleData[c][j];
		}
		/* CArray x(test, nFrames); */


		// DFT
		/* unsigned int N = x.size(), k = N, n; */
		unsigned int N = nFrames, k = N, n;
		double thetaT = 3.14159265358979323846264338328L / N;
		Complex phiT = Complex(cos(thetaT), -sin(thetaT)), T;
		while (k > 1)
		{
			n = k;
			k >>= 1;
			phiT = phiT * phiT;
			T = 1.0L;
			for (unsigned int l = 0; l < k; l++)
			{
				for (unsigned int a = l; a < N; a += n)
				{
					unsigned int b = a + k;
					Complex t = x[c][a] - x[c][b];
					x[c][a] += x[c][b];
					x[c][b] = t * T;
				}
				T *= phiT;
			}
		}
		// Decimate
		unsigned int m = (unsigned int)log2(N);
		for (unsigned int a = 0; a < N; a++)
		{
			unsigned int b = a;
			// Reverse bits
			b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
			b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
			b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
			b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
			b = ((b >> 16) | (b << 16)) >> (32 - m);
			if (b > a)
			{
				Complex t = x[c][a];
				x[c][a] = x[c][b];
				x[c][b] = t;
			}
		}
		//// Normalize (This section make it not working correctly)
		//Complex f = 1.0 / sqrt(N);
		//for (unsigned int i = 0; i < N; i++)
		//	x[i] *= f;
	}

	return x;
}
