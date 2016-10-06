#include <iostream>
#include <vector>

typedef std::vector<bool> BitMap;
typedef std::vector<int> WAH;

class Bitmap {
 public:
  
  // ReadData: import the path of ipdata.txt, update ip_data and bitmap
  void ReadData (string data_path); 

  // CompressWAH: compress bitmap to bitmapWAH
  void CompressWAH ();

  // DecompressWAH: input the index of eight ip data, update search_result
  void DecompressWAH (int search_index[]);

  // QueryResponse: operate on search_result and provide the output
  void QueryResponse ();
 
 private:
  std::vector<char[8]> ip_data;      // each element of ip_data saves one row of ipdata info
  BitMap bitmap[256*8];      // each element of bitmap is one column of the overall bitmaps
  WAH bitmapWAH[256*8];      // each element of bitmapWAH is transfered from the corresponding element in bitmap in the form of WAH
  BitMap search_result[8];
}
