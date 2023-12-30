#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define MAX_STR         64
#define MAX_RUNS        50
#define BOREDOM_MAX     100
#define C_TRUE          1
#define C_FALSE         0
#define HUNTER_WAIT     5000
#define GHOST_WAIT      600
#define NUM_HUNTERS     4
#define FEAR_MAX        10
#define LOGGING         C_TRUE

//typedef enum EvidenceType EvidenceType;
typedef enum GhostClass GhostClass;

typedef enum EvidenceType { EMF, TEMPERATURE, FINGERPRINTS, SOUND, EV_COUNT, EV_UNKNOWN } EvidenceEnumType;
enum GhostClass { POLTERGEIST, BANSHEE, BULLIES, PHANTOM, GHOST_COUNT, GH_UNKNOWN };
enum LoggerDetails { LOG_FEAR, LOG_BORED, LOG_EVIDENCE, LOG_SUFFICIENT, LOG_INSUFFICIENT, LOG_UNKNOWN };

// Helper Utilies
int randInt(int,int);        // Pseudo-random number generator function
float randFloat(float, float);  // Pseudo-random float generator function
enum GhostClass randomGhost();  // Return a randomly selected a ghost type
void ghostToString(enum GhostClass, char*); // Convert a ghost type to a string, stored in output paremeter
void evidenceToString(enum EvidenceType, char*); // Convert an evidence type to a string, stored in output parameter

// Logging Utilities
void l_hunterInit(char* name, enum EvidenceType equipment);
void l_hunterMove(char* name, char* room);
void l_hunterReview(char* name, enum LoggerDetails reviewResult);
void l_hunterCollect(char* name, enum EvidenceType evidence, char* room);
void l_hunterExit(char* name, enum LoggerDetails reason);
void l_ghostInit(enum GhostClass type, char* room);
void l_ghostMove(char* room);
void l_ghostEvidence(enum EvidenceType evidence, char* room);
void l_ghostExit(enum LoggerDetails reason);





typedef struct RoomList RoomListType;

typedef struct Room RoomType;

typedef struct RoomNode RoomNodeType;

typedef struct EvidenceNode EvidenceNodeType;

typedef struct EvidenceList EvidenceListType;

typedef struct Hunter HunterType;

typedef struct Ghost GhostType;

typedef struct House HouseType;



struct RoomList {

    RoomNodeType *head;
    RoomNodeType *tail;


};

struct EvidenceList {

    EvidenceNodeType *head;
    EvidenceNodeType *tail;

    int size;

    sem_t mutex;

};
struct RoomNode{

    RoomType *data;
    RoomNodeType *next;

};
struct EvidenceNode{

    EvidenceEnumType data;
    EvidenceNodeType *next;

};


struct Room {

    char name[MAX_STR];

    struct RoomList connectedRooms;

    int connectedRoomsSize;

    struct EvidenceList roomEvidence;

    HunterType *hunters[NUM_HUNTERS];

    int hunterCount;

    GhostType *ghost;

    sem_t mutex;
};

struct House {

    HunterType *allHunters[NUM_HUNTERS];

    GhostType *ghost;

    struct RoomList rooms;

    struct EvidenceList collectedEvidence;

};

struct Hunter{

    char name[MAX_STR];

    int fear;

    int boredom;

    RoomType *currRoom;

    EvidenceEnumType collectableEvidence;

    EvidenceListType *collectedEvidence;

};

struct Ghost{

    GhostClass ghostType;

    RoomType *currRoom;

    int boredom;


};



/* 
  Function: Initialize House Struct
  Purpose:  This function initializes a house struct. Will initialize the rooms list,
            hunters, and ghost.
  Params:  
    Input/Output: HouseType* - a pointer to the house struct that will be initialized. 
*/
void initHouse(HouseType*);

/* 
  Function: Initialize rooms list
  Purpose:  This function initializes a rooms list by setting it's head and tail pointers
            to NULL.
  Params:  
    Output: RoomListType* - A pointer to a RoomListType structure
*/
void initRoomsList(RoomListType*);


/* 
  Function: Initialize Evidence list
  Purpose:  This function initializes an EvidenceListType struct's head and tail pointers to NULL
  Params:  
    Output: EvidenceListType* - a pointer to the EvidenceListType struct that will be initialized. 
*/
void initEvidenceList(EvidenceListType*);


/* 
  Function: Create room struct
  Purpose:  This function creates a new room structure with the name passed into the function.
            This function is essentially initializing a room struct but returning a pointer to that struct.
  Params:  
    Input: char[] - The name of the room

  Return: After initializing a room struct a pointer to the room is returned
*/
RoomType* createRoom(char[]);


/* 
  Function: Connect Rooms
  Purpose:  This function will connect two rooms together. This is done by adding each room to each others connected room list.
            The connected rooms list of each room contains a list of pointers to room that are connected to each other
  Params:  
    Input/Output: RoomType* - Both RoomType*, pointers to rooms, are read and modified. They will be connected to each other
                            by adding each to each others list of connected rooms. 
*/
void connectRooms(RoomType*, RoomType*);


/* 
  Function: Initialize Room List Node
  Purpose:  This function initializes a node to be used in a room list
  Params:  
    Output: RoomNodeType **node - A double pointer to a room node. The node's data
                                member will point to the room data passed in, and it's next member will be set to NULL.
    Input:  RoomType *data - A pointer to a RoomType. This will be the data of a room node.
*/
void initRLNode(RoomNodeType **node, RoomType *data);

/* 
  Function: Add Room
  Purpose:  This function adds a RoomType to a roomlist. Makes use of helper functions in order
            to create a new room node with *room as the data. Adds this node to the end of the roomList
            linked list. If roomList is empty, the node is added as the head and tail.
  Params:  
    Input/Output:  RoomListType *roomList - the roomList that will be modified
    Input:         RoomType *room - the room that will be added to the roomList
*/
void addRoom(RoomListType *roomList, RoomType *room);

/* 
  Function: Populate rooms
  Purpose:  This function calls create room, for each room in the house, and calls connect
            room for every pair of rooms that must be connected. It also calls add room which 
            adds each room to the roomlist stored by house.
  Params:  
    Output: HouseType *house - a pointer to the house struct that the created rooms will be a part of. 
*/
void populateRooms(HouseType *house);


void populateHunters(HouseType *house);

void moveHunter(RoomType *room, HunterType *hunter);

void initGhost(HouseType *house);

void moveGhost(RoomType *room, GhostType *ghost);

void initEvNode(EvidenceNodeType **node, EvidenceEnumType data);

EvidenceEnumType dropEvidence(GhostType *ghost);

void addToRoomEvidenceList(EvidenceEnumType ev, RoomType *room);

int collectEvidence(RoomType *room, HunterType *hunter);

void addToHouseEvidenceList(EvidenceEnumType ev, HunterType *hunter);

RoomType* getConnectedRooms(RoomType *room);

int reviewEvidence(EvidenceListType *collectedEv);

void* hunterControlFLow(void*);

void* ghostControlFlow(void*);

void removeHunterFromRoom(HunterType *hunter);

void freeConnectedRooms(RoomType *room);

void freeEvidenceList(EvidenceListType *evList);

void freeHouse(HouseType *house);

void freeRoomListData(RoomListType *list);

void freeRoomList(RoomListType *list);

void freeHunters(HouseType *house);

HunterType* createHunter(char *name, int i, HouseType *house);


