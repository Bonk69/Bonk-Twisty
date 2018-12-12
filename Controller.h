#ifndef Controller_h
#define Controller_h

#include <Arduino.h>

//***********************************************************************
class Mux
{
  public:
    Mux(byte outpin_, byte numPins_, bool analog_);
    byte outpin;
    byte numPins;
    bool analog;
};
//************************************************************************
//Button (Pin Number, Command, Note Number, Channel, Debounce Time)
class Button
{
  public:
    Button(byte led, byte pin, byte command, byte value, byte channel, byte debounce);
    Button(byte led, Mux mux, byte muxpin, byte command, byte value, byte channel, byte debounce);
    byte getValue();
    void muxUpdate();
    void newValue(byte command, byte value, byte channel);
    byte Bcommand;
    byte Bvalue;
    byte Bchannel;
    byte Btoggle;
    byte Btoggle1;
    byte Btoggle2;
    byte Btoggle3;
    byte Btoggle4;
    byte Bpin;
    byte Bled;

  private:
    byte _previous;
    byte _current;
    unsigned long _time;
    int _debounce;
    byte _muxpin;
    byte _numMuxPins;
    byte _value;
    byte _command;
    bool _busy;
    byte _status;
    byte _last;
    byte _enablepin;
    byte _pin;
};
//*************************************************************************
class Pot
{
  public:
    Pot(byte pin, byte command, byte control, byte channel);
    Pot(Mux mux, byte muxpin ,byte command, byte control, byte channel);
    void muxUpdate();
    void newValue(byte command, byte value, byte channel);
    byte getValue();
    byte Pcommand;
    byte Pcontrol;
    byte Pchannel;
    byte Ppin;

  private:
    byte _pin;
    byte _muxpin;
    byte _numMuxPins;
    byte _control;
    int _value;
    int _oldValue;
    bool _changed;
    byte _enablepin;
};
//*************************************************************************
class Event
{
  public:
    Event(byte milli, byte command, byte value, byte channel);
    void recordMidiEvent();
    void playMidiEvent();
    byte recled;
    byte playled;
    byte Ecommand;
    byte Evalue;
    byte Echannel;
    byte Emilli;
   

  private:
    byte _recled;
    byte _playled;
    byte _command;
    byte _value;
    byte _channel;
    byte _milli;
  

};
//*************************************************************************

#endif
