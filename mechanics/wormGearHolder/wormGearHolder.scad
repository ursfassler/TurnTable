
wormGearHolder(false);

module wormGearHolder(fitted=false){
	$fn = 90;
	
	if(fitted){
		mount();
		translate([5.5, 0, 15.35])
			rotate([90, 0, 0])
				axisHolder();
	}
	else{
		mount();
		translate([0, 10, 0])
			axisHolder();
	}
	
	module mount(){
		width = 25;
		length = 25;
		height = 25;
		difference(){
			translate([0, -length, 0])
				cube([width, length, height]);
			
			sideLength = 11;
			translate([0, -sideLength, 10])
				#cube([sideLength, sideLength, sideLength]);
			translate([sideLength, -6, 15])
				rotate([0, 90, 0]){
					#cylinder(d=9, h=4, $fn=6);
					#cylinder(d=5, h=width);
				}
				
			for(x = [6, 19]){
				translate([x, -length+7, 0])
					screwHole();
			}
		}
		
		module screwHole(){
			#cylinder(d=4.5, h=height);
			translate([0, 0, height-4.7])
				#cylinder(d1=3.2, d2=9, h=4.7);
		}
	}
	
	module axisHolder(){
		sideLength = 10;
		difference(){
			translate([-sideLength/2, -sideLength/2, 0])
				cube([sideLength, sideLength, sideLength]);
			#cylinder(d=6, h=sideLength);
		}
	}
}
