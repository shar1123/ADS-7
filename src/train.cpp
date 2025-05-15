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
  Car* current = first;
  current->light = true;
  countOp++;
  while (true) {
    Car* temp = current;
    int steps = 1;
    while (!temp->light) {
      temp = temp->next;
      steps++;
      countOp++;
    }
    temp->light = false;
    countOp++;
    for (int i = 0; i < steps; ++i) {
      temp = temp->prev;
      countOp++;
    }
    if (temp == current) {
      return steps;
    }
    current = current->next;
    countOp++;
  }
}
int Train::getOpCount() {
  return countOp;
}
