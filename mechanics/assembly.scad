use <mocks/servo.scad>
use <drive/gearing.scad>
use <servoHolder/servoHolder.scad>
use <wormGearHolder/wormGearHolder.scad>

translate([0, 0, 5]){
	gearing(fitted=true);
	
	translate([-59, -78.4, 10])
		rotate([-90, 0, 5])
			servo(color=[0, 1, 0, 0.5]);	
}

translate([-80, -62.5, 13.5])
	rotate([0, 0, 95])
		servoHolder();

translate([-52, 20.5, 0])
	rotate([0, 0, 185])
		wormGearHolder(fitted=true);

bottom();
//ceiling();


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
