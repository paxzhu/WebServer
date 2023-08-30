// struct Request {

// }
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PATH 512
#define QUERYS 256
#define NUM 128
#define MAXBUF 1024

// typedef void (*Handler)(char*return_buf, struct Request* request);
typedef void (*Handler)(char*return_buf, char *querys);

struct Registration
{
    char *prefix;
    Handler handler;
};



struct Request
{
    char *method;
    char *uri;
};

struct nums
{
    int num1;
    int num2;
};



void adder(char* return_buf, char *querys) {
    printf("====================adder========================\n");
    char num1[NUM], num2[NUM];
    sscanf(querys, "num1=%127[^&]&num2=%127[^&]", num1, num2);
    int res = atoi(num1) + atoi(num2);
    sprintf(return_buf, "%s + %s = %d", num1, num2, res);
}

void minus(char* return_buf, char *querys) {
    printf("====================minus========================\n");
    char num1[NUM], num2[NUM];
    sscanf(querys, "num1=%127[^&]&num2=%127[^&]", num1, num2);
    int res = atoi(num1) - atoi(num2);
    sprintf(return_buf, "%s - %s = %d", num1, num2, res);
}

void mult(char* return_buf, char *querys) {
    printf("====================mult========================\n");
    char num1[NUM], num2[NUM];
    sscanf(querys, "num1=%127[^&]&num2=%127[^&]", num1, num2);
    int res = atoi(num1) * atoi(num2);
    sprintf(return_buf, "%s * %s = %d", num1, num2, res);
}

void divid(char* return_buf, char *querys) {
    printf("====================divid========================\n");
    char num1[NUM], num2[NUM];
    sscanf(querys, "num1=%127[^&]&num2=%127[^&]", num1, num2);
    if(atoi(num2) == 0) {
        sprintf(return_buf, "error: divisor is equal to 0");
    }
    else {
        double res = (double)atoi(num1) / atoi(num2);
        sprintf(return_buf, "%s / %s = %f", num1, num2, res);
    }
}


int parse_uri(char *uri, char *filename, char *querys) {
    char *query_start = strchr(uri, '?');

    // 没有问号，则整个字符串为路径，查询部分为空
    if (query_start == NULL) {
        strcpy(filename, ".");
        strcat(filename, uri);
        strcpy(querys, "");
        if(uri[strlen(uri)-1] == '/') {
            strcat(filename, "home.html");
        }
        // printf("==================%s===========================", filename);
        return 1;
    } else {
        // 复制路径部分,最多复制偏移量个字符
        strncpy(filename, uri, query_start - uri);
        filename[query_start - uri] = '\0';

        // 复制查询部分,从字符串指定位置开始复制
        strcpy(querys, query_start + 1);
        return 0;
    }
}

struct Registration registrationTable[] = {
        {"/adder", &adder},
        {"/minus", &minus},
        {"/mult", &mult},
        {"/divid", &divid}
    };

int main() {
    char uri[] = "/adder?num1=2&num2=3";
    char path[PATH], querys[QUERYS], num1[NUM], num2[NUM];
    parse_uri(uri, path, querys);
    printf("path: %s, querys: %s\n", path, querys);
    sscanf(querys, "num1=%127[^&]&num2=%127[^&]", num1, num2);
    
    // struct Request request;
    // request.method = "GET";
    // request.uri = "/adder?num1=2&num2=3";

    //==========================================================
    
    char return_buf[MAXBUF];
    for (int i = 0; i < sizeof(registrationTable) / sizeof(registrationTable[0]); i++) {
        
        if(strcmp(path, registrationTable[i].prefix) == 0) {
            printf("%s\n", registrationTable[i].prefix);
            registrationTable[i].handler(return_buf, querys);
        }
    }

    printf("%s\n", return_buf);
}