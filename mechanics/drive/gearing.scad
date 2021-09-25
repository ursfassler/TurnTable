use <../lib/gears/gears.scad>

$fn = 90;

gearing(true);

module gearing(fitted=false){
	modul = 1;
	pressure_angle = 20;
	lead_angle = 10;
	
	gear();
	if(fitted){
		translate([56, 30.4, 10])
			rotate([90, 0, 0])
				wormGear();
	}
	else{
		translate([80, 0, 0])
			wormGear();
	}

	module gear(){
		width = 25;
		difference(){
			spur_gear(
				modul=modul,
				tooth_number=100,
				width=width,
				bore=3,
				pressure_angle=pressure_angle,
				helix_angle=-lead_angle,
				optimized=false);
		}
	}
	
	module wormGear(){
		difference(){
			worm(
				modul=modul,
				thread_starts=2,
				length=60,
				bore=0,
				pressure_angle=pressure_angle,
				lead_angle=lead_angle,
				together_built=true);
			#cylinder(d=4, h=10);
		}
	}
}
