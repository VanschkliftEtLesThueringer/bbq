/*Werkstatt Arpeggiator 
  Moog Music Inc. 2014
  Written by Chris David Howe

  Circuit consists of one 10kΩ resistor and a 2.2µf capacitor low pass filter.
*/

#include <werkstatt.h>

const int arpPin = 6;
const int vcaPin = 13;

arpeggiator arpeggiator(6); //initiate and name the arpeggiator class (Output pin)

//All :tonic, minor2nd, major2nd, minor3rd, major3rd, fourth, tritone, fifth, minor6th, major6th, minor7th, major7th, octave.  See reference.txt for chord and mode ideas. 
//int pentaNotes[] = {tonic, minor3rd, fourth, fifth, minor7th};
int noteSet[] = {tonic, major2nd, major3rd, fourth, fifth, major2nd + tonic, major3rd + tonic, fourth + tonic, fifth+ tonic};

// note values: w, h, q, qt, e, et, sx, sxt, th, sxf  
int lengthSet[] = {q, qt, et, sx};

// Global Param
int randNumberNote = 0;
int randNumberNoteLengh = 0;
int BPM = 180;
  
// Track Params
int track[128];
int trackNL[128];
int trackSize = 8;
  
// Runtime
int playedTrackNoteIndex = 0; // sequenceur
int loopInit = 0; // To init track one time
int i=0;
  
void setup() {
  pinMode(arpPin, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0)); // Init the random function
}      

void loop() {
  // Define track pattern on time
  if(loopInit == 0){
    Serial.print("\n Track :");
    for(i=0; i < trackSize; i++){ // define each note according track size
      // Get a random index note within set of note
      randNumberNote = random(0, sizeof(noteSet)/sizeof(int) );
      randNumberNoteLengh = random(0, sizeof(lengthSet)/sizeof(int) );
      
      track[i] = noteSet[randNumberNote];
      trackNL[i] = lengthSet[randNumberNoteLengh ]; 
      
      Serial.print(" ");
      Serial.print(randNumberNote); 
      Serial.print("-"); 
      Serial.print(trackNL[i]);
    }
    loopInit = 1;
   }
   
   playTrack(track, 1); 
}

void playTrack(int * track, int egh){
   if(egh == 1)digitalWrite(vcaPin, 1);   
   
   // Appogiature Style
   //if(track[playedTrackNoteIndex] == fifth)
   //  arpeggiator.play(BPM, tritone, et);
   
   // Play current note of the track
   Serial.print("\n Note Played : ");Serial.print(track[playedTrackNoteIndex]);
   arpeggiator.play(BPM, track[playedTrackNoteIndex], trackNL[0]);
   
   // Get next note of the track
   playedTrackNoteIndex++;
   if(playedTrackNoteIndex > trackSize)playedTrackNoteIndex = 0;
  
   if(egh == 1)digitalWrite(vcaPin, 0);
   if(egh == 1)delay(25 );    
}
 





