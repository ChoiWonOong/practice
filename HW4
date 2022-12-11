#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
int total_cnt;

int* toBi(unsigned int n){
    static int temp[32];

    for(int i=0; i<32; i++){
        temp[i]=0;
    }
    int cnt=0;
    while(n >= 1){ 
        temp[cnt] = n%2;
        n=n/2;
        cnt++;
    }
    int len = sizeof(temp)/sizeof(int);
    //printf("len : %d\n", len);  //check length
    /*
    printf("output : ");
    
    for(int j = 0; j<len; j++){
        printf("%d", temp[j]);    //check output
    }
    printf("\n");*/
    return temp;
}
//Binary To Int Some Index -> from (start) index before (start+num) index
unsigned int Part_BiToInt(int start, int num, int* bi){
    unsigned int sum=0;
    int mul = 1;
    
    for(int i=start; i<start+num; i++ ){
        printf("%d",bi[i]);
        sum += bi[i]*mul;
        mul*=2;
        //printf("sum = %d\n", sum);    //mid_check
    }
    printf("\n");
    return sum;
}

int main(int argc, char* argv[]){
    int is_written=1;
    int set = atoi(argv[1]);
    int set_bit = 0;
    while (set>1){
        set = set / 2;
        set_bit++;      
    }
    printf("set bit : %d\n", set_bit);
    int way = atoi(argv[2]);
    int block_bytes = atoi(argv[3]);
    int block_bit=0;
    while (block_bytes>1){
        block_bytes = block_bytes / 2;
        block_bit++;
    }
    printf("block_bit : %d\n", block_bit);
    char* alloc_type = argv[4];
    char* file_name = argv[5];
    int hit = 0;
    int miss = 0;
    int write_flag;
    //check write-allocation
    if(strcmp(alloc_type,"write-allocate")==0){
        write_flag = 0;
    }
    else if(strcmp(alloc_type,"no-write-allocate")==0){
        write_flag = 1;
    }
    else{
        //argument exception
        printf("Invalid write-allocation\n");
        printf("Choose between write-allocate / no-write-allocate\n");
        exit(-1);
    }
    // ways
    int sizey = way;

    // sets
    int sizex = set_bit;
    
    //make cache by array
    //n만큼 배열의 세로 동적할당
    int** arr = (int**)malloc(sizeof(int*) * sizey);
    
    //size만큼 배열의 가로 동적할당 
    for (int i = 0; i < sizex; i++) { 
        arr[i] = (int*)malloc(sizeof(int) * sizex); 
    }
    // 배열을 -1으로 초기화
    for(int i=0; i<sizex; i++){
        for(int j=0; j<sizey; j++){
            arr[j][i] = -1;
        }
    }
    
    // hit / miss counter
    int load_miss = 0;
    int load_hit = 0; 
    int write_miss = 0;
    int write_hit = 0;
    /*
    int input_sets;
    int input_ways;
    int block_bytes;
    */
    total_cnt=0;
    int fd, read_size, write_size;
    char buf[64];
    char* ptr;
    char* cache_args[4];
    int* val;
    int cache_val[33];  

    // dynamic array allocation
    //
    // total cache volume = n_way * sets
    // int [n_way][set] 
    // e.g. 256 set 4 way
    //      int [4][256] -> 256 cache instructions
    //      int [4][128] -> 512 cache instructions
    // 
    // Use Binary To Int Function ( int* -> int )
    // 
    // initiallize all bits to zero
    for(int i=0; i<32; i++){
        cache_val[i] = 0;
    }

    unsigned int temp;
    if(argc != 6){
        printf("./getCache [sets] [ways] [block bytes] [write-alloc type] [File Name]\n");
        exit(-1); 
    }
    /*
    
    */
    fd = open(file_name, O_RDONLY);
    if(fd<0){
        printf("Can't Open");
        exit(-1);
    }
    while(1){
        int inner_cnt=0;
        read_size = read(fd, buf, 15);
        if(read_size==0)
            break;
        ptr = strtok(buf, " ");
        while(ptr!=NULL){
            cache_args[inner_cnt] = ptr;          
            ptr = strtok(NULL, " ");
            inner_cnt++;
        }
        write(STDOUT_FILENO, buf, read_size);
        temp = strtoul(cache_args[1], NULL, 16);
        printf("temp : %u\n", temp);     //16진수 -> 10진수
                
        val = toBi(temp);           //10진수 -> 2진수 배열 ex)15 -> 1111 0000 0000 0000 0000 0000 0000 0000 -> 8byte
        printf("Bi num : ");                          //check Binary number
        for(int i = 0; i< 32 ; i++){
            printf("%d", val[i]);
        }
        
        printf("\n");
    
        printf("cache : ");
        for(int i = 31; i>=0; i--){
            cache_val[i] = val[i];
            printf("%d", cache_val[i]);
        }
        printf("\n");
        printf("block : ");
        int block_num = Part_BiToInt(0, block_bit,cache_val);

        printf("set : ");
        int set_num = Part_BiToInt(block_bit, sizex ,cache_val);

        printf("tag : ");
        int tag_num = Part_BiToInt(block_bit+sizex, 32-block_bit-sizex, cache_val);
        printf("block : %d\n", block_num);
        printf("set_num : %d\n", sizex);
        printf("tag_num : %d\n", 32-block_bit-sizex);
        
        // Block Bytes - use if needed
        
        //printf("block : %d\n", block_bit);
        printf("sets : %d\n", set_num);
        printf("tags : %d\n", tag_num);



        //compare values
        //
        // 첫번 째 글자 l , s 에 따라 다르게 수행
        //
        //set 를 더 많이 비교하므로 int* 부분에 set 개수를 입력 후
        // i 번째 way 에 tag value 대입 
        /*      //draw array
    for (int i = 0; i < sizey; i++) {
        for (int j = 0; j < sizex; j++) {
            printf("%d ",arr[i][j]);
            
        }
        printf("\n");
    }
    printf("draw\n");
    */
    
    printf("sizex : %d\n", sizex);
    printf("sizey : %d\n", sizey);
    for(int i = 0; i<sizey; i++){
        if(arr[i][set_num]==tag_num){       //Hit
            if(strcmp(cache_args[0],"l")==0)
                load_hit++;
            else
                write_hit++;
            is_written=1;
            //printf("hit\n");
            //printf("flag : %d\n", is_written);
            break;
        }//
        else{                       //Miss
            if(arr[i][set_num]==-1){     //if empty
                if(strcmp(cache_args[0],"l")==0){   //load
                    load_miss++;
                    arr[i][set_num]=tag_num;    //input cache value
                    is_written=1;
                    break;
                }
                else{                               //store
                    write_miss++;
                    if(write_flag==1){}     //if no-allocate
                    else if(write_flag==0)  //if allocate access cache
                        arr[sizey-1][set_num] = tag_num;
                    is_written=1;
                    break;
                }
                          
                //printf("miss\n"); 
                //printf("flag : %d\n", is_written); //check is_written
                
                
            }
            else{                   //if not empty
                is_written=0;
                continue;
            }           
        }
    }
    
    if(is_written==0){//FIFO
        for(int i=0;i<sizey-1; i++){
            arr[i][set_num] = arr[i+1][set_num];
        }
        //printf("miss\n");
        //printf("flag : %d\n", is_written);
        if(strcmp(cache_args[0],"l")==0){
            load_miss++;
            arr[sizey-1][set_num] = tag_num;
        }
        else{
            write_miss++;
            if(write_flag==1){}         //if no-allocate
            else if(write_flag==0)      //if allocate access cache
                arr[sizey-1][set_num] = tag_num;
        }
        
    }
    printf("Total_load : %d\n", load_hit+load_miss);
    printf("Total_write : %d\n", write_hit+write_miss);
    printf("load_hit : %d\n", load_hit);
    printf("load_miss : %d\n", load_miss);
    printf("write_hit : %d\n", write_hit);
    printf("write_miss : %d\n\n", write_miss);
        total_cnt++;
    }
    
    printf("Total Cycles : %d\n", total_cnt);
    close(fd);
    return 0;
}

//
//1. get instruction with a line
//
//2. tokenize and make list with tokens
//
//3. Transform hexa to binary
//
//4. compare other bits(set ,  tag)
//
//  implement write-through / write back
//
//  write-through
//  
//  
//  
//  implement allocate / no-allocate
//
//  no-allocate
//  miss +1
//
//  allocate
//  load cache instruction from cpu
//
// – Write-through + No-write-allocate
// – Write-back + Write-allocate
