#include <stdio.h>
#include <stdlib.h>

struct cord
{
    double value;
    struct cord *next;
};
struct vector
{
    struct vector *next;
    struct cord *cordsArr;
};

int closest(double **centroids, double *vector1,int size1,int size2){
    double close=0;
    int result=0;
    int i,j;
    for( i=0;i<size1;i++ ){
        close+=(centroids[0][i]-vector1[i])*(centroids[0][i]-vector1[i]);
    }
    for( i=0;i<size2;i++){
        double tmp=0;
        for( j=0;j<size1;j++){
            tmp+=(centroids[i][j]-vector1[j])*(centroids[i][j]-vector1[j]);
        }
        if(tmp<close){
            close=tmp;
            result=i;
        }
    }
    return result;
}

double* divide(double *arr,int size){
    double *result;
    int i;
    result=(double*)malloc((size)*sizeof(double));
    if(result == NULL){
        printf("An Error Has Occurred");
        exit(1);
    }
    for(i=0 ;i<size;i++){
        result[i]=arr[i]/arr[size];
    }
    return result;
}
int check(double **centroids1,double **centroids2,int size1,int size2){
    double sum;
    int i;
    int j;
    for ( i = 0; i < size1; i++)
    {
        sum=0.0;

        for (j = 0; j < size2; j++)
        {
            sum+=(centroids1[i][j]-centroids2[i][j])*(centroids1[i][j]-centroids2[i][j]);
        }
        if((sum*sum)>0.000001){
          return -1;
     }
    }
    
    return 1;
}
int digit(char x){
    if(!(x<='9' && x>='0')) return 0;
    return 1;
}
int isNumber(char* s){
    int i;
    for (i=0;s[i]!='\0';i++){
        if((digit(s[i])==0)) return 0;
    }
    return 1;
}

void print_centroids(double **centroids, int K, int dimensions) {
    int i, j;
    for (i = 0; i < K; i++) {
        for (j = 0; j < dimensions; j++) {
            printf("%.4f", centroids[i][j]);
            if (j < dimensions - 1) {
                printf(",");
            }
        }
        printf("\n");
    }
}

void freeCords(struct cord *head) {

    if (head != NULL){
        freeCords(head->next);
        free(head);
    }

}


void freeLinkedList(struct vector* head) {
    struct vector* currentVector = head;
    struct vector* nextVector;
    while (currentVector != NULL) {
        
        struct cord* currentCord = currentVector->cordsArr;
        struct cord* nextCord;
        currentVector->cordsArr = NULL;
        nextVector = currentVector->next;
        free(currentVector);
        currentVector = nextVector;

        while (currentCord != NULL) {
            nextCord = currentCord->next;
            free(currentCord);
            currentCord = nextCord;
        }

        
    }
}




