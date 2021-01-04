#include<stdio.h>
#include<stdlib.h>

int timeslice;

typedef struct redblacknode{ // structure to create a red black node
    int pn;
	float vruntime;
	float totaltime;
	struct redblacknode *rightnode;
	struct redblacknode *leftnode;
	struct redblacknode *parentnode;
	char colour;
}node;


typedef struct rbtree{ //structure to create a red black tree which links the nodes
  node *rootnode;
  node *nill_node;
}tree;

node* createnode(float data,float tt,int i) { //function to create a node and put the given vruntime as the value of the node
 node* newnode=malloc(sizeof(node)); //assigningmemory to a node inorder to create it
	newnode->pn=i;
  newnode->leftnode=NULL;
  newnode->rightnode=NULL; //At thispoint the newly created node doesn't link to any other node.
  newnode->parentnode=NULL;
  newnode->vruntime=data;
  newnode->totaltime=tt;
  newnode->colour='R'; //the newly inserted nodes' colour is always RED

  return newnode;
}

tree* createtree() { //function to create the red black tree
  tree *newtree = malloc(sizeof(tree)); //allocate memory for a tree(according to the above tree structure)
  node *nillnode = malloc(sizeof(node)); //nillnode refers to the null node in the RBT.
  nillnode->leftnode = NULL;
  nillnode->rightnode = NULL;
  nillnode->parentnode=NULL;
  nillnode->colour = 'B'; //as all nill nodes' colour is always BLACK.
  nillnode->vruntime=0.0; //as nill node doesn't contain any value
  newtree->nill_node= nillnode;
  newtree->rootnode= newtree->nill_node; //the first nillnode created will be assigned to the tree as it's root

  return newtree;
}


void leftrotate(tree*newtree,node*nnode);
void rightrotate(tree*newtree,node*nnode);


node*insert(tree*newtree,float data,float tt,int i){
	node*nn=createnode(data,tt,i);//create the node
	node*pn=newtree->nill_node; //parent node intialization
	node*ptr=newtree->rootnode;//pointer node to traverse
	
	while(ptr!=newtree->nill_node){
		pn=ptr; //determine the parent everytime it goes through the while loop
		if(nn->vruntime<ptr->vruntime){ 
			ptr=ptr->leftnode;        
			
		}
		else{
			ptr=ptr->rightnode;//min values go left
		}
	}
	nn->parentnode=pn;
	if(pn==newtree->nill_node){ //this is the root then
		newtree->rootnode=nn;
	}
	else if(nn->vruntime<pn->vruntime){ //connects the newnode to the parentnode
		pn->leftnode=nn;
	}
	else{
		pn->rightnode=nn;
	}

	nn->leftnode=newtree->nill_node; //no children for new node
	nn->rightnode=newtree->nill_node;


	
	node *p;
	while(nn->parentnode->colour=='R'){
		if(nn->parentnode==nn->parentnode->parentnode->leftnode){
			p=nn->parentnode->parentnode->rightnode;//uncle of newnode(nn)
				if(p->colour=='R'){ //1st case :- if uncle is red.
				nn->parentnode->colour=='B'; //have to do a colour flip
				p->colour='B';
				nn->parentnode->parentnode->colour='R';
				nn=nn->parentnode->parentnode;
			}
			else {
				
			if(nn==nn->parentnode->rightnode){
				nn=nn->parentnode;
				leftrotate(newtree,nn);
			}
		
			
			nn->parentnode->colour='B';
			nn->parentnode->parentnode->colour='R';
			rightrotate(newtree,nn->parentnode->parentnode);
		}
		}
	
	else{
		p=nn->parentnode->parentnode->leftnode;
		if(p->colour=='R'){
			nn->parentnode->colour='B';
			p->colour='B';
			nn->parentnode->parentnode->colour='R';
			nn=nn->parentnode->parentnode;
		}
		else {
			
		if(nn==nn->parentnode->leftnode){
			nn=nn->parentnode;
			rightrotate(newtree,nn);
		}
		nn->parentnode->colour='B';
		nn->parentnode->parentnode->colour='R';
		leftrotate(newtree,nn->parentnode->parentnode);
	}
	
}
return nn;
}

newtree->rootnode->colour='B';

}





void rightrotate(tree*newtree,node* nnode){
	node *a=nnode->leftnode;
	nnode->leftnode=a->rightnode;
	if(a->rightnode!=newtree->nill_node){
		a->rightnode->parentnode=nnode;
	}
	a->parentnode=nnode->parentnode;
	
	if(nnode->parentnode==newtree->nill_node){
		newtree->rootnode=a;
	}
	else if(nnode==nnode->parentnode->rightnode){
		nnode->parentnode->rightnode=a;
	}
	else{
		nnode->parentnode->leftnode=a;
	}
	a->rightnode=nnode;
	nnode->parentnode=a;
}

