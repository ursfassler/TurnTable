use <mocks/servo_modified.scad>
use <drive/gearing.scad>
use <servoHolder/servoHolder.scad>
use <wormGearHolder/wormGearHolder.scad>

translate([0, 0, 5]){
	gearing(fitted=true);
	direction = [-1, 1];
	for(n = [0:1]){
		translate([-65.3, direction[n]*67.5, 6.35])
			rotate([direction[n]*90, 0, 0])
				servo_modified(color=[0, 1, 0, 0.5]);
	}
}

translate([-85, -50, 11.3])
	rotate([0, 0, 90])
		servoHolder_double();

translate([-106, 50, 0])
	rotate([0, 0, 180])
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
