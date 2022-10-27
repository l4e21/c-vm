#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "label.h"

Label create_label(int progPtr, char* name) {
  Label lbl;
  
  lbl.progPtr = progPtr;
  lbl.name = strdup(name);

  return lbl;
}

void destroy_label(Label label) {
  /* free(label); */
}

void append_label(LbList* list, Label label) {
  if (list->ptr >= list->size) {
    list->size += list->size + 1;
    list->data = (Label*) realloc(list->data, sizeof(Label) * list->size);
  }
  
  list->data[list->ptr++] = label;
  return;
}

Label get_label(LbList* list, int index) {
  return list->data[index];
}

int find_label_by_name(LbList* list, char* name) {
  int i;

  for (i=0; i<list->ptr; i++) {
    Label lbl = list->data[i];
    if (strcmp(lbl.name, name) == 0) {
      return i;
    }
  };
  return -1;
}

void destroy_labels(LbList* list) {
  for (int i=0; i<list->ptr;i++) {
    free(list->data[i].name);
  }

  free(list->data);
  list->size = 0;
  list->ptr = 0;
}
