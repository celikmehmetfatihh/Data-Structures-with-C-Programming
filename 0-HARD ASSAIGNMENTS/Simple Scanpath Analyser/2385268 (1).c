//Name: Mehmet Fatih Çelik
//ID: 2385268

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define d 10

struct Node {
    char data[100];
    struct Node *next;
};

void insert(struct Node**, char*);
struct Node *createScanpathList(char *);
int search(char[], char[], int);
void searchPattern(char *, struct Node*, struct Node*);

/*createScanpathList: This function takes the name of the file containing a number of
scanpaths which are represented as string sequences and creates a linked-list where each
node contains a string representation of a single scanpath. It will return the created list.

 searchPattern: This function takes the pattern and the linked lists of people with and without
autism to check whether the pattern is available in the scanpaths of people with and without
autism by using the Rabin-Karp Algorithm where d=10 (since there are 10 digits) and q=11. If
the pattern is detected in a scanpath, it will be highlighted with square brackets as shown
above. The general pseudo-code of the Rabin-Karp Algorithm is given below

Rabin-Karp(T, P, d, q)
n := length[T];
m := length[P];
h := d
m-1
mod q;
p := 0;
t
0
:= 0;
for i := 1 to m do
p := (dp + P[i]) mod q
t
0
:= (dt
0
+ T[i]) mod q
for s := 0 to n – m do
if p = t
s
then
if P[1..m] = T[s+1..s+m] then
print "pattern occurs with shift s"
if s < n-m then
t
s+1
:= (d(t
s
– T[s+1]h) + T[s+m+1]) mod q*/

int main(){
    char fileName1[128];
    char fileName2[128];
    char pattern[128];

    printf("Enter the file name for people with autism: ");
    scanf("%s", &fileName1);

    printf("Enter the file name for people with autism: ");
    scanf("%s", &fileName2);

    printf("Enter the pattern: ");
    scanf("%s", &pattern);

    struct Node* withAutism = createScanpathList(fileName1);
    struct Node* withoutAutism = createScanpathList(fileName2);

    searchPattern(pattern, withAutism, withoutAutism);
}

void insert(struct Node** head_ref, char* new_data){
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node* last = *head_ref; /* used in step 5*/

    strcpy(new_node->data, new_data);
    new_node->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL) last = last->next;

    last->next = new_node;
    return;
}

struct Node *createScanpathList(char *fileName){
    struct Node* head = NULL;
    char line[100];

    FILE *file = fopen(fileName, "r");
    if (file != NULL){
        while (fscanf(file, "%s", &line) > 0) {
            insert(&head, line);
        }
    }
    else{
        printf("File can not be opened!\n");
        exit(-1);
    }

    fclose(file);
    return head;
}

int search(char pat[], char txt[], int q){
    int M = strlen(pat);
    int N = strlen(txt);
    int i, j;
    int p = 0;
    int t = 0;
    int h = 1;

    for (i = 0; i < M-1; i++)
        h = (h*d)%q;

    for (i = 0; i < M; i++){
        p = (d*p + pat[i])%q;
        t = (d*t + txt[i])%q;
    }

    for (i = 0; i <= N - M; i++){

        if ( p == t ){
            for (j = 0; j < M; j++){
                if (txt[i+j] != pat[j])
                    break;
            }

            if (j == M)
                return i;
        }

        if ( i < N-M ){
            t = (d*(t - txt[i]*h) + txt[i+M])%q;

            if (t < 0)
                t = (t + q);
        }
    }

    return -1;
}

void searchPattern(char *pattern, struct Node* withAutism, struct Node* withoutAutism){
    int i, j, count = 0, maxFreq = 0, maxFreqIndex = 0, result;
    int freqArr[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    printf("\nDetected patterns for people with autism:\n");
    for (i = 0; withAutism != NULL; i++){

        int index = 0;
        int checkAnyMatch = 0;

        while (1){
            result = search(pattern, withAutism->data + index, 11);

            if (result < 0)
                break;

            count++;
            checkAnyMatch = 1;

            for (j = index; j < index + result; ++j) {
                printf("%c", withAutism->data[j]);
            }
            printf("[");

            for (j = index + result; j < index + result + strlen(pattern); ++j){
                printf("%c", withAutism->data[j]);
            }
            printf("]");

            if ((index + result) != 0)
                freqArr[(int)((withAutism->data[index + result - 1]) - '0')]++;

            index += result + strlen(pattern);
        }

        if (checkAnyMatch)
            printf("\n");

        withAutism = withAutism->next;
    }

    if (count > 0){
        for (j = 0; j < 10; ++j){
            if (freqArr[j] > maxFreq){
                maxFreq = freqArr[j];
                maxFreqIndex = j;
            }
        }

        printf("\n%d patterns detected in %d scanpaths\n", count, i);
        printf("The most frequent AOI before the pattern is / are %d\n", maxFreqIndex);
    }
    else
        printf("None\n");


	count = 0;
	maxFreq = 0;
	maxFreqIndex = 0;
    int freqArr2[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


    printf("\n\nDetected patterns for people without autism:\n");
    for (i = 0; withoutAutism != NULL; i++){

        int index = 0;
        int checkAnyMatch = 0;

        while (1){
            result = search(pattern, withoutAutism->data + index, 11);

            if (result < 0)
                break;

            count++;
            checkAnyMatch = 1;

            for (j = index; j < index + result; ++j){
                printf("%c", withoutAutism->data[j]);
            }
            printf("[");

            for (j = index + result; j < index + result + strlen(pattern); ++j){
                printf("%c", withoutAutism->data[j]);
            }
            printf("]");

            if ((index + result) != 0)
                freqArr2[(int)((withoutAutism->data[index + result - 1]) - '0')]++;

            index += result + strlen(pattern);
        }

        if (checkAnyMatch)
            printf("\n");

        withoutAutism = withoutAutism->next;
    }

    if (count > 0){
        for (j = 0; j < 10; ++j){
            if (freqArr2[j] > maxFreq){
                maxFreq = freqArr2[j];
                maxFreqIndex = j;
            }
        }

        printf("\n%d patterns detected in %d scanpaths\n", count, i);
        printf("The most frequent AOI before the pattern is / are %d\n", maxFreqIndex);
    }
    else
        printf("None\n");
}
