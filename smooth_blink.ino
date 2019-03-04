/*
 * Demonstration of sinusoidal vs sawtooth waves for controlling
 * blink pattern of LEDs.
 */

#define LED_PIN 9
#define WAVELENGTH 1000
#define SAMPLE_RATE 100 // The number of samples per wavelength

int (*get_led_lumosity)(int wavelength,
                        int min_value,
                        int max_value,
                        int loop_iteration);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);

  get_led_lumosity = get_stepped_lumosity;
}

void loop() {
  for (int i = 0; /* LOOP FOREVER */; i++) {
    int lum = get_led_lumosity(WAVELENGTH,
                               50,
                               255,
                               i);
    analogWrite(LED_PIN, lum);
    
    Serial.println(lum);

    delay(WAVELENGTH / SAMPLE_RATE);
  }
}

/*
 * For the given characteristics of the sinusoidal wave which is
 * used to control the blink pattern of the LED, and the loop
 * iteration, which is simply a counter which is incremented every
 * time the loop() function runs, this function will return the
 * luminosity of the LED. The luminosity is in the range
 * [min_value, max_value] and can be fed directly to a PWM-
 * compatible pin.
 */
int get_smooth_lumosity(int wavelength,
                        int min_value,
                        int max_value,
                        int loop_iteration) {
  int range = max_value - min_value;
  
  return (int)(abs(range * sin(loop_iteration
                               * 2
                               * PI
                               / wavelength)) + min_value);
}

int get_stepped_lumosity(int wavelength,
                         int min_value,
                         int max_value,
                         int loop_iteration) {
  return (abs(max_value
              * loop_iteration
              * 2
              / wavelength) + min_value) % 255;
}
