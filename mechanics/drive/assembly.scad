use <servo.scad>
use <gearing.scad>

translate([0, 0, 5]){
	gearing(fitted=true);
	translate([80.75, -69.3, 10])
		rotate([90, 0, 180])
			servo(color=[0, 1, 0, 0.5]);
}

bottom();
ceiling();


module bottom(){
	thickness = 10;
	translate([0, 0, -thickness/2])
		color([0, 0, 1, 0.5])
			cube([200, 200, thickness], center=true);
}

module ceiling(){
	thickness = 10;
	translate([0, 0, 30+thickness/2])
		color([0, 0, 1, 0.5])
			cube([200, 200, thickness], center=true);
}
