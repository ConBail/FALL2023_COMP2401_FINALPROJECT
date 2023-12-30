#include "defs.h"



void initGhost(HouseType *house){//Segfault happening in here


    GhostType *newGhost = malloc(sizeof(GhostType));
    //printf("dynamically allocated\n");



    newGhost->boredom = 0;

    newGhost->ghostType = randomGhost();
    //printf("got random ghost\n");

    int roomChoice = randInt(1, 13);
    //printf("got random number for room\n");

    house->ghost = newGhost;
    //printf("set the house ghost pointer\n");

    RoomNodeType *currRoom = house->rooms.head;
    //printf("got the head of rooms\n");

    for (int i = 0; i < roomChoice; i++)
    {
        currRoom = currRoom->next;
        
    }
    //printf("found random room in for loop, random num was %d\n",roomChoice);
    //printf("The ghost will start in %s\n",currRoom->data->name);
    newGhost->currRoom = currRoom->data;
    //printf("set ghosts currRoom\n");

    currRoom->data->ghost = newGhost;
    //printf("set curr rooms ghost pointer\n");

    l_ghostInit(newGhost->ghostType, newGhost->currRoom->name);
}
void moveGhost(RoomType *room, GhostType *ghost){//Likely need mutex implementation in this function

    ghost->currRoom->ghost = NULL;

    ghost->currRoom = room;

    room->ghost = ghost;




}