typedef struct Node StackRecord;
typedef StackRecord *Stack;

void IsPalindrome(char *, Stack s);
Stack CreateStack();
void PushStack(char , Stack s);
int PopStack(Stack);
int IsEmptyStack(Stack);
