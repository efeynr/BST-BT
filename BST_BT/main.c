//Ediz Efe Yener
//Goal is to create a binary search tree and balanced binary tree to compare their total access time


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int totalAccesTime=0;

//creating struct for trees
struct word {
    char name[50];
    int frequency;
    struct word * left;
    struct word * right;

};
typedef struct word Word;

//For inserting nodes into array for sorting and creating BT
Word* insertArray(char name[],int frequency){
    //Basically, we are initializing node into node Array
    Word *node=(Word *)malloc(sizeof(Word));
    strcpy(node->name,name);
    node->frequency=frequency;
    node->left=NULL;
    node->right=NULL;
}

//This is for sorting Arrays element by looking their frequencies
void sortingFunc(Word *nodeArray,int size){
// I sort the array by using bubble sorting
    Word node;
    int j,control;
    while(1){ // infinite loop
        control=0; // this is for controlling did we do or don't do opartions inside loop
        for(j=0;j<size-1;j++){
            if(nodeArray[j].frequency<nodeArray[j+1].frequency){
                node=nodeArray[j];
                nodeArray[j]=nodeArray[j+1];
                nodeArray[j+1]=node;
                control=1; // if we change something make this variable 1 for searching our array for other elements
            }
        }
        if(control==0) { // if we dont do anything in any turn, then we need to break the while loop
            break;
        }
    }
}
// this is insertion function for BST
Word* insertion(Word* tree,char name[],int frequency){
    if(tree==NULL){ // if our root(or node for another tree) is NULL, we need to fill that node.
        Word *root=(Word *)malloc(sizeof(Word)); // mallloc for root
        strcpy(root->name,name);
        root->frequency=frequency;
        root->left=NULL;
        root->right=NULL;
        return root;
    }
    if(stricmp(tree->name,name)<0) {// if current node is bigger than tree by case sensitivity
        tree->right = insertion(tree->right, name,frequency); //we are just recursively calling the right pointer for that tree.
        return tree;
    }
    tree->left=insertion(tree->left,name,frequency); // otherwise
    return tree;
}

//this is for inserting nodes into binary tree
Word* insertionBT(Word* nodeArray,Word* root,int i,int length){

    if(i<length){ //base case for recursion
        //we are changing our root for each recursive call
        Word* temp= &nodeArray[i];
        root=temp;
        //insert left child
        // 2*i+1 and 2*i+2 are the formulas to create them with a relation that i want to see
        root->left=insertionBT(nodeArray,root->left,2*i+1,length);
        //insert right child
        root->right=insertionBT(nodeArray,root->right,2*i+2,length);
    }
    return root;
}

//basically, traversing tree with LNR
void traverseLNR(Word* tree){
    if(tree==NULL){
        return;
    }
    traverseLNR(tree->left);
    printf("%s ",tree->name);
    //  printf("%d ",tree->frequency);
    traverseLNR(tree->right);
}
//basically, traversing tree with RNL
void traverseRNL(Word*tree){
    if(tree!=NULL){
        traverseRNL(tree->right);
        printf("%s ,",tree->name);
        traverseRNL(tree->left);
    }
}

//this is for calculating total access time
//FOR ALL NODES:  (depth+1)*(frequency of that node)
void totAccesFunc(Word* tree,int depth){
    if(tree!=NULL){ // do that from root to leaves
        totalAccesTime+=(depth+1)*tree->frequency; // adding current node's access time
        totAccesFunc(tree->left,depth+1); // for every level we need to add 1 to depth
        totAccesFunc(tree->right,depth+1);
    }
    // This is important because if we done with current branch(side) we need to make depth 0
    // after recursive calls we need to reset that variable to get the correct results from that function.
    depth=0;

}

int main() {
    Word *tree;
    tree = NULL; //my BST

    //these variables for reading from text
    char line[40]={0};
    char name[15]="\0";
    char number[5]="\0";
    char freq[5]="\0";
    char *token; // i use split method to read my input line by line
    FILE *inputPointer=NULL; //inputPTR
    inputPointer=fopen("input.txt","r"); // openning file with read mod
    int i=0; // for loops
    int sizeOfLine=0; // for my array's size declaration
    // i am getting the sizeOfline in my input text file to create my array.
    for(i=0;fgets(line,sizeof(line),inputPointer);i++){
        sizeOfLine++;
    }
    Word nodeArray[sizeOfLine]; // I am creating my array in static way. As you can see.

    fclose(inputPointer); // i am going to close it and open it again for taking the size of my input
    inputPointer=fopen("input.txt","r");
    i=0; // necessary for other steps
    //this is the whole reading process of my code
    while(!feof(inputPointer)) {
        fgets(line,20,inputPointer);
        token=strtok(line,","); //deliminating comma with strToken
        strcpy(number,token); // take the first string into number(which i didnt use anywhere except this line...
        token=strtok(NULL,",");
        strcpy(name,token); // same instruction  for the name input
        token=strtok(NULL,",");
        strcpy(freq,token); // and for frequency
        int freq2; // this is for changing string freq to integer
        freq2=atoi(freq); // we need integer value for freq to create tree
        tree=insertion(tree,name,freq2); // call the insertion funct
        nodeArray[i]=*insertArray(name,freq2); // fill the array with nodes
        i++;
    }
    fclose(inputPointer); // close the input File

    sortingFunc(nodeArray,sizeOfLine); //we sort the array

    Word* freqTree; // we create the freqTree
    freqTree=insertionBT(nodeArray,freqTree,0,sizeOfLine); //inserting freqTree

    printf("LNR Traverse for Binary Search Tree: \n");
    traverseLNR(tree);
    printf("\n\n\n");
    printf("LNR Traverse for Binary Tree: \n");
    traverseLNR(freqTree);

    totAccesFunc(tree,0);

    printf("\n\n\nTotal Access Time for BST: %d \n",totalAccesTime);
    totalAccesTime=0;

    totAccesFunc(freqTree,0);
    printf("\nTotal Access Time for BT: %d \n",totalAccesTime);
}