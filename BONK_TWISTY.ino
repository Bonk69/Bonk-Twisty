#include <FastLED.h>
#include <MIDI.h>
#include "Controller.h"

// setup stuff for addressable leds
#define LED_PIN     13 
#define NUM_LEDS    14
CRGB leds[NUM_LEDS];


MIDI_CREATE_DEFAULT_INSTANCE();

//************************************************************
//***SET THE NUMBER OF CONTROLS USED**************************
//************************************************************
//---How many buttons are connected directly to pins?---------
byte NUMBER_BUTTONS = 14;
//---How many potentiometers are connected directly to pins?--
byte NUMBER_POTS = 0;
//---How many buttons are connected to a multiplexer?---------
byte NUMBER_MUX_BUTTONS = 0;
//---How many potentiometers are connected to a multiplexer?--
byte NUMBER_MUX_POTS = 16;
//************************************************************

//***ANY MULTIPLEXERS? (74HC4067)************************************
//MUX address pins must be connected to Arduino UNO pins 2,3,4,5 (or 2,3,4 for 8 channel)
//A0 = PIN2, A1 = PIN3, A2 = PIN4, A3 = PIN5 // old  
//*******************************************************************
//Mux NAME (OUTPUT PIN, , How Many Mux Pins?(8 or 16) , Is It Analog?);


Mux M1(A7, 8, true); //Analog multiplexer on Arduino pin A7
Mux M2(A6, 8, true); //Analog multiplexer on Arduino analog pin A6
//*******************************************************************


// undefined midi cc we can use....
// 3
// 9
// 14-15
// 20-31
// 85-90
// 102-119


//***DEFINE DIRECTLY CONNECTED POTENTIOMETERS************************
//Pot (Pin Number, Command, CC Control, Channel Number)
//**Command parameter is for future use**

//Pot PO1(A0, 0, 1, 1);
//Pot PO2(A1, 0, 10, 1);
//Pot PO3(A2, 0, 22, 1);
//Pot PO4(A3, 0, 118, 1);
//Pot PO5(A4, 0, 30, 1);
//Pot PO6(A5, 0, 31, 1);
//*******************************************************************
//Add pots used to array below like this->  Pot *POTS[] {&PO1, &PO2, &PO3, &PO4, &PO5, &PO6};
Pot *POTS[] {};
//*******************************************************************


//***DEFINE DIRECTLY CONNECTED BUTTONS*******************************
//Button (led number, Pin Number, Command, Note Number, Channel, Debounce Time)
//** Command parameter 0=NOTE  1=CC  2=Toggle CC 3=Channel**

Button BU1(13, 6, 2, 3, 1, 5 );
Button BU2(12, 7, 2, 9, 1, 5 );
Button BU3(11, 8, 2, 14, 1, 5 );
Button BU4(10, 9, 2, 15, 1, 5 );
Button BU5(9, 10, 2, 20, 1, 5 );
Button BU6(8, 11, 3, 21, 1, 5 );
Button BU7(7, 12, 3, 22, 2, 5 );
Button BU8(6, 5, 3, 23, 3, 5 );
Button BU9(5, 14, 3, 24, 4, 5 );
Button BU10(4, 15, 2, 25, 1, 5 );
Button BU11(3, 16, 2, 26, 1, 5 );
Button BU12(2, 17, 2, 27, 1, 5 );
Button BU13(1, 18, 2, 28, 1, 5 );
Button BU14(0, 19, 2, 29, 1, 5 );
//*******************************************************************
//Add buttons used to array below like this->  Button *BUTTONS[] {&BU1, &BU2, &BU3, &BU4, &BU5, &BU6, &BU7, &BU8};
Button *BUTTONS[] {&BU1, &BU2, &BU3, &BU4, &BU5, &BU6, &BU7, &BU8, &BU9,&BU10, &BU11, &BU12, &BU13, &BU14 };//, &BU2, &BU3, &BU4, &BU5, &BU6, &BU7};
//*******************************************************************


//***DEFINE BUTTONS CONNECTED TO MULTIPLEXER*************************
//Button::Button(led number, Mux mux, byte muxpin, byte command, byte value, byte channel, byte debounce)
//** Command parameter 0=NOTE  1=CC  2=Toggle CC 3=Channel **

