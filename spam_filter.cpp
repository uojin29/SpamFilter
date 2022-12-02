#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <istream>
#include <sstream>
#include <fstream>
#include <list>
#include <map>
#include <set>
#include <regex>
#include <algorithm>
using namespace std;

void train_set(string s, map<string, int> &m); // train 학습을 시키는 함수
int test_set(string s, map<string, int> &h_m, map<string, int> &s_m, float f, string type);
void printSet(set<string> &myset);
void printMap(map<string, int> &m);

set<string> word; // 한 메일 안에서의 단어들의 집합
string text;      // 메일 하나의 내용 -> 공백을 바탕으로 잘라서 해서 set에 넣음
string str_tmp;   // 파일에서 한 줄씩 받아오는 용도
int mail_num = 0; // 메일의 수 (확인하기 위한 용도)
int flag = 0;     // flag

int main(int argc, char *argv[])
{
    map<string, int> ham_words;
    map<string, int> spam_words; //(배열과 비슷) -> 전체 메일에서의 단어 빈도수의 집합. => 더 적합할 듯
    float threshold = 0.6;
    float accuracy = 0;
    train_set("dataset_ham_train100.csv", ham_words);
    train_set("dataset_spam_train100.csv", spam_words);

    int count_ham = test_set("dataset_ham_test20.csv", ham_words, spam_words, threshold, "ham");
    int count_spam = test_set("dataset_spam_test20.csv", ham_words, spam_words, threshold, "spam");
    cout << "count_ham : " << count_ham << "    count_spam : " << count_spam << endl;
    accuracy = (float)(count_ham + count_spam) / 40 * 100;
    cout << "accuracy : " << accuracy << endl;
}

void train_set(string file_name, map<string, int> &m)
{
    fstream fs;
    fs.open(file_name, ios::in);
    while (!fs.eof())
    { // 개행문자 단위가 아니라 ,로 split 후 다음 ham까지 입력받기
        getline(fs, str_tmp, ',');
        str_tmp = regex_replace(str_tmp, regex("[^a-zA-Z0-9 ]"), " "); // 문자와 숫자, 공백을 제외하고 모두 공백으로 치환
        if (str_tmp.find("Subject") != string::npos)                   // Subject이 포함된 문장을 찾으면
        {
            if (flag == 0)
            {             // 첫 번째 Subject이 포함된 문장을 받아오면
                flag = 1; // flag를 1로 변경한다.
            }
            else if (flag == 1)
            { // Subject를 포함하고 있고 flag == 1이므로 새로운 메일의 시작 (=기존 메일의 끝)
                istringstream ss(text);
                while (getline(ss, text, ' ')) // 공백을 기준으로 문자열을 잘라서
                {
                    word.insert(text); // word라는 set에 넣어준다.
                }
                for (string s : word)
                {
                    m[s] = m[s] + 1; // word의 길이만큼 반복하며 set의 성분들을 map에 넣어준다. 이 과정에서 중복인 것은 ++된다.
                }
                //  printMap(ham_words);
                word.clear();
            }
            mail_num++; // 메일 개수 ++ㅣ(확인용)
        }
        else if (flag == 1)
        {
            text += str_tmp; // str_tmp에 저장된 내용을 text라는 string에 더한다.
        }
    }

    mail_num = 0;
}

int test_set(string file_name, map<string, int> &h_m, map<string, int> &s_m, float f, string type)
{
    double p = 1;
    double q = 1;
    double r = 1;
    int spam = 0;
    int ham = 0;
    int count = 0;

    fstream fs;
    fs.open(file_name, ios::in);
    while (!fs.eof())
    { // 개행문자 단위가 아니라 ,로 split 후 다음 ham까지 입력받기
        getline(fs, str_tmp, ',');
        str_tmp = regex_replace(str_tmp, regex("[^a-zA-Z0-9 ]"), " "); // 문자와 숫자, 공백을 제외하고 모두 공백으로 치환
        if (str_tmp.find("Subject") != string::npos)                   // Subject이 포함된 문장을 찾으면
        {
            if (flag == 0)
            {             // 첫 번째 Subject이 포함된 문장을 받아오면
                flag = 1; // flag를 1로 변경한다.
            }
            else if (flag == 1)
            { // Subject를 포함하고 있고 flag == 1이므로 새로운 메일의 시작
                istringstream ss(text);
                while (getline(ss, text, ' ')) // 공백을 기준으로 문자열을 잘라서
                {
                    word.insert(text); // word라는 set에 넣어준다.
                }
                for (string s : word)
                {
                    if (s_m[s] != 0 && h_m[s] != 0)
                    {
                        p *= ((double)s_m[s] / 100.0);
                        q *= ((double)h_m[s] / 100.0);
                    }
                }
                r = p / (p + q);
                cout << "p : " << p << "    q : " << q << "  r : " << r << endl;
                word.clear();
                if (r > f)
                {
                    cout << "this mail is spam!!!\n"
                         << endl;
                    spam++;
                    (type == "spam") ? count++ : 0;
                }
                else
                {
                    cout << "this mail is ham!!!\n"
                         << endl;
                    ham++;
                    (type == "ham") ? count++ : 0;
                }
                p = 1.0;
                q = 1.0;
                r = 1.0;
            }
            mail_num++; // 메일 개수 ++ㅣ(확인용)
        }
        else if (flag == 1)
        {
            text += str_tmp; // str_tmp에 저장된 내용을 text라는 string에 더한다.
        }
    }
    cout << "count is : " << count << endl;
    cout << "spam is : " << spam << endl;
    cout << "ham is : " << ham << endl;
    return count;
}

void printSet(set<string> &m) // set을 확인하기 위한 용도
{
    for (auto it = m.begin(); it != m.end(); ++it)
        cout << *it << ' ';
    cout << endl;
}

void printMap(map<string, int> &m) // map을 확인하기 위한 용도
{
    for (map<string, int>::iterator itr = m.begin(); itr != m.end(); ++itr)
    {
        cout << itr->first << " " << itr->second << endl;
    }
}