/*Werkstatt Arpeggiator 
  Moog Music Inc. 2014
  Written by Chris David Howe

  Circuit consists of one 10kΩ resistor and a 2.2µf capacitor low pass filter.
*/

#include <werkstatt.h>

const int arpPin = 6;
const int vcaPin = 13;

arpeggiator arpeggiator(6); //initiate and name the arpeggiator class (Output pin)

/* 
notes are assigned in intervals: tonic, minor2nd, major2nd, minor3rd,
major3rd, fourth, tritone, fifth, minor6th, major6th, minor7th,
major7th, octave. 
*/

  int pentaNotes[] = {tonic, minor3rd, tritone, fifth, minor7th};
  int notes[] = {tonic+tritone, minor2nd+tritone, minor2nd+tritone, minor2nd+tritone, tonic+tritone, minor2nd+tritone, fifth+tritone, minor2nd+tritone, tonic, minor2nd, minor2nd, minor2nd, tonic, minor2nd, fifth, minor2nd }; // VCO EXP config
  // int notes[] = {tonic, minor2nd, minor2nd, minor2nd, tonic, minor2nd, fifth, minor2nd}; // VCO EXP config
 // int notes[] = {tonic-gtritone, minor2nd-tritone, minor2nd - tritone, minor2nd-tritone, tonic-tritone, minor2nd-tritone, fifth-tritone, minor2nd-tritone}; // VCO EXP config

  //int notes[] = {0, 0, 0, 0, 0, 0, 0, 0}; // VCO EXP config


// note values: w, h, q, qt, e, et, sx, sxt, th, sxf 
  int note_values[] = {e, e, e, e, e, e, e, e,e, e, e, e, e, e, e, e}; //VCO EXP config

  
void setup() {
   pinMode(arpPin, OUTPUT);
}      


void loop() {
for (int i = 0; i < ( sizeof(notes)/sizeof(int) ); i++)
  {
   //define a BPM and run the arpeggiator.play function  
   digitalWrite(vcaPin, 1);
   arpeggiator.play(140, notes[i], note_values[i]);
 
   digitalWrite(vcaPin, 0);
   delay(25 ); 
  }
 
}
 




