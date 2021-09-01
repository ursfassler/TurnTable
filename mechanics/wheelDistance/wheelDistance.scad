$fn = 90;

height = 17;
lowerDiameter = 26;
bottomHeight = 10;
difference(){
	union(){
		cylinder(d1=lowerDiameter, d2=26, h=height, center=true);
		translate([0, 0, bottomHeight/2-height/2])
			cube([45, 15, bottomHeight], center=true);
	}
	translate([0, 0, bottomHeight])
		#cube([10, lowerDiameter, height], center=true);
	xAbs = 10;
	for(x = [-xAbs, xAbs])
		translate([x, 0, 0])
			#cylinder(d=1.5, h=height, center=true);
	xAbs2 = 17;
	for(x = [-xAbs2, xAbs2])
		translate([x, 0, 0]){
			#cylinder(d=3.8, h=height, center=true);
			coneHeight = 3.9;
			translate([0, 0, -height/2+bottomHeight-coneHeight])
				#cylinder(d1=3.8, d2=7.9, h=coneHeight);
		}
}
