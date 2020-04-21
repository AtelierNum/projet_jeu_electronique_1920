/*
  El Jarabe Tapatío
  Play The Mexican Hat Dance on a piezo buzzer!
  For info and circuit diagrams see https://github.com/tardate/LittleArduinoProjects/tree/master/playground/JarabeTapatio
 */
// melody definition
// BPM followed by series of note definitions.
// Note definition as paired values: pitch, duration.
// Durations indicated as 4 = quarter note, 8 = eighth note, etc
int melody[] = {
  // beats per minute
  172,
  // note definitions as values: pitch, duration.
  NOTE_A5  , 8,
  NOTE_GS5 , 8,

  NOTE_A5  , 8,
  NOTE_FS5 , 8,
  NOTE_F5  , 8,
  NOTE_FS5 , 8,
  NOTE_D5  , 8,
  NOTE_CS5 , 8,

  NOTE_D5  , 8,
  NOTE_A4  , 4,
  NOTE_REST, 8,
  NOTE_FS4 , 8,
  NOTE_G4  , 8,

  NOTE_A4  , 8,
  NOTE_B4  , 8,
  NOTE_CS5 , 8,
  NOTE_D5  , 8,
  NOTE_E5  , 8,
  NOTE_FS5 , 8,

  NOTE_G5  , 8,
  NOTE_E5  , 4,
  NOTE_REST, 8,
  NOTE_G5  , 8,
  NOTE_FS5 , 8,

  NOTE_G5  , 8,
  NOTE_E5  , 8,
  NOTE_DS5 , 8,
  NOTE_E5  , 8,
  NOTE_CS5 , 8,
  NOTE_B4  , 8,

  NOTE_CS5 , 8,
  NOTE_A4  , 4,
  NOTE_REST, 8,
  NOTE_A5  , 8,
  NOTE_GS5 , 8,

  NOTE_A5  , 8,
  NOTE_B5  , 8,
  NOTE_A5  , 8,
  NOTE_G5  , 8,
  NOTE_FS5 , 8,
  NOTE_E5  , 8,

  NOTE_D5  , 2,
  NOTE_REST, 2,

  NOTE_A5  , 8,
  NOTE_GS5 , 8,

  NOTE_A5  , 8,
  NOTE_FS5 , 8,
  NOTE_F5  , 8,
  NOTE_FS5 , 8,
  NOTE_D5  , 8,
  NOTE_CS5 , 8,

  NOTE_D5  , 8,
  NOTE_A4  , 4,
  NOTE_REST, 8,
  NOTE_FS4 , 8,
  NOTE_G4  , 8,

  NOTE_A4  , 8,
  NOTE_B4  , 8,
  NOTE_CS5 , 8,
  NOTE_D5  , 8,
  NOTE_E5  , 8,
  NOTE_FS5 , 8,

  NOTE_G5  , 8,
  NOTE_E5  , 4,
  NOTE_REST, 8,
  NOTE_G5  , 8,
  NOTE_FS5 , 8,

  NOTE_G5  , 8,
  NOTE_E5  , 8,
  NOTE_DS5 , 8,
  NOTE_E5  , 8,
  NOTE_CS5 , 8,
  NOTE_B4  , 8,

  NOTE_CS5 , 8,
  NOTE_A4  , 4,
  NOTE_REST, 8,
  NOTE_A5  , 8,
  NOTE_GS5 , 8,

  NOTE_A5  , 8,
  NOTE_B5  , 8,
  NOTE_A5  , 8,
  NOTE_G5  , 8,
  NOTE_FS5 , 8,
  NOTE_E5  , 8,

  NOTE_D5  , 2,
  NOTE_REST, 2,

  NOTE_A5  , 8,
  NOTE_GS5 , 8,

  NOTE_A5  , 8,
  NOTE_FS5 , 8,
  NOTE_F5  , 8,
  NOTE_FS5 , 8,
  NOTE_D5  , 8,
  NOTE_CS5 , 8,

  NOTE_D5  , 8,
  NOTE_A4  , 4,
  NOTE_REST, 8,
  NOTE_FS4 , 8,
  NOTE_G4  , 8,

  NOTE_A4  , 8,
  NOTE_B4  , 8,
  NOTE_CS5 , 8,
  NOTE_D5  , 8,
  NOTE_E5  , 8,
  NOTE_FS5 , 8,

  NOTE_G5  , 8,
  NOTE_E5  , 4,
  NOTE_REST, 8,
  NOTE_G5  , 8,
  NOTE_FS5 , 8,

  NOTE_G5  , 8,
  NOTE_E5  , 8,
  NOTE_DS5 , 8,
  NOTE_E5  , 8,
  NOTE_CS5 , 8,
  NOTE_B4  , 8,

  NOTE_CS5 , 8,
  NOTE_A4  , 4,
  NOTE_REST, 8,
  NOTE_A5  , 8,
  NOTE_GS5 , 8,

  NOTE_A5  , 8,
  NOTE_B5  , 8,
  NOTE_A5  , 8,
  NOTE_G5  , 8,
  NOTE_FS5 , 8,
  NOTE_E5  , 8,

  NOTE_D5  , 2,
  NOTE_REST, 2,

  NOTE_A5  , 8,
  NOTE_GS5 , 8,

  NOTE_A5  , 8,
  NOTE_FS5 , 8,
  NOTE_F5  , 8,
  NOTE_FS5 , 8,
  NOTE_D5  , 8,
  NOTE_CS5 , 8,

  NOTE_D5  , 8,
  NOTE_A4  , 4,
  NOTE_REST, 8,
  NOTE_FS4 , 8,
  NOTE_G4  , 8,

  NOTE_A4  , 8,
  NOTE_B4  , 8,
  NOTE_CS5 , 8,
  NOTE_D5  , 8,
  NOTE_E5  , 8,
  NOTE_FS5 , 8,

  NOTE_G5  , 8,
  NOTE_E5  , 4,
  NOTE_REST, 8,
  NOTE_G5  , 8,
  NOTE_FS5 , 8,

  NOTE_G5  , 8,
  NOTE_E5  , 8,
  NOTE_DS5 , 8,
  NOTE_E5  , 8,
  NOTE_CS5 , 8,
  NOTE_B4  , 8,

  NOTE_CS5 , 8,
  NOTE_A4  , 4,
  NOTE_REST, 8,
  NOTE_A5  , 8,
  NOTE_GS5 , 8,

  NOTE_A5  , 8,
  NOTE_B5  , 8,
  NOTE_A5  , 8,
  NOTE_G5  , 8,
  NOTE_FS5 , 8,
  NOTE_E5  , 8,

  NOTE_D5  , 2,
  NOTE_REST, 2

};
