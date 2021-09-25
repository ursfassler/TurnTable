use <../lib/gears/gears.scad>

gearing();

module gearing(){
	worm_gear(
		modul=1,
		tooth_number=100,
		thread_starts=2,
		width=10,
		length=60,
		worm_bore=1,
		gear_bore=3,
		pressure_angle=10,
		lead_angle=10,
		optimized=true,
		together_built=true);
}
	