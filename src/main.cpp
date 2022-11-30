#include <Arduino.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>
#include "eyeSprites.h"

// Hardware SPI:
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 8

// Create a new instance of the MD_MAX72XX class:
MD_Parola matrix = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
eyeDir_t eyeDirection = eyeCenter;

void eyes_open(uint16_t speed);
void eyes_close(uint16_t speed);
eyeDir_t eyes_look(uint16_t speed, eyeDir_t start, eyeDir_t end);
void eyes_blink(uint16_t speed);
void eyes_wink(uint16_t speed, bool leftEye);
void eyes_roll(uint16_t speed);

void setup() {
    // Initialize the object:
    matrix.begin();
    // Set intensity
    matrix.setIntensity(0);
    // Clear the display:
    matrix.displayClear();
    // Set alignment to center
    matrix.setTextAlignment(PA_CENTER);

    // Set Font to Eyeball sprites
    matrix.setFont(eyeballFont);
    // Print initial eyes
    matrix.print("B B");
}

void loop() {
    // Close eyes and clear display
    eyes_close(15);
    delay(50);
    matrix.displayClear();

    // Wait for next rep
    delay(10000);

    // Open eyes
    eyes_open(15);
    eyeDirection = eyeCenter;
    delay(500);

    // Blink a couple of times
    for (uint8_t i = 0; i < 2; i++)
    {
        eyes_blink(25);
        delay(100);
    }
    eyeDirection = eyeCenter;

    // Look around
    delay(500);
    eyeDirection = eyes_look(25, eyeDirection, eyeRight);
    delay(1000);
    eyeDirection = eyes_look(25, eyeDirection, eyeCenter);
    delay(200);

    // Blink a couple of times again
    for (uint8_t i = 0; i < 2; i++)
    {
        eyes_blink(25);
        delay(100);
    }
    eyeDirection = eyeCenter;

    // Look around some more
    delay(200);
    eyeDirection = eyes_look(25, eyeDirection, eyeRight);
    delay(1000);
    eyeDirection = eyes_look(25, eyeDirection, eyeLeft);
    delay(500);
    eyeDirection = eyes_look(25, eyeDirection, eyeDown);
    delay(500);
    eyeDirection = eyes_look(25, eyeDirection, eyeLeft);
    delay(1000);
    eyeDirection = eyes_look(25, eyeDirection, eyeRight);
    delay(500);
    eyeDirection = eyes_look(25, eyeDirection, eyeCenter);

    // Single wink
    delay(500);
    eyes_wink(25, false);
    eyeDirection = eyeCenter;
    delay(500);
}

void eyes_open(uint16_t speed) {
    matrix.print("A A");
    delay(speed);
    matrix.print("\001 \001");
    delay(speed);
    matrix.print("\002 \002");
    delay(speed);
    matrix.print("\003 \003");
    delay(speed);
    matrix.print("\004 \004");
    delay(speed);
    matrix.print("\005 \005");
    delay(speed);
    matrix.print("B B");
}

void eyes_close(uint16_t speed) {
    matrix.print("B B");
    delay(speed);
    matrix.print("\005 \005");
    delay(speed);
    matrix.print("\004 \004");
    delay(speed);
    matrix.print("\003 \003");
    delay(speed);
    matrix.print("\002 \002");
    delay(speed);
    matrix.print("\001 \001");
    delay(speed);
    matrix.print("A A");
}

inline void eyes_blink(uint16_t speed) {
    eyes_close(speed);
    eyes_open(speed);
}

void eyes_wink(uint16_t speed, bool leftEye) {
    if (leftEye) {
        matrix.print("\005 B");
        delay(speed);
        matrix.print("\004 B");
        delay(speed);
        matrix.print("\003 B");
        delay(speed);
        matrix.print("\002 B");
        delay(speed);
        matrix.print("\001 B");
        delay(speed);
        matrix.print("A B");
        delay(speed);
        matrix.print("\001 B");
        delay(speed);
        matrix.print("\002 B");
        delay(speed);
        matrix.print("\003 B");
        delay(speed);
        matrix.print("\004 B");
        delay(speed);
        matrix.print("\005 B");
        delay(speed);
        matrix.print("B B");
    } else {
        matrix.print("B \005");
        delay(speed);
        matrix.print("B \004");
        delay(speed);
        matrix.print("B \003");
        delay(speed);
        matrix.print("B \002");
        delay(speed);
        matrix.print("B \001");
        delay(speed);
        matrix.print("B A");
        delay(speed);
        matrix.print("B \001");
        delay(speed);
        matrix.print("B \002");
        delay(speed);
        matrix.print("B \003");
        delay(speed);
        matrix.print("B \004");
        delay(speed);
        matrix.print("B \005");
        delay(speed);
        matrix.print("B B");
    }
}

