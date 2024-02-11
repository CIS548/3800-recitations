#ifndef INSPECT_H
#define INSPECT_H

struct Message {
  int id;
  char text[50];
};

void read_msg(int id, struct Message* msg);
void inspect_example();

#endif
