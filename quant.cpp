/* ����ͷ�ļ� */
#include "quant.h"
#include "ParallelHelp.h"
#include <thread>
#include <vector>

using namespace std;

/* ȫ�ֱ������� */
const int STD_QUANT_TAB_LUMIN[64] =
{
	16, 11, 10, 16, 24, 40, 51, 61,
	12, 12, 14, 19, 26, 58, 60, 55,
	14, 13, 16, 24, 40, 57, 69, 56,
	14, 17, 22, 29, 51, 87, 80, 62,
	18, 22, 37, 56, 68, 109,103,77,
	24, 35, 55, 64, 81, 104,113,92,
	49, 64, 78, 87, 103,121,120,101,
	72, 92, 95, 98, 112,100,103,99,
};

const int STD_QUANT_TAB_CHROM[64] =
{
	17, 18, 24, 47, 99, 99, 99, 99,
	18, 21, 26, 66, 99, 99, 99, 99,
	24, 26, 56, 99, 99, 99, 99, 99,
	47, 66, 99, 99, 99, 99, 99, 99,
	99, 99, 99, 99, 99, 99, 99, 99,
	99, 99, 99, 99, 99, 99, 99, 99,
	99, 99, 99, 99, 99, 99, 99, 99,
	99, 99, 99, 99, 99, 99, 99, 99,
};


void quant_encode_par(int* du, int* qtab, int loopEnd) {
	for (int i = 0; i < loopEnd; i++) {
		du[i] /= qtab[i];
	}
}
/* ����ʵ�� */
void quant_encode(int du[64], int qtab[64])
{
	if (ParallelHelp::ThreadCount() > 1) {
		int total = 64;
		int loopEnd = 64 / ParallelHelp::ThreadCount();
		vector<thread> threads;
		int iVal;
		for (int i = 0; i < ParallelHelp::ThreadCount() - 1; i++) {
			iVal = i * loopEnd;
			threads.push_back(thread(quant_encode_par, &du[iVal], &qtab[iVal], loopEnd));
			total -= loopEnd;
		}
		iVal = loopEnd * (ParallelHelp::ThreadCount() - 1);
		quant_encode_par(&du[iVal], &qtab[iVal], total);
		for (thread &t : threads) {
			t.join();
		}
	}
	else {
		int i;
		for (i = 0; i < 64; i++) {
			du[i] /= qtab[i];
		}
	}
}

void quant_decode(int du[64], int qtab[64])
{
	int i; for (i = 0; i < 64; i++) du[i] *= qtab[i];
}






