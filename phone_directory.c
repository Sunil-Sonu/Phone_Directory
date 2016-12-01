#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include<stdlib.h>


#define ALPHA_SIZE (26)
#define CHAR_TO_INDEX(x) ((int)x-(int)'a')

struct trie{

	struct trie *children[ALPHA_SIZE];
	bool isLeaf;
};

struct stack{
	char *arr;
	int top;
};


//Additional Function
int strlen(char *arr)
{
	int i = 0;
	while (arr[i] != NULL){
		i++;
	}
	return i;
}

/* Operations related to STACK*/
void init(struct stack *s)
{
	s->arr = (char *)calloc(sizeof(char),1024);
	s->top = -1;
}


void push(struct stack *s, char ch){
	s->arr[++s->top] = ch;
}
// Not needed here
void pop(struct stack *s){
	return s->arr[s->top--];
}

/*Operations related to TRIE */
struct trie * getNode()
{
	struct trie * n = (struct trie *)malloc(sizeof(struct trie));
	int i;
	for (i = 0; i < ALPHA_SIZE; i++)
		n->children[i] = NULL;
	n->isLeaf = false;
	return n;
}
// Insertion in TRIE //
void insert(struct trie *root, char *key)
{
	int i;
	int l = strlen(key);
	struct trie *traverse = root;
	for (i = 0; i < l; i++)
	{
		int c = CHAR_TO_INDEX(key[i]);
		if (!traverse->children[c])  // If the node is not present.
			traverse->children[c] = getNode();
		traverse = traverse->children[c];
	}
	traverse->isLeaf = true;
}

void DFS(struct trie *temp, struct stack *s, char *key)
{
	int j = 0,count=0;
	while (j < ALPHA_SIZE){
		if (temp->children[j] != NULL){
			count++;
			push(s, (char)(j+97));
			DFS(temp->children[j], s, key);
			s->top--;
		}
		j++;
	}
	if (count == 0){
		printf("%s", key);
		for (int i = 0; i <= s->top; i++)
			printf("%c", s->arr[i]);
		printf("\n");
	}
}

void search(struct trie *root, char *key,struct stack *s)
{
	int level;
	int length = strlen(key);
	int index;
	struct trie *traverse = root;

	for (level = 0; level < length; level++)
	{
		index = CHAR_TO_INDEX(key[level]);
		traverse = traverse->children[index];
	}
	if (traverse){
		printf("Contacts is/are:\n");
		DFS(traverse, s, key);
	}
	else
		printf("No contact with such pattern\n");
}

int main()
{
	struct trie *root = getNode();
	char contacts[2][10] = { "sunilk","sonu" };
	for (int i = 0; i < 2; i++)
		insert(root, contacts[i]);
	char *in = (char *)malloc(sizeof(char) * 100);
	int i = 0;
	in[i] = '\0';
	struct stack *s = (struct stack *)malloc(sizeof(struct stack));
	init(s);
	while (true){
		printf("Pattern entered so far: %s\n", in);
		printf("Enter your search pattern\nEnter '_' for backspace and '$' to exit\n");
		scanf("%c", (in+i));
		system("CLS");
		if (in[i] >= 'a' && in[i] <= 'z'){
			i++;
			in[i] = '\0';
			search(root, in,s);
		}
		else if(in[i]=='_'){
			i--;
			in[i] = '\0';
			search(root, in,s);
		}
		else if (in[i] == '$') break;
		fflush(stdin);
	}
	return 0;
}
