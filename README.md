# DrawingBot
Drawing bot

Workflow to draw some TSP art : 
- Find a B&W image
- Use CyberStippleGen to create gCode
- Use GCodeInterpreter to create path
- If you want, you can check the paths with ProgramDebug
- Replace in the Arduino sketch, the paths by yours (Think about the pen)

Workflow to draw some simple paths :
- Open the Arduino Sketch, replace the paths in the loop by whatever you want