void eyes_roll(uint16_t speed) {
    eyes_look(speed, eyeCenter, eyeUp);
    delay(speed);
    matrix.print("Q Q");
    delay(speed);
    matrix.print("R R");
    delay(speed);
    matrix.print("F F");
    delay(speed);
    matrix.print("S S");
    delay(speed);
    matrix.print("T T");
    delay(speed);
    matrix.print("D D");
    delay(speed);
    matrix.print("U U");
    delay(speed);
    matrix.print("V V");
    delay(speed);
    matrix.print("E E");
    delay(speed);
    matrix.print("O O");
    delay(speed);
    matrix.print("P P");
    delay(speed);
    matrix.print("C C");
    delay(speed);
    eyes_look(speed, eyeUp, eyeCenter);
}

eyeDir_t eyes_look(uint16_t speed, eyeDir_t start, eyeDir_t end) {
    switch (start) {
    case eyeCenter:
        switch (end) {
        case eyeUp:
            matrix.print("K K");
            delay(speed);
            matrix.print("C C");
            break;
        case eyeDown:
            matrix.print("L L");
            delay(speed);
            matrix.print("D D");
            break;
        case eyeLeft:
            matrix.print("M M");
            delay(speed);
            matrix.print("E E");
            break;
        case eyeRight:
            matrix.print("N N");
            delay(speed);
            matrix.print("F F");
            break;
        default:
            matrix.print("B B");
            return start;
        }
        break;

    case eyeUp:
        switch (end) {
        case eyeCenter:
            matrix.print("K K");
            delay(speed);
            matrix.print("B B");
            break;
        case eyeDown:
            matrix.print("K K");
            delay(speed);
            matrix.print("B B");
            delay(speed);
            matrix.print("L L");
            delay(speed);
            matrix.print("D D");
            break;
        case eyeLeft:
            matrix.print("G G");
            delay(speed);
            matrix.print("E E");
            break;
        case eyeRight:
            matrix.print("H H");
            delay(speed);
            matrix.print("F F");
            break;
        default:
            matrix.print("C C");
            return start;
        }
        break;

    case eyeDown:
        switch (end) {
        case eyeCenter:
            matrix.print("L L");
            delay(speed);
            matrix.print("B B");
            break;
        case eyeUp:
            matrix.print("L L");
            delay(speed);
            matrix.print("B B");
            delay(speed);
            matrix.print("K K");
            delay(speed);
            matrix.print("C C");
            break;
        case eyeLeft:
            matrix.print("I I");
            delay(speed);
            matrix.print("E E");
            break;
        case eyeRight:
            matrix.print("J J");
            delay(speed);
            matrix.print("F F");
            break;
        default:
            matrix.print("D D");
            return start;
        }
        break;

    case eyeLeft:
        switch (end) {
        case eyeCenter:
            matrix.print("M M");
            delay(speed);
            matrix.print("B B");
            break;
        case eyeUp:
            matrix.print("G G");
            delay(speed);
            matrix.print("C C");
            break;
        case eyeDown:
            matrix.print("I I");
            delay(speed);
            matrix.print("D D");
            break;
        case eyeRight:
            matrix.print("M M");
            delay(speed);
            matrix.print("B B");
            delay(speed);
            matrix.print("N N");
            delay(speed);
            matrix.print("F F");
            break;
        default:
            matrix.print("E E");
            return start;
        }
        break;

    case eyeRight:
        switch (end) {
        case eyeCenter:
            matrix.print("N N");
            delay(speed);
            matrix.print("B B");
            break;
        case eyeUp:
            matrix.print("H H");
            delay(speed);
            matrix.print("C C");
            break;
        case eyeDown:
            matrix.print("J J");
            delay(speed);
            matrix.print("D D");
            break;
        case eyeLeft:
            matrix.print("N N");
            delay(speed);
            matrix.print("B B");
            delay(speed);
            matrix.print("M M");
            delay(speed);
            matrix.print("E E");
            break;
        default:
            matrix.print("F F");
            return start;
        }
        break;

    default:
        switch (end) {
        case eyeUp:
            matrix.print("C C");
            break;
        case eyeDown:
            matrix.print("D D");
            break;
        case eyeLeft:
            matrix.print("E E");
            break;
        case eyeRight:
            matrix.print("F F");
            break;
        default:
            matrix.print("B B");
            return eyeCenter;
        }
        break;
    }

    return end;
}

