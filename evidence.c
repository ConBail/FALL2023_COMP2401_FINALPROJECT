#include "defs.h"


void initEvidenceList(EvidenceListType* list){

    list->head = NULL;
    list->tail = NULL;

    list->size = 0;

}

EvidenceEnumType dropEvidence(GhostType *ghost)//Gonna implement mutex stuff here most likely
{
    EvidenceEnumType evType;

    if (ghost->ghostType == POLTERGEIST)
    {
        evType = (EvidenceEnumType)randomGhost();
        while (evType == SOUND)
        {
            evType = (EvidenceEnumType)randomGhost();
        }
        addToRoomEvidenceList(evType, ghost->currRoom);
    }
    
    if (ghost->ghostType == BANSHEE)
    {
        evType = (EvidenceEnumType)randomGhost();
        while (evType == FINGERPRINTS)
        {
            evType = (EvidenceEnumType)randomGhost();
        }
        addToRoomEvidenceList(evType, ghost->currRoom);
    }

    if (ghost->ghostType == BULLIES)
    {
        evType = (EvidenceEnumType)randomGhost();
        while (evType == TEMPERATURE)
        {
            evType = (EvidenceEnumType)randomGhost();
        }
        addToRoomEvidenceList(evType, ghost->currRoom);
    }

    if (ghost->ghostType == PHANTOM)
    {
        evType = (EvidenceEnumType)randomGhost();
        while (evType == EMF)
        {
            evType = (EvidenceEnumType)randomGhost();
        }
        addToRoomEvidenceList(evType, ghost->currRoom);
    }
    return evType;
}

void addToRoomEvidenceList(EvidenceEnumType ev, RoomType *room){


    EvidenceNodeType *newNode1;
    initEvNode(&newNode1, ev);

    if(room->roomEvidence.head == NULL){
        room->roomEvidence.head = newNode1;
        room->roomEvidence.tail = newNode1;
    }
    else{
        room->roomEvidence.tail->next = newNode1;
        room->roomEvidence.tail = newNode1;
    }
}

void addToHouseEvidenceList(EvidenceEnumType ev, HunterType *hunter){

    //sem_wait(&(hunter->collectedEvidence->mutex));
    EvidenceNodeType *currNode = hunter->collectedEvidence->head;

    while (currNode != NULL)
    {
        if (currNode->data == ev)
        {
            //sem_post(&(hunter->collectedEvidence->mutex));
            return;
        }
        currNode = currNode->next;
        
    }

    EvidenceNodeType *newNode1;
    initEvNode(&newNode1, ev);

    if(hunter->collectedEvidence->head == NULL){
        hunter->collectedEvidence->head = newNode1;
        hunter->collectedEvidence->tail = newNode1;
        
    }
    else{
        hunter->collectedEvidence->tail->next = newNode1;
        hunter->collectedEvidence->tail = newNode1;
    }
    hunter->collectedEvidence->size++;
    //sem_post(&(hunter->collectedEvidence->mutex));
}
void freeEvidenceList(EvidenceListType *evList){

    EvidenceNodeType *currNode = evList->head;
    EvidenceNodeType *temp;

    while (currNode != NULL)
    {
        temp = currNode;
        currNode = currNode->next;
        free(temp);
        
    }
}