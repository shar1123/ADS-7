// Copyright 2021 NNTU-CS
#include <cstdlib>
#include "train.h"

Train::Train(): first(nullptr), countOp(0) {}
Train::~Train() {
  if (!first)
    return;
  Car* current = first->next;
  while (current != first) {
    Car* next = current->next;
    delete current;
    current = next;
  }
  delete first;
}
void Train::addCar(bool light) {
  Car* newCar = new Car(light);
  if (!first) {
    first = newCar;
    first->next = first->prev = first;
  } else {
    Car* last = first->prev;
    last->next = newCar;
    newCar->prev = last;
    newCar->next = first;
    first->prev = newCar;
  }
}
int Train::getLength() {
  if (!first)
    return 0;
  int n = 1;
  Car* current = first->next;
  while (current != first) {
    current = current->next;
    ++n;
  }
  bool original = first->light;
  countOp = 0;
  int i = 0;
  while (true) {
    ++i;
    first->light = !first->light;
    const Car* p = first;
    for (int j = 0; j < n; ++j) {
      p = p->next;
      ++countOp;
    }
    if (!original && i == 2)
      break;
    if (original && i == n + 1)
      break;
  }
  first->light = original;
  return n;
}
int Train::getOpCount() {
  return countOp;
}