//Button MBU1(0, M1, 0, 2, 70, 1, 5);
//Button MBU2(1, M1, 1, 2, 71, 3, 5);
//Button MBU3(3, M1, 2, 3, 72, 1, 5);
//Button MBU4(2, M1, 3, 3, 73, 4, 5);
//Button MBU5(M1, 4, 0, 74, 1, 5);
//Button MBU6(M1, 5, 0, 75, 1, 5);
//Button MBU7(M1, 6, 0, 76, 1, 5);
//Button MBU8(M1, 7, 0, 77, 1, 5);
//Button MBU9(M1, 8, 0, 78, 1, 5);
//Button MBU10(M1, 9, 0, 79, 1, 5);
//Button MBU11(M1, 10, 0, 80, 1, 5);
//Button MBU12(M1, 11, 0, 81, 1, 5);
//Button MBU13(M1, 12, 0, 82, 1, 5);
//Button MBU14(M1, 13, 0, 83, 1, 5);
//Button MBU15(M1, 14, 0, 84, 1, 5);
//Button MBU16(M1, 15, 0, 85, 1, 5);
//*******************************************************************
////Add multiplexed buttons used to array below like this->  Button *MUXBUTTONS[] {&MBU1, &MBU2, &MBU3, &MBU4, &MBU5, &MBU6.....};
Button *MUXBUTTONS[] {};

//*******************************************************************


//***DEFINE POTENTIOMETERS CONNECTED TO MULTIPLEXER*******************
//Pot::Pot(Mux mux, byte muxpin, byte command, byte control, byte channel)
//**Command parameter is for future use**

Pot MPO1(M2, 0, 0, 30, 1);
Pot MPO2(M2, 1, 0, 31, 1);
Pot MPO3(M2, 2, 0, 85, 1);
Pot MPO4(M2, 3, 0, 86, 1);
Pot MPO5(M2, 4, 0, 87, 1);
Pot MPO6(M2, 5, 0, 88, 1);
Pot MPO7(M2, 6, 0, 89, 1);
Pot MPO8(M2, 7, 0, 90, 1);
Pot MPO9(M1, 0, 0, 102, 1);
Pot MPO10(M1, 1, 0, 103, 2);
Pot MPO11(M1, 2, 0, 104, 1);
Pot MPO12(M1, 3, 0, 105, 2);
Pot MPO13(M1, 4, 0, 106, 1);
Pot MPO14(M1, 5, 0, 107, 2);
Pot MPO15(M1, 6, 0, 108, 1);
Pot MPO16(M1, 7, 0, 109, 2);
//*******************************************************************
//Add multiplexed pots used to array below like this->  Pot *MUXPOTS[] {&MPO1, &MPO2, &MPO3, &MPO4, &MPO5, &MPO6.....};
Pot *MUXPOTS[] {&MPO1, &MPO2, &MPO3, &MPO4, &MPO5, &MPO6, &MPO7, &MPO8, &MPO9, &MPO10, &MPO11, &MPO12, &MPO13, &MPO14, &MPO15, &MPO16 };
//*******************************************************************


byte bank = 1;
byte ledbright = 100;
byte EventRecord = 0;
byte EventPlay = 0;
void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
 MIDI.begin(MIDI_CHANNEL_OFF);
  Serial.begin(115200);
}


void loop() {
  if (NUMBER_BUTTONS != 0) updateButtons();
  if (NUMBER_POTS != 0) updatePots();
  if (NUMBER_MUX_BUTTONS != 0) updateMuxButtons();
  if (NUMBER_MUX_POTS != 0) updateMuxPots();
}


