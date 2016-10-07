#include "bitmap.h"

void BitMap::ReadData(const string &data_path)
{
  IP ip;
  BM bitmap_row;
  string str;
  char *ch,*token;
  int cnt=0;
  
  ifstream file(data_path);

  while(getline(file,str))
    {
      ch =new char[str.length()+1];
      strcpy(ch,str.c_str());

      token = strtok(ch,",");  

      while(token!=NULL)
        {
          if(cnt<=7 && atoi(token)<256)
            {
              ip.data[cnt] = atoi(token);
              ++cnt;
            }
          token=strtok(NULL,",");
        }
      ip_data.push_back(ip);
      cnt = 0;
    }
  
  unsigned int i,j,k;
  for(i = 0;i < ip_data.size(); ++i) {
    for(j = 0;j < 8; ++j) {
      bitmap_row.data[j * 256+int(ip_data[i].data[j])-1] = 1;
    }
    bitmap_ini.push_back(bitmap_row);
    for( k = 0;k < 256 * 8; ++k)
      bitmap_row.data[k] = 0;
  }

  //transform
  for(i = 0;i < 256 * 8; ++i) {
    for(j = 0;j < ip_data.size(); ++j)
      bitmap[i].push_back(bitmap_ini[j].data[i]);
  }
  file.close();
  sample_number = ip_data.size();
}

CompressedBitmap Bitmap::CompressSingleBitmap (Bitmap &bitmap) {
  CompressedBitmap compressed_bitmap;

  // align bitmap to n*31 bit length
  int group_number = ceil(bitmap.size() / 31);
  for (int i = 0; i < group_number * 31 - bitmap.size(); ++i) {
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
      temp = 0;
      fill_counter = 0;
      for (int j = 0; j < 31; ++j) {
        temp = (temp << 1) + bitmap[i * 31 + j];
      }
      compressed_bitmap.push_back(temp);
    } else {      // fill code
      if (fill_counter == 0) {
        temp = (2 + fill_type) << 30;
        temp += 1;
        ++fill_counter;
        previous_fill_type = fill_type;
      } else {
        if (previous_fill_type == fill_type) {
          temp += 1;
          ++fill_counter;
        } else {
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

void BitMap::Compress () {
  for (int i = 0; i < 256 * 8; ++i) {
    compressed_bitmap[i] = CompressSingleBitmap(bitmap[i]);
  }
}

Bitmap BitMap::DecompressSingleBitmap (const CompressedBitmap &compressed_bitmap) {
  Bitmap bitmap;
  int temp;
  bool current = 0;

  for (int i = 0; i < compressed_bitmap.size(); ++i) {
    temp = compressed_bitmap[i];
    if (temp >> 31 == 0) {      // literal mode
      for (int j = 1; j < 32; ++j) {
        current = (temp << j) >> 31;
        bitmap.push_back(current);
      }
    } else {      // fill mode
      current = (temp << 1) >> 31;
      for (int j = 0; j < 31; ++j) {
        bitmap.push_back(current);
      }
    }
  }

  return bitmap;
}

void BitMap::ResponseQuery (const int query_index[8]) {
  Bitmap search_index(sample_number, true);
  Bitmap temp;

  for (int i = 0; i < 8; ++i) {
    if (query_index[i] != -1) {
      temp = DecompressSingleBitmap(compressed_bitmap[i*256 + query_index[i]]);
      for (int j = 0; j < sample_number; ++j) {
        search_index[j] &= temp[j];
      }
    }
  }

  IP output;
  int count = 0;
  for (int i = 0; i < sample_number; ++i) {
    if (search_index == 1) {
      output = ip_data[i].data;
      ++count;
      for (int j = 0; j < 8; ++j) {
        std::cout << output[j] << "  ";
      }
      std::cout << std::endl;
    }
  }
  if (count == 0) {
    std::cout << "record not found" << std::endl;
  } else {
    std::cout << count << "records found" << std::endl;
  }
}
