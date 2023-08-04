#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	

    int data;
    struct Trie* next[26];

};
// Initializes a trie structure
struct Trie *createTrie()
{   
    struct Trie* myTrie = malloc(sizeof(struct Trie));
    //struct Trie myTrie;
    //myTrie = (struct Trie)malloc(sizeof(struct Trie));
    //^idk if i need to fix this, ill just ask the TA's...
    //nvm
    myTrie->data = 0;
    myTrie->next[26] = (struct Trie*)malloc(26*sizeof(struct Trie));
    for(int i = 0; i < 26; i++){
        myTrie->next[i] = NULL;
    }
    return myTrie;
}
// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    int len = strlen(word);
    struct Trie *newNode;
    for(int i = 0; i < len; i++){//did len -1 because of the null char at the end
        if(pTrie->next[(word[i]-'a')] == NULL){
            newNode = createTrie();
            pTrie->next[(word[i]-'a')] = newNode;
        }
        pTrie = pTrie->next[(word[i]-'a')];
    }
    pTrie->data++;
    
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    int num = 0;
    int i = 0;
    int len = strlen(word);
    while((word[i] != '\0') && (pTrie->next[word[i]-'a'])){
        pTrie = pTrie->next[word[i]-'a'];
        i++;
    }
    //^should get to the end of the word, leaving the last char null.
    // if it does not the string does not exist in the trie
    if(i == len){
        num = pTrie->data;
    }
    return num;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if(pTrie == NULL){
        return NULL;
    }
    for(int i = 0; i < 26; i++){
        if(pTrie->next[i] != NULL)
            deallocateTrie(pTrie->next[i]);
    }
    free(pTrie);
    return NULL;
}


// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE* inFile = fopen(filename,"r");
    int numInputs;
    //char* letter;
    //String word;

    fscanf(inFile, " %d\n", &numInputs);
    //int* numArray = NULL;
    //numArray = (int *) malloc(numInputs * sizeof(int));
    //char lineBuffer[256];
    for(int i = 0; i < numInputs; i++){
        //pInWords[i] = "abc";
        char *lineBuffer = (char*)malloc(256*sizeof(char));
        fscanf(inFile," %s", lineBuffer);
        pInWords[i] = lineBuffer;
        //pInWords[i] = letter;
    }
    //supposed to return the nubmer of inputs
    return numInputs;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}