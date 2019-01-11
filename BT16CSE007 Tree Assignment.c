#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct tree_node_tag{
	int roll_number;
	char name[5];
	char subject_code[3];
	int marks;
	char department[5];
	int sem_number;
	
	struct tree_node_tag *left;
	struct tree_node_tag *right;
}TreeNode;

typedef struct record_tag{
	int roll_number;
	char name[5];
	char subject_code[3];
	int marks;
	char department[5];
	int sem_number;
	
	struct record_tag *next;
}record;

typedef struct popular_subject_tag{
	int marks;
	char subject_code[3];
	
	struct popular_subject_tag *next;
}pop_sub;

typedef struct topper_list_tag{
	int roll_number;
	char name[5];
	char subject_code[3];
	int marks;
	
	struct topper_list_tag *next;
}topper_list;

void InOrder(TreeNode *root);
void Visit(TreeNode *root);
void MergeSort(pop_sub** headRef);
void divide(pop_sub* source, pop_sub** frontRef, pop_sub** backRef);
pop_sub* mergeself(pop_sub* a, pop_sub* b);
/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
			// Function to Make New Tree Node


TreeNode* MakeNode(int rollno, char sub_code[])
{	
	char name[5], dept[5];
	int mrks, sem_no;
	
	printf("Enter the Name of Student: ");
	scanf("%s", name);
	printf("Enter Marks: ");
	scanf("%d", &mrks);
	printf("Department: ");
	scanf("%s", dept);
	printf("Semester Number: ");
	scanf("%d", &sem_no);
	
	TreeNode *nptr;
	nptr = (TreeNode*)malloc(sizeof(TreeNode));
	nptr->roll_number = rollno;
	strcpy(nptr->name, name);
	strcpy(nptr->subject_code, sub_code);
	nptr->marks = mrks;
	strcpy(nptr->department, dept);
	nptr->sem_number = sem_no;
	
	return(nptr);
}

/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
				// Function to find height of tree

int height(TreeNode *root)
{
	int ret_val, right_height, left_height;
	if(root == NULL)
	{
		ret_val = -1;
	}
	else if(root->left == NULL && root->right == NULL)
	{
		ret_val = 1;
	}
	else
	{
		left_height = height(root->left);
		right_height = height(root->right);
	
	
		if(left_height > right_height)
		{
			ret_val = left_height + 1;
		}
		else
		{
			ret_val = right_height + 1;
		}
	}	
	return(ret_val);
}

/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
				// Function to Rotate Right

TreeNode* rotate_right(TreeNode *ptr)
{
	TreeNode *tmp = ptr;
	if(ptr == NULL)
	{
		printf("\nERROR\n");
	}
	else if(ptr->left == NULL)
	{
		printf("Cannot Rotate Right\n");
	}
	else
	{
		tmp = ptr->left;
		ptr->left = tmp->right;
		tmp->right = ptr;
	}
	
	return(tmp);
}

/*------------------------------------------------------------------------------*/
			// Function to rotate left

TreeNode* rotate_left(TreeNode *ptr)
{
	TreeNode *tmp = ptr;
	if(ptr == NULL)
	{
		printf("\nERROR\n");
	}
	else if(ptr->right == NULL)
	{
		printf("Cannot Rotate Left\n");
	}
	else
	{
		tmp = ptr->right;
		ptr->right = tmp->left;
		tmp->left = ptr;
	}
	return(tmp);
}

/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
				//Function to insert new node

