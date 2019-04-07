String[] inputProgram;
String[] lineFromInputProgram;
PVector vStart, vEnd;
String[] sTranslateValue, sRightBValue, sLeftValue;
float fTranslateValue, fRightBValue, fLeftValue;
float angleSum;

public void settings() {
  size(800, 600);
  noSmooth();

}

public void setup() {
  inputProgram = loadStrings("output.txt");
  background(80);
  noLoop();
  vStart=new PVector (0,0);
  angleSum=0;
  strokeWeight(3);
  
}

public void draw() {
  translate(10,10);
  //A4
  line(0,0,210,0);
  line(210,0,210,297);
  line(210,297,0,297);
  line(0,297,0,0);
  text("A4",5,292);
  //A3
  line(0,0,297,0);
  line(297,0,297,420);
  line(297,420,0,420);
  line(0,420,0,0);
  text("A3",5,415);
  //A2
  
  translate(30,80);
  for (int i = 0 ; i < inputProgram.length; i++) {
    lineFromInputProgram = splitTokens(inputProgram[i]);
    sTranslateValue = match(lineFromInputProgram[0], "forward(.*?);");
    sRightBValue = match(lineFromInputProgram[0], "right(.*?);");
    sLeftValue = match(lineFromInputProgram[0], "left(.*?);");
    
    if (sRightBValue != null) { 
      fRightBValue=radians(float(sRightBValue[1].substring(1, sRightBValue[1].length()-1))); 
      angleSum+=fRightBValue;
      println(sRightBValue[1].substring(1, sRightBValue[1].length()-1));
    }
    if (sLeftValue != null) { 
      fLeftValue=radians(float(sLeftValue[1].substring(1, sLeftValue[1].length()-1))); 
      angleSum-=fLeftValue;
      println("fLeftValue "+sLeftValue[1].substring(1, sLeftValue[1].length()-1));
    }
    if (sTranslateValue != null) { 
      fTranslateValue=float(sTranslateValue[1].substring(1, sTranslateValue[1].length()-1)); 
      stroke(random(255),random(255),random(255));
      line(vStart.x,vStart.y,vStart.x+fTranslateValue*cos(angleSum),vStart.y+fTranslateValue*sin(angleSum));
      vStart = new PVector(vStart.x+fTranslateValue*cos(angleSum),vStart.y+fTranslateValue*sin(angleSum));
      println("translate "+sTranslateValue[1].substring(1, sTranslateValue[1].length()-1));
    } 
  }
  
}
