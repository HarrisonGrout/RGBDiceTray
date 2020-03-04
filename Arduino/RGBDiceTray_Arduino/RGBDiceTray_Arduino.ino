#include <FastLED.h>
#include <SoftwareSerial.h>

#define LED_PIN     5
#define NUM_LEDS    30
#define BRIGHTNESS  255
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myWhitePalette;
extern const TProgmemPalette16 myWhitePalette_p PROGMEM;

CRGBPalette16 White_p = CRGBPalette16(CRGB::White, CRGB::White, CRGB::White, CRGB::White);
CRGBPalette16 Black_p = CRGBPalette16(CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black);
CRGBPalette16 Red_p = CRGBPalette16(CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red);
CRGBPalette16 Green_p = CRGBPalette16(CRGB::Green, CRGB::Green, CRGB::Green, CRGB::Green);
CRGBPalette16 Blue_p = CRGBPalette16(CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::Blue);
CRGBPalette16 BlueWhite_p = CRGBPalette16(CRGB::Blue, CRGB::Grey, CRGB::Blue, CRGB::Grey);
CRGBPalette16 Cyan_p = CRGBPalette16(CRGB::Cyan, CRGB::Cyan, CRGB::Cyan, CRGB::Cyan);

void setup() {
  delay(3000);

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );

  currentPalette = Green_p;
  currentBlending = LINEARBLEND;
  //currentBlending = NOBLEND;

  BT.begin(9600);
  BT.println("Arduino Connected. Enter corresponding option");
}

void loop() {
    if(BT.available()) {
        mode=(BT.read());




        currentPalette = Cyan_p;
    }
    
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    FillLEDsFromPaletteColors( startIndex);
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}
