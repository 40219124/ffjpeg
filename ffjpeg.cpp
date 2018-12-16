// 包含头文件
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "jfif.h"
#include "bmp.h"
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;

int main(int argc, char *argv[])
{
    void *jfif = NULL;
    BMP   bmp  = {0};

    if (argc < 3) {
        printf(
            "jfif test program\n"
            "usage: %s -d filename decode jpg file to decode.bmp\n"
            "       %s -e filename encode bmp file to encode.jpg\n",
            argv[0], argv[0]
        );
        return 0;
    }

	ofstream times;
	times.open("timings.csv", ios_base::out | ios_base::trunc);
	double total = 0;
	int loops = 200;
	for (int i = 0; i < loops; i++) {
		if (strcmp(argv[1], "-d") == 0) {
			jfif = jfif_load(argv[2]);
			jfif_decode(jfif, &bmp);
			jfif_free(jfif);
			bmp_save(&bmp, "decode.bmp");
			bmp_free(&bmp);
		}
		else if (strcmp(argv[1], "-e") == 0) {
			bmp_load(&bmp, argv[2]);
			system_clock::time_point start = chrono::system_clock::now();
			jfif = jfif_encode(&bmp);
			system_clock::time_point end = chrono::system_clock::now();
			duration<double> diff = end - start;
			total += diff.count();
			times << diff.count() << endl;
			bmp_free(&bmp);
			jfif_save(jfif, "encode.jpg");
			jfif_free(jfif);
		}
	}
	total /= (double)loops;
	times << "avg" << endl << total << endl;

	times.close();

    return 0;
}

