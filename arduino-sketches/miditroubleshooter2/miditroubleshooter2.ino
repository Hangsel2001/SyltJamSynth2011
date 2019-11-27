/*

Copyright 2011-2012 Davey Taylor

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "Synth.h"

#define SAMPLE_FREQ     44100

uint8_t pcm = 0, tick = 0;

uint8_t sample(void) {
  if(!pcm) tick++;
  return pcm++;
}

void setup(void) {
  Synth.attachInterrupt(sample, SAMPLE_FREQ);
  Synth.setResonance(0, 0x2F);
  Synth.setResonance(1, 0x01);
  Synth.setCutoff(0, 150);
  Synth.setCutoff(1, 600);  
  Serial.begin(115200);
}

void loop(void) {
  midi_t *midi = Synth.getMidi();
  Serial.print("loop");
  
  if( midi ) {
    Serial.print("Channel:");
    Serial.println(midi->channel);
    Serial.print("Message:");
    Serial.println(midi->message);
        Serial.print("data1:");
    Serial.println(midi->data1);
        Serial.print("data2:");
    Serial.println(midi->data2);
    Synth.freeMidi();
  }
}