void leftrotate(tree*newtree,node*nnode){
	node*a=nnode->rightnode;
	nnode->rightnode=a->leftnode;
	if(a->leftnode!=newtree->nill_node){
		a->leftnode->parentnode=nnode;
	}
	a->parentnode=nnode->parentnode;
	
	if(nnode->parentnode==newtree->nill_node){
		newtree->rootnode=a;
	}
	else if(nnode==nnode->parentnode->leftnode){
		nnode->parentnode->leftnode=a;
		
	}
	
	
	else{
		nnode->parentnode->rightnode=a;
	}
	a->leftnode=nnode;
	nnode->parentnode=a;
}

node* min(tree *newtree,node*temp){
	while(temp->leftnode!=newtree->nill_node){
		temp=temp->leftnode;
	}
	return temp;
}

node* run(tree*newtree){//function which returns the process which is going to run next
 
	node*ptr=newtree->rootnode; //starts from the root
	while(ptr->leftnode!=newtree->nill_node){
		ptr=ptr->leftnode; //go until the next leftmost node is null
}

	return ptr;
}

node* deletenode(tree*newtree,node*delnode){
	node*delet=delnode;
	node*a=delnode;
	node*temp;
	char a_or_colour=a->colour;
	if(delnode->leftnode==newtree->nill_node){
		temp=delnode->rightnode;
		if(delnode->parentnode==newtree->nill_node){
			newtree->rootnode=delnode->rightnode;
		//printf(" parentnode-nill\n");
		}
		else if(delnode==delnode->parentnode->leftnode){
			delnode->parentnode->leftnode=delnode->rightnode;
			//	printf(" child-nill,left\n");
			}
		else{
			delnode->parentnode->rightnode=delnode->rightnode;
			//	printf(" right\n");
		}
		delnode->rightnode->parentnode=delnode->parentnode;
		//printf(" same\n");
		}
		else if(delnode->rightnode==newtree->nill_node){
			temp=delnode->leftnode;
			if(delnode->parentnode==newtree->nill_node){
				newtree->rootnode=delnode->leftnode;
				//printf(" parentnode-nill\n");
			}
			else if(delnode==delnode->parentnode->leftnode){
				delnode->parentnode->leftnode=delnode->leftnode;
				//	printf(" child-nill,left\n");
			}
		else{
			delnode->parentnode->rightnode=delnode->leftnode;
			//	printf(" right\n");
		}
		delnode->leftnode->parentnode=delnode->parentnode;
		//printf(" same\n");
	}
	else{
		a=min(newtree,delnode->rightnode);
		a_or_colour=a->colour;
		temp=a->rightnode;
		if(a->parentnode==delnode){
			temp->parentnode=delnode;
		}
		else{
			if(a->parentnode==newtree->nill_node){
				newtree->rootnode=a;
				//printf(" parentnode-nill\n");
			}
			else if(a==a->parentnode->leftnode){
				a->parentnode->leftnode=a->rightnode;
				//	printf(" child-nill,left\n");
			}
			else{
				a->parentnode->rightnode=a->rightnode;
				//	printf(" right\n");
			}
			a->rightnode->parentnode=a->parentnode;
			//printf(" same\n");
			a->rightnode=delnode->rightnode;
			a->rightnode->parentnode=a;
		}		
		if(delnode->parentnode==newtree->nill_node){
			newtree->rootnode=a;
			//printf(" parentnode-nill\n");
		}
		else if(delnode==delnode->parentnode->leftnode){
			delnode->parentnode->leftnode=a;
			//	printf(" child-nill,left\n");
		}
		else{
			delnode->parentnode->rightnode=a;
			//	printf(" right\n");
		}
		a->parentnode=delnode->parentnode;
		//printf(" same\n");
		a->leftnode=delnode->leftnode;
		a->leftnode->parentnode=a;
		a->colour=delnode->colour;
	}
	
	if(a_or_colour=='B'){
		
		while(temp!=newtree->rootnode && temp->colour=='B'){
			if(temp==temp->parentnode->leftnode){
				node*sibling=temp->parentnode->rightnode;
				if(sibling->colour=='R'){
					sibling->colour='B';
					temp->parentnode->colour='R';
					leftrotate(newtree,temp->parentnode);
					sibling=temp->parentnode->rightnode;
				}
				if(sibling->leftnode->colour=='B' && sibling->rightnode->colour=='B'){
					sibling->colour='R';
					temp=temp->parentnode;
				}
				else{
					if(sibling->rightnode->colour=='B'){
						sibling->leftnode->colour='B';
						sibling->colour='R';
						rightrotate(newtree,sibling);
						sibling=temp->parentnode->rightnode;
					}
					sibling->colour=temp->parentnode->colour;
					temp->parentnode->colour='B';
					sibling->rightnode->colour='B';
					leftrotate(newtree,temp->parentnode);
					temp=newtree->rootnode;
				}
			}
			else{
				node*sibling=temp->parentnode->leftnode;
				if(sibling->colour=='R'){
					sibling->colour=='B';
					temp->parentnode->colour='R';
					rightrotate(newtree,temp->parentnode);
					sibling=temp->parentnode->leftnode;
				}
				if(sibling->rightnode->colour=='B'&& sibling->leftnode->colour=='B'){
					sibling->colour='R';
					temp=temp->parentnode;
				}
				else{
					if(sibling->leftnode->colour=='B'){
						sibling->rightnode->colour='B';
						sibling->colour='R';
						leftrotate(newtree,sibling);
						sibling=temp->parentnode->leftnode;
					}
					sibling->colour=temp->parentnode->colour;
					temp->parentnode->colour='B';
					sibling->leftnode->colour='B';
					rightrotate(newtree,temp->parentnode);
					temp=newtree->rootnode;
				}
			}
		}
		temp->colour='B';
	}
	return delet;
}

