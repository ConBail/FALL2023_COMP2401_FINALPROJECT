#include "defs.h"

int main()
{
    // Initialize the random number generator
    srand(time(NULL));

    // Create the house: You may change this, but it's here for demonstration purposes
    // Note: This code will not compile until you have implemented the house functions and structures
    HouseType house;
    initHouse(&house);
    // RoomNodeType *currRoom = house.rooms.head;

    // while (currRoom != NULL)
    // {
    //     printf("Hunters in %s = %d\n", currRoom->data->name, currRoom->data->hunterCount);
    //     currRoom = currRoom->next;
    // }
    pthread_t hunter1, hunter2, hunter3, hunter4, ghost;

    pthread_create(&ghost, NULL, ghostControlFlow, house.ghost);
    pthread_create(&hunter1, NULL, hunterControlFLow, house.allHunters[0]);
    pthread_create(&hunter2, NULL, hunterControlFLow, house.allHunters[1]);
    pthread_create(&hunter3, NULL, hunterControlFLow, house.allHunters[2]);
    pthread_create(&hunter4, NULL, hunterControlFLow, house.allHunters[3]);

    pthread_join(ghost,NULL);
    pthread_join(hunter1,NULL);
    pthread_join(hunter2,NULL);
    pthread_join(hunter3,NULL);
    pthread_join(hunter4,NULL);

    // ghostControlFlow(house.ghost);

    // hunterControlFLow(house.allHunters[0]);

    // hunterControlFLow(house.allHunters[1]);

    // hunterControlFLow(house.allHunters[2]);

    // hunterControlFLow(house.allHunters[3]);

    // RoomNodeType *currRoom = house.rooms.head;

    // while (currRoom != NULL)
    // {
    //     printf("%s has %d hunters in it\n", currRoom->data->name, currRoom->data->hunterCount);
    //     currRoom = currRoom->next;
    // }
    
       


    EvidenceNodeType *currEv = house.collectedEvidence.head;
    char ev_str[MAX_STR];
    while (currEv != NULL)
    {
        evidenceToString(currEv->data, ev_str);
        printf("Hunters found: %s\n", ev_str);
        currEv = currEv->next;
    }
    if (house.collectedEvidence.size>=3)
    {
        printf("HUNTERS WIN!\n");
        ghostToString(house.ghost->ghostType, ev_str);
        printf("The ghost was a %s\n", ev_str);

    }
    else{
        printf("GHOST WINS. HUNTERS FAILED TO IDENTIFY THE GHOST.\n");
        ghostToString(house.ghost->ghostType, ev_str);
        printf("The ghost was a %s\n", ev_str);
    }
    freeHouse(&house);
    
    
    

    //populateRooms(&house);

    //populateHunters(&house);

    //printf("Hunter 1: %s", house.allHunters[0]->name);


    /*BELOW IS FOR TESTING*/



    // for (int i = 0; i < 4; i++)
    // {
    //     printf("RPOV ||| Hunters in van: H%d: %s\n", i,house.rooms.head->data->hunters[i]->name);
    //     printf("HPOV ||| Hunter %d %s is in: %s\n", i,house.allHunters[i]->name, house.allHunters[i]->currRoom->name);
    // }

    // printf("Number of hunters in van: %d", house.rooms.head->data->hunterCount);


    //printf("Ghost is in %s\n", house.ghost->currRoom->name);
    // moveGhost(house.rooms.head->next->data, house.ghost);
    // RoomNodeType *currRoom = house.rooms.head;
    // EvidenceNodeType *currNode;
    // char ev_str[MAX_STR];
    // dropEvidence(house.ghost);
    // dropEvidence(house.ghost);
    // dropEvidence(house.ghost);
    // for (int i = 0; i < 13; i++)
    // {
    //    if (currRoom->data->ghost != NULL)
    //    {
    //     printf("FOUND GHOST IN: %s\n", house.ghost->currRoom->name);
    //    }
    //    currNode = currRoom->data->roomEvidence.head;
    //    if(currNode != NULL){
    //     printf("Evidence found in %s:",currRoom->data->name);
    //     while(currNode != NULL){ 
    //         evidenceToString(currNode->data, ev_str);
    //         printf("%s, ", ev_str);
    //         currNode = currNode->next;
    //    }
    //    printf("\n");
    //    }
    //    currRoom = currRoom->next;
       
       
    // }
    // moveGhost(house.rooms.head->next->next->next->data, house.ghost);

    // printf("After moving ghost\n");

    // dropEvidence(house.ghost);
    // dropEvidence(house.ghost);
    // //printf("Ghost is in %s\n", house.ghost->currRoom->name);
    // currRoom = house.rooms.head;
    // currNode = currRoom->data->roomEvidence.head;

    // for (int i = 0; i < 13; i++)
    // {
    //    if (currRoom->data->ghost != NULL)
    //    {
    //     printf("FOUND GHOST IN: %s\n", house.ghost->currRoom->name);
    //    }
    //    currNode = currRoom->data->roomEvidence.head;
    //    if(currNode != NULL){
    //     printf("Evidence found in %s:",currRoom->data->name);
    //     while(currNode != NULL){ 
    //         evidenceToString(currNode->data, ev_str);
    //         printf("%s, ", ev_str);
    //         currNode = currNode->next;
    //    }
    //    printf("\n");
    //    }
    //    currRoom = currRoom->next;
       
       
    // }


    // printf("First Move\n");

    // moveHunter(house.rooms.head->next->data, house.allHunters[0]);

    // collectEvidence(house.allHunters[0]->currRoom,house.allHunters[0]);

    // currNode = house.rooms.head->next->data->roomEvidence.head;

    // while (currNode != NULL)
    // {
    //     evidenceToString(currNode->data, ev_str);
    //     printf("Evidence here: %s\n", ev_str);
    //     currNode = currNode->next;
    // }
    // if (house.collectedEvidence.head != NULL)
    // {
    //     evidenceToString(house.collectedEvidence.head->data, ev_str);
    //     printf("Evidence collected: %s\n", ev_str);
    // }
    // else{
    //     printf("Couldn't collect any evidence.");
    // }
    
    

    


    

    // for (int i = 0; i < 4; i++)
    // {
    //     printf("RPOV ||| Hunters in van: %s\n",house.rooms.head->data->hunters[i]->name);
    //     printf("RPOV ||| Hunters in hallway: %s\n",house.rooms.head->next->data->hunters[i]->name);
    //     printf("HPOV ||| Hunter %s is in: %s\n",house.allHunters[i]->name, house.allHunters[i]->currRoom->name);
    // }

    // printf("Number of hunters in van: %d\n", house.rooms.head->data->hunterCount);
    // printf("Number of hunters in hallway: %d\n", house.rooms.head->next->data->hunterCount);
    

    // printf("Second Move\n");

    // moveHunter(house.rooms.head->next->data, house.allHunters[3]);

    // for (int i = 0; i < 4; i++)
    // {
    //     if (house.rooms.head->data->hunters[i] != NULL)
    //     {
    //         printf("RPOV ||| Hunters in van: %s\n",house.rooms.head->data->hunters[i]->name);//Segfault happening in this area, accessing null values
    //     }
    //     if (house.rooms.head->next->data->hunters[i] != NULL)
    //     {
    //         printf("RPOV ||| Hunters in hallway: %s\n",house.rooms.head->next->data->hunters[i]->name);
    //     }
        
        
        
        
    //     printf("HPOV ||| Hunter %s is in: %s\n",house.allHunters[i]->name, house.allHunters[i]->currRoom->name);
    // }

    // printf("Number of hunters in van: %d\n", house.rooms.head->data->hunterCount);
    // printf("Number of hunters in hallway: %d\n", house.rooms.head->next->data->hunterCount);

    return 0;
}