int main(int argc , char **argv){
    int k;


    int max_iter;
    int q=0;
    int flag=-1;
    int i;
    int j;
    int vDim;
    int n=0;
    char c;
    double** vectors;

    double **centroids,**centroids2;
    double **matrix;
    int close;


    struct vector *head_vec, *curr_vec;
    struct cord *head_cord, *curr_cord;
    int cols;
    double val;
    int colNum;
    int linesNum=0;


    head_cord = malloc(sizeof(struct cord));
    curr_cord = head_cord;
    curr_cord->next = NULL;

    head_vec = malloc(sizeof(struct vector));
    curr_vec = head_vec;
    curr_vec->next = NULL;



    if(argc==2){
        k=atoi(argv[1]);
        max_iter=200;

    }
    if(argc==3){
    k=atoi(argv[1]);
    max_iter=atoi(argv[2]);


    }

    



/*getting the input*/
    while (scanf("%lf%c", &val, &c) == 2) {
        curr_cord->value = val;
        curr_cord->next = malloc(sizeof(struct cord));
        curr_cord = curr_cord->next;
        curr_cord->next = NULL;
        cols++;

        if (c == '\n') {
            if (cols > colNum) {
                colNum = cols;
            }
            cols = 0;
            curr_vec->cordsArr = head_cord;
            curr_vec->next = malloc(sizeof(struct vector));
            curr_vec = curr_vec->next;
            curr_vec->next = NULL;
            head_cord = malloc(sizeof(struct cord));
            curr_cord = head_cord;
            curr_cord->next = NULL;
            linesNum++;
        }
    }
    if (cols > 0) {
        if (cols > colNum) {
            colNum = cols;
        }
        curr_vec->cordsArr = head_cord;
        linesNum++;
    } else {
        free(curr_cord);
        curr_vec->cordsArr = NULL;
        /*curr_vec->cordsArr = head_cord;*/
    }
    n = linesNum;


    vDim=colNum;
    vectors = (double**)malloc(n*sizeof(double*));
    if(vectors==NULL){
        printf("An Error Has Occurred");
        exit(1);
    }
    for( i =0;i<n;i++)
    {
        vectors[i]=(double*)malloc(vDim*sizeof(double));
        if(vectors[i]==NULL){
            printf("An Error Has Occurred");
            exit(1);
        }
        
    }
    
    curr_vec = head_vec;
    curr_cord = curr_vec->cordsArr;
/*filling the matrix form the input*/
    for ( i = 0; i < linesNum; i++) {
        for ( j = 0; j < colNum; j++) {
            if (curr_cord != NULL) {
                vectors[i][j] = curr_cord->value;
                curr_cord = curr_cord->next;
            } else {
                vectors[i][j] = 0.0;
            }
        }
        curr_vec = curr_vec->next;
        if (curr_vec != NULL) {
            curr_cord = curr_vec->cordsArr;
        }
    }
    
    
    
    
    
    
    if(k>=n || k<=1)
    {
        printf("Invalid number of clusters!\n");
    }
    if (max_iter <= 1 || max_iter >= 1000){
        printf("Invalid maximum iteration!\n");
    }
    if (k>=n || k<=1 || max_iter <= 1 || max_iter >= 1000){
        return 1;
    }


    centroids=(double**)malloc(k*sizeof(double*));
    if(centroids==NULL){
        printf("An Error Has Occurred");
        exit(1);
    }
    
    for( i=0;i<k;i++){
        centroids[i]=(double*)malloc(vDim*sizeof(double));
        if(centroids[i]==NULL){
            printf("An Error Has Occurred");
            exit(1);
        }
    }
    centroids2=(double**)malloc(k*sizeof(double*));
    if(centroids2==NULL){
        printf("An Error Has Occurred");
        exit(1);
    }
    for( i=0;i<k;i++){
        centroids2[i]=(double*)malloc(vDim*sizeof(double));
        if(centroids2[i]==NULL){
            printf("An Error Has Occurred");
            exit(1);
        }
    }
    for( i=0;i<k;i++){
        for( j=0;j<vDim;j++) {
            centroids[i][j]=vectors[i][j];
        }
    }
    matrix= (double**) malloc(k*sizeof(double*));
    if(matrix==NULL){
        printf("An Error Has Occurred");
        exit(1);
    }
    for( i=0;i<k;i++)
    {
        matrix[i]=(double*)malloc((vDim+1)*sizeof(double));
        if(matrix[i]==NULL){
            printf("An Error Has Occurred");
            exit(1);
        }
    }
    
   
    while(q<max_iter && flag==-1){
        
        for( i=0;i<k;i++){
            
            for( j=0;j<vDim+1;j++){
                matrix[i][j]=0;
                
            }
        }
        for( i=0;i<n;i++)
        {
             close=closest(centroids,vectors[i],vDim,k);
            for( j=0;j<vDim;j++){
                
                matrix[close][j]+=vectors[i][j];
                 if(j==0){
                    matrix[close][vDim]+=1;
                }
            }
            
        }

        for( i=0;i<k;i++){
            for( j =0;j<vDim;j++){
                
                centroids2[i][j]=centroids[i][j];
                
            }
        }

        for( i=0;i<k;i++){
            free(centroids[i]);
            centroids[i]=divide(matrix[i],vDim);
        }
        flag=check(centroids,centroids2,k,vDim);
        q+=1;

    }
    print_centroids(centroids, k, vDim);

    for( i=0;i<n;i++){
        free(vectors[i]);
    }
    free(vectors);
    for( i =0;i<k;i++){
        free(centroids[i]);
        free(centroids2[i]);
        free(matrix[i]);
    }
    free(centroids);
    free(centroids2);
    free(matrix);

    curr_vec = head_vec;
    freeLinkedList(curr_vec);

return 0;
}