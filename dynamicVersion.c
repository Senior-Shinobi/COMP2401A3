#include <stdio.h>
#include <stdlib.h>

#define MAX_FISH 10

//fish struct
typedef struct Fish
{
unsigned char size;
char * species;

}Fish;

//fisherman struct
typedef struct Fisher
{

char * name;
unsigned char keepSize;
Fish bucket[MAX_FISH];
unsigned char numFish;

}Fisher;

//Pond struct
typedef struct Pond
{

Fish fish[15];
unsigned char numFish;

}Pond;

//adds fish to the pond
int addFish(Pond *p, unsigned char size, char *species){

if (p->numFish == 15){
	return 0;
}

p->fish[p->numFish].size=size;
p->fish[p->numFish].species=species;
p->numFish++;

return 1;
}
//lists all fish in the pond
void listFish(Fish *arrayOfFish, int n){

for (int i = 0; i < n;i++){
	printf("%d cm  %s\n",arrayOfFish[i].size,arrayOfFish[i].species);
}

}
//returns 0 if fisher likes the fish and 1 otherwise
char likes(Fisher *fisher, Fish *f){

if ((f->species!="Sunfish")&&(fisher->keepSize <= f->size)){
	return 1 ;
}
return 0;
}
//adds the fish to the bucket if there is room for it
int keep(Fisher *fisher, Fish *f){


	if(fisher->numFish<10){
    fisher->bucket[fisher->numFish]=*f;
    fisher->numFish++;
    return 1;
  }
  return 0;

}
//picks a random fish and runs likes and keep to see if the fisher adds them to the bucket
int castLine(Fisher *fisher,Pond *p){

if (p->numFish == 0){
	return 0;
}
int r = rand()%p->numFish;
printf("%d\n",r);
Fish *f = p->fish+r;
  if(likes(fisher,f)==1&&fisher->numFish<MAX_FISH){
    keep(fisher,f);
    p->fish[r] = p->fish[p->numFish];
		
    p->numFish--;
  }

return 1;
}
//gives fisher1 bucket to fisher2 with any extras returning to pond as well as if they are not big enough
void giveAwayFish(Fisher *fisher1, Fisher *fisher2, Pond *p){


for (int i = 0; i < fisher1->numFish;i++){
	if ((fisher1->numFish)+(fisher2->numFish) <= MAX_FISH){
		if (likes(fisher2,&fisher1->bucket[i]) > 0){
			int k = keep(fisher2, &fisher1->bucket[i]);
			if (k == 1){ 
				fisher2->bucket[fisher2->numFish+1] = fisher1->bucket[i];
				fisher1->numFish--;
				fisher2->numFish++;

			} else {
				addFish(p,fisher1->bucket[i].size,fisher1->bucket[i].species);
			}
		} else{
			addFish(p,fisher1->bucket[i].size,fisher1->bucket[i].species);
		}
	} else {
		addFish(p,fisher1->bucket[i].size,fisher1->bucket[i].species);
	} 
}

}



int main() {
//creates fishers
Fisher Fred = {.name = "Fred",.keepSize = 15};
Fisher Suzy = {.name = "Suzy",.keepSize = 10};
//makes pond
Pond p = {.numFish = 0};
//adds fish
addFish(&p,4,"Sunfish");
addFish(&p,25,"Pike");
addFish(&p,30,"Bass");
addFish(&p,30,"Perch");
addFish(&p,14,"Sunfish");
addFish(&p,15,"Pike");
addFish(&p,9,"Pike");
addFish(&p,12,"Bass");
addFish(&p,5,"Sunfish");
addFish(&p,12,"Sunfish");
addFish(&p,10,"Bass");
addFish(&p,2,"Bass");
addFish(&p,16,"Perch");
addFish(&p,30,"Sunfish");
addFish(&p,7,"Perch");

listFish(p.fish,15);

printf("\n\n");
int k;

for (int i = 0; i <10;i++){
	k = castLine(&Fred,&p);
}
listFish(Fred.bucket,10);
printf("\n\n");
for (int i = 0; i <10;i++){
	k = castLine(&Suzy,&p);
}
listFish(Suzy.bucket,10);
printf("\n\n");
listFish(p.fish,p.numFish);
giveAwayFish(&Suzy,&Fred,&p);
printf("\n\n");
listFish(Fred.bucket,10);
printf("\n\n");
listFish(Suzy.bucket,10);
printf("\n\n");
listFish(p.fish,p.numFish);
}





