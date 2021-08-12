#include "UncertainTuple.h"

void blip::UncertainTuple::addValues(unsigned int current) {}

void blip::UncertainTuple::getValues(unsigned int current) {}

blip::UncertainTuple::~UncertainTuple() {
    for (unsigned int i = 0; i < VALUE_COUNT; ++i) {
        delete adapters[i];
    }
    delete adapters;
}
