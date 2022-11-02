#include "MidiFile.h"

NAMESPACE_MIDI_BEGIN



String GetTimbreName(int i) {
	switch (i-1) {
		
		// Piano
		case 1: return "Acoustic Grand Piano";
		case 2: return "Acoustic Upright Piano";
		case 3: return "Electric Grand Piano";
		case 4: return "Honky-tonk Piano";
		case 5: return "Electric piano 1";
		case 6: return "Electric piano 2";
		case 7: return "Harpsichord";
		case 8: return "Clavinet";
		
		// Pitched percussion instrument|Chromatic Percussion
		case 9: return "Celesta";
		case 10: return "Glockenspiel";
		case 11: return "Music Box";
		case 12: return "Vibraphone";
		case 13: return "Marimba";
		case 14: return "Xylophone";
		case 15: return "Tubular Bells";
		case 16: return "Dulcimer";
		
		// Organ (music)|Organ
		case 17: return "Drawbar Organ"; // Hammond-like organ
		case 18: return "Percussive Organ"; // Hammond-like organ with harmonic percussion
		case 19: return "Rock Organ"; // Hammond-like organ with leslie speaker
		case 20: return "Pipe Organ"; // Church Organ
		case 21: return "Reed Organ"; // pump organ
		case 22: return "Accordion";
		case 23: return "Harmonica";
		case 24: return "Tango Accordion"; // Bandoneón
		
		// Guitar
		case 25: return "Nylon guitar"; // Classical guitar, Acoustic Guitar
		case 26: return "Acoustic guitar"; // Steel-string acoustic guitar, Acoustic Guitar
		case 27: return "Jazz guitar"; // Electric Guitar
		case 28: return "Clean electric guitar"; // Electric guitar
		case 29: return "Muted electrinc guitar"; // Electric Guitar, palm muted
		case 30: return "Overdriven guitar"; // Amp overdriven electric guitar
		case 31: return "Distorted guitar"; // Fuzzbox overdriven electric guitar
		case 32: return "Harmonic guitar"; // Electric guitar with harmonic pinch style playing
		
		// Bass (instrument)|Bass
		case 33: return "Acoustic Bass"; // Acoustic bass guitar
		case 34: return "Finger bass"; // Electric bass guitar played with fingers
		case 35: return "Picked bass"; // Electric bass guitar played with a pick
		case 36: return "Fretless Bass"; // Fretless bass guitar
		case 37: return "Slap Bass 1"; // Electric bass guitar played with slapping style
		case 38: return "Slap Bass 2";
		case 39: return "Synth Bass 1"; // Resonant bass with fast decay
		case 40: return "Synth Bass 2"; // Non-resonant bass without decay
		
		// String (music)|Strings
		case 41: return "Violin";
		case 42: return "Viola";
		case 43: return "Cello";
		case 44: return "Contrabass"; // Double bass
		case 45: return "Tremolo Strings";
		case 46: return "Pizzicato Strings";
		case 47: return "Orchestral Harp";
		case 48: return "Timpani";
		
		// Musical ensemble|Ensemble
		case 49: return "String Ensemble 1";
		case 50: return "String Ensemble 2";
		case 51: return "Synth Strings 1";
		case 52: return "Synth Strings 2";
		case 53: return "Choir Aahs";
		case 54: return "Choir Oohs";
		case 55: return "Synth Voice";
		case 56: return "Orchestra Hit";
		
		// Brass instrument|Brass
		case 57: return "Trumpet";
		case 58: return "Trombone";
		case 59: return "Tuba";
		case 60: return "Muted Trumpet";
		case 61: return "French Horn";
		case 62: return "Brass Section";
		case 63: return "Synth Brass 1";
		case 64: return "Synth Brass 2";
		
		// Reed aerophone|Reed
		case 65: return "Soprano Sax";
		case 66: return "Alto Sax";
		case 67: return "Tenor Sax";
		case 68: return "Baritone Sax";
		case 69: return "Oboe";
		case 70: return "English Horn";
		case 71: return "Bassoon";
		case 72: return "Clarinet";
		
		// Aerophone|Pipe
		case 73: return "Piccolo";
		case 74: return "Flute";
		case 75: return "Recorder";
		case 76: return "Pan Flute";
		case 77: return "Blown bottle";
		case 78: return "Shakuhachi";
		case 79: return "Whistle";
		case 80: return "Ocarina";
		
		// Synthesizer|Synth";: return "Lead instrument|Lead
		case 81: return "Square synth";
		case 82: return "Sawtooth synth";
		case 83: return "Calliope synth";
		case 84: return "Chiff synth";
		case 85: return "Charang synth";
		case 86: return "Space synth";
		case 87: return "Fifths synth";
		case 88: return "Bass and lead synth";
		
		// Synth pad|Synth Pad
		case 89: return "Fantasy pad";
		case 90: return "Warm pad";
		case 91: return "Polysynth pad";
		case 92: return "Choir pad";
		case 93: return "Bowed pad";
		case 94: return "Metallic pad";
		case 95: return "Halo pad";
		case 96: return "Sweep pad";
		
		// Synthesizer|Synth Effects
		case 97 : return "Rain FX";
		case 98: return "Soundtrack FX";
		case 99: return "Crystal FX";
		case 100: return "Atmosphere FX";
		case 101: return "Brightness FX";
		case 102: return "Goblins FX";
		case 103: return "Echo FX";
		case 104: return "Sci-fi FX";
		
		// World music|Ethnic
		case 105: return "Sitar";
		case 106: return "Banjo";
		case 107: return "Shamisen";
		case 108: return "Koto";
		case 109: return "Kalimba";
		case 110: return "Bag pipe";
		case 111: return "Fiddle";
		case 112: return "Shanai";
		
		// Percussion instrument|Percussive
		case 113: return "Wind chime";
		case 114: return "Agogo";
		case 115: return "Steel Drums";
		case 116: return "Woodblock";
		case 117: return "Taiko Drum";
		case 118: return "808-style tom drum";
		case 119: return "Synth Drum";
		case 120: return "Reverse Cymbal";
		
		// Sound effect|Sound Effects
		case 121: return "Guitar fret noise";
		case 122: return "Breathing noise";
		case 123: return "Seashore noise";
		case 124: return "Bird Tweet";
		case 125: return "Telephone Ring";
		case 126: return "Helicopter";
		case 127: return "Applause";
		case 128: return "Gun sound";
		
		default: return "<invalid>";
	}
}

NAMESPACE_MIDI_END
