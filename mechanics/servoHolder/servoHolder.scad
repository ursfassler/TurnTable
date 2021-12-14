height = 23;
depth = 40;

servoHolder_double();

module servoHolder_double(){
	servoHolder();
	translate([100, 0, 0])
		rotate([0, 180, 0])
			servoHolder();
	
	translate([50, 0, 0])
		cube([50, depth, height], center=true);
}

module servoHolder(){
	$fn = 90;
	innerHeight = 19;
	servoHeight = 2;
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
		coneHeight = 4.7;
		#cylinder(d=4.5, h=height, center=true);
		zAbs = height/2-coneHeight;
		for(yFlip = [0, 180]){
			rotate([0, yFlip, 0])
				translate([0, 0, height/2-coneHeight])
					#cylinder(d1=3.2, d2=9, h=coneHeight);
		}
	}
}
