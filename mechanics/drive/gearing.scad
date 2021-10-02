use <../lib/gears/gears.scad>

$fn = 90;

gearing(false);

module gearing(fitted=false){
	modul = 1;
	pressure_angle = 20;
	lead_angle = 10;
	
	gear();
	if(fitted){
		translate([56, -30.1, 10])
			rotate([-90, 0, 0])
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
			dAngle = 120;
			for(angle = [0:dAngle:360-dAngle])
				rotate([0, 0, angle])
					translate([35, 0, 0]){
						#cylinder(d=4.5, h=width);
						#cylinder(d1=9, d2=3.2, h=4.5);
					}
			translate([0, 0, -2])
				#cylinder(d=40, h=width);
		}
	}
	
	module wormGear(){
		length = 60;
		difference(){
			worm(
				modul=modul,
				thread_starts=2,
				length=length,
				bore=0,
				pressure_angle=pressure_angle,
				lead_angle=lead_angle,
				together_built=true);
			
			servoFitHeight = 3.2;
			#servoAxisFit(servoFitHeight);
			
			holdingHoleHeight = 4.7;
			#cylinder(d=4, h=holdingHoleHeight+servoFitHeight);
			
			translate([0, 0, holdingHoleHeight+servoFitHeight])
				#cylinder(d=6, h=length);
		}
	}
	
	module servoAxisFit(height=3){
		toothAngle = 360/23;
		
		linear_extrude(height)
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
