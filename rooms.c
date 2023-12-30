#include "defs.h"


void initRoomsList(RoomListType *list){

    list->head = NULL;
    list->tail = NULL;

}
RoomType* createRoom(char roomName[]){

    RoomType *room = malloc(sizeof(RoomType));

    strcpy(room->name, roomName);

    room->ghost = NULL;

    initEvidenceList(&(room->roomEvidence));

    initRoomsList(&(room->connectedRooms));

    sem_init(&(room->mutex), 0, 1);

    room->hunterCount = 0;

    room->connectedRoomsSize = 0;

    for (int i = 0; i < NUM_HUNTERS; i++)
    {
        room->hunters[i] = NULL;
    }
    

    return room;

}

void connectRooms(RoomType *room1, RoomType *room2){

    RoomNodeType *newNode1;
    RoomNodeType *newNode2;

    initRLNode(&newNode1, room1);
    initRLNode(&newNode2, room2);

    if(room1->connectedRooms.head == NULL){
        room1->connectedRooms.head = newNode2;
        room1->connectedRooms.tail = newNode2;
    }
    else{
        room1->connectedRooms.tail->next = newNode2;
        room1->connectedRooms.tail = newNode2;
    }

    if(room2->connectedRooms.head == NULL){
        room2->connectedRooms.head = newNode1;
        room2->connectedRooms.tail = newNode1;
    }
    else{
        room2->connectedRooms.tail->next = newNode1;
        room2->connectedRooms.tail = newNode1;
    }
    room1->connectedRoomsSize++;
    room2->connectedRoomsSize++;
}

RoomType* getConnectedRooms(RoomType *room){
    int roomNum = randInt(0, room->connectedRoomsSize);
    RoomNodeType *currRoom = room->connectedRooms.head;
    
    for (int i = 0; i < roomNum; i++)
    {
        currRoom = currRoom->next;
    }
    return currRoom->data;
}
void freeConnectedRooms(RoomType *room){

    RoomNodeType *currNode = room->connectedRooms.head;
    RoomNodeType *temp;

    while (currNode != NULL)
    {
        temp = currNode;
        currNode = currNode->next;
        free(temp);
        
    }
    


}
void freeRoomListData(RoomListType *list){

    RoomNodeType *currNode = list->head;
    

    while (currNode != NULL)
    {
            freeConnectedRooms(currNode->data);
            freeEvidenceList(&(currNode->data->roomEvidence));
            currNode = currNode->next;
    }


}
void freeRoomList(RoomListType *list){

    RoomNodeType *currNode = list->head;
    RoomNodeType *temp;
    
    while (currNode != NULL)
    {
        temp = currNode;
        currNode = currNode->next;
        free(temp->data);
        free(temp);
    }



}
    