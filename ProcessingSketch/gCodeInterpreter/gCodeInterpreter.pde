PrintWriter outputCode;
String[] inputGcode, lineFromGcode;
PVector startVector, vector, voidVector, lastStartVector, lastMove;
float distance=0.0, angle=0.0, maxX=0.0, maxY=0.0, minX=0.0, minY=0.0, maxXOutput=480.0, maxYOutput=280.0, scale=1.0;
String outputName="output.txt";
boolean firstdraw=true;

public void settings() {
  size(800, 800);
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
  float x;
  float y;
  lastStartVector=new PVector(0, 0);
  lastMove=new PVector(0, 0);
  background(100);
  resetMatrix();
  //////////////Check dimension
   for (int i = 0; i < inputGcode.length; i++) {
    lineFromGcode = splitTokens(inputGcode[i]);
    if (lineFromGcode.length>=3) {
      if (lineFromGcode[0].equals("G1") || lineFromGcode[0].equals("G0")) {
        for (int j = 0; j < lineFromGcode.length; j++) {
          if (lineFromGcode[j].charAt(0) == 'X') {
            x = float(splitTokens(lineFromGcode[j], "X")[0]);
            if (x<minX) minX=x;
            if (x>maxX) maxX=x;
            for (int k = 0; k < lineFromGcode.length; k++) {
              if (lineFromGcode[k].charAt(0) == 'Y') {         
                y = float(splitTokens(lineFromGcode[k], "Y")[0]);
                if (y<minY) minY=y;
                if (y>maxY) maxY=y;
              }
            }
          }
        }
      }
    }
   }
   println("  *** Xmin : "+minX+"mm Xmax : "+maxX+"mm Ymin : "+minY+"mm Ymax : "+maxY+"mm ");
   println("  *** Drawing size : "+(maxX-minX)+"mm x "+(maxY-minY)+"mm");
   //maxXOutput=480.0, maxYOutput=280.0, scale=1.0
   if (maxX>maxXOutput) scale=maxXOutput/maxX;
   if (maxY>maxYOutput && scale>maxYOutput/maxY) {
     scale=maxYOutput/maxY;
   }
   println("  *** After scale up/down : "+(maxX-minX)*scale+"mm x "+(maxY-minY)*scale+"mm");
   ///////////////////////////////////////

  for (int i = 0; i < inputGcode.length; i++) {
    lineFromGcode = splitTokens(inputGcode[i]);
    if (lineFromGcode.length>0) {
      if (lineFromGcode[0].equals("G10")) outputCode.println("penup();");
      if (lineFromGcode[0].equals("G11")) outputCode.println("pendown();");
    }
    if (lineFromGcode.length>=3) {
      if (lineFromGcode[0].equals("G1") || lineFromGcode[0].equals("G0")) {
        for (int j = 0; j < lineFromGcode.length; j++) {
          if (lineFromGcode[j].charAt(0) == 'X') {
            x = float(splitTokens(lineFromGcode[j], "X")[0]);
            if (x<minX) minX=x;
            if (x>maxX) maxX=x;
            for (int k = 0; k < lineFromGcode.length; k++) {
              if (lineFromGcode[k].charAt(0) == 'Y') {         
                y = float(splitTokens(lineFromGcode[k], "Y")[0]);
                if (y<minY) minX=y;
                if (y>maxY) maxX=y;
                startVector = new PVector (x, y);
              }
            }
          }
        }
      }
    }
    if (startVector!=voidVector) {
      vector=PVector.sub(startVector, lastStartVector);
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
      outputCode.println("forward("+scale*distance+");");

      if (angle>=PI) {
        rotate(-(PI-(angle-PI)));
      } else if (angle>=0 && angle< PI) {
        rotate((angle));
      } else if (angle<0 && angle> -PI) {
        rotate(angle);
      } else if (angle<=-PI) {
        rotate((PI+(angle+PI)));
      }
      translate(distance, 0);
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
