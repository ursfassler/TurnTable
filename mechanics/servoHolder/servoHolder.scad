servoHolder();

module servoHolder(){
	$fn = 90;
	depth = 40;
	height = 27;
	innerHeight = 19;
	servoHeight = 6;
	difference(){
		cube([50, depth, height], center=true);
		translate([0, -10, (innerHeight-height)/2+servoHeight])
			#cube([35, 20, innerHeight], center=true);
		translate([12.5, 0, (innerHeight-height)/2+servoHeight])
			#cube([10, depth, innerHeight], center=true);
		
		translate([-10, 10, 0]){
			screwHole();
		}
	}

	module screwHole(){
		#cylinder(d=4.5, h=height, center=true);
		translate([0, 0, height/2-4.7])
			#cylinder(d1=3.2, d2=9, h=4.7);
	}
}
