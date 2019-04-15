PrintWriter outputCode;
String[] inputGcode, lineFromGcode;
PVector startVector, vector, voidVector, lastStartVector, lastMove, pivotVector,vectortemp;
float distance=0.0, angle=0.0,x,y,iI,jJ,alpha,radius;
String outputName="output.txt";
boolean firstdraw=true,inverted=false;

public void settings() {
  size(1200, 1000);
}

void setup() {
  inputGcode = loadStrings("open742.gcode");
  selectInput("Select a gCode to process", "gCodeSelected");
  outputCode = createWriter(outputName); 
  noStroke();
  noLoop();
  lastStartVector=new PVector(0, 0);
  lastMove=new PVector(0, 0);
}

void draw() {
  lastStartVector=new PVector(0, 0);
  lastMove=new PVector(0, 0);
  background(100);
  translate(670,0);
  //rotate(PI);
  for (int i = 0; i < inputGcode.length; i++) {
    lineFromGcode = splitTokens(inputGcode[i]);
    if (lineFromGcode.length>0) {
      if (lineFromGcode[0].equals("G10")) outputCode.println("penup();");
      if (lineFromGcode[0].equals("G11")) outputCode.println("pendown();");
      /*
      Add Z management too
      */
    }
    if (lineFromGcode.length>=3) {
      if (lineFromGcode[0].equals("G02") || lineFromGcode[0].equals("G03") || lineFromGcode[0].equals("G2") ||lineFromGcode[0].equals("G3")) {
        for (int j = 0; j < lineFromGcode.length; j++) {
          if (lineFromGcode[j].charAt(0) == 'X') {
            x = float(splitTokens(lineFromGcode[j], "X")[0]);
            for (int k = 0; k < lineFromGcode.length; k++) {
              if (lineFromGcode[k].charAt(0) == 'Y') { 
                y = float(splitTokens(lineFromGcode[k], "Y")[0]);
                for (int l = 0; l < lineFromGcode.length; l++) {
                  if (lineFromGcode[l].charAt(0) == 'I') { 
                    iI = float(splitTokens(lineFromGcode[l], "I")[0]);
                    for (int m = 0; m < lineFromGcode.length; m++) {
                      if (lineFromGcode[m].charAt(0) == 'J') { 
                        jJ = float(splitTokens(lineFromGcode[m], "J")[0]);
                        pivotVector = new PVector(iI,jJ);
                        startVector = new PVector(x,y);
                        if (lineFromGcode[0].equals("G03") || lineFromGcode[0].equals("G3")) {
                          inverted=true;
                        } else {
                          inverted=false;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      if (lineFromGcode[0].equals("G01") || lineFromGcode[0].equals("G00") || lineFromGcode[0].equals("G1") || lineFromGcode[0].equals("G0")) {
        for (int j = 0; j < lineFromGcode.length; j++) {
          if (lineFromGcode[j].charAt(0) == 'X') {
            x = float(splitTokens(lineFromGcode[j], "X")[0]);
            for (int k = 0; k < lineFromGcode.length; k++) {
              if (lineFromGcode[k].charAt(0) == 'Y') {         
                y = float(splitTokens(lineFromGcode[k], "Y")[0]);
                startVector = new PVector (x, y);
              }
            }
          }
        }
      }
    }
    if ((pivotVector!=voidVector) && (startVector!=voidVector)) {    
      vector=new PVector(startVector.x-lastStartVector.x, startVector.y-lastStartVector.y);
      angle=(vector.heading()-lastMove.heading());
      /*if (angle>=PI) {
        outputCode.println("left("+degrees(2*PI-angle)+");");
      } else if (angle>=0 && angle< PI) {
        outputCode.println("right("+degrees(angle)+");");
      } else if (angle<0 && angle> -PI) {
        outputCode.println("left("+degrees(-angle)+");");
      } else if (angle<=-PI) {
        outputCode.println("right("+degrees(2*PI+angle)+");");
      }*/

      if (angle>=PI) {
        rotate(-(PI-(angle-PI)));
      } else if (angle>=0 && angle< PI) {
        rotate(angle);
      } else if (angle<0 && angle> -PI) {
        rotate(angle);
      } else if (angle<=-PI) {
        rotate((PI+(angle+PI)));
      }
      translate(vector.mag(),0);
      vectortemp= new PVector(pivotVector.x+startVector.x-lastStartVector.x,pivotVector.y+startVector.y-lastStartVector.y);
      alpha=(vectortemp.heading()-pivotVector.heading());
      noFill();
      stroke(cos(i/((float)inputGcode.length)*2*PI)*255, cos(i/((float)inputGcode.length)*2*PI+2*PI/3)*255, cos(i/((float)inputGcode.length)*2*PI+4*PI/3)*255);
      strokeWeight(2);
      if (!inverted) {
        if (((PI/2.0)-(PI/2.0+alpha))<=0) {
          arc(0, -pivotVector.mag(), pivotVector.mag()*2.0, pivotVector.mag()*2.0,PI/2.0,PI/2.0+alpha);
          outputCode.println("moveWheelsRL("+alpha+"*("+pivotVector.mag()+"-wheel_base/2.0),"+alpha+"*("+pivotVector.mag()+"+wheel_base/2.0));");
        } else {
          arc(0, -pivotVector.mag(), pivotVector.mag()*2.0, pivotVector.mag()*2.0,PI/2.0,PI/2.0+alpha+2*PI);
          float angletemp = alpha+2*PI;
          outputCode.println("moveWheelsRL("+angletemp+"*("+pivotVector.mag()+"-wheel_base/2.0),"+angletemp+"*("+pivotVector.mag()+"+wheel_base/2.0));");
        }
      } else {
        if (PI+PI/2.0+alpha-(PI+PI/2.0)<=0) {
          arc(0, pivotVector.mag(), pivotVector.mag()*2.0, pivotVector.mag()*2.0,3*PI/2.0+alpha,3*PI/2.0);
          float angletemp = abs(alpha);
          outputCode.println("moveWheelsRL("+angletemp+"*("+pivotVector.mag()+"+wheel_base/2.0),"+angletemp+"*("+pivotVector.mag()+"-wheel_base/2.0));");
        } else {
          arc(0, pivotVector.mag(), pivotVector.mag()*2.0, pivotVector.mag()*2.0,3*PI/2.0+alpha-2*PI,3*PI/2.0);
          float angletemp = abs(alpha-2*PI);
          outputCode.println("moveWheelsRL("+angletemp+"*("+pivotVector.mag()+"+wheel_base/2.0),"+angletemp+"*("+pivotVector.mag()+"-wheel_base/2.0));");
        }
      }
      noStroke();
      fill(cos(i/((float)inputGcode.length)*2*PI)*255, cos(i/((float)inputGcode.length)*2*PI+2*PI/3)*255, cos(i/((float)inputGcode.length)*2*PI+4*PI/3)*255);
      circle(0, 0, cos(i/((float)inputGcode.length)*2*PI)*5+10);
      if (i==1) {
        fill(0, 0, 0);
        textSize(300);
        text("Origin", 30, 30);
      }
      lastStartVector=startVector;
      startVector=voidVector;
      lastMove=vector;
      pivotVector=voidVector;
    }
    
    if (startVector!=voidVector) {
      vector=new PVector(startVector.x-lastStartVector.x, startVector.y-lastStartVector.y);
      angle=(vector.heading()-lastMove.heading());
      distance=vector.mag();

      if (angle>=PI) {
        outputCode.println("left("+degrees(2*PI-angle)+");");
      } else if (angle>=0 && angle< PI) {
        outputCode.println("right("+degrees(angle)+");");
      } else if (angle<0 && angle> -PI) {
        outputCode.println("left("+degrees(-angle)+");");
      } else if (angle<=-PI) {
        outputCode.println("right("+degrees(2*PI+angle)+");");
      }
      outputCode.println("forward("+distance+");");

      if (angle>=PI) {
        rotate(-(PI-(angle-PI)));
      } else if (angle>=0 && angle< PI) {
        rotate(angle);
      } else if (angle<0 && angle> -PI) {
        rotate(angle);
      } else if (angle<=-PI) {
        rotate((PI+(angle+PI)));
      }
      translate(distance*3, 0);
      fill(cos(i/((float)inputGcode.length)*2*PI)*255, cos(i/((float)inputGcode.length)*2*PI+2*PI/3)*255, cos(i/((float)inputGcode.length)*2*PI+4*PI/3)*255);
      circle(0, 0, cos(i/((float)inputGcode.length)*2*PI)*5+10);
      if (i==1) {
        fill(0, 0, 0);
        textSize(80);
        text("Origin", 30, 30);
      }
      lastStartVector=startVector;
      lastMove=vector;
      startVector=voidVector;
      pivotVector=voidVector;
    }
  }
  outputCode.flush(); // Writes the remaining data to the file
  outputCode.close(); // Finishes the file
  println("Done.");
}

void gCodeSelected(File gCode) {
  if (gCode == null) {
    println("Window was closed or the user hit cancel.");
  } else {
    inputGcode = loadStrings(gCode.getAbsolutePath());
    println("In progress... ");
    firstdraw=false;
    outputCode = createWriter(outputName);
    redraw();
  }
}
