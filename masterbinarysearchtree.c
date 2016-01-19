#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

struct Score_Binary_Tree{
	double score_number;
	int total_number_of_reviews;
	struct review_Binary_Tree *reviewPtr;
	struct Score_Binary_Tree *right;
	struct Score_Binary_Tree *left;
}Score_Binary_Tree;

typedef struct Score_Binary_Tree node;

struct review_Binary_Tree{
	int review_id;
   	char text[200];
	struct review_Binary_Tree *right;
	struct review_Binary_Tree *left;
	
}review_Binary_Tree;

typedef struct review_Binary_Tree node2;

struct Score_Binary_Tree *ScoreTree=NULL;

FILE *inpf;

double m_total;
int m_count;

node* search(node ** tree, double score_number){
	
    if(!(*tree)){
        return NULL;
    }

    if(score_number < (*tree)->score_number){
        search(&((*tree)->left), score_number);
    }
    
    else if(score_number > (*tree)->score_number){
        search(&((*tree)->right), score_number);
    }
    
    else if(score_number == (*tree)->score_number){
        printf("Warning! Existent score number");
        main();
    }
    
}

void preorder_display(node *tree,node2 *tree2){

    if(tree){
        
		printf("Score:%lf\n",tree->score_number);	
        printf("Review id:%d\n",tree->reviewPtr->review_id);
        printf("Text:%s\n\n",tree->reviewPtr->text);
	    preorder_display(tree->left,tree2);
	    preorder_display(tree->right,tree2);
        				
    }
    
}

void inorder_display(node *tree,node2 *tree2){

    if(tree){
       
	    inorder_display(tree->left,tree2);
	    printf("Score:%lf\n",tree->score_number);	
        printf("Review id:%d\n",tree->reviewPtr->review_id);
        printf("Text:%s\n\n",tree->reviewPtr->text);
	    inorder_display(tree->right,tree2);

        				
    }
    
}

void postorder_display(node *tree,node2 *tree2){

    if(tree){
       
	    postorder_display(tree->left,tree2);
	    postorder_display(tree->right,tree2);
	    printf("Score:%lf\n",tree->score_number);	
        printf("Review id:%d\n",tree->reviewPtr->review_id);
        printf("Text:%s\n\n",tree->reviewPtr->text);
        				
    }
    
}

void addScore(node **tree,double score_number,int total_number_of_reviews){
	
    node *temp = NULL;
    int review_id;
    char text[200];
    
    if(!(*tree)){
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        temp->score_number = score_number;
        temp->reviewPtr =(node2 *)malloc(sizeof(node2));
        temp->reviewPtr->review_id=review_id;
        strcpy(temp->reviewPtr->text,text);
        temp->reviewPtr->left = temp->reviewPtr->right =NULL ;
        *tree = temp;
        return;
    }

    if(score_number < (*tree)->score_number){
        addScore(&(*tree)->left, score_number,total_number_of_reviews);
    }
    
    else if(score_number > (*tree)->score_number){
        addScore(&(*tree)->right, score_number,total_number_of_reviews);
    }
    

}

void addReview(node **tree,node2 **tree2,double score_number,int review_id,char text[],int total_number_of_reviews){
	
    node *temp = NULL;
    
    if(!(*tree)){
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        temp->score_number = score_number;
        temp->reviewPtr =(node2 *)malloc(sizeof(node2));
        temp->reviewPtr->review_id=review_id;
        strcpy(temp->reviewPtr->text,text);
        temp->reviewPtr->left = temp->reviewPtr->right ;
        *tree = temp;
        return;
    }

    if(score_number < (*tree)->score_number){
        addReview(&(*tree)->left,tree2, score_number,review_id,text,total_number_of_reviews);
    }
    
    else if(score_number > (*tree)->score_number){
        addReview(&(*tree)->right,tree2, score_number,review_id,text,total_number_of_reviews);
    }
    
    else if(score_number == (*tree)->score_number){

    if(review_id < (*tree)->reviewPtr->review_id){
        addReview(&(*tree)->left,tree2,score_number,review_id,text,total_number_of_reviews);
    }
    
    else if(review_id > (*tree)->reviewPtr->review_id){
        addReview(&(*tree)->right,tree2,score_number,review_id,text,total_number_of_reviews);
    }

    }
    

}


