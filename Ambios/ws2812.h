// Useful typedefs
typedef unsigned char u_char;		// 8 bit
typedef unsigned int u_int;			// 16 bit

// Transmit codes
#define HIGH_CODE	(0xF0)			// b11110000
#define LOW_CODE	(0xC0)			// b11000000

// Configure processor to output to data strip
void initStrip(void);

// Send colors to the strip and show them. Disables interrupts while processing.
void showStrip(void);

// Set the color of a certain LED
void setLEDColor(u_int p, u_char r, u_char g, u_char b);

// Set the color of a certain LED
void setRColor(u_int p, u_char r);
// Set the color of a certain LED
void setBColor(u_int p, u_char b);
// Set the color of a certain LED
void setGColor(u_int p, u_char g);

// Clear the color of all LEDs (make them black/off)
void clearStrip(void);

// Fill the strip with a solid color. This will update the strip.
void fillStrip(u_char r, u_char g, u_char b);
