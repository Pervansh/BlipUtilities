#include "BlipConfigReader.h"
#include "Arduino.h"

void blip::print(LinkedList<String> list) {
  String* array = list.toArray();
  for (int i = 0; i < list.size(); ++i) {
    Serial.print(array[i] + ' ');
  }
}

uint16_t intToInt(int n) {
  return (uint16_t)n;
}

BlipConfigReader::BlipConfigReader(uint8_t cardReaderPin, char* fileName, uint16_t hashMapSize)
 : CARD_READER_PIN(cardReaderPin), configName(fileName) {
    map = new SimpleMap<String, LinkedList<String>>([](String& a, String& b) -> int {
        return a.compareTo(b);
    });
}

bool BlipConfigReader::readConfig() {
    LinkedList<String>* list = prepareConfig();
    if (!list) {
        return false;
    }

    map->clear();
    String* arr = list->toArray();
    uint32_t size = list->size();
    String val;
    LinkedList<String> lst;

    for (uint32_t i = 0; i < size; ++i) {
        String str = arr[i];
        bool isReadingValue = true;
        String value = "";
        String lastParam = "";
        LinkedList<String> params;
        for (uint16_t j = 0; j < str.length(); ++j) {
            //Serial.print(str[j]);
            if (isReadingValue) {
                if (str[j] == ' ') {
                    Serial.print(" ");
                    isReadingValue = false;
                } else {
                    Serial.print(str[j]);
                    value += str[j];
                }
            } else {
                if (str[j] == ' ') {
                    Serial.print(" ");
                    params.add(lastParam);
                    lastParam = "";
                } else {
                    Serial.print(str[j]);
                    lastParam += str[j];
                }
            }
        }
        Serial.println();
        blip::print(params);
        Serial.println();
        val = value;
        lst = params;
        if (!value.equals("")) {
            if (!lastParam.equals("")) {
                params.add(lastParam);
            }
        }
        delay(1250);
    }

    Serial.println("LAST :");
    Serial.print(val + ": ");
    blip::print(lst);
    Serial.println();
    map->put(val, lst);
    delete list;
    return true;
}

bool BlipConfigReader::safeConfig() {
    configFile = &SD.open(configName, FILE_WRITE);
    if (*configFile) {
        myFile.println("testing 1, 2, 3.");
        myFile.close();
        Serial.println("done.");
    }
    return *configFile;
}

LinkedList<String>* BlipConfigReader::prepareConfig() {
    LinkedList<String>* list = nullptr;
    if (SD.begin(CARD_READER_PIN)) {
        configFile = &SD.open(configName);
        if (*configFile) {
            list = new LinkedList<String>();
            while (configFile->available()) {
                Serial.println("READING");
                list->add(configFile->readStringUntil('\n'));
                Serial.println("WAS ADDED");
            }
        }
        delete configFile;
    }

    return list;
}

LinkedList<String> BlipConfigReader::getParameters(String valueName) {
    return map->get(valueName);
}

void BlipConfigReader::setParameters(String valueName, LinkedList<String> parameters) {
    map->put(valueName, parameters);
}

void BlipConfigReader::addValue(String valueName, LinkedList<String> params) {
    map->put(valueName, params);
}

BlipConfigReader::~BlipConfigReader() {
    delete map;
}

uint16_t blip::calculateStringHash(String string) {
    uint32_t hash = 0;
    uint32_t p = 1;
    const uint64_t div = pow(2, 16);
    for (int i = 0; i < string.length(); ++i) {
        hash += string[i] * p % div;
        // p %= div;
    }

    return (uint16_t)hash;
}

LinkedList<String> blip::splitString(String string, char splitter) {
    LinkedList<String> list;
    String stringFragment = "";
    uint16_t len = string.length();

    for (uint16_t i = 0; i < len; ++i) {
        if ((string[i] == splitter || i == len - 1) && stringFragment.length() > 0) {
            list.add(stringFragment);
            stringFragment = "";
        } else {
            stringFragment += string[i];
        }
    }

    return list;
}
