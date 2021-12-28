#include <stdio.h>
#include <string.h>
float threshold = 0.6;
double rw = 0.0;

struct Word {
    char word[100]; //word
    int count; //word count
    int ham_num; //word count in ham mail
    int spam_num; //word count in spam mail
    int check; //To count how many emails got this word
    double h_rw; //rw value of each word
    int isham;  //0: ham , 1: spam
};
struct Word w[1500000];
int w_listindex = 0;

struct Select_Spam_Word {
    char word[100]; //word
    int ham_num; //To count how many emails got this word from ham_email
    int spam_num; //To count how many emails got this word from spam_email
    double rw; //total rw value of selected word
};
struct Select_Spam_Word selectsw[1500000];
int select_w_listindex = 0;


void read_ham() {
    int line = 0;
    FILE *pFile = fopen("/Users/jeong-yiju/Desktop/Homework4/datasets/train/dataset_ham_train100.csv","r");
    char data[1024];
    char *temp[150000] = {NULL, };
    
    while (!feof(pFile) ) {
        int dupulicate_count = 0;
        fscanf(pFile, "%s", data);
        if(line != 0){
            if(strstr(data, ",ham,") == NULL){
                for(int i = 0; i < w_listindex; i++) {
                    if(strcmp(w[i].word, data) == 0){
                        w[i].count = (w[i].count) + 1;
                        dupulicate_count++;
                    }
                }
                if(dupulicate_count == 0){
                    strcpy(w[w_listindex].word, data);
                    w[w_listindex].count = 1;
                    w[w_listindex].check = 0;
                    w[w_listindex].isham = 0;
                    w_listindex++;
                }

            }
            else{
                int i = 0;
                char *cut = strtok(data, ",");
                while (cut != NULL){
                    temp[i] = cut;
                    i++;
                    cut = strtok(NULL, ",");
                }
                //printf("%s\n", temp[2]);
                strcpy(w[w_listindex].word, temp[2]);
                for(int i = 0; i < w_listindex; i++) {
                    if(strcmp(w[i].word, temp[2]) == 0){
                        w[i].count = (w[i].count) + 1;
                        dupulicate_count++;
                    }
                }
                if(dupulicate_count == 0){
                    strcpy(w[w_listindex].word, temp[2]);
                    w[w_listindex].count = 1;
                    w[w_listindex].isham = 0;
                    w_listindex++;
                }
            }
        }
        line++;
    }
    fclose(pFile);
}


void read_spam() {
    int line = 0;
    FILE *pFile = fopen("/Users/jeong-yiju/Desktop/Homework4/datasets/train/dataset_spam_train100.csv","r");
    char data[1024];
    char *temp[150000] = {NULL, };
    
    while (!feof(pFile) ) {
        int dupulicate_count = 0;
        fscanf(pFile, "%s", data);
        if(line != 0){
            if(strstr(data, ",spam,") == NULL){
                //strcpy(w[w_listindex].word, data);
                //printf("%s\n", data);
                
                for(int i = 0; i < w_listindex; i++) {
                    if(strcmp(w[i].word, data) == 0){
                        w[i].count = (w[i].count) + 1;
                        dupulicate_count++;
                    }
                }
                if(dupulicate_count == 0){
                    strcpy(w[w_listindex].word, data);
                    w[w_listindex].count = 1;
                    w[w_listindex].isham = 1;
                    w_listindex++;
                }
            }
            else{
                int i = 0;
                char *cut = strtok(data, ",");
                while (cut != NULL){
                    temp[i] = cut;
                    i++;
                    cut = strtok(NULL, ",");
                }
                //printf("%s\n", temp[2]);
                strcpy(w[w_listindex].word, temp[2]);
                for(int i = 0; i < w_listindex; i++) {
                    if(strcmp(w[i].word, temp[2]) == 0){
                        w[i].count = (w[i].count) + 1;
                        dupulicate_count++;
                    }
                }
                if(dupulicate_count == 0){
                    strcpy(w[w_listindex].word, temp[2]);
                    w[w_listindex].count = 1;
                    w[w_listindex].isham = 1;
                    w_listindex++;
                }
            }
        }
        line++;
    }
    fclose(pFile);
    
}


