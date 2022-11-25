#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>

using namespace std;

vector<string> split(string str, char Delimiter) {
    istringstream iss(str);             // istringstream에 str을 담는다.
    string buffer;                      // 구분자를 기준으로 절삭된 문자열이 담겨지는 버퍼
 
    vector<string> result;
 
    // istringstream은 istream을 상속받으므로 getline을 사용할 수 있다.
    while (getline(iss, buffer, Delimiter)) {
        result.push_back(buffer);               // 절삭된 문자열을 vector에 저장
    }
    return result;
}

int main(int argc, char** argv) {
    string str_buf;         
    ifstream fs; 
    // string filePath = "train_ham.txt";
    fs.open("dataset_ham_train100.csv"); 
	// ofstream writeFile(filePath.data());

    while(!fs.eof()){
         getline(fs,str_buf,',');
        // // write File
        // if( writeFile.is_open() ){
        //     writeFile << str_buf;
        // }
    }
    // writeFile.close();
    fs.close();

	
	return 0;
}