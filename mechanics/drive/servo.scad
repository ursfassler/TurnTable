$fn = 90;

blockLength = 38.5;
width = 18.7;
blockHeight = 37.4;
cube([blockLength, width, blockHeight], center=true);
translate([0, 0, 25.8-blockHeight/2])
	cube([54.4, width, 5.5], center=true);
translate([blockLength/2-9.5, 0, blockHeight/2])
	cylinder(d=6, h=3.4);
translate([29, 0, -16])
	cube([20, 4.4, 2], center=true);
	
