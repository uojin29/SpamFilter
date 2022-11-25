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
    char *word[101][1000];
    FILE* fp1 = NULL;
    FILE* fp2 = NULL;
    fp1 = fopen("dataset_ham_train100.csv", "r");
    fp2 = fopen("dataset_spam_train100.csv", "r");
    char str_tmp[1000000];
    int count = 0;
    int i = 0;
    int j = 0;
    if(fp1 != NULL){   
        while(!feof(fp1)){
            fgets(str_tmp, 1024, fp1);
            // -> 특수문자 공백으로 치환
            data[i].text = replaceAll(str_tmp, "'", "");
            data[i].text = replaceAll(data[i].text, "~", "");
            data[i].text = replaceAll(data[i].text, "!", "");
            data[i].text = replaceAll(data[i].text, "@", "");
            data[i].text = replaceAll(data[i].text, "#", "");
            data[i].text = replaceAll(data[i].text, "$", "");
            data[i].text = replaceAll(data[i].text, "%%", "");
            data[i].text = replaceAll(data[i].text, "^", "");
            data[i].text = replaceAll(data[i].text, "&", "");
            data[i].text = replaceAll(data[i].text, "*", "");
            data[i].text = replaceAll(data[i].text, "(", "");
            data[i].text = replaceAll(data[i].text, ")", "");
            data[i].text = replaceAll(data[i].text, "-", "");
            data[i].text = replaceAll(data[i].text, "<", "");
            data[i].text = replaceAll(data[i].text, ">", "");
            data[i].text = replaceAll(data[i].text, "?", "");
            data[i].text = replaceAll(data[i].text, "/", "");
            data[i].text = replaceAll(data[i].text, "\"", "");
            data[i].text = replaceAll(data[i].text, ".", "");
            data[i].text = replaceAll(data[i].text, ",", "");
            data[i].text = replaceAll(data[i].text, ":", "");
            data[i].text = replaceAll(data[i].text, "{", "");
            data[i].text = replaceAll(data[i].text, "}", "");
            
            //-> 그 줄에 ham 포함하고 있는지 여부 확인
            if(strstr(str_tmp, ",ham,")){
                // 포함하고 있으면 그 줄은 넘어감.
                i++;
                continue;
            }   
            else {
                //-> data 잘라서 구조체 안에 넣기.
                char *ptr = strtok(data[i].text, " \n"); // " " 공백 문자, \n를 기준으로 문자열을 자름, 포인터 반환
                while (ptr != NULL){ // 자른 문자열이 나오지 않을 때까지 반복
                    data->num = i;
                    word[i][j] = ptr;
                    if(data->num == 1){
                        printf("i = %d, %s\n", data->num, word[i][j]);
                    }
                        // 자른 문자열 출력
                    ptr = strtok(NULL, " \n"); // 다음 문자열을 잘라서 포인터를 반환
                }
            }           
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