double calculateAverageScore(node *n){

    double score_number;
    
    if (n == NULL) return 0;
        m_count++;
        m_total += n->score_number; 
        calculateAverageScore( n->left );
        calculateAverageScore( n->right );
        return m_total / (double)m_count;   // return the average
        
}

void listReviewsContainsAParticularWord(node *tree,char word[]){
    
	if (tree){
		
		if((strstr(tree->reviewPtr->text,word)) != NULL){
            printf("%d\n",tree->reviewPtr->review_id);
        }

        listReviewsContainsAParticularWord(tree->left,word);
        listReviewsContainsAParticularWord(tree->right,word);

    }
			
    
}

node* minimal(node *tree){
	
    if(tree==NULL){    	
       return NULL;
    }

    if(tree->left) 
      return minimal(tree->left);

    else 
      return tree;
      
}


node * delete(node *tree, double starting_scope_period, double end_scope_period){
       
	   node *temp;

       if(tree==NULL){
              printf("Element Not Found");
       }

       if(starting_scope_period < tree->score_number){
       	
              tree->left = delete(tree->left, starting_scope_period, end_scope_period);
              
       }

       else if(starting_scope_period > tree->score_number){
       	
              tree->right = delete(tree->right, starting_scope_period, end_scope_period);
      }
      
      
      else{
            /* Now We can delete this node and replace with either minimum element 
               in the right sub tree or maximum element in the left subtree */			
			if(tree->right && tree->left){

                    /* Here we will replace with minimum element in the right sub tree */
                    temp = minimal(tree->right);
                    tree -> score_number = temp->score_number;
					temp->reviewPtr->review_id = temp->reviewPtr->review_id; 
                    /* As we replaced it with some other node, we have to delete that node */
                    tree -> right = delete(tree->right,temp->score_number,end_scope_period);
                    
            }
            
            else{
                    /* If there is only one or zero children then we can directly 
                       remove it from the tree and connect its parent to its child */
                       					
                    temp = tree;
                    if(tree->left == NULL)
                            tree = tree->right;
                    else if(tree->right == NULL)
                            tree = tree->left;
                    free(temp);
					free(temp->reviewPtr); /* temp is longer required */

					 
            }
            
            while(starting_scope_period < end_scope_period){
            	starting_scope_period=starting_scope_period+0.5;
            	printf("%lf",starting_scope_period);   	
            	
            }


    }               

         
    return tree;

}


