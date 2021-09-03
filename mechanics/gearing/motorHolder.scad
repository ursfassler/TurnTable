$fn = 90;
height = 1;

difference(){
	union(){
		cube([60, 24, height], center=true);
		translate([12.5, 0, 5])
			cube([35, 24, 10], center=true);
	}
	translate([-20, 0, 0]){
		#cylinder(d=6.4, h=height, center=true);
		yAbs = 16.5/2;
		for(y = [-yAbs, yAbs]){
			translate([0, y, 0])
				#cylinder(d=2, h=height, center=true);
		}
	}
	translate([10, 0, 0]){
		#cylinder(d=1.7, h=25, center=true);
	}
}
