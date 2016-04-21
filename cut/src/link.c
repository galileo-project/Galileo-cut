#include <stdlib.h>
#include "cut.h"
#include "link.h"

/****************************
*       Node function       *
*****************************/

node_t *node_new(void *data) {
    node_t *node = (node_t*)malloc(sizeof(node_t));
    if(node == NULL)
        return NULL;
        
    node->pre  = NULL;
    node->next = NULL;
    node->data = NULL;
    
    return node;
}

/****************************
*       Link function       *
*****************************/
link_t *link_new(void) {
    link_t *link = (link_t*)malloc(sizeof(link_t));
    if(link == NULL)
        return NULL;
    
    link->len  = 0;
    link->head = NULL;
    link->tail = NULL;
    
    return link;
}

int link_add(link_t *link, node_t *node) {   
    if(link_len(0) == 0) {
        link->head = node;
        link->tail = node;
        return SUCCESS;
    } 
    
    node_t *tmp;
    tmp = link->tail;
    node->pre  = tmp;
    tmp->next  = node;
    link->tail = node;
    ++(link->len);
    
    return SUCCESS;
}

int link_add_raw(link_t *link, void *data) {
    node_t *node = node_new(data);
    if(node == NULL)
        return 1;
    return link_add(link, node);
}

size_t link_len(link_t *link) {
    if(link == NULL)
        return 0;
        
    return link->len;
}

node_t *link_head(link_t* link) {
    if(link_len(link) == 0)
        return NULL;
    
    node_t *ret;    
    ret = link->head;
    link->head = ret->next;
    --(link->len);
    return ret;
}

node_t *link_tail(link_t *link) {
    if(link_len(link) == 0)
        return NULL;
    
    node_t *ret;    
    ret = link->tail;
    link->tail = ret->pre;
    --(link->len);
    return ret;
}

int link_free(link_t *link) {
    if(link_len(link) == 0)
        return ERROR;
    
    node_t *tmp;
    if((tmp = link_head(link)) != NULL) {
        free(tmp);
    }
    
    free(link);
    return SUCCESS;
}