int  main(){

    int i,totalNumOfReview,reviewId;
    double scoreNumber,average,starting_scope_period,end_scope_period;
    char text[200];
    char word[200];
    
    node *root;
    node2 *root2;
    root=NULL;
    root2=NULL;
    
    DIR *dir;
    struct dirent *ent;

		  
	if ((dir = opendir ("C:\\Users\\Oguz's pc\\Desktop\\data proje2\\reviews\\")) != NULL) {
    /* print all the files and directories within directory */
        
    while ((ent = readdir (dir)) != NULL) {
        
    	//Cyle empty two times
		char str1[4],str2[4];
    	int ret1,ret2;
    	strcpy(str1, ".");
        strcpy(str2, "..");
        
        ret1 = strcmp(str1, ent->d_name);
        ret2 = strcmp(str2, ent->d_name);
                
        if(ret1 == 0){
         continue;
        }
        if(ret2 == 0){
         continue;
        }
    	
	    //Get filenames in order to read files
		char locfile[]="C:\\Users\\Oguz's pc\\Desktop\\data proje2\\reviews\\";
        strcat(locfile,ent->d_name);

        //int count;
        char *s;
        //count=0;

	    if((inpf = fopen(locfile,"r")) == NULL){
		printf("Input File Could Not Be Opened!\n");
		return;
	    }	    
	    
        memset(text,0,sizeof(text));
		fread(&text, sizeof(text), 8, inpf);

		fclose(inpf);
    
        //Get score and review id from filename
        char *remainderPtr;    
        scoreNumber = strtod (ent->d_name , &remainderPtr );
		
		char *reviewchr;
		reviewchr = ent->d_name;
		memmove (ent->d_name, ent->d_name+1, strlen (ent->d_name+1));					
		reviewId = strtoul(remainderPtr , &reviewchr ,0 );
		
		addReview(&root,&root2 ,scoreNumber,reviewId,text, totalNumOfReview);
        	    	    

    }    
    
    closedir (dir);
     
    }
	      

    else {
     /*could not open directory */
    printf("could not open directory"); 

    }

   
    
    //Reading filenames from order.txt
    /*char buf[100];    
    inpf =fopen("order.txt","r");
    if (!inpf)
    return 1;

    while (fgets(buf,20, inpf)!=NULL){

        char *remainderPtr;    
        scoreNumber = strtod (buf , &remainderPtr );
        
    	char *reviewchr;
		reviewchr = buf;
		memmove (buf, buf+1, strlen (buf+1));					
		reviewId = strtoul(remainderPtr , &reviewchr ,0 );
		
		//char locfile[]="C:\\Users\\Oguz's pc\\Desktop\\data proje2\\reviews\\";
		//strcat(locfile,buf);
		//printf(locfile);
		//char locfile[]=".txt";
		//strcat(locfile,buf);
		//printf(locfile);
		
		addScore(&root,&root2 ,scoreNumber,reviewId,text, totalNumOfReview);
		
    }

    fclose(inpf);*/
    
   
    while(1){
    	
    printf("\n     Welcome \n");
    printf("===============\n");
    printf("\n1.Add a new score node into the master-BST\n");
    printf("2.Add also some reviews into a specific review-score category\n");
    printf("3.Show the average score of all of the reviews\n");
    printf("4.List the id s of reviews which have a particular word\n");
    printf("5.Remove the reviews between in a specific score-scope\n");
    printf("6.Display the tree\n");
    printf("7.Exit\n");
    printf("Enter your choice : ");
    
    if(scanf("%d",&i)<=0){
        printf("Enter only an Integer\n");
        exit(0);
    }
    
	else {
		
        switch(i){
        	
        case 1:
        printf("Enter the score to insert : ");
        scanf("%lf",&scoreNumber);
        search(&root, scoreNumber);
        if(scoreNumber>=0 && scoreNumber<=5 ){
        printf("Enter the total number of review to insert : ");
        scanf("%d",&totalNumOfReview);	
		addScore(&root,scoreNumber,totalNumOfReview);
        }
		 
		else{
		printf("Warning!Score must be between 0-5");
		}       
        break;
        
        case 2:
        printf("Enter the score: ");
        scanf("%lf",&scoreNumber);
        printf("Enter review to insert : ");
        scanf("%d",&reviewId);
        if(reviewId == root->reviewPtr->review_id){
    	printf("Warning! Existent review id");
    	main();
        }
        char emp[1];
        printf("Enter the text to insert : ");
		gets(emp);
		gets(text);
		addReview(&root,&root2,scoreNumber,reviewId,text,totalNumOfReview);     		                              
        break;

        case 3:
        average=calculateAverageScore(root);
        printf("%lf",average);
        break;
        
        case 4:
        printf("Enter the keyword : ");
        scanf("%s",word);
		printf("Review id's list contains a particular word:\n");
        listReviewsContainsAParticularWord(root,word);	            
        break;
        
        case 5:
        printf("Enter the first score to delete : ");
        scanf("%lf",&starting_scope_period);       
        printf("Enter the last score to delete : ");
        scanf("%lf",&end_scope_period);
        
        if(starting_scope_period<0||starting_scope_period>5||end_scope_period<0||end_scope_period>5||starting_scope_period>end_scope_period){
        	printf("Invalid input");
        }
        
        else{
        	printf("Successfully deleted");
            root=delete(root,starting_scope_period,end_scope_period);
        }
        break;
        
        case 6:
	    while(1){

        printf("===============\n");
        printf("\n1.Pre-order display:\n");
        printf("2.In-order display:\n");
        printf("3.Post-order display:\n");
        printf("Enter your choice : ");
    
        if(scanf("%d",&i)<=0){
          printf("Enter only an Integer\n");
          exit(0);
        }
    
	    else {
		
        switch(i){
        	
        case 1:
        printf("\nPRE-ORDER DISPLAY\n");
        printf("===============\n");
        preorder_display(root,root2);
        main();
        break;
        
        case 2:
        printf("\nIN-ORDER DISPLAY\n");
        printf("===============\n");
		inorder_display(root,root2);
		main();	                              
        break;

        case 3:
        printf("\nPOST-ORDER DISPLAY\n");
        printf("===============\n");
		postorder_display(root,root2);
		main();	
        break;

        }
        
        }
        }       
        break;
        
        case 7:     
		return 0;
        default:    
		printf("Invalid option\n");
        }
    }
    }
    return 0;
    
}