TreeNode* InsertNode(TreeNode *node, int rollno, char sub_code[])
{
	int balance;

	if(node == NULL)
	{
		return(MakeNode(rollno, sub_code));
	}
	else if(rollno < node->roll_number)
	{
		node->left = InsertNode(node->left, rollno, sub_code);
	}
	else if(rollno > node->roll_number)
	{
		node->right = InsertNode(node->right, rollno, sub_code);
	}
	else
	{
		if(strcmp(sub_code, node->subject_code)<0)
		{
			node->left = InsertNode(node->left, rollno, sub_code);
		}
		else if(strcmp(sub_code, node->subject_code)>0)
		{
			node->right = InsertNode(node->right, rollno, sub_code);
		}
		else
		{
			printf("\nNode Already Exists.\n");
		}
	}
	printf("Test 01\n");
	balance = height(node->left) - height(node->right);
	printf("Height Balance : %d\n", balance);
	printf("Test 02\n");
	
	if(balance > 1)
	{
		if(rollno < (node->left)->roll_number)
		{
			node = rotate_right(node);
			printf("LL\n");
		}
		else if(rollno > (node->left)->roll_number)
		{
			node->left = rotate_left(node->left);
			node = rotate_right(node);
			printf("LR\n");
		}
		else if(rollno == (node->left)->roll_number)
		{
			if(strcmp(sub_code, (node->left)->subject_code) < 0)
			{
				node = rotate_right(node);
				printf("LL\n");
			}
			else if(strcmp(sub_code, (node->left)->subject_code) > 0)
			{
				node->left = rotate_left(node->left);
				node = rotate_right(node);
				printf("LR\n");
			}
		}
	}
	
	if(balance < -1)
	{
		if(rollno > (node->right)->roll_number)
		{
			node = rotate_left(node);
			printf("RR\n");
		}
		else if(rollno < (node->right)->roll_number)
		{
			node->right = rotate_right(node->right);
			node = rotate_left(node);
			printf("RL\n");
		}
		else if(rollno == (node->right)->roll_number)
		{
			if(strcmp(sub_code, (node->right)->subject_code) > 0)
			{
				node = rotate_left(node);
				printf("RR\n");
			}
			else if(strcmp(sub_code, (node->right)->subject_code) < 0)
			{
				node->right = rotate_right(node->right);
				node = rotate_left(node);
				printf("RL\n");
			}
		}
	}
	
	return(node);
}

/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/

TreeNode* minValueNode(TreeNode* node)
{
    TreeNode* current = node;
 
    while (current->left != NULL)
    {
    	current = current->left;
    }   
 
    return(current);
}


/*------------------------------------------------------------------------------*/

TreeNode* deleteNode(TreeNode *root, int rollno, char sub_code[])
{
	
	int balance;
	
	if(root == NULL)
	{
		return(root);
	}
	
	if(rollno < root->roll_number)
	{
		root->left = deleteNode(root->left, rollno, sub_code);
	}
	else if(rollno > root->roll_number)
	{
		root->right = deleteNode(root->right, rollno, sub_code);
	}
	else
	{
		if(strcmp(sub_code, root->subject_code) < 0)
		{
			root->left = deleteNode(root->left, rollno, sub_code);
		}
		else if(strcmp(sub_code, root->subject_code) > 0)
		{
			root->right = deleteNode(root->right, rollno, sub_code);
		}
		else
		{
			if(root->left == NULL || root->right == NULL)
			{
				TreeNode *tmp = root->left ? root->left : root->right;
				
				if(tmp == NULL)
				{
					tmp = root;
					root = NULL;
				}
				else
				{
					*root = *tmp;
				}
				
				free(tmp);
			}
			else
			{
				TreeNode *tmp = minValueNode(root->right);
				
				root->roll_number = tmp->roll_number;
				strcpy(root->subject_code, tmp->subject_code);
				strcpy(root->name, tmp->name);
				root->marks = tmp->marks;
				strcpy(root->department, tmp->department);
				root->sem_number = tmp->sem_number;
				
				root->right = deleteNode(root->right, tmp->roll_number, tmp->subject_code);
			}
		}
	}
	
	if(root == NULL)
	{
		return(root);
	}
	printf("test01\n");
	balance = height(root->left) - height(root->right);
	printf("balance:%d\n", balance);
	printf("test02\n");
	
	if(balance > 1)
	{
		int bal_1 = height(root->left) - height(root->left->right);
		
		if(bal_1 >= 0)
		{
			return(rotate_right(root));
		}
		else
		{
			root->left = rotate_left(root->left);
			return(rotate_right(root));
		}
		
	}
	
	if(balance < -1)
	{
		int bal_1 = height(root->right->left);
		if(bal_1 > 0)
		{
			return(rotate_right(root));
		}
		else
		{
			root->right = rotate_right(root->right);
			return(rotate_left(root));
		}
	}
	
	return(root);
}

