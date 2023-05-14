#include<stdio.h>
#include<string.h>

//(value, weight, include[])
struct node {
    int value;
    int weight;
};

int promising(int maxprofit, int W, int n, int* include, int* value, int* weight, struct node node);
void knapsack(int item_index, int maxprofit, int maxweight, int n, int* include, int* value, int* weight, struct node* queue, int index);

int main(){
    int include[11] = {1,1,1,1,1,1,1,1,1,1,1};    
    struct node queue[1025];
    struct node root = { 0,0 };
    int maxprofit=0;
    queue[1] = root;
    //item 개수 n, 최대 weight W
    int n=4; int W=16;

    //values
    int v[4] = { 40, 30, 50, 10 };

    //weight
    int w[4] = { 2, 5, 10, 5 };
    
    
    //int p = promising(W, n, include, v, w, root);
    //printf("p : %d\n", p);
   
    knapsack(0, maxprofit, W, n, include, v, w, queue, 1);
    //printf("%d\n",maxprofit);


}
int promising(int maxprofit, int W, int n, int* include, int* value, int* weight, struct node node){
    int totweight = node.weight;
    float bound = (float)node.value;
    printf("node value : %.2f\n", bound);
    printf("node weight : %d\n", node.weight);
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
void knapsack(int item_index, int maxprofit, int maxweight, int n, int* include, int* value, int* weight, struct node* queue, int index){
    if ((queue[index].weight <= maxweight) && (queue[index].value > maxprofit)) { // 지금까지 최고의 답
		maxprofit = queue[index].value;
        printf("item index : %d\n",item_index);
        
	}
    for(int i=0; i<11; i++){
            printf("%d ", include[i]);
        }printf("\n");

    if (promising(maxprofit, maxweight, n, include, value, weight, queue[index])) {
        if(queue[index].value > maxweight)
        maxweight = queue[index].value;
        int temp[11];
        memmove(temp, include, sizeof(int)*11);
        
        printf("index : %d\n", index);
        printf("maxprofit : %d\n\n", maxprofit);
        //make left child node
        // Include weight[i+1]
        include[item_index+1] = 1;

        //connect node with queue
        queue[index*2].value = queue[index].value+value[item_index+1];
        queue[index*2].weight = queue[index].weight+weight[item_index+1];
        //maxweight += weight[item_index];

        knapsack(item_index+1, maxprofit, maxweight, n, include, value, weight, queue, index*2);

        //make right child node
        // Not include weight[i+1]

        //connect node with queue
        queue[index*2+1].value = queue[index].value;
        queue[index*2+1].weight = queue[index].weight;
        include = temp;
        include[item_index+1] = 0;
    	knapsack(item_index+1, maxprofit, maxweight, n, include, value, weight, queue, index*2+1);
    }
}
