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
int noteSet[] = {tonic, minor3rd, fourth, fifth, minor7th, tonic+octave, minor3rd+octave};
//int noteSet[] = {tonic, major2nd, major3rd, fourth, fifth, major2nd + tonic, major3rd + tonic, fourth + tonic, fifth+ tonic};



// note values: w, h, q, qt, e, et, sx, sxt, th, sxf  
int lengthSet[] = {h, q, et, sx };

// Global Param
int randNumberNote = 0;
int randNumberNoteLengh = 0;
int BPM = 160;
  
  
  // Track Params
//int track[128] = {tonic+tritone, minor2nd+tritone, minor2nd+tritone, minor2nd+tritone, tonic+tritone, minor2nd+tritone, fifth+tritone, minor2nd+tritone, tonic, minor2nd, minor2nd, minor2nd, tonic, minor2nd, fifth, minor2nd };

int track[128] = {fourth, fourth+octave, fourth, fourth+octave, fourth, fourth+octave, fourth, fourth+octave};
int trackNL[128] = {e, e, e, e, e, e, e, e, e, e, e, e, e, e, e, e};
int trackOnOff[128] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int trackSize = 8;
  

// Serial Buffer (makey makey input)
int buf[2];
int idx = 0;
  
// Runtime
int playedTrackNoteIndex = 0; // sequenceur
int loopInit = 0; // To init track one time
int i=0;
  
void setup() {
  pinMode(arpPin, OUTPUT);
  digitalWrite(vcaPin, 0);
  Serial.begin(115200);
  randomSeed(analogRead(0)); // Init the random function
  //createPattern();
}    

void debug(int* seq) {
  Serial.print("\n");
  for (i = 0; i< trackSize; i++) {
    Serial.print(" ");
    Serial.print(seq[i]); 
  }
}


void getSerialInfo() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    buf[idx] = Serial.read();

    //Serial.print("idx");
    //Serial.print(idx);
    //Serial.print("\n");
    
    if (idx == 1) { // buf is full
      //Serial.print("buf");
      //Serial.print(buf[0]);
      //Serial.print(buf[1]);
      //Serial.print("\n");
        
      if (buf[0] == 0) {// key down
        // buf[1] // nr wurscht
        saucisseDownBefore(buf[1]);

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
          idx = (idx+1) % 2;
  }
}


void createPattern() {
  // Define track pattern on time

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

}

void loop() {

  getSerialInfo();
  debug(trackOnOff);
  playTrack(track);
}

void playTrack(int * track){
   
   // Play current note of the track
   //Serial.print("\n Note Played : ");Serial.print(track[playedTrackNoteIndex]);
   
   digitalWrite(vcaPin, trackOnOff[playedTrackNoteIndex]);
   if (trackOnOff[playedTrackNoteIndex] == 1) {
 
      arpeggiator.play(BPM, track[playedTrackNoteIndex], trackNL[0]);     
   }

   // Get next note of the track
   playedTrackNoteIndex++;
   if(playedTrackNoteIndex > trackSize)playedTrackNoteIndex = 0;
   delay(50);
}
 
 // Callbacks

void saucisseDownBefore(int saucisse) {
  //trackOnOff[saucisse] =  (trackOnOff[saucisse] + 1) % 2; 
}
 
void saucisseDown0() {
  trackSize = 2;
  createPattern();
}
void saucisseDown1() {
  trackSize = 4;
  createPattern();
}
void saucisseDown2() {
    trackSize = 8;
  createPattern();

}
void saucisseDown3() {
   trackSize = 12;
  createPattern();
}
void saucisseDown4() {
  trackSize = 16;
  createPattern();
  
}
void saucisseDown5() {
  trackSize = 32;
  createPattern();
}

void saucisseDownAfter() {
  
}

void saucisseUpAfter() {
  digitalWrite(vcaPin, 0);
}


void setNot1track() {
  int trackTMP[8] = {octave, octave+octave,octave, octave+octave,octave, octave+octave,octave, octave+octave};
  int trackNLTMP[8] = {e, e, e, e,e, e,e, e};
  memcpy(trackTMP, track, 8);
  memcpy(trackNLTMP, trackNL, 8);
  trackSize = 8;
}  

void setNot2track() {
  int trackTMP[8] = {octave+major2nd, octave+octave+major2nd, octave+major2nd, octave+octave+major2nd,octave+major2nd, octave+octave+major2nd,octave+major2nd, octave+octave+major2nd};
  int trackNLTMP[8] = {e, e, e, e,e, e,e, e};
  memcpy(trackTMP, track, 8);
  memcpy(trackNLTMP, trackNL, 8);
  trackSize = 8;
} 

void setNot4track() {
  int trackTMP[2] = {octave+fourth, octave+octave+fourth};
  int trackNLTMP[2] = {e, e};
  memcpy(track, trackTMP, 2);
  memcpy(trackNL, trackNLTMP, 2);
  trackSize = 2;
}  

void setNot5track() {
  int trackTMP[2] = {octave+fifth, octave+octave+fifth};
  int trackNLTMP[2] = {e, e};
  memcpy(track, trackTMP, 2);
  memcpy(trackNL, trackNLTMP, 2);
  trackSize = 1;
}  


void setNOTrack() {
int trackNO[128] = {fourth, fourth+octave, fourth, fourth+octave, fourth, fourth+octave, fourth, fourth+octave, 
octave, octave+octave, octave, octave+octave, octave, octave+octave, octave, octave+octave,
major2nd, major2nd+octave, major2nd, major2nd+octave, major2nd, major2nd+octave, major2nd, major2nd+octave,
fifth, fifth+octave, fifth, fifth+octave, fifth, fifth+octave, fifth, fifth+octave, 
octave, octave+octave, octave, octave+octave, octave, octave+octave, octave, octave+octave,
major2nd, major2nd+octave, major2nd, major2nd+octave, major2nd, major2nd+octave, major2nd, major2nd+octave};
memcpy(track, trackNO, 48);
for(i=0;i<48;i++){
 trackNL[i] = e;
}
trackSize = 48;


}