/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
				//Function to find Number of Nodes

int NumbNodes(TreeNode *root)
{
	int ret_val;
	if(root == NULL)
	{
		ret_val = 0;
	}
	else
	{
		ret_val = 1 + NumbNodes(root->left) + NumbNodes(root->right);
	}
	return(ret_val);
}

/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
//			// Function to Search data in Tree

int search(TreeNode *root, int rollno, char sub_code[], int status)
{
	status = 0;
	if(root != NULL)
	{
		if(rollno < root->roll_number)
		{
			status = search(root->left, rollno, sub_code, status);
		}
		else if(rollno > root->roll_number)
		{
			status = search(root->right, rollno, sub_code, status);
		}
		else
		{
			if(strcmp(sub_code, root->subject_code) < 0)
			{
				status = search(root->left, rollno, sub_code, status);
			}
			else if(strcmp(sub_code, root->subject_code) > 0)
			{
				status = search(root->right, rollno, sub_code, status);
			}
			else
			{
				status = 1;
			}
		}
	}
	
	return(status);
}

/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
				// Function to create list

record* listInsert(record *list, TreeNode *root)
{
	record *nptr;
	
	nptr = (record*)malloc(sizeof(record));
	nptr->roll_number = root->roll_number;
	strcpy(nptr->name, root->name);
	strcpy(nptr->subject_code, root->subject_code);
	nptr->sem_number = root->sem_number;
	strcpy(nptr->department, root->department);
	
	nptr->next = list;
	list = nptr;
	
	return(list);
}

/*------------------------------------------------------------------------------*/
				//Function to find failures

record* failures(record *list, TreeNode *root, int cutoff_marks, char sub_code[])
{
	int count = 0;
	
	if(root == NULL)
	{
		printf("\nNO FURTHER DATABASE\n");
	}
	
	if(root != NULL)
	{
		if(strcmp(sub_code, root->subject_code) == 0)
		{
			if(root->marks < cutoff_marks)
			{
				list = listInsert(list, root);
				count++;
			}
		}
		
		list = failures(list, root->left, cutoff_marks, sub_code);
		list = failures(list, root->right, cutoff_marks, sub_code);
		
	}
	
	return(list);
}


/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
				//Function for Range Search

void rangeSearch(TreeNode *root, int upper_limit, int lower_limit)
{
	TreeNode *ptr;
	ptr = root;
	
	if(root != NULL)
	{	
		printf("1\n");
		if(root->roll_number >= lower_limit && root->roll_number <= upper_limit)
		{
			rangeSearch(root->left, upper_limit, lower_limit);
			Visit(root);
			printf("2\n");
			rangeSearch(root->right, upper_limit, lower_limit);
		}
		printf("3\n");
	}	
}

/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
				// Function to get max value

int getMaxValue(TreeNode *root, int max)
{
	if(root != NULL)
	{
		if(root->marks > max)
		{
			max = root->marks;
		}
		max = getMaxValue(root->left, max);
		max = getMaxValue(root->right, max);
	}
	return(max);
}

/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
				// Function to insert popular subject node

pop_sub* Insert_SubNode(pop_sub *popular, TreeNode *root)
{
	pop_sub *sub_node;
	
	sub_node = (pop_sub*)malloc(sizeof(pop_sub));
	strcpy(sub_node->subject_code, root->subject_code);
	sub_node->marks = root->marks;
	
	sub_node->next = popular;
	popular = sub_node;
	
	return(popular);
}

/*------------------------------------------------------------------------------*/
				// Function to find kth popular subject

