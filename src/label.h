#ifndef LABEL_H
#define LABEL_H

struct __Label {
  int progPtr;
  char* name;
};

typedef struct __Label Label;

Label create_label(int progPtr, char* name);
void destroy_label(Label label);

struct __LBLIST {
  Label* data;
  int ptr;
  int size;
};

typedef struct __LBLIST LbList;

void append_label(LbList* list, Label label);
Label get_label(LbList* list, int index);
int find_label_by_name(LbList* list, char* name);
void destroy_labels(LbList* list);

#endif
