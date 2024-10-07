#include <stdio.h>  
#include <stdlib.h> 
#include <string.h>
struct node
{
    char name[20];
    int runs,fours,sixes,balls;
    float s_rate;
    struct node*next;
};
struct bowl
{
    char name[20];
    int runs,wkts,mdn,overs;
    float econ;
    struct bowl*next;
};
struct teamname
{
    char name[30];
    struct teamname* next;
};
struct teamname* t1,*t2;
struct node * team1,*team2,*sorted1,*sorted2;
struct bowl *tm1,*tm2;
int b_man1[10],b_man2[10],bowler[10],top1=-1,top2=-1,top3=-1;
void insert();
void display();
void displaybl();
int total=0,target=0,played=1;
struct bowl* search(struct bowl*x,char*y)
{
    while(x!=NULL)
    {
        if(!strcmp(x->name,y))
        {
            return x;
        }
        x=x->next;
    }
    return NULL;
}
struct teamname* setname(struct teamname *t1)
{
    struct teamname *new=(struct teamname*)malloc(sizeof(struct teamname));
    printf("TEAM NAME : ");
    scanf("%s",new->name);
    t1=new;
    struct teamname *cur;
    cur=t1;
    for(int i=1;i<=4;i++)
    {
        new=(struct teamname*)malloc(sizeof(struct teamname));
        printf("Player %d : ",i);
        scanf("%s",new->name);
        cur->next=new;
        cur=cur->next;
    }
    cur->next=NULL; 
    return t1;
}   
/*void insert(struct teamname *tm,struct teamname *nod)
{
    while(tm->next!=NULL)
    {
        tm=tm->next;
    }
    tm->next=nod;
}*/
void insert(struct bowl* new,int tmno)
{
    struct bowl*tmp;
    if(tmno==2)
    {
        if(tm1==NULL)
        {
            tm1=new;
        }
        else
        {
            tmp=tm1;
            while(tmp->next!=NULL)
            {
                tmp=tmp->next;
            }
            tmp->next=new;
 
        }
    }
    else{
        if(tm2==NULL)
        {
            tm2=new;
        }
        else
        {
            tmp=tm2;
            while(tmp->next!=NULL)
            {
                tmp=tmp->next;
            }
            tmp->next=new;
    }
    }
}
void bowling(int *bowler,int top3,int tmno,struct bowl*x)
{
    int wkt=0,mdn=0;
    float econ,truns=0;
    for(int i=top3;i>=0;i--)
    {
        if(bowler[i]==-2)
        {
            wkt++;
        }
        else if(bowler[i]!=-1)
        {
            truns=truns+bowler[i];
        }
        else if(bowler[i]==-1)
        {
            truns++;
        }
    }
    if(truns==0)
    {
        mdn++;
    }
    if(played==1)
    {
        total=total+truns;
    }
    if(tmno==2)
    {
        struct bowl*tmp=search(tm1,x->name);
        if(tmp==NULL)
        {
            econ=truns/1;
            x->econ=econ;
            x->mdn=mdn;
            x->next=NULL;
            x->overs=1;
            x->runs=truns;
            x->wkts=wkt;
            insert(x,tmno);
        }
        else
        {
            econ=(truns+tmp->runs)/(1+tmp->overs);
            tmp->econ=econ;
            tmp->mdn=tmp->mdn+mdn;
            tmp->overs=tmp->overs+1;
            tmp->runs=tmp->runs+truns;
            tmp->wkts=tmp->wkts+wkt;
            free(x);
        }
    }
    else
    {
        struct bowl*tmp=search(tm2,x->name);
        if(tmp==NULL)
        {
            econ=truns/1;
            x->econ=econ;
            x->mdn=mdn;
            x->next=NULL;
            x->overs=1;
            x->runs=truns;
            x->wkts=wkt;
            insert(x,tmno);
        }
        else
        {
            econ=(truns+tmp->runs)/(1+tmp->overs);
            tmp->econ=econ;
            tmp->mdn=tmp->mdn+mdn;
            tmp->overs=tmp->overs+1;
            tmp->runs=tmp->runs+truns;
            tmp->wkts=tmp->wkts+wkt;
            free(x);
        }
    }
}

