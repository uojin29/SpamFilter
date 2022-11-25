#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct DATA{
    int num;
    char *label;
    char *text;
};

char *replaceAll(char *s, const char *olds, const char *news);

int main(int argc, char *argv[]) {
    struct DATA data[100];
    FILE* fp1 = NULL;
    FILE* fp2 = NULL;
    fp1 = fopen("dataset_ham_train100.csv", "r");
    fp2 = fopen("dataset_spam_train100.csv", "r");
    char text[1000000];
    char str_tmp[1000000];
   // FILE *pFile = NULL;
    int count = 0;
    int i = 0;
    fp1 = fopen("dataset_ham_train100.csv", "r" );
    if(fp1 != NULL){   
        while(!feof(fp1)){
            fgets(str_tmp, 1024, fp1);
            char *s2;
            s2 = replaceAll(str_tmp, "?", "");
            data[i].text = s2;
            //char *ptr = strtok(str_tmp, "~!@#$^&*()-<>?/"); 
            //-> 그 줄에 ham 포함하고 있는지 여부 확인
            
            if(strstr(str_tmp, ",ham,")){
                // 포함하고 있으면 그 줄은 넘어감.
                i++;
                continue;
            }   
            else {
                //str_tmp가 특수문자, be동사와 같은 의미없는 단어일 경우 제거
                // char* new_ptr = strchr(str_tmp, '?');
                // if (new_ptr) {
                //     *new_ptr = ' ';  // t로 변경
                //     puts(str_tmp);
                //     //printf("\n\n\nI found - %s\n\n\n", str_tmp);
                // }
                // 포함하고 있지 않으면 text라는 빈 string에 붙이고, 그 값을 data.text에 저장하기.
                
                
                //-> data 잘라서 구조체 안에 넣기.
                char *ptr = strtok(data[i].text, " \n"); // " " 공백 문자, \n를 기준으로 문자열을 자름, 포인터 반환
                    while (ptr != NULL){ // 자른 문자열이 나오지 않을 때까지 반복
                        printf("i is %d, %s\n", i,ptr); // 자른 문자열 출력
                        ptr = strtok(NULL, " \n"); // 다음 문자열을 잘라서 포인터를 반환
                    }
             //   printf("%d %s %s",i,"i = ",data[i].text);
            }
            // count++;
            // printf("%s", str_tmp);                  
        }       
        
    }
    fclose(fp1);
    fclose(fp2);
    
    //printf("%d", count);
    return 0;
}

char *replaceAll(char *s, const char *olds, const char *news) {
  char *result, *sr;
  size_t i, count = 0;
  size_t oldlen = strlen(olds); if (oldlen < 1) return s;
  size_t newlen = strlen(news);


  if (newlen != oldlen) {
    for (i = 0; s[i] != '\0';) {
      if (memcmp(&s[i], olds, oldlen) == 0) count++, i += oldlen;
      else i++;
    }
  } else i = strlen(s);


  result = (char *) malloc(i + 1 + count * (newlen - oldlen));
  if (result == NULL) return NULL;


  sr = result;
  while (*s) {
    if (memcmp(s, olds, oldlen) == 0) {
      memcpy(sr, news, newlen);
      sr += newlen;
      s  += oldlen;
    } else *sr++ = *s++;
  }
  *sr = '\0';

  return result;
}