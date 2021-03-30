
void setup() {
  // put your setup code for core 0 here, to run once:
  Serial.begin(9600);
  Serial.println("BEGIN");
  /*initialize_terminal();
  RegFile_init();
  RegFile_new_SampleRegister(20,20);
  for(int i = 0; i<100; i++){
    RegFile_write_SampleRegister(0);
  }*/
}


void loop() {
  // put your main code for core 0 here, to run repeatedly:
  //loop_terminal();
  char c = Serial.read();
  if(c!=0) Serial.println(c);
}
