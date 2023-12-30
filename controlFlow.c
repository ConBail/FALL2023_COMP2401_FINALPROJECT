#include "defs.h"

void* hunterControlFLow(void* arg){
    HunterType *hunter = (HunterType*) arg;
    while (C_TRUE)
    {
        if(hunter->boredom == BOREDOM_MAX){
            //pthread_exit(NULL);
            l_hunterExit(hunter->name, LOG_BORED);

            //EvidenceNodeType *currEv = hunter->collectedEvidence->head;
            //char ev_str[MAX_STR];
            // while (currEv != NULL)
            // {
            //     evidenceToString(currEv->data,ev_str);
            //     printf("Hunter collected %s\n", ev_str);
            //     currEv = currEv->next;
            // }
            

            removeHunterFromRoom(hunter);
            //Clear pointers when a hunter exits


            return NULL;
            
        }
        if(hunter->fear == FEAR_MAX){
            //pthread_exit(NULL);
            l_hunterExit(hunter->name, LOG_FEAR);

            removeHunterFromRoom(hunter);
            //Clear pointers when a hunter exits



            return NULL;
        }
        
        if(hunter->currRoom->ghost != NULL){
            hunter->fear++;
            hunter->boredom = 0;
        }
        else{
            hunter->boredom++;
        }
        int whichAction = randInt(0,3);
        if(whichAction == 0){
            //printf("BEFORE MOVE\n");
            moveHunter(getConnectedRooms(hunter->currRoom), hunter);
            //printf("MOVED\n");
            l_hunterMove(hunter->name, hunter->currRoom->name);
        }
        if(whichAction == 1){
            //printf("BEFORE COLLECTING EVIDENCE\n");
            if(C_TRUE == collectEvidence(hunter->currRoom, hunter)){
                l_hunterCollect(hunter->name, hunter->collectableEvidence, hunter->currRoom->name);
            }
        }
        if(whichAction == 2){
            //printf("BEFORE REVIEWING\n");
            if(C_TRUE == reviewEvidence(hunter->collectedEvidence)){
                //pthread_exit(NULL);
                l_hunterReview(hunter->name, LOG_SUFFICIENT);
                l_hunterExit(hunter->name, LOG_EVIDENCE);

                removeHunterFromRoom(hunter);
                //Clear pointers when a hunter leaves


                return NULL;
            }
            else{
                l_hunterReview(hunter->name, LOG_INSUFFICIENT);
            }
        }

    }
    

}

void* ghostControlFlow(void* arg){
    GhostType *ghost = (GhostType*) arg;
    while(C_TRUE){
        //printf("BOREDOM == %d\n", ghost->boredom);
        if(ghost->boredom == BOREDOM_MAX){
            //pthread_exit(NULL);
            l_ghostExit(LOG_BORED);
            ghost->currRoom->ghost = NULL;
            return NULL;
        }
        if(ghost->currRoom->hunterCount != 0){
            ghost->boredom =0;
        }
        else{
            ghost->boredom++;
        }
        int whichAction = randInt(0,3);
        if(whichAction == 0){
            RoomType *ghostToRoom = getConnectedRooms(ghost->currRoom);
            //printf("Hunters in %s is %d\n", ghostToRoom->name, ghostToRoom->hunterCount);
            if(ghostToRoom->hunterCount==0){
                moveGhost(ghostToRoom,ghost);
                //printf("moving rooms\n");
                l_ghostMove(ghost->currRoom->name);
            }
            else{
                whichAction = randInt(1,3);
            }
        }
        if(whichAction == 1){
            printf("dropping evidence");
           l_ghostEvidence(dropEvidence(ghost), ghost->currRoom->name);

        }
        if(whichAction ==2){
            continue;
        }
    }
}