void inorder(tree *t, node *n) {
  if(n != t->nill_node) {
    inorder(t, n->leftnode);
    printf("\tprocess %d: ", n->pn);
    printf("%.2f\n", n->vruntime);
    inorder(t, n->rightnode);
  }
  
}

int pnum=0;
float remain_t=0.0,rtq;




int main()
{
float time_quant; //the time quantam of the cpu
tree  *newtree=createtree(); //creatingthe red black tree
int process_count=0;
float vt,tt;
int k=1,m=1,i,pn;
int flag=0;
int num_p=0;
node*j;
node*deleted;

printf("Enter the time quantam of CPU: ");
scanf("%f",&time_quant);
printf("Enter how many processes are there in the ready queue: ");
scanf("%d",&pnum);
num_p=pnum; //number of processes in the ready queue(the red black tree in this case)
node*a[pnum];
node*del;
rtq=time_quant; //rtq= remaining time quantam of the cpu at first it is equal to the original time quantam of the cpu.
float ptime=rtq/num_p; //the equal amount of time which will be given to each process at a particular time
int p=pnum;
printf("\n");

for(i=1;i<=pnum;i++){
	printf("Enter the virtual run time of the process %d: ",i); //virtual runtime is the time a process has already run in the cpu.
	scanf("%f",&vt); //vt will be 0 if it is a newly arrived process at that time.
	printf("Enter the total run time of the process   %d: ",i);
	scanf("%f",&tt); //tt is the total amount of time units which a process has to run in order to get completed.
	
	a[i]=insert(newtree, vt,tt,i); //insert the vruntime values while creating the nodes.
	printf("Process Succefully added.\n\n");
}
printf("\nCURRENT PROCESSES WITH THEIR VIRTUAL RUN TIMES\n\n");
inorder(newtree,newtree->rootnode);
printf("\n\n\n");
node*perm_deleted[pnum]; //an array of pointers tohold the permanantlydeleted nodes' addresses.




while(process_count!=pnum){
if(rtq>0){

printf("*******Remaining Time quantum at the moment      : %.2f\n",rtq);
printf("*******Number of processes at the moment         : %d\n",p);
printf("*******Amount of time which goes to each process : %.2f\n\n\n",ptime);
j=run(newtree); //get the leftmost node of the tree at the moment.
p--;
if(p<=0){
	p=num_p;
}
printf("The process %d is running.\n\n",j->pn); 
}			
				vt=j->vruntime+ptime;
				rtq=rtq-ptime;
				pn=j->pn;
				tt=j->totaltime;
				if(vt>=tt){ //if the time which can be given by the cpu is greater than the process's needed time
					del=j;
					pn=j->pn;
					perm_deleted[m]=deletenode(newtree,j); //permanantly deleted the node as the processis completed.
					printf("The process %d is completed. So it is removed from the system.\n\n",pn);
					
					remain_t=(vt-tt);// the excess time amount the cpu could give to the previously completed job
						printf("*****************************************************\n");
						printf("Remaining time quantum of the CPU             : %.2f\n",rtq);
					if(remain_t>0){
						printf("Remaining excess time of the completed process: %.2f\n",remain_t);
				}
					rtq=rtq+remain_t; //updating the rtq as there's a remaining time too
					if(rtq>0){
					
						printf("Time quantum of the CPU which can be given    : %.2f\n",rtq);
					}
						printf("*****************************************************\n");
					process_count++; //the number of processes which have beedn deleted is incremented.
					num_p--; //number of processes(nodes) in the redblack tree gets reduced as one was deleted.
					p=num_p;
					ptime=rtq/num_p; //updating the ptime according to the current situation.
					m++;
				}
				else{
				pn=j->pn;
				deleted=deletenode(newtree,j); //temporarily deleting the process inoder to update the virtual runtime.
				a[k]=insert(newtree,vt,tt,pn); //inserting the updated node(process) again to the tree.
				
			}
			if(rtq<=0){ //if rtq becomes 0 or less than 0 that means the remaining time given by cpu is over
					rtq=time_quant; //as all processes are not completed yet again cpu gives it's full time quantam.
					printf("\nRemaining Time quantum is over. Updated to the initial CPU time quantum.\n\n");
					ptime=rtq/num_p; //ptimeis updated according to the current situation.
				}

printf("\nCURRENT PROCESSES WITH THEIR VIRTUAL RUN TIMES\n\n");
inorder(newtree,newtree->rootnode);
printf("\n\n\n");
	}
	printf("All the processes has been completed.\n\n");
	return 0;
}
