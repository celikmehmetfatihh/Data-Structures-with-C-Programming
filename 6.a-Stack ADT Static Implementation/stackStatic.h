typedef struct StackRecord *Stack;

void IsPalindrome(char *, Stack s);
struct StackRecord *CreateStack(int);
void PushStack(char , Stack s);
int PopStack(Stack);
int IsEmptyStack(Stack);
