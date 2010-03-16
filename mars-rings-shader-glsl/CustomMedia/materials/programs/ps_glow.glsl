// http://www.opengl.org/sdk/docs/tutorials/ClockworkCoders/loading.php
// http://www.ogre3d.org/docs/manual/manual_23.html#SEC125

// source of this file was the .cg example shader provided by:
// http://www.ogre3d.org/forums/viewtopic.php?p=304338
//
// all i did was to rewrite it to be used with glsl instead
uniform float alpha_value;
uniform float time;

void main()
{
   vec4 color;
   color.x = 0.0; // RED
   color.y = 1.0; // Green
   color.z = 0.0; // Blue

   // Transparencia
   color.w =  alpha_value * ((sin(time * 5.0) / 3.14 + 1.0) / 2.0 );

   // this sets the color
   gl_FragColor = color;
}
