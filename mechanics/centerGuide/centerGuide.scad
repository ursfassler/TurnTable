$fn = 90;

lowerDiameter = 26;
height = 10;
difference(){
	cylinder(d=30, h=height, center=true);
	for(a = [0, 120, 240])
		rotate([0, 0, a])
			translate([10, 0, 0]){
				#cylinder(d=3.8, h=height, center=true);
				coneHeight = 3.9;
				translate([0, 0, height/2-coneHeight])
					#cylinder(d1=3.8, d2=7.9, h=coneHeight);
			}
	#cylinder(d=6, h=height, center=true);
}