pop_sub* Kthpopular(pop_sub *popular, TreeNode *root)
{
	int flag = 0;
	pop_sub *ptr;
	ptr = popular;
	
	if(root != NULL)
	{	
		if(popular == NULL)
		{
			popular = Insert_SubNode(popular, root);
			ptr = popular;
		}
		else
		{
			popular = ptr;
			while(flag == 0 && popular != NULL)
			{
				if(strcmp(root->subject_code, popular->subject_code) == 0)
				{
					popular->marks = popular->marks + root->marks;
					flag = 1;
				}
				else
				{
					popular = popular->next;
				}
			}
			popular = ptr;
			
			if(flag == 0)
			{
				popular = Insert_SubNode(popular, root);
			}
		}
		
		popular = Kthpopular(popular, root->left);
		popular = Kthpopular(popular, root->right);
	}
	MergeSort(&popular);
	return(popular);
}

/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/

int num_nodes(pop_sub *lptr)
{
	int count = 0;
	pop_sub *nptr;
	
	nptr = lptr;
	
	if(nptr == NULL)
	{
		printf("NO list\n");
	}
	else
	{
		while(nptr != NULL)
		{
			count++;
			nptr = nptr -> next;
		}
	}
	
	return(count);
}

/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
			// Function to insert topper node

topper_list* InsertTopper(topper_list *tptr, TreeNode *root)
{
	topper_list *nptr;
	
	nptr = (topper_list*)malloc(sizeof(topper_list));
	nptr->roll_number = root->roll_number;
	strcpy(nptr->name, root->name);
	strcpy(nptr->subject_code, root->subject_code);
	nptr->marks = root->marks;
	
	nptr->next = tptr;
	tptr = nptr;
	
	return(tptr);
}

/*------------------------------------------------------------------------------*/
			// Function to replace topper

topper_list* ReplaceTopper(topper_list *tptr, TreeNode *root)
{
	tptr->roll_number = root->roll_number;
	strcpy(tptr->name, root->name);
	strcpy(tptr->subject_code, root->subject_code);
	tptr->marks = root->marks;
	
	return(tptr);
}

/*------------------------------------------------------------------------------*/
			// Function to find topper

topper_list* getTopper(topper_list *tptr, TreeNode *root)
{
	int flag = 0;
	topper_list *ptr;
	ptr = tptr;
	
	if(root != NULL)
	{
		if(tptr == NULL)
		{
			tptr = InsertTopper(tptr, root);
		}
		else
		{
			tptr = ptr;
			while(flag == 0 && tptr != NULL)
			{
				if(strcmp(tptr->subject_code, root->subject_code) == 0)
				{
					if(root->marks > tptr->marks)
					{
						tptr = ReplaceTopper(tptr, root);
						flag = 1;
					}
				}
				tptr = tptr->next;
			}
			tptr = ptr;
			
			if(tptr == NULL)
			{
				tptr = InsertTopper(tptr, root);
			}
		}
		
		tptr = getTopper(tptr, root->left);
		tptr = getTopper(tptr, root->right);
	}
	
	return(tptr);
}

/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
			//Function to display The Data

void Visit(TreeNode *root)
{
	if(root == NULL)
	{
		printf("* Root is NULL *");
	}
	else
	{
		printf("****************************\n");
		printf("Name: %s\n", root->name);
		printf("Roll Number: %d\n", root->roll_number);
		printf("Subject Code: %s\n", root->subject_code);
		printf("Marks: %d\n", root->marks);
		printf("Department: %s\n", root->department);
		printf("Semester: %d\n", root->sem_number);
		printf("****************************\n");
	}
}

/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
			// InOrder Traversal

void InOrder(TreeNode *root)
{
	if(root != NULL)
	{
		InOrder(root->left);
		Visit(root);
		InOrder(root->right);
	}
}

/*------------------------------------------------------------------------------*/
			// PreOrder Traversal