void count_ham_word(){
    int line = 0;
    FILE *pFile = fopen("/Users/jeong-yiju/Desktop/Homework4/datasets/test/dataset_ham_test20.csv","r");
    char data[1024];
    char *temp[150000] = {NULL, };
    int currnum = 0;
    int num;
    
    while (!feof(pFile) ) {
        fscanf(pFile, "%s", data);
        if(line != 0){
            //printf("%s\n", data);
            if(strstr(data, ",ham,") == NULL){
                //strcpy(w[w_listindex].word, data);
                //printf("%s\n", data);
                
                for(int i = 0; i < w_listindex; i++) {
                    if(strcmp(w[i].word, data) == 0 && w[i].check == 0){
                        //w[i].ham_num = (w[i].ham_num) + 1;
                        if(num != currnum){
                            w[i].ham_num = (w[i].ham_num) + 1;
                            w[i].check = 1;
                         
                        }
                    }
                }

            }
            
            else{
                num = currnum;
                for(int i = 0; i < w_listindex; i++) {
                    w[i].check = 0;
                }
                
                int i = 0;
                char *cut = strtok(data, ",");
                while (cut != NULL){
                    temp[i] = cut;
                    i++;
                    cut = strtok(NULL, ",");
                }
                for(int i = 0; i < w_listindex; i++) {
                    if(strcmp(w[i].word, temp[2]) == 0){
                        w[i].ham_num = (w[i].ham_num) + 1;
                    }
                }
                currnum++;
            }
            
        }
        line++;
        

    }
    fclose(pFile);
}

void count_spam_word(){
    int line = 0;
    FILE *pFile = fopen("/Users/jeong-yiju/Desktop/Homework4/datasets/test/dataset_spam_test20.csv","r");
    char data[1024];
    char *temp[150000] = {NULL, };
    int currnum = 0;
    int num;
    
    while (!feof(pFile) ) {
        fscanf(pFile, "%s", data);
        if(line != 0){
            //printf("%s\n", data);
            if(strstr(data, ",spam,") == NULL){
                for(int i = 0; i < w_listindex; i++) {
                    if(strcmp(w[i].word, data) == 0 && w[i].check == 0){
                        //w[i].spam_num = (w[i].spam_num) + 1;
                        if(num != currnum){
                            w[i].spam_num = (w[i].spam_num) + 1;
                            w[i].check = 1;
                         
                        }
                    }
                }

            }
            
            else{
                num = currnum;
                for(int i = 0; i < w_listindex; i++) {
                    w[i].check = 0;
                }
                
                int i = 0;
                char *cut = strtok(data, ",");
                while (cut != NULL){
                    temp[i] = cut;
                    i++;
                    cut = strtok(NULL, ",");
                }
                for(int i = 0; i < w_listindex; i++) {
                    if(strcmp(w[i].word, temp[2]) == 0){
                        w[i].spam_num = (w[i].spam_num) + 1;
                    }
                }
                currnum++;
            }
            
        }
        line++;
        

    }
    fclose(pFile);
}


void cal_rw(){
    for(int i = 0; i < w_listindex; i++) {
        if(w[i].ham_num == 0 && w[i].spam_num != 0){
            w[i].h_rw = (float)1;
        }
        else if(w[i].spam_num == 0 && w[i].ham_num != 0){
            w[i].h_rw = (float)0;
        }
        else if (w[i].ham_num != 0 && w[i].spam_num != 0){
            w[i].h_rw = ((float)w[i].spam_num / 20) / (((float)w[i].ham_num / 20) + ((float)w[i].spam_num / 20));
        }
    }
}

void total_rw(){
    double pw = 1.0;
    double qw = 1.0;
    
    for(int i = 0; i < select_w_listindex; i++) {
        pw = pw * ((float)selectsw[i].spam_num / 20);
        qw = qw * ((float)selectsw[i].ham_num / 20);
    }
    rw = pw / (pw + qw);
    printf("Total rw: %.2f\n", rw);
    
}


void make_spamWord(){
    
    for(int i = 0; i < w_listindex; i++) {
        if(w[i].h_rw != 1.0  && w[i].h_rw > 0.6  && w[i].spam_num > 4 && strlen(w[i].word) > 2 && w[i].ham_num < 3){
            strcpy(selectsw[select_w_listindex].word, w[i].word);
            selectsw[select_w_listindex].ham_num = w[i].ham_num;
            selectsw[select_w_listindex].spam_num = w[i].spam_num;
            selectsw[select_w_listindex].rw = w[i].h_rw;
            select_w_listindex++;
            //printf("word: %s  **HAM: %d **SPAM: %d $$h_rw: %.2f\n",  w[i].word, w[i].ham_num, w[i].spam_num, w[i].h_rw);
        }
        
    }
}


