use <../lib/gears/gears.scad>

$fn = 90;

gearing(true);

module gearing(fitted=false){
	modul = 1;
	pressure_angle = 20;
	lead_angle = 10;
	
	gear();
	if(fitted){
		translate([56-100-12, -30.1, 10])
			rotate([-90, 0, 0])
				wormGear();
		guidingGears(fitted);
	}
	else{
		translate([100, 0, 0]){
			wormGear();
			guidingGears(fitted);
		}
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

	module guidingGears(fitted=true){
		angleOffset = -70;
		angleDelta = 120;
		rotate([0, 0, 10]){
			for(angle = [0:angleDelta:360-angleDelta]){
				rotate([0, 0, angle]){
					translate([60, 0, -2])
						spur_gear(
							modul=modul,
							tooth_number=20,
							width=15,
							bore=4,
							pressure_angle=pressure_angle,
							helix_angle=lead_angle,
							optimized=false);

				}
			}
			color("Gold", 0.8)
				if(fitted){
					holder();
				}
				else{
					translate([130, 0, 0])
						holder();
				}
		}

		module holder(){
			height = 25;
			translate([0, 0, height/2-5]){
				difference(){
					linear_extrude(height, center=true)
						polygon([[-40,-75], [50,-65], [90,0], [50,65], [-40,75]]);

					angleDelta = 120;
					for(angle = [0:angleDelta:360-angleDelta]){
						rotate([0, 0, angle])
							translate([60, 0, 0]){
								#cylinder(d=4, h=height, center=true);
								translate([0, 0, -2])
									#cylinder(d=26, h=17, center=true);
							}
					}

					translate([80, 0, 0])
						screwHole();
					yAbs = 63;
					for(y = [-yAbs, yAbs]){
						translate([-15, y, 0]){
							screwHole();
						}
					}

					#cylinder(d=3, h=height, center=true);

					translate([0, 0, 2])
						#cylinder(d=110, h=height, center=true);
				}
			}


			module screwHole(){
				#cylinder(d=4.5, h=height, center=true);
				translate([0, 0, height/2-4.7])
					#cylinder(d1=3.2, d2=9, h=4.7);
			}
		}
	}
}
