#ifndef CUT_LINK_H_
#define CUT_LINK_H_

typedef struct node_s {
    struct node_s *pre;
    struct node_s *next;
    void          *data;
} node_t;

node_t *node_new(void*);

typedef struct link_s {
    size_t  len;
    node_t  *head;
    node_t  *tail;
} link_t;

link_t  *link_new(void);
size_t  link_len(link_t*);
int    link_add(link_t*, node_t*);
int    link_add_raw(link_t*, void*);
node_t  *link_head(link_t*);
node_t  *link_tail(link_t*);
int     link_free(link_t*);

#endif //CUT_LINK_H_