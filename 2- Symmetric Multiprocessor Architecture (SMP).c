#include<stdio.h>
#include<stdlib.h>

//please consider that for printing a single character it only takes 0.5 units of time(Nano seconds)
int timeslice;

typedef struct cpu_structure{
	int number;
	int occupied;
	float time_quant;
	float rtq;
	float ptime;
}processor;

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

processor*create_processor(int num,int oc,float tq,float rt,float pt){
	processor *newprocessor=malloc(sizeof(processor));
	newprocessor->number=num;
	newprocessor->occupied=oc;
	newprocessor->time_quant=tq;
	newprocessor->rtq=rt;
	newprocessor->ptime=pt;
	return newprocessor;
	
}

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


int i;


	


	
	

int	count_1=0;
int	count_2=0;
int	count_3=0;
int	count_4=0; 


void f1(float pt){ //print simple letters from a to p
		float x=0.00;
		char b[16];
		
for(i=0;i<16;i++){
		b[i]='a'+i;
	}
		while(x<pt){
			if(count_1!=16){
		printf("\n\t\t%c\n",b[count_1]);
		count_1++;
	}
		x=x+0.50;
	}
}
	
void f2(float pt){ //print eight *
	float x=0.00;

	char c[8];
for(i=0;i<8;i++){
		c[i]='*';
	}
	while(x<pt){
		printf("\n\t\t%c\n",c[count_2]);
		count_2++;
		x=x+pt;
	}

}





void f3(float pt){ //print integers from 1 to 4

	float x=0.00;
	 int d[4];
for(i=1;i<=4;i++){
		d[i]=i;
	}
		while(x<pt){
		printf("\n\t\t%d\n",d[count_3+1]);
		count_3++;
		x=x+pt;
	}

}


void f4(float pt){ //print capital letters from A to K
	float x=0.00;
	char e[12];
for(i=0;i<12;i++){
		e[i]='A'+i;
	}
	while(x<pt){
		printf("\n\t\t%c\n",e[count_4]);
		count_4++;
		x=x+pt;
	}

}



int pnum=0;
float remain_t=0.0,rtq;




