#include "defs.h"

void initRLNode(RoomNodeType **node, RoomType *data){
    *node = malloc(sizeof(RoomNodeType));
        (*node)->data = data;
        (*node)->next = NULL;
}
void initEvNode(EvidenceNodeType **node, EvidenceEnumType data){
    *node = malloc(sizeof(EvidenceNodeType));
        (*node)->data = data;
        (*node)->next = NULL;
}