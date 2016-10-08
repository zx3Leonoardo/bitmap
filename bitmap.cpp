#include "bitmap.h"
using namespace std;

void BitMap::ReadData(const std::string &data_path)
{
	IP ip;
	std::string str;
	char *ch, *token;
	int cnt = 0,flag = 0;

	std::ifstream file("ipData.txt",std::ifstream::in);

	while (getline(file, str))
	{
		ch =new char[str.length()+1];
      		strcpy(ch,str.c_str());

      		token = strtok(ch,",");  

     		while(token!=NULL)
      		{
			if (cnt<4)
			{
				ip.data[cnt] = atoi(token);
				cnt++;
			}
			else 
			{
				if (cnt<=8 && cnt>4)
				{
					ip.data[cnt-1] = atoi(token);
					cnt++;
				}
				else 
					if (cnt==4)
						flag++;
			}
			token=strtok(NULL,",");
			if(flag==1)
			{
				flag = 0;
				cnt = 5;
			}
		}
		ip_data.push_back(ip);
		cnt = 0;
	}

	file.close();
	sample_number = ip_data.size();
}

void BitMap::GenerateBitmap() {
	// initialize bitmap
	Bitmap temp(sample_number, 0);
	for (int i = 0; i < 256 * 8; ++i) {
		bitmap[i] = temp;
	}

	// transform ip_data to bitmap
	for (int i = 0; i < sample_number; ++i) {
		for (int j = 0; j < 8; ++j)
			bitmap[j * 256 + int(ip_data[i].data[j])][i] = 1;
	}
}

CompressedBitmap BitMap::CompressSingleBitmap(Bitmap &bitmap) {
	CompressedBitmap compressed_bitmap;

	// align bitmap to n*31 bit length
	int group_number = ceil(double(bitmap.size()) / 31);
	int align_number = group_number * 31 - bitmap.size();
	for (int i = 0; i < align_number; ++i) {
		bitmap.push_back(0);
	}

	bool fill_flag = 0, fill_type = 0, previous_fill_type = 0;
	unsigned int temp = 0;
	int fill_counter = 0;

	for (int i = 0; i < group_number; ++i) {

		// judge whether the current group is literal or fill (default)
		fill_flag = 1;
		fill_type = bitmap[i * 31];
		for (int j = 1; j < 31; ++j) {
			if (bitmap[i * 31 + j] != fill_type) {
				fill_flag = 0;
				break;
			}
		}

		// compression coding
		if (fill_flag == 0) {      // literal code
			if (temp != 0) {
				compressed_bitmap.push_back(temp);
			}
			temp = 0;
			fill_counter = 0;
			for (int j = 0; j < 31; ++j) {
				temp = (temp << 1) + bitmap[i * 31 + j];
			}
			compressed_bitmap.push_back(temp);
			temp = 0;
		}
		else {      // fill code
			if (fill_counter == 0) {
				temp = (2 + fill_type) << 30;
				temp += 1;
				++fill_counter;
				previous_fill_type = fill_type;
			}
			else {
				if (previous_fill_type == fill_type) {
					temp += 1;
					++fill_counter;
				}
				else {
					compressed_bitmap.push_back(temp);
					temp = (2 + fill_type) << 30;
					temp += 1;
					fill_counter = 1;
					previous_fill_type = fill_type;
				}
			}
		}
	}
	if (fill_flag) {
		compressed_bitmap.push_back(temp);
	}

	return compressed_bitmap;
}

Bitmap BitMap::DecompressSingleBitmap(const CompressedBitmap &compressed_bitmap) {
	Bitmap bitmap;
	unsigned int temp, length;
	//int current = 0;
	bool current = 0;

	for (size_t i = 0; i < compressed_bitmap.size(); ++i) {
		temp = compressed_bitmap[i];
		if (temp >> 31 == 0) {      // literal mode
			for (int j = 1; j < 32; ++j) {
				current = (temp << j) >> 31;
				bitmap.push_back(current);
			}
		}
		else {      // fill mode
			current = (temp << 1) >> 31;
			length = 31 * ((temp << 2) >> 2);
			for (unsigned int j = 0; j < length; ++j) {
				bitmap.push_back(current);
			}
		}
	}

	return bitmap;
}

void BitMap::ResponseQuery(const int query_index[8]) {
	Bitmap search_index(sample_number, true);
	Bitmap temp;

	for (int i = 0; i < 8; ++i) {
		if (query_index[i] != -1) {
			temp = DecompressSingleBitmap(compressed_bitmap[i * 256 + query_index[i]]);
			for (int j = 0; j < sample_number; ++j) {
				search_index[j] = search_index[j] & temp[j];
			}
		}
	}

	int count = 0;
	for (int i = 0; i < sample_number; ++i) {
		if (search_index[i]) {
			++count;
			std::cout << "from " << int(ip_data[i].data[0]);
			for (int j = 1; j < 4; ++j) {
				std::cout << "," << int(ip_data[i].data[j]);
			}
			std::cout << " to " << int(ip_data[i].data[4]);
			for (int j = 5; j < 8; ++j) {
				std::cout << "," << int(ip_data[i].data[j]);
			}
			std::cout << std::endl;
		}
	}
	if (count == 0) {
		std::cout << "record not found" << std::endl;
	}
	else {
		std::cout << count << " records found" << std::endl;
	}
}
