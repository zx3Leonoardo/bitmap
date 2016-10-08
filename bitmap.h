#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cmath>
struct IP {
	unsigned char data[8];
};

typedef std::vector<IP> IPData;
typedef std::vector<bool> Bitmap;
typedef std::vector<int> CompressedBitmap;

class BitMap {
public:

	// generate ip_data from ipdata.txt
	void ReadData(const std::string &data_path);

	// generate bitmap from ip_data
	void GenerateBitmap();

	// compress single column bitmap to compressed_bitmap
	CompressedBitmap CompressSingleBitmap(Bitmap &bitmap);

	// compress bitmap to compressed_bitmap
	void Compress() {
		for (int i = 0; i < 256 * 8; ++i) {
			compressed_bitmap[i] = CompressSingleBitmap(bitmap[i]);
		}
	}

	// decompress single column compressed_bitmap to bitmap
	Bitmap DecompressSingleBitmap(const CompressedBitmap &compressed_bitmap);

	// respond to query input
	void ResponseQuery(const int query_index[]);

private:
	IPData ip_data;      // each element of ip_data saves one row of ip info
	Bitmap bitmap[256 * 8];      // each element of bitmap is one column of the overall bitmap
	CompressedBitmap compressed_bitmap[256 * 8];      // each element of compressed_bitmap is transfered from the corresponding element in bitmap
	int sample_number;      // sample_number is the number of samples in ipdata.txt
};
