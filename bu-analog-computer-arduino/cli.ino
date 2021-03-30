#define LINE_BUF_SIZE 128   //Maximum input string length
#define ARG_BUF_SIZE 64     //Maximum argument string length
#define MAX_NUM_ARGS 8      //Maximum number of arguments
 
int LEDpin = 13;
int blink_cycles = 10;      //How many times the LED will blink
bool error_flag = false;
 
char line[LINE_BUF_SIZE];
char args[MAX_NUM_ARGS][ARG_BUF_SIZE];
 
//Function declarations
int cmd_help();
int cmd_led();
int cmd_exit();
 
//List of functions pointers corresponding to each command
int (*commands_func[])(){
    &cmd_help,
    &cmd_led,
    &cmd_exit
};
 
//List of command names
const char *commands_str[] = {
    "help",
    "led",
    "exit"
};
 
//List of LED sub command names
const char *led_args[] = {
    "on",
    "off",
    "blink"
};
 
int num_commands = sizeof(commands_str) / sizeof(char *);
 
void setup() {
    Serial.begin(115200);
    pinMode(13, OUTPUT);
 
    cli_init();
}
 
void loop() {
    my_cli();
}