void sort1(struct node*s1,struct node*temp1)
{
    struct node*new=(struct node*)malloc(sizeof(struct node));
    new->balls=temp1->balls;
    new->runs=temp1->runs;
    new->s_rate=temp1->s_rate;
    new->sixes=temp1->sixes;
    new->fours=temp1->fours;
    strcpy(new->name,temp1->name);
    if(s1->runs < new->runs)
    {
        new->next=s1;
        s1=new;
    }
    else
    {
        while(new->runs<=s1->runs && s1->next!=NULL)
        {
            s1=s1->next;
        }
        new->next=s1->next;
        s1->next=new; 
    }
}
void score(int * player,float balls,struct node*new,int tmno)
{
    struct node*tmp;
    int four=0,six=0;
    float strikerate=0,run=0;
    for(int i=balls;i>=0;i--)
    {
        if(player[i]==4)
        {
            run=run+4;
            four++;
        }
        else if(player[i]==6)
        {
            run=run+6;
            six++;
        }
        else
        {
            run=run+player[i];
        }
    }
    new->fours=four;
    new->sixes=six;
    new->runs=run;
    new->balls=balls+1;
 
    //printf("\n%d %d",run,balls);
    strikerate=(run/(balls+1))*100.00;
    new->s_rate=strikerate;
    new->next=NULL;
    if(tmno==1)
    {
        if(team1==NULL)
        {
            team1=new;
        }
        else
        {
            tmp=team1;
            while(tmp->next!=NULL)
            {
                tmp=tmp->next;
            }
            tmp->next=new;
        }
    }
    else
    {
        if(team2==NULL)
        {
            team2=new;
        }
        else
        {
            tmp=team2;
            while(tmp->next!=NULL)
            {
                tmp=tmp->next;
            }
            tmp->next=new;
        }
    }
    
}
void over(int tmno,int op){
    struct node*strike=(struct node*)malloc(sizeof(struct node));
    struct node*nonstrike=(struct node*)malloc(sizeof(struct node));
    struct bowl*bowlr=(struct bowl*)malloc(sizeof(struct bowl));
    int ball=0,runs,wkt=0,overs=0;
    int f=1;
    printf("Striker: ");
    scanf("%s",strike->name);
    printf("Non-Striker: ");
    scanf("%s",nonstrike->name);
    printf("Bowler: ");
    scanf("%s",bowlr->name);
    while(overs<=op &&  total>=target)
    {
        while(ball<6 && total>=target)
        {   
            printf("ball %d : ",ball+1);
            scanf("%d",&runs);
            if(wkt==10)
				break;
            if(f==1)
            {
                if(runs == -1)
                {
                    top3++;
                    bowler[top3]=-1;
                    if(played==-1)
                    {
                        target=target+1;
                    }
                    continue;
                }
                else if(runs==-2)
                {
                    wkt++;
                    ball++;
                    top1++;
                    top3++;
                    b_man1[top1]=0;
                    score(b_man1,top1,strike,tmno);
                    top1=-1;
                    bowler[top3++]=-2;
                    strike=(struct node*)malloc(sizeof(struct node));
                    printf("Enter Batsman : ");
                    scanf("%s",strike->name);
                }
                else if(runs%2==0)
                {
                    top1++;
                    top3++;
                    ball++;
                    bowler[top3]=b_man1[top1]=runs;
                    if(played==-1)
                    {
                        target=target+runs;
                    }
                }
                else if(runs%2!=0)
                {
                    top1++;
                    ball++;
                    top3++;
                    bowler[top3]=b_man1[top1]=runs;
                    if(played==-1)
                    {
                        target=target+runs;
                    }
                    f=0;
                }
            }
            else
            {
                if(runs == -1)
                {
                    top3++;
                    bowler[top3]++;
                    target=target+1;
                    continue;
                }
                else if(runs==-2)
                {
                    wkt++;
                    ball++;
                    top2++;
                    b_man2[top2]=0;
                    score(b_man2,top2,nonstrike,tmno);
                    top2=-1;
                    nonstrike=(struct node*)malloc(sizeof(struct node));
                    printf("Enter Batsman : ");
                    scanf("%s",strike->name);
                }
                else if(runs%2==0)
                {
                    top2++;
                    top3++;
                    ball++;
                    if(played==-1)
                    {
                        target=target+runs;
                    }
                    bowler[top3]=b_man2[top2]=runs;
                }
                else if(runs%2!=0)
                {
                    top2++;
                    ball++;
                    top3++;
                    if(played==-1)
                    {
                        target=target+runs;
                    }
                    bowler[top3]=b_man2[top2]=runs;
                    f=1;
                }
            }
        }
        if(f==0)
        {
			f=1;
		}
		else
		{
			f=0;
		}
        if(total<target)
        {
            break;
        }
        overs++;
        bowling(bowler,top3,tmno,bowlr);
        top3=-1;
        if(overs==op)
        {
            score(b_man1,top1,strike,tmno);
            score(b_man2,top2,nonstrike,tmno);
            break;
        }
        ball=0;
        bowlr=(struct bowl*)malloc(sizeof(struct bowl));
        printf("Enter Bowler : ");
        scanf("%s",bowlr->name);
    }
    
}
int toss(struct teamname*t1,struct teamname*t2)
{
    char tss[20],ch[5];
    printf("\nToss won by %s or %s : ",t1->name,t2->name);
    scanf("%s",tss);
    while(1)
    {
        if(!strcmp(tss,t1->name))
        {
            printf("Elect Bat or Bowl ?   ");
            scanf("%s",ch);
            if(!strcmp(ch,"bat"))
            {
                printf("%s Elected to Bat First\n",t1->name);
            }
            else if(!strcmp(ch,"bowl"))
            {
                printf("%s Elected to Bowl First\n",t1->name);
            }
            return 1;
        }
        else if(!strcmp(tss,t2->name))
        {
            printf("Elect bat or bowl ?   ");
            scanf("%s",ch);
            if(!strcmp(ch,"bat"))
            {
                printf("%s Elected to Bat First\n",t2->name);
            }
            else if(!strcmp(ch,"bowl")){
                printf("%s Elected to Bowl First\n",t2->name);
            }
            return 2;
        }
        else
        {
            printf("please elect correct team \n");
        }
    }
}
void display(struct node*tmp)
{
    printf("------------------------------------------------------------\n");
    printf("NAME\t\tRUNS\tBALLS\t4'S\t6'S\tSTRIKE-RATE\n");
    printf("------------------------------------------------------------\n");
    while(tmp!=NULL)
    {
        printf("%s\t\t",tmp->name);
        printf(" %d\t  %d\t %d\t %d\t ",tmp->runs,tmp->balls,tmp->fours,tmp->sixes);
        printf(" %.2f\n",tmp->s_rate);
        tmp=tmp->next;
    }
}
/*void summary()
{
	struct node *b1=team1, *b2=team2;
	struct bowl  *bl1=tm1, *bl2=tm2;
	int a[4];
	for(int i=0;i<4;i++)
	{
		a[i]=b1->runs;
		b1=b1->next;
	}
	int j,temp;
	for(int i=0;i<4;i++)
	{
		for(j=0;j<4-1;j++)
		{
			if(a[j] < a[j+1])
			{
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
	}
	for(int i=0;i<4;i++)
	{
		printf("%d\n",a[i]);
	}
	while(b1!=NULL && bl2!=NULL)
	{
		printf("\t%s\t%d(%d)\t\t\t\t\t\t%s\t%d/%d\n",b1->name,b1->runs,b1->balls,bl2->name,bl2->wkts,bl2->runs);
		b1=b1->next;
		bl2=bl2->next;
	}
}*/
void displaybl(struct bowl*tmp)
{
    printf("------------------------------------------------------------\n");
    printf("NAME\t\tOVERS\tMAIDEN\tRUNS\tWICKETS\t ECONOMY\n");
    printf("------------------------------------------------------------\n");
    while(tmp!=NULL)
    {
        printf("%s\t\t",tmp->name);
        printf("%d \t%d \t%d \t%d   \t",tmp->overs,tmp->mdn,tmp->runs,tmp->wkts);
        printf("  %.2f\n",tmp->econ);
        tmp=tmp->next;
    }
    printf("============================================\n");
    printf("%s : ",t1);
    printf("%d\n",total);
    printf("============================================\n");
}
void displayt1()
{ 
	struct teamname *cur_node1=t1,*cur_node2=t2;
	while(cur_node1!=NULL && cur_node2!=NULL)
	{
		printf("\t%s\t\t\t\t\t\t\t\t%s\n",cur_node1->name,cur_node2->name);
		cur_node1=cur_node1->next;
		cur_node2=cur_node2->next;
	}
}
void summary()
{
    if(sorted1==NULL)
    {
        sorted1=(struct node*)malloc(sizeof(struct node));
        sorted1->balls=team1->balls;
        sorted1->runs=team1->runs;
        sorted1->s_rate=team1->s_rate;
        sorted1->sixes=team1->sixes;
        sorted1->fours=team1->fours;
        strcpy(sorted1->name,team1->name);
        sorted1->next=NULL;
    }
        struct node*tmp=team1;
        tmp=tmp->next;
        while(tmp!=NULL)
        {
            sort1(sorted1,tmp);
            tmp=tmp->next;
        }
    if(sorted2==NULL)
    {
        sorted2=(struct node*)malloc(sizeof(struct node));
        sorted2->balls=team2->balls;
        sorted2->runs=team2->runs;
        sorted2->s_rate=team2->s_rate;
        sorted2->sixes=team2->sixes;
        sorted2->fours=team2->fours;
        strcpy(sorted2->name,team2->name);
        sorted2->next=NULL;
    }
        tmp=team2;
        tmp=tmp->next;
        while(tmp!=NULL)
        {
            sort1(sorted2,tmp);
            tmp=tmp->next;
        }
    display(sorted1);
    printf("\n");
    display(sorted2);
}
int main()
{
    t1=setname(t1);
    t2=setname(t2);
    int t=toss(t1,t2);
    struct teamname *cur_node1=t1,*cur_node2=t2;
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t\t\t\tPLAYING 11 ( %s vs %s )\n",cur_node1->name,cur_node2->name);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    displayt1();
    if(t==1)
    {
        over(1,1);
        played=-1;
        printf("------------------------------------------------------------\n");
        printf("\t\t1st INNINGS\t\t\n");
        printf("------------------------------------------------------------\n");
        printf("````````````````````````````````````````````````````````````\n");
        printf("\t\t  BATTING\t\t\n");
        printf("------------------------------------------------------------\n");
        display(team1);
        if(tm2!=NULL)
        {
            printf("````````````````````````````````````````````````````````````\n");
            printf("\t\t  BOWLING\t\t\n");
            printf("------------------------------------------------------------\n");
            displaybl(tm2);
        }
        over(2,1);
        printf("------------------------------------------------------------\n");
        printf("\t\t2nd INNINGS\t\t\n");
        printf("------------------------------------------------------------\n");
        printf("````````````````````````````````````````````````````````````\n");
        printf("\t\t  BATTING\t\t\n");
        printf("------------------------------------------------------------\n");
        display(team2);
        if(tm1!=NULL)
        {
            printf("````````````````````````````````````````````````````````````\n");
            printf("\t\t  BOWLING\t\t\n");
            printf("------------------------------------------------------------\n");
            displaybl(tm1);
        }
    }
    else 
    {
        over(2,1);
        played=0;
        printf("------------------------------------------------------------\n");
        printf("\t\t1st INNINGS\t\t\n");
        printf("------------------------------------------------------------\n");
        printf("````````````````````````````````````````````````````````````\n");
        printf("\t\t  BATTING\t\t\n");
        printf("------------------------------------------------------------\n");
        display(team2);
        if(tm1!=NULL)
        {
           printf("````````````````````````````````````````````````````````````\n");
           printf("\t\t  BOWLING\t\t\n");
           printf("------------------------------------------------------------\n");
           displaybl(tm1);
        }
        over(1,1);
        printf("------------------------------------------------------------\n");
        printf("\t\t2nd INNINGS\t\t\n");
        printf("------------------------------------------------------------\n");
        printf("````````````````````````````````````````````````````````````\n");
        printf("\t\t  BATTING\t\t\n");
        printf("------------------------------------------------------------\n");
        display(team1);
        if(tm2!=NULL)
        {
            printf("````````````````````````````````````````````````````````````\n");
            printf("\t\t  BOWLING\t\t\n");
            printf("------------------------------------------------------------\n");
            displaybl(tm2);
        }
    }
    int choice;
    printf("1.TEAM DETAILS\n2.MATCH SUMMARY\n3.EXIT\n");
    while(choice!=3)
    {
        scanf("%d",&choice);
		switch(choice)
		{
			case 1:displayt1();
			break;
			case 2:summary();
		    break;
            case 3:
             exit(0);
		}
    }
    //printf("\n%d total",total);
    /*display(team1);
    if(tm2!=NULL)
    {
    displaybl(tm2);
    }*/
    return 0;
}
