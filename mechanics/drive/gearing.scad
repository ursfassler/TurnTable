use <../lib/gears/gears.scad>

$fn = 90;

gearing(true);

module gearing(fitted=false){
	modul = 1;
	pressure_angle = 20;
	lead_angle = 10;
	
	translate([71, -50.6, 10])
		rotate([-90, 0, 0])
			smallGear();
	
	if(fitted){
		translate([56, 30.4, 10])
			rotate([90, 0, 0])
				wormGear();
	}
	else{
		translate([80, 0, 0])
			wormGear();
	}
	bigGear();
	
	
	module smallGear(){
		length = 20;
		difference(){
			spur_gear(
				modul=modul,
				tooth_number=15,
				width=20,
				bore=3,
				pressure_angle=pressure_angle,
				helix_angle=0,
				optimized=false);
			servoAxisFit();
			translate([0, 0, 3+1.2])
				cylinder(d=6, h=length);
		}
	}
	
	module wormGear(){
		wormLength = 60;
		gearLength = 12;
		difference(){
			union(){
				worm(
					modul=modul,
					thread_starts=2,
					length=wormLength,
					bore=0,
					pressure_angle=pressure_angle,
					lead_angle=lead_angle,
					together_built=true);
				translate([0, 0, wormLength])
					spur_gear(
						modul=modul,
						tooth_number=15,
						width=gearLength,
						bore=0,
						pressure_angle=pressure_angle,
						helix_angle=0,
						optimized=false);
			}
			cylinder(d=4, h=wormLength+gearLength);
		}
	}
	
	module bigGear(){
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
	
	module servoAxisFit(){
		toothAngle = 360/23;
		
		linear_extrude(3)
			for(angle = [0:toothAngle:360-toothAngle])
				rotate([0, 0, angle])
					tooth();
		
		module tooth(){
			triangle();
			rotate([180, 0, 0])
				triangle();
		}

		module triangle(){
			angleOverlap = 0.1;
			angle = toothAngle/2 + angleOverlap;
			innerRadius = 2.5;
			height = innerRadius * sin(angle);
			a = innerRadius * cos(angle);
			polygon([[0,0], [3.2,0], [a,height]]);
		}
	}
}
