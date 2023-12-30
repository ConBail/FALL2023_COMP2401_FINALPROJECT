#include "defs.h"


int collectEvidence(RoomType *room, HunterType *hunter){
    //printf("Entered collect evidence\n");
    //sem_wait(&(room->mutex));
    if (room->roomEvidence.head == NULL)
    {
        //printf("No evidence worked\n");
        //sem_post(&(room->mutex));
        return C_FALSE;
    }
    else{

        if (room->roomEvidence.head->data == hunter->collectableEvidence)
        {
            EvidenceNodeType *temp = room->roomEvidence.head;

            //sem_wait((&room->roomEvidence.mutex));
            room->roomEvidence.head = room->roomEvidence.head->next;
            //sem_post((&room->roomEvidence.mutex));
            //printf("got to before adding head to house evidence list\n");

            //sem_wait(&(hunter->collectedEvidence->mutex));
            addToHouseEvidenceList(temp->data, hunter);//unsafe
            //sem_post(&(hunter->collectedEvidence->mutex));

            //printf("after adding head to house evidence list\n");

            free(temp);
            //printf("after free temp\n");
            //sem_post(&(room->mutex));
            return C_TRUE;
        
        }
        

        EvidenceNodeType *currNode = room->roomEvidence.head;
        EvidenceNodeType *prevNode = NULL;
        while (currNode != NULL && currNode->data != hunter->collectableEvidence)
        {
            
            prevNode = currNode;
            currNode = currNode->next;
            
        }
        //printf("got through the while l\n");

        if (currNode != NULL)
        {
            prevNode->next = currNode->next;

            //printf("before adding found node to house evidence list\n");

            addToHouseEvidenceList(currNode->data, hunter);//Potential segfault here
            //printf("after adding found node to house evidence list\n");
            free(currNode);
        }
        //sem_post(&(room->mutex));
        return C_TRUE;
    }
    


}
HunterType* createHunter(char *name, int i, HouseType *house){

    HunterType *newHunter = malloc(sizeof(HunterType));

    strcpy(newHunter->name, name);

    newHunter->boredom = 0;

    newHunter->fear = 0;

    newHunter->collectableEvidence = i;

    newHunter->collectedEvidence = &(house->collectedEvidence);

    newHunter->currRoom = house->rooms.head->data;

    house->rooms.head->data->hunters[house->rooms.head->data->hunterCount] = newHunter;

    house->rooms.head->data->hunterCount++;

    //moveHunter(house->rooms.head->data, newHunter);

    //newHunter->currRoom = house->rooms.head->data;

    return newHunter;

}
void populateHunters(HouseType *house){


    for (int i = 0; i<NUM_HUNTERS; i++){


        char name[MAX_STR];
        printf("Please enter a name for a hunter: ");
        fgets(name, MAX_STR, stdin);
        name[strlen(name)-1] = 0;
        HunterType *newHunter = createHunter(name, i, house);

        l_hunterInit(newHunter->name, newHunter->collectableEvidence);
        house->allHunters[i] = newHunter;
    }



}
void moveHunter(RoomType *room, HunterType *hunter){//Likely need mutex implementation in this function

    //Likely issues with this function causing segfaults
    RoomType *temp = hunter->currRoom;

    sem_wait(&(temp->mutex));
    removeHunterFromRoom(hunter);
    sem_post(&(temp->mutex));
    
    

    hunter->currRoom = room;
    sem_wait(&(room->mutex));
    for (int i = 0; i < NUM_HUNTERS; i++)
    {
        if (room->hunters[i] == NULL)
        {
            room->hunters[i] = hunter;
            //printf("%s huntercount ++: now = %d\n", room->name, room->hunterCount);
            room->hunterCount++;
            break;
        }
        
    }
    sem_post(&(room->mutex));
    

    //room->hunters[room->hunterCount] = hunter;//add hunter to first null location, using huntercount will not work

    



}
void removeHunterFromRoom(HunterType *hunter){


    for (int i = 0; i < NUM_HUNTERS; i++)
    {
        if(hunter->currRoom->hunters[i] == NULL){
            continue;
        }
        if (&(*hunter) == &(*(hunter->currRoom->hunters[i])))
        {
            
            hunter->currRoom->hunters[i] = NULL;
            //printf("%s huntercount --: now = %d\n", hunter->currRoom->name, hunter->currRoom->hunterCount);
            hunter->currRoom->hunterCount--;
            hunter->currRoom = NULL;//This could cause possible segfaults
            break;
        }
        
    }


}
int reviewEvidence(EvidenceListType *collectedEv){
    

    if (collectedEv->size>=3)
    {
        return C_TRUE;
    }
    return C_FALSE;
    


}
void freeHunters(HouseType *house){

for (int i = 0; i < NUM_HUNTERS; i++)
    {
        free(house->allHunters[i]);
    }

}