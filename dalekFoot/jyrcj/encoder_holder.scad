$fn = 100;

difference() {
// main body
translate([-3, -(22.4+6)/2, 0]) cube([37+3, 22.4+6, 12]);


union() {
// main shaft
translate([11.3, 0, 0]) cylinder(100, 7, 7, true);

translate([22.33, 0, 0]) cylinder(100, 4.5/2, 4.5/2, true);

// suspension
translate([31.8, 8.5, 0]) translate([-10, -10, -20])cube([20, 20, 40]);;

// screw on gearboxc
translate([31.8, -8.5, 5]) union() { 
    translate([-10, -10, 0])cube([20, 20, 20]);
    cylinder(100, 3.1/2, 3.1/2, true);
}

//fix
translate([1, 0, 3])
rotate([90, 0, 0]) cylinder(100, 1.5, 1.5, true);

// screw for encoder

translate([11.3, 0, 0]) translate([0, 0, 12])
for (i = [0:3]) {
    rotate([0, 0, 45+i*90])
    translate([12, 0, 0])
    screw();
    
} // end of for



} // end of union

} // end of difference

// edge
difference () {
translate([-3, -(22.4+6)/2, -3]) cube([20+3, 22.4+6, 3]);

union() {
translate([0, -22.6/2, -3])cube([37, 22.6, 3]);
translate([-50, -3.5, -3]) cube([100, 7, 3]);
}
}

module screw()
{
    cylinder(100, 1.8/2, 1.8/2, true);
    translate([0, 0, -1])cylinder(1, 1.8/2, 2.8/2);
}

