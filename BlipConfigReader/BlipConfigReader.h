#pragma once

#include "Arduino.h"
#include <SD.h>
#include <SPI.h>
#include <Vector.h>
#include <SimpleMap.h>
#include <LinkedList.h>
#include <inttypes.h>

class String;
class File;

namespace blip {
    void print(LinkedList<String> list);
    uint16_t calculateStringHash(String string);
    LinkedList<String> splitString(String string, char splitter);
}

class BlipConfigReader {
private:
    File* configFile;
    SimpleMap<String, LinkedList<String>>* map;
    LinkedList<String>* prepareConfig();
protected:
    void addValue(String valueName, LinkedList<String> params);
public:
    const char* configName;
    const uint8_t CARD_READER_PIN;

    BlipConfigReader(uint8_t cardReaderPin, char* fileName = "config.txt", bool changeable = false, uint16_t hashMapSize = 20);

    bool readConfig();

    bool safeConfig();
    
    LinkedList<String> getParameters(String valueName);

    void setParameters(String valueName, LinkedList<String> parameters);
    
    ~BlipConfigReader();
};