int main()
{
float tq[2],rtq,ptime; //the time quantam of the cpu
int cpu=2;
tree  *newtree=createtree(); //creatingthe red black tree
int process_count=0;
float pvt[4],ptt[4];
float vt,tt;
int k=1,m=1,pn;
int flag=0;
int num_p=0;
node*j;
node*deleted;
ptt[1]=8.00;
pvt[1]=0.00;
ptt[2]=4.00;
pvt[2]=0.00;
ptt[3]=2.00;
pvt[3]=0.00;
ptt[4]=6.00;
pvt[4]=0.00;

tq[1]=2.00;
tq[2]=2.00;
pnum=4;
printf("\n\tThere are %d processors. \n\n",cpu);
printf("\tThe time quantum of the processor 1: %.2f\n",tq[1]);
printf("\tThe time quantum of the processor 2: %.2f\n\n",tq[2]);
printf("\n\tThere are %d processes in the ready queue: \n\n",pnum);

for(i=1;i<=4;i++){
	printf("  The process number                :%d \n",i);
	printf("  The total time of the process     :%.2f\n",ptt[i]);
	printf("  The virtual runtime of the process:%.2f\n\n\n",pvt[i]);

}

num_p=pnum; //number of processes in the ready queue(the red black tree in this case)
node*a[pnum];
node*del;

int p=pnum;


processor*processors[cpu];
for(i=1;i<=2;i++){
	rtq=tq[i]; //rtq= remaining time quantam of the cpu at first it is equal to the original time quantam of the cpu.
	ptime=rtq/num_p; //the equal amount of time which will be given to each process at a particular time
	processors[i]=create_processor(i,0,tq[i],rtq,ptime);
}
printf("\n");

for(i=1;i<=pnum;i++){
	a[i]=insert(newtree,pvt[i],ptt[i],i); //insert the vruntime values while creating the nodes.
}
printf("\n\nCURRENT PROCESSES WITH THEIR VIRTUAL RUN TIMES: \n");
inorder(newtree,newtree->rootnode);
printf("\n\n\n");
node*perm_deleted[pnum]; //an array of pointers tohold the permanantlydeleted nodes' addresses.


int l;
while(process_count!=pnum){
l=pnum-process_count;

if(processors[1]->occupied==0){
	if(processors[1]->rtq>0){

printf("\n*******Remaining Time quantum at the moment of processor %d : %.2f\n",processors[1]->number,processors[1]->rtq);
printf("*******Number of processes at the moment                    : %d\n",l);
printf("*******Amount of time which goes to each process            : %.2f\n\n\n",processors[1]->ptime);
	j=run(newtree); //get the leftmost node of the tree at the moment.
	printf("\nThe process %d is running in the processor %d.\n\n",j->pn,processors[1]->number);
	printf("\tOUTPUT: ");
	if(j->pn==1){
		f1(processors[1]->ptime);// CALL FUNCTION 1
	}
	else if(j->pn==2){
			f2(processors[1]->ptime);// CALL FUNCTION 2
	}
	else if(j->pn==3){
			f3(processors[1]->ptime);// CALL FUNCTION 3
	}
	else if(j->pn==4){
			f4(processors[1]->ptime);// CALL FUNCTION 4
	}
	else{
		printf("Error");
	}
	p--;
	if(p<=0){
		p=num_p;
	}
	 
}
	vt=j->vruntime+processors[1]->ptime;
	processors[1]->rtq = (processors[1]->rtq) - (processors[1]->ptime);
	pn=j->pn;
	tt=j->totaltime;
	
	if(vt>=tt){ //if the time which can be given by the cpu is greater than the process's needed time
					del=j;
					pn=j->pn;
					perm_deleted[m]=deletenode(newtree,j); //permanantly deleted the node as the processis completed.
					printf("\nThe process %d is completed. So it is removed from the system.\n\n",pn);
					process_count++; //the number of processes which have beedn deleted is incremented.
					remain_t=(vt-tt);// the excess time amount the cpu could give to the previously completed job
						printf("*****************************************************\n");
						printf("Remaining time quantum of the CPU  %d         : %.2f\n",processors[1]->number,processors[1]->rtq);
					if(remain_t>0){
						printf("Remaining excess time of the completed process: %.2f\n",remain_t);
				}
					processors[1]->rtq=processors[1]->rtq+remain_t; //updating the rtq as there's a remaining time too
					if(processors[1]->rtq>0){
					
						printf("Time quantum of the CPU which can be given    : %.2f\n",processors[1]->rtq);
					}
						printf("*****************************************************\n");
					
					num_p--; //number of processes(nodes) in the redblack tree gets reduced as one was deleted.
					p=num_p;
					processors[1]->ptime=processors[1]->rtq/num_p; //updating the ptime according to the current situation.
					if(processors[1]->ptime<0.50 || (processors[1]->ptime>0.50 && processors[1]->ptime<1.00)){
						processors[1]->ptime=0.50;
					}
					m++;
				}
				
				else{
				pn=j->pn;
				deleted=deletenode(newtree,j); //temporarily deleting the process inoder to update the virtual runtime.
				a[k]=insert(newtree,vt,tt,pn); //inserting the updated node(process) again to the tree.
				
			}
			
			if(processors[1]->rtq<=0){ //if rtq becomes 0 or less than 0 that means the remaining time given by cpu is over
					processors[1]->rtq=processors[1]->time_quant; //as all processes are not completed yet again cpu gives it's full time quantam.
					printf("\nRemaining Time quantum is over. Updated to the initial CPU time quantum.\n\n");
					processors[1]->ptime=processors[1]->rtq/num_p; //ptimeis updated according to the current situation.
					if(processors[1]->ptime<0.50 || (processors[1]->ptime>0.50 && processors[1]->ptime<1.00)){
						processors[1]->ptime=0.50;
					}
				}
	
	printf("\n\nCURRENT PROCESSES WITH THEIR VIRTUAL RUN TIMES: \n");
	printf("\n");
	inorder(newtree,newtree->rootnode);
	printf("\n\n\n");
	
	
	
}
if(processors[2]->occupied==0){
	if(num_p<pnum){
		p=num_p+1;
	}
	
	if(processors[2]->rtq>0){

printf("\n*******Remaining Time quantum at the moment of processor %d : %.2f\n",processors[2]->number,processors[2]->rtq);
printf("*******Number of processes at the moment                    : %d\n",l);
printf("*******Amount of time which goes to each process            : %.2f\n\n\n",processors[2]->ptime);
j=run(newtree);

	printf("The process %d is running in the processor %d.\n\n",j->pn,processors[2]->number); 
		printf("\tOUTPUT: ");
	if(j->pn==1){
		f1(processors[1]->ptime);// CALL FUNCTION 1
	}
	else if(j->pn==2){
			f2(processors[1]->ptime);// CALL FUNCTION 2
	}
	else if(j->pn==3){
			f3(processors[1]->ptime);// CALL FUNCTION 3
	}
	else if(j->pn==4){
			f4(processors[1]->ptime);// CALL FUNCTION 4
	}
	else{
		printf("Error");
	}
	p--;
	
	if(p<=0){
		p=num_p;
	}
	
}

	vt=j->vruntime+processors[2]->ptime;
	processors[2]->rtq = (processors[2]->rtq) - (processors[2]->ptime);
	pn=j->pn;
	tt=j->totaltime;
	if(vt>=tt){ //if the time which can be given by the cpu is greater than the process's needed time

					del=j;
					pn=j->pn;
					perm_deleted[m]=deletenode(newtree,j); //permanantly deleted the node as the processis completed.
					printf("\nThe process %d is completed. So it is removed from the system.\n\n",pn);
					process_count++; //the number of processes which have beedn deleted is incremented.
					remain_t=(vt-tt);// the excess time amount the cpu could give to the previously completed job
						printf("*****************************************************\n");
						printf("Remaining time quantum of the CPU %d          : %.2f\n",processors[2]->number,processors[2]->rtq);
					if(remain_t>0){
						printf("Remaining excess time of the completed process: %.2f\n",remain_t);
				}
					processors[2]->rtq=processors[2]->rtq+remain_t; //updating the rtq as there's a remaining time too
					if(processors[2]->rtq>0){
					
						printf("Time quantum of the CPU which can be given    : %.2f\n",processors[2]->rtq);
					}
					printf("*****************************************************\n");
					
					num_p--; //number of processes(nodes) in the redblack tree gets reduced as one was deleted.
					p=num_p;
					processors[2]->ptime=processors[2]->rtq/num_p; //updating the ptime according to the current situation.
					if(processors[2]->ptime<0.50 || (processors[2]->ptime>0.50 && processors[2]->ptime<1.00)){
						processors[2]->ptime=0.50;
					}
					m++;
				}
				
				else{
				pn=j->pn;
				deleted=deletenode(newtree,j); //temporarily deleting the process inoder to update the virtual runtime.
				a[k]=insert(newtree,vt,tt,pn); //inserting the updated node(process) again to the tree.
				
			}
			
			if(processors[2]->rtq<=0){ //if rtq becomes 0 or less than 0 that means the remaining time given by cpu is over
					processors[2]->rtq=processors[2]->time_quant; //as all processes are not completed yet again cpu gives it's full time quantam.
					printf("\nRemaining Time quantum is over. Updated to the initial CPU time quantum.\n\n");
					processors[2]->ptime=processors[2]->rtq/num_p; //ptimeis updated according to the current situation.
					if(processors[2]->ptime<0.50 || (processors[2]->ptime>0.50 && processors[2]->ptime<1.00)){
						processors[2]->ptime=0.50;
					}
				}
	
	printf("\n\nCURRENT PROCESSES WITH THEIR VIRTUAL RUN TIMES: \n");
	if(process_count==pnum){
		printf("\nNothing left in the red black tree.\n");
	}
	printf("\n");
	inorder(newtree,newtree->rootnode);
	printf("\n\n\n");
	
	
	
	
}
printf("\n***************************************************************************************\n");
printf("\n\tONE ROUND IS OVER.\n");
printf("\n***************************************************************************************\n");
p=num_p;	
	

}
printf("\n\n\tAll the processes has been completed.\n\n");
return 0;
}
