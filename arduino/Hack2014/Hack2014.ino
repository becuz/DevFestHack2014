const int xPin = 2;
const int yPin = 1;
const int zPin = 0;

const int minVal = 270;
const int maxVal = 400;

void setup()
{
  while(!Serial);
  Serial.begin(9600);          //  setup serial
}

void loop()
{
  int x = analogRead(xPin);
  int y = analogRead(yPin);
  int z = analogRead(zPin);
  //Serial.print(x);Serial.print(" ");Serial.print(y);Serial.print(" ");Serial.print(z);Serial.println();
  Serial.println(getCurrentSide(x, y, z));
  delay(5);
}


unsigned int getCurrentSide(int xRead, int yRead, int zRead){
  
  //convert read values to degrees -90 to 90
  int xAng = map(xRead, minVal, maxVal, -90, 90);
  int yAng = map(yRead, minVal, maxVal, -90, 90);
  int zAng = map(zRead, minVal, maxVal, -90, 90);
  
  //calculate the differences between actual axis values and ideal positions values
  int diffs[6] = {
    abs((zAng+90) - 180),  //cube z axis on side 1 has degree 90
    abs((yAng+90) - 180),  //cube y axis on side 2 has degree 90
    abs((xAng+90) - 0),    //cube x axis on side 3 has degree -90
    abs((xAng+90) - 180),  //cube x axis on side 4 has degree 90
    abs((yAng+90) - 0),    //cube y axis on side 5 has degree -90
    abs((zAng+90) - 0)     //cube z axis on side 6 has degree -90
  };
  
  //get the most looking up side
  int minDiff = 999;
  int minIndex = -1;
  for(int i=0; i<6; i++){
    if (diffs[i] < minDiff){
      minDiff = diffs[i];
      minIndex = i;
    }  
  }
  return minIndex+1;
}
