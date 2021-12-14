use <servo.scad>

servo_modified();

module servo_modified(color){
	difference(){
		servo(color);
		translate([25, 0, 30])
			cube([10, 30, 10], center=true);
	}
}
