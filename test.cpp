#include "bitmap.h"

using namespace std;

int main() {
	string data_path = "ipData.txt";
	BitMap *bitmap_test = new BitMap();
	bitmap_test->ReadData(data_path);
	cout << "ip_data has been saved" << endl;
	bitmap_test->GenerateBitmap();
	cout << "bitmap has been established" << endl;
	bitmap_test->Compress();
	cout << "bitmap has been compressed" << endl;

	int query_index[8];
	char option;
        bool illegal_input;
	while (1) {
		cout << "please input the ip address:" << endl;
		cout << "(missing address please type -1)" << endl;
		for (int i = 0; i < 8; ++i) {
			cin >> query_index[i];
		}

                illegal_input = 0;
                for (int i = 0; i < 8; ++i) {
                  if (query_index[i] > 255 || query_index[i] < -1) {
                    illegal_input = 1;
                    break;
                  }
                }
                if (illegal_input) {
                  cout << "illegal query input, please try again" << endl << endl;
                  continue;
                }

		bitmap_test->ResponseQuery(query_index);

		cout << "continue or not?  y/n" << endl;
		cin >> option;
		if (option == 'n')
			break;
	}
	return 0;
}