//*****************************************************************
void updateButtons() {

  // Cycle through Button array
  for (int i = 0; i < NUMBER_BUTTONS; i = i + 1) {
    byte message = BUTTONS[i]->getValue();

    //  Button is pressed
    if (message == 0) {
      switch (BUTTONS[i]->Bcommand) {
        case 0: //Note
          MIDI.sendNoteOn(BUTTONS[i]->Bvalue, 127, BUTTONS[i]->Bchannel);
           switchLed(BUTTONS[i]->Bpin, true, bank);
          break;
        case 1: //CC
          MIDI.sendControlChange(BUTTONS[i]->Bvalue, 127, BUTTONS[i]->Bchannel);
          switchLed(BUTTONS[i]->Bpin, true, bank);
          break;
        case 2: //Toggle
         switch (bank) {
          case 1:
         if (BUTTONS[i]->Btoggle1 == 0) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue, 127, bank);
            switchLed(BUTTONS[i]->Bled, true, bank);
            BUTTONS[i]->Btoggle1 = 1;
          }
          else if (BUTTONS[i]->Btoggle1 == 1) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue, 0, bank);
            switchLed(BUTTONS[i]->Bled, false, bank);
            BUTTONS[i]->Btoggle1 = 0;
          }
          break;
          case 2:
          if (BUTTONS[i]->Btoggle2 == 0) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue, 127, bank);
            switchLed(BUTTONS[i]->Bled, true, bank);
            BUTTONS[i]->Btoggle2 = 1;
          }          
          else if (BUTTONS[i]->Btoggle2 == 1) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue, 0, bank);
            switchLed(BUTTONS[i]->Bled, false, bank);
            BUTTONS[i]->Btoggle2 = 0;
          }
          break;
          case 3:
          if (BUTTONS[i]->Btoggle3 == 0) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue, 127, bank);
            switchLed(BUTTONS[i]->Bled, true, bank);
            BUTTONS[i]->Btoggle3 = 1;
          }          
          else if (BUTTONS[i]->Btoggle3 == 1) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue, 0, bank);
            switchLed(BUTTONS[i]->Bled, false, bank);
            BUTTONS[i]->Btoggle3 = 0;
          }
          break;
          case 4:
          if (BUTTONS[i]->Btoggle4 == 0) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue, 127, bank);
            switchLed(BUTTONS[i]->Bled, true, bank);
            BUTTONS[i]->Btoggle4 = 1;
          }          
          else if (BUTTONS[i]->Btoggle4 == 1) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue, 0, bank);
            switchLed(BUTTONS[i]->Bled, false, bank);
            BUTTONS[i]->Btoggle4 = 0;
          }
          break;
          }
          
          break;

case 3: //channel select


switch (BUTTONS[i]->Bchannel){
case 1: 
          
        

        for (int i = 0; i < NUMBER_BUTTONS; i = i + 1) {

          if (BUTTONS[i]->Btoggle1 == 1 ){
             switchLed(BUTTONS[i]->Bled, true, 1);
       }
          if (BUTTONS[i]->Btoggle1 == 0){
              switchLed(BUTTONS[i]->Bled, false, 1);
            
          }
          bank = 1;
           
        }
        switchLed(BUTTONS[i]->Bled, true, 1); 
        break;
   case 2:

     for (int i = 0; i < NUMBER_BUTTONS; i = i + 1) {
          
            
          
          if (BUTTONS[i]->Btoggle2 == 1 ){
             switchLed(BUTTONS[i]->Bled, true, 2);
       }
          if (BUTTONS[i]->Btoggle2 == 0){
              switchLed(BUTTONS[i]->Bled, false, 2);
            
          }
          bank = 2;
          
        } 
        switchLed(BUTTONS[i]->Bled, true, 2);  
        break; 
    case 3:
    
    for (int i = 0; i < NUMBER_BUTTONS; i = i + 1) {
         
          
           
          
          if (BUTTONS[i]->Btoggle3 == 1 ){
             switchLed(BUTTONS[i]->Bled, true, 3);
       }
          if (BUTTONS[i]->Btoggle3 == 0){
              switchLed(BUTTONS[i]->Bled, false, 3);
            
          }
          bank = 3;
        }  
        switchLed(BUTTONS[i]->Bled, true, 3);    
break;
    case 4: 
    for (int i = 0; i < NUMBER_BUTTONS; i = i + 1) {
        
           
                
          if (BUTTONS[i]->Btoggle4 == 1 ){
             switchLed(BUTTONS[i]->Bled, true, 4);
       }
          if (BUTTONS[i]->Btoggle4 == 0){
              switchLed(BUTTONS[i]->Bled, false, 4);
            }
          
          bank = 4;
        }   
        switchLed(BUTTONS[i]->Bled, true, 4); 
        break; 
}

