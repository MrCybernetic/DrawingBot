import controlP5.*;


float wheel_base = 116.0, distR=0.0, distL=0.0,alpha=0.0;
ControlP5 cp5;

public void settings() {
  size(800, 600);
}

public void setup() {
  cp5 = new ControlP5(this);
    // add a vertical slider
  cp5.addSlider("DistR")
     .setPosition(100,460)
     .setSize(400,40)
     .setRange(-500,500)
     .setValue(0)
     .setSliderMode(Slider.FLEXIBLE)
     ;
  cp5.addSlider("DistL")
     .setPosition(100,505)
     .setSize(400,40)
     .setRange(-500,500)
     .setValue(0)
     .setSliderMode(Slider.FLEXIBLE)
     ;
}
public void draw() {
  background(180);
  fill(#D81E0D);
  circle(300,200,10);
  fill(#0DD823);
  circle(300+wheel_base,200,10);


  fill(#D81E0D);
  circle(300+wheel_base-cos(distR/wheel_base-distL/wheel_base)*wheel_base,200+sin(distR/wheel_base-distL/wheel_base)*wheel_base,10);
  fill(#0DD823);
 circle(300+cos(-distL/wheel_base+distR/wheel_base)*wheel_base,200-sin(-distL/wheel_base-distR/wheel_base)*wheel_base,10);
}

void DistR(int DistRSet) {
  distR=DistRSet;
}

void DistL(int DistLSet) {
  distL=DistLSet;
}
