#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct IP {
  unsigned char data[8];
};

struct BM
{
	int data[256*8+1];
	BM()
	{
		for(int i=0;i<256*8;i++)
			data[i] = 0;
	}
};
typedef std::vector<BM> bitmap;
typedef vector<int> final_bitmap[256*8+1];

typedef std::vector<IP> IPData;
typedef std::vector<bool> Bitmap;
typedef std::vector<int> CompressedBitmap;

class BitMap {
 public:
  
  // ReadData: import the path of ipdata.txt, update ip_data and bitmap
  void ReadData (string data_path); 

  // compress bitmap to compressed_bitmap
  CompressedBitmap CompressSingleBitmap (Bitmap &bitmap);
  void Compress ();

  // DecompressWAH: input the index of eight ip data, update search_result
  Bitmap DecompressSingleBitmap (const CompressedBitmap &compressed_bitmap);
  void ResponseQuery (const int query_index []);
 
 private:
  IPData ip_data;      // each element of ip_data saves one row of ipdata info
  Bitmap bitmap[256*8];      // each element of bitmap is one column of the overall bitmaps
  CompressedBitmap compressed_bitmap[256*8];      // each element of bitmapWAH is transfered from the corresponding element in bitmap in the form of WAH
  int sample_number;
}
