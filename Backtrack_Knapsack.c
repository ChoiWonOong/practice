#include<stdio.h>
#include<string.h>

//(value, weight, include[])
struct node {
    int value;
    int weight;
};
int include[11] = {1,1,1,1,1,1,1,1,1,1,1};    
int maxprofit=0;
//item 개수 n, 최대 weight W
int n=4; int W=16;

int promising(int* value, int* weight, struct node node);
void knapsack(int item_index, int* value, int* weight, struct node* tree, int index);

int main(){
    
    struct node tree[1025];
    struct node root = { 0,0 };
    
    tree[1] = root;
    

    //values
    int v[4] = { 40, 30, 50, 10 };

    //weight
    int w[4] = { 2, 5, 10, 5 };
    
    
    //int p = promising(W, n, include, v, w, root);
    //printf("p : %d\n", p);
   
    knapsack(0, v, w, tree, 1);
    //printf("%d\n",maxprofit);


}
int promising(int* value, int* weight, struct node node){
    int totweight = node.weight;
    float bound = (float)node.value;

    if (node.weight >= W) return 0; 
    else{
        for(int i=0; i<n;i++){
            printf("i = %d\n",i);
            if(include[i]==0){
                continue;
            }
                
            else if(include[i]==1){
                int temp_totweight = totweight + weight[i];
                if(temp_totweight>=W){
                    bound += (W-totweight)*value[i]/(float)weight[i];
                    node.weight = weight[i];
                    printf("value %d : %d\n", i, value[i]);
                    break;
                }
                else{
                    totweight += weight[i];
                    //node.weight = weight[i];
                    bound += value[i];
                }
            }
            
        }  
        printf("\n");
        return bound > maxprofit;
    }
}
void knapsack(int item_index, int* value, int* weight, struct node* tree, int index){
    if ((tree[index].weight <= W) && (tree[index].value > maxprofit)) { // 지금까지 최고의 답
		maxprofit = tree[index].value;
        printf("item index : %d\n",item_index);
        
	}

    if (promising(value, weight, tree[index])) {
        if(tree[index].value > W)
        W = tree[index].value;
        int temp[11];
        memmove(temp, include, sizeof(int)*11);

        printf("maxprofit : %d\n\n", maxprofit);
        //make left child node
        // Include weight[i+1]
        include[item_index+1] = 1;

        //connect node with tree
        tree[index*2].value = tree[index].value+value[item_index+1];
        tree[index*2].weight = tree[index].weight+weight[item_index+1];
        //maxweight += weight[item_index];

        knapsack(item_index+1, value, weight, tree, index*2);

        //make right child node
        // Not include weight[i+1]

        //connect node with tree
        tree[index*2+1].value = tree[index].value;
        tree[index*2+1].weight = tree[index].weight;

        for(int i =0; i<11; i++){
            include[i] = temp[i];
        }
        include[item_index+1] = 0;
    	knapsack(item_index+1, value, weight, tree, index*2+1);
    }
}
