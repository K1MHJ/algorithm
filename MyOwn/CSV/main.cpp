#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <regex>
using namespace std;


class CSVFile{
private:
  float *m_data;
  int m_x,m_y;
  float m_gap_x;
  float m_gap_y;
public:
  CSVFile(){
    m_data = nullptr;
  }
  ~CSVFile(){
    if(m_data != nullptr){
      free(m_data);
    }
  }
  void reset(int x, int y, float gap_x, float gap_y)
  {
    m_x = x;
    m_y = y;
    m_gap_x = gap_x;
    m_gap_y = gap_y;

    if(m_data != nullptr){
      free(m_data);
    }
    m_data = (float*)malloc(x * y * sizeof(float));
    memset(m_data, 0, x * y * sizeof(float)); 
  }
  void csv_show()
  {
    cout << "X," << m_x << ", " << "\r\n";
    cout << "Y," << m_y << ", " << "\r\n";
    cout << "Gap X," << m_gap_x << ", " << "\r\n";
    cout << "Gap Y," << m_gap_x << ", " << "\r\n";
    cout << "\t,";
    for(int i = 0; i < m_x; ++i){
      cout << i <<"\t,";
    }
    cout << "\r\n";
    for(int j = 0;j < m_y ;++j){
      cout << j << "\t,";
      for(int i = 0; i < m_x; ++i){
        cout << 0 <<"\t,";
      }
      cout << "\r\n";
    }
  }
  void csv_read(string filename)
  {
    ifstream ifs(filename);
    string str_buf;
    string str_comma_buf;
    char chars[] = "\r\n\t";

    for(int i = 0;getline(ifs, str_buf);++i){
      cout << "Line" << i << ":";
      str_buf.erase(std::remove(str_buf.begin(), str_buf.end(), ' '), str_buf.end());
      for (int k = 0; k < strlen(chars); ++k)
      {
        str_buf.erase(std::remove(str_buf.begin(), str_buf.end(), chars[i]), str_buf.end());
      }
      cout << str_buf << endl;
      istringstream i_stream(str_buf);
      for(int j = 0;getline(i_stream, str_comma_buf, ','); ++j){
        cout << " (" << j << ")";
        if(str_comma_buf.length() > 0){
          cout << str_comma_buf << ",";
        }
        // try{
        //   //stoi(str_comma_buf);
        //   cout << str_comma_buf << ",";
        // }
        // catch(const std::out_of_range& e){
        //   std::cout << "out_of_range"; // => "out_of_range"
        // }
        // catch (const std::invalid_argument& e) {
        //   std::cout << "invalid_argument"; // => "invalid_argument"
        // }
      }
      cout << "\r\n";
    }
  }
  void csv_write(const char* filename)
  {
    ofstream fout(filename);

    fout << "X," << m_x << ", " << "\r\n";
    fout << "Y," << m_y << ", " << "\r\n";
    fout << "Gap X," << m_gap_x << ", " << "\r\n";
    fout << "Gap Y," << m_gap_x << ", " << "\r\n";
    fout << "\t,";
    for(int i = 0; i < m_x; ++i){
      fout << i <<"\t,";
    }
    fout << "\r\n";
    for(int j = 0;j < m_y ;++j){
      fout << j << "\t,";
      for(int i = 0; i < m_x; ++i){
        fout << 0 <<"\t,";
      }
      fout << "\r\n";
    }

  }
};
int main()
{
  std::cout << "csv" <<std::endl;
  CSVFile csv;
  csv.reset(4,4,1.000, 1.000);
  csv.csv_show();
  csv.csv_write("output.csv");
  csv.csv_read("output.csv");
  return 0;
}
