$fn = 90;

servo();

module servo(color = "#81a2be"){
	color(color){
		width = 18.7;
		
		mainBlock(width);
		axis(width);
		mounting(width);
		wire();
	}
	
	module mainBlock(width){
		length = 38.5;
		height = 35.1;
		translate([-length/2, -width/2, 0])
			cube([length, width, height]);
	}
	
	module axis(width){
		translate([9.8, 0, 0]){
			cylinder(d=width, h=37.5);
			difference(){
				cylinder(d=6, h=40.8);
				#cylinder(d=1, h=50);
			}
		}
	}
	
	module mounting(width){
		length = 54.4;
		translate([-length/2, -width/2, 26.6])
			cube([54.4, width, 5.5]);
	}
	
	
	module wire(){
		translate([27, 0, 0])
			rotate([0, 30, 0])
				cube([20, 4.4, 2], center=true);
	}
}
