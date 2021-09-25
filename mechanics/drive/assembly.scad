use <servo.scad>
use <gearing.scad>

gearing(togeth);

translate([15.5, -49, 0])
	rotate([90, 0, 180])
		servo(color=[0, 1, 0, 0.5]);

