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
