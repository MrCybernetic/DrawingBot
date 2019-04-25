import controlP5.*;

ControlP5 cp5;
int inputProgramLimit = 0;

String[] inputProgram;
String[] lineFromInputProgram;
PVector vStart, vEnd,voidvector;
String[] sTranslateValue, sRightBValue, sLeftValue, sMoveWheelsValue;
String  sWheelsL, sWheelsR;
float fTranslateValue, fRightBValue, fLeftValue, fWheelsL, fWheelsR;
float wheel_base=116.0;
float alpha;
float angleSum;
boolean redraw = true, pause=false;
int value=500;
float[] positionNow={0.0,0.0,0.0};
PImage img;
PGraphics botLayer;
PGraphics pathLayer;

public void settings() {
  size(800, 600);
  noSmooth();

}

public void setup() {
  
  botLayer = createGraphics(width, height);
  pathLayer = createGraphics(width, height);
  
  botLayer.imageMode(CENTER);
 // pathLayer.imageMode(CENTER);
  img = loadImage("bot.png");
  imageMode(CENTER);
  cp5 = new ControlP5(this);
  inputProgram = loadStrings("output.txt");
  inputProgramLimit=inputProgram.length;
  background(80);
  vStart=new PVector (positionNow[0],positionNow[1]);
  angleSum=positionNow[2];
  strokeWeight(3);
    // add a vertical slider
  cp5.addSlider("slider")
     .setPosition(300,505)
     .setSize(400,40)
     .setRange(0,inputProgram.length)
     .setValue(inputProgram.length)
     .setSliderMode(Slider.FLEXIBLE)
     ;
  cp5.addButton("Play")
     .setValue(0)
     .setPosition(240,505)
     .setSize(50,40)
     ;
     value=0;
}

public void draw() {
  init();
  background(80);
  for (int i = 0 ; i < inputProgramLimit; i++) {
    lineFromInputProgram = splitTokens(inputProgram[i]);
    sTranslateValue = match(lineFromInputProgram[0], "forward(.*?);");
    sRightBValue = match(lineFromInputProgram[0], "right(.*?);");
    sLeftValue = match(lineFromInputProgram[0], "left(.*?);");
    sMoveWheelsValue = match(lineFromInputProgram[0], "moveWheelsRL(.*?);"); 
    if (sRightBValue != null) { 
      fRightBValue=radians(float(sRightBValue[1].substring(1, sRightBValue[1].length()-1))); 
      angleSum+=fRightBValue;
      positionNow[2]+=fRightBValue;
    }
    if (sLeftValue != null) { 
      fLeftValue=radians(float(sLeftValue[1].substring(1, sLeftValue[1].length()-1))); 
      angleSum-=fLeftValue;
      positionNow[2]-=fLeftValue;
      positionNow[2]=positionNow[2]%(2*PI);
    }
    if (sTranslateValue != null) { 
      
      fTranslateValue=float(sTranslateValue[1].substring(1, sTranslateValue[1].length()-1));
      positionNow[0]+=fTranslateValue*cos(angleSum);
      positionNow[1]+=fTranslateValue*sin(angleSum);
      pathLayer.beginDraw();
      pathLayer.strokeWeight(3);
      pathLayer.line(vStart.x,vStart.y,vStart.x+fTranslateValue*cos(angleSum),vStart.y+fTranslateValue*sin(angleSum));
      vStart = new PVector(vStart.x+fTranslateValue*cos(angleSum),vStart.y+fTranslateValue*sin(angleSum));
      pathLayer.endDraw();
    }
    /*if (sMoveWheelsValue != null) { 
      String[] stringTemp=split(sMoveWheelsValue[1].substring(1, sMoveWheelsValue[1].length()-1),',');
      sWheelsL= stringTemp[1];
      sWheelsR= stringTemp[0];
      fWheelsL=float(sWheelsL);
      fWheelsR=float(sWheelsR);
      alpha=abs(fWheelsR-fWheelsL)/wheel_base;
      if ((fWheelsR<=0 && fWheelsL<=0 && fWheelsR<fWheelsL)) {
        alpha*=-1;
      } 
      println(fWheelsR);
      println(fWheelsL);
      println(alpha);
      println("--------");
      pathLayer.beginDraw();
      pathLayer.strokeWeight(3);
      pathLayer.noFill();
      if (positionNow[2]>0) {
        pathLayer.arc(positionNow[0]+cos(alpha)*((fWheelsR+fWheelsL)/(2.0*alpha)), positionNow[1]+sin(alpha)*((fWheelsR+fWheelsL)/(2.0*alpha)), ((fWheelsR+fWheelsL)/(2.0*alpha))/alpha, ((fWheelsR+fWheelsL)/(2.0*alpha))/alpha, positionNow[2],positionNow[2]+alpha );
      } else {
        pathLayer.arc(positionNow[0]+cos(alpha)*((fWheelsR+fWheelsL)/(2.0*alpha)), positionNow[1]+sin(alpha)*((fWheelsR+fWheelsL)/(2.0*alpha)), ((fWheelsR+fWheelsL)/(2.0*alpha))/alpha, ((fWheelsR+fWheelsL)/(2.0*alpha))/alpha, positionNow[2]+alpha, positionNow[2]);
      }
      pathLayer.endDraw();
      positionNow[0]+=cos(alpha+angleSum)*((fWheelsR+fWheelsL)/(2.0*alpha));
      positionNow[1]+=sin(alpha+angleSum)*((fWheelsR+fWheelsL)/(2.0*alpha));
      positionNow[2]+=alpha;
      positionNow[2]=positionNow[2]%(2*PI);
      vStart = new PVector(vStart.x+cos(alpha+angleSum)*((fWheelsR+fWheelsL)/(2.0*alpha)),vStart.y+sin(alpha+angleSum)*((fWheelsR+fWheelsL)/(2.0*alpha)));
    } */
    
  }
  botLayer.beginDraw();
  botLayer.background(80);
  botLayer.endDraw();
  positionNow[2]=positionNow[2]%(2*PI);
  botLayer.beginDraw();
  botLayer.pushMatrix();
  botLayer.translate(positionNow[0],positionNow[1]);
  botLayer.rotate(positionNow[2]);
  botLayer.image(img, -13,0 );
  botLayer.popMatrix();
  botLayer.endDraw();
  image(botLayer, botLayer.width/2, botLayer.height/2);
  image(pathLayer, pathLayer.width/2, pathLayer.height/2);
  delay(10);
  
  if (!pause) {cp5.getController("slider").setValue(value);value++;}
  if (value>inputProgram.length) value=0;
  stroke(0);
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

}

void slider(int inputProgramLimitSet) {
  inputProgramLimit = inputProgramLimitSet;
  //value = inputProgramLimitSet;

}

public void Play() {
  pause=!pause;
}

void mousePressed() {
 /* fo debug purpose */
}

void init() {
  positionNow=new float[] {0.0,0.0,0.0};
  vStart=new PVector (0,0);
  sRightBValue=null;
  sLeftValue=null;
  sTranslateValue=null;
  vEnd=voidvector;
  fTranslateValue=0;
  fRightBValue=0;
  fLeftValue=0;
  angleSum=0;
}
