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
int track[128] = {tonic+tritone, minor2nd+tritone, minor2nd+tritone, minor2nd+tritone, tonic+tritone, minor2nd+tritone, fifth+tritone, minor2nd+tritone, tonic, minor2nd, minor2nd, minor2nd, tonic, minor2nd, fifth, minor2nd };
int trackNL[128] = {e, e, e, e, e, e, e, e, e, e, e, e, e, e, e, e};
int trackOnOff[128] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int trackSize = 6;
  

// Serial Buffer (makey makey input)
int buf[2];
int idx = 0;
  
// Runtime
int playedTrackNoteIndex = 0; // sequenceur
int loopInit = 0; // To init track one time
int i=0;
  
void setup() {
  pinMode(arpPin, OUTPUT);
  Serial.begin(115200);
  randomSeed(analogRead(0)); // Init the random function
  //createPattern();
}    


void createPattern() {
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
}

void getSerialInfo() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    buf[idx] = Serial.read();
    idx = (idx+1) % 2;
    if (idx == 1) { // buf is full
      if (buf[0] == 0) {// key down
        // buf[1] // nr wurscht
        saucisseDownBefore();
        if (buf[1] == 0) saucisseDown0();
        if (buf[1] == 1) saucisseDown1();
        if (buf[1] == 2) saucisseDown2();
        if (buf[1] == 3) saucisseDown3();
        if (buf[1] == 4) saucisseDown4();
        if (buf[1] == 5) saucisseDown5();
        saucisseDownAfter();
                                
      } else { // key up
        // buf[1] // nr wurscht
        /*
        saucisseUpBefore();
        if (buf[1] == 0) saucisseUp0();
        if (buf[1] == 1) saucisseUp1();
        if (buf[1] == 2) saucisseUp2();
        if (buf[1] == 3) saucisseUp3();
        if (buf[1] == 4) saucisseUp4();
        if (buf[1] == 5) saucisseUp5();
        */
        saucisseUpAfter();
        
      }
    }
  }
}



void loop() {

getSerialInfo();

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
 
 // Callbacks

void saucisseDownBefore() {
  digitalWrite(vcaPin, 1);
}
 
void saucisseDown0() {
  createPattern();
   playTrack(track, 0);   
}
void saucisseDown1() {
  createPattern();
  playTrack(track, 0); 
}
void saucisseDown2() {
  createPattern();
  playTrack(track, 0); 
}
void saucisseDown3() {
  createPattern();
  playTrack(track, 0); 
  
}
void saucisseDown4() {
   createPattern();
   playTrack(track, 0); 
  
}
void saucisseDown5() {
   createPattern();
   playTrack(track, 0); 
}

void saucisseDownAfter() {
  
}

void saucisseUpAfter() {
  digitalWrite(vcaPin, 0);
}


