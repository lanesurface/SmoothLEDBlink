/*
 * Demonstration of sinusoidal vs sawtooth waves for controlling
 * blink pattern of LEDs.
 */

#define LED_PIN 9
#define WAVELENGTH 5000
#define SAMPLE_RATE (WAVELENGTH / 10)

int (*get_led_lumosity)(int,
                        int,
                        int,
                        int);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);

  get_led_lumosity = get_stepped_lumosity;
}

void loop() {
  for (int i = 0; /* LOOP FOREVER */; i++) {
    int lum = get_led_lumosity(SAMPLE_RATE,
                               0,
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
int get_smooth_lumosity(int num_samples,
                        int min_value,
                        int max_value,
                        int loop_iteration) {
  int range = max_value - min_value;

  return (int)(abs(range * sin(PI
                               * (loop_iteration % num_samples)
                               / num_samples)) + min_value);
}

int get_stepped_lumosity(int num_samples,
                         int min_value,
                         int max_value,
                         int loop_iteration) {
  return (abs(loop_iteration
              % num_samples
              * max_value
              / num_samples) + min_value);
//  return (abs(max_value
//              * loop_iteration
//              * 2
//              / wavelength) + min_value) % 255;
}