void predict_spamfile() {
    char w[100];
    char h[100];
    double rw_w;
    double rw_h;
    int correct_h = 0;
    int correct_w = 0;
    int line = 0;
    FILE *pFile = fopen("/Users/jeong-yiju/Desktop/Homework4/datasets/test/dataset_spam_test20.csv","r");
    char data[1024];
    int currnum = 1;
    int num = 0;
    printf("\n********** test spam file **********\n");
    printf("spam mail line is...\n");
    while (!feof(pFile) ) {
        
        fscanf(pFile, "%s", data);
        
        if(line != 0){
            //printf("  word: %s\n", data);
            if(strstr(data, ",spam,") == NULL){
                if(threshold < rw){
                    for(int i = 0; i < select_w_listindex; i++) {
                        if(strcmp(selectsw[i].word, data) == 0){
                            if(strcmp(selectsw[i].word, "com")){
                                correct_w++;
                                rw_w = selectsw[i].rw;
                                strcpy(w, selectsw[i].word);
                                
                            }
                            if(strcmp(selectsw[i].word, "here")){
                                correct_h++;
                                rw_h = selectsw[i].rw;
                                strcpy(h, selectsw[i].word);
                            }
                            
                        }
                    }
                }
            }
    
            else{
                if(correct_h > 0 && correct_w > 0){
                    printf("line: %d spam mail!!\n", num);
                    
                }
                else if(correct_h > 0){
                    
                    if(rw_h > threshold){
                        printf("line: %d word: %s wr: %.2f", num, h, rw_h);
                        printf("  spam mail!!\n");
                    }
                }
                else if(correct_w > 0){
                    
                    if(rw_w > threshold){
                        printf("line: %d word: %s wr: %.2f", num, w, rw_w);
                        printf("  spam mail!!\n");
                    }
                }
               
                correct_h = 0;
                correct_w = 0;
                num = currnum;
                currnum++;
            }
        
        }
        line++;
    }
    
    fclose(pFile);
    
}


void predict_hamfile() {
    char w[100];
    char h[100];
    int correct_h = 0;
    int correct_w = 0;
    int line = 0;
    FILE *pFile = fopen("/Users/jeong-yiju/Desktop/Homework4/datasets/test/dataset_ham_test20.csv","r");
    char data[1024];
    int currnum = 1;
    int num = 0;
    double rw_w;
    double rw_h;
    printf("\n********** test ham file **********\n");
    printf("spam mail line is…\n");
    while (!feof(pFile) ) {
        
        fscanf(pFile, "%s", data);
        
        if(line != 0){
            if(strstr(data, ",ham,") == NULL){
                if(threshold < rw){
                    for(int i = 0; i < select_w_listindex; i++) {
                        if(strcmp(selectsw[i].word, data) == 0){
                            if(strcmp(selectsw[i].word, "com")){
                                correct_w++;
                                rw_w = selectsw[i].rw;
                                strcpy(w, selectsw[i].word);
                                
                            }
                            if(strcmp(selectsw[i].word, "here")){
                                correct_h++;
                                rw_h = selectsw[i].rw;
                                strcpy(h, selectsw[i].word);
                            }
                        }
                    }
                }
                
            }
    
            else{
                if(correct_h > 0 && correct_w > 0){
                    printf("line: %d spam mail!!\n", num);
                    
                }
                else if(correct_h > 0){
                    
                    if(rw_h > threshold){
                        printf("line: %d word: %s wr: %.2f", num, h, rw_h);
                        printf("  spam mail!!\n");
                    }
                }
                else if(correct_w > 0){
                    
                    if(rw_w > threshold){
                        printf("line: %d word: %s wr: %.2f", num, w, rw_w);
                        printf("  spam mail!!\n");
                    }
                }
                correct_h = 0;
                correct_w = 0;
                num = currnum;
                currnum++;
            }
        
        }
        line++;
    }
    fclose(pFile);
    
}

int main() {
    read_ham();
    read_spam();
    count_ham_word();
    count_spam_word();
    cal_rw();
    make_spamWord();
    total_rw();

    printf("**********Selected words are**********\n");
    for(int i = 0; i < select_w_listindex; i++) {
        printf("word: %s",  selectsw[i].word);
        printf("  ");
    }
    predict_spamfile();
    predict_hamfile();
}