void PreOrder(TreeNode *root)
{
	if(root != NULL)
	{
		Visit(root);
		PreOrder(root->left);
		PreOrder(root->right);
	}
}

/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
void PostOrder(TreeNode *root)
{
	if(root != NULL)
	{
		PostOrder(root->left);
		PostOrder(root->right);
		Visit(root);
	}
}
/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
			// Function to display list data

void display(record *list)
{
	record *nptr;
	nptr = list;
	if(nptr == NULL)
	{
		printf("\nNO LIST to Display\n");
	}
	else
	{
		while(nptr != NULL)
		{
			printf("******************************************\n");
			printf("Name: %s\n", nptr->name);
			printf("Roll Number: %d\n", nptr->roll_number);
			printf("Subject Code: %s\n", nptr->subject_code);
			printf("Department: %s\n", nptr->department);
			printf("Semester: %d\n", nptr->sem_number);
			printf("******************************************\n");
			
			nptr = nptr->next;
		}
	}
}

/*------------------------------------------------------------------------------*/

void display_popular(pop_sub *popular)
{
	if(popular == NULL)
	{
		printf("NO POPULAR SUBJECT\n");
	}
	else
	{
		while(popular!=NULL){
			printf("Subject Code: %s\n", popular->subject_code);
			printf("Marks: %d\n", popular->marks);
			
			popular = popular->next;
		}
	}
}

/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
			// Function to display topper list

void display_topper(topper_list *tptr)
{
	if(tptr == NULL)
	{
		printf("NO TOPPER\n");
	}
	else
	{
		while(tptr != NULL)
		{
			printf("Name: %s\n", tptr->name);
			printf("Roll Number: %d\n", tptr->roll_number);
			printf("Subject Code: %s\n", tptr->subject_code);
			printf("Marks: %d\n", tptr->marks);
			
			tptr = tptr->next;
		}
	}
}

/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
			// MERGE SORT

void MergeSort(pop_sub** headRef)
{
	pop_sub* head =* headRef;
	pop_sub* a;
	pop_sub* b;
 
	if ((head == NULL) || (head->next == NULL))
	{
		return ;
	}
	
	divide(head, &a, &b); 
	MergeSort(&a);
	MergeSort(&b);
   
	*headRef = mergeself(a, b);
}
		
void divide(pop_sub* source, pop_sub** frontRef, pop_sub** backRef)
{
	pop_sub* fast;
	pop_sub* slow;
	
	if (source==NULL || source->next==NULL)
	{
		*frontRef = source;
		*backRef = NULL;
	}
	else
	{
		slow = source;
		fast = source->next;
  
		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
 
  
		*frontRef = source;
		*backRef = slow->next;
		slow->next = NULL;
	}
}
 
pop_sub* mergeself(pop_sub* a, pop_sub* b){
	pop_sub* result = NULL;
 
  
	if (a == NULL)
	return(b);
	else if (b==NULL)
	return(a);
 
	if (a->marks < b->marks)
	{
		result = a;
		result->next = mergeself(a->next, b);
	}
	else
	{
		result = b;
		result->next = mergeself(a, b->next);
	}
	return(result);
}

/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
			// Main Function

