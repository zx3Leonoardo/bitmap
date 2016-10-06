#include <iostream>
#include <string>

#include "bitmap.h"

using namespace std;

int main() {
  string data_path = "";
  Bitmap bitmap_test = new Bitmap();
  bitmap_test.ReadData(data_path);
  cout << "bitmap has been established" << endl;
  bitmap_test.CompressWAH();
  cout << "bitmap has been compressed" << endl;

  int query_input[8];
  while (1) {
    cout << "please input the ip address:" << endl;
    cout << "(missing address please type -1)" << endl;
    for (int i = 0; i < 8; ++i) {
      cin >> query_input[i];
    }
    bitmap_test.DecompressWAH(query_input);
    bitmap_test.QueryResponse();
  }
  return 0;
}

