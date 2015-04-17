import processing.serial.*;

Serial port;
float playtime = 0;
boolean start = false;
boolean first = true;
int start_millis = 0;

void setup(){
  size(500,250);
  port = new Serial( this, "COM16", 9600);
  port.bufferUntil('\n');
  
  textFont( createFont("Monospaced.bold", 60));
}

void draw(){
  background(255, 255, 255);
  textAlign(CENTER);
  
  if(start){
    if(first){
      first = false;
      start_millis = millis();
    } else {
      playtime = millis() - start_millis;      
    }
  }
  fill(0, 0, 0);
  text(nf(int(playtime)/1000.0, 2, 3), width * 0.5, 100);
  
}

void serialEvent( Serial port ){
  String reading;
  
  reading = new String(port.readBytesUntil('\n'));
  print(reading);
  //println(reading.substring(0,1));
  
  if( reading.substring(0,1).equals("S") == true){
    start = true;
    println("Started");
  } else if (reading.substring(0, 1).equals("T") == true){
    start = false;
    first = true; 
    playtime = float( reading.substring(2) );
    println("SerialEvent" + playtime);
  }
}