int main()
{
	int cont = 1;
	int choice;
	int rollno;
	char sub_code[3];
	int cutoff_marks;
	int upper_limit, lower_limit;
	int max_Value = 0;
	int i,k;
	
	TreeNode *root = NULL;
	record *list = NULL;
	pop_sub *pop_sub_list = NULL;
	topper_list *tptr = NULL;
	
	printf("\nSTUDENT RECORDS using AVL TREE\n");
	
	while(cont == 1)
	{
		printf("\n");
		printf("\n01.Insert Node\n");
		printf("02.Delete Node\n");
		printf("03.Number of Records\n");
		printf("04.Height of Tree\n");
		printf("05.Search Data\n");
		printf("06.Range Search\n");
		printf("07.Find Failures\n");
		printf("08.Get Maximum Value\n");
		printf("09.Kth popular Subject\n");
		printf("10.Get Topper\n");
		printf("11.In Order\n");
		printf("12.Pre-Order\n");
		printf("13.Post-Order\n");
		printf("Enter your Choice: ");
		scanf("%d", &choice);
		
		switch(choice)
		{
			case 1 : printf("\nPlease fill the required Details...\n");
					 
					 printf("\nEnter the Roll Number: ");
					 scanf("%d", &rollno);
					 printf("Enter the Subject Code: ");
					 scanf("%s", sub_code);
				 	 
				 	 root = InsertNode(root, rollno, sub_code);
				 	 printf("Insertion Successfull...\n");
				 	 break;
				 	 
			case 2 : printf("\nEnter the Roll Number of Student: ");
					 scanf("%d", &rollno);
					 printf("Enter the Subject Code: ");
					 scanf("%s", sub_code);
					 
					 root = deleteNode(root, rollno, sub_code);
					 printf("Deletion Successfull\n");
					 break;
				 	 
			case 3 : printf("\nGetting Number of Records...\n");
					 int number_of_records = NumbNodes(root);
					 printf("Number of Records: %d\n", number_of_records);
					 break;

			case 4 : printf("\nDisplaying Height of Tree...\n");
					 int tree_height = height(root);
					 printf("Height: %d\n", tree_height);
					 break;
					 
			case 5 : printf("\nSEARCH DATA\n");
					 printf("Enter the Roll number: ");
					 scanf("%d", &rollno);
					 printf("Enter the Subject Code: ");
					 scanf("%s", sub_code);
					 
					 int status = search(root, rollno, sub_code, status);
					 
					 if(status == 1)
					 {
					 	printf("The given node is present\n");
					 }
					 else
					 {
					 	printf("Given node is not present\n");
					 }
					 break;
					 
			case 6 : printf("\nRANGE SEARCH...\n");
					 printf("Enter Lower Limit of Roll Number: ");
					 scanf("%d", &lower_limit);
					 printf("Enter Upper Limit: ");
					 scanf("%d", &upper_limit);
					 
					 rangeSearch(root, upper_limit, lower_limit);
					 break;
					 
			case 7 : printf("\nFINDING FAILURES...\n");
					 printf("Enter the Subject Code: ");
					 scanf("%s", sub_code);
					 printf("Enter the cut-off marks: ");
					 scanf("%d", &cutoff_marks);
					 
					 list = NULL;
					 list = failures(list, root, cutoff_marks, sub_code);
					 display(list);
					 break;
					 
			case 8 : printf("\nGetting Max Value...\n");
					 max_Value = getMaxValue(root, max_Value);
					 printf("Max Value: %d\n", max_Value);
					 break;
					 
			case 9 : printf("\nKTH POPULAR SUBJECT...\n");
					 pop_sub_list = Kthpopular(pop_sub_list, root);display_popular(pop_sub_list);
					 printf("Enter the value of k: ");
					 scanf("%d", &k);
					 
					 int j = num_nodes(pop_sub_list);
					 i = 0;
					 printf("zzzzzzzzz\n");
					 while(i>=j-k+1)
					 {
					 	pop_sub_list = pop_sub_list->next;
					 	i++;
					 }
					 display_popular(pop_sub_list);
					 break;
					 
			case 10 : printf("\nGETTING TOPPER....\n");
					  tptr = getTopper(tptr, root);
					  display_topper(tptr);
					  break;		 		 
				 	 
			case 11 : printf("\nDisplaying Data...\n\n");
					  InOrder(root);
					  break;
					 
			case 12 : printf("\nDisplaying Data...\n\n");
					  PreOrder(root);
					  break;
					  
			case 13 : printf("Displaying Data...\n\n");
					  PostOrder(root);
					  break;		  
					 
			default : printf("\nInvalid Input !!\n");
					  break;		 	 	 
		}
		
		printf("Do you want to continue (1/0): ");
		scanf("%d", &cont);
		
	}
	
	return(0);
}