case 4:
if (EventRecord = 1){
  EventRecord = 0;}
  else{
  EventRecord = 1;
  
}
break;
case 5:
if (EventPlay = 1){
  EventPlay = 0;}
  else {
    EventPlay = 1;
}
          break;
      }
    }
    //  Button is not pressed
    if (message == 1) {
      switch (BUTTONS[i]->Bcommand) {
        case 0:
          MIDI.sendNoteOff(BUTTONS[i]->Bvalue, 0, bank);
         // switchLed(BUTTONS[i]->Bpin, false, bank); 
          break;
        case 1:
          MIDI.sendControlChange(BUTTONS[i]->Bvalue, 0, bank);
          //switchLed(BUTTONS[i]->Bpin, false, bank); 
          break;
      }
    }
  }
}
//*******************************************************************
void updateMuxButtons() {

  // Cycle through Mux Button array
  for (int i = 0; i < NUMBER_MUX_BUTTONS; i = i + 1) {

    MUXBUTTONS[i]->muxUpdate();
    byte message = MUXBUTTONS[i]->getValue();

    //  Button is pressed
    if (message == 0) {
      switch (MUXBUTTONS[i]->Bcommand) {
        case 0: //Note
          MIDI.sendNoteOn(MUXBUTTONS[i]->Bvalue, 127, bank);
          break;
case 1: //CC
          MIDI.sendControlChange(MUXBUTTONS[i]->Bvalue, 127, bank);
          break;
case 2: //Toggle
         switch (bank) {
          case 1:
         if (MUXBUTTONS[i]->Btoggle1 == 0) {
            MIDI.sendControlChange(MUXBUTTONS[i]->Bvalue, 127, bank);
            switchLed(BUTTONS[i]->Bled, true, bank);
            if (EventRecord = 1){
              
            }
            MUXBUTTONS[i]->Btoggle1 = 1;
          }
          else if (MUXBUTTONS[i]->Btoggle1 == 1) {
           MIDI.sendControlChange(MUXBUTTONS[i]->Bvalue, 0, bank);
            switchLed(BUTTONS[i]->Bled, false, bank);
            MUXBUTTONS[i]->Btoggle1 = 0;
          }
          break;
          case 2:
          if (MUXBUTTONS[i]->Btoggle2 == 0) {
            MIDI.sendControlChange(MUXBUTTONS[i]->Bvalue, 127, bank);
            switchLed(BUTTONS[i]->Bled, true, bank);
            MUXBUTTONS[i]->Btoggle2 = 1;
          }          
          else if (MUXBUTTONS[i]->Btoggle2 == 1) {
            MIDI.sendControlChange(MUXBUTTONS[i]->Bvalue, 0, bank);
            switchLed(BUTTONS[i]->Bled, false, bank);
            MUXBUTTONS[i]->Btoggle2 = 0;
          }
          break;
          case 3:
          if (MUXBUTTONS[i]->Btoggle3 == 0) {
            MIDI.sendControlChange(MUXBUTTONS[i]->Bvalue, 127, bank);
            switchLed(BUTTONS[i]->Bled, true, bank);
            MUXBUTTONS[i]->Btoggle3 = 1;
          }          
          else if (MUXBUTTONS[i]->Btoggle3 == 1) {
            MIDI.sendControlChange(MUXBUTTONS[i]->Bvalue, 0, bank);
            switchLed(BUTTONS[i]->Bled, false, bank);
            MUXBUTTONS[i]->Btoggle3 = 0;
          }
          break;
          case 4:
          if (MUXBUTTONS[i]->Btoggle4 == 0) {
            MIDI.sendControlChange(MUXBUTTONS[i]->Bvalue, 127, bank);
            switchLed(BUTTONS[i]->Bled, true, bank);
            MUXBUTTONS[i]->Btoggle4 = 1;
          }          
          else if (MUXBUTTONS[i]->Btoggle4 == 1) {
            MIDI.sendControlChange(MUXBUTTONS[i]->Bvalue, 0, bank);
            switchLed(BUTTONS[i]->Bled, false, bank);
            MUXBUTTONS[i]->Btoggle4 = 0;
          }
          break;
          }
          
          break;

case 3: //channel select


switch (MUXBUTTONS[i]->Bchannel){
case 1: 
          
        

        for (int i = 0; i < NUMBER_MUX_BUTTONS; i = i + 1) {

          if (MUXBUTTONS[i]->Btoggle1 == 1 ){
             switchLed(BUTTONS[i]->Bled, true, 1);
       }
          if (MUXBUTTONS[i]->Btoggle1 == 0){
              switchLed(BUTTONS[i]->Bled, false, 1);
            
          }
          bank = 1;
           
        }
        switchLed(BUTTONS[i]->Bled, true, 1); 
        break;
   case 2:

     for (int i = 0; i < NUMBER_MUX_BUTTONS; i = i + 1) {
          
            
          
          if (MUXBUTTONS[i]->Btoggle2 == 1 ){
             switchLed(BUTTONS[i]->Bled, true, 2);
       }
          if (MUXBUTTONS[i]->Btoggle2 == 0){
              switchLed(BUTTONS[i]->Bled, false, 2);
            
          }
          bank = 2;
          
        } 
        switchLed(BUTTONS[i]->Bled, true, 2);  
        break; 
    case 3:
    
    for (int i = 0; i < NUMBER_MUX_BUTTONS; i = i + 1) {
         
          
           
          
          if (MUXBUTTONS[i]->Btoggle3 == 1 ){
             switchLed(BUTTONS[i]->Bled, true, 3);
       }
          if (MUXBUTTONS[i]->Btoggle3 == 0){
              switchLed(BUTTONS[i]->Bled, false, 3);
            
          }
          bank = 3;
        }  
        switchLed(BUTTONS[i]->Bled, true, 3);    
break;
    case 4: 
    for (int i = 0; i < NUMBER_MUX_BUTTONS; i = i + 1) {
        
           
                
          if (MUXBUTTONS[i]->Btoggle4 == 1 ){
             switchLed(BUTTONS[i]->Bled, true, 4);
       }
          if (MUXBUTTONS[i]->Btoggle4 == 0){
              switchLed(BUTTONS[i]->Bled, false, 4);
            }
          
          bank = 4;
        }   
        switchLed(BUTTONS[i]->Bled, true, 4); 
        break; 
}

case 4:
if (EventRecord = 1){
  EventRecord = 0;}
  else{
  EventRecord = 1;
  
}
break;
case 5:
if (EventPlay = 1){
  EventPlay = 0;}
  else {
    EventPlay = 1;
}
          break;
      }
    }
    //  Button is not pressed
    if (message == 1) {
      switch (MUXBUTTONS[i]->Bcommand) {
        case 0:
          MIDI.sendNoteOff(MUXBUTTONS[i]->Bvalue, 0, bank);
          break;
        case 1:
          MIDI.sendControlChange(MUXBUTTONS[i]->Bvalue, 0, bank);
          break;
      }
    }
  }
}
//***********************************************************************
void updatePots() {
  for (int i = 0; i < NUMBER_POTS; i = i + 1) {
    byte potmessage = POTS[i]->getValue();
    if (potmessage != 255) MIDI.sendControlChange(POTS[i]->Pcontrol, potmessage, bank);
  }
}
//***********************************************************************
void updateMuxPots() {
  for (int i = 0; i < NUMBER_MUX_POTS; i = i + 1) {
    MUXPOTS[i]->muxUpdate();
    byte potmessage = MUXPOTS[i]->getValue();
    if (potmessage != 255) MIDI.sendControlChange(MUXPOTS[i]->Pcontrol, potmessage, bank);
  }
}
void recordMidiEvent(byte milli, byte command, byte value, byte channel){
  
}



void switchLed(byte led, bool state, byte bank){
  
  
  switch (bank) {
        case 1: 
          if (state == true) { 
            
             leds[led] = CRGB(ledbright,0,0);
             FastLED.show();         
          } else {    
             leds[led] = CRGB(0,0,0);
             FastLED.show();    
          }
          break;
        case 2: 
          if(state == true){
             leds[led] = CRGB(0,ledbright,0);
            FastLED.show();  
          } else {
             leds[led] = CRGB(0,0,0);
             FastLED.show(); 
          }
          break; 
       case 3:
            if(state == true){
             leds[led] = CRGB(0,0,ledbright);
           FastLED.show();  
          } else {
              leds[led] = CRGB(0,0,0);
           FastLED.show(); 
          }
          break; 
       case 4:
            if(state == true){
           leds[led] = CRGB(ledbright,0,ledbright);
           FastLED.show();   
          } else {
          leds[led] = CRGB(0,0,0);
          FastLED.show();       
          }
          break; 
  }
}

