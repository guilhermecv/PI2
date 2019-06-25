int machine_state;
int led_clk_div;
int display_clk_div;

enum states
{
  WAITING,
  RUNNING,
  CHECK_VOLUME,
  CHECK_COLOR,
  CHECK_TEMP,
  CHECK_OCR,
  ERROR,
}states;

struct process
{
  int ok;
  int n_ok;
  int total;
}process;

// Armazena as cores
struct{
	int red;
	int green;
	int blue;
}color;
